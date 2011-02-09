#include "pch.h"

#include "base/String.h"

#include <utfcpp/checked.h>
#include <utfcpp/unchecked.h>

using namespace gb;
using namespace str;

// �������������� ����������� ����� ����� ��� ���������� (������������ �������� ������)
#define GB_PRERESERVE_STRINGS 1

std::string toUtf8( const std::wstring & wide )
{
	std::string utf8;
#if GB_PRERESERVE_STRINGS
	// ���������������� ������� ��� ������� ����� 2 �����
	utf8.reserve( wide.length() * 2 );
#endif
	utf8::utf16to8 (wide.begin(), wide.end(), std::back_inserter(utf8));
	return utf8;
}

std::wstring toWide( const std::string & utf8 )
{
	std::wstring wide;
#if GB_PRERESERVE_STRINGS
	// ���������������� ������� ��� ������� 1 ����
	wide.reserve( utf8.length() );
#endif
	utf8::utf8to16 (utf8.begin(), utf8.end(), std::back_inserter(wide));
	return wide;
}

#undef GB_PRERESERVE_STRINGS
