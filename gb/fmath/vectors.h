/** \file
 \brief  ������ 2-�, 3-�, 4-� ������.  

*/ 

#pragma once

#ifndef __GB_FMATH_H__
  #error �� ��������� ���� ����. ���������:   #include <gb/fmath/math.h>  
#endif

namespace gb 
{

 namespace fmath
 {

 
		/** \brief ������� 2d-������.  ��������� ��������� �� �������� */
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
			    //inline vec2_s(int   _x, int   _y)   { x=(float)_x;   y=(float)_y; }

				inline vec2_s(const float* pfArray) { *this = pfArray; }

				//! \brief ������������ �� float-������� 
				inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; }

				inline bool  operator == (const vec2_s & v) const {	return (x == v.x && y == v.y  ); }
				inline bool  operator != (const vec2_s & v) const {	return (x != v.x || y != v.y  ); }

				//inline bool  operator <  (const vec2_s & v) const { return (x < v.x && y < v.y );    }
				//inline bool  operator <= (const vec2_s & v) const {	return (x <= v.x && y <= v.y);   }
				//inline bool  operator >  (const vec2_s & v) const {	return (x > v.x && y > v.y);     }
				//inline bool  operator >= (const vec2_s & v) const {	return (x >= v.x && y >= v.y );  }

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

				inline float distance(const vec2_s& point) const 
				{
					return  sqrt( distanceSq( point ) );  
				}

				inline float distanceSq(const vec2_s& point) const 
				{ 
					return vec2_s(*this - point).lengthSq();  
				}


				inline vec2_s&   normalize() 
				{ 
					if( (0.0f==x) && (0.0f==y) ) // < ��� ����� ������. nan
						return *this; 
					register float fl=length(); 
					x/=fl; 
					y/=fl;  
					return *this; 
				}

				//! \brief  ������� ��������������
				inline vec2_s normalized() const 
				{
				 vec2_s res(*this);
				 res.normalize();
				 return res;
				}

				inline float  dot(const vec2_s& v) const { return x*v.x + y*v.y; }

 
				//! \brief Returns the z-component by taking the cross product of two 2D vectors.  ���������!  
				float ccw(const vec2_s& v) const ;


				//! \brief  ������������� (�������� ����� �����������).
				inline vec2_s& inverse() 
				{ 
					x=-x; 
					y=-y; 
					return *this; 
				}

				//! \brief ������� ������, � ���������������� �������
				inline vec2_s  inverted() const 
				{
					return vec2_s ( -x, -y ); 
				}
 		

				inline float     getMaxLength () const {  if( fabs (x) >= fabs (y) ) return x; else return y;   }

  			   // inline vec2_s&   invert() {x=-x; y=-y;  return *this; }

				inline vec2_s    lerp(const vec2_s& v, const float k) const
				{
					vec2_s r;
					r.x = x + (v.x - x) * k;
					r.y = y + (v.y - y) * k;
					return r;			
				};

				

				//! \brief  �������� ����������� ����������   
				inline float minVal() const { if(x<y) return x;   return y; }
				//! \brief  �������� ������������ ����������   
				inline float maxVal() const { if(x>y) return x;   return y; }

				//! \brief  �������� ��� ������� v1 � v2 � ��������� ����������� 
				inline vec2_s& minimize(const vec2_s& v1, const vec2_s& v2) 
				{
					if (v1.x < v2.x) x = v1.x; else  x = v2.x;
					if (v1.y < v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  �������� ������ v � ����������� �������� � ��������� �����������  
				inline vec2_s& minimize(const vec2_s& v) 
				{
					if (v.x < x) x = v.x;
					if (v.y < y) y = v.y;
					return *this;
				}

				//! \brief  �������� ��� ������� v1 � v2 � ��������� ������������  
				inline vec2_s& maximize(const vec2_s& v1, const vec2_s& v2) 
				{
					if (v1.x > v2.x) x = v1.x; else  x = v2.x;
					if (v1.y > v2.y) y = v1.y; else  y = v2.y;
					return *this;
				}

				//! \brief  �������� ������ v � ����������� �������� � ��������� ������������ 
				inline vec2_s& maximize(const vec2_s& v) 
				{
					if (v.x > x) x = v.x;
					if (v.y > y) y = v.y;
					return *this;
				}

				//! \brief ������� ����������� ������ ����� this � v
				inline vec2_s minimized(const vec2_s& v) const { vec2_s r; r.minimize(*this, v); return r; };
				//! \brief ������� ������������ ������ ����� this � v
				inline vec2_s maximized(const vec2_s& v) const { vec2_s r; r.maximize(*this, v); return r; };


				//! \brief  ��������� ���. ���������� �������� ���������. 
				inline float minAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax; if(ay<res) res=ay; return res; }
				//! \brief  ��������� ����. ���������� �������� ��������� 
				inline float maxAbsVal() const { float ax=abs(x); float ay=abs(y); float res=ax;  if(ay>res) res=ay; return res; }


				//! \brief  ���������� �����, ���������� 
				inline float minval() const { if(x<y) return x; return y;	}
				//! \brief  ����������. ���� ���������� 
				inline float maxval() const { if(x>y) return x; return y;	}


				//! \brief  ��������� �������� � �������� vmin � vmax
				inline void clump(const vec2_s& vmin, const vec2_s& vmax) 
				{
					if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
					if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				}

			//! \brief ������� ������� ����� ����� this � point
			inline vec2_s middle(const vec2_s& point) const 
			{
			    vec2_s res;
			      res.x = ( x + point.x ) / 2.0f;
			      res.y = ( y + point.y ) / 2.0f;			
			         return res;
			}


				//!  \brief   ����� true ���� ��� ���������� �������������.
				inline bool isPositive() const {  return ( (x>=0.0f) && (y>=0.0f) );  }


				//! \brief     ����� �������� �� �������.
				inline void print() const { printf(" %f %f ", x, y); }


 
			};



		/** \brief ������� 3d-������.  ��������� ��������� �� �������� */		
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

			//! \brief ������������ �� float-������� 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; }
				 
			inline bool  operator == (const vec3_s &v) const { return (x == v.x && y == v.y && z == v.z ); }
			inline bool  operator != (const vec3_s &v) const { return (x != v.x || y != v.y || z != v.z ); }

			//inline bool  operator <  (const vec3_s &v) const {	return (x <  v.x && y <  v.y && z <  v.z ); }
			//inline bool  operator <= (const vec3_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z ); }
			//inline bool  operator >  (const vec3_s &v) const {	return (x >  v.x && y >  v.y && z >  v.z ); }
			//inline bool  operator >= (const vec3_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z ); }

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




#ifdef _D3D9_H_
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=x; r.y=y; r.z=z; return r;  }
			inline void operator = (const D3DVECTOR& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef _D3D9_H_

#ifdef GB_D3DX9
			inline operator D3DXVECTOR3*() { return (D3DXVECTOR3*)&x; }
			inline operator const D3DXVECTOR3*() const { return (D3DXVECTOR3*)&x; }
			inline operator D3DXVECTOR3() const  {  return D3DXVECTOR3(x,y,z); }
		   	inline void operator = (const D3DXVECTOR3& v) {	x=v.x; y=v.y; z=v.z; }
#endif // #ifdef GB_D3DX9

			void operator = (const gb::fmath::geom3d::Point3& pnt);


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

			//! \brief  ������������� 
			inline vec3_s&   normalize ()	  
			{ 
				if( (0.0f==x) && (0.0f==y) && (0.0f==z) ) // < ��� ����� ������. nan
					   return *this; 

				register float fl=length(); 
				x/=fl; 
				y/=fl; 
				z/=fl; 
				return *this; 
			}

			//! \brief  ������� ��������������
			inline vec3_s    normalized() const { vec3_s r=*this; r.normalize(); return r; }

			//! \brief  ��������� � ������� ���������� ����� �������  this � point.
			inline float distance(const vec3_s& point)   const { return  sqrt( distanceSq(point) );  }
			//! \brief  ��������� � ������� ������� ���������� ����� �������  this � point.
			inline float distanceSq(const vec3_s& point) const { return vec3_s(*this-point).lengthSq() ;  }
 

			//! \brief �������� ���������� ���������� �� ������ ����������
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

			//! \brief     �������� ����������� ����������
			inline float minval() const   
			{ 
				float ret = x;
				if (y < ret) ret = y;
				if (z < ret) ret = z;
				return ret;
			};

			//! \brief     �������� ������������ ����������
			inline float maxval()  const
			{  
				float ret = x;
				if (ret < y) ret = y;
				if (ret < z) ret = z;
				return ret;
			}



			//* \brief   ������. ���. ���������� �� ���������.
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

			//* \brief   ������. ����. ���������� �� ���������.
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



			//! \brief  �������� ��� ������� v1 � v2 � ��������� ������������ 
			vec3_s& maximize(const vec3_s& v1, const vec3_s& v2) 
			{
				if (v1.x > v2.x) x = v1.x; else x = v2.x;
				if (v1.y > v2.y) y = v1.y; else y = v2.y;
				if (v1.z > v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  �������� ������ v � ����������� �������� � ��������� ������������
			vec3_s& maximize(const vec3_s& v)
			{
				if (v.x > x) x = v.x; 
				if (v.y > y) y = v.y; 
				if (v.z > z) z = v.z; 
				return *this;
			}

			//! \brief  �������� ��� ������� v1 � v2 � ��������� ����������� 
			vec3_s& minimize(const vec3_s& v1, const vec3_s& v2) 
			{
				if (v1.x < v2.x) x = v1.x; else x = v2.x;
				if (v1.y < v2.y) y = v1.y; else y = v2.y;
				if (v1.z < v2.z) z = v1.z; else z = v2.z;
				return *this;
			}

			//! \brief  �������� ������ v � ����������� �������� � ��������� �����������  
			vec3_s& minimize(const vec3_s& v) 
			{
				if (v.x < x) x = v.x;
				if (v.y < y) y = v.y;
				if (v.z < z) z = v.z;
				return *this;
			}

			//! \brief ������� ����������� ������ ����� this � v
			inline vec3_s minimized(const vec3_s& v) const { vec3_s r; r.minimize(*this, v); return r; };
			//! \brief ������� ������������ ������ ����� this � v
			inline vec3_s maximized(const vec3_s& v) const { vec3_s r; r.maximize(*this, v); return r; };



			//! \brief  ����� �������� � ��������� ����� vmin � vmax
			inline vec3_s& clump(const vec3_s& vmin, const vec3_s& vmax) 
			{
				if( x < vmin.x) x=vmin.x;  if(x > vmax.x) x=vmax.x;
				if( y < vmin.y) y=vmin.y;  if(y > vmax.y) y=vmax.y;
				if( z < vmin.z) z=vmin.z;  if(z > vmax.z) z=vmax.z;
				  return *this;
			}

			//! \brief ������� ������� ����� ����� this � point
			inline vec3_s middle(const vec3_s& point) const 
			{
			    vec3_s res;
			      res.x = ( x + point.x ) / 2.0f;
			      res.y = ( y + point.y ) / 2.0f;			
			      res.z = ( z + point.z ) / 2.0f;
			         return res;
			}

			//! \brief  ����� true ���� ��� ���������� �������������.
			inline bool isPositive() const {  return ( (x>=0.0f) && (y>=0.0f) && (z>=0.0f) );	}

			//! \brief ���������������� �� ������� m   ��� ����������. ���������!
			vec3_s&  transformCoord(const mat44_s& m);
			//! \brief ���������������� �� ������� m   ��� �������. ���������!
			vec3_s&  transformNormal(const mat44_s& m);
				
			 // TODO: 
			    // void transformCoordArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 
			    // void transformNormalArray(float* pfOut, int strideOut, const float* pvInput, int strideInput,  const M44& m, const int num) {...} 


			/** \brief  �������� ������� �� ������������ "����������" �� �����. 
			     ���������� ��������������� �������� ������. ���������!	*/
			vec3_s project ( 
				const proj::ViewportZ& vp,   //<  ������� ������
				const  mat44_s& Proj, //<	������� ��������
				const  mat44_s& View, //<	������� ����
				const  mat44_s& World //<	������� ���������
				)  const; 



			/** \brief ����������. ������� �� �������� ��������� � ��������������� ���������� 
			���������� ����������� ������ . ���������! */
			vec3_s  unproject( 
				const proj::ViewportZ& vp,    //<  ������� ������
				const  mat44_s& Proj,	//<	������� ��������
				const  mat44_s& View,	//<	������� ����
				const  mat44_s& World	//<	������� ���������
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


			//! \brief ����� �������� �� �������
			inline void print() const 
			{ 
				printf("%f  %f  %f ", x, y, z); 
			}

		}; // end vec3_s
		

		/** \brief ������� 4d-������. ��������� ��������� �� ��������   */		
		struct vec4_s  {

		    union {
			
				struct {
				   float x, y, z, w;
				};

				float floats [4];
			};

			inline vec4_s() {};

			inline vec4_s(const vec4_s& v)      { x=v.x;  y=v.y; z=v.z; w=v.w;  };
//			inline vec4_s(const vec4_s* v)      { x=v->x;  y=v->y; z=v->z; w=v->w;  };

			inline vec4_s(const vec3_s& v, float _w)  { x=v.x;  y=v.y; z=v.z; w=_w;  };

			inline vec4_s(const vec2_s& v, float _z, float _w) {x=v.x; y=v.y; z=_z; w=_w; }

			inline vec4_s(float _x, float _y, float _z, float _w)   { x=_x;   y=_y; z=_z; w=_w;  }
			inline vec4_s(int   _x, int   _y, int   _z, int   _w)   { x=(float)_x;   y=(float)_y;  z=(float)_z; w=(float)_w;}

			//! \brief ������������ �� float-������� 
			inline void operator = (const float* pf) {x=pf[0]; y=pf[1]; z=pf[2]; w=pf[3]; }
 
					 
			inline bool  operator == (const vec4_s &v) const {	return (x == v.x && y == v.y && z == v.z && w == v.w); }
			inline bool  operator != (const vec4_s &v) const {	return (x != v.x || y != v.y || z != v.z || w != v.w); }

			//inline bool  operator <  (const vec4_s &v) const {	return (x < v.x && y < v.y && z < v.z && w < v.w); }
			//inline bool  operator <= (const vec4_s &v) const {	return (x <= v.x && y <= v.y && z <= v.z && w <= v.w); }
			//inline bool  operator >  (const vec4_s &v) const {	return (x > v.x && y > v.y && z > v.z && w > v.w); }
			//inline bool  operator >= (const vec4_s &v) const {	return (x >= v.x && y >= v.y && z >= v.z && w >= v.w); }

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
			
			//! \brief �������� ��� ����������
		    inline void setzero() {x=y=z=w=0.0f; }
			//! ��������� ����� �� ��� ���������� ����
			inline bool empty() const { return ( (x==0.0f) && (y==0.0f) && (z==0.0f) && (w==0.0f) ); }

			inline vec4_s& set    (float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; return *this; }
 
			//! \brief  ��� �� ���������� ������� �� ��������.
			inline bool isZero(float epsilon) const
			{
				return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
			}

			//! \brief  �������� ������
			inline float length () const {	return (float)sqrt( x*x + y*y + z*z + w*w );	}
			//! \brief  �������� ������� ������
			inline float lengthSq() const {	 return (x*x + y*y + z*z + w*w);  }

			//! \brief   ������� ��������� ������������ � �������� v
			inline float   dot (const vec4_s& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

			
#pragma message ("KS777: MATH::VEC4 >> NEED CHECK CROSS METHOD !!!"  __FILE__)
			//! \brief �������� ��������� (������������)  ������������ � �������� v.
			inline vec4_s  cross ( const vec4_s & v) const
			{
				  vec4_s r;
				r.x = ( z * v.w - w * v.z) * y + ( w * v.y - y * v.w) * z + ( y * v.z - z * v.y) * w;
				r.y = ( w * v.z - z * v.w) * x + ( x * v.w - w * v.x) * z + ( z * v.x - x * v.z) * w;
				r.z = ( y * v.w - w * v.y) * x + ( w * v.x - x * v.w) * y + ( x * v.y - y * v.x) * w;
				r.w = ( z * v.y - y * v.z) * x + ( x * v.z - z * v.x) * y + ( y * v.x - x * v.y) * z;
				  return r;
			}


			// ����������� !!!!
			void cross( const vec4_s& U, const vec4_s& V, const vec4_s& W )   
			{
				assert(false && "bad code !");

				float a = V.x*W.y - V.y*W.x;
				float b = V.x*W.z - V.z*W.x;
				float c = V.x*W.w - V.w*W.x;
				float d = V.y*W.z - V.z*W.y;
				float e = V.y*W.w - V.w*W.y;
				float f = V.z*W.w - V.w*W.z;

				vec4_s Out;
				Out.x = f*U.y - e*U.z + d*U.w ;
				Out.y = f*U.x + c*U.z - b*U.w ; // no valid
				Out.z = e*U.x - c*U.y + a*U.w ;
				Out.w = d*U.x + b*U.y - a*U.z ; // no valid


				*this = Out;
			}

			//! \brief  �������������.
			inline vec4_s&   invert() {  x=-x; y=-y; z=-z; w=-w; return *this; };
			//! \brief  ������� ��������������.
			inline vec4_s    inverted() const 
			{
				vec4_s res = *this;
				res.invert();
				return res;
			}

			//! \brief  ������� ������ �� �������� ������������ ����� this � v  �� ������������ k
			inline vec4_s    lerp(const vec4_s& v, const float k) 
			{
				vec4_s r;
				r.x = x + (v.x - x) * k;
				r.y = y + (v.y - y) * k;
				r.z = z + (v.z - z) * k;
				r.w = w + (v.w - w) * k;
				return r;			
			};



	//! \brief  �������� ����������� ����������.
	inline float minval() const 
	{ 	  
	   float res = x;
	   if(y<res) res=y;
	   if(z<res) res=z;
	   if(w<res) res=w;
	      return res;
	};

	//! \brief �������� ������������ ����������.
	inline float maxval() const
	{   
	   float res = x;
	   if(res<y) res=y;
	   if(res<z) res=z;
	   if(res<w) res=w;
	       return res;
	};	
 
	/** \brief  ������. ����������� ���������� ����������.  */
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

	/** \brief  ������. ������������ ���������� ����������.  */
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


	//! \brief ��������� ��������� �������� � ��������� ����� vmin � vmax
	inline void clump(const vec4_s& vmin, const vec4_s& vmax) 
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



	//! \brief ����� �������� �� �������
	inline void print() const { printf(" %f  %f  %f  %f ", x, y, z, w); };

		}; 
		// end vec4_s

		//------------------------------------------------------------------








 }
 // end namespace fmath

}
// end namespace gb


// end file