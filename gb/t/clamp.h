#pragma once
#include "func.h"

namespace gb
{
	namespace t
	{
		template< class T >
		inline T clamp( T const &val, T const &minVal, T const &maxVal )
		{
			if( val < minVal )
				return minVal;
			else if( val > maxVal )
				return maxVal;
			else
				return val;
		}
	}
}