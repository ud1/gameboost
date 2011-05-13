/** \file
 \brief ������� 2x2, 3x3, 4x4.  

*/ 



#pragma once

#ifndef __GB_FMATH_H__
  #error �� ��������� ���� ����. ���������:   #include <gb/fmath/math.h>  
#endif

namespace gb 
{

 namespace fmath
 {




 
		//! \brief ������� 2x2
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

			//! \brief ��������� �������� �� �������
			inline void operator = (const float* pfArray)
			{
				_11 = pfArray[0];
				_12 = pfArray[1];
				_21 = pfArray[2];
				_22 = pfArray[3];
			}

			/** \brief   � ������� ��������� ���������� f   ��������� ��������.*/
			inline mat22_s&  operator =  ( float f) { 	floats [0][1] = floats [1][0] = 0.0; floats [0][0] = floats [1][1] = f; };

	        /**	 \brief ��������� ����� ���� ��������� �������	*/
			inline mat22_s operator - () const { mat22_s r=*this; r._11=-r._11; r._12=-r._12; r._21=-r._21; r._22=-r._22; return r; };

 
			/** \brief  �������������� ��������   (this = this + m) */
			inline mat22_s&  operator += ( const mat22_s& m)
			{
				floats [0][0] += m.floats [0][0];
				floats [0][1] += m.floats [0][1];
				floats [1][0] += m.floats [1][0];
				floats [1][1] += m.floats [1][1];
				return *this;
			};

			/** \brief  �������������� ���������� (this = this - m) */
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

			/** \brief  �������������� ��������� (this = this * m) */            
			inline mat22_s&  operator *= ( float f)
			{
				floats [0][0] *= f;
				floats [0][1] *= f;
				floats [1][0] *= f;
				floats [1][1] *= f;
				return *this;
			};

			/** \brief  �������������� ������� (this = this / m) */
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




		//! \brief ������� 3x3 
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

		    /**  \brief ��������� ����� ���� ��������� �������	*/
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

			/**	 \brief ������ � ������� ������� �� �������. ��������� !! */
	        inline const vec3_s operator [] ( unsigned int index ) const
	        {
		       assert( index <= 2 );
		       return reinterpret_cast<const vec3_s*>(this)[index];
	        }

			/**	 \brief �������������� � ������� 2x2 */
			inline operator mat22_s()
			{
				return mat22_s( _11, _12,
					            _21, _22 );
			}

			//! \brief  �������� ��� ��������
			inline void setzero() { _11=_12=_13=_21=_22=_23=_31=_32=_33=0.0f; };

			//! \brief �������� � ����������
			inline void setIdentity() {
				_11=1.0f; _12=0.0f; _13=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f;
				_31=0.0f; _32=0.0f; _33=1.0f;
		    };

			//! \brief �������� � ����������
			inline void reset() { setIdentity(); }

			 //! \brief  ��������������� ������� 
			inline mat33_s&   transpone() 
			{ 
				 register float t;
			    t=_12;  _12=_21; _21=t;
			    t=_13;  _13=_31; _31=t;
			    t=_23;  _23=_32; _32=t; 
				  return *this;
			};

			//! \brief    ������� ���������������� �������
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


			//! \brief  ����� �������� �� �������
			inline void print() const 
			{
			 printf("%f  %f  %f  \n%f  %f  %f  \n%f  %f  %f", 
				 _11, _12, _13, 
				 _21, _22, _23, 
				 _31, _32, _33 );
			}
 
		
		};
 
		

		//! \brief ������� 4x4. 
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

			//! \brief �������� � ���������� � ��������� ������� ��������� ��������� a (������ 1.0f)
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

			inline mat44_s(const float* pfArray)
			{
				*this = pfArray;
			}


			inline operator  const float*() const  { return &_11; }
			inline operator        float*()        { return &_11; }

#ifdef _D3D9_H_
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
#endif //  #ifdef _D3D9_H_
 


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


			inline void operator  = (const float* pfArray)
			{
				_11 = pfArray[ 0];
				_12 = pfArray[ 1];
				_13 = pfArray[ 2];
				_14 = pfArray[ 3];

				_21 = pfArray[ 4];
				_22 = pfArray[ 5];
				_23 = pfArray[ 6];
				_24 = pfArray[ 7];

				_31 = pfArray[ 8];
				_32 = pfArray[ 9];
				_33 = pfArray[10];
				_34 = pfArray[11];

				_41 = pfArray[12];
				_42 = pfArray[13];
				_43 = pfArray[14];
				_44 = pfArray[15];

			}
 


			/**    \brief ������� ���������    */
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





			/**     \brief ������� ��������� � ����������     */
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


			
 
			/**   \brief �������� ����� �����������  */
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


 
			/**   \brief ������������ �������� ������  */
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

			/**   \brief ������������ ��������� ������  */
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


			/**   \brief ��������� ���� ��������� ������� �� ������   */
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



			/**  \brief ������� ���� ��������� ������� �� ������  */
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

 
			// ��������� !
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


			/**    \brief ��������� ������� �� ������� .  ���������!  */
			inline vec4_s operator * ( const vec4_s& v ) const 
			{
				vec4_s r;
				r.x =  _11 * v.x +  _21 * v.y +  _31 * v.z +  _41 * v.w;
				r.y =  _12 * v.x +  _22 * v.y +  _32 * v.z +  _42 * v.w;
				r.z =  _13 * v.x +  _23 * v.y +  _33 * v.z +  _43 * v.w;
				r.w =  _14 * v.x +  _24 * v.y +  _34 * v.z +  _44 * v.w;
				  return r;
			}
 

			//! \brief ��������� ���� ���������.
			inline void       setzero() { memset(&_11, 0, sizeof(mat44_s)  ); }

			//! \brief ���������� � ����������
			inline mat44_s&   setIdentity() 
			{
				_11=1.0f; _12=0.0f; _13=0.0f; _14=0.0f;
				_21=0.0f; _22=1.0f; _23=0.0f; _24=0.0f; 
				_31=0.0f; _32=0.0f; _33=1.0f; _34=0.0f;  
				_41=0.0f; _42=0.0f; _43=0.0f; _44=1.0f; 
				 return *this;
	        }

			//! \brief ���������� � ����������
			inline mat44_s& reset() { setIdentity(); return *this; }

			//! \brief ����������������. (��������� ��������� �� ������� ���������)  ���������!
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

			//!  ����������-��������������   ��������� � ������� ���������������� �������� .
			mat44_s transponed() const 
			{
				mat44_s res = *this;
				res.transpone();
				return res;
			}

			/** \brief ��������� � ������� ���������������� �������� .  */
			inline mat44_s getTransponed() const { mat44_s r=*this; r.transpone(); return r; };

			/** \brief ��������� � ������� ������������.  */
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

			/** \brief ��������. ������� ���������� ���� �������� ����������. ���������. */
			mat44_s&  invert () throw();

			//! \brief ������� ��������������
			mat44_s inverted() const throw() 
			{
			  mat44_s res = *this;
			  res.invert(); 
			  return res;
			}


			vec4_s getRow(unsigned int index) const 
			{
				assert(index<4  && "invalid index" );
				return vec4_s( floats[index][0], floats[index][1], floats[index][2], floats[index][3] );
			}

			vec4_s setRow(unsigned int index, const vec4_s& row)   
			{
				assert(index<4  && "invalid index" );
				floats[index][0]=row.x; floats[index][1]=row.y; floats[index][2]=row.z; floats[index][3]=row.w;
			}
 
			vec4_s getColumn(unsigned int index) const 
			{
				assert( index<4 && "invalid index" );
				return vec4_s( floats[0][index], floats[1][index], floats[2][index], floats[3][index] );
			}

			void setColumn(unsigned int index, const vec4_s& col)
			{
				assert( index<4 && "invalid index" );
			    floats[0][index]=col.x; floats[1][index]=col.y; floats[2][index]=col.z; floats[3][index]=col.w;
			}

			//! \brief   �������� ������ ����������.
			inline vec3_s getTranslation() const
			{		  
				return vec3_s(floats[3][0], floats[3][1], floats[3][2]);
			}

			//-------------------------------------------------------------

			//! \brief  ��������� ������� �� ������ �������������. ���������!
			void decompose( vec3_s& scale, geom3d::Quaternion& rot, vec3_s& pos ) const;

			//-------------------------------------------------------------
 
			//! \brief ���������� ������� ��������� �� ��� X
			inline mat44_s& setMirrorX ()
			{
				setIdentity();
				floats  [0][0] = -1.0f;
				return *this;
			}

			//! \brief ���������� ������� ��������� �� ��� Y 
			inline mat44_s& setMirrorY ()
			{
				setIdentity();
				floats  [1][1] = -1.0f;
				return *this;
			}

			//! \brief ���������� ������� ��������� �� ��� Z
			inline mat44_s& setMirrorZ ()
			{
				setIdentity();
				floats [2][2] = -1.0f;
				return *this;
			}

		    //! \brief ���������� ������� ��������� �� ��������� plane.   ���������! 
			mat44_s& setReflection(const geom3d::plane_s& plane );


			//! \brief  ���������� ������� �������.  ��������� �����.   ���������!
			mat44_s&  setShadow(const vec4_s& Light, const geom3d::plane_s&Plane );

			//! \brief ���������� ������� �������� �� ��� X �� ���� angle . ���������!
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

			//! \brief ���������� ������� �������� �� ��� Y �� ���� angle . ���������!
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

			//! \brief ���������� ������� �������� �� ��� Z �� ���� angle . ���������!
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


			//! \brief ���������� ������� �������� �� ��� vAx �� ���� angle . ���������!
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


			//! \brief ���������� ������� �������� �� ��� �� �����������(axX,axY,axZ) �� ���� angle  . ���������!
			inline mat44_s&  setRotationAxis( float axX, float axY, float axZ, float angle )  
			{
				vec3_s vax;
				vax.x = axX; vax.y = axY; vax.z = axZ;
				vax.normalize();
				return setRotationAxis(  vax, angle);
			};

			//! \brief  ���������� ������� �������� �� ����� ����� (Yaw-Y, Pitch-X, Roll-Z). ���������!
			mat44_s& setRotationYawPitchRoll(float Yaw, float Pitch, float Roll)
			{
				mat44_s mrYaw, mrPitch, mrRoll;

				mrYaw.setRotationY(  Yaw );
				mrPitch.setRotationX(  Pitch );
				mrRoll.setRotationZ( Roll );

				*this =  mrRoll * mrPitch * mrYaw;
				return *this;
			};

			//! \brief ��������� ������� �������� �� �����������.  ���������!
			mat44_s& setRotationQuaternion(const geom3d::Quaternion& q) ;



			//! \brief ���������� ������� ������ (�������)  . ���������!
			inline mat44_s&  setTranslation( float x, float y, float z )  
			{
				setIdentity();
				_41 = x;   _42 = y;  _43 = z;  
				return *this;
			};

			//! \brief ���������� ������� ������ (�������)  ���������!
			inline mat44_s&  setTranslation( const vec3_s& vTransl) 
			{
				return  setTranslation(  vTransl.x, vTransl.y, vTransl.z);
			}
			
			//! \brief ���������� ������� ��������������� ���������!			
			inline mat44_s&  setScaling( float x, float y, float z)  
			{
				_11 = x;   _12=0.0f;   _13=0.0f;   _14=0.0f; 
				_21=0.0f;  _22 = y;    _23=0.0f;   _24=0.0f;	
				_31=0.0f;  _32=0.0f;   _33 = z;    _34=0.0f;	
				_41=0.0f;  _42=0.0f;   _43=0.0f;   _44 = 1.0f;
				return *this;
			}
			
			//! \brief ���������� ������� ���������������	 ���������!		
			inline mat44_s&  setScaling( const vec3_s& vScaling) 
			{
			  return setScaling( vScaling.x, vScaling.y, vScaling.z );
			}


			//! \brief ��������� ��� ������� ������������� 
			mat44_s& setTransformation(const vec3_s& vScale, 
								            const geom3d::Quaternion& qRotation,
								            const vec3_s& vTranslation);

			//! \brief ��������� ��� ������� ������������� 
			mat44_s& setWorldTransform(const geom3d::TransformData& t);


			//! \brief ���������� ��������������� ������������� ������������ �������. ���������.
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

			//! \brief ���������� ��������������� �������������� ������������ �������. ���������.
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


			//! \brief ���������� ��������������� �������   ��������� 
			inline void setOrthoOffCenterLH(float minX, float maxX, float minY, float maxY, float zn, float zf) 
			{
				_11 = 2.0f/(maxX-minX);         _12 = 0.0f,                     _13 = 0.0f,            _14 = 0.0f;
				_21 = 0.0f,                     _22 = 2.0f/(maxY-minY);         _23 = 0.0f,            _24 = 0.0f;
				_31 = 0.0f,                     _32 = 0.0f,                     _33 = 1.0f/(zf-zn);    _34 = 0.0f;
				_41 = (minX+maxX)/(minX-maxX);  _42 = (maxY+minY)/(minY-maxY);  _43 = zn/(zn-zf);      _44 = 1.0f;
			}
 

			//! \brief ���������� ��������������� �������  ���������   
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

			//! \brief ���������� ������������� ������������� �������. ���������.
			void setPerspectiveFovLH(float fov, float asp, float zn, float zf) 
			{
				const float yScale =   gb::fmath::scalar::cotan(fov/2.0f); //yScale = cot(fovY/2)
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

			//! \brief ���������� ������������� �������������� �������. ���������.
			void setPerspectiveFovRH(float fov, float asp, float zn, float zf)
			{
			 const float yScale =   gb::fmath::scalar::cotan(fov/2.0f);
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


			//! \brief ���������� ������������� ������������� ������� �� ������ � ������ .���������.
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

			//! \brief ���������� ������������� �������������� ������� �� ������ � ������. ���������.
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

			/** \brief ���������� ������������� ������� ����. ���������.  */
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


			/** \brief ���������� �������������� ������� ����. ���������.  */
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


			/** \brief ���������� ������������� ������� ����  �� ����������� ������� */
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

			/** \brief ���������� �������������� ������� ����  �� ����������� ������� */
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

			//! \brief  ������ ������  ������������ ������� � ������� � OpenGL 
			inline void glMul()  { glMultMatrixf( (GLfloat*)&_11  ); }

			//! \brief   ������ ������ �������� �������  � OpenGL 
			inline void glLoad() { glLoadMatrixf( (GLfloat*)&_11  ); }

			//! \brief ��������� �� ��������� OpenGL ������������ �������.
			inline void glGetProjection() 
			{    
				glGetFloatv(GL_PROJECTION_MATRIX, &_11);
			}

			//! \brief ��������� �� ��������� OpenGL ������-������� (WORLD X VIEW) �������.
			inline void glGetModelView()
			{
				glGetFloatv(GL_MODELVIEW_MATRIX, &_11);
			}

#endif // gb  OpenGL


#ifdef _D3D9_H_  // d3d9 device methods

			   //! \brief ���������� ������� � ���������� d3d9 ��� ������� ���� 
			   inline HRESULT makeDevice9TransfView(IDirect3DDevice9* pdevice) const 
			   {
				   return pdevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&_11 );
			   }

			   //! \brief ���������� ������� � ���������� d3d9 ��� ������� ��������  
			   inline HRESULT makeDevice9TransfProj(IDirect3DDevice9* pdevice) const
			   {
				   return pdevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_11 );
			   }

			   //! \brief ���������� ������� � ���������� d3d9 ��� ������� �������������  	
			   inline HRESULT makeDevice9TransfWorld(IDirect3DDevice9* pdevice) 
			   {
				   return pdevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&_11 );
			   }

			   //! \brief ���������� ������� � ������ ��� ������� ������������� �� ������� ���� trType 		
			   inline HRESULT makeDevice9Transf(IDirect3DDevice9* pdevice, D3DTRANSFORMSTATETYPE trType ) const 
			   {
				   return pdevice->SetTransform( trType, (D3DMATRIX*)&_11 );
			   }




			   //! \brief �������� �� ���������� d3d9   ������� ���� 
			   inline HRESULT readDevice9TransfView(IDirect3DDevice9* pdevice)   
			   {
				   return pdevice->GetTransform(D3DTS_VIEW, (D3DMATRIX*)&_11 );
			   }

			   //! \brief �������� �� ���������� ���������� d3d9   ������� ��������  
			   inline HRESULT readDevice9TransfProj(IDirect3DDevice9* pdevice)  
			   {
				   return pdevice->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_11 );
			   }

			   //! \brief �������� �� ���������� ���������� d3d9   ������� �������������  	
			   inline HRESULT readDevice9TransfWorld(IDirect3DDevice9* pdevice) 
			   {
				   return pdevice->GetTransform(D3DTS_WORLD, (D3DMATRIX*)&_11 );
			   }



#endif // _D3D9_H_



				//! \brief ����� �������� �� �������
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
 // end namespace fmath

}
// end namespace gb

// end file