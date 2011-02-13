//------------------------------------------------------------------------------
//
// GameBoost
//
// copyright:	(c) 2011 GameDev.ru
// authors:		Alexey Egorov (FadeToBlack aka EvilSpirit) anandamide@mail.ru
//
// url:			http://gameboost.googlecode.com/
//				http://www.gamedev.ru/community/gameboost
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Vector.h"

//------------------------------------------------------------------------------
//
// namespace gb
//
//------------------------------------------------------------------------------

namespace gb
{

	//--------------------------------------------------------------------------
	//
	// namespace base
	//
	//--------------------------------------------------------------------------
	
	namespace base
	{
		
		//----------------------------------------------------------------------
		//
		// class Line
		//
		//----------------------------------------------------------------------

		class Line {

		public:

			Vector3f src;
			Vector3f dst;

			Line() { }
			Line(const Vector3f &s, const Vector3f &d) : src(s), dst(d) { }

			inline Vector3f getDirection() const { return (dst - src); }
		};

		//----------------------------------------------------------------------
		//
		// struct TracePoint
		//
		//----------------------------------------------------------------------

		struct TracePoint {

			Vector3f point;
			Vector3f normal;
			Vector2f tex_coord;

		};
		
		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
