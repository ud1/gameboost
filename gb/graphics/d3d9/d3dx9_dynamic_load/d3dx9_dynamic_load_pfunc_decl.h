/** \file
 \brief Декларации типов точек входа в загруженную D3DX9  DLL


 \author ksacvet777

*/

#if ( defined(WIN32) )       // && defined(GB_D3D9)  )


#pragma once
#define __GB__D3DX9_DYNAMIC_LOAD_PFUNC_DECL_H__

#ifndef __GB_D3DX9_DYNAMIC_LOAD_H__
   #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ.   ВКЛЮЧАЙТЕ:  #include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
#endif



//#include <windows.h>
#ifndef _WINDOWS_
   #error  WINDOWS.H  НЕ БЫЛ ВКЛЮЧЁН РАНЕЕ
#endif

#include <string>
#include <gb/macro.h>


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
		//                 Animation Functions 
		//=================================================================
		// 

 
 
		typedef HRESULT (__stdcall *TFunc_D3DXCreateAnimationController)(
			UINT MaxNumAnimationOutputs,
			UINT MaxNumAnimationSets,
			UINT MaxNumTracks,
			UINT MaxNumEvents,
			LPD3DXANIMATIONCONTROLLER* ppAnimController
			);


		typedef HRESULT (__stdcall *TFunc_D3DXCreateCompressedAnimationSet)(
			LPCSTR pName,
			DOUBLE TicksPerSecond,
			D3DXPLAYBACK_TYPE Playback,
			LPD3DXBUFFER pCompressedData,
			UINT NumCallbackKeys,
			CONST LPD3DXKEY_CALLBACK * pCallKeys,
			LPD3DXCOMPRESSEDANIMATIONSET * ppAnimationSet
			);


		typedef HRESULT (__stdcall *TFunc_D3DXCreateKeyframedAnimationSet)(
			LPCSTR pName,
			DOUBLE TicksPerSecond,
			D3DXPLAYBACK_TYPE Playback,
			UINT NumAnimations,
			UINT NumCallbackKeys,
			CONST LPD3DXKEY_CALLBACK * pCallKeys,
			LPD3DXKEYFRAMEDANIMATIONSET * ppAnimationSet
			);


		typedef HRESULT (__stdcall *TFunc_D3DXFrameAppendChild)(
			LPD3DXFRAME pFrameParent,
			CONST D3DXFRAME * pFrameChild
			);

		typedef HRESULT (__stdcall *TFunc_D3DXFrameCalculateBoundingSphere)(
			CONST D3DXFRAME * pFrameRoot,
			LPD3DXVECTOR3 pObjectCenter,
			FLOAT * pObjectRadius
			);

		typedef HRESULT (__stdcall *TFunc_D3DXFrameDestroy)(
			LPD3DXFRAME pFrameRoot,
			LPD3DXALLOCATEHIERARCHY pAlloc
			);

		typedef LPD3DXFRAME (__stdcall *TFunc_D3DXFrameFind)(
			CONST D3DXFRAME * pFrameRoot,
			LPCSTR Name
			);

		typedef UINT (__stdcall *TFunc_D3DXFrameNumNamedMatrices)(
			CONST D3DXFRAME * pFrameRoot
			);


		typedef HRESULT (__stdcall *TFunc_D3DXFrameRegisterNamedMatrices)(
			LPD3DXFRAME pFrameRoot,
			LPD3DXANIMATIONCONTROLLER pAnimController
			);



		typedef HRESULT (__stdcall *TFunc_D3DXLoadMeshHierarchyFromXA)(
			const CHAR* Filename,
			DWORD MeshOptions,
			LPDIRECT3DDEVICE9 pDevice,
			LPD3DXALLOCATEHIERARCHY pAlloc,
			LPD3DXLOADUSERDATA pUserDataLoader,
			LPD3DXFRAME* ppFrameHierarchy,
			LPD3DXANIMATIONCONTROLLER* ppAnimController
			);

		typedef HRESULT (__stdcall *TFunc_D3DXLoadMeshHierarchyFromXW)(
			const WCHAR* Filename,
			DWORD MeshOptions,
			LPDIRECT3DDEVICE9 pDevice,
			LPD3DXALLOCATEHIERARCHY pAlloc,
			LPD3DXLOADUSERDATA pUserDataLoader,
			LPD3DXFRAME* ppFrameHierarchy,
			LPD3DXANIMATIONCONTROLLER* ppAnimController
			);





		typedef HRESULT (__stdcall *TFunc_D3DXLoadMeshHierarchyFromXInMemory)(
			LPCVOID pMemory,
			DWORD SizeOfMemory,
			DWORD MeshOptions,
			LPDIRECT3DDEVICE9 pDevice,
			LPD3DXALLOCATEHIERARCHY pAlloc,
			LPD3DXLOADUSERDATA pUserDataLoader,
			LPD3DXFRAME * ppFrameHeirarchy,
			LPD3DXANIMATIONCONTROLLER * ppAnimController
			);


		typedef HRESULT (__stdcall *TFunc_D3DXSaveMeshHierarchyToFileA)(
			const CHAR* pFilename,
			DWORD XFormat,
			CONST D3DXFRAME * pFrameRoot,
			LPD3DXANIMATIONCONTROLLER pAnimController,
			LPD3DXSAVEUSERDATA pUserDataSaver
			);

		typedef HRESULT (__stdcall *TFunc_D3DXSaveMeshHierarchyToFileW)(
			const WCHAR* pFilename,
			DWORD XFormat,
			CONST D3DXFRAME * pFrameRoot,
			LPD3DXANIMATIONCONTROLLER pAnimController,
			LPD3DXSAVEUSERDATA pUserDataSaver
			);

	 

 

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



	   ////////////////////////////////////////////

 

	/*	
typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorAdd)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC1,
           const D3DXCOLOR *pC2
);   */

 typedef D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorAdjustContrast)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC,
           FLOAT c
);

typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorAdjustSaturation)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC,
           FLOAT s
);
	  /*
typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorLerp)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC1,
           const D3DXCOLOR *pC2,
           FLOAT s
);   */

/*
typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorModulate)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC1,
           const D3DXCOLOR *pC2
);


typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorNegative)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC
);
*/



/*
typedef  D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorScale)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC,
           FLOAT s
);   

typedef   D3DXCOLOR * ( __stdcall  *TFunc_D3DXColorSubtract)(
           D3DXCOLOR *pOut,
           const D3DXCOLOR *pC1,
           const D3DXCOLOR *pC2
);   */

typedef  HRESULT  ( __stdcall  *TFunc_D3DXCreateMatrixStack)(
         DWORD Flags,
         LPD3DXMATRIXSTACK *ppStack
);

typedef  FLOAT * ( __stdcall  *TFunc_D3DXFloat16To32Array)(
           FLOAT *pOut,
           const D3DXFLOAT16 *pIn,
           UINT n
);

typedef  D3DXFLOAT16 * ( __stdcall  *TFunc_D3DXFloat32To16Array)(
           D3DXFLOAT16 *pOut,
           const FLOAT *pIn,
           UINT n
);

typedef  FLOAT  ( __stdcall  *TFunc_D3DXFresnelTerm)(
        FLOAT CosTheta,
        FLOAT RefractionIndex
);

typedef   D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixAffineTransformation)(
           D3DXMATRIX *pOut,
           FLOAT Scaling,
           const D3DXVECTOR3 *pRotationCenter,
           const D3DXQUATERNION *pRotation,
           const D3DXVECTOR3 *pTranslation
);

typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixAffineTransformation2D)(
           D3DXMATRIX *pOut,
           FLOAT Scaling,
           const D3DXVECTOR2 *pRotationCenter,
           FLOAT Rotation,
           const D3DXVECTOR2 *pTranslation
);

 typedef  HRESULT  ( __stdcall  *TFunc_D3DXMatrixDecompose)(
           D3DXVECTOR3 *pOutScale,
           D3DXQUATERNION *pOutRotation,
           D3DXVECTOR3 *pOutTranslation,
           const D3DXMATRIX *pM
);

typedef  FLOAT  ( __stdcall  *TFunc_D3DXMatrixDeterminant)(
        const D3DXMATRIX *pM
);

/*
 typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixIdentity)(
           D3DXMATRIX *pOut
);
*/

 
 

 /*
typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixInverse)(
           D3DXMATRIX *pOut,
           FLOAT *pDeterminant,
           const D3DXMATRIX *pM
);
*/



/*
typedef  BOOL  ( __stdcall  *TFunc_D3DXMatrixIsIdentity)(
        const D3DXMATRIX *pM
);
*/

typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixLookAtLH)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR3 *pEye,
           const D3DXVECTOR3 *pAt,
           const D3DXVECTOR3 *pUp
);


typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixLookAtRH)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR3 *pEye,
           const D3DXVECTOR3 *pAt,
           const D3DXVECTOR3 *pUp
);

/**************
typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixMultiply)(
           D3DXMATRIX *pOut,
           const D3DXMATRIX *pM1,
           const D3DXMATRIX *pM2
);   ******************/

typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixMultiplyTranspose)(
           D3DXMATRIX *pOut,
           const D3DXMATRIX *pM1,
           const D3DXMATRIX *pM2
);

typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixOrthoLH)(
           D3DXMATRIX *pOut,
           FLOAT w,
           FLOAT h,
           FLOAT zn,
           FLOAT zf
);

typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixOrthoOffCenterLH)(
           D3DXMATRIX *pOut,
           FLOAT l,
           FLOAT r,
           FLOAT b,
           FLOAT t,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixOrthoOffCenterRH)(
           D3DXMATRIX *pOut,
           FLOAT l,
           FLOAT r,
           FLOAT b,
           FLOAT t,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixOrthoRH)(
           D3DXMATRIX *pOut,
           FLOAT w,
           FLOAT h,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveFovLH)(
           D3DXMATRIX *pOut,
           FLOAT fovy,
           FLOAT Aspect,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveFovRH)(
           D3DXMATRIX *pOut,
           FLOAT fovy,
           FLOAT Aspect,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveLH)(
           D3DXMATRIX *pOut,
           FLOAT w,
           FLOAT h,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveOffCenterLH)(
           D3DXMATRIX *pOut,
           FLOAT l,
           FLOAT r,
           FLOAT b,
           FLOAT t,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveOffCenterRH)(
           D3DXMATRIX *pOut,
           FLOAT l,
           FLOAT r,
           FLOAT b,
           FLOAT t,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixPerspectiveRH)(
           D3DXMATRIX *pOut,
           FLOAT w,
           FLOAT h,
           FLOAT zn,
           FLOAT zf
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixReflect)(
           D3DXMATRIX *pOut,
           const D3DXPLANE *pPlane
);

typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationAxis)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR3 *pV,
           FLOAT Angle
);


typedef  D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationQuaternion)(
           D3DXMATRIX *pOut,
           const D3DXQUATERNION *pQ
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationX)(
           D3DXMATRIX *pOut,
           FLOAT Angle
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationY)(
           D3DXMATRIX *pOut,
           FLOAT Angle
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationYawPitchRoll)(
           D3DXMATRIX *pOut,
           FLOAT Yaw,
           FLOAT Pitch,
           FLOAT Roll
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixRotationZ)(
           D3DXMATRIX *pOut,
           FLOAT Angle
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixScaling)(
           D3DXMATRIX *pOut,
           FLOAT sx,
           FLOAT sy,
           FLOAT sz
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixShadow)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR4 *pLight,
           const D3DXPLANE *pPlane
);


 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixTransformation)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR3 *pScalingCenter,
           const D3DXQUATERNION *pScalingRotation,
           const D3DXVECTOR3 *pScaling,
           const D3DXVECTOR3 *pRotationCenter,
           const D3DXQUATERNION *pRotation,
           const D3DXVECTOR3 *pTranslation
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixTransformation2D)(
           D3DXMATRIX *pOut,
           const D3DXVECTOR2 *pScalingCenter,
           FLOAT pScalingRotation,
           const D3DXVECTOR2 *pScaling,
           const D3DXVECTOR2 *pRotationCenter,
           FLOAT Rotation,
           const D3DXVECTOR2 *pTranslation
);

 typedef D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixTranslation)(
           D3DXMATRIX *pOut,
           FLOAT x,
           FLOAT y,
           FLOAT z
);

typedef   D3DXMATRIX * ( __stdcall  *TFunc_D3DXMatrixTranspose)(
           D3DXMATRIX *pOut,
           const D3DXMATRIX *pM
);

//D3DXPlaneDot
//D3DXPlaneDotCoord
//D3DXPlaneDotNormal
//D3DXPlaneScale



/*
typedef   FLOAT  ( __stdcall  *TFunc_D3DXPlaneDot)(
        const D3DXPLANE *pP,
        const D3DXVECTOR4 *pV
);

typedef  FLOAT  ( __stdcall  *TFunc_D3DXPlaneDotCoord)(
        const D3DXPLANE *pP,
        const D3DXVECTOR3 *pV
);

typedef  FLOAT  ( __stdcall  *TFunc_D3DXPlaneDotNormal)(
        const D3DXPLANE *pP,
        const D3DXVECTOR3 *pV
);	*/

typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneFromPointNormal)(
           D3DXPLANE *pOut,
           const D3DXVECTOR3 *pPoint,
           const D3DXVECTOR3 *pNormal
);


typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneFromPoints)(
           D3DXPLANE *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2,
           const D3DXVECTOR3 *pV3
);

typedef  D3DXVECTOR3 * ( __stdcall  *TFunc_D3DXPlaneIntersectLine)(
           D3DXVECTOR3 *pOut,
           const D3DXPLANE *pP,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);

typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneNormalize)(
           D3DXPLANE *pOut,
           const D3DXPLANE *pP
);

/*
typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneScale)(
           D3DXPLANE *pOut,
           const D3DXPLANE *pP,
           FLOAT s
);   */

typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneTransform)(
           D3DXPLANE *pOut,
           const D3DXPLANE *pP,
           const D3DXMATRIX *pM
);

typedef  D3DXPLANE * ( __stdcall  *TFunc_D3DXPlaneTransformArray)(
           D3DXPLANE *pOut,
           UINT OutStride,
           const D3DXPLANE *pP,
           UINT PStride,
           const D3DXMATRIX *pM,
           UINT n
);

typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionBaryCentric)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ1,
           const D3DXQUATERNION *pQ2,
           const D3DXQUATERNION *pQ3,
           FLOAT f,
           FLOAT g
);

 
 

/*
typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionConjugate)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ
);   

typedef  FLOAT  ( __stdcall  *TFunc_D3DXQuaternionDot)(
        const D3DXQUATERNION *pQ1,
        const D3DXQUATERNION *pQ2
);	*/

typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionExp)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ
);

/*
typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionIdentity)(
           D3DXQUATERNION *pOut
);*/

typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionInverse)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ
);

/*
typedef BOOL  ( __stdcall  *TFunc_D3DXQuaternionIsIdentity)(
        const D3DXQUATERNION *pQ
); 
 
typedef  FLOAT  ( __stdcall  *TFunc_D3DXQuaternionLength)(
        const D3DXQUATERNION *pQ
);

typedef  FLOAT  ( __stdcall  *TFunc_D3DXQuaternionLengthSq)(
        const D3DXQUATERNION *pQ
);   
*/

typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionLn)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ
);

typedef  D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionMultiply)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ1,
           const D3DXQUATERNION *pQ2
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionNormalize)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionRotationAxis)(
           D3DXQUATERNION *pOut,
           const D3DXVECTOR3 *pV,
           FLOAT Angle
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionRotationMatrix)(
           D3DXQUATERNION *pOut,
           const D3DXMATRIX *pM
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionRotationYawPitchRoll)(
           D3DXQUATERNION *pOut,
           FLOAT Yaw,
           FLOAT Pitch,
           FLOAT Roll
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionSlerp)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ1,
           const D3DXQUATERNION *pQ2,
           FLOAT t
);

 typedef D3DXQUATERNION * ( __stdcall  *TFunc_D3DXQuaternionSquad)(
           D3DXQUATERNION *pOut,
           const D3DXQUATERNION *pQ1,
           const D3DXQUATERNION *pA,
           const D3DXQUATERNION *pB,
           const D3DXQUATERNION *pC,
           FLOAT t
);

typedef void ( __stdcall  *TFunc_D3DXQuaternionSquadSetup)(
         D3DXQUATERNION *pAOut,
         D3DXQUATERNION *pBOut,
         D3DXQUATERNION *pCOut,
         const D3DXQUATERNION *pQ0,
         const D3DXQUATERNION *pQ1,
         const D3DXQUATERNION *pQ2,
         const D3DXQUATERNION *pQ3
);

typedef void ( __stdcall  *TFunc_D3DXQuaternionToAxisAngle)(
           const D3DXQUATERNION *pQ,
           D3DXVECTOR3 *pAxis,
           FLOAT *pAngle
);


 typedef FLOAT * ( __stdcall  *TFunc_D3DXSHAdd)(
         FLOAT *pOut,
         UINT Order,
         const FLOAT *pA,
         const FLOAT *pB
);

 typedef FLOAT  ( __stdcall  *TFunc_D3DXSHDot)(
        UINT Order,
        const FLOAT *pA,
        const FLOAT *pB
);

 typedef HRESULT  ( __stdcall  *TFunc_D3DXSHEvalConeLight)(
         UINT Order,
         const D3DXVECTOR3 *pDir,
         FLOAT Radius,
         FLOAT RIntensity,
         FLOAT GIntensity,
         FLOAT BIntensity,
         FLOAT *pROut,
         FLOAT *pGOut,
         FLOAT *pBOut
);


 typedef FLOAT * ( __stdcall  *TFunc_D3DXSHEvalDirection)(
         FLOAT *pOut,
         UINT Order,
         const D3DXVECTOR3 *pDir
);

 typedef HRESULT  ( __stdcall  *TFunc_D3DXSHEvalDirectionalLight)(
         UINT Order,
         const D3DXVECTOR3 *pDir,
         FLOAT RIntensity,
         FLOAT GIntensity,
         FLOAT BIntensity,
         FLOAT *pROut,
         FLOAT *pGOut,
         FLOAT *pBOut
);


 typedef HRESULT  ( __stdcall  *TFunc_D3DXSHEvalHemisphereLight)(
        UINT Order,
        const D3DXVECTOR3 *pDir,
        D3DXCOLOR Top,
        D3DXCOLOR Bottom,
        FLOAT *pROut,
        FLOAT *pGOut,
        FLOAT *pBOut
);

 typedef HRESULT  ( __stdcall  *TFunc_D3DXSHEvalSphericalLight)(
         UINT Order,
         const D3DXVECTOR3 *pPos,
         FLOAT Radius,
         FLOAT RIntensity,
         FLOAT GIntensity,
         FLOAT BIntensity,
         FLOAT *pROut,
         FLOAT *pGOut,
         FLOAT *pBOut
);

 typedef FLOAT * ( __stdcall  *TFunc_D3DXSHMultiply2)(
        FLOAT *pOut,
        const FLOAT *pF,
        const FLOAT *pG
);


 typedef HRESULT  ( __stdcall  *TFunc_D3DXSHProjectCubeMap)(
        UINT Order,
        LPDIRECT3DCUBETEXTURE9 pCubeMap,
        FLOAT *pROut,
        FLOAT *pGOut,
        FLOAT *pBOut
);

 typedef FLOAT* ( __stdcall  *TFunc_D3DXSHRotate)(
         FLOAT *pOut,
         UINT Order,
         const D3DXMATRIX *pMatrix,
         const FLOAT *pIn
);

 typedef FLOAT* ( __stdcall  *TFunc_D3DXSHRotateZ)(
         FLOAT *pOut,
         UINT Order,
         FLOAT Angle,
         const FLOAT *pIn
);

 typedef FLOAT* ( __stdcall  *TFunc_D3DXSHScale)(
         FLOAT *pOut,
         UINT Order,
         const FLOAT *pIn,
         const FLOAT *Scale
);

 
 
	/*
 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Add)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2
);   */

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2BaryCentric)(
         D3DXVECTOR2 *pOut,
         const D3DXVECTOR2 *pV1,
         const D3DXVECTOR2 *pV2,
         const D3DXVECTOR2 *pV3,
         FLOAT f,
         FLOAT g
);

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2CatmullRom)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV0,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2,
           const D3DXVECTOR2 *pV3,
           FLOAT s
);

	 /*
 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec2CCW)(
        const D3DXVECTOR2 *pV1,
        const D3DXVECTOR2 *pV2
);   */

 /*
 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec2Dot)(
        const D3DXVECTOR2 *pV1,
        const D3DXVECTOR2 *pV2
);	*/


 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Hermite)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pT1,
           const D3DXVECTOR2 *pV2,
           const D3DXVECTOR2 *pT2,
           FLOAT s
);

		/*
 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec2Length)(
        const D3DXVECTOR2 *pV
);

 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec2LengthSq)(
        const D3DXVECTOR2 *pV
);   */

 /*
 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Lerp)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2,
           FLOAT s
);   */



 /****

 typedef D3DXVECTOR2 * ( __stdcall  *TFunc_D3DXVec2Maximize)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2
);

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Minimize)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2
);

*/

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Normalize)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV
);


 /*
 typedef D3DXVECTOR2 * ( __stdcall  *TFunc_D3DXVec2Scale)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV,
           FLOAT s
);


 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2Subtract)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV1,
           const D3DXVECTOR2 *pV2
);   */


 typedef D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec2Transform)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR2 *pV,
           const D3DXMATRIX *pM
);

 typedef D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec2TransformArray)(
           D3DXVECTOR4 *pOut,
           UINT OutStride,
           const D3DXVECTOR2 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n
);

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2TransformCoord)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV,
           const D3DXMATRIX *pM
);


 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2TransformCoordArray)(
           D3DXVECTOR2 *pOut,
           UINT OutStride,
           const D3DXVECTOR2 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n
);

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2TransformNormal)(
           D3DXVECTOR2 *pOut,
           const D3DXVECTOR2 *pV,
           const D3DXMATRIX *pM
);

 typedef D3DXVECTOR2* ( __stdcall  *TFunc_D3DXVec2TransformNormalArray)(
           D3DXVECTOR2 *pOut,
           UINT OutStride,
           const D3DXVECTOR2 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n
);


 //
 //--------
 //

 /*********************************************
 
 

 *********************************************/

 /*
 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Add)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);   */

 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3BaryCentric)(
         D3DXVECTOR3 *pOut,
         const D3DXVECTOR3 *pV1,
         const D3DXVECTOR3 *pV2,
         const D3DXVECTOR3 *pV3,
         FLOAT f,
         FLOAT g
);

 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3CatmullRom)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV0,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2,
           const D3DXVECTOR3 *pV3,
           FLOAT s
);
	  /*
 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Cross)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);

 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec3Dot)(
        const D3DXVECTOR3 *pV1,
        const D3DXVECTOR3 *pV2
);	*/

 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Hermite)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pT1,
           const D3DXVECTOR3 *pV2,
           const D3DXVECTOR3 *pT2,
           FLOAT s
);


 /*
 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec3Length)(
        const D3DXVECTOR3 *pV
);

 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec3LengthSq)(
        const D3DXVECTOR3 *pV
);	
*/


 /*
 typedef D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Lerp)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2,
           FLOAT s
);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Maximize)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Minimize)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);*/

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Normalize)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV
);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Project)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV,
           const D3DVIEWPORT9 *pViewport,
           const D3DXMATRIX *pProjection,
           const D3DXMATRIX *pView,
           const D3DXMATRIX *pWorld
);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3ProjectArray)(
           D3DXVECTOR3 *pOut,
           UINT OutStride,
           const D3DXVECTOR3 *pV,
           UINT VStride,
           const D3DVIEWPORT9 *pViewport,
           const D3DXMATRIX *pProjection,
           const D3DXMATRIX *pView,
           const D3DXMATRIX *pWorld,
           UINT n
);


/*
typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Scale)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV,
           FLOAT s
);


typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Subtract)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV1,
           const D3DXVECTOR3 *pV2
);	*/

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec3Transform)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR3 *pV,
           const D3DXMATRIX *pM
);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec3TransformArray)(
           D3DXVECTOR4 *pOut,
           UINT OutStride,
           const D3DXVECTOR3 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3TransformCoord)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV,
           const D3DXMATRIX *pM);


typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3TransformCoordArray)(
           D3DXVECTOR3 *pOut,
           UINT OutStride,
           const D3DXVECTOR3 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3TransformNormal)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV,
           const D3DXMATRIX *pM);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3TransformNormalArray)(
           D3DXVECTOR3 *pOut,
           UINT OutStride,
           const D3DXVECTOR3 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n);


typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3Unproject)(
           D3DXVECTOR3 *pOut,
           const D3DXVECTOR3 *pV,
           const D3DVIEWPORT9 *pViewport,
           const D3DXMATRIX *pProjection,
           const D3DXMATRIX *pView,
           const D3DXMATRIX *pWorld);

typedef  D3DXVECTOR3* ( __stdcall  *TFunc_D3DXVec3UnprojectArray)(
           D3DXVECTOR3 *pOut,
           UINT OutStride,
           const D3DXVECTOR3 *pV,
           UINT VStride,
           const D3DVIEWPORT9 *pViewport,
           const D3DXMATRIX *pProjection,
           const D3DXMATRIX *pView,
           const D3DXMATRIX *pWorld,
           UINT n);

 


  /*
typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Add)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2);*/

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4BaryCentric)(
         D3DXVECTOR4 *pOut,
         const D3DXVECTOR4 *pV1,
         const D3DXVECTOR4 *pV2,
         const D3DXVECTOR4 *pV3,
         FLOAT f,
         FLOAT g);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4CatmullRom)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV0,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2,
           const D3DXVECTOR4 *pV3,
           FLOAT s);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Cross)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2,
           const D3DXVECTOR4 *pV3);

   /*
typedef  FLOAT  ( __stdcall  *TFunc_D3DXVec4Dot)(
        const D3DXVECTOR4 *pV1,
        const D3DXVECTOR4 *pV2
);*/

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Hermite)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pT1,
           const D3DXVECTOR4 *pV2,
           const D3DXVECTOR4 *pT2,
           FLOAT s);


 /*
typedef  FLOAT  ( __stdcall  *TFunc_D3DXVec4Length)(
        const D3DXVECTOR4 *pV
);

 typedef FLOAT  ( __stdcall  *TFunc_D3DXVec4LengthSq)(
        const D3DXVECTOR4 *pV
);
*/

   /*
typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Lerp)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2,
           FLOAT s
);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Maximize)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2
);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Minimize)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2
);	*/


typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Normalize)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV
);

	 /*
typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Scale)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV,
           FLOAT s
);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Subtract)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV1,
           const D3DXVECTOR4 *pV2
);   */

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4Transform)(
           D3DXVECTOR4 *pOut,
           const D3DXVECTOR4 *pV,
           const D3DXMATRIX *pM
);

typedef  D3DXVECTOR4* ( __stdcall  *TFunc_D3DXVec4TransformArray)(
           D3DXVECTOR4 *pOut,
           UINT OutStride,
           const D3DXVECTOR4 *pV,
           UINT VStride,
           const D3DXMATRIX *pM,
           UINT n
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
		//        Precomputed Radiance Transfer Functions  
		//==============================================================
 

		typedef HRESULT (__stdcall *TFunc_D3DXCreatePRTBuffer)(
			UINT NumSamples,
			UINT NumCoeffs,
			UINT NumChannels,
			LPD3DXPRTBUFFER * ppBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXCreatePRTBufferTex)(
			UINT Width,
			UINT Height,
			UINT NumCoeffs,
			UINT NumChannels,
			LPD3DXPRTBUFFER * ppBuffer);

		typedef HRESULT (__stdcall *TFunc_D3DXCreatePRTCompBuffer)(
			D3DXSHCOMPRESSQUALITYTYPE Quality,
			UINT NumClusters,
			UINT NumPCA,
			LPD3DXSHPRTSIMCB pCB,
			LPVOID lpUserContext,
			LPD3DXPRTBUFFER pBuffer,
			LPD3DXPRTCOMPBUFFER * ppBuffer);

		typedef HRESULT (__stdcall *TFunc_D3DXCreatePRTEngine)(
			LPD3DXMESH pMesh,
			DWORD * pAdjacency,
			BOOL ExtractUVs,
			LPD3DXMESH pBlockerMesh,
			LPD3DXPRTENGINE ppEngine);


		typedef HRESULT (__stdcall *TFunc_D3DXCreateTextureGutterHelper)(
			UINT Width,
			UINT Height,
			LPD3DXMESH pMesh,
			FLOAT GutterSize,
			LPD3DXTEXTUREGUTTERHELPER * ppBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXLoadPRTBufferFromFileA)(
			const CHAR* pFileName,
			LPD3DXPRTBUFFER * ppBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXLoadPRTBufferFromFileW)(
			const WCHAR* pFileName,
			LPD3DXPRTBUFFER * ppBuffer);

		typedef HRESULT (__stdcall *TFunc_D3DXLoadPRTCompBufferFromFileA)(
			const CHAR* pFileName,
			LPD3DXPRTCOMPBUFFER * ppBuffer);

		typedef HRESULT (__stdcall *TFunc_D3DXLoadPRTCompBufferFromFileW)(
			const WCHAR*  pFileName,
			LPD3DXPRTCOMPBUFFER * ppBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXSavePRTBufferToFileA)(
			const CHAR* pFileName,
			LPD3DXPRTBUFFER pBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXSavePRTBufferToFileW)(
			const WCHAR* pFileName,
			LPD3DXPRTBUFFER pBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXSavePRTCompBufferToFileA)(
			const CHAR* pFileName,
			LPD3DXPRTCOMPBUFFER pBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXSavePRTCompBufferToFileW)(
			const WCHAR* pFileName,
			LPD3DXPRTCOMPBUFFER pBuffer);


		typedef HRESULT (__stdcall *TFunc_D3DXSHPRTCompSplitMeshSC)(
			UINT * pClusterIDs,
			UINT NumVertices,
			UINT NumCs,
			UINT * pSClusterIDs,
			UINT NumSCs,
			LPVOID pInputIB,
			BOOL InputIBIs32Bit,
			UINT NumFaces,
			LPD3DXBUFFER * ppIBData,
			UINT * pIBDataLength,
			BOOL OutputIBIs32Bit,
			LPD3DXBUFFER * ppFaceRemap,
			LPD3DXBUFFER * ppVertData,
			UINT * pVertDataLength,
			UINT * pSCClusterList,
			D3DXSHPRTSPLITMESHCLUSTERDATA* pSCData);

		typedef HRESULT (__stdcall *TFunc_D3DXSHPRTCompSuperCluster)(
			UINT * pClusterIDs,
			LPD3DXMESH pScene,
			UINT MaxNumClusters,
			UINT NumClusters,
			UINT * pSClusterIDs,
			UINT * pNumSCs);








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




		//-------------------------------------------------
		//        UVAtlas Functions
		//------------------------------------------------- 

		typedef HRESULT (__stdcall *TFunc_D3DXUVAtlasCreate)(
			LPD3DXMESH pMesh,
			UINT dwMaxChartNumber,
			FLOAT fMaxStretch,
			UINT dwWidth,
			UINT dwHeight,
			FLOAT fGutter,
			DWORD dwTextureIndex,
			CONST DWORD *pdwAdjacency,
			CONST DWORD *pdwFalseEdges,
			FLOAT *pfIMTArray,
			LPD3DXUVATLASCB pCallback,
			FLOAT fCallbackFrequency,
			LPVOID pUserContent,
			DWORD dwOptions,
			LPD3DXMESH *ppMeshOut,
			LPD3DXBUFFER *ppFacePartitioning,
			LPD3DXBUFFER *ppVertexRemapArray,
			FLOAT *pfMaxStretchOut,
			UINT *pdwNumChartsOut);


		typedef HRESULT (__stdcall *TFunc_D3DXUVAtlasPack)(
			LPD3DXMESH pMesh,
			UINT dwWidth,
			UINT dwHeight,
			FLOAT fGutter,
			DWORD dwTextureIndex,
			CONST DWORD * pdwPartitionResultAdjacency,
			LPD3DXUVATLASCB pCallback,
			FLOAT fCallbackFrequency,
			LPVOID pUserContent,
			DWORD dwOptions,
			LPD3DXBUFFER pFacePartitioning);

		typedef HRESULT (__stdcall *TFunc_D3DXUVAtlasPartition)(
			LPD3DXMESH pMesh,
			UINT dwMaxChartNumber,
			FLOAT fMaxStretch,
			DWORD dwTextureIndex,
			CONST DWORD *pdwAdjacency,
			CONST DWORD *pdwFalseEdges,
			FLOAT *pfIMTArray,
			LPD3DXUVATLASCB pCallback,
			FLOAT fCallbackFrequency,
			LPVOID pUserContent,
			DWORD dwOptions,
			LPD3DXMESH *ppMeshOut,
			LPD3DXBUFFER pFacePartitioning,
			LPD3DXBUFFER *ppVertexRemapArray,
			LPD3DXBUFFER *ppPartitionResultAdjacency,
			FLOAT *pfMaxStretchOut,
			UINT *pdwNumChartsOut);

		typedef HRESULT (__stdcall *TFunc_D3DXComputeIMTFromPerTexelSignal)(
			LPD3DXMESH pMesh,
			DWORD dwTextureIndex,
			FLOAT * pfTexelSignal,
			UINT uWidth,
			UINT uHeight,
			UINT uSignalDimension,
			UINT uComponents,
			DWORD dwOptions,
			LPD3DXUVATLASCB pStatusCallback,
			LPVOID pUserContext,
			LPD3DXBUFFER * ppIMTData);

		typedef HRESULT (__stdcall *TFunc_D3DXComputeIMTFromPerVertexSignal)(
			LPD3DXMESH pMesh,
			CONST FLOAT * pfVertexSignal,
			UINT uSignalDimension,
			UINT uSignalStride,
			DWORD dwOptions,
			LPD3DXUVATLASCB pStatusCallback,
			LPVOID pUserContext,
			LPD3DXBUFFER * ppIMTData);

		typedef HRESULT (__stdcall *TFunc_D3DXComputeIMTFromSignal)(
			LPD3DXMESH pMesh,
			DWORD dwTextureIndex,
			UINT uSignalDimension,
			FLOAT fMaxUVDistance,
			DWORD dwOptions,
			LPD3DXIMTSIGNALCALLBACK pSignalCallback,
			VOID * pUserData,
			LPD3DXUVATLASCB pStatusCallback,
			LPVOID pUserContext,
			LPD3DXBUFFER * ppIMTData);


		typedef HRESULT (__stdcall *TFunc_D3DXComputeIMTFromTexture)(
			LPD3DXMESH pMesh,
			LPDIRECT3DTEXTURE9 pTexture,
			DWORD dwTextureIndex,
			DWORD dwOptions,
			LPD3DXUVATLASCB pStatusCallback,
			LPVOID pUserContext,
			LPD3DXBUFFER * ppIMTData);




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



		//   -----------   Animation Functions   -----------------

 

		TFunc_D3DXCreateAnimationController     m_TFunc_D3DXCreateAnimationController  ;
		TFunc_D3DXCreateCompressedAnimationSet  m_TFunc_D3DXCreateCompressedAnimationSet   ;
		TFunc_D3DXCreateKeyframedAnimationSet   m_TFunc_D3DXCreateKeyframedAnimationSet ;
		TFunc_D3DXFrameAppendChild               m_TFunc_D3DXFrameAppendChild ;
		TFunc_D3DXFrameCalculateBoundingSphere   m_TFunc_D3DXFrameCalculateBoundingSphere ;
		TFunc_D3DXFrameDestroy      m_TFunc_D3DXFrameDestroy  ;
		TFunc_D3DXFrameFind         m_TFunc_D3DXFrameFind ;
		TFunc_D3DXFrameNumNamedMatrices           m_TFunc_D3DXFrameNumNamedMatrices ;
		TFunc_D3DXFrameRegisterNamedMatrices      m_TFunc_D3DXFrameRegisterNamedMatrices ;

		TFunc_D3DXLoadMeshHierarchyFromXA    m_TFunc_D3DXLoadMeshHierarchyFromXA ;
		TFunc_D3DXLoadMeshHierarchyFromXW    m_TFunc_D3DXLoadMeshHierarchyFromXW ; 

		TFunc_D3DXLoadMeshHierarchyFromXInMemory  m_TFunc_D3DXLoadMeshHierarchyFromXInMemory  ;

		TFunc_D3DXSaveMeshHierarchyToFileA         m_TFunc_D3DXSaveMeshHierarchyToFileA;
		TFunc_D3DXSaveMeshHierarchyToFileW         m_TFunc_D3DXSaveMeshHierarchyToFileW;

 



		//   -----------   general purpose function   ---------------


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

			   ////////////////////////



			   
		//TFunc_D3DXColorAdd                m_TFunc_D3DXColorAdd;
		TFunc_D3DXColorAdjustContrast     m_TFunc_D3DXColorAdjustContrast;
		TFunc_D3DXColorAdjustSaturation   m_TFunc_D3DXColorAdjustSaturation;
		//TFunc_D3DXColorLerp               m_TFunc_D3DXColorLerp;
		//TFunc_D3DXColorModulate           m_TFunc_D3DXColorModulate;
		//TFunc_D3DXColorNegative           m_TFunc_D3DXColorNegative;
		//TFunc_D3DXColorScale         m_TFunc_D3DXColorScale;
		//TFunc_D3DXColorSubtract      m_TFunc_D3DXColorSubtract;
		TFunc_D3DXCreateMatrixStack  m_TFunc_D3DXCreateMatrixStack;
		TFunc_D3DXFloat16To32Array   m_TFunc_D3DXFloat16To32Array;
		TFunc_D3DXFloat32To16Array   m_TFunc_D3DXFloat32To16Array;
		TFunc_D3DXFresnelTerm        m_TFunc_D3DXFresnelTerm;
		TFunc_D3DXMatrixAffineTransformation     m_TFunc_D3DXMatrixAffineTransformation;
		TFunc_D3DXMatrixAffineTransformation2D   m_TFunc_D3DXMatrixAffineTransformation2D;
		TFunc_D3DXMatrixDecompose   m_TFunc_D3DXMatrixDecompose;
		TFunc_D3DXMatrixDeterminant m_TFunc_D3DXMatrixDeterminant;
		//TFunc_D3DXMatrixIdentity    m_TFunc_D3DXMatrixIdentity;
//		TFunc_D3DXMatrixInverse     m_TFunc_D3DXMatrixInverse;
		//TFunc_D3DXMatrixIsIdentity  m_TFunc_D3DXMatrixIsIdentity;
		TFunc_D3DXMatrixLookAtLH    m_TFunc_D3DXMatrixLookAtLH;
		TFunc_D3DXMatrixLookAtRH    m_TFunc_D3DXMatrixLookAtRH;
//		TFunc_D3DXMatrixMultiply    m_TFunc_D3DXMatrixMultiply;
		TFunc_D3DXMatrixMultiplyTranspose   m_TFunc_D3DXMatrixMultiplyTranspose;
		TFunc_D3DXMatrixOrthoLH             m_TFunc_D3DXMatrixOrthoLH;
		TFunc_D3DXMatrixOrthoOffCenterLH    m_TFunc_D3DXMatrixOrthoOffCenterLH;
		TFunc_D3DXMatrixOrthoOffCenterRH    m_TFunc_D3DXMatrixOrthoOffCenterRH;
		TFunc_D3DXMatrixOrthoRH             m_TFunc_D3DXMatrixOrthoRH;
		TFunc_D3DXMatrixPerspectiveFovLH    m_TFunc_D3DXMatrixPerspectiveFovLH;
		TFunc_D3DXMatrixPerspectiveFovRH    m_TFunc_D3DXMatrixPerspectiveFovRH;
		TFunc_D3DXMatrixPerspectiveLH       m_TFunc_D3DXMatrixPerspectiveLH;
		TFunc_D3DXMatrixPerspectiveOffCenterLH   m_TFunc_D3DXMatrixPerspectiveOffCenterLH;
		TFunc_D3DXMatrixPerspectiveOffCenterRH   m_TFunc_D3DXMatrixPerspectiveOffCenterRH;
		TFunc_D3DXMatrixPerspectiveRH            m_TFunc_D3DXMatrixPerspectiveRH;
		TFunc_D3DXMatrixReflect                  m_TFunc_D3DXMatrixReflect;
		TFunc_D3DXMatrixRotationAxis             m_TFunc_D3DXMatrixRotationAxis;
		TFunc_D3DXMatrixRotationQuaternion       m_TFunc_D3DXMatrixRotationQuaternion;
		TFunc_D3DXMatrixRotationX                m_TFunc_D3DXMatrixRotationX;
		TFunc_D3DXMatrixRotationY                m_TFunc_D3DXMatrixRotationY;
		TFunc_D3DXMatrixRotationYawPitchRoll     m_TFunc_D3DXMatrixRotationYawPitchRoll;
		TFunc_D3DXMatrixRotationZ   m_TFunc_D3DXMatrixRotationZ;
		TFunc_D3DXMatrixScaling     m_TFunc_D3DXMatrixScaling;
		TFunc_D3DXMatrixShadow      m_TFunc_D3DXMatrixShadow;
		TFunc_D3DXMatrixTransformation   m_TFunc_D3DXMatrixTransformation;
		TFunc_D3DXMatrixTransformation2D m_TFunc_D3DXMatrixTransformation2D;
		TFunc_D3DXMatrixTranslation      m_TFunc_D3DXMatrixTranslation;
		TFunc_D3DXMatrixTranspose        m_TFunc_D3DXMatrixTranspose;
		//TFunc_D3DXPlaneDot               m_TFunc_D3DXPlaneDot;
		//TFunc_D3DXPlaneDotCoord          m_TFunc_D3DXPlaneDotCoord;
		//TFunc_D3DXPlaneDotNormal         m_TFunc_D3DXPlaneDotNormal;
		TFunc_D3DXPlaneFromPointNormal   m_TFunc_D3DXPlaneFromPointNormal;
		TFunc_D3DXPlaneFromPoints        m_TFunc_D3DXPlaneFromPoints;
		TFunc_D3DXPlaneIntersectLine     m_TFunc_D3DXPlaneIntersectLine;
		TFunc_D3DXPlaneNormalize         m_TFunc_D3DXPlaneNormalize;
		//TFunc_D3DXPlaneScale             m_TFunc_D3DXPlaneScale;
		TFunc_D3DXPlaneTransform         m_TFunc_D3DXPlaneTransform;
		TFunc_D3DXPlaneTransformArray    m_TFunc_D3DXPlaneTransformArray;
		TFunc_D3DXQuaternionBaryCentric  m_TFunc_D3DXQuaternionBaryCentric;
		//TFunc_D3DXQuaternionConjugate    m_TFunc_D3DXQuaternionConjugate;
		//TFunc_D3DXQuaternionDot          m_TFunc_D3DXQuaternionDot;
		TFunc_D3DXQuaternionExp          m_TFunc_D3DXQuaternionExp;
		//TFunc_D3DXQuaternionIdentity     m_TFunc_D3DXQuaternionIdentity;
		TFunc_D3DXQuaternionInverse      m_TFunc_D3DXQuaternionInverse;
		//TFunc_D3DXQuaternionIsIdentity   m_TFunc_D3DXQuaternionIsIdentity;
		//TFunc_D3DXQuaternionLength       m_TFunc_D3DXQuaternionLength;
		//TFunc_D3DXQuaternionLengthSq     m_TFunc_D3DXQuaternionLengthSq;
		TFunc_D3DXQuaternionLn           m_TFunc_D3DXQuaternionLn;
		TFunc_D3DXQuaternionMultiply     m_TFunc_D3DXQuaternionMultiply;
		TFunc_D3DXQuaternionNormalize        m_TFunc_D3DXQuaternionNormalize;
		TFunc_D3DXQuaternionRotationAxis     m_TFunc_D3DXQuaternionRotationAxis;
		TFunc_D3DXQuaternionRotationMatrix   m_TFunc_D3DXQuaternionRotationMatrix;
		TFunc_D3DXQuaternionRotationYawPitchRoll  m_TFunc_D3DXQuaternionRotationYawPitchRoll;
		TFunc_D3DXQuaternionSlerp       m_TFunc_D3DXQuaternionSlerp;
		TFunc_D3DXQuaternionSquad       m_TFunc_D3DXQuaternionSquad;
		TFunc_D3DXQuaternionSquadSetup  m_TFunc_D3DXQuaternionSquadSetup;
		TFunc_D3DXQuaternionToAxisAngle m_TFunc_D3DXQuaternionToAxisAngle;
		TFunc_D3DXSHAdd    m_TFunc_D3DXSHAdd;
		TFunc_D3DXSHDot    m_TFunc_D3DXSHDot;
		TFunc_D3DXSHEvalConeLight   m_TFunc_D3DXSHEvalConeLight;
		TFunc_D3DXSHEvalDirection   m_TFunc_D3DXSHEvalDirection;
		TFunc_D3DXSHEvalDirectionalLight   m_TFunc_D3DXSHEvalDirectionalLight;
		TFunc_D3DXSHEvalHemisphereLight    m_TFunc_D3DXSHEvalHemisphereLight;
		TFunc_D3DXSHEvalSphericalLight     m_TFunc_D3DXSHEvalSphericalLight;
		TFunc_D3DXSHMultiply2              m_TFunc_D3DXSHMultiply2;
		TFunc_D3DXSHProjectCubeMap    m_TFunc_D3DXSHProjectCubeMap;
		TFunc_D3DXSHRotate            m_TFunc_D3DXSHRotate;
		TFunc_D3DXSHRotateZ           m_TFunc_D3DXSHRotateZ;
		TFunc_D3DXSHScale             m_TFunc_D3DXSHScale;
		//TFunc_D3DXVec2Add             m_TFunc_D3DXVec2Add;
		TFunc_D3DXVec2BaryCentric     m_TFunc_D3DXVec2BaryCentric;
		TFunc_D3DXVec2CatmullRom      m_TFunc_D3DXVec2CatmullRom;
		//TFunc_D3DXVec2CCW             m_TFunc_D3DXVec2CCW;
		//TFunc_D3DXVec2Dot             m_TFunc_D3DXVec2Dot;
		TFunc_D3DXVec2Hermite         m_TFunc_D3DXVec2Hermite;
		//TFunc_D3DXVec2Length          m_TFunc_D3DXVec2Length;
		//TFunc_D3DXVec2LengthSq        m_TFunc_D3DXVec2LengthSq;
		//TFunc_D3DXVec2Lerp            m_TFunc_D3DXVec2Lerp;
		//TFunc_D3DXVec2Maximize        m_TFunc_D3DXVec2Maximize;
		//TFunc_D3DXVec2Minimize        m_TFunc_D3DXVec2Minimize;
		TFunc_D3DXVec2Normalize       m_TFunc_D3DXVec2Normalize;
		//TFunc_D3DXVec2Scale           m_TFunc_D3DXVec2Scale;
		//TFunc_D3DXVec2Subtract             m_TFunc_D3DXVec2Subtract;
		TFunc_D3DXVec2Transform            m_TFunc_D3DXVec2Transform;
		TFunc_D3DXVec2TransformArray       m_TFunc_D3DXVec2TransformArray;
		TFunc_D3DXVec2TransformCoord       m_TFunc_D3DXVec2TransformCoord;
		TFunc_D3DXVec2TransformCoordArray  m_TFunc_D3DXVec2TransformCoordArray;
		TFunc_D3DXVec2TransformNormal      m_TFunc_D3DXVec2TransformNormal;
		TFunc_D3DXVec2TransformNormalArray m_TFunc_D3DXVec2TransformNormalArray;
		//TFunc_D3DXVec3Add           m_TFunc_D3DXVec3Add;
		TFunc_D3DXVec3BaryCentric   m_TFunc_D3DXVec3BaryCentric;
		TFunc_D3DXVec3CatmullRom    m_TFunc_D3DXVec3CatmullRom;
		//TFunc_D3DXVec3Cross         m_TFunc_D3DXVec3Cross;
		//TFunc_D3DXVec3Dot           m_TFunc_D3DXVec3Dot;
		TFunc_D3DXVec3Hermite       m_TFunc_D3DXVec3Hermite;
		//TFunc_D3DXVec3Length        m_TFunc_D3DXVec3Length;
		//TFunc_D3DXVec3LengthSq      m_TFunc_D3DXVec3LengthSq;
		//TFunc_D3DXVec3Lerp          m_TFunc_D3DXVec3Lerp;
		//TFunc_D3DXVec3Maximize      m_TFunc_D3DXVec3Maximize;
		//TFunc_D3DXVec3Minimize        m_TFunc_D3DXVec3Minimize;
		TFunc_D3DXVec3Normalize       m_TFunc_D3DXVec3Normalize;
		TFunc_D3DXVec3Project         m_TFunc_D3DXVec3Project;
		TFunc_D3DXVec3ProjectArray    m_TFunc_D3DXVec3ProjectArray;
		//TFunc_D3DXVec3Scale           m_TFunc_D3DXVec3Scale;
		//TFunc_D3DXVec3Subtract        m_TFunc_D3DXVec3Subtract;
		TFunc_D3DXVec3Transform       m_TFunc_D3DXVec3Transform;
		TFunc_D3DXVec3TransformArray  m_TFunc_D3DXVec3TransformArray;
		TFunc_D3DXVec3TransformCoord  m_TFunc_D3DXVec3TransformCoord;
		TFunc_D3DXVec3TransformCoordArray   m_TFunc_D3DXVec3TransformCoordArray;
		TFunc_D3DXVec3TransformNormal       m_TFunc_D3DXVec3TransformNormal;
		TFunc_D3DXVec3TransformNormalArray  m_TFunc_D3DXVec3TransformNormalArray;
		TFunc_D3DXVec3Unproject      m_TFunc_D3DXVec3Unproject;
		TFunc_D3DXVec3UnprojectArray m_TFunc_D3DXVec3UnprojectArray;
		//TFunc_D3DXVec4Add            m_TFunc_D3DXVec4Add;
		TFunc_D3DXVec4BaryCentric    m_TFunc_D3DXVec4BaryCentric;
		TFunc_D3DXVec4CatmullRom m_TFunc_D3DXVec4CatmullRom;
		TFunc_D3DXVec4Cross      m_TFunc_D3DXVec4Cross;
		//TFunc_D3DXVec4Dot        m_TFunc_D3DXVec4Dot;
		TFunc_D3DXVec4Hermite    m_TFunc_D3DXVec4Hermite;
		//TFunc_D3DXVec4Length     m_TFunc_D3DXVec4Length;
		//TFunc_D3DXVec4LengthSq   m_TFunc_D3DXVec4LengthSq;
		//TFunc_D3DXVec4Lerp       m_TFunc_D3DXVec4Lerp;
		//TFunc_D3DXVec4Maximize   m_TFunc_D3DXVec4Maximize;
		//TFunc_D3DXVec4Minimize        m_TFunc_D3DXVec4Minimize;
		TFunc_D3DXVec4Normalize       m_TFunc_D3DXVec4Normalize;
		//TFunc_D3DXVec4Scale           m_TFunc_D3DXVec4Scale;
		//TFunc_D3DXVec4Subtract        m_TFunc_D3DXVec4Subtract;
		TFunc_D3DXVec4Transform       m_TFunc_D3DXVec4Transform;
		TFunc_D3DXVec4TransformArray  m_TFunc_D3DXVec4TransformArray;



 
							   
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


		//------  Precomputed Radiance Transfer Functions   -----------


		TFunc_D3DXCreatePRTBuffer   m_TFunc_D3DXCreatePRTBuffer ;
		TFunc_D3DXCreatePRTBufferTex   m_TFunc_D3DXCreatePRTBufferTex ;
		TFunc_D3DXCreatePRTCompBuffer   m_TFunc_D3DXCreatePRTCompBuffer ;
		TFunc_D3DXCreatePRTEngine   m_TFunc_D3DXCreatePRTEngine ;
		TFunc_D3DXCreateTextureGutterHelper   m_TFunc_D3DXCreateTextureGutterHelper ;

		TFunc_D3DXLoadPRTBufferFromFileA   m_TFunc_D3DXLoadPRTBufferFromFileA ;
		TFunc_D3DXLoadPRTBufferFromFileW   m_TFunc_D3DXLoadPRTBufferFromFileW ;

		TFunc_D3DXLoadPRTCompBufferFromFileA   m_TFunc_D3DXLoadPRTCompBufferFromFileA ;
		TFunc_D3DXLoadPRTCompBufferFromFileW   m_TFunc_D3DXLoadPRTCompBufferFromFileW ;

		TFunc_D3DXSavePRTBufferToFileA   m_TFunc_D3DXSavePRTBufferToFileA ;
		TFunc_D3DXSavePRTBufferToFileW   m_TFunc_D3DXSavePRTBufferToFileW ;

		TFunc_D3DXSavePRTCompBufferToFileA   m_TFunc_D3DXSavePRTCompBufferToFileA ;
		TFunc_D3DXSavePRTCompBufferToFileW   m_TFunc_D3DXSavePRTCompBufferToFileW ;

		TFunc_D3DXSHPRTCompSplitMeshSC   m_TFunc_D3DXSHPRTCompSplitMeshSC ;
		TFunc_D3DXSHPRTCompSuperCluster   m_TFunc_D3DXSHPRTCompSuperCluster ;






		//------------   Shader Functions   ------------------


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




	//--------------------------------------------
	//            UVAtlas Functions
	//--------------------------------------------


	TFunc_D3DXUVAtlasCreate      m_TFunc_D3DXUVAtlasCreate;
	TFunc_D3DXUVAtlasPack        m_TFunc_D3DXUVAtlasPack;
	TFunc_D3DXUVAtlasPartition   m_TFunc_D3DXUVAtlasPartition;
	TFunc_D3DXComputeIMTFromPerTexelSignal   m_TFunc_D3DXComputeIMTFromPerTexelSignal;
	TFunc_D3DXComputeIMTFromPerVertexSignal  m_TFunc_D3DXComputeIMTFromPerVertexSignal;
	TFunc_D3DXComputeIMTFromSignal      m_TFunc_D3DXComputeIMTFromSignal;
	TFunc_D3DXComputeIMTFromTexture     m_TFunc_D3DXComputeIMTFromTexture;










		Functions()
		{
			memset(&m_TFunc_D3DXCheckVersion, 0 , sizeof(Functions)  );
		}


		//!  \brief   обработка - функция sFuncName  не найдена в длл
		void handleNotFoundAddr(const char* sFuncName, void* opt=NULL) ;

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



#endif // #if ( defined(WIN32) )      // && defined(GB_D3D9)  )
// end file