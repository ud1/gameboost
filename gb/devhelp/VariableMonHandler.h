/** \file
 \brief Класс для изменения значение нажатием клавиш.
   Полезен при отладке.

 
  \todo добавить для нормали , координаты,  одним методом.
  \todo  Изменение параметров форматирования.

*/

#pragma once

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <assert.h>

// времянка !!!  удалить потом
#if (defined(WIN32))
#include <windows.h>
#endif


namespace gb {

namespace devhelp {

#pragma warning(push)
#pragma warning(disable : 4996)

 
//! \brief  Класс для изменения значение нажатием клавиш
class VariableMonHandler {
public:
	std::string name;  ///< имя хэндлера

	//! в конструкторе передать имя
	VariableMonHandler(const char* name): m_nCurrItem(0) 
	{ 
		if(name)
		{
	      this->name = name;
		}
	  
	}

 
	//! \brief xxxxxxxxx. 
	void add_bool(const char* name, bool* address);

	//! \brief xxxxxxxxx. 
	void add_bool32(const char* name, long* address);    

	//! \brief xxxxxxxxx. 
	void add_float(
			const char* name, 
			float* address,
			float mul_factor,
			float add_factor,
			float minimum,
			float maximum
			);

	//! \brief xxxxxxxxx. 
	void add_int(
			const char* name, 
			int* address, 
			int step,
			int minim,
			int maxim				
			);

	//! \brief xxxxxxxxx. 
	void add_uint(
			const char* name,
			unsigned int* address,
			unsigned int step,
			unsigned int minim, 
			unsigned int maxim
		   );


	//! \brief Построение строки данных для отрисовки на  экране.
	void make_mon_string(std::string& str) const;

	//! \brief Обработать событие нажатия клавиши "вверх". 
	void handlekey_up();

	//! \brief Обработать событие нажатия клавиши "вниз". 
	void handlekey_down();

	//! \brief Обработать событие нажатия клавиши "влево". 
	void handlekey_left()
	{
	   VariableInfo& vi = m_vector.at(m_nCurrItem);
	   vi.handle_low_or_hi(true);
	}

	//! \brief Обработать событие нажатия клавиши "вправо".
	void handlekey_right()
	{
		VariableInfo& vi = m_vector.at(m_nCurrItem);
		vi.handle_low_or_hi(false);
	}

#if (defined(WIN32) && defined(_WINDOWS_))

//! \brief Обработать оконное сообщение. Обработка клавиш производится по сообщению.
void msgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif


private:


	struct VARTYPE
	{
		enum e
		{
			UDEFINED = 0,

			BOOL8,
			BOO32,

			UINT32,
			INT32,

			FLOAT,
			FLOAT2,
 
			FLOAT3_AS_NORMAL,
			FLOAT3_AS_COORD,

			FLOAT4,
			FLOAT4_AS_COLOR,



			UNUSED_DECL_LAST,

			UNUSED_FORCE32 = 0x7f000000
		};
	};


	class VariableInfo {
	public:

		union  DATA32 
		{
			int _int;
			unsigned int _uint;
			float _float;
		};


		VariableInfo( 
			const char* name , 
			const VARTYPE::e type , 
			void* address,
			DATA32 mul_fact,
			DATA32 add_factor,
			DATA32 minim,
			DATA32 maxim
			) throw();


		VARTYPE::e  m_type;
		void* m_address;
		char m_name[32];

		DATA32 m_data32;

		DATA32 m_data_mul_factor;
		DATA32 m_data_add_factor;

		DATA32 m_data_min;
		DATA32 m_data_max;



		//! Построить строку по имени значению.
		void _AppendStr(std::string& str, bool bActiveItem) const ;
		//! изменить значение переменной по адресу. Параметр true если нажата клавиша стрелка вправо.
		void handle_low_or_hi(bool bLow);

	};


    size_t m_nCurrItem;
	std::vector<VariableInfo> m_vector;
};
// end class

//-----------------------------------------------------------------------
 
}
// end namespace
}
// end namespace

#pragma warning(pop)
// end file