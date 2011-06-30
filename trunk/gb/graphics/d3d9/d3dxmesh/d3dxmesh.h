/** \file
 \brief Ќебольша€ надстройка над ID3DXMeth
 
  \todo убрать абстрактник .. сделать простой класс.
*/

#if ( defined(WIN32) && defined(__D3DX9_H__) )
#pragma once

namespace gb
{

namespace graphic
{

namespace d3d9
{

namespace d3dxmesh
{

//---------------------------------------------------------------------------


	class ID3DXMeshEx {
	public:
	    virtual ~ID3DXMeshEx() {}
	  
	    virtual HRESULT drawSubset(UINT subset) const =0;
	    virtual HRESULT saveToFileA(const CHAR* fname) const =0;
		
		virtual UINT  getNumSubsets() const =0;
	    virtual DWORD getFVF() const =0; 
	    virtual UINT  getNumBytesPerVertex() const =0;
	    virtual UINT  getNumFaces () const =0;
	    virtual UINT  getNumVertices () const =0;
		
		//! get bound sphere XYZR
		virtual const float* getBoundingSphere() const =0;
		//! get bound box XYZXYZ
		virtual const float* getBoundingBox() const =0;

		
		

	  };
 

 

//---------------------------------------------------------------------------
}
}
}
}

#endif
// end file