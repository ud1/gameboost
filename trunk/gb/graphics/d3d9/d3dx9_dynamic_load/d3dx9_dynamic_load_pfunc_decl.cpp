#include "stdafx.h"

#if ( defined(WIN32) && defined(GB_D3D9) )

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
#include <gb/macro.h>

#include <stdlib.h>
#include <assert.h>


//!  Поиск точек входа
#define __HANDLE_DLL_ENTRY(funcname)   m_TFunc_##funcname =  \
								( TFunc_##funcname ) ::GetProcAddress(hm, GB_MAKE_STR(funcname) ); \
								\
		if(!m_TFunc_##funcname) {\
		  handleNotFoundAddr( GB_MAKE_STR(funcname) ); \
		  /* return NERROR;*/ \
		 }

//==============================================================
int gb::graphics::d3d9::d3dx9_dynamic_load::Functions::GetProcAddr(const HMODULE hm)
{
 
			void* ptr = NULL;
			const int NERROR = -1;


	//------------------------------------------------------------
	//	    General Purpose Functions
	//------------------------------------------------------------

   int _begin = 0;
   
     __HANDLE_DLL_ENTRY(D3DXCheckVersion) 
 

   __HANDLE_DLL_ENTRY(D3DXCreateBuffer)
 
	__HANDLE_DLL_ENTRY(D3DXCreateFontA)
 
	__HANDLE_DLL_ENTRY(D3DXCreateFontW)
 
	__HANDLE_DLL_ENTRY(D3DXCreateFontIndirectA)
 

	__HANDLE_DLL_ENTRY(D3DXCreateFontIndirectW)
 
 	__HANDLE_DLL_ENTRY(D3DXCreateLine)
 

	__HANDLE_DLL_ENTRY(D3DXCreateRenderToEnvMap)
 
 	__HANDLE_DLL_ENTRY(D3DXCreateRenderToSurface)
 
 	__HANDLE_DLL_ENTRY(D3DXCreateSprite)
 
	__HANDLE_DLL_ENTRY(D3DXDebugMute)
 

  __HANDLE_DLL_ENTRY(D3DXGetDriverLevel)
 
	//------------------------------------------------------------
	//	                math    functions
	//------------------------------------------------------------


   __HANDLE_DLL_ENTRY(D3DXMatrixMultiply)
 
    __HANDLE_DLL_ENTRY(D3DXMatrixInverse)
 


	//------------------------------------------------------------
	//	     MESH functions
	//------------------------------------------------------------

	__HANDLE_DLL_ENTRY(D3DXBoxBoundProbe)

	__HANDLE_DLL_ENTRY(D3DXCleanMesh)

	__HANDLE_DLL_ENTRY(D3DXComputeBoundingBox)

	__HANDLE_DLL_ENTRY(D3DXComputeBoundingSphere)

	__HANDLE_DLL_ENTRY(D3DXComputeNormals)

	__HANDLE_DLL_ENTRY(D3DXComputeTangent)

	__HANDLE_DLL_ENTRY(D3DXComputeTangentFrame)


	__HANDLE_DLL_ENTRY(D3DXComputeTangentFrameEx)


	__HANDLE_DLL_ENTRY(D3DXConcatenateMeshes)

	__HANDLE_DLL_ENTRY(D3DXCreateMesh)

	__HANDLE_DLL_ENTRY(D3DXCreateMeshFVF)


	__HANDLE_DLL_ENTRY(D3DXDeclaratorFromFVF)

	__HANDLE_DLL_ENTRY(D3DXGetFVFVertexSize)

	__HANDLE_DLL_ENTRY(D3DXIntersect)

	__HANDLE_DLL_ENTRY(D3DXIntersectSubset)

	__HANDLE_DLL_ENTRY(D3DXIntersectTri)


	__HANDLE_DLL_ENTRY(D3DXLoadMeshFromXA)


	__HANDLE_DLL_ENTRY(D3DXLoadMeshFromXW)


	__HANDLE_DLL_ENTRY(D3DXLoadMeshFromXInMemory)

	__HANDLE_DLL_ENTRY(D3DXLoadMeshFromXof)

	__HANDLE_DLL_ENTRY(D3DXLoadMeshFromXResource)

	__HANDLE_DLL_ENTRY(D3DXLoadPatchMeshFromXof)



	#pragma message(  "ks777: d3dx loader:: ПРОВЕРИТЬ D3DXLoadSkinMeshFromXof  "  __FILE__ )

	__HANDLE_DLL_ENTRY(D3DXLoadSkinMeshFromXof)

	__HANDLE_DLL_ENTRY(D3DXOptimizeFaces)


	__HANDLE_DLL_ENTRY(D3DXOptimizeVertices)

	__HANDLE_DLL_ENTRY(D3DXRectPatchSize)

	__HANDLE_DLL_ENTRY(D3DXSaveMeshToXA)

	__HANDLE_DLL_ENTRY(D3DXSaveMeshToXW)

	__HANDLE_DLL_ENTRY(D3DXSimplifyMesh)
	__HANDLE_DLL_ENTRY(D3DXSplitMesh)
	__HANDLE_DLL_ENTRY(D3DXTriPatchSize)
	__HANDLE_DLL_ENTRY(D3DXValidMesh)	
	__HANDLE_DLL_ENTRY(D3DXValidPatchMesh)
	__HANDLE_DLL_ENTRY(D3DXWeldVertices)



	//------------------------------------------------------------
	//	    Shader functions
	//------------------------------------------------------------

	
   __HANDLE_DLL_ENTRY(D3DXAssembleShader)
//  m_TFunc_D3DXAssembleShader =(TFunc_D3DXAssembleShader )::GetProcAddress(hm,"D3DXAssembleShader");
//	if(!m_TFunc_D3DXAssembleShader) {  handleNotFoundAddr( "D3DXAssembleShader" );  return NERROR; }

   __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromFileA)
 // m_TFunc_D3DXAssembleShaderFromFileA= (TFunc_D3DXAssembleShaderFromFileA)::GetProcAddress(hm,"D3DXAssembleShaderFromFileA"); 
//	if(!m_TFunc_D3DXAssembleShaderFromFileA) {  handleNotFoundAddr( "D3DXAssembleShaderFromFileA" );  return NERROR; }

   __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromFileW)	
//  m_TFunc_D3DXAssembleShaderFromFileW= (TFunc_D3DXAssembleShaderFromFileW)::GetProcAddress(hm,"D3DXAssembleShaderFromFileW"); 
//	if(!m_TFunc_D3DXAssembleShaderFromFileW) {  handleNotFoundAddr( "D3DXAssembleShaderFromFileW" );  return NERROR; }

   __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromResourceA)
 // m_TFunc_D3DXAssembleShaderFromResourceA= (TFunc_D3DXAssembleShaderFromResourceA)::GetProcAddress(hm,"D3DXAssembleShaderFromResourceA"); 
//	if(!m_TFunc_D3DXAssembleShaderFromResourceA) {  handleNotFoundAddr( "D3DXAssembleShaderFromResourceA" );  return NERROR; }

   __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromResourceW)	
// m_TFunc_D3DXAssembleShaderFromResourceW= (TFunc_D3DXAssembleShaderFromResourceW)::GetProcAddress(hm,"D3DXAssembleShaderFromResourceW"); 
//	if(!m_TFunc_D3DXAssembleShaderFromResourceW) {  handleNotFoundAddr( "D3DXAssembleShaderFromResourceW" );  return NERROR; }


   __HANDLE_DLL_ENTRY(D3DXCompileShader)
// m_TFunc_D3DXCompileShader= (TFunc_D3DXCompileShader)::GetProcAddress(hm,"D3DXCompileShader");  
//	if(!m_TFunc_D3DXCompileShader) {  handleNotFoundAddr( "D3DXCompileShader" );  return NERROR; }

 
   __HANDLE_DLL_ENTRY(D3DXCompileShaderFromFileA)
// m_TFunc_D3DXCompileShaderFromFileA= (TFunc_D3DXCompileShaderFromFileA)::GetProcAddress(hm,"D3DXCompileShaderFromFileA"); 
//	if(!m_TFunc_D3DXCompileShaderFromFileA) {  handleNotFoundAddr( "D3DXCompileShaderFromFileA" );  return NERROR; }

   __HANDLE_DLL_ENTRY(D3DXCompileShaderFromFileW)	
// m_TFunc_D3DXCompileShaderFromFileW= (TFunc_D3DXCompileShaderFromFileW)::GetProcAddress(hm,"D3DXCompileShaderFromFileW"); 
//	if(!m_TFunc_D3DXCompileShaderFromFileW) {  handleNotFoundAddr( "D3DXCompileShaderFromFileW" );  return NERROR; }


   __HANDLE_DLL_ENTRY(D3DXCompileShaderFromResourceA)
// m_TFunc_D3DXCompileShaderFromResourceA= (TFunc_D3DXCompileShaderFromResourceA)::GetProcAddress(hm,"D3DXCompileShaderFromResourceA"); 
 //	if(!m_TFunc_D3DXCompileShaderFromResourceA) {  handleNotFoundAddr( "D3DXCompileShaderFromResourceA" );  return NERROR; }

	
  __HANDLE_DLL_ENTRY(D3DXCompileShaderFromResourceW)
 // m_TFunc_D3DXCompileShaderFromResourceW= (TFunc_D3DXCompileShaderFromResourceW)::GetProcAddress(hm,"D3DXCompileShaderFromResourceW"); 
//	if(!m_TFunc_D3DXCompileShaderFromResourceW) {  handleNotFoundAddr( "D3DXCompileShaderFromResourceW" );  return NERROR; }


  __HANDLE_DLL_ENTRY(D3DXCreateTextureShader)
 // m_TFunc_D3DXCreateTextureShader= (TFunc_D3DXCreateTextureShader)::GetProcAddress(hm,"D3DXCreateTextureShader"); 
//	if(!m_TFunc_D3DXCreateTextureShader) {  handleNotFoundAddr( "D3DXCreateTextureShader" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXDisassembleShader)	
 // m_TFunc_D3DXDisassembleShader= (TFunc_D3DXDisassembleShader)::GetProcAddress(hm,"D3DXDisassembleShader"); 
//	if(!m_TFunc_D3DXDisassembleShader) {  handleNotFoundAddr( "D3DXDisassembleShader" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXFindShaderComment)	
//  m_TFunc_D3DXFindShaderComment= (TFunc_D3DXFindShaderComment)::GetProcAddress(hm,"D3DXFindShaderComment"); 
//	if(!m_TFunc_D3DXFindShaderComment) {  handleNotFoundAddr( "D3DXFindShaderComment" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetPixelShaderProfile)
 // m_TFunc_D3DXGetPixelShaderProfile= (TFunc_D3DXGetPixelShaderProfile)::GetProcAddress(hm,"D3DXGetPixelShaderProfile"); 
//	if(!m_TFunc_D3DXGetPixelShaderProfile) {  handleNotFoundAddr( "D3DXGetPixelShaderProfile" );  return NERROR; }

	  __HANDLE_DLL_ENTRY(D3DXGetShaderConstantTable)
 //m_TFunc_D3DXGetShaderConstantTable= (TFunc_D3DXGetShaderConstantTable)::GetProcAddress(hm,"D3DXGetShaderConstantTable"); 
 //	if(!m_TFunc_D3DXGetShaderConstantTable) {  handleNotFoundAddr( "D3DXGetShaderConstantTable" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderConstantTableEx)	
 // m_TFunc_D3DXGetShaderConstantTableEx= (TFunc_D3DXGetShaderConstantTableEx)::GetProcAddress(hm,"D3DXGetShaderConstantTableEx"); 
 //	if(!m_TFunc_D3DXGetShaderConstantTableEx) {  handleNotFoundAddr( "D3DXGetShaderConstantTableEx" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderInputSemantics)	
 // m_TFunc_D3DXGetShaderInputSemantics= (TFunc_D3DXGetShaderInputSemantics)::GetProcAddress(hm,"D3DXGetShaderInputSemantics"); 
//	if(!m_TFunc_D3DXGetShaderInputSemantics) {  handleNotFoundAddr( "D3DXGetShaderInputSemantics" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderOutputSemantics)	
//  m_TFunc_D3DXGetShaderOutputSemantics= (TFunc_D3DXGetShaderOutputSemantics)::GetProcAddress(hm,"D3DXGetShaderOutputSemantics"); 
//	if(!m_TFunc_D3DXGetShaderOutputSemantics) {  handleNotFoundAddr( "D3DXGetShaderOutputSemantics" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderSamplers)	
 // m_TFunc_D3DXGetShaderSamplers= (TFunc_D3DXGetShaderSamplers)::GetProcAddress(hm,"D3DXGetShaderSamplers"); 
//	if(!m_TFunc_D3DXGetShaderSamplers) {  handleNotFoundAddr( "D3DXGetShaderSamplers" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderSize)	
//  m_TFunc_D3DXGetShaderSize= (TFunc_D3DXGetShaderSize)::GetProcAddress(hm,"D3DXGetShaderSize"); 
//	if(!m_TFunc_D3DXGetShaderSize) {  handleNotFoundAddr( "D3DXGetShaderSize" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetShaderVersion)	
// m_TFunc_D3DXGetShaderVersion= (TFunc_D3DXGetShaderVersion)::GetProcAddress(hm,"D3DXGetShaderVersion"); 
//	if(!m_TFunc_D3DXGetShaderVersion) {  handleNotFoundAddr( "D3DXGetShaderVersion" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXGetVertexShaderProfile)	
 // m_TFunc_D3DXGetVertexShaderProfile= (TFunc_D3DXGetVertexShaderProfile)::GetProcAddress(hm,"D3DXGetVertexShaderProfile"); 
 //	if(!m_TFunc_D3DXGetVertexShaderProfile) {  handleNotFoundAddr( "D3DXGetVertexShaderProfile" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXPreprocessShader)	
//  m_TFunc_D3DXPreprocessShader= (TFunc_D3DXPreprocessShader)::GetProcAddress(hm,"D3DXPreprocessShader"); 
// 	if(!m_TFunc_D3DXPreprocessShader) {  handleNotFoundAddr( "D3DXPreprocessShader" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromFileA)
 // m_TFunc_D3DXPreprocessShaderFromFileA = (TFunc_D3DXPreprocessShaderFromFileA) ::GetProcAddress(hm,"D3DXPreprocessShaderFromFileA"); 
//	if(!m_TFunc_D3DXPreprocessShaderFromFileA) {  handleNotFoundAddr( "D3DXPreprocessShaderFromFileA" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromFileW)	
//	m_TFunc_D3DXPreprocessShaderFromFileW = (TFunc_D3DXPreprocessShaderFromFileW) ::GetProcAddress(hm,"D3DXPreprocessShaderFromFileW"); 
//	if(!m_TFunc_D3DXPreprocessShaderFromFileW) {  handleNotFoundAddr( "D3DXPreprocessShaderFromFileW" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromResourceA)
//  m_TFunc_D3DXPreprocessShaderFromResourceA = (TFunc_D3DXPreprocessShaderFromResourceA) ::GetProcAddress(hm,"D3DXPreprocessShaderFromResourceA"); 
// 	if(!m_TFunc_D3DXPreprocessShaderFromResourceA) {  handleNotFoundAddr( "D3DXPreprocessShaderFromResourceA" );  return NERROR; }

  __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromResourceW)	
//	m_TFunc_D3DXPreprocessShaderFromResourceW = (TFunc_D3DXPreprocessShaderFromResourceW) ::GetProcAddress(hm,"D3DXPreprocessShaderFromResourceW"); 
//	if(!m_TFunc_D3DXPreprocessShaderFromResourceW) {  handleNotFoundAddr( "D3DXPreprocessShaderFromResourceW" );  return NERROR; }


	
	
	//------------------------------------------------------------
	//	   Effect functions
	//------------------------------------------------------------
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffect)
	//m_TFunc_D3DXCreateEffect = (TFunc_D3DXCreateEffect)::GetProcAddress(hm,"D3DXCreateEffect");
	//	if(!m_TFunc_D3DXCreateEffect) {  handleNotFoundAddr( "D3DXCreateEffect" );  return NERROR; }
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectEx)	
	//m_TFunc_D3DXCreateEffectEx= (TFunc_D3DXCreateEffectEx)::GetProcAddress(hm,"D3DXCreateEffectEx");
	//	if(!m_TFunc_D3DXCreateEffectEx) {  handleNotFoundAddr( "D3DXCreateEffectEx" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompiler)	
	//m_TFunc_D3DXCreateEffectCompiler= (TFunc_D3DXCreateEffectCompiler)::GetProcAddress(hm,"D3DXCreateEffectCompiler");
	//	if(!m_TFunc_D3DXCreateEffectCompiler) {  handleNotFoundAddr( "D3DXCreateEffectCompiler" );  return NERROR; }		
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromFileA)	
	//m_TFunc_D3DXCreateEffectCompilerFromFileA= (TFunc_D3DXCreateEffectCompilerFromFileA)::GetProcAddress(hm,"D3DXCreateEffectCompilerFromFileA"); 
	//	if(!m_TFunc_D3DXCreateEffectCompilerFromFileA) {  handleNotFoundAddr( "D3DXCreateEffectCompilerFromFileA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromFileW)	
	//m_TFunc_D3DXCreateEffectCompilerFromFileW= (TFunc_D3DXCreateEffectCompilerFromFileW)::GetProcAddress(hm,"D3DXCreateEffectCompilerFromFileW");
	//	if(!m_TFunc_D3DXCreateEffectCompilerFromFileW) {  handleNotFoundAddr( "D3DXCreateEffectCompilerFromFileW" );  return NERROR; }
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromResourceA)	
	//m_TFunc_D3DXCreateEffectCompilerFromResourceA= (TFunc_D3DXCreateEffectCompilerFromResourceA)::GetProcAddress(hm,"D3DXCreateEffectCompilerFromResourceA");  
	//	if(!m_TFunc_D3DXCreateEffectCompilerFromResourceA) {  handleNotFoundAddr( "D3DXCreateEffectCompilerFromResourceA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromResourceW)	
	//m_TFunc_D3DXCreateEffectCompilerFromResourceW= (TFunc_D3DXCreateEffectCompilerFromResourceW)::GetProcAddress(hm,"D3DXCreateEffectCompilerFromResourceW");
	//	if(!m_TFunc_D3DXCreateEffectCompilerFromResourceW) {  handleNotFoundAddr( "D3DXCreateEffectCompilerFromResourceW" );  return NERROR; }
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileA)	
	//m_TFunc_D3DXCreateEffectFromFileA= (TFunc_D3DXCreateEffectFromFileA)::GetProcAddress(hm,"D3DXCreateEffectFromFileA");  
	//	if(!m_TFunc_D3DXCreateEffectFromFileA) {  handleNotFoundAddr( "D3DXCreateEffectFromFileA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileW)	
	//m_TFunc_D3DXCreateEffectFromFileW= (TFunc_D3DXCreateEffectFromFileW)::GetProcAddress(hm,"D3DXCreateEffectFromFileW");
	//	if(!m_TFunc_D3DXCreateEffectFromFileW) {  handleNotFoundAddr( "D3DXCreateEffectFromFileW" );  return NERROR; }

    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileExA)	
//	m_TFunc_D3DXCreateEffectFromFileExA= (TFunc_D3DXCreateEffectFromFileExA)::GetProcAddress(hm,"D3DXCreateEffectFromFileExA");
	//	if(!m_TFunc_D3DXCreateEffectFromFileExA) {  handleNotFoundAddr( "D3DXCreateEffectFromFileExA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileExW)	
	//m_TFunc_D3DXCreateEffectFromFileExW= (TFunc_D3DXCreateEffectFromFileExW)::GetProcAddress(hm,"D3DXCreateEffectFromFileExW");
	//	if(!m_TFunc_D3DXCreateEffectFromFileExW) {  handleNotFoundAddr( "D3DXCreateEffectFromFileExW" );  return NERROR; }
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceA)	
	//m_TFunc_D3DXCreateEffectFromResourceA= (TFunc_D3DXCreateEffectFromResourceA)::GetProcAddress(hm,"D3DXCreateEffectFromResourceA");  
	//	if(!m_TFunc_D3DXCreateEffectFromResourceA) {  handleNotFoundAddr( "D3DXCreateEffectFromResourceA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceW)	
	//m_TFunc_D3DXCreateEffectFromResourceW= (TFunc_D3DXCreateEffectFromResourceW)::GetProcAddress(hm,"D3DXCreateEffectFromResourceW");
	//	if(!m_TFunc_D3DXCreateEffectFromResourceW) {  handleNotFoundAddr( "D3DXCreateEffectFromResourceW" );  return NERROR; }
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceExA)	
	//m_TFunc_D3DXCreateEffectFromResourceExA= (TFunc_D3DXCreateEffectFromResourceExA)::GetProcAddress(hm,"D3DXCreateEffectFromResourceExA"); 
	//	if(!m_TFunc_D3DXCreateEffectFromResourceExA) {  handleNotFoundAddr( "D3DXCreateEffectFromResourceExA" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceExW)	
	//m_TFunc_D3DXCreateEffectFromResourceExW= (TFunc_D3DXCreateEffectFromResourceExW)::GetProcAddress(hm,"D3DXCreateEffectFromResourceExW");
	//	if(!m_TFunc_D3DXCreateEffectFromResourceExW) {  handleNotFoundAddr( "D3DXCreateEffectFromResourceExW" );  return NERROR; }
		
    __HANDLE_DLL_ENTRY(D3DXCreateEffectPool)		
	//m_TFunc_D3DXCreateEffectPool= (TFunc_D3DXCreateEffectPool)::GetProcAddress(hm,"D3DXCreateEffectPool"); 
	//	if(!m_TFunc_D3DXCreateEffectPool) {  handleNotFoundAddr( "D3DXCreateEffectPool" );  return NERROR; }	
	
    __HANDLE_DLL_ENTRY(D3DXDisassembleEffect)	
//	m_TFunc_D3DXDisassembleEffect= (TFunc_D3DXDisassembleEffect)::GetProcAddress(hm,"D3DXDisassembleEffect");
	//	if(!m_TFunc_D3DXDisassembleEffect) {  handleNotFoundAddr( "D3DXDisassembleEffect" );  return NERROR; }

	//-----------------------------------------------------------------------
	//		   shared   drawing functions
	//-----------------------------------------------------------------------

	
	
    __HANDLE_DLL_ENTRY(D3DXCreateBox)	
//m_TFunc_D3DXCreateBox = (TFunc_D3DXCreateBox)::GetProcAddress(hm,"D3DXCreateBox");
//if(!m_TFunc_D3DXCreateBox) {  handleNotFoundAddr( "D3DXCreateBox" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreateCylinder)	
//m_TFunc_D3DXCreateCylinder = (TFunc_D3DXCreateCylinder)::GetProcAddress(hm,"D3DXCreateCylinder");
//if(!m_TFunc_D3DXCreateCylinder) {  handleNotFoundAddr( "D3DXCreateCylinder" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreatePolygon)	
//m_TFunc_D3DXCreatePolygon = (TFunc_D3DXCreatePolygon)::GetProcAddress(hm,"D3DXCreatePolygon");
//if(!m_TFunc_D3DXCreatePolygon) {  handleNotFoundAddr( "D3DXCreatePolygon" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreateSphere)	
//m_TFunc_D3DXCreateSphere = (TFunc_D3DXCreateSphere)::GetProcAddress(hm,"D3DXCreateSphere");
//if(!m_TFunc_D3DXCreateSphere) {  handleNotFoundAddr( "D3DXCreateSphere" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreateTeapot)	
//m_TFunc_D3DXCreateTeapot = (TFunc_D3DXCreateTeapot)::GetProcAddress(hm,"D3DXCreateTeapot");
//if(!m_TFunc_D3DXCreateTeapot) {  handleNotFoundAddr( "D3DXCreateTeapot" );  return NERROR; }



    __HANDLE_DLL_ENTRY(D3DXCreateTextA)	
//m_TFunc_D3DXCreateTextA = (TFunc_D3DXCreateTextA)::GetProcAddress(hm,"D3DXCreateTextA"); 
//if(!m_TFunc_D3DXCreateTextA) {  handleNotFoundAddr( "D3DXCreateTextA" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreateTextW)	
//m_TFunc_D3DXCreateTextW = (TFunc_D3DXCreateTextW)::GetProcAddress(hm,"D3DXCreateTextW"); 
//if(!m_TFunc_D3DXCreateTextW) {  handleNotFoundAddr( "D3DXCreateTextW" );  return NERROR; }



    __HANDLE_DLL_ENTRY(D3DXCreateBox)	
//m_TFunc_D3DXCreateBox = (TFunc_D3DXCreateBox)::GetProcAddress(hm,"D3DXCreateBox");
//if(!m_TFunc_D3DXCreateBox) {  handleNotFoundAddr( "D3DXCreateBox" );  return NERROR; }


    __HANDLE_DLL_ENTRY(D3DXCreateTorus)	
//m_TFunc_D3DXCreateTorus = (TFunc_D3DXCreateTorus)::GetProcAddress(hm,"D3DXCreateTorus");
//if(!m_TFunc_D3DXCreateTorus) {  handleNotFoundAddr( "D3DXCreateTorus" );  return NERROR; }
	
	
	
	//-------------------------------------------------------
	//	  texturing functions
	//-------------------------------------------------------

 

      __HANDLE_DLL_ENTRY(D3DXCheckCubeTextureRequirements) 
// D3DXCheckCubeTextureRequirements;
 
      __HANDLE_DLL_ENTRY(D3DXCheckTextureRequirements) 
 //D3DXCheckTextureRequirements;

      __HANDLE_DLL_ENTRY(D3DXCheckVolumeTextureRequirements) 
 //D3DXCheckVolumeTextureRequirements;
 
      __HANDLE_DLL_ENTRY(D3DXComputeNormalMap) 
 //D3DXComputeNormalMap;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTexture) 
 //D3DXCreateCubeTexture;

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileA) 
 //D3DXCreateCubeTextureFromFileA;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileW) 
 //D3DXCreateCubeTextureFromFileW;

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileExA) 
 //D3DXCreateCubeTextureFromFileExA;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileExW) 
 //D3DXCreateCubeTextureFromFileExW;

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileInMemory) 
 //D3DXCreateCubeTextureFromFileInMemory;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileInMemoryEx) 
 //D3DXCreateCubeTextureFromFileInMemoryEx;

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceA) 
 //D3DXCreateCubeTextureFromResourceA;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceW) 
 //D3DXCreateCubeTextureFromResourceW;

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceExA) 
 //D3DXCreateCubeTextureFromResourceExA;
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceExW) 
 //D3DXCreateCubeTextureFromResourceExW;

      __HANDLE_DLL_ENTRY(D3DXCreateTexture) 
 //D3DXCreateTexture;

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileA) 
 //D3DXCreateTextureFromFileA;
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileW) 
 //D3DXCreateTextureFromFileW;

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileExA) 
 //D3DXCreateTextureFromFileExA;
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileExW) 
 //D3DXCreateTextureFromFileExW;

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileInMemory) 
 //D3DXCreateTextureFromFileInMemory;
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileInMemoryEx) 
 //D3DXCreateTextureFromFileInMemoryEx;

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceA) 
 //D3DXCreateTextureFromResourceA;
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceW) 
 //D3DXCreateTextureFromResourceW;

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceExA) 
// D3DXCreateTextureFromResourceExA;
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceExW) 
 //D3DXCreateTextureFromResourceExW;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTexture) 
 //D3DXCreateVolumeTexture;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileA) 
 //D3DXCreateVolumeTextureFromFileA;
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileW) 
 //D3DXCreateVolumeTextureFromFileW ;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileExA) 
 //D3DXCreateVolumeTextureFromFileExA;
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileExW) 
 //D3DXCreateVolumeTextureFromFileExW;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileInMemory) 
 //D3DXCreateVolumeTextureFromFileInMemory;
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileInMemoryEx) 
 //D3DXCreateVolumeTextureFromFileInMemoryEx ;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceA) 
// D3DXCreateVolumeTextureFromResourceA;
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceW) 
 //D3DXCreateVolumeTextureFromResourceW;

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceExA) 
// D3DXCreateVolumeTextureFromResourceExA;
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceExW) 
 //D3DXCreateVolumeTextureFromResourceExW;

      __HANDLE_DLL_ENTRY(D3DXFillCubeTexture) 
 //D3DXFillCubeTexture;
 
      __HANDLE_DLL_ENTRY(D3DXFillCubeTextureTX) 
 //D3DXFillCubeTextureTX;
 
      __HANDLE_DLL_ENTRY(D3DXFillTexture) 
 //D3DXFillTexture;
 
      __HANDLE_DLL_ENTRY(D3DXFillTextureTX) 
 //D3DXFillTextureTX;

      __HANDLE_DLL_ENTRY(D3DXFillVolumeTexture) 
 //D3DXFillVolumeTexture;
      __HANDLE_DLL_ENTRY(D3DXFillVolumeTextureTX) 
// D3DXFillVolumeTextureTX;

      __HANDLE_DLL_ENTRY(D3DXFilterTexture) 
 //D3DXFilterTexture;


      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileA) 
 //D3DXGetImageInfoFromFileA ;
      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileW) 
 //D3DXGetImageInfoFromFileW;

      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileInMemory) 
 //D3DXGetImageInfoFromFileInMemory;

      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromResourceA) 
 //D3DXGetImageInfoFromResourceA;
      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromResourceW) 
 //D3DXGetImageInfoFromResourceW;

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileA) 
 //D3DXLoadSurfaceFromFileA;
      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileW) 
 //D3DXLoadSurfaceFromFileW;

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileInMemory) 
// D3DXLoadSurfaceFromFileInMemory;

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromMemory) 
 //D3DXLoadSurfaceFromMemory;

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromResourceA) 
// D3DXLoadSurfaceFromResourceA ;
      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromResourceW) 
// D3DXLoadSurfaceFromResourceW ;

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromSurface) 
// D3DXLoadSurfaceFromSurface;

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileA) 
// D3DXLoadVolumeFromFileA;
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileW) 
// D3DXLoadVolumeFromFileW;

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileInMemory) 
// D3DXLoadVolumeFromFileInMemory ;
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromMemory) 
// D3DXLoadVolumeFromMemory;

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromResourceA) 
// D3DXLoadVolumeFromResourceA;
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromResourceW) 
// D3DXLoadVolumeFromResourceW;

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromVolume) 
// D3DXLoadVolumeFromVolume;

      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileA) 
// D3DXSaveSurfaceToFileA;
      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileW) 
// D3DXSaveSurfaceToFileW;

      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileInMemory) 
// D3DXSaveSurfaceToFileInMemory ;

      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileA) 
// D3DXSaveTextureToFileA;
      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileW) 
// D3DXSaveTextureToFileW;

      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileInMemory) 
// D3DXSaveTextureToFileInMemory ;

      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileA) 
// D3DXSaveVolumeToFileA;
      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileW) 
// D3DXSaveVolumeToFileW;

      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileInMemory) 
// D3DXSaveVolumeToFileInMemory;


 int _end_func = 0;


	

 // ok
 
  return 0;
}




//==============================================================


#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file