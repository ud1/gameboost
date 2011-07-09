/**
 * @ingroup filesystem_group
 * @file Helpers.h
 * \brief Вспомогательные функции для загрузки файла из виртуальной файловой системы
 */

#pragma once
#include "FileSystem.h"

namespace gb
{
	namespace fs
	{
		/** Читает файл целиком в строку */
		void readEntireFile(InputStream &input, std::string &out);
		
		/** Читает файл целиком в utf8-строку */
		void readEntireFileToUtf8(InputStream &input, std::string &out);
		
		/** Читает файл целиком в строку */
		bool readEntireFile(FileSystem &file_system, const std::string &file_name, std::string &out);
		
		/** Читает файл целиком в utf8-строку */
		bool readEntireFileToUtf8(FileSystem &file_system, const std::string &file_name, std::string &out);
	}
}