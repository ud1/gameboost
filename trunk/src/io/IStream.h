#pragma once
// -Eugene-, kozlov_eugene@list.ru

namespace gb
{
    namespace io
    {
        /*
         * ������ � �����.
         * 
         * ����������� ������: APPEND �� ���������� � WRITE � TRUNCATE
         * ������� �������� �� ���������.
         */
        namespace eFileAccess
        {
            enum
            {
                READ    = 0x0001f,
                WRITE   = 0x0002f,
                APPEND  = 0x0004f,
                TRUNCATE= 0x0008f
            };
        };
        /*
         * ����������� ����� ������. ������������ ��� ������-������ ������ � ����� ��������
         * ��������/����������.
         * 
         * ����������� ������: ���� � ������� write() ��� read() �������� ��������, 
         * ������� �������� �� ��������� � ����� �� ���������.
         */
        class IStream
        {
        protected:
            int file_access;
        public:
            IStream(void) : file_access(0) {};
            virtual ~IStream(void) { file_access = 0; };
            virtual size_t write(const void*buffer, const size_t size) = 0;
            virtual size_t read(void*buffer, const size_t size) = 0;
            virtual size_t write(const void*buffer, const size_t size, const size_t offset) = 0;
            virtual size_t read(void*buffer, const size_t size, const size_t offset) = 0;

            virtual bool seek(const size_t offset, const int origin) = 0;
            virtual size_t tell() = 0;

            virtual size_t size() = 0;
            virtual bool eof() = 0;
            virtual bool isOpened() = 0;
            int getFileAccess() { return file_access; };

            virtual void close() = 0;
        };
    };
};
