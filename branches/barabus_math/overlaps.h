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
#include "BBox.h"
#include "BSphere.h"
#include "Frustum.h"

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
		
		bool overlaps(const BSphere &s0, const BSphere &s1);
		bool overlaps(const BBox &b0, const BBox &b1);
		bool overlaps(const BSphere &s, const BBox &b);
		bool overlapsExact(const BSphere &s, const BBox &box, const mat4 &box_transform);
		bool overlaps(const BSphere &s, const BBox &box, const mat4 &box_transform);
		bool overlaps(const BBox &a, const mat4 &a_inv_tf, const BBox &b, const mat4 &b_tf);
		bool overlaps(const BBox &box, const Frustum &frustum);
		bool overlaps(const BBox &box, const mat4 &boxTransform, const Frustum &frustum);
		bool overlaps(const BSphere &sphere, const Frustum &frustum);

	}
	
	//--------------------------------------------------------------------------
	
}
