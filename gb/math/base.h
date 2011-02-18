/** \file
 \brief  самая базовая базовая математика.
*
*
* Наполняйте. Исправляйте ( предварительно обновив. ).  
*  А то дальше дело так и не пойдёт.
*  
*
*
*/

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

				inline bool  operator == (const vec2_s & v) const {	return (x == v.x && y == v.y  ); }
				inline bool  operator != (const vec2_s & v) const {	return (x != v.x || y != v.y  ); }

				inline bool  operator <  (const vec2_s & v) const { return (x < v.x && y < v.y );    }
				inline bool  operator <= (const vec2_s & v) const {	return (x <= v.x && y <= v.y);   }
				inline bool  operator >  (const vec2_s & v) const {	return (x > v.x && y > v.y);     }
				inline bool  operator >= (const vec2_s & v) const {	return (x >= v.x && y >= v.y );  }

				inline vec2_s  operator - () const   { vec2_s res; res.x = -x;	res.y = -y;	return res; }

				inline vec2_s  operator + (const vec2_s &v) const { vec2_s res;	res = *this; res += v; return res; }
				inline vec2_s  operator - (const vec2_s &v) const {	vec2_s res;	res = *this; res -= v; return res; }
				inline vec2_s  operator * (float f) const         { vec2_s res;	res = *this; res.x *= f;  res.y *= f; return res; }
				inline vec2_s  operator / (float f) const         { vec2_s res;	res = *this; res.x /= f;  res.y /= f; return res; }

				inline vec2_s &  operator += (const vec2_s &v) { x += v.x; y += v.y; return *this; }
				inline vec2_s &  operator -= (const vec2_s &v) { x -= v.x; y -= v.y; return *this; }
				inline vec2_s &  operator *= (float f)         { x *= f;   y *= f;	 return *this; }
				inline vec2_s &  operator /= (float f)         { x /= f;   y /= f;   return *this; }

 			    inline operator  const float*() const  { return &x; };
			    inline operator        float*()        { return &x; };

				inline void setzero() {x=y=0.0f; };
				inline bool empty() const { return ( (x==0.0f) && (y==0.0f) ); };



				inline void print() const { printf("%f %f", x, y); };
			};


		/** \brief Базовый 3d-вектор. декларировать класс от него для методов  Поправить операторы по эпислону */		
		struct vec3_s  {

		    union {
			
				struct {
				   float x, y, z;
				};

				float floats [3];
			};

					 
			inline bool  operator == (const vec3_s &v) const { return (x == v.x && y == v.y && z == v.z ); }
			inline bool  operator != (const vec3_s &v) const { return (x != v.x || y != v.y || z != v.z ); }

			inline bool  operator <  (const vec3_s &v) const {	return (x <  v.x && y <  v.y && z <  v.z ); }
			inline bool  operator <= (const vec3_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z ); }
			inline bool  operator >  (const vec3_s &v) const {	return (x >  v.x && y >  v.y && z >  v.z ); }
			inline bool  operator >= (const vec3_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z ); }

			inline vec3_s  operator - () const{	vec3_s res;	res.x = -x;	res.y = -y;	res.z = -z;	return res; }

			inline vec3_s  operator + (const vec3_s &v) const {	vec3_s res;	res = *this; res += v;	return res; }
			inline vec3_s  operator - (const vec3_s &v) const {	vec3_s res;	res = *this; res -= v;	return res; }
			inline vec3_s  operator * (float f) const         { vec3_s res = *this;      res.x *= f;	res.y *= f;	res.z *= f;	return res; }
			inline vec3_s  operator / (float f) const         { vec3_s res = *this;	     res.x /= f;	res.y /= f;	res.z /= f;	return res; }

			inline vec3_s &  operator += (const vec3_s &v)    {	x += v.x;	y += v.y;	z += v.z;	return *this; }
			inline vec3_s &  operator -= (const vec3_s &v)    {	x -= v.x;	y -= v.y;	z -= v.z;	return *this; }
			inline vec3_s &  operator *= (float f)            {	x *= f;	y *= f;	z *= f;	return *this; }
			inline vec3_s &  operator /= (float f)            {	x /= f;	y /= f;	z /= f;	return *this; }

			inline operator  const float*() const  { return &x; };
			inline operator        float*()        { return &x; };

		    inline void setzero() {x=y=z=0.0f; };
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) ); };


 			inline void print() const { printf("%f %f %f", x, y, z); };

		}; // end vec3_s
		


		/** \brief Базовый 4d-вектор.  декларировать класс от него для методов. Поправить операторы по эпислону   */		
		struct vec4_s  {

		    union {
			
				struct {
				   float x, y, z, w;
				};

				float floats [4];
			};

					 
			inline bool  operator == (const vec4_s &v) const {	return (x == v.x && y == v.y && z == v.z && w == v.w); }
			inline bool  operator != (const vec4_s &v) const {	return (x != v.x || y != v.y || z != v.z || w != v.w); }

			inline bool  operator <  (const vec4_s &v) const {	return (x < v.x && y < v.y && z < v.z && w < v.w); }
			inline bool  operator <= (const vec4_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z && w <= v.w); }
			inline bool  operator >  (const vec4_s &v) const {	return (x > v.x && y > v.y && z > v.z && w > v.w); }
			inline bool  operator >= (const vec4_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z && w >= v.w); }

			inline vec4_s  operator - () const{	vec4_s res;	res.x = -x;	res.y = -y;	res.z = -z;	res.w = -w;	return res; }

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



			inline void print() const { printf("%f %f %f %f", x, y, z, w); };

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

			
			mat22_s&  operator =  ( const mat22_s& m);
			/** \brief   В главную диагональ установить f остальное занулить.*/
			mat22_s&  operator =  ( float f);
			/** \breief  Покомпонентное сложение   (this = this + m) */
			mat22_s&  operator += ( const mat22_s& m);
			/** \breief  Покомпонентное вычитанние (this = this - m) */
			mat22_s&  operator -= ( const mat22_s& m);

			mat22_s&  operator *= ( const mat22_s& m);

			/** \breief  Покомпонентное умножение (this = this * m) */            
			mat22_s&  operator *= ( float f);
			/** \breief  Покомпонентное деление (this = this / m) */
			mat22_s&  operator /= ( float f);

			mat22_s operator + ( const mat22_s& m);
			mat22_s operator - ( const mat22_s& m);
			mat22_s operator * ( const mat22_s& m);


			mat22_s operator * ( float f );
			vec2_s  operator * ( const vec2_s& v );


			inline void setzero()     { _11=_12=_21=_22=0.0f; };
			inline void setIdentity() {	_11=1.0f; _12=0.0f;	_21=0.0f; _22=1.0f;	};
			inline void transpone()   {  register float f=_12; _12=_21; _21=f; };

			inline float determinant () { return floats [0][0] * floats [1][1] - floats [0][1] * floats [1][0];	};

            void  invert ();

			void         setRotation ( float angle );
			inline void  setMirrorX () { setIdentity();  floats [0][0] = -1.0; };
			inline void  setMirrorY () { setIdentity();  floats [1][1] = -1.0; };
			void         setScaling ( const vec2_s& v );
			void         setScaling (float x, float y);





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


			inline void setzero() { memset(&_11, 0, sizeof(mat44_s)  ); };
			inline void setIdentity() {
				_11=1.0f; _12=0.0f; _13=0.0f; _14=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f; _24=0.0f; 
				_31=0.0f; _32=0.0f; _33=1.0f; _34=0.0f;  
				_41=0.0f; _42=0.0f; _43=0.0f; _44=1.0f; 
	        };

			inline void transpone() {  
				   register float f;
				f = _12;  _12 = _21;  _21 = f;
				f = _13;  _13 = _31;  _31 = f;
				f = _14;  _14 = _41;  _41 = f;
				f = _23;  _23 = _32;  _32 = f;
				f = _24;  _24 = _42;  _42 = f;
				f = _34;  _34 = _43;  _43 = f; 
			};


			#ifdef GB_OPENGL
               inline void glMul()  { glMultMatrixf( (GLfloat*)&_11  ); };
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