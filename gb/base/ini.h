/** \file

 \brief Чтение/запись в ini-файлы 


 \author ksacvet777

 <br>

 \todo  - сделать удаление секции и ключа в секции
 \todo   - сделать запись/чтение массивов int/float

 \todo - сделать установку опций чтения/записи 
		       (токен разделитель, токен строк и т.д.  )
 
 \todo   -  добавить возможность установки комментариев для ключей
 \todo   -  добавить возможность для ключей-массивов.


*/

#pragma once

#include <gb/base/Types.h>
 
#include <gb/macro.h>

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <stdexcept>
  

#pragma warning(push)
#pragma warning( disable : 4290 )

namespace gb 
{
	
 namespace base 
 {

  /** \brief Чтение/запись в ini-файлы  */
  namespace ini 
  {

  //---------------------------------------------------------------


//! \brief  ключ + значение для ini файла   .
class IniKeyValue {
public:
	 IniKeyValue() {}
	 IniKeyValue(const std::string& skey, const std::string& svalue) 
		        : m_skey(skey), m_svalue(svalue)  {}


	virtual ~IniKeyValue() {}
	
	std::string m_skey;
	std::string m_svalue;

};



//! \brief  секция для ini-файла   .
class IniSection {
public:
	          IniSection(const std::string& sname) : m_sname(sname)  {}
	virtual  ~IniSection() { m_vector_keyval.clear(); }

	//! Получить имя секции
	const std::string& getSectionName() const { return m_sname; }


	bool addKeyValue(const std::string& skey, const std::string& svalue) 
	{
		  IniKeyValue kv(skey, svalue);
		  return    addKeyValue(kv);		
	}

	bool addKeyValue(const IniKeyValue& kv);
 
    IniSection*  addSection(const std::string& sSection);

	bool searchKey(  int& index , const std::string& sKey) const;

	bool isKeyExests(const std::string& sKey);

	int getNumKeys() const { return (int)m_vector_keyval.size(); };

	      IniKeyValue&  getKeyValueByIndex(const int index) throw(std::runtime_error&);
	const IniKeyValue&  getKeyValueByIndex(const int index) const  throw(std::runtime_error&);

	void clearAll() { m_vector_keyval.clear(); };
	
private:
	std::string m_sname;
	std::vector<IniKeyValue> m_vector_keyval;
	
};


//! \brief Главный класс.  Сам ini-файл. Чтение/записть в/из строки в/из файла.
class Ini  {
public:
	          Ini() {}
	 virtual ~Ini() { m_vector_sections.clear(); }

bool searchSection(  int& index, const std::string& sSection) const;
bool isSectionExists(const std::string& sSection) const;

int getNumSections() const { return (int)m_vector_sections.size(); }

IniSection&        getSectionByIndex(const int index) throw(std::runtime_error&);
const IniSection&  getSectionByIndex(const int index) const throw(std::runtime_error&);

IniSection* addSection(const std::string& sSection);

//! \brief Полностью удалить все секции с ключами .
void clearAllData() { m_vector_sections.clear(); }

//! \brief считать из строки   ini-данные .
bool readFromStrData(const std::string& src);

//! \brief записать в строку   ini-данные  .
bool writeToStr(  std::string& dest) const;

//! \brief прочитать  ini-файл .
bool readFromFileA(const char* fname);

//! \brief  записать в ini-файл .
bool writeToFileA(const char* fname) const;

/*
 исключены для unicode так как только для windows

bool ReadFromFileW(const WCHAR* fname); 
bool WriteToFileW(const WCHAR* fname) const;  
*/
	

bool setValue(const std::string& sSection, 
			  const std::string& sKey, 
			  const std::string& sValue );


bool setValueBool( const std::string& sSection, 
			       const std::string& sKey, const bool val );


bool setValueInt( const std::string& sSection, 
			      const std::string& sKey, const int val );


bool setValueFloat( const std::string& sSection, 
			        const std::string& sKey, const float val );


bool getValue( const std::string& sSection, 
			   const std::string& sKey, 
			     std::string& sValue) const ;


bool getValueBool(const std::string& sSection, 
			      const std::string& sKey, 
			      bool& val) const ;

bool getValueInt(const std::string& sSection, 
			     const std::string& sKey, 
			     int& val) const ;

bool getValueFloat(const std::string& sSection, 
			       const std::string& sKey, 
			       float& val) const ;


	friend std::ostream& operator << (std::ostream&os, const Ini& _ini) 
	{  
		std::string str;
		_ini.writeToStr(str);
		os << str << "\n";
		return os;
	}



private:
	bool preprocessString(std::string& str) const;
	bool parseKeyValueString(  std::string& s_OutKey, 
						   std::string& s_OutValue,
						 const std::string& src ) const ;


	std::vector<IniSection> m_vector_sections;
	
};
 

//---------------------------------------------------------------

  }
  // end namespace

 }
 // end namespace

}
// end namespace

#pragma warning(pop)
 

// end file