#error СТАРЫЙ ФАЙЛ.  ВЗЯТЬ С НЕГО КОД 

#include "stdafx.h"



#include "LDXEFH_materials.h"
#include "LDXEFH_SearchSemantics.h"


#include <string>

#pragma warning (push)
#pragma warning (disable : 4996)

 
IEFF* g_pEff = NULL;
static char g_filename[MAX_PATH];
 

ITX* g_pTextureDiffuse = NULL;
ICTX* g_pCubemap = NULL;

ITX* g_pNM_diffuse     = NULL;
ITX* g_pNM_normalmap   = NULL;

 static float fRotateTime = 0.0f;

static DAPLIB_InitData  g_InitData;
static DAPLIB_CallBackData g_pCallBack;
  // надо ли кидать в лог сообщения
  bool g_bneedputlog = true; 


  class Parameter {
  public:
	  Parameter() { memset(&m_sem_id, 0, sizeof(Parameter) );  };
	 // virtual ~Parameter() {   };

	int m_sem_id;
	D3DXPARAMETER_DESC pd;
	D3DXHANDLE hp;

	float m_data[4];

	

	//void set_semid(int _val) {  m_sem_id = _val; };
	//inline int get_sem_id() const { return m_sem_id; };

  private:

};


  //kst::VectorPointers<Parameter> g_semparams; 
  std::vector<Parameter> g_vector_params; 
 

#define __PUTLOG(m) //	MONPRINT(m);

 


//-------------------------------------------------------
static HRESULT __SetEffFloat(PINC context, IEFF* pEff, const Parameter* par ) {
  HRESULT hr =0;
  __PUTLOG(__FUNCTION__);
	if(!par->pd.Semantic) return hr;

	static SemanticNameBuffer sem ;
//	strcpy(sem.buffer  ,  par->pd.Semantic );
		sem =   par->pd.Semantic;
  int semid = GetSemanticIDbyName_float(sem);

   // пока не устанавливаются...
  return hr;

  if( semid <= 0 ) {
	 // not found
	  return hr;
  };




  /********************
  // set .....
  //
  switch(semid) {
  //case xxxx: {  hr|= pEff->SetFloat(h, xxxxxxx  ); } break;
 // case xxxx: {  hr|= pEff->SetFloat(h, xxxxxxx  ); } break;


  default: {
	  //* none
		   };
  };  // switch

  ********************/

 
	return hr  ;
};

//-------------------------------------------------------
static HRESULT __SetEffVector3(PINC context, IEFF* pEff, const  Parameter* par ) {
   HRESULT hr =0;
     __PUTLOG(__FUNCTION__);
   if(!par->pd.Semantic) return hr;

  
   switch(par->m_sem_id) {
 case RMSEM_f3_ViewPosition: {  
	 hr|=pEff->SetFloatArray(par->hp, (FLOAT*)g_efmatrcntxt.GetViewPos4() , 3 );  } break;


 default: {
	 MONPRINT("Unknow float3 parameter \n");
		hr |= E_FAIL;
		  };
   };


  return hr	;
};

//---------------------------------------------------------
HRESULT __SetEffVector4(PINC context, IEFF* pEff, const  Parameter* par ) {
   HRESULT hr =0;
       __PUTLOG(__FUNCTION__);
   if(!par->pd.Semantic) return hr;
 
		 
 switch(par->m_sem_id) {
 case RMSEM_f4_ViewPosition: {  hr|=pEff->SetVector(par->hp, g_efmatrcntxt.GetViewPos4() );  } break;


 default: {

		  };

 };   // switch
 
	return hr;
};

//---------------------------------------------------------
static HRESULT __SetEffFloat4x4(PINC context, IEFF* pEff, const  Parameter* par ) {
	HRESULT hr =0;
	   __PUTLOG(__FUNCTION__);
	if(!par->pd.Semantic) return hr;
 

	switch(par->m_sem_id) {
  case RMSEM_f4x4_View: { hr|= pEff->SetMatrix(par->hp, g_efmatrcntxt.GetView() ); }  break;
  case RMSEM_f4x4_ViewProjection: { hr|= pEff->SetMatrix(par->hp, g_efmatrcntxt.GetViewProjection() ); }  break;
  case RMSEM_f4x4_World: {  hr|= pEff->SetMatrix(par->hp, g_efmatrcntxt.GetWorld() ); }  break;
  case RMSEM_f4x4_WorldViewProjection: {  hr|= pEff->SetMatrix(par->hp, g_efmatrcntxt.GetWorldViewProjection() ); }  break;


 // case xxxx: {  }  break;
 
  default: {

		   };

	};

  return hr	;
};


//-----------------------------------------------------

HRESULT BumpyShinyVariations (PINC context, const D3DXMATRIX* world)
{	HRESULT hr =0;
	// Set transform from object space to projection space




   D3DXMATRIX   m_View ,  m_Scene;
		m_View = context->mView;
		m_Scene = context->mProj;

   D3DXVECTOR3 m_LightDirection =   D3DXVECTOR3( 1.0f, 0.0f, 0.0f );

   D3DXMATRIX CubeRotationMatrix;
   D3DXMatrixIdentity(&CubeRotationMatrix);

	D3DXMATRIX worldViewProj =   *world    * m_View *  m_Scene ;
	hr|= g_pEff->SetMatrix("WorldViewProj", &worldViewProj);

	// Send light direction in object space
	D3DXMATRIX world2obj;
	D3DXMatrixInverse(&world2obj, 0,  world);
	D3DXVECTOR3 lightDirectionInObjectSpace;
	D3DXVec3TransformNormal(&lightDirectionInObjectSpace, &m_LightDirection, &world2obj);
	// shader math requires that the light direction vector points towards the light.
	lightDirectionInObjectSpace = - lightDirectionInObjectSpace;
	D3DXVec3Normalize(&lightDirectionInObjectSpace, &lightDirectionInObjectSpace);
	hr|= g_pEff->SetValue("LightVector", &lightDirectionInObjectSpace, sizeof(D3DXVECTOR3));

	// Send eye position in object space
	D3DXMATRIX view2world;
	D3DXMatrixInverse(&view2world, 0, &m_View);
	D3DXVECTOR3 eyePositionInWorldSpace(view2world._41, view2world._42, view2world._43);
	D3DXVECTOR3 eyePositionInObjectSpace;
	D3DXVec3TransformCoord(&eyePositionInObjectSpace, &eyePositionInWorldSpace, &world2obj);
	hr|= g_pEff->SetValue("EyePosition", &eyePositionInObjectSpace, sizeof(D3DXVECTOR3));

	//D3DXMATRIX CubeRotationMatrix = m_World;
	D3DXMATRIX obj2cube;
	D3DXMATRIX world2cube;

	// For environment mapping: transform from object space to cube space
	D3DXMatrixTranspose(&world2cube, &CubeRotationMatrix);
	D3DXMatrixMultiply(&obj2cube,  world, &world2cube);
	//D3DXMatrixTranspose(&obj2cube, &obj2cube);
	hr|= g_pEff->SetMatrix("ObjToCubeSpace", &obj2cube);

	// For environment mapping: Set the bump scale
	static FLOAT m_fBumpScale = 0.5f;
	hr|= g_pEff->SetValue("BumpScaleEnv", &m_fBumpScale, sizeof(float));
			 
	// For environment mapping: eye position in cube space
	D3DXMatrixInverse(&view2world, 0, &m_View);
	D3DXVECTOR3 eyeWorldPos(view2world._41, view2world._42, view2world._43);
	D3DXVECTOR3 eyeCubePos;
	D3DXMatrixTranspose(&world2cube, &CubeRotationMatrix);
	D3DXVec3TransformCoord(&eyeCubePos, &eyeWorldPos, &world2cube);
	hr|= g_pEff->SetValue("EyePositionEnv", &eyeCubePos, sizeof(D3DXVECTOR3));

	return hr;
}

//---------------------------------------------------
static HRESULT __SetEffTexture(PINC context, IEFF* pEff, const  Parameter* par ) {
  HRESULT hr =0;
  	if(!par->pd.Semantic) return hr;
 
	switch (par->m_sem_id) {
  case RMSEM_txtr_DiffuseMap : { hr |= pEff->SetTexture(par->hp, g_pTextureDiffuse ); } break;
  case RMSEM_txtr_NormalMap  : { hr |= pEff->SetTexture(par->hp, g_pNM_normalmap ); } break;
  case RMSEM_txtr_SelfIluminationMap  : {  } break;
  case RMSEM_txtr_ReflectionMap  : {  } break;
  case RMSEM_txtr_BumpMap   : {  hr |= pEff->SetTexture(par->hp, g_pNM_normalmap ); } break;
  case RMSEM_txtr_LightMap : {  } break;
  case RMSEM_txtr_HeightMap   : {  } break;
  case RMSEM_txtr_SpecularMap  : {  } break;
  case RMSEM_txtr_EnvirMap  : { hr |= pEff->SetTexture(par->hp, g_pCubemap);  } break;

   default: {
	   // none !!!
			};
 
	};   // switch

 

  return hr	;
};


// функция установки всех параметров в эффект
HRESULT   __SetRenderEffParams(PINC context, IEFF* pEff, const D3DXMATRIX* w) {
  HRESULT hr =0;
 

   hr|= BumpyShinyVariations(context,  w);
   if FAILED(hr) {
	   MONPRINT("Faile set  BumpyShinyVariations \n");
   };


			const UINT CSZE = (UINT)g_vector_params.size();  
  for(UINT c=0; c< CSZE; c++) {

   Parameter par =	g_vector_params.at((size_t)c);

	if(!par.pd.Semantic) {
		// no set
		continue;
	};


	switch( par.pd.Type ) {
	 case D3DXPT_FLOAT: {

		 if( par.pd.Class == D3DXPC_SCALAR ) {
			  hr |= __SetEffFloat(context,   pEff,  &par );	
		 };

		 if( par.pd.Class == D3DXPC_VECTOR ) {
			 if(par.pd.Columns == 3)   hr |= __SetEffVector3(context,   pEff,    &par  );
			 if(par.pd.Columns == 4)   hr |= __SetEffVector4(context,   pEff,    &par   );
		 };

	     if( (par.pd.Class == D3DXPC_MATRIX_ROWS) || (par.pd.Class == D3DXPC_MATRIX_COLUMNS) ) {
		    if( (par.pd.Rows==4)  && (par.pd.Columns==4) ) {
			    hr |= __SetEffFloat4x4(context,   pEff,     &par   );	
		    };

		  };
 

	    } break; // case D3DXPT_FLOAT:
 
 
	 case D3DXPT_TEXTURE: {
		        hr |= __SetEffTexture(context,   pEff,    &par   );	 
			 
	 } break;

	 default: {
		 // undef
			  };
	};	// switch

 

  if FAILED(hr)
	    break;

  };  // for

  if FAILED(hr) {
	  MONPRINT("FAILED \n");
  };
 
	return hr;
};

//------------------------
HRESULT __SetTechn(PINC context, IEFF* pEff, UINT number) {
	if(!pEff) return 0;
   HRESULT hr =0;

   D3DXEFFECT_DESC ed;
 hr|= pEff->GetDesc(&ed);
 if FAILED(hr) return hr;

 if(number > ed.Techniques-1) { number = ed.Techniques-1; };

  D3DXTECHNIQUE_DESC td;
 D3DXHANDLE htechn = pEff->GetTechnique(number);
 if(!htechn) return E_FAIL;

  hr|=pEff->SetTechnique(htechn);

 return hr;

};


HRESULT   __FuncDAPLIB_OnCreateDevice(IDVC* pdvc, const D3DSURFACE_DESC* pbbsd, void* pUserData )
{
	HRESULT hr = 0;

 // hr |= D3DXCreateTextureFromFileA(pdvc, "z:\\_KSW\\CLIENT\\GRAPHIC\\LDXEFH\\LDXEFH\\test_texture\\txtr_DF.bmp", &g_pTextureDiffuse);
  hr |= D3DXCreateTextureFromFileA(pdvc, "z:\\!TEXTURES\\!DVD\\!GROUND\\7651a055.dds", &g_pTextureDiffuse);
  hr |= D3DXCreateCubeTextureFromFileA(pdvc, "Z:\\!TEXTURES\\!DVD\\!CUBEMAP\\Sky128.dds", &g_pCubemap );

  hr |= D3DXCreateTextureFromFileA(pdvc, "Z:\\_KSW\\CLIENT\\GRAPHIC\\__LDXEFH_old\\LDXEFH\\media\\rockwall_diffuse.dds", &g_pNM_diffuse);
  hr |= D3DXCreateTextureFromFileA(pdvc, "Z:\\_KSW\\CLIENT\\GRAPHIC\\__LDXEFH_old\\LDXEFH\\media\\rockwall_normal.dds", & g_pNM_normalmap);
	


	return hr;
};

HRESULT   __FuncDAPLIB_OnResetDevice(IDVC* pdvc, const D3DSURFACE_DESC* pbbsd, void* pUserData )
{
	HRESULT hr = 0;
	  g_Material_test_EffectParam.ResetDevice();
	  g_MaterialBumpReflectNoDiffuse.ResetDevice();
	  g_MaterialBumpPointLight.ResetDevice();
	   g_MaterialBumpSpecular.ResetDevice();

	   if(g_pEff) {
		   hr |= g_pEff->OnResetDevice();
	   };


	return hr;
};

HRESULT  __FuncDAPLIB_OnLostDevice (void* pUserData)
{  
	HRESULT hr = 0;
	 g_Material_test_EffectParam.LostDevice();
	 g_MaterialBumpReflectNoDiffuse.LostDevice();
	 g_MaterialBumpPointLight.LostDevice();
	 g_MaterialBumpSpecular.LostDevice();

	 if(g_pEff) {
		 hr |= g_pEff->OnLostDevice();
	 };


 return 0;
};

HRESULT  __FuncDAPLIB_OnDestroyDevice(void* pUserData)
{  
	HRESULT hr = 0;
	 g_Material_test_EffectParam.Release();
	 g_MaterialBumpReflectNoDiffuse.Release();
	 g_MaterialBumpPointLight.Release();
	 g_MaterialBumpSpecular.Release();


 SAFE_REL(g_pTextureDiffuse);
 SAFE_REL(g_pCubemap);

   SAFE_REL(g_pNM_diffuse); 
   SAFE_REL(g_pNM_normalmap);


	SAFE_REL(g_pEff);
 
  return 0;
}; 

static HRESULT __Create(IEFF** ppOut, IDVC* pdevice) {
  HRESULT hr =0;
  if(g_filename[0] == 0) 
	    return hr;
   //  __try   {
	
	  hr = D3DXCreateEffectFromFileA(
		    pdevice,
		  g_filename, //LPCTSTR pSrcFile,
		  NULL, //CONST D3DXMACRO * pDefines,
		  NULL, //LPD3DXINCLUDE pInclude,
		  0, //DWORD Flags,
		  NULL, // LPD3DXEFFECTPOOL pPool,
		   ppOut, // LPD3DXEFFECT * ppEffect,
		  NULL // LPD3DXBUFFER * ppCompilationErrors
		  );


  //  }    __except(EXCEPTION_EXECUTE_HANDLER)
  //  {
	//hr |= E_FAIL;
	//return hr;
   // }



	if(FAILED(hr)) return hr;

	// hr|=__GetEffParams();

 
	  IEFF* pEff = *ppOut;
	  
	D3DXEFFECT_DESC  effDescr;
	hr |= pEff->GetDesc(&effDescr);
	if FAILED(hr) return hr;



	for(UINT c=0; c<effDescr.Parameters; c++) {

		Parameter par;

		par.hp = pEff->GetParameter( NULL, c);
		if(!par.hp) {
		  hr |=	E_FAIL; 
		  continue;
		}

		hr |= pEff->GetParameterDesc(par.hp, &par.pd);
		if FAILED(hr) return hr;

		if(!par.pd.Semantic) {
			continue;
		};


		static SemanticNameBuffer sem ;
		//strcpy(sem.buffer,  par.pd.Semantic );
			sem = par.pd.Semantic;
	    par.m_sem_id =  GetSemanticIDbyName(sem, &par.pd) ;
 

		if(par.m_sem_id ) {
			g_vector_params.push_back(par);
		};


		if FAILED(hr)
			break;

	};  // for


   return hr;
};
 



//=======================================================================  
void __FuncDAPLIB_FrameMove (float fTime, float fElapsedTime, void* pUserData )
{

} 
//=======================================================================  
HRESULT __FuncDAPLIB_FrameRender (const DAPLIB_RenderContext* context, void* pUserData )
{
    HRESULT hr =0;
	M mWorld, mwvp;
	D3DXMatrixIdentity(&mWorld);
								   //sin(context->fTime * 4.0f) * 2.0f
	 // D3DXMatrixTranslation(&mWorld,      0.0f  ,    0.0f, 0.0f );
	  fRotateTime += context->fTimeElapsed * 0.1f;
	   D3DXMatrixRotationAxis(&mWorld , &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) , fRotateTime );

	 D3DXMatrixMultiply ( &mwvp  ,  &mWorld  , &context->mViewProj  );

	D3DXVECTOR4 eyePos =  *( (D3DXVECTOR4*) &context->mInverseView._41  );

	if(IsVirtualKeyDown(VK_F5) ) {
		if(g_pEff) {
			__try {
			g_pEff->Release(); 
			} __except(1) {};
			
			g_pEff=NULL;
		};

	 g_vector_params.clear();


	 hr |= __Create( &g_pEff , context->pdvc);
	  Sleep(500);
	}

    
	 if(IsVirtualKeyDown(VK_F6) ) {
			  fRotateTime=0.0f;
		   Sleep(1);
	   }

	 if(IsVirtualKeyDown(VK_F6) ) {
		 if(g_pEff) {
			 g_pEff->SetTechnique("EnvSpecular");



		 };
	 }



   g_efmatrcntxt.SetNew( &mWorld, &context->mView, &context->mProj );

   // execute render
   __try {
	   if(g_pEff) {	 



			   // begin test
		   /*
		  g_Test.m_eff = g_pEff;
		  g_Test->SetFloat("fdsfds", 645.6546f);
		   Test* pt =   &g_Test;
		 hr |=  pt->SetMatrix("WorldViewProj", &context->mViewProj );
		// hr |=  pt->SetFloat("fdfsdfds", 456.56456f);

		 Test& tref = g_Test;
		 hr |= tref->SetFloat("dffdsfd", 45543.4354f);

			*/
			// end test


	   hr |= __SetRenderEffParams(context, g_pEff,   &mWorld );
	   if FAILED(hr) return hr;
		  UINT passes =0;
	   hr |= g_pEff->Begin(&passes, 0);
	   for(UINT c=0; c<passes; c++) {
		   hr |= g_pEff->BeginPass(c);
		   hr |= context->funcDrawTeapot(NULL, 1);
		   hr |= g_pEff->EndPass();

		if FAILED(hr) break;
	   };
	   


	   hr |= g_pEff->End();



	   } 
	   else
	   {
		 hr |=DAPLIB_DRWH_DrawStr(24,42, "Effect is NULL", &COLOR4F_RED  );

	   };// if




   }   __except(1) {
	  hr |=DAPLIB_DRWH_DrawStr(20,200, "Render Exception \n", &COLOR4F_RED  );
	   hr |= E_FAIL;
   };

   
   if(g_filename[0] ) {
   hr |= DAPLIB_DRWH_DrawStrEx(20,220, g_filename  , dapl_fontsize_normal , &COLOR4F_YELLOW  );
   }
   else
   {
   hr |= DAPLIB_DRWH_DrawStrEx(20,220, "File no defined." , dapl_fontsize_normal , &COLOR4F_YELLOW  );
   }

   DAPLIB_DRWH_DrawFormat(20,240,  dapl_fontsize_normal ,  "Nums semantic param: %u\n" , (unsigned int)g_vector_params.size() );
   Parameter par;
   for(size_t c=0; c<g_vector_params.size(); c++ ) {
	  par = g_vector_params.at(c);
	 hr |= DAPLIB_DRWH_DrawStrEx(0,0,  par.pd.Semantic  , dapl_fontsize_normal , &COLOR4F_YELLOW  );

   };




   // end
  return hr;



	   //* test g_MaterialBumpSpecular
	   hr |= g_MaterialBumpSpecular.CheckCreate(context->pdvc);
	   hr |= g_MaterialBumpSpecular.SetMatrixViewProj(&mwvp);
	   hr |= g_MaterialBumpSpecular.SetMatrixView(&context->mView);
	   hr |= g_MaterialBumpSpecular.SetMatrixWorld(&mWorld );

	   hr |= g_MaterialBumpSpecular.SetEyePosition(&eyePos);

	   hr |= g_MaterialBumpSpecular.SetTextureDiffuse(g_pNM_diffuse);
	   hr |= g_MaterialBumpSpecular.SetTextureNormalMap(g_pNM_normalmap); 

	   hr |= g_MaterialBumpSpecular.BeginDraw();
	   hr |= context->funcDrawTeapot(NULL, TRUE);
	   hr |= g_MaterialBumpSpecular.EndDraw();
	   return hr;






	   //* test g_MaterialBumpPointLight
	   hr |= g_MaterialBumpPointLight.CheckCreate(context->pdvc);

	   hr |= g_MaterialBumpPointLight.SetMatrixWorldViewProj(&mwvp);
	   hr |= g_MaterialBumpPointLight.SetMatrixWorld(&mWorld );

	   hr |= g_MaterialBumpPointLight.SetTextureDiffuse(g_pNM_diffuse);
	   hr |= g_MaterialBumpPointLight.SetTextureNormalMap(g_pNM_normalmap);

	   hr |= g_MaterialBumpPointLight.BeginDraw();
	   hr |= context->funcDrawTeapot(NULL, TRUE);
	   hr |= g_MaterialBumpPointLight.EndDraw();
	   return hr;









   //* test MaterialBumpReflectNoDiffuse
   hr |= g_MaterialBumpReflectNoDiffuse.CheckCreate(context->pdvc);

   hr |= g_MaterialBumpReflectNoDiffuse.SetMatrixWorldViewProj(&mwvp);
   hr |= g_MaterialBumpReflectNoDiffuse.SetMatrixWorld(&mWorld );


  M mTemp;
 /* //Set variables for the effect
  //Calculate the matrices
  Matrix modelViewProj = matBox * camera.MatView * camera.MatProj;
  Matrix modelViewIT = matBox * camera.MatView * camera.MatProj;

  modelViewIT = Matrix.Invert(modelViewIT);
  modelViewIT = Matrix.TransposeMatrix(modelViewIT);*/

	 mTemp =  context->mView;
   D3DXMatrixMultiply( &mTemp, &mWorld , &context->mViewProj );
  D3DXMatrixInverse(&mTemp, NULL,  &mTemp);
   D3DXMatrixTranspose(&mTemp, &mTemp);






  hr |= g_MaterialBumpReflectNoDiffuse.GetMaterialEffect()->SetMatrix("ModelViewIT" , &mTemp);


   hr |= g_MaterialBumpReflectNoDiffuse.SetEyePosition(&eyePos);


   hr |= g_MaterialBumpReflectNoDiffuse.SetTextureDiffuse(g_pNM_diffuse);
   hr |= g_MaterialBumpReflectNoDiffuse.SetTextureNormalMap(g_pNM_normalmap);

   hr |= g_MaterialBumpReflectNoDiffuse.BeginDraw();
        hr |= context->funcDrawTeapot(NULL, TRUE);
   hr |= g_MaterialBumpReflectNoDiffuse.EndDraw();
   return hr;


 




   //* test  g_Material_test_EffectParam
  
  hr |= g_Material_test_EffectParam.CheckCreate(context->pdvc);
  hr |= g_Material_test_EffectParam.SetMatrixWorld(&mWorld);
  hr |= g_Material_test_EffectParam.SetMatrixView(&context->mView );
  hr |= g_Material_test_EffectParam.SetMatrixProj(&context->mProj );

 
  hr |= g_Material_test_EffectParam.SetTextureDiffuse(g_pTextureDiffuse);
  hr |= g_Material_test_EffectParam.BeginDraw();
     hr |= context->funcDrawTeapot(NULL, TRUE);
  hr |= g_Material_test_EffectParam.EndDraw();
  return hr;






	return hr;
};  

//=======================================================================
  int _tmain(int argc, _TCHAR* argv[]) {
	HRESULT  hr =0;
 

   g_filename[0]=0;
  
   if(argc < 2) {  
	// strcpy(g_filename, "z:\\CODE_EXPERIMENT\\LDXEFH\\test\\test_effect.fx"); 
	  strcpy(g_filename,    "z:\\_KSW\\CLIENT\\GRAPHIC\\__LDXEFH_old\\LDXEFH\\nvidia\\BumpyShinyVariations\\MEDIA\\programs\\HLSL_BumpyShinyVariations\\BumpyShinyVariations.fx" );
   }
   else
   {
	 strcpy(g_filename, argv[1] ); 
   }



	memset(&g_InitData, 0, sizeof(g_InitData));
	g_InitData.bEnableDXUTGUI = true;
	g_InitData.bEnableLogging = true;
	g_InitData.bFullScreen = false;
	g_InitData.bHandleAltEnter = true;
	g_InitData.bHandleDefaultHotkeys = true;
	g_InitData.bParseCommandLine = true;
	g_InitData.bShowMsgBoxOnError = true;
	g_InitData.clearColor = 0xFF0000FF;
	g_InitData.eCameraMode = daplcm_ModelView ;
	//  g_InitData.  



	memset(&g_pCallBack, 0, sizeof(g_pCallBack));
	g_pCallBack.funcDAPLIB_FrameMove = __FuncDAPLIB_FrameMove;
	g_pCallBack.funcDAPLIB_FrameRender = __FuncDAPLIB_FrameRender;   



	hr |= DAPLIB_RegisterDeviceCallBack(__FuncDAPLIB_OnCreateDevice, __FuncDAPLIB_OnResetDevice, __FuncDAPLIB_OnLostDevice, __FuncDAPLIB_OnDestroyDevice, NULL );



	hr |= DAPLIB_Init ( &g_InitData,  &g_pCallBack, DAPPLLIBRARY_VERSION);
	if FAILED(hr) return hr;





	hr |= DAPLIB_Start();



	return 0;
}


#pragma warning (pop)