/*	\file FileStream.cpp
 *	\author -Eugene-, kozlov_eugene@list.ru
*/
#include "pch.h"

#include <gb/io/FileStream.h>

using namespace gb::io;

FileStream::FileStream(void) : IStream(), file(0), name(0) {};
            
FileStream::FileStream(const char *_name, const int mode) : IStream(), file(0), name("") 
{
    name = _name;
    open(_name, mode);
};

FileStream::~FileStream(void)
{
    if(file)
        fclose((FILE*)file);
    file = 0;
    name = "";
};

bool FileStream::open(const char *_name, const int mode)
{
    if(file)
        return false;
    name = _name;
    char str_mode[5] = "\0\0\0";
    if(mode & eFileAccess::TRUNCATE)
    {
        // Чтение/запись с перезаписью файла
        if((mode & eFileAccess::WRITE) && (mode & eFileAccess::READ))
            strcpy(str_mode, "w+");
        // Чтение с перезаписью файла
        else if((mode & eFileAccess::WRITE))
            strcpy(str_mode, "w");
    }
    else
    {
        // Чтение/дополнение (без перезаписи файла)
        if((mode & eFileAccess::APPEND) && (mode & eFileAccess::READ))
            strcpy(str_mode, "a+");
        // Чтение/запись без перезаписи файла
        else if((mode & eFileAccess::WRITE) && (mode & eFileAccess::READ))
            strcpy(str_mode, "r+");
        // Чтение (без перезаписи файла)
        else if((mode & eFileAccess::READ))
            strcpy(str_mode, "r");
        // Дополнение (без перезаписи файла)
        else if((mode & eFileAccess::APPEND))
            strcpy(str_mode, "a");
    };
    //Что то через ж* объявили...

    if(str_mode[0] == 0)
        return false;
    file = fopen(_name, str_mode);
    if(!file)
        return false;
    return true;
};

size_t FileStream::write(const void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fwrite(buffer, 1, size, file);
};

size_t FileStream::read(void*buffer, const size_t size)
{
    if(!file)
        return 0;
    return fread(buffer, 1, size, file);
};

size_t FileStream::tell()
{
    if(!file)
        return 0;
    return ftell(file);
};

bool FileStream::seek(const size_t offset, const int origin)
{
    if(!file)
        return false;
    return fseek(file, offset, origin) == 0;
};

void FileStream::close()
{
    if(!file)
        return;
    fclose(file);
    file = 0;
    name = "";
};

size_t FileStream::size()
{
    if(!file)
        return 0;
    long cur_pos = ftell(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, cur_pos, SEEK_SET);
    return (size_t)size;
};

bool FileStream::isOpened()
{
    return file != 0;   
};

size_t FileStream::write(const void*buffer, const size_t size, const size_t offset)
{
    if(!file)
        return 0;
    long cur_pos = ftell(file);
    fseek(file, offset, SEEK_SET);
    size_t bytes_written = fwrite(buffer, 1, size, file);
    fseek(file, cur_pos, SEEK_SET);   
    return bytes_written;
};

size_t FileStream::read(void*buffer, const size_t size, const size_t offset)
{
    if(!file)
        return 0;
    long cur_pos = ftell(file);
    fseek(file, offset, SEEK_SET);
    size_t bytes_read = fread(buffer, 1, size, file);
    fseek(file, cur_pos, SEEK_SET);   
    return bytes_read;
};

bool FileStream::eof()
{
    return (bool)(feof(file));
};
