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

			inline operator base::vec3_s() const { return base::vec3_s(x,y,z); }


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
	  
	
	  inline void set(const base::vec3_s& vCenter, float fRadius) {center=vCenter; radius=fRadius; }
	  inline void set( float centerX, float centerY, float centerZ, float fRadius) { center.x=centerX;  center.y=centerY;  center.z=centerZ;  radius=fRadius; 	}
	  inline void set(int ix, int iy, int iz, int r) { center.x=(float)ix;  center.y=(float)iy;  center.z=(float)iz;	radius = (float)r; }

	  //! \brief Получить расстояние между краями сфер. Вернёт отрицательное если сферы пересекаются.
      inline float distanceBetweenSphere(const Sphere& s) const 
	  {
		  float res = 0.0f;
		  {  base::vec3_s t(center-s.center); res=t.length();  }
		  res = res - ( radius + s.radius );
		  return res;
	  }

	  //! \brief Проверка пересечения сфер
	  inline bool checkIntersectSphere(const Sphere& s) 
	  {
		  float dist;
		  {  base::vec3_s t(center-s.center); dist=t.length();  }

		  if (dist < (radius + s.radius) ) 
			  return false;

		  return true;
	  };



	
	};
		
	//! \brief Бокс по мин. и макс. координатам. Axis aligned bounding box.
	class AABB {
	public:
	  base::vec3_s   min; ///< минимальная точка бокса
	  base::vec3_s   max; ///< максимальная точка бокса
	  
	  inline AABB() {}
	  inline AABB(const AABB& aabb) {min=aabb.min; max=aabb.max;}	  
	  inline AABB(const base::vec3_s& _min, const base::vec3_s& _max) { min=_min; max=_max;  }
	

	  inline bool operator == (const AABB& aabb) { return (min == aabb.min) && (max == aabb.max); }
	
	
/*	inline void  make(int nminx, int nminy, int nminz, int nmaxx, int nmaxy, int nmaxz) 
	{
	  min.x = (float)nminx;	min.y = (float)nminy; min.z = (float)nminz;
	  max.x = (float)nmaxx; max.y = (float)nmaxy; max.z = (float)nmaxz;
	  min.minimize(&max); max.maximize(&min);
	};
*/




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
 
	//! \brief   Линия в трёхмерном пространстве по двум точкам  
	class Line {
	public:
		base::vec3_s   src; 
		base::vec3_s   dest;

		inline Line() {};
		inline Line(const Line& l) {src=l.src; dest=l.dest; };	
		inline Line(const base::vec3_s& _src, const base::vec3_s& _dest) {src=_src; dest=_dest; };

		inline base::vec3_s getDirection() const { base::vec3_s r (dest - src); r.normalize(); return r; }



      #if ( defined(GB_OPENGL) &&  defined(__GL_H__) )
		//! \brief Вывод вершин для OpenGl по старинке.
		inline void glVertex() { glVertex3f(src.x, src.y, src.z); glVertex3f(dest.x, dest.y, dest.z);   };
      #endif


		//! вывод на консоль.
		inline void print() const { src.print(); printf("  "); dest.print(); printf("  \n"); };

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

	   //! \brief  Присваивание из float-массива
	   inline void operator = (const float* pfArray)
	   {
		   a = pfArray[0]; 
		   b = pfArray[1];
		   c = pfArray[2];
		   d = pfArray[3];	   
	   }

	   inline operator        float*()       { return &a; };
	   inline operator const  float*() const { return &a; };


	   inline void set(float _a, float _b, float _c, float _d)  { a=_a; b=_b; c=_c; d=_d; }


	    //! \brief Построение плоскости по координате point и направлению normal.
		inline plane_s& makeFromPointNormal(const base::vec3_s& point, const base::vec3_s& normal) 
		{
			base::vec3_s nn(normal);
			nn.normalize();
			a=nn.x;  
			b=nn.y;  
			c=nn.z;  
			d= -( normal.dot(point) ); 
			return *this;
		};

        //! \brief Построение плоскости по точкам.
		inline plane_s& makeFromPoints(const base::vec3_s& p1, const base::vec3_s& p2, const base::vec3_s& p3 ) 
		{
			base::vec3_s vsub1 = p1 - p2;    	 
			vsub1.normalize();

			base::vec3_s vsub2 = p1 - p3;	 
			vsub2.normalize();

			base::vec3_s nrml = vsub1.cross(vsub2);   
			nrml.normalize();

			makeFromPointNormal(p1, &nrml);
			return *this;
		}

		//! \brief   Нормализовать плоскость.
		inline void normalize() 
		{
			register const float fm = sqrt(a*a + b*b + c*c); 
			a/= fm;	
			b/= fm; 
			c/= fm; 
			d/= fm; 
		}


		inline float dot(const base::vec4_s& v) const        { return a*v.x + b*v.y + c*v.z + d*v.w ; }
		inline float dotCoord  (const base::vec3_s& v) const { return a*x + b*y + c*z + d*1.0f; }
		inline float dotNormal (const base::vec3_s& v) const { return a*x + b*y + c*z + d*0.0f; }

		//! \brief   Масштабировать плоскость.
		inline void scale(float s) {a*=s; b*=s; c*=s; d*=s; }


		//! \brief  Вернуть нормаль плоскости.  ПРОВЕРИТЬ !!!!
		inline base::vec3_s  getNormal() const  
		{ 
			base::vec3_s res; 
			res.x=a; 
			res.y=b; 
			res.z=c; 
			return res; 
		}

		//! \brief  Инвертировать плоскость
		inline void inverse() { a*=-a; b*=-b; c*=-c;  }

		//! \brief  Получить инвертированую плоскость
		inline plane_s inverted() const { plane_s res = *this; res.inverse(); return res; }
 

#ifdef GB_D3DX9
  inline void operator = (const D3DXPLANE& p)  { a=p.a; b=p.b; c=p.c; d=p.d; }
  inline operator D3DXPLANE() const { return D3DXPLANE(a, b, c, d); }
#endif



		//! \brief  Вывод на консоль.
		void print() const 	{ printf( "%f  %f  %f  %f", a, b, c, d); 	}


	};



	class Plane : public plane_s {
	public:
		inline Plane() {};
		inline Plane(const Plane& p) {a=p.a; b=p.b; c=p.c; d=p.d; }

		inline Plane(float _a, float _b, float _c, float _d) { a=_a; b=_b; c=_c; d=_d; }


		//---------------------------------------------------------------------
		//                        ОПЕРАТОРЫ
		//---------------------------------------------------------------------




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


	



//	inline void print() const { printf("%f  %f  %f  %f",  a, b, c, d); }

	};



	struct quat_s {

		union {
			struct { float x, y, z, w;  };
			float floats [4];
		};


	};





	//! \brief Стандартный  кватернион.
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
		inline Quaternion operator * ( const Quaternion &q ) const 
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




	//! \brief Треугольник по трём точкам . 
	class Triangle {
	public:
		base::vec3_s   p1; ///< первая точка(вершина) треугольника 
		base::vec3_s   p2; ///< вторая точка(вершина) треугольника   
		base::vec3_s   p3; ///< третья точка(вершина) треугольника 


		inline Triangle() {}
		inline Triangle(const Triangle& t) { *this = t; }
		inline Triangle(const base::vec3_s _p1, const base::vec3_s _p2, const base::vec3_s _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		inline void set(const base::vec3_s _p1, const base::vec3_s _p2, const base::vec3_s _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		/** \brief Вычислить и вернуть среднюю точку треугольника */
		inline base::vec3_s middlePoint() const 
		{ 
			base::vec3_s res;
			res.x= (p1.x + p2.x + p3.x) / 3.0f;
			res.y= (p1.y + p2.y + p3.y) / 3.0f;
			res.z= (p1.z + p2.z + p3.z) / 3.0f;
			return res;
		}

		//! \brief Вычислить и вернуть плоскость по точкам треугольника 
		plane_s getPlane() const
		{
			plane_s plane; 
			plane.makeFromPoints(p1,p2,p3); 	
			return plane;
		}


#if ( defined(GB_OPENGL) && defined(__GL_H__)   )
		//! \brief Вывод вершин по OpenGL  по старинке.
		inline void glDraw()   {
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(p3.x, p3.y, p3.z); 
		}
#endif





	};



	//!  \brief Клас бесконечный прожектор по лучу (точка основания) и углу прожектора 
	class  Projector {
	public:
		Ray ray;   ///< луч (центр и направление прожектора)
		float phi; ///< угол конуса

		Projector() {};
		Projector(const Projector& pr) {ray=pr.ray; phi=pr.phi;  };


	}; // Projector



   //! \brief Стандартная пирамида видимости
   class Frustum  {
   public:

	   union {
		   struct {
			   Plane  front;
			   Plane  back;  
			   Plane  left;   
			   Plane  right;   
			   Plane  top;
			   Plane  bottom;  
		   };

		   plane_s  planes[6] ;
	   };

	   inline Frustum() {}
	   inline Frustum(const Frustum& f) { *this=f; }


	   /** \brief Выполнить построение из матричного произведения view * proj */
	   void make(const base::mat44_s& mViewProj);	

	   /** \brief Выполнить построение из матриц   view и proj */
	   void make(const base::mat44_s& mView, const base::mat44_s& mProj) 
	   {
		   base::mat44_s mViewProj = mView * mProj;
		   make(mViewProj);
	   }

       //! \brief Проверка попадания точки в пирамиду 
	   bool checkPoint(const base::vec3_s& point) const; 

       //! \brief Проверка попадания сферы в пирамиду
	   bool checkSphere(const Sphere& sphere)  const; 

	   //! \brief Проверка попадания бокса в пирамиду
       bool checkAABB(const AABB& aabb) const;




     //! \brief Отладочный вывод на консоль
     inline void print() const 
	 {
		 printf("front=");  front.print();  printf("\n");
		 printf("back=");   back.print();   printf("\n");
		 printf("left= ");  left.print();   printf("\n");
		 printf("right=");  right.print();  printf("\n");
		 printf("top=");    top.print();    printf("\n");
		 printf("bottom="); bottom.print(); printf("\n");
 	 }


   };






    //---------------------------------------------------------------------
	//                    КОНСТАНТЫ
	//---------------------------------------------------------------------


// static const Quaternion QUATERNION_IDENTITY = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );





    } // end ns
  } // end ns math
} // end ns gb

// end file