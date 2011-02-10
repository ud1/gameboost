#pragma once
#include "IStream.h"
#include "gb/base/types.h"
// -Eugene-, kozlov_eugene@list.ru

namespace gb
{
    namespace io
    {
        /*
         * ����� ������ ��� ������ � �����.
         * 
         * ����������� ������: �������� mode �-��� create() - gb::io::eFileAccess;
         * ��� ������ �������������, ��������� eFileAccess::TRUNCATE � eFileAccess::APPEND
         */
        typedef class MemoryStream : public IStream
        {
        protected:
            size_t      file_size;
            uint8_t    *file;
            size_t      offset;
        public:
            MemoryStream(void);
            MemoryStream(size_t size, int mode = eFileAccess::READ | eFileAccess::WRITE);
            virtual ~MemoryStream(void);
            virtual uint8_t*create(size_t size, int mode = eFileAccess::READ | eFileAccess::WRITE);
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
        } CMemoryStream;
    };
};
