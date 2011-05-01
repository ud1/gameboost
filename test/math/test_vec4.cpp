
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



void printVectors(const D3DXVECTOR4& dxv, const vec4_s& gbv)
{

 printf("\n%f  %f  %f  %f \n", dxv.x , dxv.y , dxv.z , dxv.w );
 printf("\n");
 gbv.print();
 printf("\n\n\n");

};

void test_mul()
{
 D3DXMATRIX dxm;
   D3DXMatrixLookAtLH(  &dxm,
 &D3DXVECTOR3( 45.15f,   135.15f,   32.458f ) , 
 &D3DXVECTOR3( 6.25f ,   13.48f,   -47.365f ) , 
 &D3DXVECTOR3( -9.35f,  -14.65f,    8.36 ) );

  D3DXVECTOR4 a (  13.1f , 45.76 , 8.304f , 7.31f  );
 D3DXVECTOR4 dxv ;// = dxm * a;
D3DXVec4Transform(  &dxv, &a , &dxm);

   
 mat44_s m;
 m.setViewLookAtLH(    
	 vec3_s( 45.15f,   135.15f,   32.458f ) , 
	 vec3_s( 6.25f ,   13.48f,   -47.365f ) , 
	 vec3_s( -9.35f,  -14.65f,    8.36 ) 
	  
	 );


vec4_s a2 = vec4_s (   13.1f , 45.76 , 8.304f , 7.31f    );
 vec4_s  gbv;
 gbv = m * a2;



 int end =0;
}


void test_cross1()
{

	//vec4_s v;
 // v.cross( vec4_s(xxx , xxxx, xxxx) );


};

void test_cross2()
{
D3DXVECTOR4 dxv;
vec4_s gbv;


 // d3dx
	{
 D3DXVECTOR4 v1 = D3DXVECTOR4 ( 45.0f , 13.0f  , 5.0f , 12.0f  );
 D3DXVECTOR4 v2 = D3DXVECTOR4 ( 46.0f , 4.0f  , 32.0f , 34.0f  );
 D3DXVECTOR4 v3 = D3DXVECTOR4 ( 11.0f , 65.0f  , 6.0f , 7.0f  );
  
D3DXVec4Cross(&dxv, &v1, &v2, &v3);

	}

	// gb
	{
 vec4_s v1 = vec4_s(  45.0f , 13.0f  , 5.0f , 12.0f   );
 vec4_s v2 = vec4_s(   46.0f , 4.0f  , 32.0f , 34.0f );
 vec4_s v3 = vec4_s(  11.0f , 65.0f  , 6.0f , 7.0f   );

 gbv.cross(v1, v2, v3);
	}

  printVectors(dxv, gbv);
}

//===================================================
int main()
{

test_mul();

test_cross2();


system("pause");
  return 0;
};