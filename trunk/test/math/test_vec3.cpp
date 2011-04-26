#include <gb/math/math.h>

#include <stdio.h>

#define DXV  D3DXVECTOR3
#define GBV  gb::math::base::vec3_s
 
using namespace gb::math;
using namespace gb::math::base;

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

void print_vectors(const D3DXVECTOR3& dxv, const gb::math::base::vec3_s& gbv)
{
  printf("\n----------------\n");
  printf("%f  %f  %f" ,  dxv.x , dxv.y ,  dxv.z );
  printf("\n----------------\n");
  gbv.print();
 
}

//===============================================
void print_func(const char* funcname)
{
	printf("\n\n\n****************** %s ***********************\n" , funcname );
}


#define PRINTFUNC  print_func(__FUNCTION__);


//==================================
void test_cross()
{
	PRINTFUNC
  DXV   dxvres ;
  GBV  gbvres ;
 
 

// d3dx
 D3DXVec3Cross( &dxvres,
   &D3DXVECTOR3(  1.454f , 2.455f , 1.975f   ),
   &D3DXVECTOR3(  2.4588f , -1.488f , 4.566f  )
	 );

// gb
GBV gbv1 = vec3_s(  1.454f , 2.455f , 1.975f    );

gbvres = gbv1.cross(   vec3_s( 2.4588f , -1.488f , 4.566f  )    );


 print_vectors( dxvres , gbvres );
}


//================================================
void test_transformCoord()
{
	PRINTFUNC
	DXV   dxv ;
    GBV  gbv ;

	printf("\n      D3DX: \n");
	// d3dx ===========================================
	{
D3DXQUATERNION   qRot;
 D3DXVECTOR3 vn = D3DXVECTOR3(  0.645f  ,  0.315f  ,  0.2111f  );
 D3DXQuaternionRotationAxis( &qRot,
	 &vn,
	 1.2455f
	);
 printf("\n d3dx quat rot= %f  %f  %f  %f  \n", qRot.x, qRot.y, qRot.z , qRot.w  );



  D3DXMATRIX m;
  {
   D3DXMATRIX ms, mr, mt;
   D3DXMatrixScaling(&ms,  1.24f , 0.945f , 0.895f  );
   D3DXMatrixRotationQuaternion(&mr , &qRot  );
   D3DXMatrixTranslation( &mt , 1.35f , 1.364f , 0.658f   );

   m = mt * mr * ms;
  }



	printf("\n matrix: \n");
	printf("\n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n  ", 
		m._11, m._12, m._13, m._14, 
		m._21, m._22, m._23, m._24,
		m._31, m._32, m._33, m._34,	 
		m._41, m._42, m._43, m._44	 
		);
 
	
  dxv  = DXV( 2.1544f , 1.648f , 3.16548f  );
  D3DXVec3TransformCoord( &dxv, 
	  &D3DXVECTOR3( 2.1544f , 1.648f , 3.16548f  ),
		 &m );

	}

		printf("\n      GB: \n");
	// gb =================================
	{
		gb::math::geom3d::Quaternion qRot;
		vec3_s vn = vec3_s(  0.645f  ,  0.315f  ,  0.2111f  );
		vn.normalize();
		qRot.setRotationAxis( vn ,   1.2455f   );
		printf("\n q rot =");
		qRot.print();
		printf("\n");

   mat44_s m;
   {
   mat44_s ms, mr, mt;
   ms.setScaling( 1.24f , 0.945f , 0.895f   );
   mr.setRotationQuaternion( qRot );
   mt.setTranslation(   1.35f , 1.364f , 0.658f        );

   m = mt * mr * ms;
   }
   
   	printf("\n matrix: \n");
	 m.print();


    gbv = vec3_s (   2.1544f , 1.648f , 3.16548f    );
    gbv.transformCoord(m);                


	}



   print_vectors( dxv , gbv );

};

//================================================
void test_transformNormal()
{
	PRINTFUNC
		DXV   dxv ;
	GBV  gbv ;

	printf("\n      D3DX: \n");
	// d3dx ===========================================
	{
		D3DXQUATERNION   qRot;
		D3DXVECTOR3 vn = D3DXVECTOR3(  0.645f  ,  0.315f  ,  0.2111f  );
		D3DXQuaternionRotationAxis( &qRot,
			&vn,
			1.2455f
			);
		printf("\n d3dx quat rot= %f  %f  %f  %f  \n", qRot.x, qRot.y, qRot.z , qRot.w  );



		D3DXMATRIX m;
		{
			D3DXMATRIX ms, mr, mt;
			D3DXMatrixScaling(&ms,  1.24f , 0.945f , 0.895f  );
			D3DXMatrixRotationQuaternion(&mr , &qRot  );
			D3DXMatrixTranslation( &mt , 1.35f , 1.364f , 0.658f   );

			m = mt * mr * ms;
		}



		printf("\n matrix: \n");
		printf("\n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n%f   %f   %f   %f  \n  ", 
			m._11, m._12, m._13, m._14, 
			m._21, m._22, m._23, m._24,
			m._31, m._32, m._33, m._34,	 
			m._41, m._42, m._43, m._44	 
			);


		D3DXVECTOR3 dxa  = DXV( 2.1544f , 1.648f , 3.16548f );
		D3DXVec3Normalize(&dxa , &dxa);
		D3DXVec3TransformNormal( &dxv,  
			&dxa,
			&m );

	}

	printf("\n      GB: \n");
	// gb =================================
	{
		gb::math::geom3d::Quaternion qRot;
		vec3_s vn = vec3_s(  0.645f  ,  0.315f  ,  0.2111f  );
		vn.normalize();
		qRot.setRotationAxis( vn ,   1.2455f   );
		printf("\n q rot =");
		qRot.print();
		printf("\n");

		mat44_s m;
		{
			mat44_s ms, mr, mt;
			ms.setScaling( 1.24f , 0.945f , 0.895f   );
			mr.setRotationQuaternion( qRot );
			mt.setTranslation(   1.35f , 1.364f , 0.658f        );

			m = mt * mr * ms;
		}

		printf("\n matrix: \n");
		m.print();


		gbv = vec3_s (   2.1544f , 1.648f , 3.16548f    );
		gbv.normalize();
		gbv.transformNormal(m);                


	}



	print_vectors( dxv , gbv );

 

};




//=============================================================
int main()
{
  test_cross();

  test_transformCoord();
	  test_transformNormal();



 printf(" \n\n  ######################   end program   ##################### \n");
  system("pause");
 return 0;
};