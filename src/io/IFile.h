#pragma once

#include "Config.h"

namespace gb
{
    namespace io
    {

        class IFile
        {
        public:
            IFile(void) {};
	        virtual ~IFile(void);
            virtual size_t write(const void*buffer, const size_t size) = 0;
            virtual size_t read(void*buffer, const size_t size) = 0;
            virtual size_t tell() = 0;
            virtual size_t size() = 0;
            virtual bool seek(const size_t offset, const int origin) = 0;
            virtual void close() = 0;
            virtual bool isOpened() = 0;
        };

	} // namespace
}  // namespace
