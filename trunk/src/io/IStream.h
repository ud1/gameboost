#pragma once
// -Eugene-, kozlov_eugene@list.ru

namespace gb
{
    namespace io
    {
        /*
         * Доступ к файлу.
         * 
         * Особенности работы: APPEND не сочетается с WRITE и TRUNCATE
         * текущее смещение не изменится.
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
         * Абстрактный поток данных. Использовать для чтения-записи данных в любых функциях
         * загрузки/сохранения.
         * 
         * Особенности работы: если в функции write() или read() задавать смещение, 
         * текущее смещение не изменится в файле не изменится.
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
