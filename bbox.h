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
		//
		// class BBox
		//
		//----------------------------------------------------------------------

		class BBox {

		public:

			Vector3f min;
			Vector3f max;

			BBox() {};
			BBox(const Vector3f &mn, const Vector3f &mx);

			Vector3f getOrigin() const { return min + (max - min) * 0.5f; }
			Vector3f getExtents() const { return (max - min) * 0.5f; }

			Vector3f getVertex(int) const;
			Plane getPlane(int) const;

			bool trace(const Line &ray, TracePoint &intersection, bool fix_src = true, bool fix_dst = false) const;
			void include(const Vector3f &point, float radius = 0.0f);

		};
		
		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
