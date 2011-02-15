#include "pch.h"

#include <gb/fs/Helpers.h>

namespace gb
{
	namespace fs
	{
		void readEntireFile(InputStream *input, std::string &out)
		{
			size_t size = input->size();
			char *data = new char[size];
			input->read(data, size);
			out.assign(data, size);
			delete []data;
		}
		
		bool readEntireFile(FileSystem *file_system, const std::string &file_name, std::string &out)
		{
			InputStream *input = file_system->getInputStream(file_name);
			if (!input)
				return false;

			readEntireFile(input, out);
			input->release();
			return true;
		}
	}
}