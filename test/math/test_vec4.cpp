
#include <gb/math/math.h>

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



//===================================================
int main()
{

test_mul();


};