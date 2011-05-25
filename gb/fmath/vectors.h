/** \file
 \brief  Вектор 2-х, 3-х, 4-х мерный.  

*/ 

#pragma once

#ifndef __GB_FMATH_H__
  #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

namespace gb 
{

 namespace fmath
 {

 
		/** \brief Базовый 2d-вектор.  Поправить операторы по эпислону */
		struct vec2 {

			union {
			
				struct {
				   float x, y;
				};

				float floats [2];
			};

			    inline vec2() {}

			    inline vec2(const vec2& v)      { x=v.x;  y=v.y;  }
				inline vec2(const vec2* v)      { x=v->x;  y=v->y;    }

			    inline vec2(float _x, float _y)   { x=_x;   y=_y;   }
			    //inline vec2(int   _x, int   _y)   { x=(float)_x;   y=(float)_y; }

				inline vec2(const float* pfArray) { *this = pfArray; }

				//! \brief Присваивание из float-массива 
				inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; }

				inline bool  operator == (const vec2 & v) const {	return (x == v.x && y == v.y  ); }
				inline bool  operator != (const vec2 & v) const {	return (x != v.x || y != v.y  ); }

				//inline bool  operator <  (const vec2 & v) const { return (x < v.x && y < v.y );    }
				//inline bool  operator <= (const vec2 & v) const {	return (x <= v.x && y <= v.y);   }
				//inline bool  operator >  (const vec2 & v) const {	return (x > v.x && y > v.y);     }
				//inline bool  operator >= (const vec2 & v) const {	return (x >= v.x && y >= v.y );  }

				inline vec2  operator + () const   { 	return *this; }
				inline vec2  operator - () const   { vec2 res; res.x = -x;	res.y = -y;	return res; }

				inline vec2  operator + (const vec2 &v) const { vec2 res;	res = *this; res += v; return res; }
				inline vec2  operator - (const vec2 &v) const {	vec2 res;	res = *this; res -= v; return res; }
				inline vec2  operator * (float f) const         { vec2 res;	res = *this; res.x *= f;  res.y *= f; return res; }
				inline vec2  operator / (float f) const         { vec2 res;	res = *this; res.x /= f;  res.y /= f; return res; }

				inline vec2 &  operator += (const vec2 &v)  { x += v.x; y += v.y;   return *this; }
				inline vec2 &  operator -= (const vec2 &v)  { x -= v.x; y -= v.y;   return *this; }
				inline vec2 &  operator *= (float f)          { x *= f;   y *= f;	    return *this; }
				inline vec2 &  operator *= ( const vec2& v) { x *= v.x;	y *= v.y;	return *this; }

				inline vec2 &  operator /= (float f)           { x /= f;    y /= f;   return *this; }
				inline vec2 &  operator /= ( const vec2& v ) { x /= v.x;  y /= v.y; return *this; }



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


#ifdef __D3DX9MATH_H__

			inline operator const D3DXVECTOR2*() const { return (D3DXVECTOR2*)&x; }
			inline operator   D3DXVECTOR2*()   { return (D3DXVECTOR2*)&x; }
			inline operator   D3DXVECTOR2() const  { return D3DXVECTOR2(x,y); }
			
			inline void operator = (const D3DXVECTOR2& v) {	x=v.x; y=v.y; }
#endif



//#if ( defined(_WINDEF_) || defined(__GB_TYPES_H__) || defined(__wtypes_h__) )
#if ( defined(_WINDOWS_) || defined(__GB_TYPES_H__) )
	 void operator = (const POINT& p)
	 {
		 x = (float)p.x;
		 y = (float)p.y;
	 }
#endif




				inline void setzero() {x=y=0.0f; }
				inline bool empty() const { return ( (x==0.0f) && (y==0.0f) ); }

				inline vec2& set     (float _x, float _y) {x=_x; y=_y;  return *this; }
				inline vec2& set_all (float val) { x=val; y=val;        return *this; }

				inline bool isZero(float epsilon) const
				{
					return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon );
				}

 
				inline float     length () const  {	return (float)sqrt ( x*x + y*y );	}
			    inline float     lengthSq() const {	 return (x*x + y*y );  }

				inline float distance(const vec2& point) const 
				{
					return  sqrt( distanceSq( point ) );  
				}

				inline float distanceSq(const vec2& point) const 
				{ 
					return vec2(*this - point).lengthSq();  
				}


				inline vec2&   normalize() 
				{ 
					if( (0.0f==x) && (0.0f==y) ) // < без этого глючит. nan
						return *this; 
					register float fl=length(); 
					x/=fl; 
					y/=fl;  
					return *this; 
				}

				//! \brief  Вернуть нормализованый
				inline vec2 normalized() const 
				{
				 vec2 res(*this);
				 res.normalize();
				 return res;
				}

				inline float  dot(const vec2& v) const { return x*v.x + y*v.y; }

 
				//! \brief Returns the z-component by taking the cross product of two 2D vectors.  ПРОВЕРЕНА!  
				float ccw(const vec2& v) const ;


				//! \brief  Инвертировать (поменять знаки компонентов).
				inline vec2& inverse() 
				{ 
					x=-x; 
					y=-y; 
					return *this; 
				}

				//! \brief Вернуть вектор, с противоположными знаками
				inline vec2  inverted() const 
				{
					return vec2 ( -x, -y ); 
				}
 		

				inline float     getMaxLength () const {  if( fabs (x) >= fabs (y) ) return x; else return y;   }

  			   // inline vec2&   invert() {x=-x; y=-y;  return *this; }

				inline vec2    lerp(const vec2& v, const float k) const
				{
					vec2 r;
					r.x = x + (v.x - x) * k;
					r.y = y + (v.y - y) * k;
					return r;			
				};

				

				//! \brief  Получить минимальную компоненту   
				inline float minVal() const { if(x<y) return x;   return y; }
				//! \brief  Получить Максимальную компоненту   
				inline float maxVal() const { if(x>y) return x;   return y; }

				//! \brief  Сравнить два вектора v1 и v2 и присвоить минимальный 
				inline vec2& minimize(const vec2& v1, const vec2& v2) 
				{
					if (v1.x < v2.x) x = v1.x; else  x = v2.x;
					if (v1.y < v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  Сравнить вектор v и собственное значение и присвоить минимальный  
				inline vec2& minimize(const vec2& v) 
				{
					if (v.x < x) x = v.x;
					if (v.y < y) y = v.y;
					return *this;
				}

				//! \brief  Сравнить два вектора v1 и v2 и присвоить максимальный  
				inline vec2& maximize(const vec2& v1, const vec2& v2) 
				{
					if (v1.x > v2.x) x = v1.x; else  x = v2.x;
					if (v1.y > v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  Сравнить вектор v и собственное значение и присвоить максимальный 
				inline vec2& maximize(const vec2& v) 
				{
					if (v.x > x) x = v.x;
					if (v.y > y) y = v.y;
					return *this;
				}

				//! \brief Вернуть минимальный вектор между this и v
				inline vec2 minimized(const vec2& v) const { vec2 r; r.minimize(*this, v); return r; };
				//! \brief Вернуть максимальный вектор между this и v
				inline vec2 maximized(const vec2& v) const { vec2 r; r.maximize(*this, v); return r; };


				//! \brief  вычислить мин. абсолютное значение компонент. 
				inline float minAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax; if(ay<res) res=ay; return res; }
				//! \brief  вычислить макс. абсолютное значение компонент 
				inline float maxAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax;  if(ay>res) res=ay; return res; }


				//! \brief  вычисление миним, компоненты 
				inline float minval() const { if(x<y) return x; return y;	}
				//! \brief  вычисление. макс компоненты 
				inline float maxval() const { if(x>y) return x; return y;	}


				//! \brief  Отсечение значений в пределах vmin и vmax
				inline void clump(const vec2& vmin, const vec2& vmax) 
				{
					if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
					if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				}

			//! \brief Вернуть среднюю точку между this и point
			inline vec2 middle(const vec2& point) const 
			{
			    vec2 res;
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
		struct vec3  {

		    union {
			
				struct {
				   float x, y, z;
				};

				float floats [3];
			};

			inline vec3() {}

			inline vec3(const vec3& v)             { x=v.x;   y=v.y;   z=v.z;   }
			inline vec3(const vec3* v)             { x=v->x;  y=v->y; z=v->z;   }

			inline vec3(const vec2& v, float _z)   { x=v.x;  y=v.y; z=_z;     }

			inline vec3(float _x, float _y, float _z)   { x=_x;    y=_y;    z=_z;  }
			inline vec3(int   _x, int   _y, int   _z)   { x=(float)_x;   y=(float)_y;  z=(float)_z; }

			inline vec3(const float* pfArray) { *this = pfArray; }

			//inline vec3(vec4);

			//! \brief Присваивание из float-массива 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; }
				 
			inline bool  operator == (const vec3 &v) const { return (x == v.x && y == v.y && z == v.z ); }
			inline bool  operator != (const vec3 &v) const { return (x != v.x || y != v.y || z != v.z ); }

			//inline bool  operator <  (const vec3 &v) const {	return (x <  v.x && y <  v.y && z <  v.z ); }
			//inline bool  operator <= (const vec3 &v) const {	return (x <= v.x && y <= v.y && z <= v.z ); }
			//inline bool  operator >  (const vec3 &v) const {	return (x >  v.x && y >  v.y && z >  v.z ); }
			//inline bool  operator >= (const vec3 &v) const {	return (x >= v.x && y >= v.y && z >= v.z ); }

			inline vec3  operator + () const   { 	return *this; }
			inline vec3  operator - () const{	vec3 res;	res.x = -x;	res.y = -y;	res.z = -z;	return res; }

			inline vec3  operator + (const vec3 &v) const {	vec3 res;	res = *this; res += v;	return res; }
			inline vec3  operator - (const vec3 &v) const {	vec3 res;	res = *this; res -= v;	return res; }
			inline vec3  operator * (float f) const         { vec3 res = *this;      res.x *= f;	res.y *= f;	res.z *= f;	return res; }
			inline vec3  operator / (float f) const         { vec3 res = *this;	     res.x /= f;	res.y /= f;	res.z /= f;	return res; }

			inline vec3 &  operator += (const vec3 &v)    {	x += v.x;	y += v.y;	z += v.z;	return *this; }
			inline vec3 &  operator -= (const vec3 &v)    {	x -= v.x;	y -= v.y;	z -= v.z;	return *this; }
			inline vec3 &  operator *= (float f)            {	x *= f;	y *= f;	z *= f;	return *this; }
			inline vec3 &  operator *= (const vec3 &v)    {	x *= v.x;	y *= v.y;	z *= v.z;	return *this; }
			inline vec3 &  operator /= (float f)            {	x /= f;	y /= f;	z /= f;	return *this; }
			inline vec3 &  operator /= (const vec3 &v)    {	x /= v.x;	y /= v.y;	z /= v.z;	return *this; }
 
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




#ifdef _D3D9_H_
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=x; r.y=y; r.z=z; return r;  }
			inline void operator = (const D3DVECTOR& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef _D3D9_H_

#ifdef __D3DX9MATH_H__
			inline operator D3DXVECTOR3*() { return (D3DXVECTOR3*)&x; }
			inline operator const D3DXVECTOR3*() const { return (D3DXVECTOR3*)&x; }
			inline operator D3DXVECTOR3() const  {  return D3DXVECTOR3(x,y,z); }
		   	inline void operator = (const D3DXVECTOR3& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef __D3DX9MATH_H__

			void operator = (const gb::fmath::geom3d::Point3& pnt);


		    inline void setzero() {x=y=z=0.0f; }
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) ); }

			inline vec3& set    (float _x, float _y, float _z) { x=_x; y=_y; z=_z; return *this; };
			inline vec3& set_all(float val) { x=val; y=val; z=val;                 return *this; }

			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon )  ;
			}

			inline float     length () const {	return (float)sqrt ( x*x + y*y + z*z );	}
			inline float     lengthSq() const {	 return (x*x + y*y + z*z);  }

			inline float     dot(const vec3& v) const { return x*v.x + y*v.y + z*v.z; }

			inline vec3& inverse() { x=-x; y=-y; z=-z; return *this; }
			inline vec3  inverted() const { return vec3 (-x, -y, -z); }

			inline vec3    cross (const vec3 &v) const
			{
				      vec3 r;
			        r.x = y * v.z  -  z * v.y;
			        r.y = z * v.x  -  x * v.z;
			        r.z = x * v.y  -  y * v.x;
					return r;		 
			}

			//! \brief  Нормализовать 
			inline vec3&   normalize ()	  
			{ 
				if( (0.0f==x) && (0.0f==y) && (0.0f==z) ) // < без этого глючит. nan
					   return *this; 

				register float fl=length(); 
				x/=fl; 
				y/=fl; 
				z/=fl; 
				return *this; 
			}

			//! \brief  Вернуть нормализованый
			inline vec3    normalized() const { vec3 r=*this; r.normalize(); return r; }

			//! \brief  Вычислить и вернуть расстояние между точками  this и point.
			inline float distance(const vec3& point)   const { return  sqrt( distanceSq(point) );  }
			//! \brief  Вычислить и вернуть квадрат расстояния между точками  this и point.
			inline float distanceSq(const vec3& point) const { return vec3(*this-point).lengthSq() ;  }
 

			//! \brief Получить наибольшее абсолютное из каждой компоненты
			inline float     getMaxLength () const {   return scalar::max3 ( fabs (x), fabs (y), fabs (z) );   }

			inline vec3&   invert() {x=-x; y=-y; z=-z; return *this; };

			inline vec3    lerp(const vec3& v, const float k) const 
			{
				vec3 r;
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
			vec3& maximize(const vec3& v1, const vec3& v2) 
			{
				if (v1.x > v2.x) x = v1.x; else x = v2.x;
				if (v1.y > v2.y) y = v1.y; else y = v2.y;
				if (v1.z > v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  Сравнить вектор v и собственное значение и присвоить максимальный
			vec3& maximize(const vec3& v)
			{
				if (v.x > x) x = v.x; 
				if (v.y > y) y = v.y; 
				if (v.z > z) z = v.z; 
				return *this;
			}

			//! \brief  Сравнить два вектора v1 и v2 и присвоить минимальный 
			vec3& minimize(const vec3& v1, const vec3& v2) 
			{
				if (v1.x < v2.x) x = v1.x; else x = v2.x;
				if (v1.y < v2.y) y = v1.y; else y = v2.y;
				if (v1.z < v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  Сравнить вектор v и собственное значение и присвоить минимальный  
			vec3& minimize(const vec3& v) 
			{
				if (v.x < x) x = v.x;
				if (v.y < y) y = v.y;
				if (v.z < z) z = v.z;
				return *this;
			}

			//! \brief Вернуть минимальный вектор между this и v
			inline vec3 minimized(const vec3& v) const { vec3 r; r.minimize(*this, v); return r; };
			//! \brief Вернуть максимальный вектор между this и v
			inline vec3 maximized(const vec3& v) const { vec3 r; r.maximize(*this, v); return r; };



			//! \brief  отсеч значения в диапазоне между vmin и vmax
			inline vec3& clump(const vec3& vmin, const vec3& vmax) 
			{
				if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
				if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				if( z < vmin.z) z=vmin.z;  if(z > vmax.z) z=vmax.z;
				  return *this;
			}

			//! \brief Вернуть среднюю точку между this и point
			inline vec3 middle(const vec3& point) const 
			{
			    vec3 res;
			      res.x = ( x + point.x ) / 2.0f;
			      res.y = ( y + point.y ) / 2.0f;			
			      res.z = ( z + point.z ) / 2.0f;
			         return res;
			}

			//! \brief  Вернёт true если все компоненты положительные.
			inline bool isPositive() const {  return ( (x>=0.0f) && (y>=0.0f) && (z>=0.0f) );	}

			//! \brief Тарнсформировать по матрице m   как координату. ПРОВЕРЕНО!
			vec3&  transformCoord(const mat44& m);
			//! \brief Тарнсформировать по матрице m   как нормаль. ПРОВЕРЕНО!
			vec3&  transformNormal(const mat44& m);
				
			 // TODO: 
			    // void transformCoordArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 
			    // void transformNormalArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 


			/** \brief  Проекция вектора из виртуального "зазеркалья" на экран. 
			     Возвращает спроектированый экранный вектор. ПРОВЕРЕНА!	*/
			vec3 project ( 
				const proj::ViewportZ& vp,   //<  область вывода
				const  mat44& Proj, //<	матрица проекции
				const  mat44& View, //<	матрица вида
				const  mat44& World //<	матрица модельная
				)  const; 



			/** \brief Анпроекция. Перевод из экранных координат в пространственые координаты 
			Возвращает переведённый вектор . ПРОВЕРЕНА! */
			vec3  unproject( 
				const proj::ViewportZ& vp,    //<  область вывода
				const  mat44& Proj,	//<	матрица проекции
				const  mat44& View,	//<	матрица вида
				const  mat44& World	//<	матрица модельная
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

		}; // end vec3
		

		/** \brief Базовый 4d-вектор. Поправить операторы по эпислону   */		
		struct vec4  {

		    union {
			
				struct {
				   float x, y, z, w;
				};

				float floats [4];
			};

			inline vec4() {};

			inline vec4(const vec4& v)      { x=v.x;  y=v.y; z=v.z; w=v.w;  };
//			inline vec4(const vec4* v)      { x=v->x;  y=v->y; z=v->z; w=v->w;  };

			inline vec4(const vec3& v, float _w)  { x=v.x;  y=v.y; z=v.z; w=_w;  };

			inline vec4(const vec2& v, float _z, float _w) {x=v.x; y=v.y; z=_z; w=_w; }

			inline vec4(float _x, float _y, float _z, float _w)   { x=_x;   y=_y; z=_z; w=_w;  }
			inline vec4(int   _x, int   _y, int   _z, int   _w)   { x=(float)_x;   y=(float)_y;  z=(float)_z; w=(float)_w;}

			//! \brief Присваивание из float-массива 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; w=pf[3]; }
 
					 
			inline bool  operator == (const vec4 &v) const {	return (x == v.x && y == v.y && z == v.z && w == v.w); }
			inline bool  operator != (const vec4 &v) const {	return (x != v.x || y != v.y || z != v.z || w != v.w); }
 
			inline vec4  operator + () const   { 	return *this; }
			inline vec4  operator - () const { vec4 res;	res.x = -x;	res.y = -y;	res.z = -z;	res.w = -w;	return res; }

			inline vec4  operator + (const vec4 &v) const {	vec4 res;	res = *this;	res += v;	return res; }
			inline vec4  operator - (const vec4 &v) const {	vec4 res;	res = *this;	res -= v;	return res; }
			inline vec4  operator * (float f) const         {	vec4 res;	res = *this;	res.x *= f;	res.y *= f;	res.z *= f;	res.w *= f;	return res; }
			inline vec4  operator / (float f) const         {	vec4 res;	res = *this;	res.x /= f;	res.y /= f;	res.z /= f;	res.w /= f;	return res; }

			inline vec4 &  operator += (const vec4 &v) {	x += v.x;	y += v.y;	z += v.z;	w += v.w;	return *this; }
			inline vec4 &  operator -= (const vec4 &v) {	x -= v.x;	y -= v.y;	z -= v.z;	w -= v.w;	return *this; }
			inline vec4 &  operator *= (float f)         {	x *= f;	y *= f;	z *= f;	w *= f;	return *this; }

			inline vec4 &  operator /= (float f)         {	x /= f;	y /= f;	z /= f;	w /= f;	return *this; }

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




#ifdef __D3DX9MATH_H__
			inline operator D3DXVECTOR4*() { return (D3DXVECTOR4*)&x; }
			inline operator const D3DXVECTOR4*() const { return (D3DXVECTOR4*)&x; }
			inline operator D3DXVECTOR4() const  {  return D3DXVECTOR4(x,y,z,w); }
		   	inline void operator = (const D3DXVECTOR4& v) {	x=v.x; y=v.y; z=v.z; w=v.w; }	
#endif					
			
			//! \brief Обнулить все компоненты
		    inline void setzero() {x=y=z=w=0.0f; }
			//! проверить равны ли все компоненты нулю
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) && (w==0.0f) ); }

			inline vec4& set    (float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; return *this; }
 
			//! \brief  Все ли компоненты нулевые по эпсилону.
			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
			}

			//! \brief  получить длинну
			inline float length () const {	return (float)sqrt( x*x + y*y + z*z + w*w );	}
			//! \brief  получить квадрат длинны
			inline float lengthSq() const {	 return (x*x + y*y + z*z + w*w);  }

			//! \brief   Вернуть скалярное произведение с вектором v
			inline float   dot (const vec4& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

			
#pragma message ("KS777: MATH::VEC4 >> NEED CHECK CROSS METHOD !!!"  __FILE__)
			//! \brief Получить векторное (перекрестное)  произведение с вектором v.
			inline vec4  cross ( const vec4 & v) const
			{
				  vec4 r;
				r.x = ( z * v.w - w * v.z) * y + ( w * v.y - y * v.w) * z + ( y * v.z - z * v.y) * w;
				r.y = ( w * v.z - z * v.w) * x + ( x * v.w - w * v.x) * z + ( z * v.x - x * v.z) * w;
				r.z = ( y * v.w - w * v.y) * x + ( w * v.x - x * v.w) * y + ( x * v.y - y * v.x) * w;
				r.w = ( z * v.y - y * v.z) * x + ( x * v.z - z * v.x) * y + ( y * v.x - x * v.y) * z;
				  return r;
			}


			// НЕПРАВИЛЬНО !!!!
			void cross( const vec4& U, const vec4& V, const vec4& W )   
			{
				assert(false && "bad code !");

				float a = V.x*W.y - V.y*W.x;
				float b = V.x*W.z - V.z*W.x;
				float c = V.x*W.w - V.w*W.x;
				float d = V.y*W.z - V.z*W.y;
				float e = V.y*W.w - V.w*W.y;
				float f = V.z*W.w - V.w*W.z;

				vec4 Out;
				Out.x = f*U.y - e*U.z + d*U.w ;
				Out.y = f*U.x + c*U.z - b*U.w ; // no valid
				Out.z = e*U.x - c*U.y + a*U.w ;
				Out.w = d*U.x + b*U.y - a*U.z ; // no valid


				*this = Out;
			}

			//! \brief  Инвертировать.
			inline vec4&   invert() {  x=-x; y=-y; z=-z; w=-w; return *this; };
			//! \brief  Вернуть инвертированый.
			inline vec4    inverted() const 
			{
				vec4 res = *this;
				res.invert();
				return res;
			}

			//! \brief  Вернуть вектор по линейной интерполяции между this и v  по коэффициенту k
			inline vec4    lerp(const vec4& v, const float k) 
			{
				vec4 r;
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
	inline void clump(const vec4& vmin, const vec4& vmax) 
	{
		if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
		if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
		if( z < vmin.z) z=vmin.z;  if(z > vmax.z) z=vmax.z;
		if( w < vmin.w) w=vmin.w;  if(w > vmax.w) w=vmax.w;
	};



	void toCstr(char* buf) const 
	{
		*buf = '\0';
	    sprintf(buf, "%f %f %f %f", x, y, z, w );
	}

	bool fromCstr(const char* s) 
	{
		const int NS = sscanf(s, "%f%f%f%f", &x, &y, &z, &w);
		if(4!=NS)  return false;
		return true;
	}



	//! \brief Вывод значений на консоль
	inline void print() const { printf(" %f  %f  %f  %f ", x, y, z, w); };

		}; 
		// end vec4

		//------------------------------------------------------------------








 }
 // end namespace fmath

}
// end namespace gb


// end file