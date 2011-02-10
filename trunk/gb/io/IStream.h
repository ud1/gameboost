/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#pragma once

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
        namespace eStreamAccess
        {
            enum
            {
                READ    = 0x0001,
                WRITE   = 0x0002,
                APPEND  = 0x0004,
                TRUNCATE= 0x0008
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
            int stream_access;
        public:
            IStream(void) : stream_access(0) {};
            virtual ~IStream(void) { };
            virtual size_t write(const void*buffer, const size_t size) = 0;
            virtual size_t read(void*buffer, const size_t size) = 0;
            virtual size_t write(const void*buffer, const size_t size, const size_t offset) = 0;
            virtual size_t read(void*buffer, const size_t size, const size_t offset) = 0;

            virtual bool seek(const size_t offset, const int origin) = 0;
            virtual size_t tell() = 0;

            virtual size_t size() = 0;
            virtual bool eof() = 0;
            virtual bool isOpened() = 0;
            int getStreamAccess() { return stream_access; };

            virtual void close() = 0;
        };
    };
};
