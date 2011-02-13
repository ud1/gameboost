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
#include "Line.h"
#include "Plane.h"

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

		inline float distance(const Vector3f &a, const Vector3f &b)
		{
			return (a - b).length();
		}

		//----------------------------------------------------------------------

		inline float distance(const Plane &p, const Vector3f &v)
		{
			return dot(v, p.normal) + p.dist;
		}

		//----------------------------------------------------------------------

		inline float distance(const Line &l, const Vector3f &v)
		{
			TracePoint i;
			Plane p(normalize(l.getDirection()), v);
			p.trace(l, i, false, false);
			return distance(v, i.point);
		}

		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
