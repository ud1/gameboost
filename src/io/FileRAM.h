#pragma once

#include "io/IFile.h"

namespace gb
{
    namespace io
    {

        typedef class FileRAM : public IFile
        {
        protected:
            size_t      file_size;
            uint8_t    *file;
            size_t      offset;
        public:
            FileRAM(void);
            FileRAM(size_t size);
            virtual ~FileRAM(void);
            virtual uint8_t*create(size_t size);
            virtual size_t write(const void*buffer, const size_t size);
            virtual size_t read(void*buffer, const size_t size);
            virtual size_t tell();
            virtual size_t size();
            virtual bool seek(const size_t offset, const int origin);
            virtual void close();
            virtual bool isOpened();
        } CFileRAM;

    } // namespace
} // namespace
