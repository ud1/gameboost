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

/***********************************************************************



 TODO:  
   --- Поправить операторы для сравнения по эпсилону.
   --- Перенести в cpp методы матрицы 4x4 .
   --- Тяжелые методы перенести в cpp
   ---   transformCoord   transformNormal   для vec3 


   STORY:

   ---  добавлены операции для векторов.
   ---  добавлены методы для векторов.
   --- для структур векторов добавлены конструкторы
   --  round теперь inline


***********************************************************************/

#pragma once

#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <string.h>

#include <gb/math/forw_decl.h>
#include <gb/math/scalar.h>

#include <assert.h>

#ifdef GB_D3D9
  #include <d3d9.h>
#endif

// temp
#ifdef GB_D3DX9
  #include <d3dx9Math.h>
#endif


namespace gb 
{

	namespace math
	{

	
		/** \brief Самые базовые типы математики. */
		namespace base
		{


		/** \brief Базовый 2d-вектор.  Поправить операторы по эпислону */
		struct vec2_s {

			union {
			
				struct {
				   float x, y;
				};

				float floats [2];
			};

			    inline vec2_s() {}

			    inline vec2_s(const vec2_s& v)      { x=v.x;  y=v.y;  }
				inline vec2_s(const vec2_s* v)      { x=v->x;  y=v->y;    }

			    inline vec2_s(float _x, float _y)   { x=_x;   y=_y;   }
			    inline vec2_s(int   _x, int   _y)   { x=(float)_x;   y=(float)_y; }

				inline vec2_s(const float* pfArray) { *this = pfArray; }

				//! \brief Присваивание из float-массива 
				inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; }

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
				inline vec2_s &  operator *= ( const vec2_s& v) { x *= v.x;	y *= v.y;	return *this; }

				inline vec2_s &  operator /= (float f)           { x /= f;    y /= f;   return *this; }
				inline vec2_s &  operator /= ( const vec2_s& v ) { x /= v.x;  y /= v.y; return *this; }



 			    inline operator  const float*() const  { return (float*)&x; }
			    inline operator        float*()        { return (float*)&x; }

				inline float operator [] (unsigned int index) const
				{
					assert(index<2 && "invalid index");
					const float* pf = &x;
					return pf[index];
				}

				inline  float& operator [] (unsigned int index) 
				{
					assert(index<2 && "invalid index");
					float* pf = &x;
					return *(pf + index);
				}


#ifdef GB_D3DX9
			inline operator const D3DXVECTOR2*() const { return (D3DXVECTOR2*)&x; }
			inline operator   D3DXVECTOR2*()   { return (D3DXVECTOR2*)&x; }
			inline operator   D3DXVECTOR2() const  { return D3DXVECTOR2(x,y); }
			
			inline void operator = (const D3DXVECTOR2& v) {	x=v.x; y=v.y; }
#endif


				inline void setzero() {x=y=0.0f; }
				inline bool empty() const { return ( (x==0.0f) && (y==0.0f) ); }

				inline vec2_s& set     (float _x, float _y) {x=_x; y=_y;  return *this; }
				inline vec2_s& set_all (float val) { x=val; y=val;        return *this; }

				inline bool isZero(float epsilon) const
				{
					return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon );
				}

				inline float     length () const  {	return (float)sqrt ( x*x + y*y );	}
			    inline float     lengthSq() const {	 return (x*x + y*y );  }

				inline vec2_s&   normalize() { register float fl=length(); x/=fl; y/=fl;  return *this; }

				inline float     dot(const vec2_s& v) const { return x*v.x + y*v.y; }

				// !!!!! float cross(const vec2_s& v) const {  ......  }

				// TODO:
				//   FLOAT D3DXVec2CCW( CONST D3DXVECTOR2 * pV1,   CONST D3DXVECTOR2 * pV2);
				// float cross(v2) conts {.....}


				// float distance(v2), distanceSq(v2)


				inline vec2_s& inverse() { x=-x; y=-y; return *this; }
				inline vec2_s  inverted() const { return vec2_s (-x, -y); }
 		

				inline float     getMaxLength () const {  if( fabs (x) >= fabs (y) ) return x; else return y;   }

  			   // inline vec2_s&   invert() {x=-x; y=-y;  return *this; }

				inline vec2_s    lerp(const vec2_s& v, const float k) const
				{
					vec2_s r;
					r.x = x + (v.x - x) * k;
					r.y = y + (v.y - y) * k;
					return r;			
				};

				

				//! \brief  Получить минимальную компоненту   
				inline float minVal() const { if(x<y) return x;   return y; }
				//! \brief  Получить Максимальную компоненту   
				inline float maxVal() const { if(x>y) return x;   return y; }

				//! \brief  Сравнить два вектора v1 и v2 и присвоить минимальный 
				inline vec2_s& minimize(const vec2_s& v1, const vec2_s& v2) 
				{
					if (v1.x < v2.x) x = v1.x; else  x = v2.x;
					if (v1.y < v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  Сравнить вектор v и собственное значение и присвоить минимальный  
				inline vec2_s& minimize(const vec2_s& v) 
				{
					if (v.x < x) x = v.x;
					if (v.y < y) y = v.y;
					return *this;
				}

				//! \brief  Сравнить два вектора v1 и v2 и присвоить максимальный  
				inline vec2_s& maximize(const vec2_s& v1, const vec2_s& v2) 
				{
					if (v1.x > v2.x) x = v1.x; else  x = v2.x;
					if (v1.y > v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  Сравнить вектор v и собственное значение и присвоить максимальный 
				inline vec2_s& maximize(const vec2_s& v) 
				{
					if (v.x > x) x = v.x;
					if (v.y > y) y = v.y;
					return *this;
				}

				//! \brief Вернуть минимальный вектор между this и v
				inline vec2_s minimized(const vec2_s& v) const { vec2_s r; r.minimize(*this, v); return r; };
				//! \brief Вернуть максимальный вектор между this и v
				inline vec2_s maximized(const vec2_s& v) const { vec2_s r; r.maximize(*this, v); return r; };


				//! \brief  вычислить мин. абсолютное значение компонент. 
				inline float minAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax; if(ay<res) res=ay; return res; }
				//! \brief  вычислить макс. абсолютное значение компонент 
				inline float maxAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax;  if(ay>res) res=ay; return res; }


				//! \brief  вычисление миним, компоненты 
				inline float minval() const { if(x<y) return x; return y;	}
				//! \brief  вычисление. макс компоненты 
				inline float maxval() const { if(x>y) return x; return y;	}


				//! \brief  Отсечение значений в пределах vmin и vmax
				inline void clump(const vec2_s& vmin, const vec2_s& vmax) 
				{
					if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
					if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				}

			//! \brief Вернуть среднюю точку между this и point
			inline vec2_s middle(const vec2_s& point) const 
			{
			    vec2_s res;
			      res.x = ( x + point.x ) / 2.0f;
			      res.y = ( y + point.y ) / 2.0f;			
			         return res;
			}


				//!  \brief   Вернёт true если все компоненты положительные.
				inline bool isPositive() const {  return ( (x>=0.0f) && (y>=0.0f) );  }


				//! \brief     Вывод значений на консоль.
				inline void print() const { printf(" %f %f ", x, y); }


 
			};



		/** \brief Базовый 3d-вектор.  Поправить операторы по эпислону */		
		struct vec3_s  {

		    union {
			
				struct {
				   float x, y, z;
				};

				float floats [3];
			};

			inline vec3_s() {}

			inline vec3_s(const vec3_s& v)             { x=v.x;   y=v.y;   z=v.z;   }
			inline vec3_s(const vec3_s* v)             { x=v->x;  y=v->y; z=v->z;   }

			inline vec3_s(const vec2_s& v, float _z)   { x=v.x;  y=v.y; z=_z;     }

			inline vec3_s(float _x, float _y, float _z)   { x=_x;    y=_y;    z=_z;  }
			inline vec3_s(int   _x, int   _y, int   _z)   { x=(float)_x;   y=(float)_y;  z=(float)_z; }

			inline vec3_s(const float* pfArray) { *this = pfArray; }

			//inline vec3_s(vec4_s);

			//! \brief Присваивание из float-массива 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; }
				 
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


			inline float operator [] (unsigned int index) const
			{
				assert(index<3 && "invalid index");
				const float* pf = &x;
				return pf[index];
			}

			inline  float& operator [] (unsigned int index) 
			{
				assert(index<3 && "invalid index");
				float* pf = &x;
				return *(pf + index);
			}




#ifdef GB_D3D9
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=x; r.y=y; r.z=z; return r;  }
			inline void operator = (const D3DVECTOR& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef GB_D3D9

#ifdef GB_D3DX9
			inline operator D3DXVECTOR3*() { return (D3DXVECTOR3*)&x; }
			inline operator const D3DXVECTOR3*() const { return (D3DXVECTOR3*)&x; }
			inline operator D3DXVECTOR3() const  {  return D3DXVECTOR3(x,y,z); }
		   	inline void operator = (const D3DXVECTOR3& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef GB_D3DX9

			void operator = (const gb::math::geom3d::Point3& pnt);


		    inline void setzero() {x=y=z=0.0f; }
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) ); }

			inline vec3_s& set    (float _x, float _y, float _z) { x=_x; y=_y; z=_z; return *this; };
			inline vec3_s& set_all(float val) { x=val; y=val; z=val;                 return *this; }

			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon )  ;
			}

			inline float     length () const {	return (float)sqrt ( x*x + y*y + z*z );	}
			inline float     lengthSq() const {	 return (x*x + y*y + z*z);  }

			inline float     dot(const vec3_s& v) const { return x*v.x + y*v.y + z*v.z; }

			inline vec3_s& inverse() { x=-x; y=-y; z=-z; return *this; }
			inline vec3_s  inverted() const { return vec3_s (-x, -y, -z); }

			inline vec3_s    cross (const vec3_s &v) const
			{
				      vec3_s r;
			        r.x = y * v.z  -  z * v.y;
			        r.y = z * v.x  -  x * v.z;
			        r.z = x * v.y  -  y * v.x;
					return r;		 
			}

			//! \brief  Нормализовать 
			inline vec3_s&   normalize ()	  { register float fl=length(); x/=fl; y/=fl; z/=fl; return *this; }
			//! \brief  Вернуть нормализованый
			inline vec3_s    normalized() const { vec3_s r=*this; r.normalize(); return r; }

			//! \brief  Вычислить и вернуть расстояние между точками  this и point.
			inline float distance(const vec3_s& point)   const { return  sqrt( distanceSq(point) );  }
			//! \brief  Вычислить и вернуть квадрат расстояния между точками  this и point.
			inline float distanceSq(const vec3_s& point) const { return vec3_s(*this-point).lengthSq() ;  }
 

			//! \brief Получить наибольшее абсолютное из каждой компоненты
			inline float     getMaxLength () const {   return scalar::max3 ( fabs (x), fabs (y), fabs (z) );   }

			inline vec3_s&   invert() {x=-x; y=-y; z=-z; return *this; };

			inline vec3_s    lerp(const vec3_s& v, const float k) const 
			{
				vec3_s r;
				r.x = x + (v.x - x) * k;
				r.y = y + (v.y - y) * k;
				r.z = z + (v.z - z) * k;
				return r;			
			};

			//! \brief     получить минимальную компоненту
			inline float minval() const   
			{ 
				float ret = x;
				if (y < ret) ret = y;
				if (z < ret) ret = z;
				return ret;
			};

			//! \brief     получить максимальную компоненту
			inline float maxval()  const
			{  
				float ret = x;
				if (ret < y) ret = y;
				if (ret < z) ret = z;
				return ret;
			}



			//* \brief   вычисл. мин. абсолютное из компонент.
			inline float minAbsVal() const 
			{
				float ax=abs(x);
				float ay=abs(y); 
				float az=abs(z); 
				float res=ax;
				if(ay<res) res=ay;
				if(az<res) res=az;
				return res;
			}

			//* \brief   вычисл. макс. абсолютное из компонент.
			inline float maxAbsVal() const
			{
				float ax=abs(x);
				float ay=abs(y); 
				float az=abs(z); 
				float res=ax;
				if(ay>res) res=ay;
				if(az>res) res=az;
				return res;
			}



			//! \brief  Сравнить два вектора v1 и v2 и присвоить максимальный 
			vec3_s& maximize(const vec3_s& v1, const vec3_s& v2) 
			{
				if (v1.x > v2.x) x = v1.x; else x = v2.x;
				if (v1.y > v2.y) y = v1.y; else y = v2.y;
				if (v1.z > v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  Сравнить вектор v и собственное значение и присвоить максимальный
			vec3_s& maximize(const vec3_s& v)
			{
				if (v.x > x) x = v.x; 
				if (v.y > y) y = v.y; 
				if (v.z > z) z = v.z; 
				return *this;
			}

			//! \brief  Сравнить два вектора v1 и v2 и присвоить минимальный 
			vec3_s& minimize(const vec3_s& v1, const vec3_s& v2) 
			{
				if (v1.x < v2.x) x = v1.x; else x = v2.x;
				if (v1.y < v2.y) y = v1.y; else y = v2.y;
				if (v1.z < v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  Сравнить вектор v и собственное значение и присвоить минимальный  
			vec3_s& minimize(const vec3_s& v) 
			{
				if (v.x < x) x = v.x;
				if (v.y < y) y = v.y;
				if (v.z < z) z = v.z;
				return *this;
			}

			//! \brief Вернуть минимальный вектор между this и v
			inline vec3_s minimized(const vec3_s& v) const { vec3_s r; r.minimize(*this, v); return r; };
			//! \brief Вернуть максимальный вектор между this и v
			inline vec3_s maximized(const vec3_s& v) const { vec3_s r; r.maximize(*this, v); return r; };



			//! \brief  отсеч значения в диапазоне между vmin и vmax
			inline vec3_s& clump(const vec3_s& vmin, const vec3_s& vmax) 
			{
				if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
				if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				if( z < vmin.z) z=vmin.z;  if(z > vmax.z) z=vmax.z;
				  return *this;
			}

			//! \brief Вернуть среднюю точку между this и point
			inline vec3_s middle(const vec3_s& point) const 
			{
			    vec3_s res;
			      res.x = ( x + point.x ) / 2.0f;
			      res.y = ( y + point.y ) / 2.0f;			
			      res.z = ( z + point.z ) / 2.0f;
			         return res;
			}

			//! \brief  Вернёт true если все компоненты положительные.
			inline bool isPositive() const {  return ( (x>=0.0f) && (y>=0.0f) && (z>=0.0f) );	}

			//! \brief Тарнсформировать по матрице m   как координату. ПРОВЕРЕНО!
			vec3_s&  transformCoord(const mat44_s& m);
			//! \brief Тарнсформировать по матрице m   как нормаль. ПРОВЕРЕНО!
			vec3_s&  transformNormal(const mat44_s& m);
				
			 // TODO: 
			    // void transformCoordArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 
			    // void transformNormalArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 


			/** \brief  Проекция вектора из виртуального "зазеркалья" на экран. 
			     Возвращает спроектированый экранный вектор. ПРОВЕРЕНА!	*/
			vec3_s project ( 
				const proj::ViewportZ& vp,   //<  область вывода
				const base::mat44_s& Proj, //<	матрица проекции
				const base::mat44_s& View, //<	матрица вида
				const base::mat44_s& World //<	матрица модельная
				)  const; 



			/** \brief Анпроекция. Перевод из экранных координат в пространственые координаты 
			Возвращает переведённый вектор . ПРОВЕРЕНА! */
			vec3_s  unproject( 
				const proj::ViewportZ& vp,    //<  область вывода
				const base::mat44_s& Proj,	//<	матрица проекции
				const base::mat44_s& View,	//<	матрица вида
				const base::mat44_s& World	//<	матрица модельная
				) const	;




			inline void toCstr(char* buf) const 
			{
				*buf = '\0';
				sprintf(buf, "%f %f %f", x, y, z);
			}

			bool fromCstr(const char* s) 
			{
				const int res = sscanf(s, "%f %f %f", &x, &y, &z);
				if( 3 != res )
					   return false;
				   return true;
			}


			//! \brief Вывод значений на консоль
			inline void print() const 
			{ 
				printf("%f  %f  %f ", x, y, z); 
			}

		}; // end vec3_s
		

		/** \brief Базовый 4d-вектор. Поправить операторы по эпислону   */		
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

			inline vec4_s(const vec2_s& v, float _z, float _w) {x=v.x; y=v.y; z=_z; w=_w; }

			inline vec4_s(float _x, float _y, float _z, float _w)   { x=_x;   y=_y; z=_z; w=_w;  }
			inline vec4_s(int   _x, int   _y, int   _z, int   _w)   { x=(float)_x;   y=(float)_y;  z=(float)_z; w=(float)_w;}

			//! \brief Присваивание из float-массива 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; w=pf[3]; }
 
					 
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

			inline operator  const float*() const  { return &x; }
			inline operator        float*()        { return &x; }


			inline float operator [] (unsigned int index) const
			{
				assert(index<4 && "invalid index");
				const float* pf = &x;
				return pf[index];
			}

			inline  float& operator [] (unsigned int index) 
			{
				assert(index<4 && "invalid index");
				float* pf = &x;
				return *(pf + index);
			}




#ifdef GB_D3DX9
			inline operator D3DXVECTOR4*() { return (D3DXVECTOR4*)&x; }
			inline operator const D3DXVECTOR4*() const { return (D3DXVECTOR4*)&x; }
			inline operator D3DXVECTOR4() const  {  return D3DXVECTOR4(x,y,z,w); }
		   	inline void operator = (const D3DXVECTOR4& v) {	x=v.x; y=v.y; z=v.z; w=v.w; }	
#endif					
			
		    inline void setzero() {x=y=z=w=0.0f; };
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) && (w==0.0f) ); };

			inline vec4_s& set    (float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; return *this; };
			//inline vec4_s& set_all(float val) {x=val; y=val; z=val; w=val; return *this; };

			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
			}

			inline float length () const {	return (float)sqrt( x*x + y*y + z*z + w*w );	}
			inline float lengthSq() const {	 return (x*x + y*y + z*z + w*w);  }

			inline float   dot (const vec4_s& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

			
#pragma message ("KS777: MATH::VEC4 >> NEED CHECK CROSS METHOD !!!"  __FILE__)
			inline vec4_s  cross ( const vec4_s & v) const
			{
				  vec4_s r;
				r.x = ( z * v.w - w * v.z) * y + ( w * v.y - y * v.w) * z + ( y * v.z - z * v.y) * w;
				r.y = ( w * v.z - z * v.w) * x + ( x * v.w - w * v.x) * z + ( z * v.x - x * v.z) * w;
				r.z = ( y * v.w - w * v.y) * x + ( w * v.x - x * v.w) * y + ( x * v.y - y * v.x) * w;
				r.w = ( z * v.y - y * v.z) * x + ( x * v.z - z * v.x) * y + ( y * v.x - x * v.y) * z;
				  return r;
			}

	  /*************
  D3DXVec4Cross(Out, U, V, W)	 cross4(1.2.3)

a = VxWy − VyWx
b = VxWz − VzWx
c = VxWw − VwWx
d = VyWz − VzWy
e = VyWw − VwWy
f = VzWw − VwWz
Outx = fUy − eUz + dUw
Outy = fUx + cUz − bUw
Outz = eUx − cUy + aUw
Outw = dUx + bUy − aUz
	 **************************/



			inline vec4_s&   invert() {x=-x; y=-y; z=-z; w=-w; return *this; };

			inline vec4_s    lerp(const vec4_s& v, const float k) 
			{
				vec4_s r;
				r.x = x + (v.x - x) * k;
				r.y = y + (v.y - y) * k;
				r.z = z + (v.z - z) * k;
				r.w = w + (v.w - w) * k;
				return r;			
			};



	//! \brief  Получить минимальную компоненту.
	inline float minval() const 
	{ 	  
	   float res = x;
	   if(y<res) res=y;
	   if(z<res) res=z;
	   if(w<res) res=w;
	      return res;
	};

	//! \brief Получить максимальную компоненту.
	inline float maxval() const
	{   
	   float res = x;
	   if(res<y) res=y;
	   if(res<z) res=z;
	   if(res<w) res=w;
	       return res;
	};	
 
	/** \brief  вычисл. минимальной абсолютной компоненты.  */
	inline float minAbsVal() const 
	{ 
		float ax=abs(x); 
		float ay=abs(y); 
		float az=abs(z); 
		float aw=abs(w);
		      float res=ax;    
			  if(ay<res) res=ay; 
			  if(az<res) res=az; 
			  if(aw<res) res=aw; 
			  return res; 
	}

	/** \brief  вычисл. максимальной абсолютной компоненты.  */
	inline float maxAbsVal() const 
	{ 
		float ax=abs(x); 
		float ay=abs(y); 
		float az=abs(z); 
		float aw=abs(w);
	          float res=ax;
			  if(ay>res) res=ay; 
			  if(az>res) res=az;	 
			  if(aw>res) res=aw;	
			  return res;	
	}


	//! \brief Выполнить отсечение значений в диапазоне между vmin и vmax
	inline void clump(const vec4_s& vmin, const vec4_s& vmax) 
	{
		if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
		if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
		if( z < vmin.z) z=vmin.z;  if(z > vmax.z) z=vmax.z;
		if( w < vmin.w) w=vmin.w;  if(w > vmax.w) w=vmax.w;
	};


    //! \brief Вывод значений на консоль
	inline void print() const { printf(" %f  %f  %f  %f ", x, y, z, w); };

		}; 
		// end vec4_s
		
		//------------------------------------------------------------------


		//! \brief Матрица 2x2
		struct mat22_s 
		{
			union 
			{
				struct {

				   float _11,  _12,
				         _21,  _22;
				};

				float floats [2][2];

				float array [4];
			};

			inline mat22_s() {};
			inline mat22_s(const mat22_s& m) { *this=m; };
			inline mat22_s(float _11_, float _12_, float _21_, float _22_) {_11=_11_; _12=_12_; _21=_21_; _22=_22_;  };
			inline mat22_s(const float* pfArray) { *this = pfArray; }

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

			//! \brief Присвоить значения из массива
			inline void operator = (const float* pfArray)
			{
				_11 = pfArray[0];
				_12 = pfArray[1];
				_21 = pfArray[2];
				_22 = pfArray[3];
			}

			/** \brief   В главную диагональ установить f   остальное занулить.*/
			inline mat22_s&  operator =  ( float f) { 	floats [0][1] = floats [1][0] = 0.0; floats [0][0] = floats [1][1] = f; };

	        /**	 \brief Обращение знака всех элементов матрицы	*/
			inline mat22_s operator - () const { mat22_s r=*this; r._11=-r._11; r._12=-r._12; r._21=-r._21; r._22=-r._22; return r; };

 
			/** \brief  Покомпонентное сложение   (this = this + m) */
			inline mat22_s&  operator += ( const mat22_s& m)
			{
				floats [0][0] += m.floats [0][0];
				floats [0][1] += m.floats [0][1];
				floats [1][0] += m.floats [1][0];
				floats [1][1] += m.floats [1][1];
				return *this;
			};

			/** \brief  Покомпонентное вычитанние (this = this - m) */
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

			/** \brief  Покомпонентное умножение (this = this * m) */            
			inline mat22_s&  operator *= ( float f)
			{
				floats [0][0] *= f;
				floats [0][1] *= f;
				floats [1][0] *= f;
				floats [1][1] *= f;
				return *this;
			};

			/** \brief  Покомпонентное деление (this = this / m) */
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
			}
			
			inline vec2_s row(unsigned int index)
			{
			   assert(index<2 && "invalid index");
			   vec2_s res;
			   switch(index)
			   {
			    case 0: { res.x=_11; res.y=_12; } break;
			    case 1: { res.x=_21; res.y=_22; } break;
				default: {}				
			   }
			   return res;
			}
			
			inline vec2_s column(unsigned int index)
			{
			   assert(index<2 && "invalid index");			
			   vec2_s res;
			   switch(index)
			   {
			    case 0: { res.x=_11; res.y=_21; } break;
			    case 1: { res.x=_12; res.y=_22; } break;
				default: {}				
			   }			   
			   return res;
			}			
			


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




		//! \brief Матрица 3x3 
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

				   float array [9];
			};


			inline mat33_s() {};
			inline mat33_s(const mat33_s& m) { *this = m; };
			inline mat33_s( float _11_, float _12_, float _13_,
				            float _21_, float _22_, float _23_,
				            float _31_, float _32_, float _33_ ) :

								_11( _11_ ), _12( _12_ ), _13( _13_ ),
								_21( _21_ ), _22( _22_ ), _23( _23_ ),
								_31( _31_ ), _32( _32_ ), _33( _33_ ) {}

			inline mat33_s(const float* pfArray) { *this = pfArray; }

			inline operator  const float*() const  { return &_11; };
			inline operator        float*()        { return &_11; };

			inline mat33_s&  operator =  ( const mat22_s& m)
			{
				floats [0][0] = m.floats [0][0]; 
				floats [0][1] = m.floats [0][1]; 
				floats [1][0] = m.floats [1][0];
				floats [1][1] = m.floats [1][1];
				return *this;
			};

			inline void operator = (const float* pfArray)
			{
			 _11=  pfArray[0]; _12= pfArray[1];  _13= pfArray[2];
			 _21=  pfArray[3]; _22= pfArray[4];  _23= pfArray[5];
			 _31=  pfArray[6]; _32= pfArray[7];  _33= pfArray[8];	
			}

			mat33_s& operator = ( float a );

		    /**  \brief Обращение знака всех элементов матрицы	*/
	        inline mat33_s operator - () const
		    {
			   mat33_s r = *this;
				r._11=-r._11;   r._12=-r._12;   r._13=-r._13; 
				r._21=-r._21;   r._22=-r._22;   r._23=-r._23; 
				r._31=-r._31;   r._32=-r._32;   r._33=-r._33; 		   
			   return r;
		    };

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

			/**	 \brief Доступ к строкам матрицы по индексу. ПРОВЕРИТЬ !! */
	        inline const vec3_s operator [] ( unsigned int index ) const
	        {
		       assert( index <= 2 );
		       return reinterpret_cast<const vec3_s*>(this)[index];
	        }

			/**	 \brief Преобразование в матрицу 2x2 */
			inline operator mat22_s()
			{
				return mat22_s( _11, _12,
					            _21, _22 );
			}

			//! \brief  Занулить все элементы
			inline void setzero() { _11=_12=_13=_21=_22=_23=_31=_32=_33=0.0f; };

			//! \brief Сбросить в идентичную
			inline void setIdentity() {
				_11=1.0f; _12=0.0f; _13=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f;
				_31=0.0f; _32=0.0f; _33=1.0f;
		    };

			//! \brief Сбросить в идентичную
			inline void reset() { setIdentity(); }

			 //! \brief  Транспонировать матрицу 
			inline mat33_s&   transpone() 
			{ 
				 register float t;
			    t=_12;  _12=_21; _21=t;
			    t=_13;  _13=_31; _31=t;
			    t=_23;  _23=_32; _32=t; 
				  return *this;
			};

			//! \brief    Вернуть транспонированую матрицу
			inline mat33_s getTransponed() const 
			{
				mat33_s res = *this;
				res.transpone();
				return res;			
			}

			float  determinant () const;


			mat33_s& invert ();
			mat33_s  inverted() const { mat33_s res; res=*this; res.invert(); return res; }

			mat33_s& setScaling ( float x, float y, float z );
			mat33_s& setScaling ( const vec3_s& v );

			mat33_s& setRotationX ( float angle );
			mat33_s& setRotationY ( float angle );
			mat33_s& setRotationZ ( float angle );

			mat33_s& setRotation ( const vec3_s& v, float angle );

			mat33_s&  setMirrorX();
			mat33_s&  setMirrorY();
			mat33_s&  setMirrorZ();


			//! \brief  Вывод значений на консоль
			inline void print() const 
			{
			 printf("%f  %f  %f  \n%f  %f  %f  \n%f  %f  %f", 
				 _11, _12, _13, 
				 _21, _22, _23, 
				 _31, _32, _33 );
			}
 
		
		};
 
		

		//! \brief Матрица 4x4. 
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

				   float array[16];
			};


			inline mat44_s() {}

			//! \brief Сбросить в идентичную и заполнить главную диагональ значением a (обычно 1.0f)
			inline mat44_s(float a)
			{
			   setIdentity();
			   _11=a; 
			   _22=a;
			   _33=a;
			   _44=a;
			}

			inline mat44_s(const mat44_s& m) { *this = m; }

			inline mat44_s( float _11_, float _12_, float _13_, float _14_,
	                        float _21_, float _22_, float _23_, float _24_,
	                        float _31_, float _32_, float _33_, float _34_,
	                        float _41_, float _42_, float _43_, float _44_ ) : 
			_11( _11_ ), _12( _12_ ), _13( _13_ ), _14( _14_ ),
			_21( _21_ ), _22( _22_ ), _23( _23_ ), _24( _24_ ),
			_31( _31_ ), _32( _32_ ), _33( _33_ ), _34( _34_ ),
			_41( _41_ ), _42( _42_ ), _43( _43_ ), _44( _44_ )  {}


			inline operator  const float*() const  { return &_11; }
			inline operator        float*()        { return &_11; }

#ifdef GB_D3D9
			inline operator D3DMATRIX*()   { return (D3DMATRIX*)&_11; }
			inline operator const D3DMATRIX*() const  { return (D3DMATRIX*)&_11; }
			inline operator const D3DMATRIX() const 
			{
			   D3DMATRIX res;
			   for(int c=0;c<4; c++)
			   {
			     for(int j=0; j<4; j++)
				 {
				  res.m[c][j] = floats[c][j];
				 }
			   }
			   return res;
			}


			inline void operator = (const D3DMATRIX& m)
			{
				_11 = m._11;
				_12 = m._12;
				_13 = m._13;
				_14 = m._14;

				_21 = m._21;
				_22 = m._22;
				_23 = m._23;
				_24 = m._24;

				_31 = m._31;
				_32 = m._32;
				_33 = m._33;
				_34 = m._34;

				_41 = m._41;
				_42 = m._42;
				_43 = m._43;
				_44 = m._44;
			}
#endif // GB_D3D9
 


#ifdef GB_D3DX9
			inline operator D3DXMATRIX*()   { return (D3DXMATRIX*)&_11; }
			inline operator const D3DXMATRIX*() const  { return (D3DXMATRIX*)&_11; }
			inline operator const D3DXMATRIX() const 
			{
			   D3DXMATRIX res;
			   for(int c=0;c<4; c++)
			   {
			     for(int j=0; j<4; j++)
				 {
				  res.m[c][j] = floats[c][j];
				 }
			   }
			   return res;
			}
			inline void operator = (const D3DXMATRIX& m)
			{
			   for(int c=0;c<4; c++)
			   {
			     for(int j=0; j<4; j++)
				 {
				  floats[c][j] = m.m [c][j];
				 }
			   }		
			
			}


#endif // GB_D3DX9


			/**    \brief Строгое сравнение    */
			inline bool operator == ( const mat44_s& m ) const
			{
			 return ( ( _11 == m._11) &&
					  ( _12 == m._12) &&
					  ( _13 == m._13) &&
					  ( _14 == m._14) &&

					  ( _21 == m._21) &&
					  ( _22 == m._22) &&
					  ( _23 == m._23) &&
					  ( _24 == m._24) &&

					  ( _31 == m._31) &&
					  ( _32 == m._32) &&
					  ( _33 == m._33) &&
					  ( _34 == m._34) &&

					  ( _41 == m._41) &&
					  ( _42 == m._42) &&
					  ( _43 == m._43) &&
					  ( _44 == m._44) );
			}





			/**     \brief Строгое сравнение с отрицанием     */
			inline bool operator != ( const mat44_s& m ) const
			{
		      return ( ( _11 != m._11) ||
				       ( _12 != m._12) ||
					   ( _13 != m._13) ||
					   ( _14 != m._14) ||

					   ( _21 != m._21) ||
					   ( _22 != m._22) ||
					   ( _23 != m._23) ||
					   ( _24 != m._24) ||

					   ( _31 != m._31) ||
					   ( _32 != m._32) ||
					   ( _33 != m._33) ||
					   ( _34 != m._34) ||

					   ( _41 != m._41) ||
					   ( _42 != m._42) ||
					   ( _43 != m._43) ||
					   ( _44 != m._44) );
			};


			
 
			/**   \brief Инверсия знака компонентов  */
			inline mat44_s operator - () const
			{
				mat44_s r;

				r._11 = -_11 ;
				r._12 = -_12 ;
				r._13 = -_13 ;
				r._14 = -_14 ;

				r._21 = -_21 ;
				r._22 = -_22 ;
				r._23 = -_23 ;
				r._24 = -_24 ;

				r._31 = -_31 ;
				r._32 = -_32 ;
				r._33 = -_33 ;
				r._34 = -_34 ;

				r._41 = -_41 ;
				r._42 = -_42 ;
				r._43 = -_43 ;
				r._44 = -_44 ;

				return r;
			}


 
			/**   \brief Поэлементное сложение матриц  */
			inline mat44_s operator + ( const mat44_s& m ) const
			{
				mat44_s r;

				r._11 = _11 + m._11;
				r._12 = _12 + m._12;
				r._13 = _13 + m._13;
				r._14 = _14 + m._14;

				r._21 = _21 + m._21;
				r._22 = _22 + m._22;
				r._23 = _23 + m._23;
				r._24 = _24 + m._24;

				r._31 = _31 + m._31;
				r._32 = _32 + m._32;
				r._33 = _33 + m._33;
				r._34 = _34 + m._34;

				r._41 = _41 + m._41;
				r._42 = _42 + m._42;
				r._43 = _43 + m._43;
				r._44 = _44 + m._44;

				return r;
			}

			/**   \brief Поэлементное вычитание матриц  */
			inline mat44_s operator - ( const mat44_s& m ) const
			{
				mat44_s r;

				r._11 = _11 -  m._11;
				r._12 = _12 -  m._12;
				r._13 = _13 -  m._13;
				r._14 = _14 -  m._14;

				r._21 = _21 -  m._21;
				r._22 = _22 -  m._22;
				r._23 = _23 -  m._23;
				r._24 = _24 -  m._24;

				r._31 = _31 -  m._31;
				r._32 = _32 -  m._32;
				r._33 = _33 -  m._33;
				r._34 = _34 -  m._34;

				r._41 = _41 -  m._41;
				r._42 = _42 -  m._42;
				r._43 = _43 -  m._43;
				r._44 = _44 -  m._44;

				return r;
			}


			/**   \brief Умножение всех элементов матрицы на скаляр   */
			inline mat44_s operator * (  float f ) const 
			{
				mat44_s r;

				r._11 = _11 * f;
				r._12 = _12 * f;
				r._13 = _13 * f;
				r._14 = _14 * f;

				r._21 = _21 * f;
				r._22 = _22 * f;
				r._23 = _23 * f;
				r._24 = _24 * f;

				r._31 = _31 * f;
				r._32 = _32 * f;
				r._33 = _33 * f;
				r._34 = _34 * f;

				r._41 = _41 * f;
				r._42 = _42 * f;
				r._43 = _43 * f;
				r._44 = _44 * f;

				return r;
			}



			/**  \brief Деление всех элементов матрицы на скаляр  */
			inline mat44_s operator / ( float f ) const
			{
				mat44_s r;

				r._11 = _11 / f;
				r._12 = _12 / f;
				r._13 = _13 / f;
				r._14 = _14 / f;

				r._21 = _21 / f;
				r._22 = _22 / f;
				r._23 = _23 / f;
				r._24 = _24 / f;

				r._31 = _31 / f;
				r._32 = _32 / f;
				r._33 = _33 / f;
				r._34 = _34 / f;

				r._41 = _41 / f;
				r._42 = _42 / f;
				r._43 = _43 / f;
				r._44 = _44 / f;

				return r;
			}


			inline mat44_s&     operator += (const mat44_s& m) { mat44_s t=*this + m; *this=t; return *this;  }
			inline mat44_s&     operator -= (const mat44_s& m) { mat44_s t=*this - m; *this=t; return *this;  }
			inline mat44_s&     operator *= (float f)          { mat44_s t=*this * f; *this=t; return *this;  }
			inline mat44_s&     operator /= (float f)          { mat44_s t=*this / f; *this=t; return *this;  }



			inline mat44_s&  operator *= ( const mat44_s& m )
			{
				mat44_s t;
				t = *this * m;
				*this = t;
				return *this;
			}

 
			// ПРОВЕРЕНО !
			inline mat44_s operator * ( const mat44_s& m ) const
			{
				mat44_s r;
					
			 r._11 = floats[0][0] * m.floats[0][0] + floats[0][1] * m.floats[1][0] + floats[0][2] * m.floats[2][0] + floats[0][3] * m.floats[3][0];
			 r._12 = floats[0][0] * m.floats[0][1] + floats[0][1] * m.floats[1][1] + floats[0][2] * m.floats[2][1] + floats[0][3] * m.floats[3][1];
			 r._13 = floats[0][0] * m.floats[0][2] + floats[0][1] * m.floats[1][2] + floats[0][2] * m.floats[2][2] + floats[0][3] * m.floats[3][2];
			 r._14 = floats[0][0] * m.floats[0][3] + floats[0][1] * m.floats[1][3] + floats[0][2] * m.floats[2][3] + floats[0][3] * m.floats[3][3];

			 r._21 = floats[1][0] * m.floats[0][0] + floats[1][1] * m.floats[1][0] + floats[1][2] * m.floats[2][0] + floats[1][3] * m.floats[3][0];
			 r._22 = floats[1][0] * m.floats[0][1] + floats[1][1] * m.floats[1][1] + floats[1][2] * m.floats[2][1] + floats[1][3] * m.floats[3][1];
			 r._23 = floats[1][0] * m.floats[0][2] + floats[1][1] * m.floats[1][2] + floats[1][2] * m.floats[2][2] + floats[1][3] * m.floats[3][2];
			 r._24 = floats[1][0] * m.floats[0][3] + floats[1][1] * m.floats[1][3] + floats[1][2] * m.floats[2][3] + floats[1][3] * m.floats[3][3];

			 r._31 = floats[2][0] * m.floats[0][0] + floats[2][1] * m.floats[1][0] + floats[2][2] * m.floats[2][0] + floats[2][3] * m.floats[3][0];
			 r._32 = floats[2][0] * m.floats[0][1] + floats[2][1] * m.floats[1][1] + floats[2][2] * m.floats[2][1] + floats[2][3] * m.floats[3][1];
			 r._33 = floats[2][0] * m.floats[0][2] + floats[2][1] * m.floats[1][2] + floats[2][2] * m.floats[2][2] + floats[2][3] * m.floats[3][2];
			 r._34 = floats[2][0] * m.floats[0][3] + floats[2][1] * m.floats[1][3] + floats[2][2] * m.floats[2][3] + floats[2][3] * m.floats[3][3];
			 
			 r._41 = floats[3][0] * m.floats[0][0] + floats[3][1] * m.floats[1][0] + floats[3][2] * m.floats[2][0] + floats[3][3] * m.floats[3][0];
			 r._42 = floats[3][0] * m.floats[0][1] + floats[3][1] * m.floats[1][1] + floats[3][2] * m.floats[2][1] + floats[3][3] * m.floats[3][1];
			 r._43 = floats[3][0] * m.floats[0][2] + floats[3][1] * m.floats[1][2] + floats[3][2] * m.floats[2][2] + floats[3][3] * m.floats[3][2];
			 r._44 = floats[3][0] * m.floats[0][3] + floats[3][1] * m.floats[1][3] + floats[3][2] * m.floats[2][3] + floats[3][3] * m.floats[3][3];
		 
				return  r;
			}


			/**    \brief Умножение вектора на матрицу .  ПРОВЕРЕНО!  */
			inline vec4_s operator * ( const vec4_s& v ) const 
			{
				vec4_s r;
				r.x =  _11 * v.x +  _21 * v.y +  _31 * v.z +  _41 * v.w;
				r.y =  _12 * v.x +  _22 * v.y +  _32 * v.z +  _42 * v.w;
				r.z =  _13 * v.x +  _23 * v.y +  _33 * v.z +  _43 * v.w;
				r.w =  _14 * v.x +  _24 * v.y +  _34 * v.z +  _44 * v.w;
				  return r;
			}
 

			//! \brief Зануление всех элементов.
			inline void       setzero() { memset(&_11, 0, sizeof(mat44_s)  ); }

			//! \brief Установить в идентичную
			inline mat44_s&   setIdentity() 
			{
				_11=1.0f; _12=0.0f; _13=0.0f; _14=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f; _24=0.0f; 
				_31=0.0f; _32=0.0f; _33=1.0f; _34=0.0f;  
				_41=0.0f; _42=0.0f; _43=0.0f; _44=1.0f; 
				 return *this;
	        }

			//! \brief Установить в идентичную
			inline mat44_s& reset() { setIdentity(); return *this; }

			//! \brief Транспонирование. (Отражение элементов по главной диагонали)  ПРОВЕРЕНА!
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
			}

			/** \brief Вычислить и вернуть транспонированое значение .  */
			inline mat44_s getTransponed() const { mat44_s r=*this; r.transpone(); return r; };

			/** \brief Вычислить и вернуть определитель.  */
			inline float determinant()  const
			{
				 return 
					( _11 *  _22 -  _12 *  _21) * ( _33 *  _44 -  _34 *  _43) -
					( _11 *  _23 -  _13 *  _21) * ( _32 *  _44 -  _34 *  _42) +
					( _11 *  _24 -  _14 *  _21) * ( _32 *  _43 -  _33 *  _42) +
					( _12 *  _23 -  _13 *  _22) * ( _31 *  _44 -  _34 *  _41) -
					( _12 *  _24 -  _14 *  _22) * ( _31 *  _43 -  _33 *  _41) +
					( _13 *  _24 -  _14 *  _23) * ( _31 *  _42 -  _32 *  _41);
			};

			/** \brief Инверсия. Бросает исключение если инверсия невозможна. ПРОВЕРЕНА. */
			mat44_s&  invert () throw();


			vec4_s getRow(unsigned int index) const 
			{
				assert(index<4  && "invalid index" );
				return vec4_s( floats[index][0], floats[index][1], floats[index][2], floats[index][3] );
			}
 
			vec4_s getColumn(unsigned int index) const 
			{
				assert( index<4 && "invalid index" );
				return vec4_s( floats[0][index], floats[1][index], floats[2][index], floats[3][index] );
			}
 
			//! \brief Построение матрицы отражения по оси X
			inline mat44_s& setMirrorX ()
			{
				setIdentity();
				floats  [0][0] = -1.0f;
				return *this;
			}

			//! \brief Построение матрицы отражения по оси Y 
			inline mat44_s& setMirrorY ()
			{
				setIdentity();
				floats  [1][1] = -1.0f;
				return *this;
			}

			//! \brief Построение матрицы отражения по оси Z
			inline mat44_s& setMirrorZ ()
			{
				setIdentity();
				floats [2][2] = -1.0f;
				return *this;
			}

			//! \brief Построение матрицы поворота по оси X на угол angle . ПРОВЕРЕНО!
			inline mat44_s&  setRotationX( const float angle )  
			{ 
				setIdentity();  
				float sina, cosa;
				scalar::sincos(angle, sina, cosa);
				_22 =  cosa;    
				_23 =  sina;
				_32 = -sina;   
				_33 =  cosa;
                  return *this;
			}

			//! \brief Построение матрицы поворота по оси Y на угол angle . ПРОВЕРЕНО!
			inline mat44_s&  setRotationY( const float angle )  
			{
				setIdentity(); 
				float sina, cosa;
				scalar::sincos(angle, sina, cosa);
				_11 =  cosa;  
				_13 = -sina;
				_31 =  sina; 
				_33 =  cosa;
				return *this;
			};

			//! \brief Построение матрицы поворота по оси Z на угол angle . ПРОВЕРЕНО!
			inline mat44_s&  setRotationZ( const float angle ) 
			{
				setIdentity(); 
				float sina, cosa;
				scalar::sincos(angle, sina, cosa);
				_11 =  cosa;  
				_12 =  sina;
				_21 = -sina; 
				_22 =  cosa;
				return *this;
			};


			//! \brief Построение матрицы поворота по оси vAx на угол angle . ПРОВЕРЕНО!
			inline mat44_s&  setRotationAxis( const vec3_s& vAx,  const float angle ) 
			{
				float sina, cosa, mcosa; 
				scalar::sincos( angle , sina, cosa );
				mcosa = 1.0f - cosa;

				vec3_s ax = vAx;
				ax.normalize();

				_11 =(mcosa * ax.x * ax.x) + cosa;
				_12 =(mcosa * ax.x * ax.y) - (ax.z * sina);
				_13 =(mcosa * ax.z * ax.x) + (ax.y * sina);
				_14 = 0.0f;

				_21 =(mcosa * ax.x * ax.y) + (ax.z * sina);
				_22 =(mcosa * ax.y * ax.y) + cosa;
				_23 =(mcosa * ax.y * ax.z) - (ax.x * sina);
				_24 = 0.0f;

				_31 =(mcosa * ax.z * ax.x) - (ax.y * sina);
				_32 =(mcosa * ax.y * ax.z) + (ax.x * sina);
				_33 =(mcosa * ax.z * ax.z) + cosa;
				_34 = 0.0f;

				_41 = 0.0f;
				_42 = 0.0f;
				_43 = 0.0f;
				_44 = 1.0f;

				transpone(); // need

				return *this;
			};


			//! \brief Построение матрицы поворота по оси по компонентам(axX,axY,axZ) на угол angle  . ПРОВЕРЕНО!
			inline mat44_s&  setRotationAxis( float axX, float axY, float axZ, float angle )  
			{
				vec3_s vax;
				vax.x = axX; vax.y = axY; vax.z = axZ;
				vax.normalize();
				return setRotationAxis(  vax, angle);
			};



			//! \brief Построение матрицы сдвига (позиции)  . ПРОВЕРЕНО!
			inline mat44_s&  setTranslation( float x, float y, float z )  
			{
				setIdentity();
				_41 = x;   _42 = y;  _43 = z;  
				return *this;
			};

			//! \brief Построение матрицы сдвига (позиции)  ПРОВЕРЕНО!
			inline mat44_s&  setTranslation( const vec3_s& vTransl) 
			{
				return  setTranslation(  vTransl.x, vTransl.y, vTransl.z);
			}
			
			//! \brief Построение матрицы масштабирования ПРОВЕРЕНО!			
			inline mat44_s&  setScaling( float x, float y, float z)  
			{
				_11 = x;   _12=0.0f;   _13=0.0f;   _14=0.0f; 
				_21=0.0f;  _22 = y;    _23=0.0f;   _24=0.0f;	
				_31=0.0f;  _32=0.0f;   _33 = z;    _34=0.0f;	
				_41=0.0f;  _42=0.0f;   _43=0.0f;   _44 = 1.0f;
				return *this;
			}
			
			//! \brief Построение матрицы масштабирования	 ПРОВЕРЕНО!		
			inline mat44_s&  setScaling( const vec3_s& vScaling) 
			{
			  return setScaling( vScaling.x, vScaling.y, vScaling.z );
			}

			//! \brief Построить матрицу поворота по кватерниону.  ПРОВЕРЕНО!
			mat44_s& setRotationQuaternion(const geom3d::Quaternion& q) ;


			//! \brief Построить как матрицу трансформации 
			mat44_s& setTransformation(const vec3_s& vScale, 
								            const geom3d::Quaternion& qRotation,
								            const vec3_s& vTranslation);

			//! \brief Построить как матрицу трансформации 
			mat44_s& setWorldTransform(const geom3d::TransformData& t);


			//! \brief Построение ортографической левосторонней проекционной матрицы. ПРОВЕРЕНА.
			inline void setOrthoLH(float w, float h, float zn, float zf)
			{
				_11=2.0f/w;    _12=0.0f;       _13=0.0f;           _14=0.0f;
				_21=0.0f;      _22=2.0f/h;     _23=0.0f;           _24=0.0f;
				_31=0.0f;      _32=0.0f;       _33=1.0f/(zf-zn);   _34=0.0f;
				_41=0.0f;      _42=0.0f;       _43= -zn/(zf-zn);   _44=1.0f;

				// 2/w  0    0           0
				// 0    2/h  0           0
				// 0    0    1/(zf-zn)   0
				// 0    0   -zn/(zf-zn)  1
			}

			//! \brief Построение ортографической правосторонней проекционной матрицы. ПРОВЕРЕНА.
			inline void setOrthoRH(float w, float h, float zn, float zf)
			{
				_11=2.0f/w;     _12=0.0f;    _13=0.0f;          _14=0.0f;
				_21=0.0f;       _22=2.0f/h;  _23=0.0f;          _24=0.0f;
				_31=0.0f;       _32=0.0f;    _33=1.0f/(zn-zf);  _34=0.0f;
				_41=0.0f;       _42=0.0f;    _43=zn/(zn-zf);    _44=1.0f;

				// 2/w  0    0           0
				// 0    2/h  0           0
				// 0    0    1/(zn-zf)   0
				// 0    0    zn/(zn-zf)  l
			}


			//! \brief Построение ортографической матрицы   ПРОВЕРЕНА 
			inline void setOrthoOffCenterLH(float minX, float maxX, float minY, float maxY, float zn, float zf) 
			{
				_11 = 2.0f/(maxX-minX);         _12 = 0.0f,                     _13 = 0.0f,            _14 = 0.0f;
				_21 = 0.0f,                     _22 = 2.0f/(maxY-minY);         _23 = 0.0f,            _24 = 0.0f;
				_31 = 0.0f,                     _32 = 0.0f,                     _33 = 1.0f/(zf-zn);    _34 = 0.0f;
				_41 = (minX+maxX)/(minX-maxX);  _42 = (maxY+minY)/(minY-maxY);  _43 = zn/(zn-zf);      _44 = 1.0f;
			}
 

			//! \brief Построение ортографической матрицы  ПРОВЕРЕНА   
			inline void setOrthoOffCenterRH(float minX, float maxX, float minY, float maxY, float zn, float zf)
			{
				_11=2.0f/(maxX-minX);        _12=0.0f;                     _13=0.0f;            _14=0.0f;
				_21=0.0f;                    _22=2.0f/(maxY-minY);         _23=0.0f;            _24=0.0f;
				_31=0.0f;                    _32=0.0f;                     _33=1.0f/(zn-zf);    _34=0.0f;  
				_41=(minX+maxX)/(minX-maxX); _42=(maxY+minY)/(minY-maxY);  _43=zn/(zn-zf);      _44=1.0f;  

				// 2/(r-l)      0            0           0
				// 0            2/(t-b)      0           0
				// 0            0            1/(zn-zf)   0
				// (l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  l
			}
 

			//-------------------------------------------------------------

			//! \brief построение перспективной левосторонней матрицы. ПРОВЕРЕНА.
			void setPerspectiveFovLH(float fov, float asp, float zn, float zf) 
			{
				const float yScale =   gb::math::scalar::cotan(fov/2.0f); //yScale = cot(fovY/2)
				const float xScale = yScale / asp;     //xScale = yScale / aspect ratio

				//xScale     0          0               0
				//0        yScale       0               0
				//0          0       zf/(zf-zn)         1
				//0          0       -zn*zf/(zf-zn)     0
				_11 = xScale;   _12 = 0.0f;    _13 = 0.0f;             _14 = 0.0f;
				_21 = 0.0f;     _22 = yScale;  _23 = 0.0f;             _24 = 0.0f;
				_31 = 0.0f;     _32 = 0.0f;    _33 =  zf/(zf-zn);      _34 = 1.0f;
				_41 = 0.0f;     _42 = 0.0f;    _43 = -zn*zf/(zf-zn);   _44 = 0.0f;
			}

			//! \brief построение перспективной правосторонней матрицы. ПРОВЕРЕНА.
			void setPerspectiveFovRH(float fov, float asp, float zn, float zf)
			{
			 const float yScale =   gb::math::scalar::cotan(fov/2.0f);
			 const float xScale = yScale / asp; 
				
			    _11 = xScale;   _12 = 0.0f;    _13 = 0.0f;           _14 = 0.0f;
				_21 = 0.0f;     _22 = yScale;  _23 = 0.0f;           _24 = 0.0f;
				_31 = 0.0f;     _32 = 0.0f;    _33 = zf/(zn-zf);     _34 = -1.0f;
				_41 = 0.0f;     _42 = 0.0f;    _43 = zn*zf/(zn-zf);  _44 = 0.0f;					
				// xScale     0          0              0
				// 0        yScale       0              0
				// 0        0        zf/(zn-zf)        -1
				// 0        0        zn*zf/(zn-zf)      0
				// where:
				// yScale = cot(fovY/2)   
				// xScale = yScale / aspect ratio
			}


			//! \brief Построение перспективной левосторонней матрицы по высоте и ширине .ПРОВЕРЕНА.
			void setPerspectiveLH(float w, float h, float zn, float zf) 
			{
				// 2*zn/w  0       0              0
				// 0       2*zn/h  0              0
				// 0       0       zf/(zf-zn)     1
				// 0       0       zn*zf/(zn-zf)  0

				_11 = 2.0f*zn/w;  _12 = 0.0f,        _13 = 0.0f,           _14 = 0.0f;
				_21 = 0.0f,       _22 = 2.0f*zn/h;   _23 = 0.0f,           _24 = 0.0f;
				_31 = 0.0f,       _32 = 0.0f,        _33 = zf/(zf-zn);     _34 = 1.0f;
				_41 = 0.0f,       _42 = 0.0f,        _43 = zn*zf/(zn-zf);  _44 = 0.0f;
			}

			//! \brief Построение перспективной правосторонней матрицы по высоте и ширине. ПРОВЕРЕНА.
			void setPerspectiveRH(float w, float h, float zn, float zf) 
			{
				// 2*zn/w  0       0              0
				// 0       2*zn/h  0              0
				// 0       0       zf/(zn-zf)    -1
				// 0       0       zn*zf/(zn-zf)  0

				_11 = 2.0f*zn/w;  _12 = 0.0f,       _13 = 0.0f,           _14 = 0.0f;
				_21 = 0.0f,       _22 = 2.0f*zn/h;  _23 = 0.0f,           _24 = 0.0f;
				_31 = 0.0f,       _32 = 0.0f,       _33 = zf/(zn-zf);     _34 = -1.0f;
				_41 = 0.0f,       _42 = 0.0f,       _43 = zn*zf/(zn-zf);  _44 = 0.0f;
			}
 

			//-------------------------------------------------------------

			/** \brief Построение левосторонней матрицы вида. ПРОВЕРЕНА.  */
			void setViewLookAtLH(const vec3_s& eye, const vec3_s& at, const vec3_s& up)
			{
            vec3_s  zaxis = (at - eye);  zaxis.normalize(); 
		    vec3_s  xaxis = up.cross(zaxis); xaxis.normalize();
		    vec3_s  yaxis =  zaxis.cross(xaxis); 

		   _11=xaxis.x;           _12=yaxis.x;            _13=zaxis.x;            _14=0.0f;
		   _21=xaxis.y;           _22=yaxis.y;            _23=zaxis.y;            _24=0.0f;
		   _31=xaxis.z;           _32=yaxis.z;            _33=zaxis.z;            _34=0.0f;
		   _41= -xaxis.dot(eye);  _42= -yaxis.dot(eye);   _43= -zaxis.dot(eye);   _44=1.0f;

			// zaxis = normal(At - Eye)
			// xaxis = normal(cross(Up, zaxis))
			// yaxis = cross(zaxis, xaxis)
			// xaxis.x           yaxis.x           zaxis.x          0
			// xaxis.y           yaxis.y           zaxis.y          0
			// xaxis.z           yaxis.z           zaxis.z          0
			// -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  l	
			}


			/** \brief Построение правосторонней матрицы вида. ПРОВЕРЕНА.  */
			void setViewLookAtRH(const vec3_s& eye, const vec3_s& at, const vec3_s& up)
			{
            vec3_s  zaxis = (eye - at);  zaxis.normalize(); 
		    vec3_s  xaxis = up.cross(zaxis); xaxis.normalize();
		    vec3_s  yaxis =  zaxis.cross(xaxis); 			
			
		   _11=xaxis.x;           _12=yaxis.x;            _13=zaxis.x;            _14=0.0f;
		   _21=xaxis.y;           _22=yaxis.y;            _23=zaxis.y;            _24=0.0f;
		   _31=xaxis.z;           _32=yaxis.z;            _33=zaxis.z;            _34=0.0f;
		   _41= -xaxis.dot(eye);  _42= -yaxis.dot(eye);   _43= -zaxis.dot(eye);   _44=1.0f;			
			
	    	// zaxis = normal(Eye - At)
	    	// xaxis = normal(cross(Up, zaxis))
	    	// yaxis = cross(zaxis, xaxis)	    
	    	//  xaxis.x           yaxis.x           zaxis.x          0
	    	//  xaxis.y           yaxis.y           zaxis.y          0
	    	//  xaxis.z           yaxis.z           zaxis.z          0
	     	// -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  	
			}


			/** \brief Построение левосторонней матрицы вида  по направлению взгляда */
			inline  void setViewDirLH(const vec3_s& eye, const vec3_s& dir, const vec3_s& up) 
			{ 
                #pragma message ("KS777 MATH::MAT44  need check setViewDirLH" __FILE__ )

				vec3_s to = dir.normalized();
				const float flen = eye.length();
				to.x += flen;
				to.y += flen;
				to.z += flen;

				vec3_s at = eye + to;
				setViewLookAtLH( eye, at, up);
			}

			/** \brief Построение правосторонней матрицы вида  по направлению взгляда */
			inline  void setViewDirRH(const vec3_s& eye, const vec3_s& dir, const vec3_s& up) 
			{ 
				#pragma message ("KS777 MATH::MAT44 warn  need check setViewDirRH" __FILE__ )

				vec3_s to = dir.normalized();
				const float flen = eye.length();
				to.x += flen;
				to.y += flen;
				to.z += flen;

				vec3_s at = eye + to;
				setViewLookAtRH( eye, at, up);
			}

 

			#if ( defined GB_OPENGL  && defined __GL_H__ )
			   /** \brief Старый способ  перемножения матрицы с текущей в OpenGL */
               inline void glMul()  { glMultMatrixf( (GLfloat*)&_11  ); }

			   /** \brief Старый способ загрузки матрицы  в OpenGL */
               inline void glLoad() { glLoadMatrixf( (GLfloat*)&_11  ); }
            #endif


#ifdef GB_D3D9  // d3d9 device methods

			   //! \brief Установить матрицу в устройство d3d9 как матрицу ВИДА 
			   inline HRESULT makeDevice9TransfView(IDirect3DDevice9* pdevice) const 
			   {
				   return pdevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&_11 );
			   }

			   //! \brief Установить матрицу в устройство d3d9 как матрицу ПРОЕКЦИИ  
			   inline HRESULT makeDevice9TransfProj(IDirect3DDevice9* pdevice) const
			   {
				   return pdevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_11 );
			   }

			   //! \brief Установить матрицу в устройство d3d9 как матрицу ТРАНСФОРМАЦИИ  	
			   inline HRESULT makeDevice9TransfWorld(IDirect3DDevice9* pdevice) 
			   {
				   return pdevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&_11 );
			   }

			   //! \brief Установить матрицу в девайс как матрицу трансформации по данному типу trType 		
			   inline HRESULT makeDevice9Transf(IDirect3DDevice9* pdevice, D3DTRANSFORMSTATETYPE trType ) const 
			   {
				   return pdevice->SetTransform( trType, (D3DMATRIX*)&_11 );
			   }




			   //! \brief Получить из устройства d3d9   матрицу ВИДА 
			   inline HRESULT readDevice9TransfView(IDirect3DDevice9* pdevice)   
			   {
				   return pdevice->GetTransform(D3DTS_VIEW, (D3DMATRIX*)&_11 );
			   }

			   //! \brief Получить из устройства устройства d3d9   матрицу ПРОЕКЦИИ  
			   inline HRESULT readDevice9TransfProj(IDirect3DDevice9* pdevice)  
			   {
				   return pdevice->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_11 );
			   }

			   //! \brief Получить из устройства устройства d3d9   матрицу ТРАНСФОРМАЦИИ  	
			   inline HRESULT readDevice9TransfWorld(IDirect3DDevice9* pdevice) 
			   {
				   return pdevice->GetTransform(D3DTS_WORLD, (D3DMATRIX*)&_11 );
			   }



#endif // GB_D3D9



				//! \brief Вывод значений на консоль
			   inline void print() const
			   {
				   printf("\n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n  ", 
					   _11, _12, _13, _14, 
					   _21, _22, _23, _24,
					   _31, _32, _33, _34,	 
					   _41, _42, _43, _44	 
					   );
			   }

		
		};
 

//-------------------------------------------------------------------------
//                         CONST
//-------------------------------------------------------------------------



static const mat22_s     MATRIX22_IDENTITY =  mat22_s 
(
  1.0f,  0.0f,
  0.0f,  1.0f
);


static const mat33_s     MATRIX33_IDENTITY =  mat33_s 
(
  1.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f,  1.0f
);

static const mat44_s     MATRIX44_IDENTITY =  mat44_s 
(
  1.0f,  0.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,  0.0f,
  0.0f,  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f,  0.0f,  1.0f 
);







		}
		// end namespace base
 

	}
	// end namespace math

}
// end namespace gb


// end file