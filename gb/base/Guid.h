/*! \file Guid.h
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	Реализация 128-битного аналога Windows GUID, без поддержки генерации новых GUID.
 */
#pragma once

#include <gb/Config.h>
#include <gb/str/String.h>
#include <gb/base/Timer.h>

#include <sstream>

// Включить поддержку классом Boost.Serialize
#define GB_ENABLE_BOOST_SERIALIZE 1


#if GB_ENABLE_BOOST_SERIALIZE
#include <boost/serialization/serialization.hpp>
#endif


namespace gb
{
	namespace base
	{


/*! \briefСтруктура представляет собой имитацию Windows GUID, с минимальной поддержкой генерации
 * Для поддержки корректной генерации новых GUID обращайтесь к WinAPI UuidCreate(), CoCreateGuid()
 * Для использования надо задать структуру Flavor, смотрите макрос DEFINE_NEW_GUID_TYPE ниже
 * Типы GUID с разными Flavor несовместимы для присваивания, сравнения и т.д. Это сделано специально
 * для уменьшения путаницы между ресурсами и хранилищами разных типов
 */
template <class Flavor>
struct GuidTemplate
{
	typedef GuidTemplate<Flavor> ThisClass;

	uint32_t D1, D2, D3, D4;



	GuidTemplate(): D1(0), D2(0), D3(0), D4(0)
	{
		//memset (Data, 0, sizeof(Data));
	}



	GuidTemplate (uint32_t a, uint32_t b, uint32_t c, uint32_t d): D1(a), D2(b), D3(c), D4(d)
	{
		/*Data[0] = a;
		Data[1] = b;
		Data[2] = c;
		Data[3] = d;*/
	}



	GuidTemplate (const ThisClass & other)
	{
		//memcpy (Data, other.Data, sizeof(Data));
		D1 = other.D1;
		D2 = other.D2;
		D3 = other.D3;
		D4 = other.D4;
	}



	//! Проверка на нули
	inline bool isZero() const
	{
		//return ! Data[0] && ! Data[1] && ! Data[2] && ! Data[3];
		return !D1 && !D2 && !D3 && !D4;
	}



	//! Обнуляет GUID
	void setZero()
	{
		//memset (Data, 0, sizeof(Data));
		D1 = D2 = D3 = D4 = 0;
	}



	void generateSimple (uint32_t id)
	{
		D1 = ((uint16_t)id << 16) | (uint16_t)id;
		// TODO: заменить на кроссплатформенный доступ к миллисек.таймеру
		D2 = (uint32_t)gb::base::Timer::getTickCount();
		D3 = id;
		D4 = id;
/*
		Data[0] = (uint16_t)(id << 16) | (uint16_t)id;
		Data[1] = OS::GetTickCount();
		Data[2] = id;
		Data[3] = id;
*/
	}



	//! Представление в виде строки
	inline std::string toString() const
	{
		std::stringstream ss;
		ss << (*this);
		return ss.str();
	}



	//! Короткое представление GUID по первым 4 цифрам + код типа GUID из структуры Flavor
	std::string toShortPrefix() const
	{
		std::stringstream ss;	
		ss << Flavor::TypePrefix() << "=";
		ss.width(4);
		ss.fill(L'0');
		//ss << std::hex << (Data [0] >> 16);
		ss << std::hex << (D1 >> 16);
		return ss.str();
	}



	//! Создаёт имя для использования в питоне вида "prefix_000000001111111122222222"
	//! Для генерации функций в скриптовом языке, которые были бы уникальны по этому Guid
	//! например: def WidgetClick_000000001111111122222222():
	std::string toPythonIdentifier (const std::string & prefix) const
	{
		std::stringstream ss;
		ss << prefix;

		ss.width(8);
		ss.fill(L'0');
		//ss << std::hex << Data [0];
		ss << std::hex << D1;

		ss.width(8);
		ss.fill(L'0');
		//ss << Data [1];
		ss << D2;

		ss.width(8);
		ss.fill(L'0');
		//ss << Data [2];
		ss << D3;

		ss.width(8);
		ss.fill(L'0');
		//ss << Data [3];
		ss << D4;

		return ss.str();
	}

	

	//! Сравнение гуидов, требуется для использования его как ключа в словарях
	inline bool operator < (const ThisClass & other) const
	{
		if (D1 < other.D1) return true;
		if (D1 == other.D1)
		{
			if (D2 < other.D2) return true;
			if (D2 == other.D2)
			{
				if (D3 < other.D3) return true;
				if (D3 == other.D3)
				{
					if (D4 < other.D4) return true;
				}
			}
		}
		return false;

	}



	//! Просто сравнение
	inline bool operator == (const ThisClass & other) const
	{
		if (D1 != other.D1) return false;
		if (D2 != other.D2) return false;
		if (D3 != other.D3) return false;
		if (D4 != other.D4) return false;
		return true;
	}



	inline bool operator != (const ThisClass & other) const
	{
		return !(*this == other);
	}

	typedef std::list <ThisClass> List;
	typedef std::set <ThisClass> Set;
	typedef std::vector <ThisClass> Vector;

	template <class OtherGuidType>
	OtherGuidType ConvertTo()
	{
		OtherGuidType v;
		//memcpy (v.Data, Data, sizeof(Data));
		v.D1 = D1;
		v.D2 = D2;
		v.D3 = D3;
		v.D4 = D4;
		return v;
	}

#ifdef GB_ENABLE_BOOST_SERIALIZE
protected:
	// BOOST SERIALIZATION
	friend class boost::serialization::access;

	template <class Archive>
	void serialize (Archive & ar, const uint32_t version)
	{
		ar & D1 & D2 & D3 & D4;
	}
#endif
}; // class GuidTemplate



template <class Flavor>
std::ostream & operator<<( std::ostream & os, const GuidTemplate<Flavor> & p )
{
	// 8 знаков
	os.width(8);
	os.fill('0');
	os << std::hex << p.D1 << "-";

	// 4 знака
	os.width(4);
	os.fill('0');
	os << (uint16_t)(p.D2 >> 16) << "-";

	// 4 знака
	os.width(4);
	os.fill('0');
	os << (uint16_t)(p.D2) << "-";

	// 4 знака
	os.width(4);
	os.fill('0');
	os << (uint16_t)(p.D3 >> 16) << "-";

	// 4 + 8 = 12 знаков
	os.width(4);
	os.fill('0');
	os << (uint16_t)(p.D3);

	os.width(8);
	os.fill('0');
	os << p.D4;
	return os;
}



template <class Flavor>
std::istream & operator>>( std::istream & is, GuidTemplate<Flavor> & p )
{
	std::string		str;
 	is >> str;

	if (str.empty()) {
		p.setZero();
		return is;
	}
	
	std::vector <std::string> parts;
	// error: ‘ba’ has not been declared
	//gb::str::split (parts, str, ba::is_any_of ("-"));
	gb::str::split (parts, str, "-");
	if (parts.size() != 5)
	{
		p.setZero();
		return is;
	}

	p.D1 = gb::str::uint32FromHex (parts[0]);
	p.D2 = (uint16_t)gb::str::uint32FromHex (parts[1]) << 16 | (uint16_t)gb::str::uint32FromHex (parts[2]);
 	uint64_t last = gb::str::uint64FromHex (parts[4]);
	p.D3 = (uint16_t)gb::str::uint32FromHex (parts[3]) << 16 | (uint16_t)(last >> 32);
	p.D4 = (uint32_t)last;

	return is;
}

// Макрос создаёт новый тип GUID на основе шаблона GuidTemplate
#define DEFINE_NEW_GUID_TYPE( GUIDNAME ) \
	typedef struct { \
		static const char * TypePrefix() { return #GUIDNAME; } \
	} GUIDFL_##GUIDNAME; \
	typedef GuidTemplate <GUIDFL_##GUIDNAME>	GUIDNAME##Guid;

// создадим новый тип - StringGuid
DEFINE_NEW_GUID_TYPE( String );

	} // namespace base
} // namespace gb
