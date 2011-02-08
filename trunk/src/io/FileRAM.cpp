#include "precompiled_headers.h"

#include "io/FileRAM.h"

#include <stdio.h>
#include <string>

using namespace gb::io;

FileRAM::FileRAM(void) : IFile(), file(0), file_size(0), offset(0) {};
            
FileRAM::FileRAM(size_t _size) : IFile(), file(0), file_size(0), offset(0)
{
    create(_size);
};

FileRAM::~FileRAM(void)
{
    if(file)
        delete[]file;
    file = 0;
    file_size = 0;
    offset = 0;
};

uint8_t*FileRAM::create(size_t _size)
{
    if(file)
        return file;
    file_size = _size;
    offset = 0;
    file = new uint8_t[file_size];
    return file;
};

size_t FileRAM::write(const void*buffer, const size_t size)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_write = file_size - offset;
    if(bytes_for_write > size)
        bytes_for_write = size;
    memcpy((void*)(file + offset), buffer, size);
    return bytes_for_write;
};

size_t FileRAM::read(void*buffer, const size_t size)
{
    if(!file || !buffer || !size)
        return 0;
    size_t bytes_for_read = file_size - offset;
    if(bytes_for_read > size)
        bytes_for_read = size;
    memcpy(buffer, (void*)(file + offset), size);
    return bytes_for_read;
};

size_t FileRAM::tell()
{
    if(!file)
        return 0;
    return offset;
};

bool FileRAM::seek(const size_t offset_, const int origin)
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

void FileRAM::close()
{
    if(!file)
        return;
    delete[]file;
    file = 0;
    offset = 0;
};

size_t FileRAM::size()
{
    if(!file)
        return 0;
    return file_size;
};

bool FileRAM::isOpened()
{
    return file != 0;   
};
