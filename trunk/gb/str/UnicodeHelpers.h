#pragma once

#include <gb/base/Types.h>

#include <string>
#include <algorithm>
#include <utfcpp/utf8.h>

namespace gb
{
	namespace str
	{
		
		namespace details
		{
			
			template <size_t fsize, size_t tsize>
			struct StringConverter{};
			
			template <size_t s>
			struct StringConverter<s, s>
			{
				template <typename F, typename T>
				void convert(const F *from, size_t size, std::basic_string<T> to)
				{
					to.append(from, from + size);
				}
			};
			
			template <>
			struct StringConverter<1, 2>
			{
				template <typename F, typename T>
				void convert(const F *from, size_t size, std::basic_string<T> &to)
				{
					utf8::utf8to16(from, from + size, std::back_inserter(to));
				}
			};
			
			template <>
			struct StringConverter<1, 4>
			{
				template <typename F, typename T>
				void convert(const F *from, size_t size, std::basic_string<T> &to)
				{
					utf8::utf8to32(from, from + size, std::back_inserter(to));
				}
			};
			
			template <>
			struct StringConverter<2, 1>
			{
				template <typename F, typename T>
				void convert(const F *from, size_t size, std::basic_string<T> &to)
				{
					utf8::utf16to8(from, from + size, std::back_inserter(to));
				}
			};
			
			template <>
			struct StringConverter<4, 1>
			{
				template <typename F, typename T>
				void convert(const F *from, size_t size, std::basic_string<T> &to)
				{
					utf8::utf32to8(from, from + size, std::back_inserter(to));
				}
			};
		}

		inline void wstringToUtf8(const std::wstring &str, std::string &result)
		{
			details::StringConverter<sizeof(wchar_t), sizeof(char)>().convert<wchar_t, char>(str.c_str(), str.size(), result);
		}
		
		inline std::string wstringToUtf8(const std::wstring &str)
		{
			std::string result;
			wstringToUtf8(str, result);
			return result;
		}
		
		inline void utf8ToWstring(const std::string &str, std::wstring &result)
		{
			details::StringConverter<sizeof(char), sizeof(wchar_t)>().convert<char, wchar_t>(str.c_str(), str.size(), result);
		}
		
		inline std::wstring utf8ToWstring(const std::string &str)
		{
			std::wstring result;
			utf8ToWstring(str, result);
			return result;
		}
		
		namespace encoding
		{
			enum eEncoding
			{
				ENC_NONE,
				UTF32BE,
				UTF32LE,
				UTF16BE,
				UTF16LE,
				UTF8
			};
		}
		
		// Byte Order Mark
		// http://unicode.org/faq/utf_bom.html
		inline encoding::eEncoding checkBOM(const std::string &str)
		{
			if (str.size() < 2)
				return encoding::ENC_NONE;
			
			if (str[0] == (char)0xFE && str[1] == (char)0xFF)
				return encoding::UTF16BE;
			if (str[0] == (char)0xFF && str[1] == (char)0xFE)
				return encoding::UTF16LE;

			if (str.size() < 3)
				return encoding::ENC_NONE;
			if (str[0] == (char)0xef && str[1] == (char)0xBB && str[2] == (char)0xBF)
				return encoding::UTF8;

			if (str.size() < 4)
				return encoding::ENC_NONE;

			if (str[0] == (char)0x00 && str[1] == (char)0x00 && str[2] == (char)0xFE && str[3] == (char)0xFF)
				return encoding::UTF32BE;
			if (str[0] == (char)0xFF && str[1] == (char)0xFE && str[2] == (char)0x00 && str[3] == (char)0x00)
				return encoding::UTF32LE;

			return encoding::ENC_NONE;
		}
		
		inline std::string getBOM(encoding::eEncoding enc)
		{
			switch (enc)
			{
				case encoding::UTF8:
					return "\xef\xbb\xbf";
				case encoding::UTF16BE:
					return "\xfe\xff";
				case encoding::UTF16LE:
					return "\xff\xfe";
				case encoding::UTF32BE:
					return "\x00\x00\xfe\xff";
				case encoding::UTF32LE:
					return "\xff\xfe\x00\x00";
			}
			
			return "";
		}
		
		inline void changeEndianess16(const std::string &str_in, std::string &str_out)
		{
			str_out.resize(str_in.size());
			for (size_t i = 0; i < str_in.size()/2; ++i)
			{
				str_out[2*i+1] = str_in[2*i+0];
				str_out[2*i+0] = str_in[2*i+1];
			}
		}
		
		inline void changeEndianess16(std::string &str)
		{
			for (size_t i = 0; i < str.size()/2; ++i)
			{
				char v0 = str[2*i+0];
				char v1 = str[2*i+1];
				str[2*i+1] = v0;
				str[2*i+0] = v1;
			}
		}
		
		void changeEndianess32(const std::string &str_in, std::string &str_out)
		{
			str_out.resize(str_in.size());
			for (size_t i = 0; i < str_in.size()/4; ++i)
			{
				str_out[4*i+3] = str_in[4*i+0];
				str_out[4*i+2] = str_in[4*i+1];
				str_out[4*i+1] = str_in[4*i+2];
				str_out[4*i+0] = str_in[4*i+3];
			}
		}

		inline void changeEndianess32(std::string &str)
		{
			for (size_t i = 0; i < str.size()/4; ++i)
			{
				char v0 = str[2*i+0];
				char v1 = str[2*i+1];
				char v2 = str[2*i+2];
				char v3 = str[2*i+3];
				str[4*i+3] = v0;
				str[4*i+2] = v1;
				str[4*i+1] = v2;
				str[4*i+0] = v3;
			}
		}
		
		inline bool is_big_endian()
		{
			union
			{
				uint32_t i;
				char c[4];
			} const bint = {0x01020304};

			return bint.c[0] == 1; 
		}
		
		inline void rawStringToUtf8(const std::string &str, std::string &out)
		{
			encoding::eEncoding enc = checkBOM(str);
			bool big_endian = is_big_endian();
			switch (enc)
			{
				case encoding::ENC_NONE:
				case encoding::UTF8:
					out = str;
					return;
				case encoding::UTF32BE:
				{
					if (big_endian)
					{
						details::StringConverter<4, sizeof(char)>().convert<uint32_t, char>((const uint32_t *)str.c_str(), str.size() / 4, out);
						return;
					}
					else
					{
						std::string temp;
						changeEndianess32(str, temp);
						details::StringConverter<4, sizeof(char)>().convert<uint32_t, char>((const uint32_t *)temp.c_str(), temp.size() / 4, out);
						return;
					}
				}
				case encoding::UTF32LE:
				{
					if (!big_endian)
					{
						details::StringConverter<4, sizeof(char)>().convert<uint32_t, char>((const uint32_t *)str.c_str(), str.size() / 4, out);
						return;
					}
					else
					{
						std::string temp;
						changeEndianess32(str, temp);
						details::StringConverter<4, sizeof(char)>().convert<uint32_t, char>((const uint32_t *)temp.c_str(), temp.size() / 4, out);
						return;
					}
				}
				case encoding::UTF16BE:
				{
					if (big_endian)
					{
						details::StringConverter<2, sizeof(char)>().convert<uint16_t, char>((const uint16_t *)str.c_str(), str.size() / 2, out);
						return;
					}
					else
					{
						std::string temp;
						changeEndianess16(str, temp);
						details::StringConverter<2, sizeof(char)>().convert<uint16_t, char>((const uint16_t *)temp.c_str(), temp.size() / 2, out);
						return;
					}
				}
				case encoding::UTF16LE:
				{
					if (!big_endian)
					{
						details::StringConverter<2, sizeof(char)>().convert<uint16_t, char>((const uint16_t *)str.c_str(), str.size() / 2, out);
						return;
					}
					else
					{
						std::string temp;
						changeEndianess16(str, temp);
						details::StringConverter<2, sizeof(char)>().convert<uint16_t, char>((const uint16_t *)temp.c_str(), temp.size() / 2, out);
						return;
					}
				}
			}
		}
		
		inline std::string rawStringToUtf8(const std::string &str)
		{
			std::string result;
			rawStringToUtf8(str, result);
			return result;
		}
		
		inline void rawStringToWstring(const std::string &str, std::wstring &out)
		{
			std::string utf8str;
			rawStringToUtf8(str, utf8str);
			utf8ToWstring(utf8str, out);
		}
		
		inline std::wstring rawStringToWstring(const std::string &str)
		{
			std::wstring result;
			rawStringToWstring(str, result);
			return result;
		}
	}
}
