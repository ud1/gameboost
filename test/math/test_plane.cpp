

#include <gb/math/math.h>
#include <d3dx9math.h>

#include <stdio.h>

using namespace gb::math;
using namespace gb::math::base;

#pragma warning(disable : 4305)

 
#define DXP  D3DXPLANE
#define GBP  gb::math::geom3d::Plane

#if defined(DEBUG) || defined(_DEBUG)
  #pragma comment( lib, "d3dx9d.lib" )
#else
  #pragma comment( lib, "d3dx9.lib" )
#endif


//===============================================
void print_func(const char* funcname)
{
    printf("\n****************** %s ***********************\n" , funcname );
}


#define PRINTFUNC  print_func(__FUNCTION__);

//=============================================
void print_planes(const DXP& dxp, const GBP& gbp)
{
  printf("-----------------------------------\n");
 printf("%f  %f  %f  %f\n" , dxp.a , dxp.b , dxp.c , dxp.d );
  printf("-----------------------------------\n");
 gbp.print();
printf("\n");

};

////==========================================
//void xxx()
//{
// PRINTFUNC
//  GBP gbp;
//  DXP dxp;
//
//  xxxxxxxxxxxxxxxxxxxxxxxxxxx
//  
//  
//  print_planes(dxp , gbp);
//};

//===============================================
void test_normalize() 
{
	PRINTFUNC
	GBP gbp;
	DXP dxp;

 D3DXPlaneNormalize( &dxp , 
	 &DXP(  1.155f , 3.155f , 6.15f , 1.6448f ) );

 gbp = GBP( 1.155f , 3.155f , 6.15f , 1.6448f   );
 gbp.normalize();

  print_planes(dxp , gbp);
};

//===============================================
void test_dot() 
{
	PRINTFUNC
	GBP gbp;
	DXP dxp;

	float fdot_dxp =   D3DXPlaneDot( &dxp, &D3DXVECTOR4 ( 1.025f , 0.458f , 0.954f , 0.648f ) 	);
	float fdot_gbp = gbp.dot( vec4_s(   1.025f , 0.458f , 0.954f , 0.648f     ) );


 printf( "\ndxres=%f \ngbres=%f\n\n", fdot_dxp , fdot_gbp  );
};

//===============================================
void test_FromPointNormal()
{
	PRINTFUNC
	GBP gbp;
	DXP dxp;

	{
D3DXVECTOR3 p = D3DXVECTOR3(  34.1574f , 12.488f , 32.158f  );
D3DXVECTOR3 n = D3DXVECTOR3(  0.645f , 0.426f , 0.36645f  );
D3DXVec3Normalize(&n , &n);
	
	D3DXPlaneFromPointNormal( &dxp,  &p,  &n );

	}

	{
  vec3_s p = vec3_s(    34.1574f , 12.488f , 32.158f    );
  vec3_s n = vec3_s(    0.645f , 0.426f , 0.36645f     );
    n.normalize();

	gbp.makeFromPointNormal(p, n);
 
	}
 
   print_planes(dxp , gbp);
};

//===============================================
void test_FromPoints()
{
	PRINTFUNC
	GBP gbp;
	DXP dxp;

	{
D3DXVECTOR3 p1 = D3DXVECTOR3(  44.14f , 12.488f , 32.158f  );
D3DXVECTOR3 p2 = D3DXVECTOR3(  36.15f , 12.456f , 78.15f  );
D3DXVECTOR3 p3 = D3DXVECTOR3(  56.45f , 40.155f , 23.155f  );
 
D3DXPlaneFromPoints(&dxp , &p1 , &p2, &p3);

	}

	{
  vec3_s p1          = vec3_s(  44.14f , 12.488f , 32.158f   );
  vec3_s p2          = vec3_s(  36.15f , 12.456f , 78.15f  );
  vec3_s p3          = vec3_s(  56.45f , 40.155f , 23.155f  );
    gbp.makeFromPoints(p1,p2,p3);
  

	}


   print_planes(dxp , gbp);
};



//=====================================
void test_scale()
{
      PRINTFUNC

	  GBP gbp;
	  DXP dxp;

 
  D3DXPlaneScale( &dxp,
	   &D3DXPLANE (  6.15f , 3.054f , -4.056f , 1.648f   ),
	    1.458f
	 );


  gbp = GBP(    6.15f , 3.054f , -4.056f , 1.648f     );
 gbp.scale( 1.458f);




   print_planes(dxp , gbp);
}


//==============================================================
int main()
{

	test_normalize();
	test_dot();
	test_FromPointNormal();
	test_FromPoints();
test_scale();







 printf(" \n\n  ######################   end program   ##################### \n");
system("pause");
 return 0;
};