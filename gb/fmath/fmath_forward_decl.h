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
 

struct vec2;
struct vec3;
struct vec4;

struct mat22;
struct mat33;
struct mat44;

class  Quaternion;

 
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

class  Projector;
class  Frustum;
class  Cilinder;

struct TransformData;

}
//---------------------------------------------------------------


namespace proj
{

struct PerspectiveProjData;
struct RelatCoord;

struct vieport_s;
class ViewportZ;

}
//---------------------------------------------------------------

namespace context 
{

struct float_context_type_e;
class FloatContext;
struct vector_context_type_e;
struct matrix4x4_context_type_e;
class GeometryContext;
 

}


//---------------------------------------------------------------
}
// end namespace fmath

}
// end namespace gb

// end file