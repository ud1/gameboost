/** \file  formater.h
*  \brief ����� �������������� ������� ����� ��/� ������/������.
*
*
*   \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*
*  - ������� � ������������ ��� str
*  - ������� ����� ��� ����������� �� ����� windows
*  - ��������� ��� �����.
*
*
*/

#pragma once

#include <gb/base/Types.h>
#include <gb/Config.h>
#include <gb/str/KsDefines.h>


namespace gb {

	namespace str {




	/** \brief ����� ����������� ������� �������������� ������� ����� ��/� ������/������. <br> 
		 �������� ��� �� ��������� ������ ������� . */
	class Formater {
	public:

	/** \brief �������������� bool � ������ */
	static const char* boolToCstr(bool b) ;

	/** \brief �������������� BOOL � ������ */
	static const char* boolToUppercaseCstr(bool b) ;

	/** \brief �������������� float � ������ */
	static const char* floatToCstr(float f) ;

	static bool floatFromCstr( KS_OUT float* val, const char* s ) ;
	static bool floatFromCstr(KS_OUT float& val, const char* s) ;

	/** \brief ��������������  ��������� ������ � ������  */
	static const char* intToCstr(int32_t i) ;

	/** \brief ��������������  ��������� ������ �� ������. ���� �������� �������� ����� false  */
	static bool intFromCstr(KS_OUT int32_t* val, const char* s) ;

	static bool intFromCstr(KS_OUT int32_t& val, const char* s) ;

	/** \brief ��������������  ������������ ������ � ������  */
	static const char* uintToCstr(uint32_t val) ;

	static bool uintFromCstring(KS_OUT uint32_t& val, const char* s);

	/** \brief ��������������  ������ � ������  � ����������������� ����   */
	static const char* intToHex(int32_t i) ;
	/** \brief ��������������  ������ � ������  � ����������������� ���� � ��������� "0x" */
	static const char* intToCppHex(int32_t i) ; 

	/** \brief  ������� ��������� � ���� hex-������  � ����� buff  � ��������� � ������� ��������.  <BR>
	    ����� ������ ���� ������ �� ����� 11 . ������ ���������� = 0xA23A98FC  */
	static const char* pointerToCstr(const void* p) ;
	
	/** \brief ��������� ��������� ������ �� ����� . */
	static const char* byteToCStrAsBin(uint8_t u) ;

	/** \brief �������������� uint32_t � �������� �������������. */
	static const char* uintToBinCstr(uint32_t dwArg) ;

    /** \brief �������������� uint32_t � c���������  �������������. ���� bAsHex==true �� � ����������������� ����. */
	static const char* uintToCstr(const uint32_t dw, bool bAsHex=false) ;

	/** \brief ����� �������� ��������  0xAF33. �� ���� ������ ������� 0x ��������� ��� � hex . */
	static bool uintFromCstr(KS_OUT uint32_t* pdwOut, const char* s) ;
	static bool uintFromCstr(KS_OUT uint32_t& dw,     const char* s) ;

	/** \brief �������������� � uint �� ������ ���������� ����� � �������� ����. */
	static uint32_t uintFromBinCstr(const char* _s, int32_t nlen= -1) throw(); 

	/** \brief ��������� ������ �� ������� �������� ����� uint32_t */
	static void print_bits(  uint32_t value) ;

	/** \brief ������ uint32_t �������� � �������� ���� �� ������� */
	static void printDwordAsBin(const uint32_t dw) ;
	/** \brief ������  �����  � �������� ������������� �� ������� . */
	static void printByteAsBin(uint8_t u) ;
	


#ifdef _WIN32
	/** \brief ����� ���� � ������ */
	static uint32_t hwndAsUint(const HWND hwnd) ;
#endif

 
 

    };
    // end class
	
	
	
	}
	// end namespace str

}
// end namespace gb






// end file