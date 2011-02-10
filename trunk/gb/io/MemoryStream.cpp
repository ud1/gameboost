/*	\file MemoryStream.cpp
 *	\author -Eugene-, kozlov_eugene@list.ru
*/
#include "pch.h"

#include <gb/io/MemoryStream.h>

using namespace gb::io;

MemoryStream::MemoryStream(void) : IStream(), file(0), file_size(0), offset(0) {};
            
MemoryStream::MemoryStream(size_t _size, int mode) : IStream(), file(0), file_size(0), offset(0)
{
    create(_size, mode);
};

MemoryStream::~MemoryStream(void)
{
    if(file)
        delete[]file;
    file = 0;
    file_size = 0;
    offset = 0;
};

uint8_t*MemoryStream::create(size_t _size, int mode)
{
    if(file || (mode & eFileAccess::APPEND) || (mode & eFileAccess::TRUNCATE))
        return file;
    file_size = _size;
    offset = 0;
    file_access = mode;
    file = new uint8_t[file_size];
    return file;
};

size_t MemoryStream::write(const void*buffer, const size_t size)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_write = file_size - offset;
    if(bytes_for_write > size)
        bytes_for_write = size;
    memcpy((void*)(file + offset), buffer, bytes_for_write);
    return bytes_for_write;
};

size_t MemoryStream::read(void*buffer, const size_t size)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_read = file_size - offset;
    if(bytes_for_read > size)
        bytes_for_read = size;
    memcpy(buffer, (void*)(file + offset), bytes_for_read);
    return bytes_for_read;
};

size_t MemoryStream::tell()
{
    if(!file)
        return 0;
    return offset;
};

bool MemoryStream::seek(const size_t offset_, const int origin)
{
    if(!file)
        return false;
    int64_t res_offset = 0;
    if(origin == SEEK_SET)      res_offset = offset_;          
    else if(origin == SEEK_CUR) res_offset = offset_ + offset; 
    else if(origin == SEEK_END) res_offset = file_size + offset;
    if(res_offset < 0 || res_offset >= file_size)
        return false; 
    offset = (size_t)res_offset;
    return true;
};

void MemoryStream::close()
{
    if(!file)
        return;
    delete[]file;
    file = 0;
    offset = 0;
};

size_t MemoryStream::size()
{
    if(!file)
        return 0;
    return file_size;
};

bool MemoryStream::isOpened()
{
    return file != 0;   
};

size_t MemoryStream::write(const void*buffer, const size_t size, const size_t _offset)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_write = file_size - _offset;
    if(bytes_for_write > size)
        bytes_for_write = size;
    memcpy((void*)(file + _offset), buffer, bytes_for_write);
    return bytes_for_write;
};

size_t MemoryStream::read(void*buffer, const size_t size, const size_t _offset)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_read = file_size - _offset;
    if(bytes_for_read > size)
        bytes_for_read = size;
    memcpy(buffer, (void*)(file + _offset), bytes_for_read);
    return bytes_for_read;
};

bool MemoryStream::eof()
{
    return file_size == offset;   
};
