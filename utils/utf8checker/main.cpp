#include <gb/fs/LocalFS.h>
#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>
#include <gb/str/UnicodeHelpers.h>

#include <string>
#include <vector>
#include <algorithm>

#include <boost/filesystem.hpp>

using namespace gb::fs;
using namespace gb::str;
using namespace boost::filesystem;

LocalFS file_system;
std::vector<wchar_t> chars;

wchar_t cp1251ToUtf16Table[] =
{
	/*0x80*/ 0x402, 0x403, 0x201A, 0x453, 0x201E, 0x2026, 0x2020, 0x2021, 0x20AC, 0x2030, 0x409, 0x2039, 0x40A, 0x40C, 0x40B, 0x40F, 
	/*0x90*/ 0x452, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x0, 0x2122, 0x459, 0x203A, 0x45A, 0x45C, 0x45B, 0x45F,
	/*0xA0*/ 0xA0, 0x40E, 0x45E, 0x408, 0xA4, 0x490, 0xA6, 0xA7, 0x401, 0xA9, 0x404, 0xAB, 0xAC, 0xAD, 0xAE, 0x407,
	/*0xB0*/ 0xB0, 0xB1, 0x406, 0x456, 0x491, 0xB5, 0xB6, 0xB7, 0x451, 0x2116, 0x454, 0xBB, 0x458, 0x405, 0x455, 0x457,
	/*0xC0*/ 0x410, 0x411, 0x412, 0x413, 0x414, 0x415, 0x416, 0x417, 0x418, 0x419, 0x41A, 0x41B, 0x41C, 0x41D, 0x41E, 0x41F,
	/*0xD0*/ 0x420, 0x421, 0x422, 0x423, 0x424, 0x425, 0x426, 0x427, 0x428, 0x429, 0x42A, 0x42B, 0x42C, 0x42D, 0x42E, 0x42F,
	/*0xE0*/ 0x430, 0x431, 0x432, 0x433, 0x434, 0x435, 0x436, 0x437, 0x438, 0x439, 0x43A, 0x43B, 0x43C, 0x43D, 0x43E, 0x43F,
	/*0xF0*/ 0x440, 0x441, 0x442, 0x443, 0x444, 0x445, 0x446, 0x447, 0x448, 0x449, 0x44A, 0x44B, 0x44C, 0x44D, 0x44E, 0x44F
};

void convertFromCp1251(const std::string &filename, const std::string &str)
{
	std::wstring wstr;
	wstr.reserve(str.size());
	
	for (size_t i = 0; i < str.size(); ++i)
	{
		unsigned char ch = str[i];
		
		if (ch < 0x80)
			wstr += ch;
		else
			wstr += cp1251ToUtf16Table[ch - 0x80];
	}
	
	std::string utf8string;
	wstringToUtf8(wstr, utf8string);
	
	OutputStream *file = file_system.getOutputStream(filename, true);
	file->write(utf8string.c_str(), utf8string.size());
	file->release();
}

void checkFile(const std::string &filename)
{
	std::string str;
	std::wstring wstr;
	
	try
	{
		readEntireFileToUtf8(file_system, filename, str);
		utf8ToWstring(str, wstr);
	}
	catch(...)
	{
		ERROR_LOG("invalid encoding, file: " << filename);
		convertFromCp1251(filename, str);
		ERROR_LOG("Converted from cp1251 to utf8: " << filename);
		return;
	}
	
	for (size_t i = 0; i < wstr.size(); ++i)
	{
		wchar_t ch = wstr[i];
		if (!std::binary_search(chars.begin(), chars.end(), ch))
		{
			ERROR_LOG("invalid encoding, wrong character, file: " << filename);
			return;
		}
	}
}

void recurse(const path &dir)
{
	if (exists(dir) && is_directory(dir))
	{
		directory_iterator it(dir);
		for (; it != directory_iterator(); ++it)
		{
			path f = *it;
			if (is_directory(f))
				recurse(f);
			else
			{
				std::string extension = f.extension().c_str();
				if (extension == ".h" || extension == ".cpp")
					checkFile(f.string());
			}
		}
	}
}

int main()
{
	for (wchar_t ch = L'a'; ch <= L'z'; ++ch)
		chars.push_back(ch);
	
	for (wchar_t ch = L'A'; ch <= L'Z'; ++ch)
		chars.push_back(ch);
	
	for (wchar_t ch = L'0'; ch <= L'9'; ++ch)
		chars.push_back(ch);
	
	for (wchar_t ch = L'а'; ch <= L'я'; ++ch)
		chars.push_back(ch);
	
	for (wchar_t ch = L'А'; ch <= L'Я'; ++ch)
		chars.push_back(ch);
	
	chars.push_back(L'ё');
	chars.push_back(L'Ё');
	chars.push_back(L'®');
	
	chars.push_back(L'.');
	chars.push_back(L',');
	chars.push_back(L' ');
	chars.push_back(L'*');
	chars.push_back(L'/');
	chars.push_back(L'#');
	chars.push_back(L'%');
	chars.push_back(L'\"');
	chars.push_back(L'\'');
	chars.push_back(L'‘');
	chars.push_back(L'’');
	chars.push_back(L'`');
	chars.push_back(L'\\');
	chars.push_back(L';');
	chars.push_back(L'^');
	chars.push_back(L'&');
	chars.push_back(L'(');
	chars.push_back(L')');
	chars.push_back(L'[');
	chars.push_back(L']');
	chars.push_back(L'{');
	chars.push_back(L'}');
	chars.push_back(L'+');
	chars.push_back(L'-');
	chars.push_back(L'<');
	chars.push_back(L'>');
	chars.push_back(L'=');
	chars.push_back(L'|');
	chars.push_back(L':');
	chars.push_back(L'_');
	chars.push_back(L'~');
	chars.push_back(L'!');
	chars.push_back(L'@');
	chars.push_back(L'?');
	chars.push_back(L'$');
	chars.push_back(L'\t');
	chars.push_back(L'\n');
	chars.push_back(L'\r');
	chars.push_back(65279);
	
	std::sort(chars.begin(), chars.end());
	
	recurse("../");
}