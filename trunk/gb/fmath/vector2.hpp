// vector2.hpp

#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#pragma once


namespace gb
{

	namespace fmath
	{
	
	
		template <typename T>
		struct vector2 {

			T  x, y;

			inline vector2<T>() 
			{ 
				x=y=T(); 
			}

			inline vector2<T>(const vector2<T>& a)
			{ 
				x=a.x;
				y=a.y;
			}

			inline vector2<T>(const T& _x, const T& _y)   
			{ 
				x = _x;   
				y = _y;   
			}

			inline vector2<T>(const T* _array) 
			{ 
				*this = _array; 
			}

			inline void operator = (const T* _array) 
			{
				x = _array[0]; 
				y = _array[1]; 
			}

			inline bool  operator == (const vector2<T> & v) const 
			{	
				return (x == v.x && y == v.y  ); 
			}
			
			inline bool  operator != (const vector2<T> & v) const 
			{	
				return (x != v.x || y != v.y  ); 
			}

			
			inline vector2<T>  operator + () const   
			{ 	
				return *this; 
			}
			
			inline vector2<T>  operator - () const
			{ 
				return vector2<T>( -x , -y );
			}

			
			inline vector2<T>  operator + (const vector2<T> &v) const
			{ 
				vector2<T> res(*this);
				res += v; 
				return res; 
			}
			
			inline vector2<T>  operator - (const vector2<T> &v) const
			{	
				vector2<T> res(*this); 
				res -= v; 
				return res; 
			}


			inline vector2<T>  operator * (const T value) const         
			{ 
				vector2<T> res(*this); 
				res.x *= value;  
				res.y *= value; 
				return res; 
			}

			inline vector2<T>  operator / (const T value) const
			{ 
				vector2<T> res (*this); 
				res.x /= value;
				res.y /= value;
				return res; 
			}

			
			
			inline vector2<T> &  operator += (const vector2<T> &v)  
			{ 
				x += v.x; 
				y += v.y;
				return *this; 
			}
			
			inline vector2<T> &  operator -= (const vector2<T> &v)  
			{ 
				x -= v.x;
				y -= v.y;
				return *this; 
			}
			
			inline vector2<T> &  operator *= (const T value)
			{ 
				x *= value;
				y *= value;
				return *this; 
			}
			
			inline vector2<T> &  operator *= ( const vector2<T>& v) 
			{ 
				x *= v.x;
				y *= v.y;
				return *this;
			}


			inline vector2<T> &  operator /= (const T value)
			{ 
				x /= value;
				y /= value;
				return *this; 
			}
			
			inline vector2<T> &  operator /= ( const vector2<T>& v )
			{ 
				x /= v.x;
				y /= v.y;
				return *this; 
			}



			inline operator  const T*() const  { return (T*)&x; }
			inline operator        T*()        { return (T*)&x; }

#pragma message("!!NEED replace exception  to   bad index  "   __FILE__ )

			inline T operator [] (const size_t index) const throw()
			{
				if(index>1)
				{
					throw std::runtime_error("invalid index");
				}
				
				const T* parray = &x;
				return parray[index];
			}

			inline  T& operator [] (const size_t index) throw()
			{
				if(index>1)
				{
					throw std::runtime_error("invalid index");
				}
				
				T* parray = &x;
				return *(parray + index);
			}

			/**************************
			#ifdef __D3DX9MATH_H__

					inline operator const D3DXVECTOR2*() const { return (D3DXVECTOR2*)&x; }
					inline operator   D3DXVECTOR2*()   { return (D3DXVECTOR2*)&x; }
					inline operator   D3DXVECTOR2() const  { return D3DXVECTOR2(x,y); }
					inline void operator = (const D3DXVECTOR2& v) {	x=v.x; y=v.y; }
			#endif
			***********************/


			#if  defined(_WINDOWS_) && defined(WIN32)
			void operator = (const POINT& p)
			{
				x = (T)p.x;
				y = (T)p.y;
			}
			#endif
			
			
			/********************
			#ifdef   __GB_TYPES_H__
			void operator = (const POINT& p)
			{
				 x = (T)p.x;
				 y = (T)p.y;
			}
			#endif
			******************************/
 

 
			// old:  setzero
			inline void setzero() 
			{
				x = y = T(); 
			}
			
			// old: empty
			inline bool is_zero() const 
			{
				return (x==(T)0) && (y==(T)0); 
			}
			
			// old:  isZero
			inline bool is_zero(const T epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon );
			}		
			
			inline vector2<T>& set(const T _x, const T _y) 
			{
				x = _x; 
				y = _y;  
				return *this; 
			}
 

 
			inline T     length () const  
			{	
				return (T)sqrt ( x*x + y*y );
			}
			
			// old:  lengthSq
			inline T     length_sq() const 
			{	 
				return (x*x + y*y );  
			}



			inline T distance(const vector2<T>& point) const 
			{
				return  sqrt( distanceSq( point ) );  
			}

			// old:  distanceSq
			inline T distance_sq(const vector2<T>& point) const 
			{ 
				return vector2<T>(*this - point).lengthSq();  
			}


			inline vector2<T>& normalize() 
			{ 
				if( (0.0f==x) && (0.0f==y) ) // < ��� ����� ������. nan
				{
					return *this; 
				}
				
				register T _LEN = length(); 
				x /= _LEN;
				y /= _LEN; 
				return *this; 
			}

			//! \brief  ������� ��������������
			inline vector2<T> normalized() const 
			{
				vector2<T> res(*this);
				res.normalize();
				return res;
			}

			inline T  dot(const vector2<T>& a) const 
			{ 
				return x * a.x  +  y * a.y;
			}

#pragma message("??????? ccw  .... "   __FILE__ )
			
			//! \brief Returns the z-component by taking the cross product of two 2D vectors.  ���������!  
			T ccw(const vector2<T>& v) const;			


			//! \brief  ������������� (�������� ����� �����������).
			inline vector2<T>& inverse() 
			{ 
				x=-x; 
				y=-y; 
				return *this; 
			}

			//! \brief ������� ������, � ���������������� �������
			inline vector2<T>  inverted() const 
			{
				return vector2<T> ( -x, -y ); 
			}

			// old: getMaxLength
			inline T get_max_length () const 
			{  
				//  old:   if( fabs (x) >= fabs (y) ) 
				if( abs (x) >= abs (y) ) 
					return x; 
				else 
					return y;   
			}

		   // inline vector2<T>&   invert() {x=-x; y=-y;  return *this; }

			inline vector2<T> lerp(const vector2<T>& v, const T k) const
			{
				vector2<T> r;
				r.x = x + (v.x - x) * k;
				r.y = y + (v.y - y) * k;
				return r;			
			}


			//! \brief  �������� ����������� ����������     old: minVal
			inline T min_value() const
			{ 
				if( x < y ) 
					return x;   
				return y; 
			}
			
			//! \brief  �������� ������������ ����������    old: maxVal
			inline T max_value() const 
			{ 
				if( x > y ) 
					return x;   
				return y; 
			}

/* 			//! \brief  �������� ��� ������� v1 � v2 � ��������� ����������� 
			inline vector2<T>& minimize(const vector2<T>& v1, const vector2<T>& v2) 
			{
				if (v1.x < v2.x) x = v1.x; else  x = v2.x;
				if (v1.y < v2.y) y = v1.y; else  y = v2.y;
				return *this;
			} */

			//! \brief  �������� ������ v � ����������� �������� � ��������� �����������  
			inline vector2<T>& minimize(const vector2<T>& v) 
			{
				if (v.x < x) x = v.x;
				if (v.y < y) y = v.y;
				return *this;
			}

/* 			//! \brief  �������� ��� ������� v1 � v2 � ��������� ������������  
			inline vector2<T>& maximize(const vector2<T>& v1, const vector2<T>& v2) 
			{
				if (v1.x > v2.x) x = v1.x; else  x = v2.x;
				if (v1.y > v2.y) y = v1.y; else  y = v2.y;
				return *this;
			} */

			//! \brief  �������� ������ v � ����������� �������� � ��������� ������������ 
			inline vector2<T>& maximize(const vector2<T>& v) 
			{
				if (v.x > x) x = v.x;
				if (v.y > y) y = v.y;
				return *this;
			}

			//! \brief ������� ����������� ������ ����� this � v
			inline vector2<T> minimized(const vector2<T>& v) const 
			{ 
				vector2<T> r(*this); 
				r.minimize(v); 
				return r; 
			}
			
			//! \brief ������� ������������ ������ ����� this � v
			inline vector2<T> maximized(const vector2<T>& v) const 
			{ 
				vector2<T> r(*this); 
				r.maximize(v); 
				return r; 
			}


			//! \brief  ��������� ���. ���������� �������� ���������.  old:  minAbsVal
			inline T min_abs_value() const
			{
				T ax=abs(x); 
				T ay=abs(y); 
				
				if(ay < res) return ay; 
				return ax; 
			}
			
			//! \brief  ��������� ����. ���������� �������� ���������    old: maxAbsVal
			inline T max_abs_value() const
			{ 
				T ax=abs(x); 
				T ay=abs(y); 
				
				if(ay > res) return ay; 
				return res;
			}


			////! \brief  ���������� �����, ���������� 
			//inline T minval() const
			//{
			//	if(x < y) return x; 
			//	return y;
			//}
			
			////! \brief  ����������. ���� ����������  // old :   maxval
			//inline T max_value() const
			//{
			//	if(x > y) return x; 
			//	return y;
			//}


			//! \brief  ��������� �������� � �������� vmin � vmax
			inline vector2<T>& clump(const vector2<T>& vmin, const vector2<T>& vmax) 
			{
				if(x < vmin.x) x = vmin.x;  
				if(x > vmax.x) x = vmax.x;
				
				if(y < vmin.y) y = vmin.y;  
				if(y > vmax.y) y = vmax.y;
				
				return *this;
			}

			//! \brief ������� ������� ����� ����� this � point
			inline vector2<T> middle(const vector2<T>& point) const 
			{
				vector2<T> res;
				const T _TWO = (T)2;
				res.x = ( x + point.x ) / _TWO;
				res.y = ( y + point.y ) / _TWO;			
				return res;
			}


			//!  \brief   ����� true ���� ��� ���������� �������������.  old:  isPositive
			inline bool is_positive() const 
			{  
				return ( (x>=0.0f) && (y>=0.0f) );  
			}
 

			friend std::ostream &operator << (std::ostream &stream, const vector2<T>& v)
			{
				stream << v.x << " " << v.y;
				return stream;
			}

			#pragma message("NEED operator >> for vector2 "  __FILE__ )

			//friend std::istream &operator >> (std::istream &stream, vector2<T>& v)
			//{
			//	stream >> v.x >> " " >> v.y ;
			//	return stream;
			//}

			
			#pragma message("NEED operator << for vector2 "  __FILE__ )
	/*

			#if defined(_MSC_VER)
			#pragma warning( push )
			#pragma warning( disable : 4290 )
			#endif

			friend std::stringstream &operator >> (std::stringstream &stream, color3<T>& c) throw (std::invalid_argument)
			{
				stream >> c.r; 
				stream >> c.g; 
				stream >> c.b; 

				if(stream.fail())
				{
					throw std::invalid_argument("cast error");
				}

				return stream;
			}



			#if defined(_MSC_VER)
			#pragma warning( pop )
			#endif


	*/

		
		};
	
	
	
	}

}

#endif // #ifndef __VECTOR2_H__
