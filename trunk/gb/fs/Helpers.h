#pragma once
#include "FileSystem.h"

namespace gb
{
	namespace fs
	{
		void readEntireFile(InputStream *input, std::string &out);
		bool readEntireFile(FileSystem *file_system, const std::string &file_name, std::string &out);
	}
}