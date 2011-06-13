#include "d3d9pch.h"



#include <gb/macro.h>
#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
using  gb::graphics::d3d9::d3dx9_dynamic_load::CD3DX9_Dll_Loader;

#include "d3dxmesh.h"
#include <gb/fmath/fmath.h>
using namespace gb::fmath;
using namespace gb::fmath::geom3d;



namespace gb
{

namespace graphic
{

namespace d3d9
{

namespace d3dxmesh
{

//=========================================================================

 class D3DXMeshEx  : public ID3DXMeshEx {
 public:
   ID3DXMesh* m_pmesh;
   IDirect3DDevice9* m_device;
   UINT m_subsets;
   CD3DX9_Dll_Loader* m_pd3dxdll;
   Sphere m_sphere;
   AABB  m_aabb;
   
 
   D3DXMeshEx(
	   IDirect3DDevice9* device, 
	   CD3DX9_Dll_Loader* pd3dxdll  , 
	   const char* fname) 
     : m_pd3dxdll(pd3dxdll), m_device(device)  
   {
     assert(m_pd3dxdll);
     m_pmesh = NULL;  
	 m_subsets=0;

	 m_sphere.center.setzero();
	 m_sphere.radius = 0.0f;

	 m_aabb.min = m_aabb.max = vec3(0.0f,0.0f,0.0f);
   
   }
   
   virtual ~D3DXMeshEx() 
   {
      GB_SAFE_REL(m_pmesh);
	  m_subsets=0;	
   }
 

    virtual HRESULT drawSubset(UINT subset) const 
	{
	  if(!m_pmesh)
	  {
	   assert(false);
	   return E_FAIL;
	  }
	  if(subset >=m_subsets)
	  {
	    assert(false);
		return E_FAIL;
	  }
	  
	  HRESULT hr = m_pmesh->DrawSubset(subset);
	  return hr;
	}
	
    virtual HRESULT saveToFileA(const CHAR* fname) const 
	{
	 HRESULT hr =0;
	 #pragma message("  ????????????????  "  __FILE__)
	 assert(false);
	 
	  return hr;
	};
	
	virtual UINT getNumSubsets() const { return m_subsets; }
    virtual DWORD getFVF() const 
	{
	  assert(m_pmesh);
	 return m_pmesh->GetFVF();
	} 
	
    virtual UINT getNumBytesPerVertex() const 
	{
	 assert(m_pmesh);
	 return m_pmesh->GetNumBytesPerVertex();
	}
	
    virtual UINT getNumFaces () const 
	{
	 assert(m_pmesh);
	 return m_pmesh->GetNumFaces();
	}
	
    virtual UINT getNumVertices () const 
	{
	 assert(m_pmesh);
	 return m_pmesh->GetNumVertices();
	} 

	virtual const float* getBoundingSphere() const 
	{
	  return &m_sphere.center.x;
	}
  
	virtual const float* getBoundingBox() const 
	{
	   return &m_aabb.min.x;
	}

	 
};




// temp !!!!!!
D3DXMeshEx  g_mesh(NULL, NULL, "dfsdfds" );


//=========================================================================
}
}
}
}

// end file