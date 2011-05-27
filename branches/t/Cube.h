
#include <istream>
#include <stdexcept>
#include "stdlib.h"

namespace t 
{


struct CubeCoord
{
	size_t w; 
	size_t h;
	size_t d;
};

template <typename T, size_t TSIZE>

struct Cube {

	//! \brief  сторона . НЕ РАЗМЕР!  размер: size()*size()*size()  .
	size_t size() const 
	{
		return TSIZE;
	}

	inline operator T*()
	{
		return &m_array[0][0][0];
	}

	inline operator const T*() const
	{
		return &m_array[0][0][0];
	}

	inline const T& at(size_t w, size_t h, size_t d) const
	{
		if( (w<0) || (w>=TSIZE) || (h<0) || (h>=TSIZE) || (d<0) || (d>=TSIZE)  )
		{
			throw std::runtime_error("bad index");
		}

		return  m_array[w][h][d];
	}

	inline T& at(size_t w, size_t h, size_t d)
	{
		if( (w<0) || (w>=TSIZE) || (h<0) || (h>=TSIZE) || (d<0) || (d>=TSIZE)  )
		{
			throw std::runtime_error("bad index");
		}

		return  m_array[w][h][d];
	}

	void fill(const T& value)
	{
		for(size_t cw; cw<TSIZE; cw++)
		{
			for(size_t ch; ch<TSIZE; ch++)
			{
				for(size_t cd; cd<TSIZE; cd++)
				{
				   m_array[cw][ch][cd] = value;
				}
			}
		}
	}




protected:
	T m_array [TSIZE][TSIZE][TSIZE] ;

};

}
