#pragma once

#include <string>
#include <gb/fs/Stream.h>

namespace gb
{
	namespace fs
	{
		class FileSystem : public base::IRefCountable
		{
		public:
			virtual InputStream *getInputStream(const std::string &path) = 0;
			virtual OutputStream *getOutputStream(const std::string &path, bool truncate) = 0;
			virtual IOStream *getIOStream(const std::string &path, bool truncate) = 0;
		};
		
		typedef base::RefCntHolder<FileSystem> PFileSystem;
	}
}