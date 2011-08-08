

#include <gb/logging/Logger.h>

namespace
{
	static GB_LOGGER_TYPE logger;
}

namespace gb
{
	namespace base
	{
		template<>
		GB_LOGGER_TYPE &getLogger()
		{
			return logger;
		}
	}
}