/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/

  #include "pch.h"
#include "gb/io/FileStream.h"
using namespace gb::io;


//	Warning	1	warning C4267: 'argument' : conversion from 'size_t' to 'long',
// possible loss of data	z:\!!gb\gameboost\gb\io\filestream.cpp	88
#pragma warning(disable : 4267)


FileStream::FileStream(void) : IStream(), file(0), name(0) {}
            
FileStream::FileStream(const char *_name, const int mode) : IStream(), file(0), name("") 
{
    open(_name, mode);
}

FileStream::~FileStream(void)
{
    if(file)
        fclose((FILE*)file);
}

bool FileStream::open(const char *_name, const int mode)
{
    if(file)
        return false;
    name = _name;
    char str_mode[5] = "\0\0\0";
    if(mode & eStreamAccess::TRUNCATE)
    {
        // ������/������ � ����������� �����
        if((mode & eStreamAccess::WRITE) && (mode & eStreamAccess::READ))
            strcpy(str_mode, "w+");
        // ������ � ����������� �����
        else if((mode & eStreamAccess::WRITE))
            strcpy(str_mode, "w");
    }
    else
    {
        // ������/���������� (��� ���������� �����)
        if((mode & eStreamAccess::APPEND) && (mode & eStreamAccess::READ))
            strcpy(str_mode, "a+");
        // ������/������ ��� ���������� �����
        else if((mode & eStreamAccess::WRITE) && (mode & eStreamAccess::READ))
            strcpy(str_mode, "r+");
        // ������ (��� ���������� �����)
        else if((mode & eStreamAccess::READ))
            strcpy(str_mode, "r");
        // ���������� (��� ���������� �����)
        else if((mode & eStreamAccess::APPEND))
            strcpy(str_mode, "a");
    }
    strcat(str_mode, "b");
    //��� �� ����� �* ��������...
    if(str_mode[0] == 'b')
        return false;

    file = fopen(_name, str_mode);
    if(!file)
        return false;
    return true;
}

size_t FileStream::write(const void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fwrite(buffer, 1, size, file);
}

size_t FileStream::read(void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fread(buffer, 1, size, file);
}

size_t FileStream::tell()
{
    if(!file)
        return 0;
    return ftell(file);
}

bool FileStream::seek(const size_t offset, const int origin)
{
    if(!file)
        return false;
    return fseek(file, offset, origin) == 0;
}

void FileStream::close()
{
    if(!file)
        return;
    fclose(file);
    file = 0;
    name = "";
}

size_t FileStream::size()
{
    if(!file)
        return 0;
    size_t cur_pos = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, cur_pos, SEEK_SET);
    return size;
}

bool FileStream::isOpened()
{
    return file != 0;   
}

size_t FileStream::write(const void*buffer, const size_t size, const size_t offset)
{
    if(!file)
        return 0;
    size_t cur_pos = ftell(file);
    fseek(file, offset, SEEK_SET);
    size_t bytes_written = fwrite(buffer, 1, size, file);
    fseek(file, cur_pos, SEEK_SET);   
    return bytes_written;
}

size_t FileStream::read(void*buffer, const size_t size, const size_t offset)
{
    if(!file)
        return 0;
    size_t cur_pos = ftell(file);
    fseek(file, offset, SEEK_SET);
    size_t bytes_read = fread(buffer, 1, size, file);
    fseek(file, cur_pos, SEEK_SET);   
    return bytes_read;
}

bool FileStream::eof()
{
    return feof(file) != 0;
}
