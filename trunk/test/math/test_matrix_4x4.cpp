

#include <gb/math/math.h>
#include <d3dx9math.h>

#include <stdio.h>

using namespace gb::math;
using namespace gb::math::base;

#pragma warning(disable : 4305)

 
#define MDX  D3DXMATRIX
#define MGB  gb::math::base::mat44_s

#if defined(DEBUG) || defined(_DEBUG)
  #pragma comment( lib, "d3dx9d.lib" )
#else
  #pragma comment( lib, "d3dx9.lib" )
#endif

//=========================================================================
void print_matrices(const D3DXMATRIX& m, const mat44_s& mgb )
{
	printf("\n ================================================= \n");
 printf("\n%f  %f  %f  %f  \n%f  %f  %f  %f  \n%f  %f  %f  %f  \n%f  %f  %f  %f  \n  ", 
	 m._11, m._12, m._13, m._14, 
	 m._21, m._22, m._23, m._24,
	 m._31, m._32, m._33, m._34,	 
	 m._41, m._42, m._43, m._44	 
	 );
 printf("\n -------------------------------------- \n");
 mgb.print();
};

void print_div()
{
   printf("\n---------------------div------------------------\n");
}


//===========================================================
void setval(  D3DXMATRIX& m)
{
	m._11= 8.067f;
	m._12= 6.545f;
	m._13= 2.455f;
	m._14= 1.832f;

	m._21= 0.545f;
	m._22= 7.854f;
	m._23= 8.988f;
	m._24= 4.038f;

	m._31= 5.966f;
	m._32= 1.069f;
	m._33= 2.235f;
	m._34= 5.905f;

	m._41= 4.903f;
	m._42= 6.534f;
	m._43= 2.077f;
	m._44= 8.355f;
}


//===========================================================
void setval(  D3DXMATRIX& m,   mat44_s& mgb)
{
 m._11= 8.067f;
 m._12= 6.545f;
 m._13= 2.455f;
 m._14= 1.832f;

 m._21= 0.545f;
 m._22= 7.854f;
 m._23= 8.988f;
 m._24= 4.038f;

 m._31= 5.966f;
 m._32= 1.069f;
 m._33= 2.235f;
 m._34= 5.905f;

 m._41= 4.903f;
 m._42= 6.534f;
 m._43= 2.077f;
 m._44= 8.355f;

//***************************************************************

 mgb._11= 8.06;
 mgb._12= 6.545;
 mgb._13= 2.455;
 mgb._14= 1.832;

 mgb._21= 0.545;
 mgb._22= 7.8;
 mgb._23= 8.988;
 mgb._24= 4.038;

 mgb._31= 5.966;
 mgb._32= 1.069;
 mgb._33= 2.235;
 mgb._34= 5.905;

 mgb._41= 4.903;
 mgb._42= 6.534;
 mgb._43= 2.077;
 mgb._44= 8.355;

}

//===============================================
void print_func(const char* funcname)
{
    printf("\n****************** %s ***********************\n" , funcname );
}


#define PRINTFUNC  print_func(__FUNCTION__);



//======================================================
void test_identity()
{
PRINTFUNC
 MDX mdx;
  MGB mgb;

  // set identity
  D3DXMatrixIdentity(&mdx);
  mgb.reset();
  print_matrices(mdx,mgb);
}


//===========================================================
void test_assign()
{
	PRINTFUNC
 D3DXMATRIX mdx;
 for(int c=0; c<16; c++)
 {
   float* pf = &mdx._11;
   pf[c] = (float)c;
 }

 MGB mgb;
 mgb = mdx;

  print_matrices(mdx,mgb);
// int _end =0;
}

//===========================================================
void test_mul()
{
	PRINTFUNC
 D3DXMATRIX mdx1, mdx2, mdxres;

 mdx1 = D3DXMATRIX(
	 2.45f, 1.45f, 1.48f, 6.28f, 
	 1.54f, 9.58f, 9.35f, 1.87f,
	 3.46f, 5.66f, 1.56f, 1.65f,
	 7.49f, 3.87f, 7.12f, 3.45f );

 mdx2 = D3DXMATRIX(
	 2.45f, 1.45f, 1.48f, 6.28f, 
	 1.54f, 9.58f, 9.35f, 1.87f,
	 3.46f, 5.66f, 1.56f, 1.65f,
	 7.49f, 3.87f, 7.12f, 3.45f );

//D3DXMatrixMultiply
 mdxres = mdx1 * mdx2;
//********************************************************
mat44_s mgb1 , mgb2 , mgbres;

 mgb1 = mat44_s(
	 2.45f, 1.45f, 1.48f, 6.28f, 
	 1.54f, 9.58f, 9.35f, 1.87f,
	 3.46f, 5.66f, 1.56f, 1.65f,
	 7.49f, 3.87f, 7.12f, 3.45f );

 mgb2 = mat44_s(
	 2.45f, 1.45f, 1.48f, 6.28f, 
	 1.54f, 9.58f, 9.35f, 1.87f,
	 3.46f, 5.66f, 1.56f, 1.65f,
	 7.49f, 3.87f, 7.12f, 3.45f );


 // первый способ
mgbres = mgb1 * mgb2;

//второй способ
//mgbres = mgb1 ;
//mgbres *= mgb2;


print_matrices(mdxres , mgbres);

 int _end = 0;
}

//==================================================
void test_determinant()
{
PRINTFUNC

	MDX mdx;
   mdx = MDX(
	 2.45f, 1.45f, 1.48f, 6.28f, 
	 1.54f, 9.58f, 9.35f, 1.87f,
	 3.46f, 5.66f, 1.56f, 1.65f,
	 7.49f, 3.87f, 7.12f, 3.45f );


	MGB mgb; mgb  = mdx;

float det = D3DXMatrixDeterminant(&mdx);
printf("mdx det= %f \n", det);
det = mgb.determinant();
printf("mgb det= %f \n", det);

}

//====================================
void test_inverse()
{
PRINTFUNC
	MDX mdx;
	MGB mgb;

  setval(mdx);
  mgb = mdx;

  D3DXMatrixInverse(&mdx , NULL , &mdx);
  mgb.invert();

print_matrices(mdx , mgb);
}

//======================================
void test_view_lookatLH()
{
	PRINTFUNC
  MDX mdx;
  MGB mgb;

 D3DXMatrixLookAtLH(
   &mdx,
	    &D3DXVECTOR3(   5.45f , 4.86f,  3.945f  ), // pEye,
	    &D3DXVECTOR3(   -1.25f , 2.458f , 20.458f  ), // pAt,
	    &D3DXVECTOR3(   0.0f , 1.0f , 0.0f ) // pUp
	  );

  mgb.setViewLookAtLH(
	  vec3_s(  5.45f , 4.86f,  3.945f ), // pEye,
	  vec3_s(  -1.25f , 2.458f , 20.458f  ), // pAt,
	  vec3_s(   0.0f , 1.0f , 0.0f ) // pUp	  
	  );

print_matrices(mdx , mgb);
}


//======================================
void test_view_lookatRH()
{
	PRINTFUNC
	MDX mdx;
	MGB mgb;

	D3DXMatrixLookAtRH(
		&mdx,
		&D3DXVECTOR3(   5.45f , 4.86f,  3.945f  ), // pEye,
		&D3DXVECTOR3(   -1.25f , 2.458f , 20.458f  ), // pAt,
		&D3DXVECTOR3(   0.0f , 1.0f , 0.0f ) // pUp
		);

	mgb.setViewLookAtRH(
		vec3_s(  5.45f , 4.86f,  3.945f ), // pEye,
		vec3_s(  -1.25f , 2.458f , 20.458f  ), // pAt,
		vec3_s(   0.0f , 1.0f , 0.0f ) // pUp	  
		);

	print_matrices(mdx , mgb);
}


//===============================
void test_orthoLH()
{
PRINTFUNC

MDX mdx;
MGB mgb;

  D3DXMatrixOrthoLH( &mdx,
							   800, //  FLOAT w,
							   600, //FLOAT h,
							   0.1f, //FLOAT zn,
							   100.0f // FLOAT zf
							   );


mgb.setOrthoLH(800, 600, 0.1f , 100.0f );
	
print_matrices(mdx , mgb);
}

//===============================
void test_orthoRH()
{
	PRINTFUNC

  MDX mdx;
  MGB mgb;

  D3DXMatrixOrthoRH( &mdx,
							   800, //  FLOAT w,
							   600, //FLOAT h,
							   0.1f, //FLOAT zn,
							   100.0f // FLOAT zf
							   );


mgb.setOrthoRH(800, 600, 0.1f , 100.0f );

	print_matrices(mdx , mgb);
}


//====================================
void test_setOrthoOffCenterLH()
{
	PRINTFUNC

  MDX mdx;
  MGB mgb;

    D3DXMatrixOrthoOffCenterLH(
  &mdx,
  15.0f, //FLOAT l, // Minimum x-value of view volume. 
  125.45f,//FLOAT r, // Maximum x-value of view volume. 

  12.45f,//FLOAT b, // Minimum y-value of view volume. 
  142.15f,//FLOAT t, // Maximum y-value of view volume. 

  0.1f ,//FLOAT zn, // Minimum z-value of the view volume. 
  100.0f//FLOAT zf // Maximum z-value of the view volume.
);

	mgb.setOrthoOffCenterLH(
	  15.0f, //FLOAT l, // Minimum x-value of view volume. 
  125.45f,//FLOAT r, // Maximum x-value of view volume. 

  12.45f,//FLOAT b, // Minimum y-value of view volume. 
  142.15f,//FLOAT t, // Maximum y-value of view volume. 

  0.1f ,//FLOAT zn, // Minimum z-value of the view volume. 
  100.0f//FLOAT zf // Maximum z-value of the view volume.	
		
		);

	print_matrices(mdx , mgb);
}



//====================================
void test_setOrthoOffCenterRH()
{
  PRINTFUNC
  MDX mdx;
  MGB mgb;

    D3DXMatrixOrthoOffCenterRH(
  &mdx,
  15.0f, //FLOAT l, // Minimum x-value of view volume. 
  125.45f,//FLOAT r, // Maximum x-value of view volume. 

  12.45f,//FLOAT b, // Minimum y-value of view volume. 
  142.15f,//FLOAT t, // Maximum y-value of view volume. 

  0.1f ,//FLOAT zn, // Minimum z-value of the view volume. 
  100.0f//FLOAT zf // Maximum z-value of the view volume.
);

	mgb.setOrthoOffCenterRH(
	  15.0f, //FLOAT l, // Minimum x-value of view volume. 
  125.45f,//FLOAT r, // Maximum x-value of view volume. 

  12.45f,//FLOAT b, // Minimum y-value of view volume. 
  142.15f,//FLOAT t, // Maximum y-value of view volume. 

  0.1f ,//FLOAT zn, // Minimum z-value of the view volume. 
  100.0f//FLOAT zf // Maximum z-value of the view volume.		
		);

	print_matrices(mdx , mgb);
}


//=============================
void test_setPerspectiveFovLH()
{
  PRINTFUNC
  MDX mdx;
  MGB mgb;

 D3DXMatrixPerspectiveFovLH( &mdx,
   1.3f,  // FLOAT fovy,
   1.12f, // FLOAT Aspect,
  0.01f, //FLOAT zn,
  1000.0f //FLOAT zf
 );

 mgb.setPerspectiveFovLH(    
   1.3f,  // FLOAT fovy,
   1.12f, // FLOAT Aspect,
  0.01f, //FLOAT zn,
  1000.0f //FLOAT zf	 
 );
 
	print_matrices(mdx , mgb);   
}


//=============================
void test_setPerspectiveFovRH()
{
  PRINTFUNC
  MDX mdx;
  MGB mgb;

 D3DXMatrixPerspectiveFovRH( &mdx,
   1.3f,  // FLOAT fovy,
   1.12f, // FLOAT Aspect,
  0.01f, //FLOAT zn,
  1000.0f //FLOAT zf
 );

 mgb.setPerspectiveFovRH(    
   1.3f,  // FLOAT fovy,
   1.12f, // FLOAT Aspect,
  0.01f, //FLOAT zn,
  1000.0f //FLOAT zf	 
 );
 
	print_matrices(mdx , mgb);   
}

//====================================
void test_setPerspectiveLH()
{
  PRINTFUNC
  MDX mdx;
  MGB mgb;

  D3DXMatrixPerspectiveLH( &mdx,
 800.0f, // FLOAT w,
  600.0f, //FLOAT h,
  0.096f, //FLOAT zn,
  1200.0f // FLOAT zf
);

  mgb.setPerspectiveLH(800.0f  ,  600.0f , 0.096f , 1200.0f );

	print_matrices(mdx , mgb); 
}


//====================================
void test_setPerspectiveRH()
{
  PRINTFUNC
  MDX mdx;
  MGB mgb;

  D3DXMatrixPerspectiveRH( &mdx,
 800.0f, // FLOAT w,
  600.0f, //FLOAT h,
  0.096f, //FLOAT zn,
  1200.0f // FLOAT zf
);

  mgb.setPerspectiveRH(800.0f  ,  600.0f , 0.096f , 1200.0f );

	print_matrices(mdx , mgb); 
}


//=========================================================================
int main( )
{
  test_identity();
  test_mul();
 test_determinant();
 test_inverse();

 test_view_lookatLH();
 test_view_lookatRH();

test_orthoLH();
test_orthoRH();

test_setOrthoOffCenterLH();
test_setOrthoOffCenterRH();

test_setPerspectiveFovLH();
test_setPerspectiveFovRH();

test_setPerspectiveLH();
test_setPerspectiveRH();

 



 printf(" \n\n  ######################   end program   ##################### \n");
system("pause");
	return 0;
}

