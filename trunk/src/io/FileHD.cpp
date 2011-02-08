#include "FileHD.h"
#include <stdio.h>
using namespace gb::io;

FileHD::FileHD(void) : IFile(), file(0), name("") {};
            
FileHD::FileHD(const char *_name, const char*mode) : IFile(), file(0), name("") 
{
    name = _name;
    open(_name, mode);
};

FileHD::~FileHD(void)
{
    if(file)
        fclose((FILE*)file);
    file = 0;
    name = "";
};

bool FileHD::open(const char *_name, const char*mode)
{
    if(file)
        return false;
    name = _name;
    file = (int32_t)fopen(_name, mode);
    if(!file)
        return false;
    return true;
};

size_t FileHD::write(const void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fwrite(buffer, 1, (size_t)size, (FILE*)file);
};

size_t FileHD::read(void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fread(buffer, 1, (size_t)size, (FILE*)file);
};

size_t FileHD::tell()
{
    if(!file)
        return 0;
    return ftell((FILE*)file);
};

bool FileHD::seek(const size_t offset, const int origin)
{
    if(!file)
        return false;
    return fseek((FILE*)file, (size_t)offset, origin) == 0;
};

void FileHD::close()
{
    if(!file)
        return;
    fclose((FILE*)file);
    file = 0;
    name = "";
};

size_t FileHD::size()
{
    if(!file)
        return 0;
    long cur_pos = ftell((FILE*)file);
    fseek((FILE*)file, 0, SEEK_END);
    long size = ftell((FILE*)file);
    fseek((FILE*)file, cur_pos, SEEK_SET);
    return (size_t)size;
};
bool FileHD::isOpened()
{
    return file != 0;   
};
