#include "Config.h"

#ifdef _WIN32
#include <Windows.h>
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

#include <list>
#include <set>
#include <vector>
#include <map>

#if GB_ALLOW_BOOST_LIBRARY
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#endif

#include "base/Types.h"
