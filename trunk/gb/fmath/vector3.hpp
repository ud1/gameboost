// vector3.hpp

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#pragma once


namespace gb
{

	namespace fmath
	{
	
	
		template <typename T>
		struct vector3 
		{
			T  x, y, z;

			inline vector3<T> ()
			{ 
				x = y = z = T(); 
			}

			inline vector3<T> (const vector3<T>& v)
			{ 
				x = v.x;   
				y = v.y;   
				z = v.z;   
			}
 
			inline vector3<T>(const vector2<T>& v, const T _z)
			{ 
				x = v.x;
				y = v.y;
				z =  _z;     
			}

			inline vector3<T>( T _x , T _y , T _z )
			{ 
				x = _x;
				y = _y;
				z = _z;  
			}
 
			inline vector3<T>(const T* _array) 
			{
				*this = _array;
			}

			//inline vector3<T>(vec4);

			//! \brief ������������ �� T-������� 
			inline void operator = (const T* _array)
			{
				x = _array[0];
				y = _array[1];
				z = _array[2]; 
			}
				 
			inline bool  operator == (const vector3<T> &v) const
			{
				return (x == v.x && y == v.y && z == v.z );
			}
			
			inline bool  operator != (const vector3<T> &v) const
			{
				return (x != v.x || y != v.y || z != v.z );
			}
 
 
			inline vector3<T>  operator + () const
			{
				return *this;
			}
			
			inline vector3<T>  operator - () const
			{	
				return vector3<T> res( -x, -y, -z );
			}

			inline vector3<T>  operator + (const vector3<T> &v) const
			{	
				vector3<T> res(*this); 
				res += v;	
				return res; 
			}
			
			inline vector3<T>  operator - (const vector3<T> &v) const
			{	
				vector3<T> res(*this); 
				res -= v;	
				return res; 
			}
			
			
			inline vector3<T>  operator * (T f) const         { vector3<T> res = *this;      res.x *= f;	res.y *= f;	res.z *= f;	return res; }
			inline vector3<T>  operator / (T f) const         { vector3<T> res = *this;	     res.x /= f;	res.y /= f;	res.z /= f;	return res; }

			
			
			inline vector3<T> &  operator += (const vector3<T> &v)
			{
				x += v.x;	
				y += v.y;	
				z += v.z;	
				return *this; 
			}
			
			inline vector3<T> &  operator -= (const vector3<T> &v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;	
				return *this; 
			}
			
			inline vector3<T> &  operator *= (const T value)
			{
				x *= value;	
				y *= value;	
				z *= value;	
				return *this; 
			}
			
			inline vector3<T> &  operator *= (const vector3<T> &v)
			{
				x *= v.x;
				y *= v.y;
				z *= v.z;
				return *this; 
			}
			
			inline vector3<T> &  operator /= (const T value)
			{
				x /= value;
				y /= value;
				z /= value;
				return *this; 
			}
			
			inline vector3<T> &  operator /= (const vector3<T> &v)
			{
				x /= v.x;
				y /= v.y;
				z /= v.z;
				return *this; 
			}
 
 
 
			inline vector3<T> &  operator += (const T value)
			{
				return vector3<T>(x + value, y + value, z + value);
			} 
			
			inline vector3<T> &  operator -= (const T value)
			{
				return vector3<T>(x - value, y - value, z - value);			
			}			
			

			inline operator  const T*() const  { return &x; }
			inline operator        T*()        { return &x; }
 

			inline T operator [] (const size_t index) const throw()
			{
				if(index>2)
				{
					throw std::runtime_error("invalid index");				
				}
				
				const T* parray = &x;
				return parray[index];
			}

			inline  T& operator [] (const size_t index)  throw()
			{
				if(index>2)
				{
					throw std::runtime_error("invalid index");
				}
				
				T* parray = &x;
				return *(parray + index);
			}



			/***************************
			#ifdef _D3D9_H_
						inline operator D3DVECTOR*() { return (D3DVECTOR*)&x; }
						inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&x; }
						inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=x; r.y=y; r.z=z; return r;  }
						inline void operator = (const D3DVECTOR& v) {	x=v.x; y=v.y; z=v.z; }
			#endif // #ifdef _D3D9_H_
			****************************/


			/****************************
			#ifdef __D3DX9MATH_H__
						inline operator D3DXVECTOR3*() { return (D3DXVECTOR3*)&x; }
						inline operator const D3DXVECTOR3*() const { return (D3DXVECTOR3*)&x; }
						inline operator D3DXVECTOR3() const  {  return D3DXVECTOR3(x,y,z); }
					   	inline void operator = (const D3DXVECTOR3& v) {	x=v.x; y=v.y; z=v.z; }
			#endif // #ifdef __D3DX9MATH_H__
			***************************/


			void operator = (const Point3& pnt);

			// old: setzero
		    inline void set_zero()
			{
				x = y = z = T(); 
			}
			
			// old:  empty
			inline bool is_zero() const
			{ 
				return (x==0.0f) && (y==0.0f) && (z==0.0f); 
			}
			
			// old: isZero
			inline bool is_zero(const T epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon );
			}			

			
			inline vector3<T>& set ( const T _x, const T _y, const T _z )
			{ 
				x=_x;
				y=_y; 
				z=_z; 
				return *this; 
			}
 

			inline T   length () const
			{
				return (T)sqrt ( x*x + y*y + z*z );	
			}
			
			// old :  lengthSq
			inline T   length_sq() const 
			{
			return (x*x + y*y + z*z);  
			}

			inline T  dot(const vector3<T>& a) const 
			{
				return x * a.x + y * a.y + z * a.z; 
			}

			inline vector3<T>& inverse()
			{
				x=-x;
				y=-y;
				z=-z;
				return *this; 
			}
			
			inline vector3<T>  inverted() const 
			{ 
				return vector3<T> (-x, -y, -z); 
			}

			inline vector3<T>    cross (const vector3<T> &v) const
			{
				vector3<T> r;
				r.x = y * v.z  -  z * v.y;
				r.y = z * v.x  -  x * v.z;
				r.z = x * v.y  -  y * v.x;
				return r;		 
			}

			//! \brief  ������������� 
			inline vector3<T>&   normalize ()	  
			{ 
				if( is_zero() ) // < ��� ����� ������. nan
				{
					assert(false && "apply normalize to zero vector");
					return *this;
				}					   

				register T _LEN = length(); 
				x /= fl; 
				y /= fl; 
				z /= fl; 
				return *this; 
			}

			//! \brief  ������� ��������������
			inline vector3<T>    normalized() const
			{ 
				vector3<T> res(*this); 
				res.normalize(); 
				return res;
			}

			//! \brief  ��������� � ������� ���������� ����� �������  this � point.
			inline T distance(const vector3<T>& point)   const
			{ 
				return  sqrt( distanceSq(point) );  
			}
			//! \brief  ��������� � ������� ������� ���������� ����� �������  this � point.  old:  distanceSq
			inline T distance_sq(const vector3<T>& point) const 
			{ 
				return vector3<T>(*this-point).lengthSq();  
			}
 

			//! \brief �������� ���������� ���������� �� ������ ����������  old:  getMaxLength
			inline T     get_max_length () const
			{
				// old line:  return scalar::max3 ( fabs (x), fabs (y), fabs (z) );
				return scalar::max3 ( abs (x), abs (y), abs (z) );
			}

			inline vector3<T>&  invert()
			{
				x = -x;
				y = -y;
				z = -z;
				return *this; 
			}

			inline vector3<T>   lerp(const vector3<T>& v, const T k) const 
			{
				vector3<T> r;
				r.x = x + (v.x - x) * k;
				r.y = y + (v.y - y) * k;
				r.z = z + (v.z - z) * k;
				return r;			
			}

			//! \brief     �������� ����������� ����������  old:  minval
			inline T min_value() const   
			{ 
				T ret = x;
				if (y < ret) ret = y;
				if (z < ret) ret = z;
				return ret;
			}

			//! \brief     �������� ������������ ����������    old:  maxval
			inline T max_value()  const
			{  
				T ret = x;
				if (ret < y) ret = y;
				if (ret < z) ret = z;
				return ret;
			}



			//* \brief   ������. ���. ���������� �� ���������.    old:minAbsVal
			inline T min_abs_value() const 
			{
				T ax=abs(x);
				T ay=abs(y); 
				T az=abs(z); 
				T res=ax;
				
				if(ay<res) res=ay;
				if(az<res) res=az;
				return res;
			}

			//* \brief   ������. ����. ���������� �� ���������.    old:
			inline T max_abs_value() const
			{
				T ax=abs(x);
				T ay=abs(y); 
				T az=abs(z); 
				T res=ax;
				
				if(ay>res) res=ay;
				if(az>res) res=az;
				return res;
			}



/* 			//! \brief  �������� ��� ������� v1 � v2 � ��������� ������������ 
			vector3<T>& maximize(const vector3<T>& v1, const vector3<T>& v2) 
			{
				if (v1.x > v2.x) x = v1.x; else x = v2.x;
				if (v1.y > v2.y) y = v1.y; else y = v2.y;
				if (v1.z > v2.z) z = v1.z; else z = v2.z;
				return *this;
			} */

			//! \brief  �������� ������ v � ����������� �������� � ��������� ������������
			vector3<T>& maximize(const vector3<T>& v)
			{
				if (v.x > x) x = v.x; 
				if (v.y > y) y = v.y; 
				if (v.z > z) z = v.z; 
				return *this;
			}

/* 			//! \brief  �������� ��� ������� v1 � v2 � ��������� ����������� 
			vector3<T>& minimize(const vector3<T>& v1, const vector3<T>& v2) 
			{
				if (v1.x < v2.x) x = v1.x; else x = v2.x;
				if (v1.y < v2.y) y = v1.y; else y = v2.y;
				if (v1.z < v2.z) z = v1.z; else z = v2.z;
				return *this;
			} */

			//! \brief  �������� ������ v � ����������� �������� � ��������� �����������  
			vector3<T>& minimize(const vector3<T>& v) 
			{
				if (v.x < x) x = v.x;
				if (v.y < y) y = v.y;
				if (v.z < z) z = v.z;
				return *this;
			}

			//! \brief ������� ����������� ������ ����� this � v
			inline vector3<T> minimized(const vector3<T>& v) const
			{ 
				vector3<T> res(*this); 
				res.minimize(v); 
				return res;
			}
			
			//! \brief ������� ������������ ������ ����� this � v
			inline vector3<T> maximized(const vector3<T>& v) const
			{ 
				vector3<T> res(*this); 
				re.maximize(v); 
				return res;
			}



			//! \brief  ����� �������� � ��������� ����� vmin � vmax
			inline vector3<T>& clump(const vector3<T>& vmin, const vector3<T>& vmax) 
			{
				if( x < vmin.x) x = vmin.x;  if(x > vmax.x) x = vmax.x;
				if( y < vmin.y) y = vmin.y;  if(y > vmax.y) y = vmax.y;
				if( z < vmin.z) z = vmin.z;  if(z > vmax.z) z = vmax.z;
				  return *this;
			}

			//! \brief ������� ������� ����� ����� this � point
			inline vector3<T> middle(const vector3<T>& point) const 
			{
				vector3<T> res;
				const T _TWO = (T)2;
				res.x = ( x + point.x ) / _TWO;
				res.y = ( y + point.y ) / _TWO;			
				res.z = ( z + point.z ) / _TWO;
				return res;
			}

			//! \brief  ����� true ���� ��� ���������� �������������. old:  isPositive
			inline bool is_positive() const
			{
				return ( (x>=0.0f) && (y>=0.0f) && (z>=0.0f) );	
			}

			//! \brief ���������������� �� ������� m   ��� ����������. ���������!  old:  transformCoord
			vector3<T>&  transform_coord(const matrix4x4<T>& m); // const mat44& m
			
			//! \brief ���������������� �� ������� m   ��� �������. ���������! old: transformNormal
			vector3<T>&  transform_normal(const matrix4x4<T>& m); // const mat44& m
				
			 // TODO: 
			// void transformCoordArray(T* pfOut, int strideOut, const T* pvInput, int strideInput,  const M44& m, const int num) {...} 
			// void transformNormalArray(T* pfOut, int strideOut, const T* pvInput, int strideInput,  const M44& m, const int num) {...} 


			/** \brief  �������� ������� �� ������������ "����������" �� �����. 
			     ���������� ��������������� �������� ������. ���������!	*/
			vector3<T> project ( 
				const ViewportZ& vp,   //<  ������� ������
				const  matrix4x4<T>& Proj, //<	������� ��������
				const  matrix4x4<T>& View, //<	������� ����
				const  matrix4x4<T>& World //<	������� ���������
				)  const; 



			/** \brief ����������. ������� �� �������� ��������� � ��������������� ���������� 
			���������� ����������� ������ . ���������! */
			vector3<T>  unproject( 
				const ViewportZ& vp,    //<  ������� ������
				const  matrix4x4<T>& Proj,	//<	������� ��������
				const  matrix4x4<T>& View,	//<	������� ����
				const  matrix4x4<T>& World	//<	������� ���������
				) const	;


#pragma message ("delete tostr() fromstr()  "  __FILE__  )
 
 /*********************************
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
  *************************/


			// ! \brief ����� �������� �� �������
			// inline void print() const 
			// { 
				// printf("%f  %f  %f ", x, y, z); 
			// }


		  			  

			friend std::ostream &operator << (std::ostream &stream, const vector3<T>& v)
			{
				stream << v.x << " " << v.y << " " << v.z ;
				return stream;
			}

	#pragma message("!!!! Need operator >>  "   __FILE__ )		
			
			//friend std::istream &operator >> (std::istream &stream, vector3<T>& v)
			//{
			//	stream >> v.x >> " " >> v.y >> " " >> v.z ;
			//	return stream;
			//}




		
		
		};
	
	
	
	}

}





#endif // #ifndef __VECTOR3_H__
