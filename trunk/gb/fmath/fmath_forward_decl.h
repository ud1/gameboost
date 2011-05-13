/** \file fmath_forward_decl.h
 \brief Для gb::fmath форвард-декларации.


*/

#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif
 

namespace gb
{
namespace fmath
{

//---------------------------------------------------------------

namespace scalar
{


}
//---------------------------------------------------------------
 

struct vec2_s;
struct vec3_s;
struct vec4_s;

struct mat22_s;
struct mat33_s;
struct mat44_s;

 
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
//---------------------------------------------------------------

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
//---------------------------------------------------------------


namespace proj
{

struct ProjectionData;
struct RelatCoord;

struct vieport_s;
class ViewportZ;

}
//---------------------------------------------------------------


//---------------------------------------------------------------
}
// end namespace fmath

}
// end namespace gb

// end file