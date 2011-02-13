#include "Logger.h"

namespace
{
	static LOGGER_TYPE logger;
}

namespace gb
{
	namespace base
	{
		template<>
		LOGGER_TYPE &getLogger()
		{
			return logger;
		}
	}
}
