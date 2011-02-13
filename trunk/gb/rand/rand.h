/** \file rand.h
* \brief Получение случайных значений.
*
* \todo Сделать дополнение из boost random
* \todo убрать из util::formater:: рандом функции
*
*
*
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <gb\base\Types.h>



namespace gb {
	namespace rand {

	/** \brief Генератор случайного bool  */
	bool randomBool(); 

	/** \brief Генератор случайного целого в диапазоне (0 - nmax) */
	int32_t randomMax(int32_t nmax);

	/** \brief Получение случайного целого в диапазоне (nmin - nmax) */
	int32_t randomMinMax(int32_t nmin , int32_t nmax);

	/** \brief Генератор случайного положительного float-числа  в диапазоне:   0.0f ... 1.0f  */
	float randomUnsFloatBetween01() ;

	/** \brief Генератор случайного float-числа со случайным знаком в диапазоне: -1.0f ... +1.0f   */
	float randomSignFloat1() ;

	/** \brief Генератор случайной строки в sOut требуемой длины nLenght 
	        в диапазоне между chrMin и chrMax включитально .
	 chrMin должен быть меньше или равен chrMax. 
	 Ни один из них не должен быть нулём.
	 Возвращает false, если входные параметры некорректны.	 */
	bool randomStr(std::string& sOut, char chrMin, char chrMax, const int nLenght);

	/** \brief Генератор случайной строки латинского алфавита в нижнем регистре.  */
	bool randomStrLatinLowerCase(std::string& sOut,  const int nLenght);

	/** \brief Генератор случайной строки в буфер pdest. 
	 \param 
	   pdest - [out] Буфер назначения. 
	   ndestlen - [out] Длина буфера	включая место под нультерминатор 
			 chrMin, char chrMax -  диапазон символов включительно.
			 nLenght - требуемый размер. Корректируется под ndestlen если больше.	*/
	void randomCstr(char* pdest, int ndestlen, char chrMin, char chrMax, const int nLenght);

 
    } 
	// end namespace rand
	

}
// end namespace gb

// end file