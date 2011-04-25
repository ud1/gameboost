
#include <gb/math/math.h>
#include <d3dx9math.h>

#include <stdio.h>

using namespace gb::math;
using namespace gb::math::base;

#pragma warning(disable : 4305)

 
#define DXQ  D3DXQUATERNION
#define GBQ  gb::math::geom3d::Quaternion 

#if defined(DEBUG) || defined(_DEBUG)
  #pragma comment( lib, "d3dx9d.lib" )
#else
  #pragma comment( lib, "d3dx9.lib" )
#endif

//==============================================================
void printq( const DXQ& dxq , const GBQ&  gbq )
{
 printf("\n-------------------------------------\n");
 printf( "%f  %f  %f  %f", dxq.x , dxq.y , dxq.z , dxq.w );
 printf("\n-------------------------------------\n");
  gbq.print();
  printf("\n");
}


//================================================================
void print_func(const char* funcname)
{
	printf("\n****************** %s ***********************\n", funcname);
}

#define PRINTFUNC  print_func(__FUNCTION__);




//==========================
void test_normalize()
{
	 PRINTFUNC
   DXQ dxq = DXQ( 1.45f , 0.2487f , 3.155f , 1.975f  );
   GBQ gbq = GBQ( 1.45f , 0.2487f , 3.155f , 1.975f  );

   D3DXQuaternionNormalize(  &dxq , &DXQ( dxq )  );

   gbq.normalize();

    printq(dxq , gbq);
}
 


//=============================================
void test_slerp()
{
 PRINTFUNC

  DXQ dxq;
  GBQ gbq;
 {
   DXQ q1 = D3DXQUATERNION (  1.458f, 2.345f, 1.15f, 0.964f  );
   DXQ q2 = D3DXQUATERNION (  3.054f , 1.035f, 3.45f, 1.644f  );

   D3DXQuaternionNormalize(  &q1 , &D3DXQUATERNION(q1)   );
   D3DXQuaternionNormalize(  &q2 , &D3DXQUATERNION(q2)   );

	   D3DXQuaternionSlerp(  &dxq,	 &q1, &q2,   0.89f );

 }
  //--------------------------------
 {
  gbq = GBQ( 3.054f , 1.035f, 3.45f, 1.644f    );
  GBQ gbq2 = GBQ( 1.458f, 2.345f, 1.15f, 0.964f    );

  gbq.normalize();
  gbq2.normalize();

  gbq.slerp( GBQ( 1.458f, 2.345f, 1.15f, 0.964f    ) , 0.89f  );
 }


  printq(dxq , gbq);
}


//==================================
void test_mul()
{
	  PRINTFUNC
   DXQ dxq;
   GBQ gbq;

   D3DXQuaternionMultiply(
	    &dxq,
	    &D3DXQUATERNION ( 0.25f  , 0.64f  , 0.324f , 0.287f    ),
	    &D3DXQUATERNION ( 0.645f , 0.164f , 0.254f , 0.1645f   )
	   );


gbq = GBQ(  0.25f  , 0.64f  , 0.324f , 0.287f    );
gbq = gbq * GBQ(  0.645f , 0.164f , 0.254f , 0.1645f    );
 

 printq(dxq , gbq);
}


//=====================================
void test_inverse()
{
	PRINTFUNC

   DXQ dxq;
   GBQ gbq;

   D3DXQuaternionInverse( &dxq,
	     &D3DXQUATERNION ( 0.3255f , 0.54f , 0.685f, 0.824f  )
	   );

 
   gbq = GBQ(  0.3255f , 0.54f , 0.685f, 0.824f    );
   gbq.inverse();


 printq(dxq , gbq);
};
//
////========================================
//void test_slerp()
//{
//	PRINTFUNC
//
//  DXQ dxq;
//  GBQ gbq;
//
//  D3DXQuaternionSlerp( &dxq,
//	    &D3DXQUATERNION ( 0.245f , 0.645f , 0.756f , 0.298f  ),
//	    &D3DXQUATERNION ( 0.366f , 0.845f , 0.2015f, 0.615f  ),
//	     0.457f // FLOAT t
//	  );
//
//  //***************************
//
//     gbq = GBQ(   0.245f , 0.645f , 0.756f , 0.298f    );
//      gbq.slerp( GBQ(  0.366f , 0.845f , 0.2015f, 0.615f    ),   0.457f    )
//
//
// printq(dxq , gbq);
//}

//=====================================
void test_length()
{
 	PRINTFUNC
 
  DXQ dxq;
  GBQ gbq;

  // sqrtf(pQ->x * pQ->x + pQ->y * pQ->y + pQ->z * pQ->z + pQ->w * pQ->w);



  printq(dxq , gbq);
}


//======================================
void test_conjugate()
{

	PRINTFUNC

		DXQ dxq;
	GBQ gbq;




  printq(dxq , gbq);
}


//=====================================
void test_rotationYawPitchRoll()
{
	PRINTFUNC
	DXQ dxq;
	GBQ gbq;

	  D3DXQuaternionRotationYawPitchRoll(
		 &dxq,
		 0.345f , 0.812f , 1.324f
		 // FLOAT Yaw,
		// FLOAT Pitch,
		 //FLOAT Roll
		);


   gbq.setRotationYawPitchRoll( 0.345f , 0.812f , 1.324f );   

  printq(dxq , gbq);
}


//=================================================
void test_rotate_x()
{
	PRINTFUNC
	DXQ dxq;
	GBQ gbq;

  // none code !!!!
	assert(false && "no code !!!");

  gbq.setRotationX(  0.458f );
  printq(dxq , gbq);
};






//=========================================================================
int main( )
{
	test_normalize();
test_slerp();
test_inverse();
test_slerp();
test_mul();
test_rotationYawPitchRoll();



printf("\n\n ###############  END  ##################\n\n");
system("pause");
	return 0;
}