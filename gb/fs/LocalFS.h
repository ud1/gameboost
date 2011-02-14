#pragma once

#include <gb/fs/FileSystem.h>

namespace gb
{
	namespace fs
	{
		class LocalFS : public FileSystem
		{
		public:
			InputStream *getInputStream(const std::string &path);
			OutputStream *getOutputStream(const std::string &path, bool truncate);
			IOStream *getIOStream(const std::string &path, bool truncate);
		};
	}
}


