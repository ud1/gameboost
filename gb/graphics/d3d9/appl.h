/** \file appl.h
 \brief Шаблон приложения на основе граф. API Directx 9
*
*
 \todo Убрать зависимость от ID3DXFont используется для вывода текста.
*
* 
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once

#include <windows.h>
#include <mmsystem.h>

#include <gb/graphics/d3d9/d3d9.h>
//#include <d3d9.h>


//#include "appl_3d_types.h"
#include <gb/system/winappl/winappl.h>
#include <gb/graphics/d3d9/common.h>

// временно !!!
#include <d3dx9.h>
#include <d3dx9Core.h>


#define   ENABLE_USING_D3DXFONT

// z:\!!gb\gameboost\gb\graphics\d3d9\appl.h


namespace gb 
{

 namespace graphics 
 {

  namespace d3d9 
  {

   //! \brief Приложение на d3d9  и прочее сопутствующее.
   namespace appl 
   {


//-------------------------------------------------------------------------


class ApplD3D9;

// !!!!!!!!! базовые заголовки пока не залиты .

//!   Данные инициализации приложения (класса  ApplD3D9 )
class APPL_D3D9_INIT_DATA  : public  gb::system::winappl::APPL_3D_INIT_DATA 
{
public:

	struct CALLBACKDATAD3D9 
	{
		typedef HRESULT (__cdecl *TFuncOnFrameDraw)(ApplD3D9* const appl, void* pUserParam);
		typedef HRESULT (__cdecl *TFuncOnFrameMove)(void* pUserParam, float fTime, float fDeltaTime);	

		void* pUserParam;

		TFuncOnFrameDraw  funcOnFrameDraw;  
		TFuncOnFrameMove  funcOnFrameMove;



	};

	CALLBACKDATAD3D9 callback_d3d9;

	APPL_D3D9_INIT_DATA()  
	{
		memset(&callback_d3d9, 0, sizeof(callback_d3d9) );


	};

};




// использовать или нет d3dx шрифт (временно !)
//#define ENABLE_USING_D3DXFONT

  //    базовый класс пока не залит
class ApplD3D9  : public gb::system::winappl::Appl3D {
public:
	           ApplD3D9();
	virtual   ~ApplD3D9();

	//-------------------------------------------------------------------------

	virtual HRESULT init(const APPL_D3D9_INIT_DATA* initData);
	virtual HRESULT run();
	virtual HRESULT shutDown(int nExitCode);
	virtual HRESULT finalize();

	IDirect3DTexture9*  getSampleTexture() const  throw();
 
	inline IDirect3DDevice9* getD3D9Device() const { return m_pd3dDevice; }
	inline IDirect3D9* GetDirect3D9() const { return m_pd3d; }
	inline const D3DPRESENT_PARAMETERS* GetPresentParameters() const { return &m_d3dpp; }
	inline const D3DSURFACE_DESC* GetBackBufferSurfDesrc() const { return &m_bbsd; }
 


	virtual HRESULT PostShutDownCommand()    { m_bShutDownFlag = TRUE ; return 0; };

	// temp 
	HRESULT DrawInternalSampleScene() const ;



	//----------------------------------------------------------------

protected:

	virtual gb::system::winappl::APPL_3D_INIT_DATA* getAppl3dInitData() 
	{
	    return (gb::system::winappl::APPL_3D_INIT_DATA*)&m_initdata;
	};

	virtual HRESULT doBeginFrameDraw();
	virtual HRESULT doHandleResizeWindow(int nNewWidth, int nNewHeight);


	HRESULT  destroyDevice();
	HRESULT  initD3D();
	HRESULT  createRenderingWindow(const APPL_D3D9_INIT_DATA* intiData)  ;

	static LRESULT WINAPI mainWindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	HRESULT  reset( int w, int h );
	HRESULT  doRenderind()  ;
	HRESULT  MakeMonDrawText(std::string& sOut, IDirect3D9* pd3d, const D3DSURFACE_DESC* backSurf)  ;
	HRESULT SetupMatrices(const ApplD3D9* pRender) const;
	

private:

#ifdef ENABLE_USING_D3DXFONT
	ID3DXFont*  m_pFont;
#endif

	ID3DXMesh* m_pTempMesh; ///< времянка
	APPL_D3D9_INIT_DATA m_initdata ; 
   
	WNDCLASSEXW m_windowclass ;
 
	//BOOL   m_bFlagShutDown;


	IDirect3D9*             m_pd3d ;
	IDirect3DDevice9*       m_pd3dDevice;
	D3DPRESENT_PARAMETERS   m_d3dpp;
	D3DSURFACE_DESC         m_bbsd;
	D3DCAPS9                m_caps;

};
// end class




//-------------------------------------------------------------------------

	} // end ns

   } // end ns

  } // end ns 

} // end ns 

#endif
// end file