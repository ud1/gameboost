/** \file
 \brief Декларации типов точек входа в загруженную D3DX9  DLL


 \author ksacvet777
*/

#if ( defined(WIN32) && defined(GB_D3D9)  )


#pragma once

#ifndef __GB_D3DX9_DYNAMIC_LOAD_H__
   #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ.   ВКЛЮЧАЙТЕ:  #include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
#endif



#include <windows.h>


namespace  gb
{

namespace  graphics
{

namespace  d3d9
{

namespace d3dx9_dynamic_load
{


 //------------------------------------------------------------------

	//! \brief  Сборка - точки входа в D3DX9 dll .
	class Functions {
	public:
 

		typedef BOOL (__stdcall *TFunc_D3DXCheckVersion)(UINT D3DSDKVersion, UINT D3DXSDKVersion);

		// 
		//================================================================= 
		//                       general purpose function 
		//=================================================================
		// 

		typedef HRESULT (__stdcall *TFunc_D3DXCreateBuffer)( DWORD NumBytes, LPD3DXBUFFER * ppBuffer);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateFontA)(LPDIRECT3DDEVICE9 pDevice,
			INT Height,	   	UINT Width,	UINT Weight, UINT MipLevels, BOOL Italic,
			DWORD CharSet, 	DWORD OutputPrecision, 	DWORD Quality,	DWORD PitchAndFamily,
			const CHAR* pFacename,	LPD3DXFONT * ppFont		);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateFontW)(
			LPDIRECT3DDEVICE9 pDevice, 	INT Height,	UINT Width,	 UINT Weight, 	UINT MipLevels,
			BOOL Italic,  DWORD CharSet, DWORD OutputPrecision,
			DWORD Quality, DWORD PitchAndFamily, const WCHAR* pFacename, LPD3DXFONT * ppFont );




		typedef HRESULT (__stdcall *TFunc_D3DXCreateFontIndirectA)(	LPDIRECT3DDEVICE9 pDevice,
			CONST D3DXFONT_DESCA * pDesc, 	LPD3DXFONT * ppFont	  	);

		typedef HRESULT (__stdcall *TFunc_D3DXCreateFontIndirectW)(
			LPDIRECT3DDEVICE9 pDevice, 	CONST D3DXFONT_DESCW * pDesc, LPD3DXFONT * ppFont );




		typedef HRESULT (__stdcall *TFunc_D3DXCreateLine)(
			LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE* ppLine);

		typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToEnvMap)(LPDIRECT3DDEVICE9 pDevice,
			UINT Size,  UINT MipLevels,	 D3DFORMAT Format, BOOL DepthStencil,
			D3DFORMAT DepthStencilFormat, ID3DXRenderToEnvMap** ppRenderToEnvMap  );

		typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToSurface)(
			LPDIRECT3DDEVICE9 pDevice,    UINT Width, UINT Height, D3DFORMAT Format,
			BOOL DepthStencil, D3DFORMAT DepthStencilFormat, ID3DXRenderToSurface** ppRenderToSurface );


		typedef HRESULT (__stdcall *TFunc_D3DXCreateSprite)(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE * ppSprite);


		typedef HRESULT (__stdcall *TFunc_D3DXDebugMute)(	BOOL Mute);


		typedef HRESULT (__stdcall *TFunc_D3DXGetDriverLevel)( LPDIRECT3DDEVICE9 pDevice);



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

		typedef BOOL (__stdcall *TFunc_D3DXBoxBoundProbe)(
			CONST D3DXVECTOR3 * pMin,
			CONST D3DXVECTOR3 * pMax,
			CONST D3DXVECTOR3 * pRayPosition,
			CONST D3DXVECTOR3 * pRayDirection
			);



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

		





		typedef  HRESULT (__stdcall *TFunc_D3DXConvertMeshSubsetToSingleStrip)(
			LPD3DXBASEMESH MeshIn,
			DWORD AttribId,
			DWORD IBOptions,
			LPDIRECT3DINDEXBUFFER9 * ppIndexBuffer,
			DWORD * pNumIndices
			);

		typedef  HRESULT (__stdcall *TFunc_D3DXConvertMeshSubsetToStrips)(
			LPD3DXBASEMESH MeshIn,
			DWORD AttribId,
			DWORD IBOptions,
			LPDIRECT3DINDEXBUFFER9 * ppIndexBuffer,
			DWORD * pNumIndices,
			LPD3DXBUFFER * ppStripLengths,
			DWORD * pNumStrips
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





		typedef  HRESULT (__stdcall *TFunc_D3DXCreateNPatchMesh)(
			LPD3DXMESH pMeshSysMem,
			LPD3DXPATCHMESH * pPatchMesh
			);

		typedef  HRESULT (__stdcall *TFunc_D3DXCreatePatchMesh)(
			CONST D3DXPATCHINFO * pInfo,
			DWORD dwNumPatches,
			DWORD dwNumVertices,
			DWORD dwOptions,
			CONST D3DVERTEXELEMENT9 * pDecl,
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPD3DXPATCHMESH * pPatchMesh
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXDeclaratorFromFVF)( DWORD FVF,
			D3DVERTEXELEMENT9 Declaration[MAX_FVF_DECL_SIZE]
		);



		typedef  HRESULT (__stdcall *TFunc_D3DXCreateSkinInfo)(
			DWORD NumVertices,
			CONST D3DVERTEXELEMENT9 * pDeclaration,
			DWORD NumBones,
			LPD3DXSKININFO * ppSkinInfo
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXFVFFromDeclarator)(
			CONST LPD3DVERTEXELEMENT9 * pDeclaration,
			DWORD * pFVF
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXGenerateOutputDecl)(
			D3DVERTEXELEMENT9 * pOutput,
			CONST D3DVERTEXELEMENT9 * pInput
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXGetDeclLength)(
			CONST D3DVERTEXELEMENT9 * pDecl
			);

		typedef  HRESULT (__stdcall *TFunc_D3DXGetDeclVertexSize)(
			CONST D3DVERTEXELEMENT9 * pDecl,
			DWORD Stream
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


		typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromXA)(
			const CHAR* pFilename,
			DWORD Options,
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPD3DXBUFFER * ppAdjacency,
			LPD3DXBUFFER * ppMaterials,
			LPD3DXBUFFER * ppEffectInstances,
			DWORD * pNumMaterials,
			LPD3DXMESH * ppMesh
			);

		typedef  HRESULT (__stdcall *TFunc_D3DXLoadMeshFromXW)(
			const WCHAR* pFilename,
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


		typedef  HRESULT (__stdcall *TFunc_D3DXSaveMeshToXA)(
			const CHAR* pFilename,
			LPD3DXMESH pMesh,
			CONST DWORD * pAdjacency,
			CONST D3DXMATERIAL * pMaterials,
			CONST D3DXEFFECTINSTANCE * pEffectInstances,
			DWORD NumMaterials,
			DWORD Format
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXSaveMeshToXW)(
			const WCHAR* pFilename,
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


		typedef  BOOL (__stdcall  *TFunc_D3DXSphereBoundProbe)(
			CONST D3DXVECTOR3 * pCenter,
			FLOAT Radius,
			CONST D3DXVECTOR3 * pRayPosition,
			CONST D3DXVECTOR3 * pRayDirection
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


		typedef  HRESULT (__stdcall *TFunc_D3DXTessellateNPatches)(
			LPD3DXMESH pMeshIn,
			CONST DWORD * pAdjacencyIn,
			FLOAT NumSegs,
			BOOL QuadraticInterpNormals,
			LPD3DXMESH * ppMeshOut,
			LPD3DXBUFFER * ppAdjacencyOut
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXTessellateRectPatch)(
			LPDIRECT3DVERTEXBUFFER9 pVB,
			CONST FLOAT * pNumSegs,
			CONST D3DVERTEXELEMENT9 * pInDecl,
			CONST D3DRECTPATCH_INFO * pRectPatchInfo,
			LPD3DXMESH pMesh
			);

		typedef  HRESULT (__stdcall *TFunc_D3DXTessellateTriPatch)(
			LPDIRECT3DVERTEXBUFFER9 pVB,
			CONST FLOAT * pNumSegs,
			CONST D3DVERTEXELEMENT9 * pInDecl,
			CONST D3DTRIPATCH_INFO * pTriPatchInfo,
			LPD3DXMESH pMesh
			);




		typedef  HRESULT (__stdcall *TFunc_D3DXTriPatchSize)(
			CONST FLOAT * pfNumSegs,
			DWORD * pdwTriangles,
			DWORD * pdwVertices
			);


		typedef  HRESULT (__stdcall *TFunc_D3DXValidMesh)(
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
			CONST D3DXWELDEPSILONS * pEpsilons,
			CONST DWORD * pAdjacencyIn,
			DWORD * pAdjacencyOut,
			DWORD * pFaceRemap,
			LPD3DXBUFFER * ppVertexRemap
			);


		//==============================================================
		//        Shape Drawing Functions  
		//==============================================================


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateBox)(
			LPDIRECT3DDEVICE9 pDevice,
			FLOAT Width,
			FLOAT Height,
			FLOAT Depth,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency );


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateCylinder)(
			LPDIRECT3DDEVICE9 pDevice,
			FLOAT Radius1,
			FLOAT Radius2,
			FLOAT Length,
			UINT Slices,
			UINT Stacks,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency );



		typedef  HRESULT (__stdcall *TFunc_D3DXCreatePolygon)(
			LPDIRECT3DDEVICE9 pDevice,
			FLOAT Length,
			UINT Sides,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency );


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateSphere)(
			LPDIRECT3DDEVICE9 pDevice,
			FLOAT Radius,
			UINT Slices,
			UINT Stacks,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency  );


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateTeapot)(
			LPDIRECT3DDEVICE9 pDevice,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency  );


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateTextA)(
			LPDIRECT3DDEVICE9 pDevice,
			HDC hDC,
			const CHAR* pText,   
			FLOAT Deviation,
			FLOAT Extrusion,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency,
			LPGLYPHMETRICSFLOAT pGlyphMetrics	);


		typedef  HRESULT (__stdcall *TFunc_D3DXCreateTextW)(
			LPDIRECT3DDEVICE9 pDevice,
			HDC hDC,
			const WCHAR* pText,	
			FLOAT Deviation,
			FLOAT Extrusion,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency,
			LPGLYPHMETRICSFLOAT pGlyphMetrics	);

		typedef  HRESULT (__stdcall *TFunc_D3DXCreateTorus)(
			LPDIRECT3DDEVICE9 pDevice,
			FLOAT InnerRadius,
			FLOAT OuterRadius,
			UINT Sides,
			UINT Rings,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency  );










		//==============================================================
		//          Shader Functions   
		//==============================================================


		typedef HRESULT (__stdcall *TFunc_D3DXAssembleShader)(
			LPCSTR pSrcData,
			UINT SrcDataLen,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs
			);

		typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromFileA)(
			const CHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs
			);

		typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromFileW)(
			const WCHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs
			);





		typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromResourceA)(
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs
			);

		typedef HRESULT (__stdcall *TFunc_D3DXAssembleShaderFromResourceW)(
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
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


#pragma message("ks777:  d3dx dyn load:: хз  проверить описание строк на юникод/анси для TFunc_D3DXCompileShaderFromFile  "  __FILE__)

		typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromFileA)(
			const CHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			const CHAR* pFunctionName,
			const CHAR* pProfile,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs,
			LPD3DXCONSTANTTABLE * ppConstantTable
			) ;

		typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromFileW)(
			const WCHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			const WCHAR* pFunctionName,
			const WCHAR* pProfile,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs,
			LPD3DXCONSTANTTABLE * ppConstantTable
			) ;







		typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromResourceA)(
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			const CHAR* pFunctionName,
			const CHAR* pProfile,
			DWORD Flags,
			LPD3DXBUFFER* ppShader,
			LPD3DXBUFFER * ppErrorMsgs,
			LPD3DXCONSTANTTABLE * ppConstantTable
			);



		typedef HRESULT (__stdcall *TFunc_D3DXCompileShaderFromResourceW)(
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			const WCHAR* pFunctionName,
			const WCHAR* pProfile,
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

		typedef DWORD (__stdcall *TFunc_D3DXGetShaderVersion)(
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

		typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromFileA)(
			const CHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			LPD3DXBUFFER* ppShaderText,
			LPD3DXBUFFER* ppErrorMsgs
			);



		typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromFileW)(
			const WCHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			LPD3DXBUFFER* ppShaderText,
			LPD3DXBUFFER* ppErrorMsgs
			);
 
		typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromResourceA)(
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			LPD3DXBUFFER* ppShaderText,
			LPD3DXBUFFER* ppErrorMsgs
			);

		typedef HRESULT (__stdcall *TFunc_D3DXPreprocessShaderFromResourceW)(
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			LPD3DXBUFFER* ppShaderText,
			LPD3DXBUFFER* ppErrorMsgs
			);






		//==================================================================
		//                D3DX      EFFECT   
		//=================================================================


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


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromFileA)(
			const CHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTCOMPILER * ppEffectCompiler,
			LPD3DXBUFFER * ppParseErrors
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromFileW)(
			const WCHAR* pSrcFile,
			CONST D3DXMACRO* pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTCOMPILER * ppEffectCompiler,
			LPD3DXBUFFER * ppParseErrors
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromResourceA)(
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTCOMPILER * ppEffectCompiler,
			LPD3DXBUFFER * ppParseErrors
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectCompilerFromResourceW)(
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTCOMPILER * ppEffectCompiler,
			LPD3DXBUFFER * ppParseErrors
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFileA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFileW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

#pragma message("ks777: d3dx9 dyn load:: проверить параметры строки на корректность !!   "  __FILE__ )

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFileExA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			const CHAR*  pSkipConstants,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromFileExW)(	 
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			LPCSTR pSkipConstants,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

 

   #pragma message("ks777: d3dx9 dyn load:: проверить параметры строки на корректность !!   "  __FILE__ )

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResourceA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResourceW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,						 
			const WCHAR* pSrcResource,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);


    #pragma message("ks777: d3dx9 dyn load:: проверить параметры строки на корректность !!   "  __FILE__ )

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResourceExA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DXMACRO * pDefines,
			LPD3DXINCLUDE pInclude,
			LPCSTR pSkipConstants,
			DWORD Flags,
			LPD3DXEFFECTPOOL pPool,
			LPD3DXEFFECT * ppEffect,
			LPD3DXBUFFER * ppCompilationErrors
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateEffectFromResourceExW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
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



	//----------------------------------------------------------------
					
		typedef HRESULT  (__stdcall *TFunc_D3DXCreateBox)(
		  LPDIRECT3DDEVICE9 pDevice,
		  FLOAT Width,
		  FLOAT Height,
		  FLOAT Depth,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCylinder)(
		  LPDIRECT3DDEVICE9 pDevice,
		  FLOAT Radius1,
		  FLOAT Radius2,
		  FLOAT Length,
		  UINT Slices,
		  UINT Stacks,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreatePolygon)(
		  LPDIRECT3DDEVICE9 pDevice,
		  FLOAT Length,
		  UINT Sides,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateSphere)(
		  LPDIRECT3DDEVICE9 pDevice,
		  FLOAT Radius,
		  UINT Slices,
		  UINT Stacks,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);

				
		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTeapot)(
		  LPDIRECT3DDEVICE9 pDevice,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextA)(
		  LPDIRECT3DDEVICE9 pDevice,
		  HDC hDC,
		  const CHAR* pText,
		  FLOAT Deviation,
		  FLOAT Extrusion,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency,
		  LPGLYPHMETRICSFLOAT pGlyphMetrics);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextW)(
			LPDIRECT3DDEVICE9 pDevice,
			HDC hDC,
			const WCHAR* pText,
			FLOAT Deviation,
			FLOAT Extrusion,
			LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency,
			LPGLYPHMETRICSFLOAT pGlyphMetrics);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTorus)(
		  LPDIRECT3DDEVICE9 pDevice,
		  FLOAT InnerRadius,
		  FLOAT OuterRadius,
		  UINT Sides,
		  UINT Rings,
		  LPD3DXMESH * ppMesh,
		  LPD3DXBUFFER * ppAdjacency);


		//
		//------------------------------------------
		//          texture function
		//------------------------------------------
		//
 

		typedef HRESULT  (__stdcall *TFunc_D3DXCheckCubeTextureRequirements)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT * pSize,
			UINT * pNumMipLevels,
			DWORD Usage,
			D3DFORMAT * pFormat,
			D3DPOOL Pool
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCheckTextureRequirements)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT * pWidth,
			UINT * pHeight,
			UINT * pNumMipLevels,
			DWORD Usage,
			D3DFORMAT * pFormat,
			D3DPOOL Pool
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCheckVolumeTextureRequirements)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT * pWidth,
			UINT * pHeight,
			UINT * pDepth,
			UINT * pNumMipLevels,
			DWORD Usage,
			D3DFORMAT * pFormat,
			D3DPOOL Pool
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXComputeNormalMap)(
			LPDIRECT3DTEXTURE9 pTexture,
			LPDIRECT3DTEXTURE9 pSrcTexture,
			CONST PALETTEENTRY * pSrcPalette,
			DWORD Flags,
			DWORD Channel,
			FLOAT Amplitude
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTexture)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileExA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileExW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileInMemory)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromFileInMemoryEx)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromResourceA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromResourceW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromResourceExA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateCubeTextureFromResourceExW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			UINT Size,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTexture)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			LPDIRECT3DTEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			LPDIRECT3DTEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileExA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR*  pSrcFile,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileExW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileInMemory)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromFileInMemoryEx)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DTEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromResourceA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromResourceW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			LPDIRECT3DTEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromResourceExA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR*  pSrcResource,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DTEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateTextureFromResourceExW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR*  pSrcResource,
			UINT Width,
			UINT Height,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DTEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTexture)(
			LPDIRECT3DDEVICE9 pDevice,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);





		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR* pSrcFile,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR* pSrcFile,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileExA)(
			LPDIRECT3DDEVICE9 pDevice,
			const CHAR*  pSrcFile,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DVOLUMETEXTURE9 * ppTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileExW)(
			LPDIRECT3DDEVICE9 pDevice,
			const WCHAR*  pSrcFile,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DVOLUMETEXTURE9 * ppTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileInMemory)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcFile,
			UINT SrcData,
			LPDIRECT3DVOLUMETEXTURE9 ppVolumeTexture
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromFileInMemoryEx)(
			LPDIRECT3DDEVICE9 pDevice,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromResourceA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromResourceW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);




		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromResourceExA)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXCreateVolumeTextureFromResourceExW)(
			LPDIRECT3DDEVICE9 pDevice,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			UINT Width,
			UINT Height,
			UINT Depth,
			UINT MipLevels,
			DWORD Usage,
			D3DFORMAT Format,
			D3DPOOL Pool,
			DWORD Filter,
			DWORD MipFilter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo,
			PALETTEENTRY * pPalette,
			LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXFillCubeTexture)(
			LPDIRECT3DCUBETEXTURE9 pTexture,
			LPD3DXFILL3D pFunction,
			LPVOID pData
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXFillCubeTextureTX)(
			LPDIRECT3DCUBETEXTURE9 pTexture,
			LPD3DXTEXTURESHADER pTextureShader
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXFillTexture)(
			LPDIRECT3DTEXTURE9 pTexture,
			LPD3DXFILL2D pFunction,
			LPVOID pData
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXFillTextureTX)(
			LPDIRECT3DTEXTURE9 pTexture,
			LPD3DXTEXTURESHADER pTextureShader
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXFillVolumeTexture)(
			LPDIRECT3DVOLUMETEXTURE9 pTexture,
			LPD3DXFILL3D pFunction,
			LPVOID pData
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXFillVolumeTextureTX)(
			LPDIRECT3DVOLUMETEXTURE9 pTexture,
			LPD3DXTEXTURESHADER pTextureShader
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXFilterTexture)(
			LPDIRECT3DBASETEXTURE9 pBaseTexture,
			CONST PALETTEENTRY * pPalette,
			UINT SrcLevel,
			DWORD MipFilter
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXGetImageInfoFromFileA)(
			const CHAR*  pSrcFile,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXGetImageInfoFromFileW)(
			const WCHAR* pSrcFile,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXGetImageInfoFromFileInMemory)(
			LPCVOID pSrcData,
			UINT SrcDataSize,
			D3DXIMAGE_INFO * pSrcInfo
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXGetImageInfoFromResourceA)(
			HMODULE hSrcModule,
			const CHAR*  pSrcFile,
			D3DXIMAGE_INFO * pSrcInfo
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXGetImageInfoFromResourceW)(
			HMODULE hSrcModule,
			const WCHAR* pSrcFile,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromFileA)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY* pDestPalette,
			CONST RECT* pDestRect,
			const CHAR* pSrcFile,
			CONST RECT* pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO* pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromFileW)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY* pDestPalette,
			CONST RECT* pDestRect,
			const WCHAR* pSrcFile,
			CONST RECT* pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO* pSrcInfo
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromFileInMemory)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY * pDestPalette,
			CONST RECT * pDestRect,
			LPCVOID pSrcData,
			UINT SrcData,
			CONST RECT * pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromMemory)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY * pDestPalette,
			CONST RECT * pDestRect,
			LPCVOID pSrcMemory,
			D3DFORMAT SrcFormat,
			UINT SrcPitch,
			CONST PALETTEENTRY * pSrcPalette,
			CONST RECT * pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromResourceA)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY * pDestPalette,
			CONST RECT * pDestRect,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST RECT * pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromResourceW)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY * pDestPalette,
			CONST RECT * pDestRect,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			CONST RECT * pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXLoadSurfaceFromSurface)(
			LPDIRECT3DSURFACE9 pDestSurface,
			CONST PALETTEENTRY * pDestPalette,
			CONST RECT * pDestRect,
			LPDIRECT3DSURFACE9 pSrcSurface,
			CONST PALETTEENTRY * pSrcPalette,
			CONST RECT * pSrcRect,
			DWORD Filter,
			D3DCOLOR ColorKey
			);




		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromFileA)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			const CHAR* pSrcFile,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromFileW)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			const WCHAR* pSrcFile,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromFileInMemory)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			LPCVOID pSrcData,
			UINT SrcDataSize,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromMemory)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			LPCVOID pSrcMemory,
			D3DFORMAT SrcFormat,
			UINT SrcRowPitch,
			UINT SrcSlicePitch,
			CONST PALETTEENTRY * pSrcPalette,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromResourceA)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			HMODULE hSrcModule,
			const CHAR* pSrcResource,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromResourceW)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			HMODULE hSrcModule,
			const WCHAR* pSrcResource,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey,
			D3DXIMAGE_INFO * pSrcInfo
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXLoadVolumeFromVolume)(
			LPDIRECT3DVOLUME9 pDestVolume,
			CONST PALETTEENTRY * pDestPalette,
			CONST D3DBOX * pDestBox,
			LPDIRECT3DVOLUME9 pSrcVolume,
			CONST PALETTEENTRY * pSrcPalette,
			CONST D3DBOX * pSrcBox,
			DWORD Filter,
			D3DCOLOR ColorKey
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveSurfaceToFileA)(
			const CHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DSURFACE9 pSrcSurface,
			CONST PALETTEENTRY * pSrcPalette,
			CONST RECT * pSrcRect
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveSurfaceToFileW)(
			const WCHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DSURFACE9 pSrcSurface,
			CONST PALETTEENTRY * pSrcPalette,
			CONST RECT * pSrcRect
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveSurfaceToFileInMemory)(
			LPD3DXBUFFER * ppDestBuf,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DSURFACE9 pSrcSurface,
			CONST PALETTEENTRY * pSrcPalette,
			CONST RECT * pSrcRect
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveTextureToFileA)(
			const CHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DBASETEXTURE9 pSrcTexture,
			CONST PALETTEENTRY * pSrcPalette
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveTextureToFileW)(
			const WCHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DBASETEXTURE9 pSrcTexture,
			CONST PALETTEENTRY * pSrcPalette
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXSaveTextureToFileInMemory)(
			LPD3DXBUFFER * ppDestBuf,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DBASETEXTURE9 pSrcTexture,
			CONST PALETTEENTRY * pSrcPalette
			);


		typedef HRESULT  (__stdcall *TFunc_D3DXSaveVolumeToFileA)(
			const CHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DVOLUME9 pSrcVolume,
			CONST PALETTEENTRY * pSrcPalette,
			CONST D3DBOX * pSrcBox
			);

		typedef HRESULT  (__stdcall *TFunc_D3DXSaveVolumeToFileW)(
			const WCHAR* pDestFile,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DVOLUME9 pSrcVolume,
			CONST PALETTEENTRY * pSrcPalette,
			CONST D3DBOX * pSrcBox
			);



		typedef HRESULT  (__stdcall *TFunc_D3DXSaveVolumeToFileInMemory)(
			LPD3DXBUFFER * ppDestBuf,
			D3DXIMAGE_FILEFORMAT DestFormat,
			LPDIRECT3DVOLUME9 pSrcVolume,
			CONST PALETTEENTRY * pSrcPalette,
			CONST D3DBOX * pSrcBox
			);








		//---------------------------------------------------
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

		//------------------    math    --------------------

	    TFunc_D3DXMatrixMultiply		  m_TFunc_D3DXMatrixMultiply;
	    TFunc_D3DXMatrixInverse			  m_TFunc_D3DXMatrixInverse;
							   
		//------------------     mesh    ---------------------

		TFunc_D3DXBoxBoundProbe            m_TFunc_D3DXBoxBoundProbe;
		TFunc_D3DXCleanMesh				   m_TFunc_D3DXCleanMesh   ;
		TFunc_D3DXComputeBoundingBox       m_TFunc_D3DXComputeBoundingBox     ;

		TFunc_D3DXComputeBoundingSphere	  m_TFunc_D3DXComputeBoundingSphere  ;

		TFunc_D3DXComputeNormals	    m_TFunc_D3DXComputeNormals    ;
		TFunc_D3DXComputeTangent	    m_TFunc_D3DXComputeTangent    ;
		TFunc_D3DXComputeTangentFrame	m_TFunc_D3DXComputeTangentFrame    ;

		TFunc_D3DXComputeTangentFrameEx  m_TFunc_D3DXComputeTangentFrameEx    ; 
		TFunc_D3DXConcatenateMeshes	     m_TFunc_D3DXConcatenateMeshes    ;






        TFunc_D3DXConvertMeshSubsetToSingleStrip  m_TFunc_D3DXConvertMeshSubsetToSingleStrip; 
	    TFunc_D3DXConvertMeshSubsetToStrips		  m_TFunc_D3DXConvertMeshSubsetToStrips;

		TFunc_D3DXCreateMesh	 m_TFunc_D3DXCreateMesh   ;
		TFunc_D3DXCreateMeshFVF  m_TFunc_D3DXCreateMeshFVF    ;

 
        TFunc_D3DXCreatePatchMesh     m_TFunc_D3DXCreatePatchMesh; 

		TFunc_D3DXCreateNPatchMesh    m_TFunc_D3DXCreateNPatchMesh;

		TFunc_D3DXDeclaratorFromFVF   m_TFunc_D3DXDeclaratorFromFVF  ;

 
		TFunc_D3DXCreateSkinInfo       m_TFunc_D3DXCreateSkinInfo;
		TFunc_D3DXFVFFromDeclarator	   m_TFunc_D3DXFVFFromDeclarator;
		TFunc_D3DXGenerateOutputDecl   m_TFunc_D3DXGenerateOutputDecl;

		TFunc_D3DXGetDeclLength	     m_TFunc_D3DXGetDeclLength;
		TFunc_D3DXGetDeclVertexSize  m_TFunc_D3DXGetDeclVertexSize;

 

		TFunc_D3DXGetFVFVertexSize	  m_TFunc_D3DXGetFVFVertexSize   ;


		TFunc_D3DXIntersect		    m_TFunc_D3DXIntersect  ;
		TFunc_D3DXIntersectSubset   m_TFunc_D3DXIntersectSubset   ;
		TFunc_D3DXIntersectTri      m_TFunc_D3DXIntersectTri     ;

		TFunc_D3DXLoadMeshFromXA	  m_TFunc_D3DXLoadMeshFromXA   ;
		TFunc_D3DXLoadMeshFromXW	  m_TFunc_D3DXLoadMeshFromXW   ;

		TFunc_D3DXLoadMeshFromXInMemory  m_TFunc_D3DXLoadMeshFromXInMemory    ;

		TFunc_D3DXLoadMeshFromXof		  m_TFunc_D3DXLoadMeshFromXof  ;
		TFunc_D3DXLoadMeshFromXResource   m_TFunc_D3DXLoadMeshFromXResource  ;
		TFunc_D3DXLoadPatchMeshFromXof    m_TFunc_D3DXLoadPatchMeshFromXof   ;

		TFunc_D3DXLoadSkinMeshFromXof	  m_TFunc_D3DXLoadSkinMeshFromXof   ;
		TFunc_D3DXOptimizeFaces		      m_TFunc_D3DXOptimizeFaces  ;
		TFunc_D3DXOptimizeVertices		  m_TFunc_D3DXOptimizeVertices  ;
		TFunc_D3DXRectPatchSize			  m_TFunc_D3DXRectPatchSize   ;

		TFunc_D3DXSaveMeshToXA			 m_TFunc_D3DXSaveMeshToXA ;
		TFunc_D3DXSaveMeshToXW			 m_TFunc_D3DXSaveMeshToXW ;

		TFunc_D3DXSimplifyMesh			 m_TFunc_D3DXSimplifyMesh   ;

		TFunc_D3DXSphereBoundProbe       m_TFunc_D3DXSphereBoundProbe;

		TFunc_D3DXSplitMesh			 m_TFunc_D3DXSplitMesh ;

 
		TFunc_D3DXTessellateNPatches   m_TFunc_D3DXTessellateNPatches;	 
		TFunc_D3DXTessellateRectPatch  m_TFunc_D3DXTessellateRectPatch; 
		TFunc_D3DXTessellateTriPatch   m_TFunc_D3DXTessellateTriPatch;


		TFunc_D3DXTriPatchSize		 m_TFunc_D3DXTriPatchSize   ;


		TFunc_D3DXValidMesh			   m_TFunc_D3DXValidMesh  ;
		TFunc_D3DXValidPatchMesh	   m_TFunc_D3DXValidPatchMesh  ;

		TFunc_D3DXWeldVertices		  m_TFunc_D3DXWeldVertices   ;


		//-----------------   shaders    -----------------------------


		TFunc_D3DXAssembleShader    m_TFunc_D3DXAssembleShader    ;

		TFunc_D3DXAssembleShaderFromFileA   m_TFunc_D3DXAssembleShaderFromFileA; 
		TFunc_D3DXAssembleShaderFromFileW   m_TFunc_D3DXAssembleShaderFromFileW; 

		TFunc_D3DXAssembleShaderFromResourceA    m_TFunc_D3DXAssembleShaderFromResourceA;
		TFunc_D3DXAssembleShaderFromResourceW    m_TFunc_D3DXAssembleShaderFromResourceW;

		TFunc_D3DXCompileShader             m_TFunc_D3DXCompileShader; 

		TFunc_D3DXCompileShaderFromFileA    m_TFunc_D3DXCompileShaderFromFileA;
		TFunc_D3DXCompileShaderFromFileW    m_TFunc_D3DXCompileShaderFromFileW;

		TFunc_D3DXCompileShaderFromResourceA   m_TFunc_D3DXCompileShaderFromResourceA;
		TFunc_D3DXCompileShaderFromResourceW   m_TFunc_D3DXCompileShaderFromResourceW;

		TFunc_D3DXCreateTextureShader    m_TFunc_D3DXCreateTextureShader;
		TFunc_D3DXDisassembleShader    m_TFunc_D3DXDisassembleShader; 
		TFunc_D3DXFindShaderComment	  m_TFunc_D3DXFindShaderComment;


		TFunc_D3DXGetPixelShaderProfile    m_TFunc_D3DXGetPixelShaderProfile;
		TFunc_D3DXGetShaderConstantTable    m_TFunc_D3DXGetShaderConstantTable;
		TFunc_D3DXGetShaderConstantTableEx    m_TFunc_D3DXGetShaderConstantTableEx;
 
		TFunc_D3DXGetShaderInputSemantics	   m_TFunc_D3DXGetShaderInputSemantics;

		TFunc_D3DXGetShaderOutputSemantics   m_TFunc_D3DXGetShaderOutputSemantics; 
		TFunc_D3DXGetShaderSamplers    m_TFunc_D3DXGetShaderSamplers;
		TFunc_D3DXGetShaderSize   m_TFunc_D3DXGetShaderSize;


		TFunc_D3DXGetShaderVersion    m_TFunc_D3DXGetShaderVersion; 
		TFunc_D3DXGetVertexShaderProfile     m_TFunc_D3DXGetVertexShaderProfile;
		TFunc_D3DXPreprocessShader	  m_TFunc_D3DXPreprocessShader;

		TFunc_D3DXPreprocessShaderFromFileA     m_TFunc_D3DXPreprocessShaderFromFileA;
		TFunc_D3DXPreprocessShaderFromFileW     m_TFunc_D3DXPreprocessShaderFromFileW;

		TFunc_D3DXPreprocessShaderFromResourceA	  m_TFunc_D3DXPreprocessShaderFromResourceA;
		TFunc_D3DXPreprocessShaderFromResourceW	  m_TFunc_D3DXPreprocessShaderFromResourceW;


     	//-------------------     effect       -------------------


      TFunc_D3DXCreateEffect     m_TFunc_D3DXCreateEffect;
	  TFunc_D3DXCreateEffectEx      m_TFunc_D3DXCreateEffectEx;
	  TFunc_D3DXCreateEffectCompiler     m_TFunc_D3DXCreateEffectCompiler;

   TFunc_D3DXCreateEffectCompilerFromFileA     m_TFunc_D3DXCreateEffectCompilerFromFileA; 
   TFunc_D3DXCreateEffectCompilerFromFileW	   m_TFunc_D3DXCreateEffectCompilerFromFileW;

   TFunc_D3DXCreateEffectCompilerFromResourceA     m_TFunc_D3DXCreateEffectCompilerFromResourceA;  
   TFunc_D3DXCreateEffectCompilerFromResourceW	   m_TFunc_D3DXCreateEffectCompilerFromResourceW;

   TFunc_D3DXCreateEffectFromFileA     m_TFunc_D3DXCreateEffectFromFileA;  
   TFunc_D3DXCreateEffectFromFileW	   m_TFunc_D3DXCreateEffectFromFileW;

  TFunc_D3DXCreateEffectFromFileExA      m_TFunc_D3DXCreateEffectFromFileExA;
  TFunc_D3DXCreateEffectFromFileExW	     m_TFunc_D3DXCreateEffectFromFileExW;

   TFunc_D3DXCreateEffectFromResourceA     m_TFunc_D3DXCreateEffectFromResourceA;  
   TFunc_D3DXCreateEffectFromResourceW     m_TFunc_D3DXCreateEffectFromResourceW;

	TFunc_D3DXCreateEffectFromResourceExA     m_TFunc_D3DXCreateEffectFromResourceExA;  
	TFunc_D3DXCreateEffectFromResourceExW     m_TFunc_D3DXCreateEffectFromResourceExW;

   TFunc_D3DXCreateEffectPool     m_TFunc_D3DXCreateEffectPool; 
   TFunc_D3DXDisassembleEffect    m_TFunc_D3DXDisassembleEffect;

   
   //------------    Shape Drawing Functions    -----------------------
   
    TFunc_D3DXCreateBox       m_TFunc_D3DXCreateBox;
	TFunc_D3DXCreateCylinder   m_TFunc_D3DXCreateCylinder;
    TFunc_D3DXCreatePolygon     m_TFunc_D3DXCreatePolygon;
	TFunc_D3DXCreateSphere   m_TFunc_D3DXCreateSphere;
    TFunc_D3DXCreateTeapot      m_TFunc_D3DXCreateTeapot;

	TFunc_D3DXCreateTextA    m_TFunc_D3DXCreateTextA; 
	TFunc_D3DXCreateTextW    m_TFunc_D3DXCreateTextW; 

    TFunc_D3DXCreateTorus   m_TFunc_D3DXCreateTorus;


	//---------------  textured functions  --------------------




	TFunc_D3DXCheckCubeTextureRequirements  m_TFunc_D3DXCheckCubeTextureRequirements;
	TFunc_D3DXCheckTextureRequirements  m_TFunc_D3DXCheckTextureRequirements;

	TFunc_D3DXCheckVolumeTextureRequirements  m_TFunc_D3DXCheckVolumeTextureRequirements;
	TFunc_D3DXComputeNormalMap  m_TFunc_D3DXComputeNormalMap;
	TFunc_D3DXCreateCubeTexture  m_TFunc_D3DXCreateCubeTexture;

	TFunc_D3DXCreateCubeTextureFromFileA  m_TFunc_D3DXCreateCubeTextureFromFileA;
	TFunc_D3DXCreateCubeTextureFromFileW  m_TFunc_D3DXCreateCubeTextureFromFileW;

	TFunc_D3DXCreateCubeTextureFromFileExA  m_TFunc_D3DXCreateCubeTextureFromFileExA;
	TFunc_D3DXCreateCubeTextureFromFileExW  m_TFunc_D3DXCreateCubeTextureFromFileExW;

	TFunc_D3DXCreateCubeTextureFromFileInMemory  m_TFunc_D3DXCreateCubeTextureFromFileInMemory;
	TFunc_D3DXCreateCubeTextureFromFileInMemoryEx  m_TFunc_D3DXCreateCubeTextureFromFileInMemoryEx;

	TFunc_D3DXCreateCubeTextureFromResourceA  m_TFunc_D3DXCreateCubeTextureFromResourceA;
	TFunc_D3DXCreateCubeTextureFromResourceW  m_TFunc_D3DXCreateCubeTextureFromResourceW;

	TFunc_D3DXCreateCubeTextureFromResourceExA  m_TFunc_D3DXCreateCubeTextureFromResourceExA;
	TFunc_D3DXCreateCubeTextureFromResourceExW  m_TFunc_D3DXCreateCubeTextureFromResourceExW;

	TFunc_D3DXCreateTexture  m_TFunc_D3DXCreateTexture;

	TFunc_D3DXCreateTextureFromFileA  m_TFunc_D3DXCreateTextureFromFileA;
	TFunc_D3DXCreateTextureFromFileW  m_TFunc_D3DXCreateTextureFromFileW;

	TFunc_D3DXCreateTextureFromFileExA  m_TFunc_D3DXCreateTextureFromFileExA;
	TFunc_D3DXCreateTextureFromFileExW  m_TFunc_D3DXCreateTextureFromFileExW;

	TFunc_D3DXCreateTextureFromFileInMemory  m_TFunc_D3DXCreateTextureFromFileInMemory;
	TFunc_D3DXCreateTextureFromFileInMemoryEx  m_TFunc_D3DXCreateTextureFromFileInMemoryEx;

	TFunc_D3DXCreateTextureFromResourceA  m_TFunc_D3DXCreateTextureFromResourceA;
	TFunc_D3DXCreateTextureFromResourceW  m_TFunc_D3DXCreateTextureFromResourceW;

	TFunc_D3DXCreateTextureFromResourceExA  m_TFunc_D3DXCreateTextureFromResourceExA;
	TFunc_D3DXCreateTextureFromResourceExW  m_TFunc_D3DXCreateTextureFromResourceExW;

	TFunc_D3DXCreateVolumeTexture  m_TFunc_D3DXCreateVolumeTexture;

	TFunc_D3DXCreateVolumeTextureFromFileA  m_TFunc_D3DXCreateVolumeTextureFromFileA;
	TFunc_D3DXCreateVolumeTextureFromFileW m_TFunc_D3DXCreateVolumeTextureFromFileW ;

	TFunc_D3DXCreateVolumeTextureFromFileExA  m_TFunc_D3DXCreateVolumeTextureFromFileExA;
	TFunc_D3DXCreateVolumeTextureFromFileExW  m_TFunc_D3DXCreateVolumeTextureFromFileExW;

	TFunc_D3DXCreateVolumeTextureFromFileInMemory  m_TFunc_D3DXCreateVolumeTextureFromFileInMemory;
	TFunc_D3DXCreateVolumeTextureFromFileInMemoryEx m_TFunc_D3DXCreateVolumeTextureFromFileInMemoryEx ;

	TFunc_D3DXCreateVolumeTextureFromResourceA  m_TFunc_D3DXCreateVolumeTextureFromResourceA;
	TFunc_D3DXCreateVolumeTextureFromResourceW  m_TFunc_D3DXCreateVolumeTextureFromResourceW;

	TFunc_D3DXCreateVolumeTextureFromResourceExA  m_TFunc_D3DXCreateVolumeTextureFromResourceExA;
	TFunc_D3DXCreateVolumeTextureFromResourceExW  m_TFunc_D3DXCreateVolumeTextureFromResourceExW;

	TFunc_D3DXFillCubeTexture  m_TFunc_D3DXFillCubeTexture;
	TFunc_D3DXFillCubeTextureTX  m_TFunc_D3DXFillCubeTextureTX;
	TFunc_D3DXFillTexture  m_TFunc_D3DXFillTexture;
	TFunc_D3DXFillTextureTX  m_TFunc_D3DXFillTextureTX;

	TFunc_D3DXFillVolumeTexture  m_TFunc_D3DXFillVolumeTexture;
	TFunc_D3DXFillVolumeTextureTX  m_TFunc_D3DXFillVolumeTextureTX;

	TFunc_D3DXFilterTexture  m_TFunc_D3DXFilterTexture;


	TFunc_D3DXGetImageInfoFromFileA m_TFunc_D3DXGetImageInfoFromFileA ;
	TFunc_D3DXGetImageInfoFromFileW  m_TFunc_D3DXGetImageInfoFromFileW;

	TFunc_D3DXGetImageInfoFromFileInMemory  m_TFunc_D3DXGetImageInfoFromFileInMemory;

	TFunc_D3DXGetImageInfoFromResourceA  m_TFunc_D3DXGetImageInfoFromResourceA;
	TFunc_D3DXGetImageInfoFromResourceW  m_TFunc_D3DXGetImageInfoFromResourceW;

	TFunc_D3DXLoadSurfaceFromFileA  m_TFunc_D3DXLoadSurfaceFromFileA;
	TFunc_D3DXLoadSurfaceFromFileW  m_TFunc_D3DXLoadSurfaceFromFileW;

	TFunc_D3DXLoadSurfaceFromFileInMemory  m_TFunc_D3DXLoadSurfaceFromFileInMemory;

	TFunc_D3DXLoadSurfaceFromMemory  m_TFunc_D3DXLoadSurfaceFromMemory;

	TFunc_D3DXLoadSurfaceFromResourceA m_TFunc_D3DXLoadSurfaceFromResourceA ;
	TFunc_D3DXLoadSurfaceFromResourceW m_TFunc_D3DXLoadSurfaceFromResourceW ;

	TFunc_D3DXLoadSurfaceFromSurface  m_TFunc_D3DXLoadSurfaceFromSurface;

	TFunc_D3DXLoadVolumeFromFileA  m_TFunc_D3DXLoadVolumeFromFileA;
	TFunc_D3DXLoadVolumeFromFileW  m_TFunc_D3DXLoadVolumeFromFileW;

	TFunc_D3DXLoadVolumeFromFileInMemory m_TFunc_D3DXLoadVolumeFromFileInMemory ;
	TFunc_D3DXLoadVolumeFromMemory  m_TFunc_D3DXLoadVolumeFromMemory;

	TFunc_D3DXLoadVolumeFromResourceA  m_TFunc_D3DXLoadVolumeFromResourceA;
	TFunc_D3DXLoadVolumeFromResourceW  m_TFunc_D3DXLoadVolumeFromResourceW;

	TFunc_D3DXLoadVolumeFromVolume  m_TFunc_D3DXLoadVolumeFromVolume;

	TFunc_D3DXSaveSurfaceToFileA  m_TFunc_D3DXSaveSurfaceToFileA;
	TFunc_D3DXSaveSurfaceToFileW  m_TFunc_D3DXSaveSurfaceToFileW;

	TFunc_D3DXSaveSurfaceToFileInMemory m_TFunc_D3DXSaveSurfaceToFileInMemory ;

	TFunc_D3DXSaveTextureToFileA  m_TFunc_D3DXSaveTextureToFileA;
	TFunc_D3DXSaveTextureToFileW  m_TFunc_D3DXSaveTextureToFileW;

	TFunc_D3DXSaveTextureToFileInMemory m_TFunc_D3DXSaveTextureToFileInMemory ;

	TFunc_D3DXSaveVolumeToFileA  m_TFunc_D3DXSaveVolumeToFileA;
	TFunc_D3DXSaveVolumeToFileW  m_TFunc_D3DXSaveVolumeToFileW;

	TFunc_D3DXSaveVolumeToFileInMemory  m_TFunc_D3DXSaveVolumeToFileInMemory;






		Functions()
		{
			memset(&m_TFunc_D3DXCheckVersion, 0 , sizeof(Functions)  );
		}


		//!  \brief   обработка - функция sFuncName  не найдена в длл
		void handleNotFoundAddr(const char* sFuncName)
		{

			int stop = 0;
		}

		//! \brief Найти все точки входа в длл
		int GetProcAddr(const HMODULE hm);




	};


 //------------------------------------------------------------------

}
// end namespace d3dx9_dynamic_load

}
// end namespace d3d9

}
// end namespace graphics

}
// end namespace gb 



#endif // #if ( defined(WIN32) && defined(GB_D3D9)  )
// end file