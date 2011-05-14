/** \file
 \brief  ����������� ���������� .


*/

#pragma once

#ifndef __GB_FMATH_H__
   #error �� ��������� ���� ����. ���������:   #include <gb/fmath/math.h>  
#endif

namespace gb 
{

  namespace fmath
  {

//----------------------------------------------------------------------


	//! \brief �����������  ����������.
	class Quaternion   {
	public:

		union {
			struct { float x, y, z, w;  };
			float floats [4];
		};

		inline Quaternion() { x=y=z=0.0f; w=1.0f; }
		inline Quaternion(const Quaternion& q)
		{ 
			x=q.x; y=q.y; z=q.z; w=q.w; 
			normalize();
		}

		inline Quaternion(float _x, float _y, float _z, float _w) 
		{ 
			x=_x; y=_y; z=_z; w=_w; 
			normalize();
		}

		inline Quaternion(const float* pfArray)
		{
			 x = pfArray[0];
			 y = pfArray[1];
			 z = pfArray[2];
			 w = pfArray[3];
		}

		//-----------------------------------------------------------------
		//                     ���������
		//-----------------------------------------------------------------

		inline operator         float*()         { return &x; };
		inline operator const   float*() const   { return &x; };


		inline bool operator == (const Quaternion &q) const
		{ 
			return	x == q.x && y == q.y && z == q.z && w == q.w ||
				x == -q.x && y == -q.y && z == -q.z && w == -q.w;
		}

		inline bool operator != (const Quaternion &q) const
		{
			return	!(x == q.x && y == q.y && z == q.z && w == q.w ||
				x == -q.x && y == -q.y && z == -q.z && w == -q.w);
		}

		inline Quaternion&  operator += ( const Quaternion& q )
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		inline Quaternion& operator -= ( const Quaternion& q )
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}
 
		inline Quaternion& operator *= ( const float f )
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return *this;
		}

		inline Quaternion& operator /= ( const float f )
		{
			const float  fInverse = 1.0f/f;
			x *= fInverse;
			y *= fInverse;
			z *= fInverse;
			w *= fInverse;
			return *this;
		}
 
		inline Quaternion operator + () const
		{
			return *this;
		}

		inline Quaternion operator - () const
		{
			return Quaternion(-x, -y, -z, -w);
		}

		inline Quaternion operator + ( const Quaternion& q ) const
		{
			return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		inline Quaternion operator - ( const Quaternion& q ) const
		{
			return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
		}
 

		//!   ���������
		inline Quaternion operator * ( const Quaternion &q ) const 
		{
			Quaternion res;
			res.x = w*q.x + x*q.w + z*q.y - y*q.z;
			res.y = w*q.y + y*q.w + x*q.z - z*q.x;
			res.z = w*q.z + z*q.w + y*q.x - x*q.y;

			res.w = w*q.w - x*q.x - y*q.y - z*q.z;
			return res;
		}
 
		inline Quaternion operator * ( const float f ) const
		{
			return Quaternion( x*f, y*f, z*f, w*f );
		}


		inline Quaternion operator / ( const float f ) const
		{
			const float fInverse = 1.0f / f;
			return Quaternion(x * fInverse, y * fInverse, z * fInverse, w * fInverse);
		}
 
		inline Quaternion&   operator *= (const Quaternion &q) 
		{ 
			Quaternion r(*this); 
			*this=r*q; 
			return *this;   
		} 
 

#ifdef __D3DX9MATH_H__

		inline operator D3DXQUATERNION*()             { return (D3DXQUATERNION*)&x; }
		inline operator const D3DXQUATERNION*() const { return (D3DXQUATERNION*)&x; }
		inline operator D3DXQUATERNION() { return D3DXQUATERNION( x , y , z , w ); }
		inline void operator = (const D3DXQUATERNION& q) { x=q.x; y=q.y; z=q.z; w=q.w; }

#endif //#ifdef __D3DX9MATH_H__



		//----------------------------------------------------------------//
		//                           ������		        	              //
		//----------------------------------------------------------------//
 
		// \brief  ��������� ��������  ����� �������������
		inline void set(float _x, float _y, float _z, float _w)
		{
			x=_x; y=_y; z=_z; w=_w;
			normalize();
		}

		// \brief �������� � ����������
		inline void setIdentity() { x=y=z=0.0f; w=1.0f; }
		// \brief �������� � ����������
		inline void reset() { setIdentity(); }

		// \brief �������� �� ���������� ��������
		inline bool isIdentity(float eps = 0.0f) const
		{ 
			return abs(x) <= eps && abs(y) <= eps && abs(z) <= eps && abs(w) - 1.0f <= eps;
		}

		//! \brief  �������� ������
		inline float length() const	{ return sqrt(x*x + y*y + z*z + w*w); }
		//! \brief  �������� ������� ������
		inline float lengthSq() const {	return   (x*x + y*y + z*z + w*w); }

		// \brief   �������������   ���������!
		inline Quaternion&  normalize()
		{
			const float len = length();
			if (len > 1e-6) 
			{
				x /= len;
				y /= len;
				z /= len;
				w /= len;
			}
			return *this;
		}

		// //! \brief �������� �������������� ����������
		// inline Quaternion getNormalized() const { Quaternion r = *this; r.normalize(); return r;  }

		//! \brief  ������� ����������� ����������   ���������
		inline Quaternion conjugate(const Quaternion &q) const
		{
			  Quaternion res;
			    res.w =  q.w;
			    res.x = -q.x;
			    res.y = -q.y;
			    res.z = -q.z;
			  return  res;
		}

		//! \brief ������� ��������� ������������ 
		inline float dot(const Quaternion &g) const 
		{
			return w*g.w + x*g.x + y*g.y + z*g.z;
		}

		//! \brief return  exponentiation
		Quaternion  pow(const Quaternion &q, float exponent) const;

		//! \brief  �������������.  ��������� !
		void inverse () 
		{
			const float fNorm = x*x + y*y + z*z + w*w;
			if ( fNorm > 0.0 )
			{
				const float fin = 1.0f/fNorm;
				w =   w * fin;
				x = - x * fin;
				y = - y * fin;
				z = - z * fin;
			}
			else
			{

			}
		}

		//! \brief  ������� �������������� .
		inline Quaternion inversed() const 
		{
		  Quaternion res(*this);
		  res.inverse(); 
		  return res;
		}


 

		////*  natural log
		//Quaternion  logn () const
		//{
		//	Quaternion res;

		//	//		A unit quaternion, is defined by:
		//	//Q == (cos(theta), sin(theta) * v) where |v| = 1
		//	//The natural logarithm of Q is, ln(Q) = (0, theta * v)


		//	//????
		//		return res;

		//}



		// todo !!!!!!!!!!!!!!!!!!!
	//	Quaternion& setFromRotationMatrix(const  mat44& m);





#ifdef __D3DX9MATH_H__


		//! \brief ������� ��� d3dx  return calculates the natural logarithm.
		Quaternion ln(const Quaternion& q)
		{
		//A unit quaternion, is defined by:
		//Q == (cos(theta), sin(theta) * v) where |v| = 1
		//The natural logarithm of Q is, ln(Q) = (0, theta * v)
             Quaternion res;
			D3DXQuaternionLn(res , *this );
			return res;
		}



		// todo ������� ��� d3dx
		Quaternion  exp(const Quaternion& qu) const 
		{
			//Given a pure quaternion defined by:
			// q = (0, theta * v); 
			//This method calculates the exponential result.
			//exp(Q) = (cos(theta), sin(theta) * v)
			Quaternion res;
			D3DXQuaternionExp(  res , qu  );
			return res;
		};


		// todo ������� ��� d3dx
	   Quaternion& setBaryCentric(const Quaternion& q1,	const Quaternion& q2,const Quaternion& q3, float f,	float g	)
	   {
		   D3DXQuaternionBaryCentric( *this, q1, q2, q3, f,	g);
           return *this;
	   };


      // todo ������� ��� d3dx
      Quaternion& setSquad(const Quaternion& q1, const Quaternion& a,  const Quaternion& b,  const Quaternion& c, float t )
	  {
		  D3DXQuaternionSquad( *this, q1, a, b, c, t);
		  return *this;
	  };


      static void  squadSetup( Quaternion& AOut, Quaternion& BOut, Quaternion& COut,
	             const Quaternion& Q0, const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3 )
	   {
		     D3DXQuaternionSquadSetup( AOut,  BOut, COut, Q0,  Q1, Q2 , Q3  );
	   };



#endif __D3DX9MATH_H__



		/**  ������� ��������� �������������� � d3dx  
		-------------------------------------
		0.606882  0.275320  0.666870  0.333432
		-------------------------------------
		0.610759  0.206986  0.689953  0.328778
		*/
	    Quaternion slerp(const Quaternion&q, float t);

		//inline Quaternion slerp(const Quaternion &q, float t) const { Quaternion r = slerp(*this, q, t); return r;  };


		inline float getRotationAngle() const 
		{
			// Compute the half angle.  Remember that w = cos(theta / 2)
			float thetaOver2 = scalar::safeAcos(w);
			// Return the rotation angle
			return thetaOver2 * 2.0f;
		}

		 vec3  getRotationAxis() const;

		geom3d::AxiesAngle getRotationAxiesAngle() const;

		inline geom3d::AxiesAngle toAxiesAngle() const ;


		inline Quaternion& setRotationX(float theta) {

			// Compute the half angle
			const float k = theta*0.5f;

			// Set the values
			w = cos(k);
			x = sin(k);
			y = 0.0f;
			z = 0.0f;
			return *this;
		}

		inline Quaternion&	setRotationY(float theta) 
		{
			const float	k =   theta*0.5f;
			w = cos(k);
			x = 0.0f;
			y = sin(k);
			z = 0.0f;
			return *this;
		}

		inline Quaternion&  setRotationZ(float theta) 
		{
			float	k = theta*0.5f;
			w = cos(k);
			x = 0.0f;
			y = 0.0f;
			z = sin(k);
			return *this;
		}


		Quaternion&         setRotationAxis(const  vec3 &axis, float theta) ;


		Quaternion&  setRotationAxis(const geom3d::AxiesAngle& aa) ;


		//! \brief  ��������� ���������� �� ����� ������
		void setRotationYawPitchRoll( float yaw, float pitch, float roll)
		{
			float	sp, sb, sh;
			float	cp, cb, ch;
			gb::fmath::scalar::sincos(pitch * 0.5f , sp , cp  ); 
			gb::fmath::scalar::sincos(roll * 0.5f  , sb , cb  );
			gb::fmath::scalar::sincos(yaw * 0.5f   , sh , ch  );
			  x =  -(-ch*sp*cb - sh*cp*sb);
			  y =  -(ch*sp*sb  - sh*cb*cp);
			  z =  -(sh*sp*cb  - ch*cp*sb);
			  w =  ch*cp*cb + sh*sp*sb;
		}


		//! \brief  ��������� ���������� �� ����� ������  
		void setRotationEulersAngles(const geom3d::EulerAngles& ea);

		//! \brief ���������� �� ������� ��������
		Quaternion&  setRotationMatrix(const  mat44& m);
 
 /*****************************
		inline void  invert() 
		{
			*this = conjugate(*this);
			*this /= lengthSq();
		}

		inline Quaternion inverse() const 
		{
			return conjugate(*this) / lengthSq();
		}
*******************************/


		//! \brief  ����� �� �������
		void print() const { printf("%f  %f  %f  %f" , x , y, z, w ); }

	};



//----------------------------------------------------------------------

  } // end namespace fmath
} // end namespace gb
// end file