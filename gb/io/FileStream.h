/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#pragma once
#include "../io/IStream.h"
#include <stdio.h>
#include <string>
#include <cstring>

namespace gb
{
    namespace io
    {
        /*
         * Поток данных для чтения с диска.
         * 
         * Особенности работы: параметр mode ф-ции open() - gb::io::eFileAccess
         */
        typedef class FileStream : public IStream
        {
        protected:
            FILE* file;
            std::string  name;
        public:
            FileStream(void);
            FileStream(const char *name, const int mode = eStreamAccess::READ);
            virtual ~FileStream(void);
            virtual bool open(const char *name, const int mode = eStreamAccess::READ);
            virtual size_t write(const void*buffer, const size_t size);
            virtual size_t read(void*buffer, const size_t size);
            virtual size_t write(const void*buffer, const size_t size, const size_t offset);
            virtual size_t read(void*buffer, const size_t size, const size_t offset);

            virtual bool seek(const size_t offset, const int origin);
            virtual size_t tell();
 
            virtual size_t size();
            virtual bool eof();
            virtual bool isOpened();

            virtual void close();
        } CFileStream;
    };
};