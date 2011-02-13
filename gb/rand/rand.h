/** \file rand.h
* \brief ��������� ��������� ��������.
*
* \todo ������� ���������� �� boost random
  \todo ������ �� util::formater:: ������ �������
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

	/** \brief ��������� ���������� bool  */
	bool randomBool(); 

	/** \brief ��������� ���������� ������ � ��������� (0 - nmax) */
	int32_t randomMax(int32_t nmax);

	/** \brief ��������� ���������� ������ � ��������� (nmin - nmax) */
	int32_t randomMinMax(int32_t nmin , int32_t nmax);

	/** \brief ��������� ���������� �������������� float-�����  � ���������:   0.0f ... 1.0f  */
	float randomUnsFloatBetween01() ;

	/** \brief ��������� ���������� float-����� �� ��������� ������ � ���������: -1.0f ... +1.0f   */
	float randomSignFloat1() ;

	/** \brief ��������� ��������� ������ � sOut ��������� ����� nLenght 
	        � ��������� ����� chrMin � chrMax ������������ .
	 chrMin ������ ���� ������ ��� ����� chrMax. 
	 �� ���� �� ��� �� ������ ���� ����.
	 ���������� false, ���� ������� ��������� �����������.	 */
	bool randomStr(std::string& sOut, char chrMin, char chrMax, const int nLenght);

	/** \brief ��������� ��������� ������ ���������� �������� � ������ ��������.  */
	bool randomStrLatinLowerCase(std::string& sOut,  const int nLenght);

	/** \brief ��������� ��������� ������ � ����� pdest. 
	 \param 
	   pdest - [out] ����� ����������. 
	   ndestlen - [out] ����� ������	������� ����� ��� �������������� 
			 chrMin, char chrMax -  �������� �������� ������������.
			 nLenght - ��������� ������. �������������� ��� ndestlen ���� ������.	*/
	void randomCstr(char* pdest, int ndestlen, char chrMin, char chrMax, const int nLenght);

 
    } 
	// end namespace rand
	

}
// end namespace gb

// end file