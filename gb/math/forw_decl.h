/** \file
 \brief Для gb::math форвард-декларации.


*/

#pragma once
#define __GB_MATH_FORW_DECL_H__

/*
#ifndef __GB_MATH_H__
   #error Файл <gb/math/math.h> должен быть включён прежде.  Не включайте этот файл. Включайте <gb/math/math.h> 
#endif
*/

namespace gb
{
namespace math
{
//---------------------------------------------------------------


namespace scalar
{



}

namespace base
{

struct vec2_s;
struct vec3_s;
struct vec4_s;

struct mat22_s;
struct mat33_s;
struct mat44_s;

}
// end namespace base

namespace geom2d
{

struct Size2d;
class Normal2;
class Point2;
class Rect;
class Circle;
class Line;
class Ray;


}
// end namespace geom2d


namespace geom3d
{

struct Size3d;
class Normal3;
class Point3;

struct AxiesAngle;
class Sphere;
class AABB;
class Ray;
class Line;
class EulerAngles;
class Triangle;

struct plane_s;
class  Plane;

struct quat_s;
class  Quaternion;

class  Projector;
class  Frustum;
class  Cilinder;
struct TransformData;

}
// end namespace geom3d


namespace proj
{

struct ProjectionData;
struct RelatCoord ;
struct Viewport;

}
// end namespace proj

//---------------------------------------------------------------
}
// end namespace math

}
// endnamespace gb

// end file