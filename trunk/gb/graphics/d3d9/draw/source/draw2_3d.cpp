#include "d3d9pch.h"

#if ( defined(WIN32) && defined(_D3D9_H_) )

#include <gb/graphics/d3d9/draw/draw.h>
#include "internal.h"

#include <gb/color/color.h>
#include <gb/fmath/fmath.h>
using namespace gb::fmath;

#include <assert.h>

namespace gb 
{
namespace graphics 
{
namespace d3d9 
{
namespace draw
{
 
//=========================================================================


 
//=========================================================================
GB_D3D9_API HRESULT Draw3dPoints(IDirect3DDevice9* pdevice, 
					 const float* vec3Array_coord,
					 int num, 
					 float pointSize, 
					 D3DCOLOR color )
{
	HRESULT hr = 0;
	assert(pdevice);

 static const DWORD  FVF_3DPOINTS = D3DFVF_XYZ ;

	if(!pdevice)
	{
		return E_FAIL;
	}

	//  get old data
	DWORD dwoldfvf = 0;
	hr |= pdevice->GetFVF( &dwoldfvf );
	DWORD dwoldfillmode = 0;
	hr |= pdevice->GetRenderState( D3DRS_FILLMODE , &dwoldfillmode ); 
	D3DMATERIAL9 mat;
	hr |= pdevice->GetMaterial(&mat) ;
	float fPointSize = 1.0f;
	hr |= pdevice->GetRenderState(D3DRS_POINTSIZE , (DWORD*)&fPointSize );
		

	 

	if FAILED(hr)
	{
		return hr;
	}

	 // set data
	hr |= pdevice->SetFVF(FVF_3DPOINTS);
	hr |= pdevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_POINT );

	D3DMATERIAL9 newmat = mat;

	newmat.Emissive =  gb::color::make_d3dcolorvalue(color);


    hr |= pdevice->SetMaterial(&newmat);

	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&pointSize) );
 
	// draw
	hr |= pdevice->DrawPrimitiveUP(
		D3DPT_POINTLIST, num, 
		(void*)vec3Array_coord, 
		sizeof(D3DVECTOR) 
		);

	// restore data
   	hr |= pdevice->SetFVF( dwoldfvf );
	hr |= pdevice->SetRenderState(D3DRS_FILLMODE, dwoldfillmode );
   	hr |= pdevice->SetMaterial(&mat) ;
	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&fPointSize) );


	return hr;
};


//=====================================================================
// num - сколько точек
GB_D3D9_API HRESULT Draw3dLines(IDirect3DDevice9* pdevice, const float* vec3_coord, int num, D3DCOLOR color )
{
	HRESULT hr = S_OK;
	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}

	// read old data
	DWORD dwoldfvf = 0;
	hr |= pdevice->GetFVF( &dwoldfvf );
	D3DMATERIAL9 oldmat;
	hr |= pdevice->GetMaterial(&oldmat) ;

 // set data
	static const DWORD  VG_FVF_3DLINES     =  D3DFVF_XYZ ;
  hr |= pdevice->SetFVF(VG_FVF_3DLINES);
  D3DMATERIAL9 newmat = oldmat;
  newmat.Emissive = gb::color::make_d3dcolorvalue(color);
  hr |= pdevice->SetMaterial(&newmat);
 
 // do render
 hr |= pdevice->DrawPrimitiveUP(
	 D3DPT_LINESTRIP, 
	 num - 1, 
	 (void*)vec3_coord,
	 sizeof(float)*3 
	 );


 // restore old data
 	hr |= pdevice->SetFVF( dwoldfvf );
 hr |= pdevice->SetMaterial(&oldmat) ;

  return hr;
};
 
//=====================================================================
GB_D3D9_API HRESULT Draw3dRay(IDirect3DDevice9* pdevice, const float* vec3_orig, 
						const float* vec3_normal , D3DCOLOR color)
{
	HRESULT hr = S_OK;

	assert(pdevice);

	if(!pdevice)
	{
		 return E_FAIL;
	}
 



	gb::fmath::vec3  orig (vec3_orig);
 
	gb::fmath::vec3 varr[2];
	varr[0] = vec3_orig;

	static const float VG_MAX_INFINITY_VALUE = 3.4E30f;
 
	varr[1] = vec3_normal;
	varr[1].normalize();
	varr[1] *= VG_MAX_INFINITY_VALUE;

	varr[1] += orig;

  hr |= Draw3dLines(pdevice,varr[0], 2, color );
 
	return hr;
};

//=====================================================================
GB_D3D9_API HRESULT  Draw3dTraingle(
					IDirect3DDevice9* pdevice,
					const float* vec3_v1, 
					const float* vec3_v2, 
					const float* vec3_v3,
					D3DCOLOR color ) 
{
	HRESULT hr = 0;

	assert(pdevice);

	if(!pdevice)
	{
		return E_FAIL;
	}

 
	gb::fmath::vec3 varr[4];
	varr[0] =  vec3_v1;
	varr[1] =  vec3_v2;
	varr[2] =  vec3_v3;
	varr[3] =  vec3_v1;

	static const UINT nNumValue = 3;

  hr |=  Draw3dLines(pdevice, varr[0], 4,  color );

	return hr;
};


//=====================================================================
GB_D3D9_API HRESULT Draw3dAxiesAlignBoundBox(IDirect3DDevice9* pdevice,
								 const float* vec3_min, 
								 const float* vec3_max,
								 D3DCOLOR color ) 
{
	HRESULT hr = S_OK;

	assert(pdevice);

	if( !pdevice )
	{
		return E_FAIL;
	}

   // get old data
	DWORD dwoldfvf = 0;
	hr |=  pdevice->GetFVF(&dwoldfvf);
	DWORD dwoldpervertex = 0;
	hr |= pdevice->GetRenderState(D3DRS_COLORVERTEX , &dwoldpervertex  );
	D3DMATERIAL9 oldmat;
	hr |= pdevice->GetMaterial(&oldmat) ;

  const DWORD  FVF_3DLINES     =  (D3DFVF_XYZ | D3DFVF_DIFFUSE) ;

 class VERTEX
 {
	 public:

	 float x,y,z; 
	 D3DCOLOR color;  // хз  почему-то цвета по вершинам не фурычат.. хз ((
	 // сделал через материал.

	 inline VERTEX()
	 {
		 x=y=z=0.0f;
		 color = 0xffffffff;
	 }

	 void operator = (const vec3& v)
	 {
		 x=v.x;
		 y=v.y;
		 z=v.z;
	 }
 };
 
	//memset(vArrLine, 0, sizeof(vec3) * 8 );

	static const int nCount_quad_vert = 4;


	// set new data
	hr |= pdevice->SetFVF(FVF_3DLINES);
	hr |= pdevice->SetRenderState(D3DRS_COLORVERTEX , 1 );
    D3DMATERIAL9 newmat = oldmat;
	newmat.Emissive = gb::color::make_d3dcolorvalue(color);
	newmat.Diffuse  = gb::color::make_d3dcolorvalue(color);

	hr |= pdevice->SetMaterial(&newmat) ;



	const int NSIZEOF = sizeof( VERTEX );
	VERTEX vArrLine [8];

   for(int c=0; c<8; c++)
   {
	   vArrLine[c].color = color;
   }

	// vectors
	vec3 min = vec3_min;
	vec3 max = vec3_max;

	///  first quad ///
	/// 0
	vArrLine[0].x = min.x;
	vArrLine[0].y = min.y;
	vArrLine[0].z = min.z;


	/// 1
	vArrLine[1].x = max.x;
	vArrLine[1].y = min.y;
	vArrLine[1].z = min.z;


	/// 2
	vArrLine[2].x = max.x;
	vArrLine[2].y = max.y;
	vArrLine[2].z = min.z;


	/// 3
	vArrLine[3].x = min.x;
	vArrLine[3].y = max.y;
	vArrLine[3].z = min.z;


	/// 4
	vArrLine[4].x = min.x;
	vArrLine[4].y = min.y;
	vArrLine[4].z = min.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*) vArrLine, NSIZEOF);



	///  second quad ///
	/// 0
	vArrLine[0].x = max.x;
	vArrLine[0].y = max.y;
	vArrLine[0].z = max.z;

	/// 1
	vArrLine[1].x = max.x;
	vArrLine[1].y = min.y;
	vArrLine[1].z = max.z;


	// 2
	vArrLine[2].x = min.x;
	vArrLine[2].y = min.y;
	vArrLine[2].z = max.z;


	// 3
	vArrLine[3].x = min.x;
	vArrLine[3].y = max.y;
	vArrLine[3].z = max.z;


	// 4
	vArrLine[4].x = max.x;
	vArrLine[4].y = max.y;
	vArrLine[4].z = max.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*) vArrLine, NSIZEOF);



 // draw edges

	   const int nCount_border = 1;


	/// border 0    ///
	vArrLine[0].x = max.x;
	vArrLine[0].y = max.y;
	vArrLine[0].z = max.z;

	vArrLine[1].x = max.x;
	vArrLine[1].y = max.y;
	vArrLine[1].z = min.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*) vArrLine, NSIZEOF);



	/// border 1    ///
	vArrLine[0].x = min.x;
	vArrLine[0].y = max.y;
	vArrLine[0].z = max.z;

	vArrLine[1].x = min.x;
	vArrLine[1].y = max.y;
	vArrLine[1].z = min.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*) vArrLine, NSIZEOF);


	/// border 2   ///
	vArrLine[0].x = max.x;
	vArrLine[0].y = min.y;
	vArrLine[0].z = max.z;

	vArrLine[1].x = max.x;
	vArrLine[1].y = min.y;
	vArrLine[1].z = min.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*) vArrLine, NSIZEOF);


	/// border 3    ///
	vArrLine[0].x = min.x;
	vArrLine[0].y = min.y;
	vArrLine[0].z = min.z;

	vArrLine[1].x = min.x;
	vArrLine[1].y = min.y;
	vArrLine[1].z = max.z;

	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*) vArrLine, NSIZEOF);



	/// end ///
   	hr |=  pdevice->SetFVF( dwoldfvf );
	hr |= pdevice->SetRenderState(D3DRS_COLORVERTEX ,  dwoldpervertex );
	hr |= pdevice->SetMaterial(&oldmat) ;

	return hr;
};


//=======================================================================



//=========================================================================
GB_D3D9_API HRESULT Draw3dAxies(IDirect3DDevice9* pdevice, 
						const float* vec3_coord, float  axiesLen) 
{
	HRESULT hr = 0;

	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}

	// save data
	DWORD dwOldfvf = 0;
	hr |= pdevice->GetFVF(&dwOldfvf);
	D3DMATERIAL9 oldmat;
 	hr |= pdevice->GetMaterial(&oldmat);

	vec3 varr[2];
	D3DMATERIAL9 material;

	hr |= pdevice->SetFVF(D3DFVF_XYZ);



	// x
	if(vec3_coord)
	{
		varr[0] =  vec3_coord;
		varr[1] =  vec3_coord;
	}
	else
	{
		varr[0] = vec3(0.0f , 0.0f , 0.0f);
		varr[1] = vec3(0.0f , 0.0f , 0.0f);
	}

	varr[1].x += axiesLen;
	material.Emissive.r = 1.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 1.0f;
	hr |= pdevice->SetMaterial(&material);
	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(float)*3 );



	// y
	if(vec3_coord)
	{
		varr[0] =  vec3_coord;
		varr[1] =  vec3_coord;
	}
	else
	{
		varr[0] = vec3(0.0f , 0.0f , 0.0f);
		varr[1] = vec3(0.0f , 0.0f , 0.0f);
	}


	varr[1].y += axiesLen;
	material.Emissive.r = 0.0f;
	material.Emissive.g = 1.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 1.0f;
	hr |= pdevice->SetMaterial(&material);
	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(float)*3  );



	// z
	if(vec3_coord)
	{
		varr[0] =  vec3_coord;
		varr[1] =  vec3_coord;
	}
	else
	{
		varr[0] = vec3(0.0f , 0.0f , 0.0f);
		varr[1] = vec3(0.0f , 0.0f , 0.0f);
	}


	varr[1].z += axiesLen;
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 1.0f;
	material.Emissive.a = 1.0f;
	hr |= pdevice->SetMaterial(&material);
	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(float)*3  );


	// restore
	hr |= pdevice->SetMaterial(&oldmat);
	hr |= pdevice->SetFVF(dwOldfvf);
 
 
	return hr;
};



//========================================================================


}
}
}
}

#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file