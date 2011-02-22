﻿/** \file
 \brief  самая базовая базовая математика.
*
*
* Наполняйте. Исправляйте ( предварительно обновив. ).  
*  А то дальше дело так и не пойдёт.
*  
*
*
*/

/***********************************************************************


 TODO:  
   --- Поправить операторы для сравнения по эпсилону.


   STORY:

   ---  добавлены методы для векторов.
   --- для структур векторов добавлены конструкторы
   --  round теперь inline


***********************************************************************/

#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gb/math/scalar.h>

namespace gb 
{

	namespace math
	{

	
		/** \brief Самые базовые типы математики. */
		namespace base
		{

		/** \brief Базовый 2d-вектор. декларировать класс от него для методов  Поправить операторы по эпислону   */
		struct vec2_s {

			union {
			
				struct {
				   float x, y;
				};

				float floats [2];
			};

			    inline vec2_s() {};

			    inline vec2_s(const vec2_s& v)      { x=v.x;  y=v.y;  };
				inline vec2_s(const vec2_s* v)      { x=v->x;  y=v->y;    };

			    inline vec2_s(float _x, float _y)   { x=_x;   y=_y;   };
			    inline vec2_s(int   _x, int   _y)   { x=(float)_x;   y=(float)_y; };

				inline bool  operator == (const vec2_s & v) const {	return (x == v.x && y == v.y  ); }
				inline bool  operator != (const vec2_s & v) const {	return (x != v.x || y != v.y  ); }

				inline bool  operator <  (const vec2_s & v) const { return (x < v.x && y < v.y );    }
				inline bool  operator <= (const vec2_s & v) const {	return (x <= v.x && y <= v.y);   }
				inline bool  operator >  (const vec2_s & v) const {	return (x > v.x && y > v.y);     }
				inline bool  operator >= (const vec2_s & v) const {	return (x >= v.x && y >= v.y );  }

				inline vec2_s  operator + () const   { 	return *this; }
				inline vec2_s  operator - () const   { vec2_s res; res.x = -x;	res.y = -y;	return res; }

				inline vec2_s  operator + (const vec2_s &v) const { vec2_s res;	res = *this; res += v; return res; }
				inline vec2_s  operator - (const vec2_s &v) const {	vec2_s res;	res = *this; res -= v; return res; }
				inline vec2_s  operator * (float f) const         { vec2_s res;	res = *this; res.x *= f;  res.y *= f; return res; }
				inline vec2_s  operator / (float f) const         { vec2_s res;	res = *this; res.x /= f;  res.y /= f; return res; }

				inline vec2_s &  operator += (const vec2_s &v)  { x += v.x; y += v.y;   return *this; }
				inline vec2_s &  operator -= (const vec2_s &v)  { x -= v.x; y -= v.y;   return *this; }
				inline vec2_s &  operator *= (float f)          { x *= f;   y *= f;	    return *this; }
				inline vec2_s &  operator *= ( const vec2_s& v) { x *= v.x;	y *= v.y;	return *this;	}

				inline vec2_s &  operator /= (float f)           { x /= f;    y /= f;   return *this; }
				inline vec2_s &  operator /= ( const vec2_s& v ) { x /= v.x;  y /= v.y; return *this;	}



 			    inline operator  const float*() const  { return &x; };
			    inline operator        float*()        { return &x; };

				inline void setzero() {x=y=0.0f; };
				inline bool empty() const { return ( (x==0.0f) && (y==0.0f) ); };

				inline bool isZero(float epsilon) const
				{
					return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) ;
				}

				inline float     length () const  {	return (float)sqrt ( x*x + y*y );	}
			    inline float     lengthSq() const {	 return (x*x + y*y );  }

				inline float     dot(const vec2_s& v) const { return x*v.x + y*v.y; };
							



				inline float     getMaxLength () const {  if( fabs (x) >= fabs (y) ) return x; else return y;   }


  			    inline vec2_s&   invert() {x=-x; y=-y;  return *this; };

				inline void print() const { printf(" %f %f ", x, y); };
			};


		/** \brief Базовый 3d-вектор. декларировать класс от него для методов  Поправить операторы по эпислону */		
		struct vec3_s  {

		    union {
			
				struct {
				   float x, y, z;
				};

				float floats [3];
			};

			inline vec3_s() {};

			inline vec3_s(const vec3_s& v)             { x=v.x;   y=v.y;   z=v.z;   };
			inline vec3_s(const vec3_s* v)             { *this=*v; }; // x=v->x;  y=v->y; z=v->z;   };

			inline vec3_s(const vec2_s& v, float _z)   { x=v.x;  y=v.y; z=_z;     };

			inline vec3_s(float _x, float _y, float _z)   { x=_x;    y=_y;    z=_z;  };
			inline vec3_s(int   _x, int   _y, int   _z)   { x=(float)_x;   y=(float)_y;  z=(float)_z; };

					 
			inline bool  operator == (const vec3_s &v) const { return (x == v.x && y == v.y && z == v.z ); }
			inline bool  operator != (const vec3_s &v) const { return (x != v.x || y != v.y || z != v.z ); }

			inline bool  operator <  (const vec3_s &v) const {	return (x <  v.x && y <  v.y && z <  v.z ); }
			inline bool  operator <= (const vec3_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z ); }
			inline bool  operator >  (const vec3_s &v) const {	return (x >  v.x && y >  v.y && z >  v.z ); }
			inline bool  operator >= (const vec3_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z ); }

			inline vec3_s  operator + () const   { 	return *this; }
			inline vec3_s  operator - () const{	vec3_s res;	res.x = -x;	res.y = -y;	res.z = -z;	return res; }

			inline vec3_s  operator + (const vec3_s &v) const {	vec3_s res;	res = *this; res += v;	return res; }
			inline vec3_s  operator - (const vec3_s &v) const {	vec3_s res;	res = *this; res -= v;	return res; }
			inline vec3_s  operator * (float f) const         { vec3_s res = *this;      res.x *= f;	res.y *= f;	res.z *= f;	return res; }
			inline vec3_s  operator / (float f) const         { vec3_s res = *this;	     res.x /= f;	res.y /= f;	res.z /= f;	return res; }

			inline vec3_s &  operator += (const vec3_s &v)    {	x += v.x;	y += v.y;	z += v.z;	return *this; }
			inline vec3_s &  operator -= (const vec3_s &v)    {	x -= v.x;	y -= v.y;	z -= v.z;	return *this; }
			inline vec3_s &  operator *= (float f)            {	x *= f;	y *= f;	z *= f;	return *this; }
			inline vec3_s &  operator *= (const vec3_s &v)    {	x *= v.x;	y *= v.y;	z *= v.z;	return *this; }
			inline vec3_s &  operator /= (float f)            {	x /= f;	y /= f;	z /= f;	return *this; }
			inline vec3_s &  operator /= (const vec3_s &v)    {	x /= v.x;	y /= v.y;	z /= v.z;	return *this; }


			inline operator  const float*() const  { return &x; }
			inline operator        float*()        { return &x; }

		    inline void setzero() {x=y=z=0.0f; }
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) ); }

			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon )  ;
			}

			inline float     length () const {	return (float)sqrt ( x*x + y*y + z*z );	}
			inline float     lengthSq() const {	 return (x*x + y*y + z*z);  }

			inline float     dot(const vec3_s& v) const { return x*v.x + y*v.y + z*v.z; };

            #pragma message ("KS777:  NEED CHECK !!!"  __FILE__)
			inline vec3_s    cross (const vec3_s &v) const
			{
				vec3_s r;
				   r.x = y * v.z - z * v.y;
				   r.y = z * v.x - x * v.z;
				   r.z = x * v.y - y * v.x;
				return r;
			}

			inline vec3_s&   normalize ()	  { register float fl=length(); x/=fl; y/=fl; z/=fl; return *this; }
			inline vec3_s    getNormalized() const { vec3_s r=*this; r.normalize(); return r; };
 
			inline float     getMaxLength () const {   return scalar::max3 ( fabs (x), fabs (y), fabs (z) );   }

			inline vec3_s&   invert() {x=-x; y=-y; z=-z; return *this; };

 			inline void print() const { printf(" %f %f %f ", x, y, z); };

		}; // end vec3_s
		


		/** \brief Базовый 4d-вектор.  декларировать класс от него для методов. Поправить операторы по эпислону   */		
		struct vec4_s  {

		    union {
			
				struct {
				   float x, y, z, w;
				};

				float floats [4];
			};

			inline vec4_s() {};

			inline vec4_s(const vec4_s& v)      { x=v.x;  y=v.y; z=v.z; w=v.w;  };
			inline vec4_s(const vec4_s* v)      { x=v->x;  y=v->y; z=v->z; w=v->w;  };

			inline vec4_s(const vec3_s& v, float _w)  { x=v.x;  y=v.y; z=v.z; w=_w;  };

			inline vec4_s(float _x, float _y, float _z, float _w)   { x=_x;   y=_y; z=_z; w=_w;  };
			inline vec4_s(int   _x, int   _y, int   _z, int   _w)   { x=(float)_x;   y=(float)_y;  z=(float)_z; w=(float)_w;};

					 
			inline bool  operator == (const vec4_s &v) const {	return (x == v.x && y == v.y && z == v.z && w == v.w); }
			inline bool  operator != (const vec4_s &v) const {	return (x != v.x || y != v.y || z != v.z || w != v.w); }

			inline bool  operator <  (const vec4_s &v) const {	return (x < v.x && y < v.y && z < v.z && w < v.w); }
			inline bool  operator <= (const vec4_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z && w <= v.w); }
			inline bool  operator >  (const vec4_s &v) const {	return (x > v.x && y > v.y && z > v.z && w > v.w); }
			inline bool  operator >= (const vec4_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z && w >= v.w); }

			inline vec4_s  operator + () const   { 	return *this; }
			inline vec4_s  operator - () const { vec4_s res;	res.x = -x;	res.y = -y;	res.z = -z;	res.w = -w;	return res; }

			inline vec4_s  operator + (const vec4_s &v) const {	vec4_s res;	res = *this;	res += v;	return res; }
			inline vec4_s  operator - (const vec4_s &v) const {	vec4_s res;	res = *this;	res -= v;	return res; }
			inline vec4_s  operator * (float f) const         {	vec4_s res;	res = *this;	res.x *= f;	res.y *= f;	res.z *= f;	res.w *= f;	return res; }
			inline vec4_s  operator / (float f) const         {	vec4_s res;	res = *this;	res.x /= f;	res.y /= f;	res.z /= f;	res.w /= f;	return res; }

			inline vec4_s &  operator += (const vec4_s &v) {	x += v.x;	y += v.y;	z += v.z;	w += v.w;	return *this; }
			inline vec4_s &  operator -= (const vec4_s &v) {	x -= v.x;	y -= v.y;	z -= v.z;	w -= v.w;	return *this; }
			inline vec4_s &  operator *= (float f)         {	x *= f;	y *= f;	z *= f;	w *= f;	return *this; }

			inline vec4_s &  operator /= (float f)         {	x /= f;	y /= f;	z /= f;	w /= f;	return *this; }

			inline operator  const float*() const  { return &x; };
			inline operator        float*()        { return &x; };

		    inline void setzero() {x=y=z=w=0.0f; };
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) && (w==0.0f) ); };

			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
			}

			inline float length () const {	return (float)sqrt( x*x + y*y + z*z + w*w );	}
			inline float lengthSq() const {	 return (x*x + y*y + z*z + w*w);  }

			inline float   dot (const vec4_s& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

            #pragma message ("KS777:  NEED CHECK !!!"  __FILE__)
			inline vec4_s  cross ( const vec4_s & v) const
			{
				  vec4_s r;
				r.x = ( z * v.w - w * v.z) * y + ( w * v.y - y * v.w) * z + ( y * v.z - z * v.y) * w;
				r.y = ( w * v.z - z * v.w) * x + ( x * v.w - w * v.x) * z + ( z * v.x - x * v.z) * w;
				r.z = ( y * v.w - w * v.y) * x + ( w * v.x - x * v.w) * y + ( x * v.y - y * v.x) * w;
				r.w = ( z * v.y - y * v.z) * x + ( x * v.z - z * v.x) * y + ( y * v.x - x * v.y) * z;
				  return r;
			}


			inline vec4_s&   invert() {x=-x; y=-y; z=-z; w=-w; return *this; };


			inline void print() const { printf(" %f %f %f %f ", x, y, z, w); };

		}; // end vec4_s
		

		/** Декларировать самые главные методы можно здесь Остальные лучше наследованием */
		struct mat22_s 
		{

			union 
			{
				struct {

				   float _11,  _12,
				         _21,  _22;
				};

				float floats [2][2];
			};

			inline operator  const float*() const  { return &_11; };
			inline operator        float*()        { return &_11; };


			inline mat22_s&  operator =  ( const mat22_s& m)
			{
				floats [0][0] = m.floats [0][0]; 
				floats [0][1] = m.floats [0][1]; 
				floats [1][0] = m.floats [1][0];
				floats [1][1] = m.floats [1][1];
				return *this;
			};

			/** \brief   В главную диагональ установить f   остальное занулить.*/
			inline mat22_s&  operator =  ( float f) { 	floats [0][1] = floats [1][0] = 0.0; floats [0][0] = floats [1][1] = f; };

			/** \breief  Покомпонентное сложение   (this = this + m) */
			inline mat22_s&  operator += ( const mat22_s& m)
			{
				floats [0][0] += m.floats [0][0];
				floats [0][1] += m.floats [0][1];
				floats [1][0] += m.floats [1][0];
				floats [1][1] += m.floats [1][1];
				return *this;
			};

			/** \breief  Покомпонентное вычитанние (this = this - m) */
			inline mat22_s&  operator -= ( const mat22_s& m)
			{
				floats [0][0] -= m.floats [0][0];
				floats [0][1] -= m.floats [0][1];
				floats [1][0] -= m.floats [1][0];
				floats [1][1] -= m.floats [1][1];
				return *this;
			};

			inline mat22_s&  operator *= ( const mat22_s& m)
			{
				mat22_s c  = *this ;
				floats [0][0] = c.floats [0][0]*m.floats [0][0] + c.floats [0][1]*m.floats [1][0];
				floats [0][1] = c.floats [0][0]*m.floats [0][1] + c.floats [0][1]*m.floats [1][1];
				floats [1][0] = c.floats [1][0]*m.floats [0][0] + c.floats [1][1]*m.floats [1][0];
				floats [1][1] = c.floats [1][0]*m.floats [0][1] + c.floats [1][1]*m.floats [1][1];
				return *this;
			};

			/** \breief  Покомпонентное умножение (this = this * m) */            
			inline mat22_s&  operator *= ( float f)
			{
				floats [0][0] *= f;
				floats [0][1] *= f;
				floats [1][0] *= f;
				floats [1][1] *= f;
				return *this;
			};

			/** \breief  Покомпонентное деление (this = this / m) */
			inline mat22_s&  operator /= ( float f)
			{
				floats [0][0] /= f;
				floats [0][1] /= f;
				floats [1][0] /= f;
				floats [1][1] /= f;
				return *this;
			};

			inline mat22_s operator + ( const mat22_s& m) const
			{
				mat22_s res;
				  res.floats[0][0] = floats [0][0] + m.floats [0][0];
				  res.floats[0][1] = floats [0][1] + m.floats [0][1];
				  res.floats[1][0] = floats [1][0] + m.floats [1][0];
				  res.floats[1][1] = floats [1][1] + m.floats [1][1];
				     return res;
			};

			inline mat22_s operator - ( const mat22_s& m) const
			{
				  mat22_s res;
				res.floats [0][0] = floats [0][0] - m.floats [0][0];
				res.floats [0][1] = floats [0][1] - m.floats [0][1];
				res.floats [1][0] = floats [1][0] - m.floats [1][0];
				res.floats [1][1] = floats [1][1] - m.floats [1][1];
				return res;
			};

			inline mat22_s operator * ( const mat22_s& m) const
			{
				  mat22_s res;
				res.floats[0][0] = floats[0][0]*m.floats[0][0]+floats[0][1]*m.floats[1][0];
				res.floats[0][1] = floats[0][0]*m.floats[0][1]+floats[0][1]*m.floats[1][1];
				res.floats[1][0] = floats[1][0]*m.floats[0][0]+floats[1][1]*m.floats[1][0];
				res.floats[1][1] = floats[1][0]*m.floats[0][1]+floats[1][1]*m.floats[1][1];
				return res;
			};

			inline mat22_s operator * ( float f ) const
			{
				  mat22_s res;
				res.floats[0][0] = floats[0][0] * f;
				res.floats[0][1] = floats[0][1] * f;
				res.floats[1][0] = floats[1][0] * f;
				res.floats[1][1] = floats[1][1] * f;
				return  res;
			};

			inline vec2_s  operator * ( const vec2_s& v ) const
			{
				vec2_s res; 
				res.x =  floats [0][0]*v.x + floats [0][1]*v.y ;
				res.y =  floats [1][0]*v.x + floats [1][1]*v.y ;
				return res;
			};


			inline mat22_s&  setzero()     { _11=_12=_21=_22=0.0f; return *this; };
			inline mat22_s&  setIdentity() {	_11=1.0f; _12=0.0f;	_21=0.0f; _22=1.0f;	return *this; };
			inline mat22_s&  transpone()   {  register float f=_12; _12=_21; _21=f;  return *this; };

			inline float determinant () const { return floats [0][0] * floats [1][1] - floats [0][1] * floats [1][0];	};

			inline mat22_s&  invert ()
			{
			   float det =   determinant();  
			   mat22_s m;
				 m.floats [0][0] =  floats [1][1] / det;
				 m.floats [0][1] = -floats [0][1] / det;
				 m.floats [1][0] = -floats [1][0] / det;
				 m.floats [1][1] =  floats [0][0] / det;
				     *this = m;
				     return *this;
			};

			inline mat22_s   getInverted () const { mat22_s r(*this); r.invert(); return r;  };

			inline mat22_s&  setScaling ( const vec2_s& v )
			{
				   floats [0][0] = v.x;
				   floats [1][1] = v.y;
				   floats [0][1] = floats [1][0] = 0.0;
				   return *this;
			};

			inline mat22_s&   setScaling (float x, float y)
			{
				floats [0][0] = x;
				floats [1][1] = y;
				    floats [0][1] = floats [1][0] = 0.0;
				    return *this;
			};

			mat22_s&  setRotation ( float angle )
			{
				float    cosine, sine;
				scalar::sincos(angle , sine , cosine );
				  floats [0][0] = cosine;
				  floats [0][1] = sine;
				  floats [1][0] = -sine;
				  floats [1][1] = cosine;
				     return *this;
			};


			inline mat22_s&  setMirrorX () { setIdentity();  floats [0][0] = -1.0; return *this; };
			inline mat22_s&  setMirrorY () { setIdentity();  floats [1][1] = -1.0; return *this; };
 

		}; 



		/** Декларировать самые главные методы можно здесь Остальные лучше наследованием */
		struct mat33_s
		{
		
			union 
			{
				struct {

				   float _11,  _12,  _13,
				         _21,  _22,  _23,
				         _31,  _32,  _33;
				};

				   float floats [3][3];
			};

			inline operator  const float*() const  { return &_11; };
			inline operator        float*()        { return &_11; };

			mat33_s& mat33_s::operator = ( float a );

			mat33_s operator + ( const mat33_s& m ) const;
			mat33_s operator - ( const mat33_s& m ) const;

			mat33_s&   operator *= ( float f );
			mat33_s&   operator *= ( const mat33_s& m );
            mat33_s&   operator /= ( float f );

			mat33_s&   operator += ( const mat33_s& a );
			mat33_s&   operator -= ( const mat33_s& a );


			mat33_s  operator * ( const mat33_s& m) const;
			mat33_s  operator * (  float f ) const;
			vec3_s   operator * ( const vec3_s& v ) const;

 
			inline void setzero() { _11=_12=_13=_21=_22=_23=_31=_32=_33=0.0f; };
			inline void setIdentity() {
				_11=1.0f; _12=0.0f; _13=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f;
				_31=0.0f; _32=0.0f; _33=1.0f;
		    };

			inline void transpone() { 
				 register float t;
			    t=_12;  _12=_21; _21=t;
			    t=_13;  _13=_31; _31=t;
			    t=_23;  _23=_32; _32=t;   
			};

			float  determinant () const;
			mat33_s& invert ();

			mat33_s& setScaling ( float x, float y, float z );
			mat33_s& setScaling ( const vec3_s& v );

			mat33_s& setRotationX ( float angle );
			mat33_s& setRotationY ( float angle );
			mat33_s& setRotationZ ( float angle );

			mat33_s& setRotation ( const vec3_s& v, float angle );

			mat33_s&  setMirrorX();
			mat33_s&  setMirrorY();
			mat33_s&  setMirrorZ();
 
		
		};
 
		

		/** Декларировать самые главные методы можно здесь Остальные лучше наследованием  */
		struct mat44_s
		{
			union 
			{
				struct {

				   float _11,  _12,  _13,  _14,
				         _21,  _22,  _23,  _24,
				         _31,  _32,  _33,  _34,
						 _41,  _42,  _43,  _44;
				};

				   float floats [4][4];
			};

			inline operator  const float*() const  { return &_11; };
			inline operator        float*()        { return &_11; };

			//








			inline void       setzero() { memset(&_11, 0, sizeof(mat44_s)  ); };
			inline mat44_s&   setIdentity() {
				_11=1.0f; _12=0.0f; _13=0.0f; _14=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f; _24=0.0f; 
				_31=0.0f; _32=0.0f; _33=1.0f; _34=0.0f;  
				_41=0.0f; _42=0.0f; _43=0.0f; _44=1.0f; 
				 return *this;
	        };

			inline mat44_s& transpone() 
			{  
				   register float f;
				f = _12;  _12 = _21;  _21 = f;
				f = _13;  _13 = _31;  _31 = f;
				f = _14;  _14 = _41;  _41 = f;
				f = _23;  _23 = _32;  _32 = f;
				f = _24;  _24 = _42;  _42 = f;
				f = _34;  _34 = _43;  _43 = f; 
				  return *this;
			};


			#ifdef GB_OPENGL
			   /** \brief Старый способ загрузки матрицы в OpenGL */
               inline void glMul()  { glMultMatrixf( (GLfloat*)&_11  ); };
			   /** \brief Старый способ перемножения матрицы  с текущей в OpenGL */
               inline void glLoad() { glLoadMatrixf( (GLfloat*)&_11  ); };
            #endif

            #ifdef GB_D3D9
			   inline operator = (const D3DMATRIX& m) { *this=(mat44_s)m; };
			   inline operator const D3DMATRIX*() const { return (D3DMATRIX*)&_11; };
			   inline operator       D3DMATRIX*()       { return (D3DMATRIX*)&_11; };
			#endif
		
		};
 



		}
		// end namespace base



		// sample
		class Vector2 : public base::vec2_s
		{
		public:
			Vector2() {};
			Vector2(const Vector2& v) {  x=v.x; y=v.y; };
			Vector2(float _x, float _y) { x=_x; y=_y; };
		
		
		};

	}
	// end namespace math

}
// end namespace gb


// end file