#pragma once

namespace gb
{
	namespace t
	{
		template< class T >
		inline T clamp( T const &val, T const &minVal, T const &maxVal )
		{
			if( val < minVal )
				return minVal;
			
			if( val > maxVal )
				return maxVal;
			
			return val;
		}
	}
}