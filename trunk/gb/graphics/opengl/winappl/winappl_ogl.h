/** \file
 \brief windows-Приложение на OpenGL
*
*

*
*
 \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/


#ifdef GB_OPENGL
#ifdef WIN32

#pragma once
 
 
#include <gb/system/winappl/winappl.h>
#include <gb/graphics/opengl/ogl.h>

//#include <windows.h>


//#include "appl_3d_types.h"

namespace gb
{

 namespace graphics
 {

  namespace opengl
  {

   namespace winappl 
   {
 
//--------------------------------------------------------------------

class ApplOpenGL;
 

class APPL_OPENGL_INIT_DATA : public gb::system::winappl::APPL_3D_INIT_DATA  {
public:

	struct CALLBACKDATAOGL
	{
		typedef HRESULT (__cdecl *TFuncOnCrateDrawContext)   (ApplOpenGL* appl, void* pUserData);
		typedef HRESULT (__cdecl *TFuncOnDestroyDrawContext) (ApplOpenGL* appl, void* pUserData);

		typedef HRESULT (__cdecl *TFuncOnFrameDraw)(ApplOpenGL* appl, void* pUserData);
		//typedef BOOL    (__cdecl *TFuncApoglOnKeyboard)(int nvkey, bool bDown, void* pUserData);
		//typedef (__cdecl *TFuncApoglOnMouse)( xxxxxx);	


		void* pUserData;

		TFuncOnCrateDrawContext    funcOnCrateDrawContext;
		TFuncOnDestroyDrawContext  funcOnDestroyDrawContext;


		TFuncOnFrameDraw  funcOnFrameDraw;
	//	TFuncApoglOnKeyboard   funcOnKeyboard;


	};



	unsigned long nWindowBits  ;

	//BOOL bWindowed  ;

	//CLEARCOLOR clearColor;

	CALLBACKDATAOGL  callback_ogl;


	APPL_OPENGL_INIT_DATA() {

		memset(&callback_ogl , 0, sizeof(callback_ogl) );

		clearColor.blue += 0.31f;

		nWindowBits = 32;




	};
};



//* \brief  Для отрисовки текста
class DrawFontData {
public:
	unsigned int m_fontListBase ; 
	HFONT m_hfont;

	DrawFontData() 
	{
		m_fontListBase=0;
		m_hfont = 0;
	};

	//* удалить если не удалён
	void release()
	{
		if (m_fontListBase != 0)
		{
			glDeleteLists(m_fontListBase, 96);
			m_fontListBase =0;
		}

		if(m_hfont)
		{
			DeleteObject( m_hfont ); 
			m_hfont = 0;
		}
	}

	//* созданы ли данные , если нет тогда создать.
	HRESULT check_created(HDC hdc)
	{
		HRESULT hr = 0;
		if(m_fontListBase) return hr;

		m_fontListBase =  glGenLists(96);

		m_hfont = CreateFontA(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			"Courier New");

		/*	  m_hfont = CreateFontA (
		xxx, // __in  int nHeight,
		xxx, // __in  int nWidth,
		xxx, // __in  int nEscapement,
		xxx, // __in  int nOrientation,
		xxx, // __in  int fnWeight,
		xxx, // __in  DWORD fdwItalic,
		xxx, // __in  DWORD fdwUnderline,
		xxx, // __in  DWORD fdwStrikeOut,
		xxx, // __in  DWORD fdwCharSet,
		xxx, // __in  DWORD fdwOutputPrecision,
		xxx, // __in  DWORD fdwClipPrecision,
		xxx, // __in  DWORD fdwQuality,
		xxx, // __in  DWORD fdwPitchAndFamily,
		xxx, // __in  LPCTSTR lpszFace
		);
		*/

		if (!m_hfont)
			return E_FAIL;

		if(!SelectObject(  hdc, m_hfont) )
		{
			return E_FAIL;    
		}

		if(! wglUseFontBitmapsA( hdc,   32, 96,  m_fontListBase  ) )
		{
			return E_FAIL;
		};

		return hr;
	}

	//* подготовка трансформации к выводу строк
	HRESULT doPrepareTransform(uint32_t nClientWidth, uint32_t nClientHeight)
	{

		glMatrixMode(GL_PROJECTION); 
		glLoadIdentity(); 

		glOrtho(
			0.0f, 
			nClientWidth - 1.0, 
			nClientHeight - 1.0, 
			0.0f, 
			-1.0, 
			1.0
			);

		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity(); 

		return S_OK;
	}

	HRESULT drawString(HDC hdc, int x, int y,   const char* str)
	{
		if( FAILED(check_created(hdc) ) )
		{
			return E_FAIL;
		}


		if ( !str )
			return S_FALSE;

		glRasterPos2i(  x,   y);
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_fontListBase   - 32);
		glCallLists((int)strlen(str), GL_UNSIGNED_BYTE, str);
		glPopAttrib();


		return  0;
	}


};




class ApplOpenGL : public gb::system::winappl::Appl3D {
public:
	ApplOpenGL();
	virtual  ~ApplOpenGL();

HRESULT init(const APPL_OPENGL_INIT_DATA* pInitData);
virtual HRESULT run() ;
virtual HRESULT shutDown(int nExitCode) ;
virtual HRESULT finalize() ;


	//void setupProjection(int width, int height);

	inline HDC   getDeviceContext() const { return m_hDC; };
	inline HGLRC getGlRenderContext() const { return m_hRC; }; 

	inline  DrawFontData* getDrawFontData() { return &m_DrawFontData; };

protected:

	virtual gb::system::winappl::APPL_3D_INIT_DATA* getAppl3dInitData() 
	{
	  return (gb::system::winappl::APPL_3D_INIT_DATA*)&m_initdata;
	};

	virtual HRESULT doBeginFrameDraw();
	virtual HRESULT doHandleResizeWindow(int nNewWidth, int nNewHeight);

	HRESULT                   doRendering();
	HRESULT                   setupPixelFormat(HDC hDC);
	static LRESULT CALLBACK   mainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//HRESULT                   keybMsgProc(const unsigned int nvkey, bool bDown ) const;


private:

	class StringsHardwIndo {
	public:
		//StringsHardwIndo() {};

		std::string sVendor; 
		std::string sRenderer; 
		std::string sVersion;
	};



private:
	APPL_OPENGL_INIT_DATA   m_initdata;

	HDC     m_hDC ;
	HGLRC   m_hRC;

 
	DrawFontData  m_DrawFontData;

	StringsHardwIndo m_StringsHardwIndo;

};

//--------------------------------------------------------------------

   } // end ns
  } // end ns
 } // end ns
} // end ns

#endif // #ifdef WIN32
#endif // #ifdef GB_OPENGL
// end file