#pragma once
#include "IFile.h"
#include <string>

namespace gb
{
    namespace io
    {
        typedef class FileHD : public IFile
        {
        protected:
            int32_t file;
            std::string  name;
        public:
            FileHD(void);
            FileHD(const char *name, const char*mode = "rb");
            virtual ~FileHD(void);
            virtual bool open(const char *name, const char*mode = "rb");
            virtual size_t write(const void*buffer, const size_t size);
            virtual size_t read(void*buffer, const size_t size);
            virtual size_t tell();
            virtual size_t size();
            virtual bool seek(const size_t offset, const int origin);
            virtual void close();
            virtual bool isOpened();
        } CFileHD;
    };
};