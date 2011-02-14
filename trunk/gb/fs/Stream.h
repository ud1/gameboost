#pragma once

#include <gb/base/IRefCountable.h>
#include <gb/fs/SeekType.h>

namespace gb
{
	namespace fs
	{
		class InputStream : public base::IRefCountable
		{
		public:
			virtual bool		eof() const = 0;
			virtual size_t		read(char *output, size_t size) = 0;
			virtual void		seek(off_t pos, eSeekType::SeekType seek_type ) = 0;
			virtual off_t		size() = 0;
			virtual off_t		tell() = 0;
		};
		
		class OutputStream : public base::IRefCountable
		{
		public:
			virtual void		seek(off_t pos, eSeekType::SeekType seek_type ) = 0;
			virtual off_t		size() = 0;
			virtual off_t		tell() = 0;
			virtual size_t		write(char const *input, size_t size) = 0;
		};
		
		class IOStream : public base::IRefCountable
		{
		public:
			virtual bool		eof() const = 0;
			virtual size_t		read(char *output, size_t size) = 0;
			virtual size_t		write(char const *input, size_t size) = 0;
			virtual void		seek(off_t pos, eSeekType::SeekType seek_type ) = 0;
			virtual off_t		size() = 0;
			virtual off_t		tell() = 0;
		};
	}
}
