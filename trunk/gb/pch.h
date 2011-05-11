#include <gb/Config.h>

#if ( defined(_WIN32) || defined(WIN32)  )
	#include <Windows.h>
	#include <Shlobj.h>
	#include <mbstring.h>
#endif

#include <string>
#include <ctime>
#include <cstdarg>
#include <clocale>
#include <cstdio>
#include <cfloat>
#include <cmath>
#include <cassert>

#include <stdio.h>
#include <string.h>

#include <list>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <stdexcept>


#if GB_ALLOW_BOOST_LIBRARY
	#include <boost/algorithm/string.hpp>

	#include <boost/filesystem.hpp>

	#include <boost/bind.hpp>

	#include <boost/lambda/lambda.hpp>

	#include <boost/interprocess/sync/interprocess_semaphore.hpp>

	#include <boost/intrusive/set.hpp>

	#include <boost/date_time/posix_time/posix_time.hpp>

	#include <boost/thread.hpp>
	#include <boost/thread/thread.hpp>
	#include <boost/thread/mutex.hpp>

// 	#include <boost/wave.hpp>
// 	#include <boost/wave/cpplexer/cpp_lex_token.hpp>
// 	#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

	#include <boost/tuple/tuple.hpp>
	#include <boost/tuple/tuple_comparison.hpp>

	#if GB_ENABLE_BOOST_SERIALIZE
		#include <boost/serialization/serialization.hpp>
	#endif

#endif

#include <gb/base/Types.h>



// end file