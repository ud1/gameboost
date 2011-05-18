/** \file
 \brief Динамическая загрузка/ использование DLL   библиотеки D3DX9


  \author kscvet777


  \todo  сделать макрозащиту от неправильного включения.
  \todo поправить функцию  checkExistsDll на поиск в директории приложения.
  \todo убрать DEF_TEMP_ERR_HANDLE.
  \todo Precomputed Radiance Transfer Functions
  \todo  UVAtlas Functions


*/


#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once
#define __GB_D3DX9_DYNAMIC_LOAD_H__


#include <gb/graphics/d3d9/api_decl.h>

#include <d3dx9.h>

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load_pfunc_decl.h>

#include <stdlib.h>

#include <string>
#include <vector>
#include <stdexcept>

#include <gb/macro.h>
#include <assert.h>

#pragma warning( push )
#pragma warning( disable : 4297 )

namespace  gb
{

namespace  graphics
{

namespace  d3d9
{

//!  \brief Динамическая загрузка/ использование DLL   библиотеки D3DX9 .
namespace d3dx9_dynamic_load
{



	//d3dx9_undef   = 0 ,

	//d3dx9_24,
	//d3dx9_25,
	//d3dx9_26,
	//d3dx9_27,
	//d3dx9_28,
	//d3dx9_29,
	//d3dx9_30,
	//d3dx9_31,
	//d3dx9_32,
	//d3dx9_33,
	//d3dx9_34,
	//d3dx9_ ....,
 
 
  
  //-------------------------------------------------------------------------

  
  
/** \brief   Получить файл d3dx dll по номеру версии. 
    Например если передать 44 , то получиться d3dx9_44.dll  */
GB_D3D9_API void  makeD3DX9dllFilename_by_version(std::string& strOut, unsigned int vers, bool bDebugV=false) ;



//! \brief  ПРоверить существует ли dll . bIncludeExeDir - проверить или нет директорию приложениея.
GB_D3D9_API bool checkDllExistsA (const char* fname, bool bIncludeExeDir) ;
 
//!  \brief  УБРАТЬ !
GB_D3D9_API bool checkExistsDll(const char* sDllFilename) ;
 
//! \brief получить самую последнюю версию установленой библиотеки.
GB_D3D9_API bool getInstaledD3DXlastVersion(unsigned int* piOutVers) ;


//! \brief вывод  на консоль информации об обнаруженых в системе d3dx9 dll .
GB_D3D9_API void print_d3dx9_dll_info() ;


/** \brief  получит все инсталированые версии d3dx dll в системе   в вектор versions .
     Например если обнаружена  d3dx9_44.dll  то в векторе в том числе будет 44   */
GB_D3D9_API bool getInstaledD3DXallVersion(std::vector<unsigned int>& versions) ;

 

/**  \brief Загрузаить новейшую версию d3dx9 dll обнаруженную в системе.  Вернёт хэндл загр. длл.
  Еслит ошибка вернёт ноль.  piOutVers - версия, которая была загружена.       */
GB_D3D9_API HMODULE loadDllLastVersion(unsigned int* piOutVers ); 
 

//! \brief  Загрузчик d3dx9 dll  . Так же использование d3dx9  через него. 
class CD3DX9_Dll_Loader {
public:

    /** \brief Конструктор выполняет загрузку новейшей версии d3dx9 dll , 
	обнаруженой в системе.  Если ничего не найдено  бросает исключение.  */
	CD3DX9_Dll_Loader() throw()
	{
		m_versDll = 0;
		m_hmDLL = 0;

		m_hmDLL = loadDllLastVersion( &m_versDll );
		if(m_versDll == 0)
		{
			throw ( std::runtime_error("Error load d3dx9 dll !") );
		}

		int nres = m_fnc.GetProcAddr(m_hmDLL);

		if( nres<0 )
		{
			throw ( std::runtime_error("Invalid operation") );
		}
	}

    virtual ~CD3DX9_Dll_Loader()
	{
	   if(m_hmDLL)
	   {
		   ::FreeLibrary(m_hmDLL);
		   m_hmDLL = 0;
	   }

		m_versDll = 0;
	}
	
	//! \brief  Получить версию загруженой d3dx9 dll .
	unsigned int  getLoadedD3DX9dll_version() const 
	{
	  return m_versDll;
	}



//-------------------------------------------------------------------------


	//! temp!  времянка  убрать !!!!!
#define DEF_TEMP_ERR_HANDLE(funcname)   throw std::runtime_error( GB_MAKE_STR2(funcname) );


	//-------------------------------------------------------------
	//	General Purpose Functions
	//-------------------------------------------------------------


	BOOL D3DXCheckVersion( UINT D3DSDKVersion, UINT D3DXSDKVersion)
	{
		if( !m_fnc.m_TFunc_D3DXCheckVersion ) 
		{
			DEF_TEMP_ERR_HANDLE(D3DXCheckVersion)
		}

		return m_fnc.m_TFunc_D3DXCheckVersion(D3DSDKVersion, D3DXSDKVersion );
	}


	HRESULT D3DXCreateBuffer( DWORD NumBytes,    LPD3DXBUFFER * ppBuffer )
	{
		if( !m_fnc.m_TFunc_D3DXCreateBuffer )
		{
		  DEF_TEMP_ERR_HANDLE(D3DXCreateBuffer)
		}

		return  m_fnc.m_TFunc_D3DXCreateBuffer(NumBytes, ppBuffer );
	}


	HRESULT D3DXCreateFontA(LPDIRECT3DDEVICE9 pDevice,	INT Height,	UINT Width,	UINT Weight, UINT MipLevels,
		  BOOL Italic, DWORD CharSet,	DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily,
		  const CHAR* pFacename,	LPD3DXFONT * ppFont	)
	{
				if( !m_fnc.m_TFunc_D3DXCreateFontA )
				{
				  DEF_TEMP_ERR_HANDLE(D3DXCreateFontA)
				}

		return	m_fnc.m_TFunc_D3DXCreateFontA (pDevice,	  Height,	Width,	Weight, MipLevels,
			Italic,   CharSet,	  OutputPrecision,   Quality,   PitchAndFamily,
			pFacename, ppFont	);
	}


	HRESULT D3DXCreateFontW(LPDIRECT3DDEVICE9 pDevice,	INT Height,	UINT Width,	UINT Weight, UINT MipLevels,
				BOOL Italic, DWORD CharSet,	DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily,
				const WCHAR* pFacename,	LPD3DXFONT * ppFont	)
	{
				if( !m_fnc.m_TFunc_D3DXCreateFontW )
				{
					DEF_TEMP_ERR_HANDLE(D3DXCreateFontW)
				}

		return	m_fnc.m_TFunc_D3DXCreateFontW (pDevice,	  Height,	Width,	Weight, MipLevels,
			Italic,   CharSet,	  OutputPrecision,   Quality,   PitchAndFamily,
			pFacename, ppFont	);
	}


	HRESULT D3DXCreateFontIndirectA( LPDIRECT3DDEVICE9 pDevice, CONST D3DXFONT_DESCA* pDesc, LPD3DXFONT * ppFont )
	{
		  if( !m_fnc.m_TFunc_D3DXCreateFontIndirectA )
		  {
			 DEF_TEMP_ERR_HANDLE(D3DXCreateFontIndirectA)
		  }

	   return  m_fnc.m_TFunc_D3DXCreateFontIndirectA( pDevice,   pDesc,  ppFont);
	}


	HRESULT D3DXCreateFontIndirectW( LPDIRECT3DDEVICE9 pDevice, CONST D3DXFONT_DESCW * pDesc, LPD3DXFONT * ppFont )
	{
		if( !m_fnc.m_TFunc_D3DXCreateFontIndirectW )
		{
			DEF_TEMP_ERR_HANDLE(D3DXCreateFontIndirectW)
		}

		return  m_fnc.m_TFunc_D3DXCreateFontIndirectW( pDevice,   pDesc,  ppFont);
	}


	HRESULT D3DXCreateLine(	LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE* ppLine)
	{
		if(!m_fnc.m_TFunc_D3DXCreateLine)
		{
			DEF_TEMP_ERR_HANDLE(D3DXCreateLine)
		}

		return m_fnc.m_TFunc_D3DXCreateLine(  pDevice,  ppLine  );
	}


	HRESULT D3DXCreateRenderToEnvMap(	LPDIRECT3DDEVICE9 pDevice, 	UINT Size,	UINT MipLevels,	 D3DFORMAT Format,
				BOOL DepthStencil, D3DFORMAT DepthStencilFormat, ID3DXRenderToEnvMap** ppRenderToEnvMap	)
	{
		if(!m_fnc.m_TFunc_D3DXCreateRenderToEnvMap)
		{
			DEF_TEMP_ERR_HANDLE(D3DXCreateRenderToEnvMap)
		}

		return m_fnc.m_TFunc_D3DXCreateRenderToEnvMap( pDevice,   Size,	  MipLevels,  Format,
			  DepthStencil,   DepthStencilFormat,   ppRenderToEnvMap);
	}


	HRESULT D3DXCreateRenderToSurface(LPDIRECT3DDEVICE9 pDevice,	UINT Width,	UINT Height,
				D3DFORMAT Format, BOOL DepthStencil, D3DFORMAT DepthStencilFormat,
				LPD3DXRENDERTOSURFACE * ppRenderToSurface   )
	{
		if(!m_fnc.m_TFunc_D3DXCreateRenderToSurface)
		{
			DEF_TEMP_ERR_HANDLE(D3DXCreateRenderToSurface)
		}

		return m_fnc.m_TFunc_D3DXCreateRenderToSurface( pDevice, Width,	  Height,
			  Format,   DepthStencil,   DepthStencilFormat, ppRenderToSurface   );
	}


	HRESULT D3DXCreateSprite(	LPDIRECT3DDEVICE9 pDevice,	LPD3DXSPRITE * ppSprite	)
	{
		if(!m_fnc.m_TFunc_D3DXCreateSprite)
		{
			DEF_TEMP_ERR_HANDLE(D3DXCreateSprite)
		}
		return m_fnc.m_TFunc_D3DXCreateSprite(pDevice,	ppSprite	);
	}


	BOOL D3DXDebugMute(	BOOL Mute )
	{
		if(!m_fnc.m_TFunc_D3DXDebugMute)    
		{
			DEF_TEMP_ERR_HANDLE(D3DXDebugMute);
		}
		return	m_fnc.m_TFunc_D3DXDebugMute(Mute);
	}

	UINT D3DXGetDriverLevel( LPDIRECT3DDEVICE9 pDevice)
	{
	   if(!m_fnc.m_TFunc_D3DXGetDriverLevel)
	   {
		  DEF_TEMP_ERR_HANDLE(D3DXDebugMute);
	   }
	   return m_fnc.m_TFunc_D3DXGetDriverLevel(pDevice);
	}



	//-------------------------------------------------------------
	//	Math Functions
	//-------------------------------------------------------------



	D3DXMATRIX * D3DXMatrixInverse(D3DXMATRIX * pOut, FLOAT * pDeterminant, CONST D3DXMATRIX * pM )
	{
	   if(!m_fnc.m_TFunc_D3DXMatrixInverse)
	   {
		  DEF_TEMP_ERR_HANDLE( D3DXMatrixInverse );
	   }
	   return m_fnc.m_TFunc_D3DXMatrixInverse(pOut,  pDeterminant, pM);
	}


	D3DXMATRIX * D3DXMatrixMultiply(D3DXMATRIX * pOut,CONST D3DXMATRIX * pM1,CONST D3DXMATRIX * pM2	)
	{
	   if(!m_fnc.m_TFunc_D3DXMatrixMultiply)
	   {
		   DEF_TEMP_ERR_HANDLE(m_fnc.m_TFunc_D3DXMatrixMultiply);
	   }
	   return m_fnc.m_TFunc_D3DXMatrixMultiply( pOut, pM1, pM2 );
	}



	//-------------------------------------------------------------
	//	 mesh functions
	//-------------------------------------------------------------




	BOOL D3DXboxBoundProbe(  CONST D3DXVECTOR3 * pMin,  CONST D3DXVECTOR3 * pMax,
		CONST D3DXVECTOR3 * pRayPosition,  CONST D3DXVECTOR3 * pRayDirection)
	{
		if(!m_fnc.m_TFunc_D3DXBoxBoundProbe)
		{
			DEF_TEMP_ERR_HANDLE( D3DXboxBoundProbe );
		}
		return m_fnc.m_TFunc_D3DXBoxBoundProbe(pMin, pMax, pRayPosition,  pRayDirection);
	}


	HRESULT D3DXCleanMesh( D3DXCLEANTYPE CleanType, LPD3DXMESH pMeshIn, CONST DWORD * pAdjacencyIn,
		LPD3DXMESH * ppMeshOut, DWORD * pAdjacencyOut, LPD3DXBUFFER * ppErrorsAndWarnings )
	{
		if(! m_fnc.m_TFunc_D3DXCleanMesh)
		{
			DEF_TEMP_ERR_HANDLE( D3DXCleanMesh );
		}
		return   m_fnc.m_TFunc_D3DXCleanMesh( CleanType,   pMeshIn,   pAdjacencyIn, ppMeshOut, 
			pAdjacencyOut,   ppErrorsAndWarnings);
	}


	HRESULT D3DXComputeBoundingBox( CONST D3DXVECTOR3 * pFirstPosition, DWORD NumVertices,
		DWORD dwStride, D3DXVECTOR3 * pMin, D3DXVECTOR3 * pMax)
	{
		if(!m_fnc.m_TFunc_D3DXComputeBoundingBox)
		{
			DEF_TEMP_ERR_HANDLE( D3DXComputeBoundingBox );
		}
		return m_fnc.m_TFunc_D3DXComputeBoundingBox(pFirstPosition, NumVertices, dwStride, pMin,  pMax);
	}


	HRESULT D3DXComputeBoundingSphere( CONST D3DXVECTOR3 * pFirstPosition,  DWORD NumVertices, DWORD dwStride,
		D3DXVECTOR3 * pCenter,  FLOAT * pRadius )
	{
		if(!m_fnc.m_TFunc_D3DXComputeBoundingSphere)
		{
			DEF_TEMP_ERR_HANDLE( D3DXComputeBoundingSphere );
		}
		return m_fnc.m_TFunc_D3DXComputeBoundingSphere(pFirstPosition,  NumVertices,  dwStride, pCenter,   pRadius);
	}


	HRESULT D3DXComputeNormals( LPD3DXBASEMESH pMesh, CONST DWORD * pAdjacency)
	{
		if(!m_fnc.m_TFunc_D3DXComputeNormals)
		{
			DEF_TEMP_ERR_HANDLE( D3DXComputeNormals );
		}
		return m_fnc.m_TFunc_D3DXComputeNormals( pMesh,  pAdjacency);
	}

	HRESULT D3DXComputeTangent(	  LPD3DXMESH Mesh,	  DWORD TexStageIndex,  DWORD TangentIndex,
			DWORD BinormIndex,	 DWORD Wrap,  CONST DWORD * pAdjacency)
	{
		if( !m_fnc.m_TFunc_D3DXComputeTangent )
		{
		  DEF_TEMP_ERR_HANDLE( D3DXComputeTangent );
		}
		return m_fnc.m_TFunc_D3DXComputeTangent ( Mesh,	 TexStageIndex,  TangentIndex,
			  BinormIndex,	   Wrap,    pAdjacency );
	}


	HRESULT D3DXComputeTangentFrame(  ID3DXMesh * pMesh,  DWORD dwOptions )
	{

		if(!m_fnc.m_TFunc_D3DXComputeTangentFrame )
		{
			DEF_TEMP_ERR_HANDLE( D3DXComputeTangentFrame );
		}
		return m_fnc.m_TFunc_D3DXComputeTangentFrame(pMesh,  dwOptions);
	}


	HRESULT D3DXComputeTangentFrameEx( ID3DXMesh * pMesh,  DWORD dwTextureInSemantic,  DWORD dwTextureInIndex,  
		DWORD dwUPartialOutSemantic,DWORD dwUPartialOutIndex,  DWORD dwVPartialOutSemantic,  
		DWORD dwVPartialOutIndex,  DWORD dwNormalOutSemantic,	DWORD dwNormalOutIndex,  DWORD dwOptions, 
		CONST DWORD * pdwAdjacency,  FLOAT fPartialEdgeThreshold,
		FLOAT fSingularPointThreshold,  FLOAT fNormalEdgeThreshold,  ID3DXMesh ** ppMeshOut,  ID3DXBuffer ** ppVertexMapping )
	{
		if(!m_fnc.m_TFunc_D3DXComputeTangentFrameEx)
		{
			DEF_TEMP_ERR_HANDLE( D3DXComputeTangentFrameEx );
		}
		return m_fnc.m_TFunc_D3DXComputeTangentFrameEx(pMesh,    dwTextureInSemantic,    dwTextureInIndex,  
			dwUPartialOutSemantic,  dwUPartialOutIndex,   dwVPartialOutSemantic,  
			dwVPartialOutIndex,    dwNormalOutSemantic,	  dwNormalOutIndex,    dwOptions, 
			pdwAdjacency,    fPartialEdgeThreshold, fSingularPointThreshold,    fNormalEdgeThreshold,  
			ppMeshOut,   ppVertexMapping );
	}


	HRESULT D3DXConcatenateMeshes( LPD3DXMESH * ppMeshes, UINT NumMeshes, DWORD Options, CONST D3DXMATRIX * pGeomXForms, 
		CONST D3DXMATRIX * pTextureXForms,  CONST D3DVERTEXELEMENT9 * pDecl, LPDIRECT3DDEVICE9 pD3DDevice, 
		LPD3DXMESH * ppMeshOut )
	{
		if(!m_fnc.m_TFunc_D3DXConcatenateMeshes)
		{
			DEF_TEMP_ERR_HANDLE( D3DXConcatenateMeshes );
		}
		return m_fnc.m_TFunc_D3DXConcatenateMeshes(  ppMeshes,   NumMeshes,   Options, pGeomXForms, 
		   pTextureXForms,    pDecl,   pD3DDevice,  ppMeshOut );
	}


	HRESULT D3DXConvertMeshSubsetToSingleStrip(  LPD3DXBASEMESH MeshIn,  DWORD AttribId,  DWORD IBOptions,
		LPDIRECT3DINDEXBUFFER9 * ppIndexBuffer,  DWORD * pNumIndices )
	{
		if(!m_fnc.m_TFunc_D3DXConvertMeshSubsetToSingleStrip)
		{
			DEF_TEMP_ERR_HANDLE( D3DXConvertMeshSubsetToSingleStrip );
		}
		return m_fnc.m_TFunc_D3DXConvertMeshSubsetToSingleStrip(MeshIn,  AttribId,  IBOptions,
			ppIndexBuffer,   pNumIndices);
	}

	HRESULT D3DXConvertMeshSubsetToStrips( LPD3DXBASEMESH MeshIn, DWORD AttribId,  DWORD IBOptions,
		LPDIRECT3DINDEXBUFFER9 * ppIndexBuffer,  DWORD * pNumIndices,  LPD3DXBUFFER * ppStripLengths,
		DWORD * pNumStrips)
	{
		if(!m_fnc.m_TFunc_D3DXConvertMeshSubsetToStrips)
		{
			DEF_TEMP_ERR_HANDLE( D3DXConvertMeshSubsetToStrips );
		}
		return m_fnc.m_TFunc_D3DXConvertMeshSubsetToStrips (MeshIn,   AttribId,    IBOptions, 
			ppIndexBuffer,  pNumIndices, ppStripLengths, pNumStrips);
	}


	HRESULT D3DXCreateMesh( DWORD NumFaces,  DWORD NumVertices,  DWORD Options,  
			CONST LPD3DVERTEXELEMENT9 * pDeclaration,
			LPDIRECT3DDEVICE9 pD3DDevice,  LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXCreateMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXCreateMesh );
		}
		return m_fnc.m_TFunc_D3DXCreateMesh (NumFaces,    NumVertices,    Options,  
			  pDeclaration, pD3DDevice,   ppMesh );
	}


	HRESULT D3DXCreateMeshFVF( DWORD NumFaces, DWORD NumVertices, DWORD Options, DWORD FVF,  
		LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXMESH * ppMesh )
	{
		if( !m_fnc.m_TFunc_D3DXCreateMeshFVF )
		{
			DEF_TEMP_ERR_HANDLE( D3DXCreateMeshFVF );
		}
		return m_fnc.m_TFunc_D3DXCreateMeshFVF (  NumFaces,   NumVertices,   Options,
			FVF, pD3DDevice, ppMesh );
	}


	HRESULT D3DXCreateNPatchMesh( LPD3DXMESH pMeshSysMem, LPD3DXPATCHMESH * pPatchMesh )
	{
		if( !m_fnc.m_TFunc_D3DXCreateNPatchMesh)
		{
			DEF_TEMP_ERR_HANDLE( D3DXCreateNPatchMesh );
		}
		return m_fnc.m_TFunc_D3DXCreateNPatchMesh ( pMeshSysMem,  pPatchMesh  );
	}


	HRESULT D3DXCreatePatchMesh( CONST D3DXPATCHINFO * pInfo, DWORD dwNumPatches, DWORD dwNumVertices, DWORD dwOptions,
		CONST D3DVERTEXELEMENT9 * pDecl, LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXPATCHMESH * pPatchMesh )
	{
		if( !m_fnc.m_TFunc_D3DXCreatePatchMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXCreatePatchMesh );
		}
		return m_fnc.m_TFunc_D3DXCreatePatchMesh( pInfo,   dwNumPatches,   dwNumVertices,   dwOptions,
			pDecl,   pD3DDevice,  pPatchMesh  );
	}

	HRESULT D3DXCreateSkinInfo( DWORD NumVertices, CONST D3DVERTEXELEMENT9 * pDeclaration, 
		DWORD NumBones, LPD3DXSKININFO * ppSkinInfo)
	{
		if( !m_fnc.m_TFunc_D3DXCreateSkinInfo )
		{
			DEF_TEMP_ERR_HANDLE( D3DXCreateSkinInfo );
		}
		return m_fnc.m_TFunc_D3DXCreateSkinInfo ( NumVertices,  pDeclaration,   NumBones,   ppSkinInfo );
	}


	HRESULT D3DXDeclaratorFromFVF( DWORD FVF, D3DVERTEXELEMENT9 Declaration[MAX_FVF_DECL_SIZE] )
	{
		if( !m_fnc.m_TFunc_D3DXDeclaratorFromFVF)
		{
			DEF_TEMP_ERR_HANDLE( D3DXDeclaratorFromFVF );
		}
		return m_fnc.m_TFunc_D3DXDeclaratorFromFVF ( FVF,   Declaration );
	}

	HRESULT D3DXFVFFromDeclarator( CONST LPD3DVERTEXELEMENT9 * pDeclaration, DWORD * pFVF)
	{
		if( !m_fnc.m_TFunc_D3DXFVFFromDeclarator)
		{
			DEF_TEMP_ERR_HANDLE( D3DXFVFFromDeclarator );
		}
		return m_fnc.m_TFunc_D3DXFVFFromDeclarator ( pDeclaration, pFVF );
	}


	HRESULT D3DXGenerateOutputDecl(  D3DVERTEXELEMENT9 * pOutput,  CONST D3DVERTEXELEMENT9 * pInput)
	{
		if( !m_fnc.m_TFunc_D3DXGenerateOutputDecl )
		{
			DEF_TEMP_ERR_HANDLE( D3DXGenerateOutputDecl );
		}
		return m_fnc.m_TFunc_D3DXGenerateOutputDecl ( pOutput, pInput );
	}


	UINT D3DXGetDeclLength( CONST D3DVERTEXELEMENT9 * pDecl )
	{
		if( !m_fnc.m_TFunc_D3DXGetDeclLength )
		{
			DEF_TEMP_ERR_HANDLE( D3DXGetDeclLength );
		}
		return m_fnc.m_TFunc_D3DXGetDeclLength ( pDecl );
	}


	UINT D3DXGetDeclVertexSize( CONST D3DVERTEXELEMENT9 * pDecl, DWORD Stream)
	{
		if( !m_fnc.m_TFunc_D3DXGetDeclVertexSize )    
		{
			DEF_TEMP_ERR_HANDLE( D3DXGetDeclVertexSize );
		}
		return m_fnc.m_TFunc_D3DXGetDeclVertexSize ( pDecl,   Stream );
	}





	UINT D3DXGetFVFVertexSize( DWORD FVF )
	{
		if( !m_fnc.m_TFunc_D3DXGetFVFVertexSize)
		{
			DEF_TEMP_ERR_HANDLE( D3DXGetFVFVertexSize );
		}
		return m_fnc.m_TFunc_D3DXGetFVFVertexSize ( FVF );

	}

	HRESULT D3DXIntersect(  LPD3DXBASEMESH pMesh,  CONST D3DXVECTOR3 * pRayPos, 
			CONST D3DXVECTOR3 * pRayDir, BOOL* pHit,  DWORD* pFaceIndex, 
			FLOAT* pU, FLOAT* pV, FLOAT* pDist, LPD3DXBUFFER* ppAllHits, DWORD* pCountOfHits)
	{
		if( !m_fnc.m_TFunc_D3DXIntersect )
		{
			DEF_TEMP_ERR_HANDLE( D3DXIntersect );
		}
		return m_fnc.m_TFunc_D3DXIntersect (  pMesh,   pRayPos, pRayDir, pHit, pFaceIndex, 
			pU,   pV,  pDist,   ppAllHits,   pCountOfHits );
	}


	HRESULT D3DXIntersectSubset( LPD3DXBASEMESH pMesh,  DWORD AttribId, 
			CONST D3DXVECTOR3 * pRayPos,
			CONST D3DXVECTOR3 * pRayDir, BOOL * pHit,DWORD * pFaceIndex, FLOAT * pU,  FLOAT * pV, 
			FLOAT * pDist,  LPD3DXBUFFER * ppAllHits,  DWORD * pCountOfHits)
	{
		if( !m_fnc.m_TFunc_D3DXIntersectSubset)
		{
			DEF_TEMP_ERR_HANDLE( D3DXIntersectSubset );
		}
		return m_fnc.m_TFunc_D3DXIntersectSubset ( pMesh,    AttribId,   pRayPos,
			pRayDir,   pHit,  pFaceIndex,   pU,    pV,  pDist,   ppAllHits,  pCountOfHits );
	}


	BOOL D3DXIntersectTri( CONST D3DXVECTOR3 * p0,  CONST D3DXVECTOR3 * p1,  
			CONST D3DXVECTOR3 * p2,
			CONST D3DXVECTOR3 * pRayPos,  CONST D3DXVECTOR3 * pRayDir,
			FLOAT * pU,  FLOAT * pV,  FLOAT * pDist)
	{
		if( !m_fnc.m_TFunc_D3DXIntersectTri )
		{
			DEF_TEMP_ERR_HANDLE( D3DXIntersectTri );
		}
		return m_fnc.m_TFunc_D3DXIntersectTri ( p0,   p1,  p2,  pRayPos,   pRayDir,
			pU,   pV,   pDist );
	}

 

	HRESULT D3DXLoadMeshFromXA( const CHAR* pFilename,  DWORD Options,  
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPD3DXBUFFER * ppAdjacency,  LPD3DXBUFFER * ppMaterials,  LPD3DXBUFFER * ppEffectInstances,
		DWORD * pNumMaterials,  LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXLoadMeshFromXA )
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadMeshFromXA );
		}
		return m_fnc.m_TFunc_D3DXLoadMeshFromXA ( pFilename,    Options,   pD3DDevice,
			ppAdjacency,  ppMaterials, ppEffectInstances,  pNumMaterials,  ppMesh );
	}

	HRESULT D3DXLoadMeshFromXW( const WCHAR* pFilename,  DWORD Options,  
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPD3DXBUFFER * ppAdjacency,  LPD3DXBUFFER * ppMaterials, 
			LPD3DXBUFFER * ppEffectInstances,
			DWORD * pNumMaterials,  LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXLoadMeshFromXW )
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadMeshFromXW );
		}
		return m_fnc.m_TFunc_D3DXLoadMeshFromXW ( pFilename,    Options,   pD3DDevice,
			ppAdjacency,  ppMaterials, ppEffectInstances,  pNumMaterials,  ppMesh );
	}




	HRESULT D3DXLoadMeshFromXInMemory( LPCVOID Memory, DWORD SizeOfMemory, DWORD Options,
		LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXBUFFER * ppAdjacency, LPD3DXBUFFER * ppMaterials,
		LPD3DXBUFFER * ppEffectInstances, DWORD * pNumMaterials, LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXLoadMeshFromXInMemory )
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadMeshFromXInMemory );
		}
		return m_fnc.m_TFunc_D3DXLoadMeshFromXInMemory ( Memory,   SizeOfMemory, 
			Options,  pD3DDevice,   ppAdjacency,   ppMaterials,  ppEffectInstances,  
			pNumMaterials,  ppMesh );
	}


	HRESULT D3DXLoadMeshFromXof(  LPD3DXFILEDATA pxofMesh,  DWORD Options, 
		LPDIRECT3DDEVICE9 pDevice,
		LPD3DXBUFFER * ppAdjacency,  LPD3DXBUFFER * ppMaterials,  LPD3DXBUFFER * ppEffectInstances,
		DWORD * pNumMaterials,  LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXLoadMeshFromXof )
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadMeshFromXof );
		}
		return m_fnc.m_TFunc_D3DXLoadMeshFromXof ( pxofMesh,  Options, pDevice, ppAdjacency,  ppMaterials, 
			ppEffectInstances,	pNumMaterials,  ppMesh );
	}


	HRESULT D3DXLoadMeshFromXResource( HMODULE Module, LPCSTR Name, LPCSTR Type, DWORD Options,
			LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXBUFFER * ppAdjacency, LPD3DXBUFFER * ppMaterials,
			LPD3DXBUFFER * ppEffectInstances, DWORD * pNumMaterials, LPD3DXMESH * ppMesh )
	{
		if( !m_fnc.m_TFunc_D3DXLoadMeshFromXResource)
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadMeshFromXResource );
		}
		return m_fnc.m_TFunc_D3DXLoadMeshFromXResource (  Module,  Name,   Type,   Options,
			pD3DDevice,   ppAdjacency,   ppMaterials,  ppEffectInstances,  pNumMaterials,   ppMesh );
	}


	HRESULT D3DXLoadPatchMeshFromXof(  LPD3DXFILEDATA pxofMesh,  DWORD Options,  
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPD3DXBUFFER * ppMaterials,  LPD3DXBUFFER * ppEffectInstances,  PDWORD pNumMaterials, 
			LPD3DXPATCHMESH* ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXLoadPatchMeshFromXof )
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadPatchMeshFromXof );
		}
		return m_fnc.m_TFunc_D3DXLoadPatchMeshFromXof (  pxofMesh,    Options,   
			pD3DDevice,  ppMaterials,  ppEffectInstances, pNumMaterials,  ppMesh );
	}


	HRESULT D3DXLoadSkinMeshFromXof( LPD3DXFILEDATA pxofMesh, DWORD Options,  
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPD3DXBUFFER * ppAdjacency, LPD3DXBUFFER * ppMaterials, LPD3DXBUFFER * ppEffectInstances,
			DWORD * pMatOut, LPD3DXSKININFO * ppSkinInfo, LPD3DXMESH * ppMesh )
	{
		if( !m_fnc.m_TFunc_D3DXLoadSkinMeshFromXof)
		{
			DEF_TEMP_ERR_HANDLE( D3DXLoadSkinMeshFromXof );
		}
		return m_fnc.m_TFunc_D3DXLoadSkinMeshFromXof ( pxofMesh,   Options, 
			pD3DDevice, ppAdjacency,   ppMaterials,  
			ppEffectInstances,  pMatOut,   ppSkinInfo,   ppMesh );
	}


	HRESULT D3DXOptimizeFaces( LPCVOID pIndices, UINT NumFaces, UINT NumVertices, 
		BOOL Indices32Bit, DWORD* pFaceRemap)
	{
		if( !m_fnc.m_TFunc_D3DXOptimizeFaces )
		{
			DEF_TEMP_ERR_HANDLE( D3DXOptimizeFaces );
		}
		return m_fnc.m_TFunc_D3DXOptimizeFaces ( pIndices,   NumFaces,   NumVertices,   
			Indices32Bit,  pFaceRemap );
	}


	HRESULT D3DXOptimizeVertices(  LPCVOID pIndices,  UINT NumFaces,  UINT NumVertices,  BOOL Indices32Bit,
		DWORD * pVertexRemap)
	{
		if( !m_fnc.m_TFunc_D3DXOptimizeVertices )
		{
			DEF_TEMP_ERR_HANDLE( D3DXOptimizeVertices );
		}
		return m_fnc.m_TFunc_D3DXOptimizeVertices ( pIndices,  NumFaces,  NumVertices, 
			Indices32Bit, pVertexRemap );
	}


	HRESULT D3DXRectPatchSize(  CONST FLOAT* pfNumSegs, DWORD* pdwTriangles, DWORD* pwdVertices)
	{
		if( !m_fnc.m_TFunc_D3DXRectPatchSize )
		{
			DEF_TEMP_ERR_HANDLE( D3DXRectPatchSize );
		}
		return m_fnc.m_TFunc_D3DXRectPatchSize ( pfNumSegs,   pdwTriangles,   pwdVertices );
	}


	HRESULT D3DXSaveMeshToXA( const CHAR* pFilename, LPD3DXMESH pMesh, CONST DWORD * pAdjacency, 
				CONST D3DXMATERIAL * pMaterials,  CONST D3DXEFFECTINSTANCE * pEffectInstances, 
				DWORD NumMaterials,  DWORD Format)
	{
		if( !m_fnc.m_TFunc_D3DXSaveMeshToXA )
		{
			DEF_TEMP_ERR_HANDLE( D3DXSaveMeshToXA );
		}
		return m_fnc.m_TFunc_D3DXSaveMeshToXA( pFilename,   pMesh,   pAdjacency,  pMaterials,   pEffectInstances, 
			NumMaterials,    Format );
	}	

 
	HRESULT D3DXSaveMeshToXW( const WCHAR* pFilename, LPD3DXMESH pMesh, CONST DWORD * pAdjacency, 
				CONST D3DXMATERIAL * pMaterials,  CONST D3DXEFFECTINSTANCE * pEffectInstances, 
				DWORD NumMaterials,  DWORD Format)
	{
		if( !m_fnc.m_TFunc_D3DXSaveMeshToXW )
		{
			DEF_TEMP_ERR_HANDLE( D3DXSaveMeshToXW );
		}
		return m_fnc.m_TFunc_D3DXSaveMeshToXW ( pFilename,   pMesh,   pAdjacency,  pMaterials,   pEffectInstances, 
			NumMaterials,    Format );
	}




	HRESULT D3DXSimplifyMesh(  LPD3DXMESH pMesh,  CONST DWORD * pAdjacency,  
				CONST D3DXATTRIBUTEWEIGHTS * pVertexAttributeWeights,  CONST FLOAT * pVertexWeights,  
				DWORD MinValue,  DWORD Options,  LPD3DXMESH * ppMesh)
	{
		if( !m_fnc.m_TFunc_D3DXSimplifyMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXSimplifyMesh );
		}
		return m_fnc.m_TFunc_D3DXSimplifyMesh ( pMesh,   pAdjacency,   pVertexAttributeWeights,    pVertexWeights,  
			MinValue,    Options,   ppMesh );
	}			


	BOOL D3DXSphereBoundProbe( CONST D3DXVECTOR3 * pCenter, FLOAT Radius, CONST D3DXVECTOR3 * pRayPosition,
			CONST D3DXVECTOR3 * pRayDirection)
	{
		if( !m_fnc.m_TFunc_D3DXSphereBoundProbe )
		{
			DEF_TEMP_ERR_HANDLE( D3DXSphereBoundProbe );
		}
		return m_fnc.m_TFunc_D3DXSphereBoundProbe ( pCenter, Radius, pRayPosition,  pRayDirection );
	}

 


	void D3DXSplitMesh( LPD3DXMESH pMeshIn, CONST DWORD * pAdjacencyIn, CONST DWORD MaxSize,
				CONST DWORD Options, DWORD * pMeshesOut, LPD3DXBUFFER * ppMeshArrayOut,
				LPD3DXBUFFER * ppAdjacencyArrayOut, LPD3DXBUFFER * ppFaceRemapArrayOut,
				LPD3DXBUFFER * ppVertRemapArrayOut)
	{
		if( !m_fnc.m_TFunc_D3DXSplitMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXSplitMesh );
		}
		return m_fnc.m_TFunc_D3DXSplitMesh ( pMeshIn,   pAdjacencyIn,   MaxSize,  Options,   pMeshesOut,
			ppMeshArrayOut,  ppAdjacencyArrayOut,   ppFaceRemapArrayOut, ppVertRemapArrayOut );
	}


	HRESULT D3DXTessellateNPatches( LPD3DXMESH pMeshIn,  CONST DWORD * pAdjacencyIn, FLOAT NumSegs,
		BOOL QuadraticInterpNormals, LPD3DXMESH * ppMeshOut, LPD3DXBUFFER * ppAdjacencyOut)
	{
		if( !m_fnc.m_TFunc_D3DXTessellateNPatches )
		{
			DEF_TEMP_ERR_HANDLE( D3DXTessellateNPatches );
		}
		return m_fnc.m_TFunc_D3DXTessellateNPatches ( pMeshIn,   pAdjacencyIn,   NumSegs, 
					QuadraticInterpNormals,	 ppMeshOut,   ppAdjacencyOut );
	}


	HRESULT D3DXTessellateRectPatch(  LPDIRECT3DVERTEXBUFFER9 pVB,
		CONST FLOAT * pNumSegs,  CONST D3DVERTEXELEMENT9 * pInDecl, 
		CONST D3DRECTPATCH_INFO * pRectPatchInfo,  LPD3DXMESH pMesh)
	{
		if( !m_fnc.m_TFunc_D3DXTessellateRectPatch )
		{
			DEF_TEMP_ERR_HANDLE( D3DXTessellateRectPatch );
		}
		return m_fnc.m_TFunc_D3DXTessellateRectPatch ( pVB,  pNumSegs, pInDecl,  pRectPatchInfo,  pMesh );
	}
			   

	HRESULT D3DXTessellateTriPatch(  LPDIRECT3DVERTEXBUFFER9 pVB,  CONST FLOAT * pNumSegs,  
			CONST D3DVERTEXELEMENT9 * pInDecl,
			CONST D3DTRIPATCH_INFO * pTriPatchInfo,  LPD3DXMESH pMesh)
	{
		if( !m_fnc.m_TFunc_D3DXTessellateTriPatch )
		{
			DEF_TEMP_ERR_HANDLE( D3DXTessellateTriPatch );
		}
		return m_fnc.m_TFunc_D3DXTessellateTriPatch (  pVB,   pNumSegs, pInDecl,  pTriPatchInfo, pMesh ); 
	}


	HRESULT D3DXTriPatchSize(  CONST FLOAT * pfNumSegs,  DWORD * pdwTriangles,  DWORD * pdwVertices)
	{
		if( !m_fnc.m_TFunc_D3DXTriPatchSize )
		{
			DEF_TEMP_ERR_HANDLE( D3DXTriPatchSize );
		}
		return m_fnc.m_TFunc_D3DXTriPatchSize ( pfNumSegs,   pdwTriangles,   pdwVertices );
	}


	HRESULT D3DXValidMesh(  LPD3DXMESH pMeshIn,  CONST DWORD * pAdjacency,  LPD3DXBUFFER * ppErrorsAndWarnings)
	{
		if( !m_fnc.m_TFunc_D3DXValidMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXValidMesh );
		}
		return m_fnc.m_TFunc_D3DXValidMesh( pMeshIn,  pAdjacency, ppErrorsAndWarnings );
	}


	HRESULT D3DXValidPatchMesh( LPD3DXPATCHMESH  pMeshIn, DWORD * pNumDegenerateVertices,
		DWORD * pNumDegeneratePatches,  LPD3DXBUFFER * ppErrorsAndWarnings)
	{
		if( !m_fnc.m_TFunc_D3DXValidPatchMesh )
		{
			DEF_TEMP_ERR_HANDLE( D3DXValidPatchMesh );
		}
		return m_fnc.m_TFunc_D3DXValidPatchMesh( pMeshIn,  pNumDegenerateVertices,
			pNumDegeneratePatches,  ppErrorsAndWarnings );
	}


	HRESULT D3DXWeldVertices(  LPD3DXMESH pMesh,  DWORD Flags,  CONST D3DXWELDEPSILONS * pEpsilons,
		CONST DWORD * pAdjacencyIn,  DWORD * pAdjacencyOut,  DWORD * pFaceRemap,  LPD3DXBUFFER * ppVertexRemap)
	{
		if( !m_fnc.m_TFunc_D3DXWeldVertices )
		{
			DEF_TEMP_ERR_HANDLE( D3DXWeldVertices );
		}
		return m_fnc.m_TFunc_D3DXWeldVertices ( pMesh,  Flags,pEpsilons, pAdjacencyIn, pAdjacencyOut,  pFaceRemap,  ppVertexRemap );
	}


	//-------------------------------------------------------
	//	    Shader function
	//-------------------------------------------------------


 
 
HRESULT D3DXAssembleShader(  LPCSTR pSrcData,  UINT SrcDataLen,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs )
{
	if( !m_fnc.m_TFunc_D3DXAssembleShader )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXAssembleShader );
	}
    return m_fnc.m_TFunc_D3DXAssembleShader ( pSrcData, SrcDataLen,   pDefines,
	       pInclude,   Flags,   ppShader,   ppErrorMsgs  );
}
 
 
HRESULT D3DXAssembleShaderFromFileA(  const CHAR* pSrcFile,  CONST D3DXMACRO* pDefines,  
		LPD3DXINCLUDE pInclude, DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXAssembleShaderFromFileA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXAssembleShaderFromFileA );
	}
    return m_fnc.m_TFunc_D3DXAssembleShaderFromFileA(  pSrcFile,   pDefines,  pInclude,
	       Flags,   ppShader,   ppErrorMsgs );
}

 
HRESULT D3DXAssembleShaderFromFileW(  const WCHAR* pSrcFile,  CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,
		DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXAssembleShaderFromFileW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXAssembleShaderFromFileW );
	}
    return m_fnc.m_TFunc_D3DXAssembleShaderFromFileW ( pSrcFile,  pDefines,  pInclude,
	         Flags,   ppShader,  ppErrorMsgs );
}
 
 
HRESULT D3DXAssembleShaderFromResourceA(  HMODULE hSrcModule,  const CHAR* pSrcResource,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXAssembleShaderFromResourceA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXAssembleShaderFromResourceA );
	}
    return m_fnc.m_TFunc_D3DXAssembleShaderFromResourceA ( hSrcModule,    pSrcResource,   pDefines,
        pInclude,   Flags,  ppShader,    ppErrorMsgs );
}


HRESULT D3DXAssembleShaderFromResourceW(  HMODULE hSrcModule,  const WCHAR* pSrcResource,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXAssembleShaderFromResourceW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXAssembleShaderFromResourceW );
	}
    return m_fnc.m_TFunc_D3DXAssembleShaderFromResourceW ( hSrcModule,    pSrcResource,   pDefines,
        pInclude,   Flags,  ppShader,    ppErrorMsgs );
}




 
HRESULT D3DXCompileShader(  LPCSTR pSrcData,  UINT srcDataLen,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  LPCSTR pFunctionName,  LPCSTR pProfile,
		DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER* ppErrorMsgs,  
		LPD3DXCONSTANTTABLE * ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXCompileShader )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCompileShader );
	}
    return m_fnc.m_TFunc_D3DXCompileShader ( pSrcData,    srcDataLen,    pDefines,
           pInclude,    pFunctionName,  pProfile,
          Flags,    ppShader,   ppErrorMsgs,   ppConstantTable );
}

 
HRESULT D3DXCompileShaderFromFileA(  const CHAR* pSrcFile,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  LPCSTR pFunctionName,  LPCSTR pProfile,
		DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs,
		LPD3DXCONSTANTTABLE * ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXCompileShaderFromFileA)
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCompileShaderFromFileA );
	}
    return m_fnc.m_TFunc_D3DXCompileShaderFromFileA( pSrcFile,   pDefines,
		   pInclude,    pFunctionName,    pProfile,
		   Flags,   ppShader,    ppErrorMsgs, ppConstantTable );
}

HRESULT D3DXCompileShaderFromFileW(  const WCHAR* pSrcFile,  CONST D3DXMACRO* pDefines,
		LPD3DXINCLUDE pInclude,  const WCHAR* pFunctionName,  const WCHAR* pProfile,
		DWORD Flags,  LPD3DXBUFFER* ppShader,  LPD3DXBUFFER * ppErrorMsgs,
		LPD3DXCONSTANTTABLE * ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXCompileShaderFromFileW)
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCompileShaderFromFileW );
	}
    return m_fnc.m_TFunc_D3DXCompileShaderFromFileW( pSrcFile,   pDefines,
		   pInclude,    pFunctionName,    pProfile,
		   Flags,   ppShader,    ppErrorMsgs, ppConstantTable );
}


HRESULT D3DXCompileShaderFromResourceA(  HMODULE hSrcModule,  const CHAR* pSrcResource,
		CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,  LPCSTR pFunctionName,
		LPCSTR pProfile,  DWORD Flags,  LPD3DXBUFFER* ppShader,
		LPD3DXBUFFER * ppErrorMsgs,  LPD3DXCONSTANTTABLE * ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXCompileShaderFromResourceA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCompileShaderFromResourceA );
	}
    return m_fnc.m_TFunc_D3DXCompileShaderFromResourceA ( hSrcModule,    pSrcResource,
          pDefines,    pInclude,    pFunctionName,  pProfile,    Flags,    ppShader,
          ppErrorMsgs,   ppConstantTable );
}
 

 
HRESULT D3DXCompileShaderFromResourceW(  HMODULE hSrcModule,  const WCHAR* pSrcResource,
		CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,  const WCHAR* pFunctionName,
		const WCHAR* pProfile,  DWORD Flags,  LPD3DXBUFFER* ppShader,
		LPD3DXBUFFER * ppErrorMsgs,  LPD3DXCONSTANTTABLE * ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXCompileShaderFromResourceW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCompileShaderFromResourceW );
	}
    return m_fnc.m_TFunc_D3DXCompileShaderFromResourceW ( hSrcModule,    pSrcResource,
          pDefines,    pInclude,    pFunctionName,  pProfile,    Flags,    ppShader,
          ppErrorMsgs,   ppConstantTable );
}





 
HRESULT D3DXCreateTextureShader(  CONST DWORD * pFunction,  LPD3DXTEXTURESHADER * ppTextureShader)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureShader )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateTextureShader );
	}
    return m_fnc.m_TFunc_D3DXCreateTextureShader ( pFunction,  ppTextureShader );
} 

 
HRESULT D3DXDisassembleShader( CONST DWORD * pShader,  BOOL EnableColorCode,
		LPCSTR pComments,  LPD3DXBUFFER * ppDisassembly)
{
	if( !m_fnc.m_TFunc_D3DXDisassembleShader )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXDisassembleShader );
	}
    return m_fnc.m_TFunc_D3DXDisassembleShader ( pShader,    EnableColorCode,
		    pComments,    ppDisassembly );
}		
 
 
HRESULT D3DXFindShaderComment(  CONST DWORD* pFunction,  DWORD FourCC,  
			LPCVOID* ppData,  UINT* pSizeInBytes)
{
	if( !m_fnc.m_TFunc_D3DXFindShaderComment )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXFindShaderComment );
	}
    return m_fnc.m_TFunc_D3DXFindShaderComment ( pFunction,   FourCC,  ppData,   pSizeInBytes );
}
 
 
LPCSTR D3DXGetPixelShaderProfile(  LPDIRECT3DDEVICE9 pDevice)
{
	if( !m_fnc.m_TFunc_D3DXGetPixelShaderProfile )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetPixelShaderProfile );
	}
    return m_fnc.m_TFunc_D3DXGetPixelShaderProfile ( pDevice );
}

 
HRESULT D3DXGetShaderConstantTable(  CONST DWORD* pFunction,  LPD3DXCONSTANTTABLE*  ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderConstantTable )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderConstantTable );
	}
    return m_fnc.m_TFunc_D3DXGetShaderConstantTable ( pFunction,   ppConstantTable );
}
 
 
 HRESULT D3DXGetShaderConstantTableEx(  CONST DWORD* pFunction,  DWORD Flags,
			LPD3DXCONSTANTTABLE*  ppConstantTable)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderConstantTableEx )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderConstantTableEx );
	}
    return m_fnc.m_TFunc_D3DXGetShaderConstantTableEx ( pFunction,  Flags,  ppConstantTable );
}


HRESULT D3DXGetShaderInputSemantics( CONST DWORD* pFunction, D3DXSEMANTIC* pSemantics, UINT* pCount)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderInputSemantics )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderInputSemantics );
	}
    return m_fnc.m_TFunc_D3DXGetShaderInputSemantics ( pFunction, pSemantics, pCount );
}
 

HRESULT D3DXGetShaderOutputSemantics( CONST DWORD* pFunction, D3DXSEMANTIC* pSemantics, UINT* pCount)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderOutputSemantics )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderOutputSemantics );
	}
    return m_fnc.m_TFunc_D3DXGetShaderOutputSemantics ( pFunction, pSemantics,  pCount );
}
 
 
HRESULT D3DXGetShaderSamplers( CONST DWORD* pFunction, LPCSTR* pSamplers, UINT* pCount)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderSamplers )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderSamplers );
	}
    return m_fnc.m_TFunc_D3DXGetShaderSamplers( pFunction,   pSamplers,  pCount );
}
 
 UINT D3DXGetShaderSize(  CONST DWORD * pFunction)
 {
 	if( !m_fnc.m_TFunc_D3DXGetShaderSize )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderSize );
	}
    return m_fnc.m_TFunc_D3DXGetShaderSize ( pFunction );
 }

 
DWORD D3DXGetShaderVersion(  CONST DWORD* pFunction)
{
	if( !m_fnc.m_TFunc_D3DXGetShaderVersion )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetShaderVersion );
	}
    return m_fnc.m_TFunc_D3DXGetShaderVersion ( pFunction );
}

LPCSTR D3DXGetVertexShaderProfile(  LPDIRECT3DDEVICE9 pDevice)
{
	if( !m_fnc.m_TFunc_D3DXGetVertexShaderProfile )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXGetVertexShaderProfile );
	}
    return m_fnc.m_TFunc_D3DXGetVertexShaderProfile ( pDevice );
}

 
HRESULT D3DXPreprocessShader(  LPCSTR pSrcData,  UINT SrcDataSize,
			CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,
			LPD3DXBUFFER* ppShaderText,  LPD3DXBUFFER* ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXPreprocessShader )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXPreprocessShader );
	}
    return m_fnc.m_TFunc_D3DXPreprocessShader ( pSrcData,    SrcDataSize,  pDefines,   pInclude,
		    ppShaderText,   ppErrorMsgs );
}


HRESULT D3DXPreprocessShaderFromFileA(  const CHAR* pSrcFile,  CONST D3DXMACRO* pDefines,
			 LPD3DXINCLUDE pInclude,  LPD3DXBUFFER* ppShaderText,  LPD3DXBUFFER* ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXPreprocessShaderFromFileA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXPreprocessShaderFromFileA );
	}
    return m_fnc.m_TFunc_D3DXPreprocessShaderFromFileA ( pSrcFile,    pDefines, pInclude,  
			ppShaderText, ppErrorMsgs );
}



HRESULT D3DXPreprocessShaderFromFileW(  const WCHAR* pSrcFile,  CONST D3DXMACRO* pDefines,
			 LPD3DXINCLUDE pInclude,  LPD3DXBUFFER* ppShaderText,  LPD3DXBUFFER* ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXPreprocessShaderFromFileW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXPreprocessShaderFromFileW );
	}
    return m_fnc.m_TFunc_D3DXPreprocessShaderFromFileW ( pSrcFile,    pDefines, pInclude,  
			ppShaderText, ppErrorMsgs );
}




HRESULT D3DXPreprocessShaderFromResourceA(  HMODULE hSrcModule,  const CHAR* pSrcResource,
		 CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,  LPD3DXBUFFER* ppShaderText,
		 LPD3DXBUFFER* ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXPreprocessShaderFromResourceA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXPreprocessShaderFromResourceA );
	}
    return m_fnc.m_TFunc_D3DXPreprocessShaderFromResourceA ( hSrcModule,    pSrcResource,
		pDefines,    pInclude,  ppShaderText, ppErrorMsgs );
}
  

HRESULT D3DXPreprocessShaderFromResourceW(  HMODULE hSrcModule,  const WCHAR* pSrcResource,
		 CONST D3DXMACRO* pDefines,  LPD3DXINCLUDE pInclude,  LPD3DXBUFFER* ppShaderText,
		 LPD3DXBUFFER* ppErrorMsgs)
{
	if( !m_fnc.m_TFunc_D3DXPreprocessShaderFromResourceW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXPreprocessShaderFromResourceW );
	}
    return m_fnc.m_TFunc_D3DXPreprocessShaderFromResourceW ( hSrcModule,    pSrcResource,
		pDefines,    pInclude,  ppShaderText, ppErrorMsgs );
}
 

   //-----------------------------------------------------
   //	  Shared drawing functions
   //-----------------------------------------------------



HRESULT D3DXCreateBox(  LPDIRECT3DDEVICE9 pDevice,  FLOAT Width,  FLOAT Height,
		FLOAT Depth,  LPD3DXMESH * ppMesh,  LPD3DXBUFFER * ppAdjacency)
{
	if( !m_fnc.m_TFunc_D3DXCreateBox )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateBox );
	}
    return m_fnc.m_TFunc_D3DXCreateBox ( pDevice,    Width,    Height,
		      Depth,    ppMesh,    ppAdjacency );
}


HRESULT D3DXCreateCylinder(  LPDIRECT3DDEVICE9 pDevice,  FLOAT Radius1,  FLOAT Radius2,
		FLOAT Length,  UINT Slices,  UINT Stacks,  LPD3DXMESH * ppMesh,  
		LPD3DXBUFFER * ppAdjacency)
{
	if( !m_fnc.m_TFunc_D3DXCreateCylinder )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateCylinder );
	}
    return m_fnc.m_TFunc_D3DXCreateCylinder (  pDevice,    Radius1,    Radius2,
		  Length,    Slices,    Stacks,  ppMesh,  
		   ppAdjacency );
}


HRESULT D3DXCreatePolygon(  LPDIRECT3DDEVICE9 pDevice,  FLOAT Length,  UINT Sides,
			LPD3DXMESH * ppMesh,  LPD3DXBUFFER * ppAdjacency )
{
	if( !m_fnc.m_TFunc_D3DXCreatePolygon )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreatePolygon );
	}
    return m_fnc.m_TFunc_D3DXCreatePolygon ( pDevice,   Length,   Sides,
			    ppMesh,   ppAdjacency  );
}



HRESULT D3DXCreateSphere( LPDIRECT3DDEVICE9 pDevice,  FLOAT Radius,  UINT Slices,
			UINT Stacks,  LPD3DXMESH * ppMesh,  LPD3DXBUFFER * ppAdjacency )
{
	if( !m_fnc.m_TFunc_D3DXCreateSphere )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateSphere );
	}
    return m_fnc.m_TFunc_D3DXCreateSphere ( pDevice,   Radius,  Slices,
			    Stacks,    ppMesh,    ppAdjacency );
}


HRESULT D3DXCreateTeapot(  LPDIRECT3DDEVICE9 pDevice,  LPD3DXMESH * ppMesh,  LPD3DXBUFFER * ppAdjacency)
{
	if( !m_fnc.m_TFunc_D3DXCreateTeapot )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateTeapot );
	}
    return m_fnc.m_TFunc_D3DXCreateTeapot ( pDevice,   ppMesh,  ppAdjacency );
}

HRESULT D3DXCreateTextA(  LPDIRECT3DDEVICE9 pDevice,
			HDC hDC,  const CHAR* pText, 
			FLOAT Deviation,  FLOAT Extrusion,  LPD3DXMESH * ppMesh,
			LPD3DXBUFFER * ppAdjacency,  LPGLYPHMETRICSFLOAT pGlyphMetrics)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextA )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateTextA );
	}
    return m_fnc.m_TFunc_D3DXCreateTextA (  pDevice,  hDC,    pText, Deviation,   
       	Extrusion,    ppMesh,  ppAdjacency,  pGlyphMetrics );
}

  
  
HRESULT D3DXCreateTextW(  LPDIRECT3DDEVICE9 pDevice,  HDC hDC,  const WCHAR* pText,  
		FLOAT Deviation,  FLOAT Extrusion,  LPD3DXMESH * ppMesh,
		LPD3DXBUFFER * ppAdjacency,  LPGLYPHMETRICSFLOAT pGlyphMetrics)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextW )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateTextW );
	}
    return m_fnc.m_TFunc_D3DXCreateTextW ( pDevice,  hDC,  pText,  
		  Deviation,    Extrusion,    ppMesh,
		   ppAdjacency,    pGlyphMetrics );
}


HRESULT D3DXCreateTorus(  LPDIRECT3DDEVICE9 pDevice,  FLOAT InnerRadius,  FLOAT OuterRadius,
			UINT Sides,  UINT Rings,  LPD3DXMESH * ppMesh,  LPD3DXBUFFER * ppAdjacency)
{
	if( !m_fnc.m_TFunc_D3DXCreateTorus )
	{
	  DEF_TEMP_ERR_HANDLE( D3DXCreateTorus );
	}
    return m_fnc.m_TFunc_D3DXCreateTorus ( pDevice,  InnerRadius,   OuterRadius,
			  Sides,    Rings,    ppMesh,  ppAdjacency );
}

 
//---------------------------------------------------------
//       texture  functions  
//---------------------------------------------------------


HRESULT D3DXCheckCubeTextureRequirements(  LPDIRECT3DDEVICE9 pDevice,  UINT * pSize,  
										 UINT * pNumMipLevels,  DWORD Usage, D3DFORMAT * pFormat,  D3DPOOL Pool)
{
	if( !m_fnc.m_TFunc_D3DXCheckCubeTextureRequirements )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCheckCubeTextureRequirements );
	}
	return m_fnc.m_TFunc_D3DXCheckCubeTextureRequirements ( pDevice,   pSize,  
		pNumMipLevels,    Usage,   pFormat,  Pool );
}


HRESULT D3DXCheckTextureRequirements(  LPDIRECT3DDEVICE9 pDevice,
									 UINT * pWidth,  UINT * pHeight,  UINT * pNumMipLevels,
									 DWORD Usage,  D3DFORMAT * pFormat,  D3DPOOL Pool)
{
	if( !m_fnc.m_TFunc_D3DXCheckTextureRequirements )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCheckTextureRequirements );
	}
	return m_fnc.m_TFunc_D3DXCheckTextureRequirements ( pDevice,
		pWidth,  pHeight, pNumMipLevels,  Usage,    pFormat,  Pool );
}




HRESULT D3DXCheckVolumeTextureRequirements(  LPDIRECT3DDEVICE9 pDevice,
										   UINT * pWidth,  UINT * pHeight,  UINT * pDepth,
										   UINT * pNumMipLevels,  DWORD Usage,  D3DFORMAT * pFormat,  D3DPOOL Pool)
{
	if( !m_fnc.m_TFunc_D3DXCheckVolumeTextureRequirements )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCheckVolumeTextureRequirements );
	}
	return m_fnc.m_TFunc_D3DXCheckVolumeTextureRequirements ( pDevice,
		pWidth,   pHeight,   pDepth, pNumMipLevels,  Usage,   pFormat,  Pool );
}


HRESULT D3DXComputeNormalMap(  LPDIRECT3DTEXTURE9 pTexture,  LPDIRECT3DTEXTURE9 pSrcTexture,
							 CONST PALETTEENTRY * pSrcPalette,  DWORD Flags,  DWORD Channel,  FLOAT Amplitude)
{
	if( !m_fnc.m_TFunc_D3DXComputeNormalMap )
	{
		DEF_TEMP_ERR_HANDLE( D3DXComputeNormalMap );
	}
	return m_fnc.m_TFunc_D3DXComputeNormalMap ( pTexture,  pSrcTexture,
		pSrcPalette,   Flags,   Channel,   Amplitude );
}


HRESULT D3DXCreateCubeTexture(  LPDIRECT3DDEVICE9 pDevice,
							  UINT Size, UINT MipLevels, DWORD Usage,  D3DFORMAT Format,
							  D3DPOOL Pool,  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTexture );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTexture (  pDevice,
		  Size,   MipLevels,   Usage,    Format,
		  Pool,     ppCubeTexture);
}


HRESULT D3DXCreateCubeTextureFromFileA( LPDIRECT3DDEVICE9 pDevice,  const CHAR* pSrcFile,
									  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileA );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileA ( pDevice,    pSrcFile,
		ppCubeTexture );
}

HRESULT D3DXCreateCubeTextureFromFileW( LPDIRECT3DDEVICE9 pDevice,  const WCHAR* pSrcFile,
									  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileW );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileW ( pDevice,    pSrcFile,
		ppCubeTexture );
}






HRESULT D3DXCreateCubeTextureFromFileExA(
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
										LPDIRECT3DCUBETEXTURE9 * ppCubeTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileExA );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileExA (  pDevice, pSrcFile, 
		Size, MipLevels,  Usage,  Format,
		Pool,  Filter, MipFilter, ColorKey,  pSrcInfo,  pPalette,  ppCubeTexture );
}




HRESULT D3DXCreateCubeTextureFromFileExW(
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
										)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileExW );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileExW (  pDevice, pSrcFile,  
		Size, MipLevels,  Usage,  Format,
		Pool,  Filter, MipFilter, ColorKey,  pSrcInfo,  pPalette,  ppCubeTexture );
}






HRESULT D3DXCreateCubeTextureFromFileInMemory(  LPDIRECT3DDEVICE9 pDevice,
											  LPCVOID pSrcData,  UINT SrcDataSize,
											  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
											  )
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileInMemory ( pDevice,
		pSrcData,  SrcDataSize, ppCubeTexture );
}




HRESULT D3DXCreateCubeTextureFromFileInMemoryEx(
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
	LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileInMemoryEx )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromFileInMemoryEx );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromFileInMemoryEx ( pDevice,
		pSrcData,    SrcDataSize,    Size,   MipLevels,  Usage,  Format,   Pool, Filter,
		MipFilter,   ColorKey,  pSrcInfo,  pPalette,  ppCubeTexture );
}



HRESULT D3DXCreateCubeTextureFromResourceA( LPDIRECT3DDEVICE9 pDevice,  
										  HMODULE hSrcModule,
										  const CHAR* pSrcResource, 
										  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceA );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceA( pDevice, hSrcModule,  
		pSrcResource, ppCubeTexture );
}



HRESULT D3DXCreateCubeTextureFromResourceW( LPDIRECT3DDEVICE9 pDevice,  
										  HMODULE hSrcModule,
										  const WCHAR*  pSrcResource, 
										  LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceW( pDevice, hSrcModule,  
			pSrcResource, ppCubeTexture );
}



HRESULT D3DXCreateCubeTextureFromResourceExA(
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
	LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceExA);
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceExA ( pDevice,
		hSrcModule, pSrcResource, Size, MipLevels, Usage, Format,  Pool,  Filter,   
		MipFilter,  ColorKey,  pSrcInfo, pPalette,  ppCubeTexture );
}



HRESULT D3DXCreateCubeTextureFromResourceExW(
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
	LPDIRECT3DCUBETEXTURE9 * ppCubeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceExW );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceExW ( pDevice,
		hSrcModule, pSrcResource, Size, MipLevels, Usage, Format,  Pool,  Filter,   
		MipFilter,  ColorKey,  pSrcInfo, pPalette,  ppCubeTexture );
}


HRESULT D3DXCreateTexture(LPDIRECT3DDEVICE9 pDevice,
						  UINT Width,
						  UINT Height,
						  UINT MipLevels,
						  DWORD Usage,
						  D3DFORMAT Format,
						  D3DPOOL Pool,
						  LPDIRECT3DTEXTURE9 * ppTexture  )
{
	if( !m_fnc.m_TFunc_D3DXCreateTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTexture );
	}
	return m_fnc.m_TFunc_D3DXCreateTexture ( pDevice,  Width,  Height,     MipLevels,
		  Usage, Format,  Pool,	  ppTexture  );
}




HRESULT D3DXCreateTextureFromFileA(LPDIRECT3DDEVICE9 pDevice,
								  const CHAR* pSrcFile,
								  LPDIRECT3DTEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileA );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileA( pDevice,  pSrcFile,  ppTexture  );
}



HRESULT D3DXCreateTextureFromFileW(LPDIRECT3DDEVICE9 pDevice,
								  const WCHAR* pSrcFile,
								  LPDIRECT3DTEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileW );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileW( pDevice,  pSrcFile,  ppTexture  );
}


HRESULT D3DXCreateTextureFromFileExA(LPDIRECT3DDEVICE9 pDevice,
									const CHAR* pSrcFile,
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
									LPDIRECT3DTEXTURE9 * ppTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileExA );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileExA ( pDevice,  pSrcFile,
		  Width, Height,  MipLevels, Usage, Format,	Pool,  Filter,
		  MipFilter, ColorKey,  pSrcInfo,  pPalette,   ppTexture );
}




HRESULT D3DXCreateTextureFromFileExW(LPDIRECT3DDEVICE9 pDevice,
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
									LPDIRECT3DTEXTURE9 * ppTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileExW );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileExW ( pDevice,  pSrcFile,
		Width, Height,  MipLevels, Usage, Format,	Pool,  Filter,
		MipFilter, ColorKey,  pSrcInfo,  pPalette,   ppTexture );
}




HRESULT D3DXCreateTextureFromFileInMemory(
	LPDIRECT3DDEVICE9 pDevice,
	LPCVOID pSrcData,
	UINT SrcDataSize,
	LPDIRECT3DTEXTURE9 * ppTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileInMemory ( pDevice,
		  pSrcData,  SrcDataSize,	  ppTexture  );
}



HRESULT D3DXCreateTextureFromFileInMemoryEx(
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
	LPDIRECT3DTEXTURE9 * ppTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromFileInMemoryEx )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromFileInMemoryEx );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromFileInMemoryEx ( pDevice,  
		pSrcData,  SrcDataSize,  Width, Height,  MipLevels,  Usage,  
		Format, Pool, Filter, MipFilter, ColorKey,	pSrcInfo, 
		pPalette,  ppTexture  );
}

  /***********************      ***********************
HRESULT D3DXCreateCubeTextureFromResourceA(
	LPDIRECT3DDEVICE9 pDevice,
	HMODULE hSrcModule,
	const CHAR* pSrcResource,
	LPDIRECT3DCUBETEXTURE9 * ppCubeTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceA);
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceA ( pDevice,  hSrcModule,
		  pSrcResource,	 ppCubeTexture  );
}


HRESULT D3DXCreateCubeTextureFromResourceW (
	LPDIRECT3DDEVICE9 pDevice,
	HMODULE hSrcModule,
	const WCHAR* pSrcResource,
	LPDIRECT3DCUBETEXTURE9 * ppCubeTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateCubeTextureFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXCreateCubeTextureFromResourceW ( pDevice,  hSrcModule,
		pSrcResource,	 ppCubeTexture  );
}
 **************************    *******************************/



HRESULT D3DXCreateTextureFromResourceExA(LPDIRECT3DDEVICE9 pDevice,
										HMODULE hSrcModule,
										const CHAR* pSrcResource,
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
										LPDIRECT3DTEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromResourceExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromResourceExA );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromResourceExA (  pDevice, 
			hSrcModule,	 pSrcResource, Width,  Height,	 MipLevels,	 Usage,	 Format,
			 Pool,	 Filter,  MipFilter,  ColorKey,    pSrcInfo,   pPalette,  ppTexture );
}




HRESULT D3DXCreateTextureFromResourceExW(LPDIRECT3DDEVICE9 pDevice,
										HMODULE hSrcModule,
										const WCHAR* pSrcResource,
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
										LPDIRECT3DTEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateTextureFromResourceExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateTextureFromResourceExW );
	}
	return m_fnc.m_TFunc_D3DXCreateTextureFromResourceExW (  pDevice, 
		hSrcModule,	 pSrcResource, Width,  Height,	 MipLevels,	 Usage,	 Format,
		Pool,	 Filter,  MipFilter,  ColorKey,    pSrcInfo,   pPalette,  ppTexture );
}


 
HRESULT D3DXCreateVolumeTexture(LPDIRECT3DDEVICE9 pDevice,
								UINT Width,
								UINT Height,
								UINT Depth,
								UINT MipLevels,
								DWORD Usage,
								D3DFORMAT Format,
								D3DPOOL Pool,
								LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTexture );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTexture ( pDevice,  Width,  Height, 
			Depth, MipLevels, Usage, Format, Pool, ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromFileA( LPDIRECT3DDEVICE9 pDevice,
										const  CHAR* pSrcFile,  
										LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileA );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileA ( pDevice,
		pSrcFile,  ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromFileW( LPDIRECT3DDEVICE9 pDevice,
										 const WCHAR* pSrcFile,  
										 LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileW );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileW ( pDevice,
		pSrcFile,  ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromFileExA (
	LPDIRECT3DDEVICE9 pDevice,
	const  CHAR* pSrcFile,
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
	LPDIRECT3DVOLUMETEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileExA );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileExA ( pDevice, pSrcFile, Width, Height, Depth,
			MipLevels, Usage, Format,Pool, Filter, MipFilter, ColorKey, 
			pSrcInfo, pPalette,  ppTexture );
}



HRESULT D3DXCreateVolumeTextureFromFileExW (
	LPDIRECT3DDEVICE9 pDevice,
	const WCHAR* pSrcFile,
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
	LPDIRECT3DVOLUMETEXTURE9 * ppTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileExW );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileExW ( pDevice, pSrcFile, Width, Height, Depth,
		MipLevels, Usage, Format,Pool, Filter, MipFilter, ColorKey, 
		pSrcInfo, pPalette,  ppTexture );
}




HRESULT D3DXCreateVolumeTextureFromFileInMemory( LPDIRECT3DDEVICE9 pDevice,
												LPCVOID pSrcFile, UINT SrcData, LPDIRECT3DVOLUMETEXTURE9 ppVolumeTexture)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileInMemory)
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileInMemory ( pDevice, pSrcFile, SrcData, ppVolumeTexture );
}




HRESULT D3DXCreateVolumeTextureFromFileInMemoryEx(
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
	LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileInMemoryEx )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromFileInMemoryEx );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromFileInMemoryEx ( pDevice,  
		pSrcData, SrcDataSize,  Width, Height, Depth, MipLevels,  Usage, 
		Format,  Pool, Filter, MipFilter, ColorKey,  pSrcInfo,  pPalette,  
		ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromResourceA(
	LPDIRECT3DDEVICE9 pDevice,
	HMODULE hSrcModule,
	const CHAR* pSrcResource,
	LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromResourceA );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceA ( pDevice, hSrcModule,
		pSrcResource,  ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromResourceW(
	LPDIRECT3DDEVICE9 pDevice,
	HMODULE hSrcModule,
	const WCHAR* pSrcResource,
	LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture )
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceW ( pDevice, hSrcModule,
		pSrcResource,  ppVolumeTexture );
}




HRESULT D3DXCreateVolumeTextureFromResourceExA(
		LPDIRECT3DDEVICE9 pDevice,
		HMODULE hSrcModule,
		const  CHAR* pSrcResource,
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
		LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceExA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromResourceExA );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceExA ( pDevice,
		hSrcModule,  pSrcResource, Width, Height, Depth, MipLevels, Usage,   Format,
		Pool,  Filter,  MipFilter, ColorKey,  pSrcInfo, pPalette, ppVolumeTexture );
}



HRESULT D3DXCreateVolumeTextureFromResourceExW(
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
	LPDIRECT3DVOLUMETEXTURE9 * ppVolumeTexture 	)
{
	if( !m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceExW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXCreateVolumeTextureFromResourceExW );
	}
	return m_fnc.m_TFunc_D3DXCreateVolumeTextureFromResourceExW ( pDevice,
		hSrcModule,  pSrcResource, Width, Height, Depth, MipLevels, Usage,   Format,
		Pool,  Filter,  MipFilter, ColorKey,  pSrcInfo, pPalette, ppVolumeTexture );
}


HRESULT D3DXFillCubeTexture( LPDIRECT3DCUBETEXTURE9 pTexture, LPD3DXFILL3D pFunction, LPVOID pData)
{
	if( !m_fnc.m_TFunc_D3DXFillCubeTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillCubeTexture );
	}
	return m_fnc.m_TFunc_D3DXFillCubeTexture ( pTexture,   pFunction,
		pData );
}




HRESULT D3DXFillCubeTextureTX( LPDIRECT3DCUBETEXTURE9 pTexture,
							  LPD3DXTEXTURESHADER pTextureShader)
{
	if( !m_fnc.m_TFunc_D3DXFillCubeTextureTX )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillCubeTextureTX );
	}
	return m_fnc.m_TFunc_D3DXFillCubeTextureTX( pTexture, pTextureShader );
}




HRESULT D3DXFillTexture(LPDIRECT3DTEXTURE9 pTexture, LPD3DXFILL2D pFunction, 
						LPVOID pData)
{
	if( !m_fnc.m_TFunc_D3DXFillTexture)
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillTexture );
	}
	return m_fnc.m_TFunc_D3DXFillTexture ( pTexture,  pFunction,  pData );
}


HRESULT D3DXFillTextureTX( LPDIRECT3DTEXTURE9 pTexture, LPD3DXTEXTURESHADER pTextureShader )
{
	if( !m_fnc.m_TFunc_D3DXFillTextureTX )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillTextureTX );
	}
	return m_fnc.m_TFunc_D3DXFillTextureTX ( pTexture,  pTextureShader );
}




HRESULT D3DXFillVolumeTexture( LPDIRECT3DVOLUMETEXTURE9 pTexture,
							  LPD3DXFILL3D pFunction, LPVOID pData)
{
	if( !m_fnc.m_TFunc_D3DXFillVolumeTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillVolumeTexture );
	}
	return m_fnc.m_TFunc_D3DXFillVolumeTexture ( pTexture, pFunction,   pData );
}




HRESULT D3DXFillVolumeTextureTX( LPDIRECT3DVOLUMETEXTURE9 pTexture,
								LPD3DXTEXTURESHADER pTextureShader)
{
	if( !m_fnc.m_TFunc_D3DXFillVolumeTextureTX )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFillVolumeTextureTX );
	}
	return m_fnc.m_TFunc_D3DXFillVolumeTextureTX ( pTexture, pTextureShader );
}


HRESULT D3DXFilterTexture( LPDIRECT3DBASETEXTURE9 pBaseTexture,
						  CONST PALETTEENTRY * pPalette, UINT SrcLevel, DWORD MipFilter)
{
	if( !m_fnc.m_TFunc_D3DXFilterTexture )
	{
		DEF_TEMP_ERR_HANDLE( D3DXFilterTexture );
	}
	return m_fnc.m_TFunc_D3DXFilterTexture ( pBaseTexture,  pPalette,   SrcLevel,  
		MipFilter );
}



HRESULT D3DXGetImageInfoFromFile( const CHAR* pSrcFile, D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXGetImageInfoFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXGetImageInfoFromFileA );
	}
	return m_fnc.m_TFunc_D3DXGetImageInfoFromFileA ( pSrcFile,  pSrcInfo );
}


HRESULT D3DXGetImageInfoFromFileW( const WCHAR* pSrcFile, D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXGetImageInfoFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXGetImageInfoFromFileW );
	}
	return m_fnc.m_TFunc_D3DXGetImageInfoFromFileW ( pSrcFile,  pSrcInfo );
}



HRESULT D3DXGetImageInfoFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize,
										 D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXGetImageInfoFromFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXGetImageInfoFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXGetImageInfoFromFileInMemory ( pSrcData,  
		SrcDataSize, pSrcInfo );
}



HRESULT D3DXGetImageInfoFromResourceA( HMODULE hSrcModule, const CHAR* pSrcFile,
									 D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXGetImageInfoFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXGetImageInfoFromResourceA );
	}
	return m_fnc.m_TFunc_D3DXGetImageInfoFromResourceA ( hSrcModule, pSrcFile, pSrcInfo );
}



HRESULT D3DXGetImageInfoFromResourceW( HMODULE hSrcModule, const WCHAR* pSrcFile,
									 D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXGetImageInfoFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXGetImageInfoFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXGetImageInfoFromResourceW ( hSrcModule,   pSrcFile, pSrcInfo );
}




HRESULT D3DXLoadSurfaceFromFileA(LPDIRECT3DSURFACE9 pDestSurface,
								CONST PALETTEENTRY* pDestPalette,
								CONST RECT* pDestRect,
								CONST CHAR* pSrcFile,
								CONST RECT* pSrcRect,
								DWORD Filter,
								D3DCOLOR ColorKey,
								D3DXIMAGE_INFO* pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromFileA );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromFileA ( pDestSurface, pDestPalette,  
		pDestRect,  pSrcFile,  pSrcRect,  Filter,   ColorKey, pSrcInfo  );
}


HRESULT D3DXLoadSurfaceFromFileW(LPDIRECT3DSURFACE9 pDestSurface,
								CONST PALETTEENTRY* pDestPalette,
								CONST RECT* pDestRect,
								CONST WCHAR* pSrcFile,
								CONST RECT* pSrcRect,
								DWORD Filter,
								D3DCOLOR ColorKey,
								D3DXIMAGE_INFO* pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromFileW );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromFileW ( pDestSurface, pDestPalette,  
		pDestRect,  pSrcFile,  pSrcRect,  Filter,   ColorKey, pSrcInfo  );
}






HRESULT D3DXLoadSurfaceFromFileInMemory(LPDIRECT3DSURFACE9 pDestSurface,
										CONST PALETTEENTRY * pDestPalette,
										CONST RECT * pDestRect,
										LPCVOID pSrcData,
										UINT SrcData,
										CONST RECT * pSrcRect,
										DWORD Filter,
										D3DCOLOR ColorKey,
										D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromFileInMemory ( pDestSurface,
		pDestPalette, pDestRect,  pSrcData,  SrcData,  pSrcRect,  Filter,
		ColorKey, pSrcInfo );
}




HRESULT D3DXLoadSurfaceFromMemory(LPDIRECT3DSURFACE9 pDestSurface,
								  CONST PALETTEENTRY * pDestPalette,
								  CONST RECT * pDestRect,
								  LPCVOID pSrcMemory,
								  D3DFORMAT SrcFormat,
								  UINT SrcPitch,
								  CONST PALETTEENTRY * pSrcPalette,
								  CONST RECT * pSrcRect,
								  DWORD Filter,
								  D3DCOLOR ColorKey)
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromMemory );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromMemory ( pDestSurface,
		pDestPalette,  pDestRect, pSrcMemory,  SrcFormat, SrcPitch,
		pSrcPalette,  pSrcRect,  Filter,  ColorKey );
}



HRESULT D3DXLoadSurfaceFromResourceA(LPDIRECT3DSURFACE9 pDestSurface,
									CONST PALETTEENTRY * pDestPalette,
									CONST RECT * pDestRect,
									HMODULE hSrcModule,
									const CHAR* pSrcResource,
									CONST RECT * pSrcRect,
									DWORD Filter,
									D3DCOLOR ColorKey,
									D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromResourceA );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromResourceA ( pDestSurface,
		pDestPalette, pDestRect,  hSrcModule, pSrcResource, pSrcRect,  Filter, 
		ColorKey,  pSrcInfo );
}



HRESULT D3DXLoadSurfaceFromResourceW(LPDIRECT3DSURFACE9 pDestSurface,
									CONST PALETTEENTRY * pDestPalette,
									CONST RECT * pDestRect,
									HMODULE hSrcModule,
									const WCHAR* pSrcResource,
									CONST RECT * pSrcRect,
									DWORD Filter,
									D3DCOLOR ColorKey,
									D3DXIMAGE_INFO * pSrcInfo)
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromResourceW ( pDestSurface,
			pDestPalette, pDestRect,  hSrcModule, pSrcResource, pSrcRect,  Filter, 
			ColorKey,  pSrcInfo );
}




HRESULT D3DXLoadSurfaceFromSurface(
								   LPDIRECT3DSURFACE9 pDestSurface,
								   CONST PALETTEENTRY * pDestPalette,
								   CONST RECT * pDestRect,
								   LPDIRECT3DSURFACE9 pSrcSurface,
								   CONST PALETTEENTRY * pSrcPalette,
								   CONST RECT * pSrcRect,
								   DWORD Filter,
								   D3DCOLOR ColorKey )
{
	if( !m_fnc.m_TFunc_D3DXLoadSurfaceFromSurface)
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadSurfaceFromSurface );
	}
	return m_fnc.m_TFunc_D3DXLoadSurfaceFromSurface (  pDestSurface,
		pDestPalette,  pDestRect,  pSrcSurface,  pSrcPalette,
		pSrcRect,  Filter,  ColorKey );
}




HRESULT D3DXLoadVolumeFromFileA(LPDIRECT3DVOLUME9 pDestVolume,
							   CONST PALETTEENTRY * pDestPalette,
							   CONST D3DBOX * pDestBox,
							   const CHAR* pSrcFile,
							   CONST D3DBOX * pSrcBox,
							   DWORD Filter,
							   D3DCOLOR ColorKey,
							   D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromFileA );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromFileA ( pDestVolume,
		pDestPalette, pDestBox, pSrcFile, pSrcBox, Filter, ColorKey, pSrcInfo);
}


HRESULT D3DXLoadVolumeFromFileW(LPDIRECT3DVOLUME9 pDestVolume,
							   CONST PALETTEENTRY * pDestPalette,
							   CONST D3DBOX * pDestBox,
							   const WCHAR* pSrcFile,
							   CONST D3DBOX * pSrcBox,
							   DWORD Filter,
							   D3DCOLOR ColorKey,
							   D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromFileW );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromFileW ( pDestVolume,
		pDestPalette,  pDestBox,  pSrcFile,  pSrcBox,  Filter,  ColorKey,  pSrcInfo );
}




HRESULT D3DXLoadVolumeFromFileInMemory(LPDIRECT3DVOLUME9 pDestVolume,
									   CONST PALETTEENTRY * pDestPalette,
									   CONST D3DBOX * pDestBox,
									   LPCVOID pSrcData,
									   UINT SrcDataSize,
									   CONST D3DBOX * pSrcBox,
									   DWORD Filter,
									   D3DCOLOR ColorKey,
									   D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromFileInMemory ( pDestVolume,
		pDestPalette,  pDestBox,  pSrcData,  SrcDataSize,  pSrcBox,  Filter,
		ColorKey,  pSrcInfo );
}


HRESULT D3DXLoadVolumeFromMemory(LPDIRECT3DVOLUME9 pDestVolume,
								 CONST PALETTEENTRY * pDestPalette,
								 CONST D3DBOX * pDestBox,
								 LPCVOID pSrcMemory,
								 D3DFORMAT SrcFormat,
								 UINT SrcRowPitch,
								 UINT SrcSlicePitch,
								 CONST PALETTEENTRY * pSrcPalette,
								 CONST D3DBOX * pSrcBox,
								 DWORD Filter,
								 D3DCOLOR ColorKey )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromMemory );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromMemory ( pDestVolume,  pDestPalette,  pDestBox,
		pSrcMemory,  SrcFormat,  SrcRowPitch,  SrcSlicePitch, pSrcPalette, pSrcBox,
		Filter,  ColorKey );
}



HRESULT D3DXLoadVolumeFromResourceA( LPDIRECT3DVOLUME9 pDestVolume,
								   CONST PALETTEENTRY * pDestPalette,
								   CONST D3DBOX * pDestBox,
								   HMODULE hSrcModule,
								   const CHAR* pSrcResource,
								   CONST D3DBOX * pSrcBox,
								   DWORD Filter,
								   D3DCOLOR ColorKey,
								   D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromResourceA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromResourceA );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromResourceA ( pDestVolume,  pDestPalette,
		pDestBox, hSrcModule, pSrcResource, pSrcBox, Filter, ColorKey,  pSrcInfo );
}



HRESULT D3DXLoadVolumeFromResourceW( LPDIRECT3DVOLUME9 pDestVolume,
								   CONST PALETTEENTRY * pDestPalette,
								   CONST D3DBOX * pDestBox,
								   HMODULE hSrcModule,
								   const WCHAR* pSrcResource,
								   CONST D3DBOX * pSrcBox,
								   DWORD Filter,
								   D3DCOLOR ColorKey,
								   D3DXIMAGE_INFO * pSrcInfo )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromResourceW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromResourceW );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromResourceW ( pDestVolume,  pDestPalette,
		pDestBox, hSrcModule, pSrcResource, pSrcBox, Filter, ColorKey,  pSrcInfo );
}





HRESULT D3DXLoadVolumeFromVolume( LPDIRECT3DVOLUME9 pDestVolume,
			 CONST PALETTEENTRY * pDestPalette,
			 CONST D3DBOX * pDestBox,
			 LPDIRECT3DVOLUME9 pSrcVolume,
			 CONST PALETTEENTRY * pSrcPalette,
			 CONST D3DBOX * pSrcBox,
			 DWORD Filter,
			 D3DCOLOR ColorKey )
{
	if( !m_fnc.m_TFunc_D3DXLoadVolumeFromVolume )
	{
		DEF_TEMP_ERR_HANDLE( D3DXLoadVolumeFromVolume );
	}
	return m_fnc.m_TFunc_D3DXLoadVolumeFromVolume (  pDestVolume, pDestPalette,
		pDestBox,  pSrcVolume,  pSrcPalette,  pSrcBox , Filter,  ColorKey  );
}


HRESULT D3DXSaveSurfaceToFileA( const CHAR* pDestFile,    D3DXIMAGE_FILEFORMAT DestFormat,
							  LPDIRECT3DSURFACE9 pSrcSurface,    CONST PALETTEENTRY * pSrcPalette,
							  CONST RECT * pSrcRect )
{
	if( !m_fnc.m_TFunc_D3DXSaveSurfaceToFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveSurfaceToFileA );
	}
	return m_fnc.m_TFunc_D3DXSaveSurfaceToFileA (pDestFile,  DestFormat,
		  pSrcSurface,    pSrcPalette,  pSrcRect   );
}


HRESULT D3DXSaveSurfaceToFileW( const WCHAR* pDestFile,    D3DXIMAGE_FILEFORMAT DestFormat,
							  LPDIRECT3DSURFACE9 pSrcSurface,    CONST PALETTEENTRY * pSrcPalette,
							  CONST RECT * pSrcRect )
{
	if( !m_fnc.m_TFunc_D3DXSaveSurfaceToFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveSurfaceToFileW );
	}
	return m_fnc.m_TFunc_D3DXSaveSurfaceToFileW (pDestFile,      DestFormat,
		  pSrcSurface,    pSrcPalette,     pSrcRect  );
}





HRESULT D3DXSaveSurfaceToFileInMemory(
									  LPD3DXBUFFER * ppDestBuf,
									  D3DXIMAGE_FILEFORMAT DestFormat,
									  LPDIRECT3DSURFACE9 pSrcSurface,
									  CONST PALETTEENTRY * pSrcPalette,
									  CONST RECT * pSrcRect)
{
	if( !m_fnc.m_TFunc_D3DXSaveSurfaceToFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveSurfaceToFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXSaveSurfaceToFileInMemory ( ppDestBuf,  DestFormat,
		pSrcSurface,  pSrcPalette, pSrcRect );
}


HRESULT D3DXSaveTextureToFileA(const CHAR* pDestFile, D3DXIMAGE_FILEFORMAT DestFormat,
							  LPDIRECT3DBASETEXTURE9 pSrcTexture,   CONST PALETTEENTRY * pSrcPalette )
{
	if( !m_fnc.m_TFunc_D3DXSaveTextureToFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveTextureToFileA );
	}
	return m_fnc.m_TFunc_D3DXSaveTextureToFileA ( pDestFile,  DestFormat,  pSrcTexture,
		pSrcPalette );
}

HRESULT D3DXSaveTextureToFileW(const WCHAR* pDestFile, D3DXIMAGE_FILEFORMAT DestFormat,
							  LPDIRECT3DBASETEXTURE9 pSrcTexture,   CONST PALETTEENTRY * pSrcPalette )
{
	if( !m_fnc.m_TFunc_D3DXSaveTextureToFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveTextureToFileW );
	}
	return m_fnc.m_TFunc_D3DXSaveTextureToFileW ( pDestFile,  DestFormat,  pSrcTexture,
		pSrcPalette );
}



HRESULT D3DXSaveTextureToFileInMemory(LPD3DXBUFFER * ppDestBuf,
									  D3DXIMAGE_FILEFORMAT DestFormat,
									  LPDIRECT3DBASETEXTURE9 pSrcTexture,
									  CONST PALETTEENTRY * pSrcPalette  )
{
	if( !m_fnc.m_TFunc_D3DXSaveTextureToFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveTextureToFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXSaveTextureToFileInMemory ( ppDestBuf,  DestFormat,
		pSrcTexture, pSrcPalette  );
}



HRESULT D3DXSaveVolumeToFileA( const CHAR* pDestFile,
							 D3DXIMAGE_FILEFORMAT DestFormat,
							 LPDIRECT3DVOLUME9 pSrcVolume,
							 CONST PALETTEENTRY * pSrcPalette,
							 CONST D3DBOX * pSrcBox  )
{
	if( !m_fnc.m_TFunc_D3DXSaveVolumeToFileA )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveVolumeToFileA );
	}
	return m_fnc.m_TFunc_D3DXSaveVolumeToFileA ( pDestFile,  DestFormat, pSrcVolume,
		pSrcPalette,  pSrcBox  );
}


HRESULT D3DXSaveVolumeToFileW( const WCHAR* pDestFile,
							 D3DXIMAGE_FILEFORMAT DestFormat,
							 LPDIRECT3DVOLUME9 pSrcVolume,
							 CONST PALETTEENTRY * pSrcPalette,
							 CONST D3DBOX * pSrcBox  )
{
	if( !m_fnc.m_TFunc_D3DXSaveVolumeToFileW )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveVolumeToFileW );
	}
	return m_fnc.m_TFunc_D3DXSaveVolumeToFileW ( pDestFile,  DestFormat, pSrcVolume,
		pSrcPalette,  pSrcBox  );
}



HRESULT D3DXSaveVolumeToFileInMemory(
									 LPD3DXBUFFER * ppDestBuf,
									 D3DXIMAGE_FILEFORMAT DestFormat,
									 LPDIRECT3DVOLUME9 pSrcVolume,
									 CONST PALETTEENTRY * pSrcPalette,
									 CONST D3DBOX * pSrcBox )
{
	if( !m_fnc.m_TFunc_D3DXSaveVolumeToFileInMemory )
	{
		DEF_TEMP_ERR_HANDLE( D3DXSaveVolumeToFileInMemory );
	}
	return m_fnc.m_TFunc_D3DXSaveVolumeToFileInMemory ( ppDestBuf, DestFormat,
		pSrcVolume, pSrcPalette,  pSrcBox );
}





 


//-------------------------------------------------------------------------


	Functions m_fnc;

protected:

    void throw_error(int code)
	{
		assert(false);
		if(code == 0)
		{

		}
		throw std::runtime_error("Null pointer !");
	};


	HMODULE m_hmDLL;
	unsigned int m_versDll;

};
 
 

}
// end namespace d3dx9_dynamic_load

}
// end namespace d3d9

}
// end namespace graphics

}
// end namespace gb


#pragma warning( pop )

#endif // #if ( defined(WIN32) && defined(GB_D3D9) )

// end file