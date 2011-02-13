#pragma once

#include "gb/Config.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <boost/thread/mutex.hpp>

namespace gb
{
	namespace mt
	{
		
		typedef boost::mutex Mutex;
		
	}
}

#endif
