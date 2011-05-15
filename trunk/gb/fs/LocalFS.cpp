#include <gb/fs/LocalFS.h>

#include <cstdio>
#include <boost/concept_check.hpp>

namespace
{
	using namespace gb::fs;
	
	class StreamImpl
	{
	public:
		StreamImpl(FILE *file)
		{
			this->file = file;
		}
		
		~StreamImpl()
		{
			fclose(file);
		}
		
		bool eof() const
		{
			return (bool) feof(file);
		}
		
		size_t read(char *output, size_t size)
		{
			return fread((void *) output, 1, size, file);
		}
		
		size_t write(char const *input, size_t size)
		{
			return fwrite((void *) input, 1, size, file);
		}
		
		void seek(gb::fs::off_t pos, eSeekType::SeekType seek_type )
		{
			switch (seek_type)
			{
				case eSeekType::HEAD:
					fseek(file, pos, SEEK_SET);
					break;
				case eSeekType::CURRENT:
					fseek(file, pos, SEEK_CUR);
					break;
				case eSeekType::TAIL:
					fseek(file, pos, SEEK_END);
					break;
			}
		}
		
		gb::fs::off_t size()
		{
			gb::fs::off_t pos = tell();
			seek(0, eSeekType::TAIL);
			gb::fs::off_t res = tell();
			seek(pos, eSeekType::HEAD);
			return res;
		}
		
		gb::fs::off_t tell()
		{
			return ftell(file);
		}
	private:
		FILE *file;
	};
	
	class InputStreamImpl : public InputStream
	{
	public:
		InputStreamImpl(FILE *file) : impl(file) {}
		
		bool eof() const { return impl.eof(); }
		size_t read(char *output, size_t size) { return impl.read(output, size); }
		void seek(gb::fs::off_t pos, eSeekType::SeekType seek_type ) { return impl.seek(pos, seek_type); }
		gb::fs::off_t size() { return impl.size(); }
		gb::fs::off_t tell() { return impl.tell(); }
	
	private:
		StreamImpl impl;
	};
	
	class OutputStreamImpl : public OutputStream
	{
	public:
		OutputStreamImpl(FILE *file) : impl(file) {}
		
		void seek(gb::fs::off_t pos, eSeekType::SeekType seek_type ) { return impl.seek(pos, seek_type); }
		gb::fs::off_t size() { return impl.size(); }
		gb::fs::off_t tell() { return impl.tell(); }
		size_t write(char const *input, size_t size) { return impl.write(input, size); }
	
	private:
		StreamImpl impl;
	};
	
	class IOStreamImpl : public IOStream
	{
	public:
		IOStreamImpl(FILE *file) : impl(file) {}
		
		bool eof() const { return impl.eof(); }
		size_t read(char *output, size_t size) { return impl.read(output, size); }
		size_t write(char const *input, size_t size) { return impl.write(input, size); }
		void seek(gb::fs::off_t pos, eSeekType::SeekType seek_type ) { return impl.seek(pos, seek_type); }
		gb::fs::off_t size() { return impl.size(); }
		gb::fs::off_t tell() { return impl.tell(); }
	
	private:
		StreamImpl impl;
	};
}
namespace gb
{
	namespace fs
	{

		InputStream *LocalFS::getInputStream(const std::string &path)
		{
			FILE *file = fopen(path.c_str(), "rb");
			if (!file)
				return NULL;
			return new InputStreamImpl(file);
		}
		
		OutputStream *LocalFS::getOutputStream(const std::string &path, bool truncate)
		{
			FILE *file;
			if (truncate)
				file = fopen(path.c_str(), "wb");
			else file = fopen(path.c_str(), "ab");
			
			if (!file)
				return NULL;
			return new OutputStreamImpl(file);
		}
		
		IOStream *LocalFS::getIOStream(const std::string &path, bool truncate)
		{
			FILE *file;
			if (truncate)
				file = fopen(path.c_str(), "w+b");
			else
			{
				file = fopen(path.c_str(), "r+b");
				// create file
				if (!file)
					file = fopen(path.c_str(), "wb");
				if (!file)
					return NULL;
				fclose(file);
				
				file = fopen(path.c_str(), "r+b");
			}
			
			if (!file)
				return NULL;
			return new IOStreamImpl(file);
		}
	}
}
