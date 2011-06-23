#include "d3d9pch.h"



#if ( defined(WIN32) )     // && defined(GB_D3D9) )

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
#include <gb/macro.h>

#include <stdlib.h>
#include <assert.h>

#pragma warning(disable : 4996)


//!  œÓËÒÍ ÚÓ˜ÂÍ ‚ıÓ‰‡
#define __HANDLE_DLL_ENTRY(funcname)   m_TFunc_##funcname =  \
                                                                ( TFunc_##funcname ) ::GetProcAddress(hm, GB_MAKE_STR(funcname) ); \
                                                                \
                if(!m_TFunc_##funcname) {\
                  handleNotFoundAddr( GB_MAKE_STR(funcname) ); \
                  /* return NERROR;*/ \
                 }


//==============================================================
void gb::graphics::d3d9::d3dx9_dynamic_load::Functions::handleNotFoundAddr(
				const char* sFuncName, void* opt)
{
#ifdef _DEBUG
	std::string temp;
	temp = " Entry point not found in d3dx dll :  \n";
	temp += sFuncName;
	//GB_MBOX(temp.c_str() );


	static FILE* st_file = NULL;
	if(st_file == NULL)
	{
	st_file =  fopen( "__getProcAddrlog.txt", "w");
	}

	fputs(sFuncName, st_file);
	fputs( "\n", st_file);

#endif

	int stop = 0;
}






//==============================================================
int gb::graphics::d3d9::d3dx9_dynamic_load::Functions::GetProcAddr(const HMODULE hm)
{
 
                        void* ptr = NULL;
                        const int NERROR = -1;


   int _begin = 0;

   // #error œ≈–≈ƒ≈À¿“‹ !  Õ≈ ‚ÒÂ ÙÛÌÍˆËË Ë˘ÂÚ  .. “Ó˜ÍË ‚ıÓ‰‡.	
   
  __HANDLE_DLL_ENTRY(D3DXCheckVersion) 						
			

	  //------------------------------------------------------------
	  //           Animation Functions
	  //------------------------------------------------------------



	__HANDLE_DLL_ENTRY(D3DXCreateAnimationController)
	__HANDLE_DLL_ENTRY(D3DXCreateCompressedAnimationSet)
	__HANDLE_DLL_ENTRY(D3DXCreateKeyframedAnimationSet)
	__HANDLE_DLL_ENTRY(D3DXFrameAppendChild)
	__HANDLE_DLL_ENTRY(D3DXFrameCalculateBoundingSphere)
	__HANDLE_DLL_ENTRY(D3DXFrameDestroy)
	__HANDLE_DLL_ENTRY(D3DXFrameFind)
	__HANDLE_DLL_ENTRY(D3DXFrameNumNamedMatrices)
	__HANDLE_DLL_ENTRY(D3DXFrameRegisterNamedMatrices)

	__HANDLE_DLL_ENTRY(D3DXLoadMeshHierarchyFromXA)
	__HANDLE_DLL_ENTRY(D3DXLoadMeshHierarchyFromXW)

	__HANDLE_DLL_ENTRY(D3DXLoadMeshHierarchyFromXInMemory)

	__HANDLE_DLL_ENTRY(D3DXSaveMeshHierarchyToFileA)
	__HANDLE_DLL_ENTRY(D3DXSaveMeshHierarchyToFileW)




						
        //------------------------------------------------------------
        //          General Purpose Functions
        //------------------------------------------------------------
		
	


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
        //              MATH  functions
        //------------------------------------------------------------


   __HANDLE_DLL_ENTRY(D3DXMatrixMultiply)
   __HANDLE_DLL_ENTRY(D3DXMatrixInverse)

 

//	__HANDLE_DLL_ENTRY(D3DXColorAdd);
	__HANDLE_DLL_ENTRY(D3DXColorAdjustContrast);
	__HANDLE_DLL_ENTRY(D3DXColorAdjustSaturation);
//	__HANDLE_DLL_ENTRY(D3DXColorLerp);
//	__HANDLE_DLL_ENTRY(D3DXColorModulate);
//	__HANDLE_DLL_ENTRY(D3DXColorNegative);
//	__HANDLE_DLL_ENTRY(D3DXColorScale);
//	__HANDLE_DLL_ENTRY(D3DXColorSubtract);
	__HANDLE_DLL_ENTRY(D3DXCreateMatrixStack);
	__HANDLE_DLL_ENTRY(D3DXFloat16To32Array);
	__HANDLE_DLL_ENTRY(D3DXFloat32To16Array);
	__HANDLE_DLL_ENTRY(D3DXFresnelTerm);
	__HANDLE_DLL_ENTRY(D3DXMatrixAffineTransformation);
	__HANDLE_DLL_ENTRY(D3DXMatrixAffineTransformation2D);
	__HANDLE_DLL_ENTRY(D3DXMatrixDecompose);
	__HANDLE_DLL_ENTRY(D3DXMatrixDeterminant);
//	__HANDLE_DLL_ENTRY(D3DXMatrixIdentity);
	__HANDLE_DLL_ENTRY(D3DXMatrixInverse);
//	__HANDLE_DLL_ENTRY(D3DXMatrixIsIdentity);
	__HANDLE_DLL_ENTRY(D3DXMatrixLookAtLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixLookAtRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixMultiply);
	__HANDLE_DLL_ENTRY(D3DXMatrixMultiplyTranspose);
	__HANDLE_DLL_ENTRY(D3DXMatrixOrthoLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixOrthoOffCenterLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixOrthoOffCenterRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixOrthoRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveFovLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveFovRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveOffCenterLH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveOffCenterRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixPerspectiveRH);
	__HANDLE_DLL_ENTRY(D3DXMatrixReflect);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationAxis);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationQuaternion);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationX);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationY);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationYawPitchRoll);
	__HANDLE_DLL_ENTRY(D3DXMatrixRotationZ);
	__HANDLE_DLL_ENTRY(D3DXMatrixScaling);
	__HANDLE_DLL_ENTRY(D3DXMatrixShadow);
	__HANDLE_DLL_ENTRY(D3DXMatrixTransformation);
	__HANDLE_DLL_ENTRY(D3DXMatrixTransformation2D);
	__HANDLE_DLL_ENTRY(D3DXMatrixTranslation);
	__HANDLE_DLL_ENTRY(D3DXMatrixTranspose);
//	__HANDLE_DLL_ENTRY(D3DXPlaneDot);
//	__HANDLE_DLL_ENTRY(D3DXPlaneDotCoord);
//	__HANDLE_DLL_ENTRY(D3DXPlaneDotNormal);
	__HANDLE_DLL_ENTRY(D3DXPlaneFromPointNormal);
	__HANDLE_DLL_ENTRY(D3DXPlaneFromPoints);
	__HANDLE_DLL_ENTRY(D3DXPlaneIntersectLine);
	__HANDLE_DLL_ENTRY(D3DXPlaneNormalize);
//	__HANDLE_DLL_ENTRY(D3DXPlaneScale);
	__HANDLE_DLL_ENTRY(D3DXPlaneTransform);
	__HANDLE_DLL_ENTRY(D3DXPlaneTransformArray);
	__HANDLE_DLL_ENTRY(D3DXQuaternionBaryCentric);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionConjugate);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionDot);
	__HANDLE_DLL_ENTRY(D3DXQuaternionExp);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionIdentity);
	__HANDLE_DLL_ENTRY(D3DXQuaternionInverse);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionIsIdentity);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionLength);
//	__HANDLE_DLL_ENTRY(D3DXQuaternionLengthSq);
	__HANDLE_DLL_ENTRY(D3DXQuaternionLn);
	__HANDLE_DLL_ENTRY(D3DXQuaternionMultiply);
	__HANDLE_DLL_ENTRY(D3DXQuaternionNormalize);
	__HANDLE_DLL_ENTRY(D3DXQuaternionRotationAxis);
	__HANDLE_DLL_ENTRY(D3DXQuaternionRotationMatrix);
	__HANDLE_DLL_ENTRY(D3DXQuaternionRotationYawPitchRoll);
	__HANDLE_DLL_ENTRY(D3DXQuaternionSlerp);
	__HANDLE_DLL_ENTRY(D3DXQuaternionSquad);
	__HANDLE_DLL_ENTRY(D3DXQuaternionSquadSetup);
	__HANDLE_DLL_ENTRY(D3DXQuaternionToAxisAngle);
	__HANDLE_DLL_ENTRY(D3DXSHAdd);
	__HANDLE_DLL_ENTRY(D3DXSHDot);
	__HANDLE_DLL_ENTRY(D3DXSHEvalConeLight);
	__HANDLE_DLL_ENTRY(D3DXSHEvalDirection);
	__HANDLE_DLL_ENTRY(D3DXSHEvalDirectionalLight);
	__HANDLE_DLL_ENTRY(D3DXSHEvalHemisphereLight);
	__HANDLE_DLL_ENTRY(D3DXSHEvalSphericalLight);
	__HANDLE_DLL_ENTRY(D3DXSHMultiply2);
	__HANDLE_DLL_ENTRY(D3DXSHProjectCubeMap);
	__HANDLE_DLL_ENTRY(D3DXSHRotate);
	__HANDLE_DLL_ENTRY(D3DXSHRotateZ);
	__HANDLE_DLL_ENTRY(D3DXSHScale);
//	__HANDLE_DLL_ENTRY(D3DXVec2Add);
	__HANDLE_DLL_ENTRY(D3DXVec2BaryCentric);
	__HANDLE_DLL_ENTRY(D3DXVec2CatmullRom);
//	__HANDLE_DLL_ENTRY(D3DXVec2CCW);
//	__HANDLE_DLL_ENTRY(D3DXVec2Dot);
	__HANDLE_DLL_ENTRY(D3DXVec2Hermite);
//	__HANDLE_DLL_ENTRY(D3DXVec2Length);
//	__HANDLE_DLL_ENTRY(D3DXVec2LengthSq);
//	__HANDLE_DLL_ENTRY(D3DXVec2Lerp);
//	__HANDLE_DLL_ENTRY(D3DXVec2Maximize);
//	__HANDLE_DLL_ENTRY(D3DXVec2Minimize);
	__HANDLE_DLL_ENTRY(D3DXVec2Normalize);
//	__HANDLE_DLL_ENTRY(D3DXVec2Scale);
//	__HANDLE_DLL_ENTRY(D3DXVec2Subtract);
	__HANDLE_DLL_ENTRY(D3DXVec2Transform);
	__HANDLE_DLL_ENTRY(D3DXVec2TransformArray);
	__HANDLE_DLL_ENTRY(D3DXVec2TransformCoord);
	__HANDLE_DLL_ENTRY(D3DXVec2TransformCoordArray);
	__HANDLE_DLL_ENTRY(D3DXVec2TransformNormal);
	__HANDLE_DLL_ENTRY(D3DXVec2TransformNormalArray);
//	__HANDLE_DLL_ENTRY(D3DXVec3Add);
	__HANDLE_DLL_ENTRY(D3DXVec3BaryCentric);
	__HANDLE_DLL_ENTRY(D3DXVec3CatmullRom);
//	__HANDLE_DLL_ENTRY(D3DXVec3Cross);
//	__HANDLE_DLL_ENTRY(D3DXVec3Dot);
	__HANDLE_DLL_ENTRY(D3DXVec3Hermite);
//	__HANDLE_DLL_ENTRY(D3DXVec3Length);
//	__HANDLE_DLL_ENTRY(D3DXVec3LengthSq);
//	__HANDLE_DLL_ENTRY(D3DXVec3Lerp);
//	__HANDLE_DLL_ENTRY(D3DXVec3Maximize);
//	__HANDLE_DLL_ENTRY(D3DXVec3Minimize);
	__HANDLE_DLL_ENTRY(D3DXVec3Normalize);
	__HANDLE_DLL_ENTRY(D3DXVec3Project);
	__HANDLE_DLL_ENTRY(D3DXVec3ProjectArray);
//	__HANDLE_DLL_ENTRY(D3DXVec3Scale);
//	__HANDLE_DLL_ENTRY(D3DXVec3Subtract);
	__HANDLE_DLL_ENTRY(D3DXVec3Transform);
	__HANDLE_DLL_ENTRY(D3DXVec3TransformArray);
	__HANDLE_DLL_ENTRY(D3DXVec3TransformCoord);
	__HANDLE_DLL_ENTRY(D3DXVec3TransformCoordArray);
	__HANDLE_DLL_ENTRY(D3DXVec3TransformNormal);
	__HANDLE_DLL_ENTRY(D3DXVec3TransformNormalArray);
	__HANDLE_DLL_ENTRY(D3DXVec3Unproject);
	__HANDLE_DLL_ENTRY(D3DXVec3UnprojectArray);
//	__HANDLE_DLL_ENTRY(D3DXVec4Add);
	__HANDLE_DLL_ENTRY(D3DXVec4BaryCentric);
	__HANDLE_DLL_ENTRY(D3DXVec4CatmullRom);
	__HANDLE_DLL_ENTRY(D3DXVec4Cross);
//	__HANDLE_DLL_ENTRY(D3DXVec4Dot);
	__HANDLE_DLL_ENTRY(D3DXVec4Hermite);
//	__HANDLE_DLL_ENTRY(D3DXVec4Length);
//	__HANDLE_DLL_ENTRY(D3DXVec4LengthSq);
//	__HANDLE_DLL_ENTRY(D3DXVec4Lerp);
//	__HANDLE_DLL_ENTRY(D3DXVec4Maximize);
//	__HANDLE_DLL_ENTRY(D3DXVec4Minimize);
	__HANDLE_DLL_ENTRY(D3DXVec4Normalize);
//	__HANDLE_DLL_ENTRY(D3DXVec4Scale);
//	__HANDLE_DLL_ENTRY(D3DXVec4Subtract);
	__HANDLE_DLL_ENTRY(D3DXVec4Transform);
	__HANDLE_DLL_ENTRY(D3DXVec4TransformArray);





 


        //------------------------------------------------------------
        //           MESH functions
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

        #pragma message(  "ks777: d3dx loader:: œ–Œ¬≈–»“‹ D3DXLoadSkinMeshFromXof  "  __FILE__ )

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
        //       Precomputed Radiance Transfer Functions
        //------------------------------------------------------------

 __HANDLE_DLL_ENTRY(D3DXCreatePRTBuffer)
 __HANDLE_DLL_ENTRY(D3DXCreatePRTBufferTex) 
 __HANDLE_DLL_ENTRY(D3DXCreatePRTCompBuffer) 
 __HANDLE_DLL_ENTRY(D3DXCreatePRTEngine)
 __HANDLE_DLL_ENTRY(D3DXCreateTextureGutterHelper)

 __HANDLE_DLL_ENTRY(D3DXLoadPRTBufferFromFileA)
 __HANDLE_DLL_ENTRY(D3DXLoadPRTBufferFromFileW)

 __HANDLE_DLL_ENTRY(D3DXLoadPRTCompBufferFromFileA)
 __HANDLE_DLL_ENTRY(D3DXLoadPRTCompBufferFromFileW)

 __HANDLE_DLL_ENTRY(D3DXSavePRTBufferToFileA) 
 __HANDLE_DLL_ENTRY(D3DXSavePRTBufferToFileW) 

 __HANDLE_DLL_ENTRY(D3DXSavePRTCompBufferToFileA)
 __HANDLE_DLL_ENTRY(D3DXSavePRTCompBufferToFileW)

 __HANDLE_DLL_ENTRY(D3DXSHPRTCompSplitMeshSC) 
 __HANDLE_DLL_ENTRY(D3DXSHPRTCompSuperCluster)



        //------------------------------------------------------------
        //          Shader functions
        //------------------------------------------------------------

        __HANDLE_DLL_ENTRY(D3DXAssembleShader)

        __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromFileA)
        __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromFileW) 

        __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromResourceA)
        __HANDLE_DLL_ENTRY(D3DXAssembleShaderFromResourceW)     
        __HANDLE_DLL_ENTRY(D3DXCompileShader)
        __HANDLE_DLL_ENTRY(D3DXCompileShaderFromFileA)
        __HANDLE_DLL_ENTRY(D3DXCompileShaderFromFileW)  
        __HANDLE_DLL_ENTRY(D3DXCompileShaderFromResourceA)      
        __HANDLE_DLL_ENTRY(D3DXCompileShaderFromResourceW)
        __HANDLE_DLL_ENTRY(D3DXCreateTextureShader)
        __HANDLE_DLL_ENTRY(D3DXDisassembleShader)       
        __HANDLE_DLL_ENTRY(D3DXFindShaderComment)       
        __HANDLE_DLL_ENTRY(D3DXGetPixelShaderProfile)
        __HANDLE_DLL_ENTRY(D3DXGetShaderConstantTable)
        __HANDLE_DLL_ENTRY(D3DXGetShaderConstantTableEx)        
        __HANDLE_DLL_ENTRY(D3DXGetShaderInputSemantics) 
        __HANDLE_DLL_ENTRY(D3DXGetShaderOutputSemantics)        
        __HANDLE_DLL_ENTRY(D3DXGetShaderSamplers)       
        __HANDLE_DLL_ENTRY(D3DXGetShaderSize)   
        __HANDLE_DLL_ENTRY(D3DXGetShaderVersion)        
        __HANDLE_DLL_ENTRY(D3DXGetVertexShaderProfile)  
        __HANDLE_DLL_ENTRY(D3DXPreprocessShader)        
        __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromFileA)
        __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromFileW)       
        __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromResourceA)
        __HANDLE_DLL_ENTRY(D3DXPreprocessShaderFromResourceW)   



        
        //------------------------------------------------------------
        //         Effect functions
        //------------------------------------------------------------
        
    __HANDLE_DLL_ENTRY(D3DXCreateEffect)        
    __HANDLE_DLL_ENTRY(D3DXCreateEffectEx)              
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompiler)        
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromFileA)       
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromFileW)       
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromResourceA)   
    __HANDLE_DLL_ENTRY(D3DXCreateEffectCompilerFromResourceW)   
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileA)       
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileW)       
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileExA)     
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromFileExW)     
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceA)           
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceW)   
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceExA) 
    __HANDLE_DLL_ENTRY(D3DXCreateEffectFromResourceExW)         
    __HANDLE_DLL_ENTRY(D3DXCreateEffectPool)            
    __HANDLE_DLL_ENTRY(D3DXDisassembleEffect)   


        //------------------------------------------------------------
        //                 shared   drawing functions
        //------------------------------------------------------------

    __HANDLE_DLL_ENTRY(D3DXCreateBox)   
    __HANDLE_DLL_ENTRY(D3DXCreateCylinder)      
    __HANDLE_DLL_ENTRY(D3DXCreatePolygon)        
    __HANDLE_DLL_ENTRY(D3DXCreateSphere)        
    __HANDLE_DLL_ENTRY(D3DXCreateTeapot)        
    __HANDLE_DLL_ENTRY(D3DXCreateTextA) 
    __HANDLE_DLL_ENTRY(D3DXCreateTextW) 
    __HANDLE_DLL_ENTRY(D3DXCreateBox)   
    __HANDLE_DLL_ENTRY(D3DXCreateTorus) 

        
        //-------------------------------------------------------
        //        texturing functions
        //-------------------------------------------------------

      __HANDLE_DLL_ENTRY(D3DXCheckCubeTextureRequirements) 
      __HANDLE_DLL_ENTRY(D3DXCheckTextureRequirements) 
      __HANDLE_DLL_ENTRY(D3DXCheckVolumeTextureRequirements) 
      __HANDLE_DLL_ENTRY(D3DXComputeNormalMap) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTexture) 


      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileExW) 

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileInMemory) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromFileInMemoryEx) 

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceW) 

      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateCubeTextureFromResourceExW) 

      __HANDLE_DLL_ENTRY(D3DXCreateTexture) 

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileExW) 

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileInMemory) 
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromFileInMemoryEx) 

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceW) 

      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateTextureFromResourceExW) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTexture) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileExW) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileInMemory) 
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromFileInMemoryEx) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceW) 

      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceExA) 
      __HANDLE_DLL_ENTRY(D3DXCreateVolumeTextureFromResourceExW) 

      __HANDLE_DLL_ENTRY(D3DXFillCubeTexture) 
      __HANDLE_DLL_ENTRY(D3DXFillCubeTextureTX) 
      __HANDLE_DLL_ENTRY(D3DXFillTexture) 
      __HANDLE_DLL_ENTRY(D3DXFillTextureTX) 
      __HANDLE_DLL_ENTRY(D3DXFillVolumeTexture) 
      __HANDLE_DLL_ENTRY(D3DXFillVolumeTextureTX) 
      __HANDLE_DLL_ENTRY(D3DXFilterTexture) 

      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromFileInMemory) 

      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXGetImageInfoFromResourceW) 


      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromFileInMemory) 

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromMemory) 

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromResourceW) 

      __HANDLE_DLL_ENTRY(D3DXLoadSurfaceFromSurface) 

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileA) 
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileW) 

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromFileInMemory) 
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromMemory) 

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromResourceA) 
      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromResourceW) 
 

      __HANDLE_DLL_ENTRY(D3DXLoadVolumeFromVolume) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileA) 
 
      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileW) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveSurfaceToFileInMemory) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileA) 
 
      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileW) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveTextureToFileInMemory) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileA) 
 
      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileW) 
 

      __HANDLE_DLL_ENTRY(D3DXSaveVolumeToFileInMemory) 
 

	 //-----------------------------------------------------
	 //	   UVAtlas Functions
	 //-----------------------------------------------------

__HANDLE_DLL_ENTRY(D3DXUVAtlasCreate)
__HANDLE_DLL_ENTRY(D3DXUVAtlasPack)
__HANDLE_DLL_ENTRY(D3DXUVAtlasPartition)
__HANDLE_DLL_ENTRY(D3DXComputeIMTFromPerVertexSignal)
__HANDLE_DLL_ENTRY(D3DXComputeIMTFromPerTexelSignal)
__HANDLE_DLL_ENTRY(D3DXComputeIMTFromSignal)
__HANDLE_DLL_ENTRY(D3DXComputeIMTFromTexture)
 
 

 int _end_func = 0;


        

 // ok
 
  return 0;
}




//==============================================================


#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file
