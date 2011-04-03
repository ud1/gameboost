

#include <gb/fs/Helpers.h>
#include <gb/str/UnicodeHelpers.h>

namespace gb
{
	namespace fs
	{
		void readEntireFile(InputStream &input, std::string &out)
		{
			size_t size = input.size();
			char *data = new char[size];
			input.read(data, size);
			out.assign(data, size);
			delete []data;
		}
		
		void readEntireFileToUtf8(InputStream &input, std::string &out)
		{
			std::string raw_string;
			readEntireFile(input, raw_string);
			str::rawStringToUtf8(raw_string, out);
		}
		
		bool readEntireFile(FileSystem &file_system, const std::string &file_name, std::string &out)
		{
			InputStream *input = file_system.getInputStream(file_name);
			if (!input)
				return false;

			readEntireFile(*input, out);
			input->release();
			return true;
		}
		
		bool readEntireFileToUtf8(FileSystem &file_system, const std::string &file_name, std::string &out)
		{
			std::string raw_string;
			readEntireFile(file_system, file_name, raw_string);
			str::rawStringToUtf8(raw_string, out);
		}
	}
}