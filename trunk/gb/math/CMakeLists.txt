project( gb-math )
cmake_minimum_required(VERSION 2.8)

set( gb-math_SOURCES
		math.h
		BBox.h
		Camera.h
		CoordSystem.h
		Frustum.h Frustum.cpp
		IntersectionType.h
		Plane.h
		Rect.h
		restrictedQuadTree.h
)

applyPCH(gb-math_SOURCES)

add_library( gb-math STATIC ${gb-math_SOURCES} )
