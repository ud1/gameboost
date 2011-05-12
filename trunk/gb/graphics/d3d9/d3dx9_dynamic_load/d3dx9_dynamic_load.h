

#pragma once

#include <d3d9.h>



/******************
d3dx9_undef   = 0 ,
d3dx9_24,
d3dx9_25,
d3dx9_26,
d3dx9_27,
d3dx9_28,
d3dx9_29,
d3dx9_30,
d3dx9_31,
d3dx9_32,
d3dx9_33,
d3dx9_34,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
******************/





namespace dl
{
  
  
  //-------------------------------------------------------------------------

//! \brief   ѕолучить файл d3dx dll по номеру версии   
void  makeD3DX9dllFilename_by_version(std::string& strOut, unsigned int vers, bool bDebugV=false)
{
  strOut = "";
  strOut += "d3dx9";
  
  if(bDebugV)
  {
    strOut += "d";
  }

  strOut += "_";
  
  char buf [32];
  sprintf( buf , "%02i" , vers );
  strOut += buf;
  strOut += ".dll";

  // temp mon
  if(vers<10)
  {
   int _stop =0;
  }
 
}





bool checkDllExistsA (const char* fname)   
{    
    return ::GetFileAttributesA(fname) != DWORD(-1);
}
 
bool checkExistsDll(const char* sDllFilename)
{
   std::string sfullpath ;
   char bufsysdir[MAX_PATH];
 
  if(! ::GetSystemDirectoryA(bufsysdir, MAX_PATH ))
  {
   throw (std::runtime_error("system error"));
  }
  
  sfullpath = bufsysdir;
  sfullpath += '\\';
  sfullpath += sDllFilename;
  
  if( checkDllExistsA(sfullpath.c_str() ) )
  {
    return true;
  
  }  
 
   return false;
}
 
 // получить самую последнюю версию установленой библиотеки.
bool getInstaledD3DXlastVersion(unsigned int* piOutVers)
 {
   *piOutVers  =0;
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	   *piOutVers = cvers;
	   return true;
	  }

  } 
 
    return false;
 }


void print_d3dx9_dll_info()
{
	std::string str;
  for(unsigned int c=50; c>=0; c--)
  {
	makeD3DX9dllFilename_by_version(str, c);
	if(  checkExistsDll (str.c_str() ) )
	{
	
	 printf( str.c_str() );
	printf("\n");
	}

  
  }




   printf("\n   END. \n");
}


 //  получит все инсталированые версии d3dx dll в системе.
bool getInstaledD3DXallVersion(std::vector<unsigned int>& versions)
 {
   bool result = false;
	versions.clear();
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	    versions.push_back(cvers);
	   result =  true;
	  }

  } 
 
    return  result;
 }



 




HMODULE loadDllLastVersion(unsigned int* piOutVers )
{
 
	if(piOutVers) *piOutVers = 0;
   if( !getInstaledD3DXlastVersion( piOutVers ) )
   {
   
     return 0;
   }
   
   std::string dllfname;
   makeD3DX9dllFilename_by_version(dllfname, *piOutVers );
   
   HMODULE hm = 0 ;
   hm = ::LoadLibraryA(dllfname.c_str() );
   if(hm)
   {
    /// error load.  none
   }

   return hm;
}  
 


 
//////////////////////////////////////////////

class DFunctions {
public:



// typedef HRESULT (__stdcall *TFunc_xxx)(int arg);
 
	struct MARK_BEGIN_FUNC_DECL {};
 
 typedef BOOL (__stdcall *TFunc_D3DXCheckVersion)(UINT D3DSDKVersion, UINT D3DXSDKVersion);
 
// 
//==================================================================== 
//                       general purpose function 
//====================================================================
// 
 
 typedef HRESULT (__stdcall *TFunc_D3DXCreateBuffer)( DWORD NumBytes, LPD3DXBUFFER * ppBuffer);
 
 
 typedef HRESULT  (__stdcall *TFunc_D3DXCreateFontA)(
  LPDIRECT3DDEVICE9 pDevice,
  INT Height,
  UINT Width,
  UINT Weight,
  UINT MipLevels,
  BOOL Italic,
  DWORD CharSet,
  DWORD OutputPrecision,
  DWORD Quality,
  DWORD PitchAndFamily,
  CHAR* pFacename,
  LPD3DXFONT * ppFont
);

 typedef HRESULT  (__stdcall *TFunc_D3DXCreateFontW)(
  LPDIRECT3DDEVICE9 pDevice,
  INT Height,
  UINT Width,
  UINT Weight,
  UINT MipLevels,
  BOOL Italic,
  DWORD CharSet,
  DWORD OutputPrecision,
  DWORD Quality,
  DWORD PitchAndFamily,
  WCHAR* pFacename,
  LPD3DXFONT * ppFont
);




 typedef HRESULT (__stdcall *TFunc_D3DXCreateFontIndirectA)(
  LPDIRECT3DDEVICE9 pDevice,
  CONST D3DXFONT_DESCA * pDesc,
  LPD3DXFONT * ppFont
);

 typedef HRESULT (__stdcall *TFunc_D3DXCreateFontIndirectW)(
  LPDIRECT3DDEVICE9 pDevice,
  CONST D3DXFONT_DESCW * pDesc,
  LPD3DXFONT * ppFont
);



 
 typedef HRESULT (__stdcall *TFunc_D3DXCreateLine)(
  LPDIRECT3DDEVICE9 pDevice,
  LPD3DXLINE* ppLine
);

 typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToEnvMap)(
  LPDIRECT3DDEVICE9 pDevice,
  UINT Size,
  UINT MipLevels,
  D3DFORMAT Format,
  BOOL DepthStencil,
  D3DFORMAT DepthStencilFormat,
  ID3DXRenderToEnvMap** ppRenderToEnvMap
);

 typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToSurface)(
  LPDIRECT3DDEVICE9 pDevice,
  UINT Width,
  UINT Height,
  D3DFORMAT Format,
  BOOL DepthStencil,
  D3DFORMAT DepthStencilFormat,
  ID3DXRenderToSurface** ppRenderToSurface
);


 typedef HRESULT (__stdcall *TFunc_D3DXCreateSprite)(
  LPDIRECT3DDEVICE9 pDevice,
  LPD3DXSPRITE * ppSprite
);


 typedef HRESULT (__stdcall *TFunc_D3DXDebugMute)(
  BOOL Mute
);


 typedef HRESULT (__stdcall *TFunc_D3DXGetDriverLevel)(
  LPDIRECT3DDEVICE9 pDevice
);



// 
//==================================================================== 
//                         D3DX math
//====================================================================
// 




typedef D3DXMATRIX* ( __stdcall  *TFunc_D3DXMatrixMultiply)(
  D3DXMATRIX * pOut,
  CONST D3DXMATRIX * pM1,
  CONST D3DXMATRIX * pM2
);



typedef D3DXMATRIX* ( __stdcall  *TFunc_D3DXMatrixInverse)(
  D3DXMATRIX * pOut,
  FLOAT * pDeterminant,
  CONST D3DXMATRIX * pM
);






//=========================================================================
//             D3DX MESH 
//=========================================================================


typedef  HRESULT (__stdcall * TFunc_D3DXCleanMesh)(
  D3DXCLEANTYPE CleanType,
  LPD3DXMESH pMeshIn,
  CONST DWORD * pAdjacencyIn,
  LPD3DXMESH * ppMeshOut,
  DWORD * pAdjacencyOut,
  LPD3DXBUFFER * ppErrorsAndWarnings
);




typedef  HRESULT (__stdcall * TFunc_D3DXComputeBoundingBox)(
  CONST D3DXVECTOR3 * pFirstPosition,
  DWORD NumVertices,
  DWORD dwStride,
  D3DXVECTOR3 * pMin,
  D3DXVECTOR3 * pMax
);


typedef  HRESULT (__stdcall *TFunc_D3DXComputeBoundingSphere)(
  CONST D3DXVECTOR3 * pFirstPosition,
  DWORD NumVertices,
  DWORD dwStride,
  D3DXVECTOR3 * pCenter,
  FLOAT * pRadius
);



typedef  HRESULT (__stdcall *TFunc_D3DXComputeNormals)(
  LPD3DXBASEMESH pMesh,
  CONST DWORD * pAdjacency
);


typedef  HRESULT (__stdcall *TFunc_D3DXComputeTangent)(
  LPD3DXMESH Mesh,
  DWORD TexStageIndex,
  DWORD TangentIndex,
  DWORD BinormIndex,
  DWORD Wrap,
  CONST DWORD * pAdjacency
);


typedef  HRESULT (__stdcall *TFunc_D3DXComputeTangentFrame)(
  ID3DXMesh * pMesh,
  DWORD dwOptions
);


typedef  HRESULT (__stdcall *TFunc_D3DXComputeTangentFrameEx)(
  ID3DXMesh * pMesh,
  DWORD dwTextureInSemantic,
  DWORD dwTextureInIndex,
  DWORD dwUPartialOutSemantic,
  DWORD dwUPartialOutIndex,
  DWORD dwVPartialOutSemantic,
  DWORD dwVPartialOutIndex,
  DWORD dwNormalOutSemantic,
  DWORD dwNormalOutIndex,
  DWORD dwOptions,
  CONST DWORD * pdwAdjacency,
  FLOAT fPartialEdgeThreshold,
  FLOAT fSingularPointThreshold,
  FLOAT fNormalEdgeThreshold,
  ID3DXMesh ** ppMeshOut,
  ID3DXBuffer ** ppVertexMapping
);


typedef  HRESULT (__stdcall *TFunc_D3DXConcatenateMeshes)(
  LPD3DXMESH * ppMeshes,
  UINT NumMeshes,
  DWORD Options,
  CONST D3DXMATRIX * pGeomXForms,
  CONST D3DXMATRIX * pTextureXForms,
  CONST D3DVERTEXELEMENT9 * pDecl,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXMESH * ppMeshOut
);


  //  ..........
  
  
typedef  HRESULT (__stdcall *TFunc_D3DXCreateMesh)(
  DWORD NumFaces,
  DWORD NumVertices,
  DWORD Options,
  CONST LPD3DVERTEXELEMENT9 * pDeclaration,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXMESH * ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXCreateMeshFVF)(
  DWORD NumFaces,
  DWORD NumVertices,
  DWORD Options,
  DWORD FVF,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXMESH * ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXDeclaratorFromFVF)( DWORD FVF,
  D3DVERTEXELEMENT9 Declaration[MAX_FVF_DECL_SIZE]
);

typedef  UINT (__stdcall *TFunc_D3DXGetFVFVertexSize)(
  DWORD FVF
);


typedef  HRESULT (__stdcall *TFunc_D3DXIntersect)(
  LPD3DXBASEMESH pMesh,
  CONST D3DXVECTOR3 * pRayPos,
  CONST D3DXVECTOR3 * pRayDir,
  BOOL * pHit,
  DWORD * pFaceIndex,
  FLOAT * pU,
  FLOAT * pV,
  FLOAT * pDist,
  LPD3DXBUFFER * ppAllHits,
  DWORD * pCountOfHits
);


typedef  HRESULT (__stdcall *TFunc_D3DXIntersectSubset)(
  LPD3DXBASEMESH pMesh,
  DWORD AttribId,
  CONST D3DXVECTOR3 * pRayPos,
  CONST D3DXVECTOR3 * pRayDir,
  BOOL * pHit,
  DWORD * pFaceIndex,
  FLOAT * pU,
  FLOAT * pV,
  FLOAT * pDist,
  LPD3DXBUFFER * ppAllHits,
  DWORD * pCountOfHits
);


typedef  BOOL (__stdcall *TFunc_D3DXIntersectTri)(
  CONST D3DXVECTOR3 * p0,
  CONST D3DXVECTOR3 * p1,
  CONST D3DXVECTOR3 * p2,
  CONST D3DXVECTOR3 * pRayPos,
  CONST D3DXVECTOR3 * pRayDir,
  FLOAT * pU,
  FLOAT * pV,
  FLOAT * pDist
);


typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromX)(
  LPCTSTR pFilename,
  DWORD Options,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXBUFFER * ppAdjacency,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  DWORD * pNumMaterials,
  LPD3DXMESH * ppMesh
);



typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromXInMemory)(
  LPCVOID Memory,
  DWORD SizeOfMemory,
  DWORD Options,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXBUFFER * ppAdjacency,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  DWORD * pNumMaterials,
  LPD3DXMESH * ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromXof)(
  LPD3DXFILEDATA pxofMesh,
  DWORD Options,
  LPDIRECT3DDEVICE9 pDevice,
  LPD3DXBUFFER * ppAdjacency,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  DWORD * pNumMaterials,
  LPD3DXMESH * ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromXResource)(
  HMODULE Module,
  LPCSTR Name,
  LPCSTR Type,
  DWORD Options,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXBUFFER * ppAdjacency,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  DWORD * pNumMaterials,
  LPD3DXMESH * ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXLoadPatchMeshFromXof)(
  LPD3DXFILEDATA pxofMesh,
  DWORD Options,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  PDWORD pNumMaterials,
  LPD3DXPATCHMESH* ppMesh
);


typedef  HRESULT (__stdcall *TFunc_D3DXLoadSkinMeshFromXof)(
  LPD3DXFILEDATA pxofMesh,
  DWORD Options,
  LPDIRECT3DDEVICE9 pD3DDevice,
  LPD3DXBUFFER * ppAdjacency,
  LPD3DXBUFFER * ppMaterials,
  LPD3DXBUFFER * ppEffectInstances,
  DWORD * pMatOut,
  LPD3DXSKININFO * ppSkinInfo,
  LPD3DXMESH * ppMesh
);



typedef  HRESULT (__stdcall *TFunc_D3DXOptimizeFaces)(
  LPCVOID pIndices,
  UINT NumFaces,
  UINT NumVertices,
  BOOL Indices32Bit,
  DWORD * pFaceRemap
);


typedef  HRESULT (__stdcall *TFunc_D3DXOptimizeVertices)(
  LPCVOID pIndices,
  UINT NumFaces,
  UINT NumVertices,
  BOOL Indices32Bit,
  DWORD * pVertexRemap
);


typedef  HRESULT (__stdcall *TFunc_D3DXRectPatchSize)(
  CONST FLOAT * pfNumSegs,
  DWORD * pdwTriangles,
  DWORD * pwdVertices
);


typedef  HRESULT (__stdcall *TFunc_D3DXSaveMeshToX)(
  LPCTSTR pFilename,
  LPD3DXMESH pMesh,
  CONST DWORD * pAdjacency,
  CONST D3DXMATERIAL * pMaterials,
  CONST D3DXEFFECTINSTANCE * pEffectInstances,
  DWORD NumMaterials,
  DWORD Format
);


typedef  HRESULT (__stdcall *TFunc_D3DXSimplifyMesh)(
  LPD3DXMESH pMesh,
  CONST DWORD * pAdjacency,
  CONST D3DXATTRIBUTEWEIGHTS * pVertexAttributeWeights,
  CONST FLOAT * pVertexWeights,
  DWORD MinValue,
  DWORD Options,
  LPD3DXMESH * ppMesh
);


typedef  void (__stdcall *TFunc_D3DXSplitMesh)(
  LPD3DXMESH pMeshIn,
  CONST DWORD * pAdjacencyIn,
  CONST DWORD MaxSize,
  CONST DWORD Options,
  DWORD * pMeshesOut,
  LPD3DXBUFFER * ppMeshArrayOut,
  LPD3DXBUFFER * ppAdjacencyArrayOut,
  LPD3DXBUFFER * ppFaceRemapArrayOut,
  LPD3DXBUFFER * ppVertRemapArrayOut
);

typedef  HRESULT (__stdcall *TFunc_D3DXTriPatchSize)(
  CONST LOAT * pfNumSegs,
  DWORD * pdwTriangles,
  DWORD * pdwVertices
);


typedef  HRESULT (__stdcall *TFunc_D3DXValidMesh(
  LPD3DXMESH pMeshIn,
  CONST DWORD * pAdjacency,
  LPD3DXBUFFER * ppErrorsAndWarnings
);


typedef  HRESULT (__stdcall *TFunc_D3DXValidPatchMesh)(
  LPD3DXPATCHMESH  pMeshIn,
  DWORD * pNumDegenerateVertices,
  DWORD * pNumDegeneratePatches,
  LPD3DXBUFFER * ppErrorsAndWarnings
);


typedef  HRESULT (__stdcall *TFunc_D3DXWeldVertices)(
  LPD3DXMESH pMesh,
  DWORD Flags,
  CONST D3DXWeldEpsilons * pEpsilons,
  CONST DWORD * pAdjacencyIn,
  DWORD * pAdjacencyOut,
  DWORD * pFaceRemap,
  LPD3DXBUFFER * ppVertexRemap
);




//=========================================================================
//                D3DX      Shader Functions   
//=========================================================================


typedef HRESULT (__stdcall *TFunc_D3DXAssembleShader)(
  LPCSTR pSrcData,
  UINT SrcDataLen,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER * ppErrorMsgs
);

typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromFile)(
  LPCTSTR pSrcFile,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER * ppErrorMsgs
);


typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromResource)(
  HMODULE hSrcModule,
  LPCTSTR pSrcResource,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER * ppErrorMsgs
);


typedef HRESULT (__stdcall *TFunc_D3DXCompileShader)(
  LPCSTR pSrcData,
  UINT srcDataLen,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pFunctionName,
  LPCSTR pProfile,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER* ppErrorMsgs,
  LPD3DXCONSTANTTABLE * ppConstantTable
);


typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromFile)(
  LPCSTR pSrcFile,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pFunctionName,
  LPCSTR pProfile,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER * ppErrorMsgs,
  LPD3DXCONSTANTTABLE * ppConstantTable
);


typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromResource)(
  HMODULE hSrcModule,
  LPCSTR pSrcResource,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pFunctionName,
  LPCSTR pProfile,
  DWORD Flags,
  LPD3DXBUFFER* ppShader,
  LPD3DXBUFFER * ppErrorMsgs,
  LPD3DXCONSTANTTABLE * ppConstantTable
);


typedef HRESULT (__stdcall *TFunc_D3DXCreateTextureShader)(
  CONST DWORD * pFunction,
  LPD3DXTEXTURESHADER * ppTextureShader
);


typedef HRESULT (__stdcall *TFunc_D3DXDisassembleShader)(
  CONST DWORD * pShader,
  BOOL EnableColorCode,
  LPCSTR pComments,
  LPD3DXBUFFER * ppDisassembly
);

typedef HRESULT (__stdcall *TFunc_D3DXFindShaderComment)(
  CONST DWORD* pFunction,
  DWORD FourCC,
  LPCVOID* ppData,
  UINT* pSizeInBytes
);

typedef LPCSTR (__stdcall *TFunc_D3DXGetPixelShaderProfile)(
  LPDIRECT3DDEVICE9 pDevice
);


typedef HRESULT (__stdcall *TFunc_D3DXGetShaderConstantTable)(
  CONST DWORD* pFunction,
  LPD3DXCONSTANTTABLE*  ppConstantTable
);

typedef HRESULT (__stdcall *TFunc_D3DXGetShaderConstantTableEx)(
  CONST DWORD* pFunction,
  DWORD Flags,
  LPD3DXCONSTANTTABLE*  ppConstantTable
);


typedef HRESULT (__stdcall *TFunc_D3DXGetShaderInputSemantics)(
  CONST DWORD* pFunction,
  D3DXSEMANTIC* pSemantics,
  UINT* pCount
);

typedef HRESULT (__stdcall *TFunc_D3DXGetShaderOutputSemantics)(
  CONST DWORD* pFunction,
  D3DXSEMANTIC* pSemantics,
  UINT* pCount
);


typedef HRESULT (__stdcall *TFunc_D3DXGetShaderSamplers)(
  CONST DWORD* pFunction,
  LPCSTR* pSamplers,
  UINT* pCount
);


typedef UINT (__stdcall *TFunc_D3DXGetShaderSize)(
  CONST DWORD * pFunction
);

typedef DWORD (__stdcall *TFunc_D3DXGetShaderVersion(
  CONST DWORD* pFunction
);


typedef LPCSTR (__stdcall *TFunc_D3DXGetVertexShaderProfile)(
  LPDIRECT3DDEVICE9 pDevice
);

typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShader)(
  LPCSTR pSrcData,
  UINT SrcDataSize,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPD3DXBUFFER* ppShaderText,
  LPD3DXBUFFER* ppErrorMsgs
);

typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromFile)(
  LPCSTR pSrcFile,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPD3DXBUFFER* ppShaderText,
  LPD3DXBUFFER* ppErrorMsgs
);


typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromResource)(
  HMODULE hSrcModule,
  LPCSTR pSrcResource,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  LPD3DXBUFFER* ppShaderText,
  LPD3DXBUFFER* ppErrorMsgs
);






//=========================================================================
//                D3DX      EFFECT   
//=========================================================================


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffect)(
  LPDIRECT3DDEVICE9 pDevice,
  LPCVOID pSrcData,
  UINT SrcDataLen,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectEx)(
  LPDIRECT3DDEVICE9 pDevice,
  LPCVOID pSrcData,
  UINT SrcDataLen,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pSkipConstants,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompiler)(
  LPCSTR pSrcData,
  UINT SrcDataLen,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTCOMPILER * ppEffectCompiler,
  LPD3DXBUFFER * ppParseErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromFile)(
  LPCTSTR pSrcFile,
  CONST D3DXMACRO* pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTCOMPILER * ppEffectCompiler,
  LPD3DXBUFFER * ppParseErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromResource)(
  HMODULE hSrcModule,
  LPCTSTR pSrcResource,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTCOMPILER * ppEffectCompiler,
  LPD3DXBUFFER * ppParseErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFile)(
  LPDIRECT3DDEVICE9 pDevice,
  LPCTSTR pSrcFile,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFileEx)(
  LPDIRECT3DDEVICE9 pDevice,
  LPCTSTR pSrcFile,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pSkipConstants,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResource)(
  LPDIRECT3DDEVICE9 pDevice,
  HMODULE hSrcModule,
  LPCTSTR pSrcResource,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);

typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResourceEx)(
  LPDIRECT3DDEVICE9 pDevice,
  HMODULE hSrcModule,
  LPCTSTR pSrcResource,
  CONST D3DXMACRO * pDefines,
  LPD3DXINCLUDE pInclude,
  LPCSTR pSkipConstants,
  DWORD Flags,
  LPD3DXEFFECTPOOL pPool,
  LPD3DXEFFECT * ppEffect,
  LPD3DXBUFFER * ppCompilationErrors
);


typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectPool)(
  LPD3DXEFFECTPOOL* ppPool
);


typedef HRESULT  (__stdcall *TFunc_D3DXDisassembleEffect)(
  LPD3DXEFFECT pEffect,
  BOOL EnableColorCode,
  LPD3DXBUFFER * ppDisassembly
);


 
 
 
 
 

 //----------------------------------------------------------------------
 //
 //

 struct MARK_BEGIN_MEMBERS_FUNC_POINTER {};

 TFunc_D3DXCheckVersion m_TFunc_D3DXCheckVersion;
 
 
 //   -----------   general purpose function   ------------------
 
 
 TFunc_D3DXCreateBuffer        m_TFunc_D3DXCreateBuffer;

 TFunc_D3DXCreateFontA         m_TFunc_D3DXCreateFontA;
 TFunc_D3DXCreateFontW         m_TFunc_D3DXCreateFontW;

 TFunc_D3DXCreateFontIndirectA    m_TFunc_D3DXCreateFontIndirectA;
 TFunc_D3DXCreateFontIndirectW    m_TFunc_D3DXCreateFontIndirectW;

 TFunc_D3DXCreateLine              m_TFunc_D3DXCreateLine;
 TFunc_D3DXCreateRenderToEnvMap    m_TFunc_D3DXCreateRenderToEnvMap;
 TFunc_D3DXCreateRenderToSurface   m_TFunc_D3DXCreateRenderToSurface;
 TFunc_D3DXCreateSprite            m_TFunc_D3DXCreateSprite;
 TFunc_D3DXDebugMute               m_TFunc_D3DXDebugMute;
 TFunc_D3DXGetDriverLevel          m_TFunc_D3DXGetDriverLevel;
 
 //---------------
 
 

	DFunctions()
	{
		memset(&m_TFunc_D3DXCheckVersion, 0 , sizeof(DFunctions)  );
	
	}

 

 void handleNotFoundAddr()
 {
 
   int stop = 0;
 }

 int GetProcAddr(const HMODULE hm)
 {
    void* ptr = NULL;
	const int NERROR = -1;

 
 m_TFunc_D3DXCheckVersion = (TFunc_D3DXCheckVersion)::GetProcAddress(hm,"D3DXCheckVersion");
 if(!m_TFunc_D3DXCheckVersion)   {  handleNotFoundAddr();  return NERROR; }


 m_TFunc_D3DXCreateBuffer = (  TFunc_D3DXCreateBuffer  )::GetProcAddress(hm,  "D3DXCreateBuffer"  );
 if(!m_TFunc_D3DXCreateBuffer ) {  handleNotFoundAddr();  return NERROR; }


  m_TFunc_D3DXCreateFontA = (  TFunc_D3DXCreateFontA  )::GetProcAddress(hm,  "D3DXCreateFontA"  );
 if(! m_TFunc_D3DXCreateFontA ) {  handleNotFoundAddr();  return NERROR; }

  m_TFunc_D3DXCreateFontW = (  TFunc_D3DXCreateFontW  )::GetProcAddress(hm,  "D3DXCreateFontW"  );
 if(! m_TFunc_D3DXCreateFontW ) {  handleNotFoundAddr();  return NERROR; }

 

 m_TFunc_D3DXCreateFontIndirectA = (  TFunc_D3DXCreateFontIndirectA  )::GetProcAddress(hm,  "D3DXCreateFontIndirectA"  );
 if(!m_TFunc_D3DXCreateFontIndirectA ) {  handleNotFoundAddr();  return NERROR; }
 
 m_TFunc_D3DXCreateFontIndirectW = (  TFunc_D3DXCreateFontIndirectW  )::GetProcAddress(hm,  "D3DXCreateFontIndirectW"  );
 if(!m_TFunc_D3DXCreateFontIndirectW ) {  handleNotFoundAddr();  return NERROR; }



  m_TFunc_D3DXCreateLine = (  TFunc_D3DXCreateLine  )::GetProcAddress(hm,  "D3DXCreateLine"  );
 if(!m_TFunc_D3DXCreateLine ) {  handleNotFoundAddr();  return NERROR; }
 

 m_TFunc_D3DXCreateRenderToEnvMap = (  TFunc_D3DXCreateRenderToEnvMap  )::GetProcAddress(hm, "D3DXCreateRenderToEnvMap"  );
 if(!m_TFunc_D3DXCreateRenderToEnvMap ) {  handleNotFoundAddr();  return NERROR; }


 
  m_TFunc_D3DXCreateRenderToSurface = (TFunc_D3DXCreateRenderToSurface)::GetProcAddress(hm,"D3DXCreateRenderToSurface");
 if(!m_TFunc_D3DXCreateRenderToSurface) {  handleNotFoundAddr();  return NERROR; }
 
 
   m_TFunc_D3DXCreateSprite = (TFunc_D3DXCreateSprite)::GetProcAddress(hm,"D3DXCreateSprite");
 if(!m_TFunc_D3DXCreateSprite) {  handleNotFoundAddr();  return NERROR; }
 
 
 m_TFunc_D3DXDebugMute = (TFunc_D3DXDebugMute)::GetProcAddress(hm,"D3DXDebugMute");
 if(!m_TFunc_D3DXDebugMute) {  handleNotFoundAddr();  return NERROR; }
 
  m_TFunc_D3DXGetDriverLevel = (TFunc_D3DXGetDriverLevel)::GetProcAddress(hm,"D3DXGetDriverLevel");
 if(!m_TFunc_D3DXGetDriverLevel) {  handleNotFoundAddr();  return NERROR; }
 
 
  // m_TFunc_xxxxxxxxxxx = (TFunc_xxxxxxxxxxx)::GetProcAddress(hm,"xxxxxxxxxxx");
 //if(!m_TFunc_xxxxxxxxxxx) return   NERROR;
 
 
 
  return 0;
 }
 
 
 
};
 
 
}
// end namespace




// end file