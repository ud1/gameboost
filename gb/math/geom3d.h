/** \file geom3d.h
 \brief геометрия в 3d.
*
*  Наполнение на основе выложеного ребятами в папку бранч,   опенсурсных движков,   выуженого из гугла , своих наработок.
*
*
*/

#pragma once
#include <gb/math/scalar.h>
#include <gb/math/base.h>

#include <assert.h>



namespace gb 
{

  namespace math
  {
  
    /** \brief  геометрия в 3d  */
    namespace geom3d
	{


        /** \brief 3-х мерный размер */
		struct Size3d {

			union {
				float x;
				float width;
			};

			union {
				float y;
				float height;
			};

			union {
				float z;
				float depth;
			};


		};

        //! \brief  Сборка  ось повотора и угол
		struct AxiesAngle {

			base::vec3_s   axies; ///< ось повотора (должен быть нормализован)
			       float   angle; ///< угол поворота
		
		};
	
	
	//! \brief Сфера по центральной точке и радиусу. Она же Bounding sphere.
	class Sphere {
	public:
	  base::vec3_s  center;  ///<  центральная координата сферы.
	  float   radius;  ///<  радиус сферы.
	  
	  inline Sphere() {}
	  inline Sphere(const Sphere& s) {center=s.center; radius=s.radius; }
	  inline Sphere(const base::vec3_s& _center, const float _radius) {center=_center; radius=_radius; }	  
	  
	
	
	
	};
	
	
	//! \brief Бокс по мин. и макс. координатам. Axis aligned bounding box.
	class AABB {
	public:
	  base::vec3_s   min; ///< минимальная точка бокса
	  base::vec3_s   max; ///< максимальная точка бокса
	  
	  inline AABB() {}
	  inline AABB(const AABB& aabb) {min=aabb.min; max=aabb.max;}	  
	  inline AABB(const base::vec3_s& _min, const base::vec3_s& _max) { min=_min; max=_max;  }
	
	
	
	};
	
	
	//! \brief Луч в трёхмерном пространстве по позиции и направлению   
	class Ray {
	public:
	   base::vec3_s   orig; ///< точка центр луча
	   base::vec3_s   dir;  ///< направление луча ( должен быть нормализован)
	   
	   inline Ray() {}
	   inline Ray(const Ray& r) {orig=r.orig; dir=r.dir; }
	   inline Ray(const base::vec3_s& _orig, const base::vec3_s& _dir, bool bNeedNormalizeDir)
       {
	    orig=_orig;
	    dir=_dir;
	    if(bNeedNormalizeDir) dir.normalize();	   
	   }	   
	
	
	//! \brief  вывод на консоль.
    inline void print() const { orig.print(); printf("  "); dir.print(); printf("  "); };
	
	};
 

	/** \brief   Линия в трёхмерном пространстве по двум точкам  */
	class Line {
	public:
		base::vec3_s   src; 
		base::vec3_s   dest;

		inline Line() {};
		inline Line(const Line& l) {src=l.src; dest=l.dest; };	
		inline Line(const base::vec3_s& _src, const base::vec3_s& _dest) {src=_src; dest=_dest; };



      #if ( defined(GB_OPENGL) &&  defined(__GL_H__) )
		//! \brief Вывод вершин для OpenGl по старинке.
		inline void glVertex() { glVertex3f(src.x, src.y, src.z); glVertex3f(dest.x, dest.y, dest.z);   };
      #endif


		//! вывод на консоль.
		inline void print() const { src.print(); printf("  "); dest.print(); printf("  "); };

	}; // Line


	/** \brief  Углы Элера */
	class EulerAngles {
	public:
		float yaw;
		float pitch;
		float roll;

		inline EulerAngles() {};
		inline EulerAngles(const EulerAngles& ea  ) {yaw=ea.yaw; pitch=ea.pitch; roll=ea.roll; };
		inline EulerAngles(float fyaw, float fpitch, float froll) { yaw=fyaw;  pitch=fpitch;  roll=froll; };
 
	};	


	struct plane_s {
		union {

			//union {
			//	struct { float x, y, z; };
			//	float  d;
			//};

		   struct { float x , y , z , w ;   };

		   struct { float a , b , c , d ;   };
	       float floats [4];

		};

		inline plane_s& makeFromPointNormal(const base::vec3_s& point, const base::vec3_s& normal) 
		{
			a=normal.x;  
			b=normal.y;  
			c=normal.z;  
			d= -( normal.dot(point) ); 
			return *this;
		};


		inline plane_s& makeFromPoints(const base::vec3_s& p1, const base::vec3_s& p2, const base::vec3_s& p3 ) 
		{
			base::vec3_s vsub1 =   p1 - p2;    	 
			vsub1.normalize();
			base::vec3_s vsub2  = p1 - p3;	 
			vsub2.normalize();

			base::vec3_s nrml = vsub1.cross(vsub2);   
			nrml.normalize();
			makeFromPointNormal(p1, &nrml);
			return *this;
		}



	};


	class Plane : public plane_s {
	public:
		inline Plane() {};
		inline Plane(const Plane& p) {a=p.a; b=p.b; c=p.c; d=p.d; }

		inline Plane(float _a, float _b, float _c, float _d) 
		{
			a=_a;
			b=_b;
			c=_c;
			d=_d;
		}


		//---------------------------------------------------------------------
		//                        ОПЕРАТОРЫ
		//---------------------------------------------------------------------

		inline operator        float*()       { return &a; };
		inline operator const  float*() const { return &a; };


		inline bool operator == ( const Plane& p ) const
		{
			return a == p.a && b == p.b && c == p.c && d == p.d;
		}

		inline bool operator != ( const Plane& p ) const
		{
			return a != p.a || b != p.b || c != p.c || d != p.d;
		}

		inline Plane& operator *= ( const float f )
		{
			a *= f;  b *= f;  c *= f;  d *= f;   return *this;
		}

		inline Plane& operator /= ( const float f )
		{
			const float fi = 1.0f/f;    a*=fi;  b*=fi;  c*=fi;  d*=fi;   return *this;
		}



		inline Plane operator + () const {    return *this; }
		inline Plane operator - () const {   return Plane(-a, -b, -c, -d);}

		inline Plane operator * ( const float f ) const
		{
			return Plane(a * f, b * f, c * f, d * f);
		}

		inline Plane operator / ( const float f ) const
		{
			const float fi = 1.0f / f;  return Plane(a*fi, b*fi, c*fi, d*fi);
		}

		inline friend Plane operator * (float f, const Plane& p )
		{
			return Plane(f*p.a, f*p.b, f*p.c, f*p.d);
		}




		//---------------------------------------------------------------------
		//                         МЕТОДЫ
		//---------------------------------------------------------------------


	inline base::vec3_s getOrigin() const { base::vec3_s r; r.x=x; r.y=y; r.z=z; return r;  };



	};


	struct quat_s {

		union {
			struct { float x, y, z, w;  };
			float floats [4];
		};


	};



	class Quaternion : public quat_s {
	public:

		inline Quaternion() { x=y=z=0.0f; w=1.0f; };
		inline Quaternion(const Quaternion& q) { x=q.x; y=q.y; z=q.z; w=q.w; };
		inline Quaternion(float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; };
		inline Quaternion(const float* pfArray)
		{
			 x = pfArray[0];
			 y = pfArray[1];
			 z = pfArray[2];
			 w = pfArray[3];
		}

		//-----------------------------------------------------------------
		//                     ОПЕРАТОРЫ
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

		//inline Quaternion& operator *= ( const Quaternion& q )
		//{
		//	D3DXQuaternionMultiply(this, this, &q);
		//	return *this;
		//}

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


#pragma message ("KS777: MATH::QUAT >> NEED CHECK MUL OPERATOR " __FILE__)

	   // babar
		/*inline Quaternion   operator * (const Quaternion &q) const 
		{
			Quaternion res;
			res.x =  w*q.x + x*q.w + y*q.z - z*q.y;
			res.y =  w*q.y + y*q.w + z*q.x - x*q.z;
			res.z =  w*q.z + z*q.w + x*q.y - y*q.x;

			res.w =  w * q.w - x * q.x - y * q.y - z * q.z;
			return res;
		}
		*/

		// book
		inline Quaternion Quaternion::operator * ( const Quaternion &q ) const 
		{
			Quaternion res;
			res.x = w*q.x + x*q.w + z*q.y - y*q.z;
			res.y = w*q.y + y*q.w + x*q.z - z*q.x;
			res.z = w*q.z + z*q.w + y*q.x - x*q.y;

			res.w = w*q.w - x*q.x - y*q.y - z*q.z;
			return res;
		}
		//////////////////////////////////////////////////////////////////////


		inline Quaternion operator * ( const float f ) const
		{
			return Quaternion( x*f, y*f, z*f, w*f );
		}



		inline Quaternion operator / ( const float f ) const
		{
			const float fInverse = 1.0f / f;
			return Quaternion(x * fInverse, y * fInverse, z * fInverse, w * fInverse);
		}


		//inline Quaternion operator * (const float f, const Quaternion& q )
		//{
		//	return Quaternion( f*q.x, f*q.y, f*q.z, f*q.w );
		//}




		inline Quaternion&   operator *= (const Quaternion &q) { Quaternion r(*this); *this=r*q; return *this;   } 
		//{
		//	Quaternion res;
		//	res.x = w * q.x + x * q.w + y * q.z - z * q.y;
		//	res.y = w * q.y + y * q.w + z * q.x - x * q.z;
		//	res.z = w * q.z + z * q.w + x * q.y - y * q.x;
		//	res.w = w * q.w - x * q.x - y * q.y - z * q.z;
		//	*this = res;
		//	return *this;
		//}







		//-----------------------------------------------------------------
		//                     МЕТОДЫ
		//-----------------------------------------------------------------
 

		inline void setIdentity() {  x = y = z = 0.0f; w = 1.0f; }

		inline bool isIdentity(float eps = 0.0f) const
		{ 
			return 
				abs(x) <= eps && 
				abs(y) <= eps && 
				abs(z) <= eps && 
				abs(w) - 1.0f <= eps;
		}

		inline float length() const	{ return sqrt(x * x + y * y + z * z + w * w); }

		inline float lengthSq() const {	return  (x * x + y * y + z * z + w * w);  }

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

		inline Quaternion conjugate(const Quaternion &q) const
		{
			  Quaternion res;
			    res.w = q.w;
			    res.x = -q.x;
			    res.y = -q.y;
			    res.z = -q.z;
			  return  res;
		}

		inline float dot( const Quaternion &g) const 
		{
			return w*g.w + x*g.x + y*g.y + z*g.z;
		}

		Quaternion  pow(const Quaternion &q, float exponent) const;

/*****************************************************

		Quaternion  exp() const 
		{
			//			Given a pure quaternion defined by:
			//q = (0, theta * v); 
			//    
			//This method calculates the exponential result.
			//exp(Q) = (cos(theta), sin(theta) * v)
			//
			?????

		}

		Quaternion&  inverse()
		{
		
         // A unit quaternion, is defined by:
         // Q == (cos(theta), sin(theta) * v) where |v| = 1
         // The natural logarithm of Q is, ln(Q) = (0, theta * v)

         ????
		   return *this;
		}

		//*  natural log
		Quaternion  logn () const
		{
            Quaternion res;
		 
//		A unit quaternion, is defined by:
//Q == (cos(theta), sin(theta) * v) where |v| = 1
//The natural logarithm of Q is, ln(Q) = (0, theta * v)


		????
			return res;
		
		}


		Quaternion& setFromRotationMatrix(const base::mat44_s& m);

		 
		static Quaternion BaryCentric(
			const Quaternion& q1,
			const Quaternion& q2,
			const Quaternion& q3,
			float f,
			float g	);

   Quaternion& setRotationYawPitchRoll( float yaw,  float pitch,  float roll );

  
   static Quaternion Squad(
	   const Quaternion&  q1,
	   const Quaternion&  gA,
	   const Quaternion&  gB,
	   const Quaternion&  gC,
	   float t
	   );

   static void  SquadSetup(
	   Quaternion& AOut,
	   Quaternion& BOut,
	   Quaternion& COut,
	   const Quaternion& Q0,
	   const Quaternion& Q1,
	   const Quaternion& Q2,
	   const Quaternion& Q3
	   );



***************************************************/



		static Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);

		inline Quaternion slerp(const Quaternion &q, float t) const { Quaternion r = slerp(*this, q, t); return r;  };


		inline float getRotationAngle() const 
		{
			// Compute the half angle.  Remember that w = cos(theta / 2)
			float thetaOver2 = scalar::safeAcos(w);
			// Return the rotation angle
			return thetaOver2 * 2.0f;
		}

		base::vec3_s  getRotationAxis() const;

		inline AxiesAngle getRotationAxiesAngle() const 
		{
			AxiesAngle res;
			res.angle = getRotationAngle();
			res.axies = getRotationAxis();
			return res;
		}

		inline AxiesAngle toAxiesAngle() const { return getRotationAxiesAngle(); }


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

		Quaternion&         setRotationAboutAxisAngle(const base::vec3_s &axis, float theta) ;

		inline Quaternion&  setRotationAboutAxisAngle(const AxiesAngle& aa)
		{
		  return setRotationAboutAxisAngle( aa.axies , aa.angle );
		}






	};



    //---------------------------------------------------------------------
	//                    КОНСТАНТЫ
	//---------------------------------------------------------------------


const Quaternion QUATERNION_IDENTITY = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );





    } // end ns
  } // end ns
} // end ns

// end file