#pragma once

#include <gb/base/IRefCountable.h>
#include <gb/fs/SeekType.h>
#include <stdexcept>

namespace gb
{
	namespace fs
	{
		/** \brief Поток для чтения */
		class InputStream : public base::IRefCountable
		{
		public:
			virtual bool		eof() const = 0;
			virtual size_t		read(char *output, size_t size) = 0;
			virtual void		seek(off_t pos, eSeekType::SeekType seek_type ) = 0;
			virtual off_t		size() = 0;
			virtual off_t		tell() = 0;
			
			template <typename T>
			InputStream &operator >> (T &t)
			{
				if (sizeof(T) != read((char *) &t, sizeof(T)))
					throw std::runtime_error("read error");
				
				return *this;
			}
		};
		
		/** \brief Поток для записи */
		class OutputStream : public base::IRefCountable
		{
		public:
			virtual void		seek(off_t pos, eSeekType::SeekType seek_type ) = 0;
			virtual off_t		size() = 0;
			virtual off_t		tell() = 0;
			virtual size_t		write(char const *input, size_t size) = 0;
			
			template <typename T>
			OutputStream &operator << (const T &t)
			{
				if (sizeof(T) != write((char *) &t, sizeof(T)))
					throw std::runtime_error("write error");
				
				return *this;
			}
		};
		
		/** \brief Поток для чтения и записи */
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
