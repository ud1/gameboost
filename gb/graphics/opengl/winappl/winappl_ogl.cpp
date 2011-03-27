#ifdef GB_OPENGL
#ifdef WIN32


/*
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
*/

#include <gb/graphics/opengl/winappl/winappl_ogl.h>

#include <assert.h>

#pragma comment( lib, "winmm.lib" )
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "glaux.lib")
 
// link with Win32 GLUT lib 
//#pragma comment (lib, "glut32.lib")

//=========================================================================

namespace gb
{
namespace graphics
{
namespace opengl
{
namespace winappl 
{

// disable implicit float-double casting
#pragma warning(disable:4305)

// времянки
#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

static const WCHAR* CWSTR_CL_CLASSNAME = L"GLClass";


void  __DrawHardwareInfo(ApplOpenGL* appl, bool bIncludePerfInfo, bool bIncludeHardwInfo)
{	
#pragma message("KS777: APPL OGL >> NEED SET CODE "  __FILE__)
	if( (bIncludePerfInfo == false) && (bIncludeHardwInfo == false)) return;
	return ;


	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//static float trnslz = -2.0f;
	//glTranslatef(0.0, 0.0, trnslz );
	//glMatrixMode(GL_PROJECTION);
	glOrtho(
	0.0f, 
	(GLdouble)appl->getWindowClientWidth(), 
	0.0, 
	(GLdouble)appl->getWindowClientHeight(), 
	-10.0, 
	10.0);
	*/

	//static char shwInfo[2048];
	//shwInfo[0] =0;

	//DrawFontData* pdfd = appl->getDrawFontData();

	//if(bIncludeHardwInfo) 
	//{
	//DrawStr(10, context->uiWindowHeight-  85, shwInfo );
	//strcpy(shwInfo, (char*)glGetString(GL_EXTENSIONS) );
	//DrawStr(10, ::GetRenderContextPtr()->uiWindowHeight-  55, shwInfo );
	//};

	/*********************
	if(bIncludePerfInfo) 
	{
	char sfps[32];
	strcat(shwInfo, "Fps= ");
	int ifps =  appl->getCapturedFps() ;
	_itoa_s(	 ifps,	 sfps,	 32, 10  );
	strcat(shwInfo, sfps);

	pdfd->drawString(appl->getDeviceContext(), 10, 30, shwInfo );
	//DrawStr(10, context->uiWindowHeight - 30, shwInfo );

	};
	************************/ 

};

void makeHardwStr(std::string& sOutVendor, std::string& sOutRenderer, std::string& sOutVersion )
{
	char buf [256];
	buf [0] = 0;

	sOutVendor    = "";
	sOutRenderer  = "";
	sOutVersion   = "";

#pragma warning(push)
#pragma warning(disable : 4996)

	strcat(buf, (char*)glGetString (GL_VENDOR)  ); 
	sOutVendor = buf;
	buf [0] = 0;

	strcat(buf, (char*)glGetString (GL_RENDERER)  );
	sOutRenderer = buf; 
	buf [0] = 0;

	strcat(buf, (char*)glGetString (GL_VERSION)  );
	sOutVersion = buf;
	buf [0] = 0;

#pragma warning(pop)

}

ApplOpenGL::ApplOpenGL()  // : m_CaptureTimer(&m_fpsMonData)
{
	m_hDC=0;
	m_hRC = 0;
	m_bShutDownFlag = FALSE;
	//m_hwnd = 0;

	//memset(&m_windowinfo, 0, sizeof(m_windowinfo) );
}

//=========================================================================
ApplOpenGL::~ApplOpenGL()
{

}
 

//=========================================================================
HRESULT ApplOpenGL::doHandleResizeWindow(int nNewWidth, int nNewHeight)
{
  // setupProjection 

 
	if (nNewHeight == 0)                    // don't want a divide by zero
	{
		nNewHeight = 1;                 
	}

	glViewport(0, 0, nNewWidth, nNewHeight);   // reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
	glLoadIdentity();                       // reset projection matrix

 // calculate aspect ratio of window
 gluPerspective(52.0f,(GLfloat)nNewWidth/(GLfloat)nNewHeight,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);             // set modelview matrix
	glLoadIdentity();                       // reset modelview matrix


	m_initdata.nWindowHeight = nNewWidth;	
	m_initdata.nWindowHeight = nNewHeight;  


  return 0;
}

//=========================================================================
HRESULT ApplOpenGL::doBeginFrameDraw()
{
  HRESULT hr =0;
  hr |= gb::system::winappl::Appl3D::doBeginFrameDraw();
  if FAILED(hr)
  {
	  return hr;
  }

  if( (!m_hDC) || (!m_hRC) )
  {
	  return E_FAIL;
  }

  // KS777:  NEW code
  if(!wglMakeCurrent(  m_hDC ,   m_hRC  ))
  {

	  printf("Error make current context \n");
	  return E_FAIL;
  };

  return hr;
};


//=========================================================================
HRESULT ApplOpenGL::doRendering()
{
	HRESULT hr =0;

	hr |= doBeginFrameDraw();
	



	// clear screen and depth buffer	
	glClearColor(	 m_initdata.clearColor.red,  m_initdata.clearColor.green, m_initdata.clearColor.blue, 1.0  );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);


	// draw callback
	m_frameDrawTimeMonData.beginFrameDraw();
	if(m_initdata.callback_ogl.funcOnFrameDraw)
	{

		hr |= m_initdata.callback_ogl.funcOnFrameDraw(this, m_initdata.basecallback.pUserParam );
	}
	else
	{
		// draw sample scene

		// move back 5 units and rotate about all 3 axes
		glTranslatef(0.0, 0.0, -5.0f);	 
		glRotatef( m_timeData.m_fCurrentTime * 0.1f , 1.0f, 0.0f, 0.0f );
		glRotatef( m_timeData.m_fCurrentTime * 0.1f , 0.0f, 1.0f, 0.0f );
		glRotatef( m_timeData.m_fCurrentTime * 0.1f , 0.0f, 0.0f, 1.0f );

		// lime greenish color
		glColor3f(0.7f, 1.0f, 0.3f);

		// draw the triangle such that the rotation point is in the center
		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();

		// end 
	}
	m_frameDrawTimeMonData.endFrameDraw();
	// draw hardw info


	// __DrawHardwareInfo(this, true, true );
	{
		glColor3f(1.0f, 1.0f, 1.0f);
 
#if 1
		hr |= m_DrawFontData.check_created(m_hDC);
		hr |= m_DrawFontData.doPrepareTransform(getWindowClientWidth(), getWindowClientHeight() );

		 hr |= m_DrawFontData.drawString(m_hDC, 10, 10, m_StringsHardwIndo.sRenderer.c_str() );

 
		hr |= m_DrawFontData.drawString(m_hDC, 10, 70, m_fpsMonData.str.c_str() );
		hr |= m_DrawFontData.drawString(m_hDC, 10, 83,  m_frameDrawTimeMonData.m_str.c_str() );
#endif

	}


	// update perf info
	m_fpsMonData.nCountFrames++;


	// swap buf
	if( !SwapBuffers(m_hDC) )
	{
		printf("Error swap buffers \n");
		hr |= E_FAIL;
	};

	return hr;
}

//=========================================================================
HRESULT ApplOpenGL::setupPixelFormat(HDC hDC)
{
	HRESULT hr =0;

	PIXELFORMATDESCRIPTOR pfd =
	{   
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version

		//PFD_SWAP_EXCHANGE | // ks777
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering




		PFD_TYPE_RGBA,              // color type
		24, //32,                         // prefered color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		16,                         // depth buffer
		0,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	int pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if(!pixelFormat)
	{
		printf("Error choose pixel format \n");
		return E_FAIL;
	}

	if(!SetPixelFormat(hDC, pixelFormat, &pfd))
	{
		printf("Error setup pixel format \n");
		hr |= E_FAIL;
	}

	return hr;
}

//=========================================================================
LRESULT CALLBACK ApplOpenGL::mainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//  static 
	//  static 
	int height, width;
	HRESULT hr =0;

	static ApplOpenGL* pApplOpenGL = NULL;
	LPCREATESTRUCT pcrstr = NULL;

	if(pApplOpenGL )
	{
	  if(pApplOpenGL->m_bShutDownFlag)
      {
	  // ????????????  this->
		  //  ??????  do shutdown ...
#pragma message("KS777: ??????  do shutdown ...  " __FILE__ )
	
	  }
	}


	// do msg proc
	if(pApplOpenGL)
	{

      BOOL bNeedProcAgain = TRUE;
	  hr |= pApplOpenGL->messageProc( hWnd, uMsg, wParam, lParam, &bNeedProcAgain);
	  if(!bNeedProcAgain)
	  {
	    return 0;
	  }
	}

	// dispatch messages
	switch (uMsg)
	{   
	case WM_CREATE: 

		pcrstr  = (LPCREATESTRUCT)lParam;
		pApplOpenGL = (ApplOpenGL*)pcrstr->lpCreateParams;
		assert(pApplOpenGL);

		// window creation
		pApplOpenGL->m_hDC = GetDC(hWnd);
		pApplOpenGL->setupPixelFormat( pApplOpenGL->m_hDC );
		//SetupPalette();

		pApplOpenGL->m_hRC = wglCreateContext(pApplOpenGL->m_hDC);
		if(!pApplOpenGL->m_hRC)
		{
			printf("Error wgl create context \n"); 
			return E_FAIL;
		}
		if(!wglMakeCurrent( pApplOpenGL->m_hDC ,  pApplOpenGL->m_hRC  ))
		{
			printf("Error make current context \n");

			return E_FAIL;
		};


     #pragma message("KS777: ТУТ БЫ ПОСТАВИТЬ вызов о создании контекста ")

		break;

	case WM_DESTROY: 
		{
			// window destroy

		}
		break;
		
	case WM_QUIT: {} break;
	case WM_CLOSE:         
		{
			// windows is closing
		assert(pApplOpenGL);

		// de select rendering context and delete it
		wglMakeCurrent(pApplOpenGL->m_hDC, NULL);
		wglDeleteContext(pApplOpenGL->m_hRC);
		pApplOpenGL->m_hRC = 0;
 

      #pragma message("KS777: mainwproc >> need insert handle destroy appl " __FILE__)

		// send WM_QUIT to message queue
		PostQuitMessage(0);
	}
		break;

	case WM_SIZE:
		assert(pApplOpenGL);
		height = HIWORD(lParam);        // retrieve width and height
		width = LOWORD(lParam);
 
		hr |= pApplOpenGL->doHandleResizeWindow(width, height);

		break;

	case WM_ACTIVATEAPP:        // activate app
		break;

	case WM_PAINT:              // paint
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:        // left mouse button
		break;

	case WM_RBUTTONDOWN:        // right mouse button
		break;

	case WM_MOUSEMOVE:          // mouse movement
		break;

	case WM_LBUTTONUP:          // left button release
		break;

	case WM_RBUTTONUP:          // right button release
		break;

	case WM_KEYUP:
		assert(pApplOpenGL);
		hr |= pApplOpenGL->keybMsgProc((unsigned int)wParam, false );


		break;

	case WM_KEYDOWN:
		assert(pApplOpenGL);
		int fwKeys;
		LPARAM keyData;
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		hr |= pApplOpenGL->keybMsgProc( (unsigned int)wParam, true );
		if(pApplOpenGL->m_bShutDownFlag)
		{
          PostQuitMessage(0);
		}


		/****************
		switch(fwKeys)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		****************/

		break;




	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


HRESULT ApplOpenGL::init(const APPL_OPENGL_INIT_DATA* pInitData)
{
	HRESULT hr =0;

	//this->m_initdata
//		this->m_oglInitdata

	if(pInitData)	  
	{
		m_initdata = *pInitData;
	}

	//bool exiting = false;

	WNDCLASSEXW windowClass;     // window class

	DWORD      dwExStyle;       // Window Extended Style
	DWORD      dwStyle;         // Window Style
	RECT       windowRect;


	windowRect.left=(long)0;                        // Set Left Value To 0
	windowRect.right=(long)m_initdata.nWindowWidth; // Set Right Value To Requested Width
	windowRect.top=(long)0;                         // Set Top Value To 0
	windowRect.bottom=(long)m_initdata.nWindowHeight;   // Set Bottom Value To Requested Height

	// fill out the window class structure
	windowClass.cbSize          = sizeof(WNDCLASSEXW);
	windowClass.style           = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc     = mainWindowProc;
	windowClass.cbClsExtra      = 0;
	windowClass.cbWndExtra      = 0;
	windowClass.hInstance       = m_initdata.hInstance;
	windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
	windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
	windowClass.hbrBackground   = NULL;                             // don't need background
	windowClass.lpszMenuName    = NULL;                             // no menu
	windowClass.lpszClassName   = CWSTR_CL_CLASSNAME;
	windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

	// register the windows class
	if ( !RegisterClassExW( &windowClass )  )
	{
	 printf("Error register class \n");
		return  E_FAIL;
	}

    if(m_initdata.bWindowed == FALSE)
	{
		MessageBoxA(NULL, "Полноэкранный режим пока отключён", "ApplOpenGL", 
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST );
    m_initdata.bWindowed = TRUE;
	}


	if (!m_initdata.bWindowed)  // fullscreen?
	{
		DEVMODE dmScreenSettings;                   // device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); 
		dmScreenSettings.dmPelsWidth  = m_initdata.nWindowWidth;   // screen width
		dmScreenSettings.dmPelsHeight = m_initdata.nWindowHeight;   // screen height
		dmScreenSettings.dmBitsPerPel = m_initdata.nWindowBits;  // bits per pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// 
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			printf("Display mode failed \n" );
			m_initdata.bWindowed =  TRUE; 
			return E_FAIL;
		}
	}

	if (!m_initdata.bWindowed)  // Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;                  // Window Extended Style
		dwStyle=WS_POPUP;                       // Windows Style
		ShowCursor(FALSE);                      // Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;                    // Windows Style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

	// class registered, so now create our window
	 
#pragma message("НЕ ОТОБРАЖАЕТСЯ НАДПИСЬ ОКНА ПРИ MULTIBYTE" __FILE__) 
	m_hwnd = CreateWindowExW (
		NULL,                                 // extended style
		CWSTR_CL_CLASSNAME, //  L"GLClass",                          // class name
		L"OpenGL Application",      // app name
		dwStyle | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,                               // x,y coordinate
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, // width, height
		NULL,                               // handle to parent
		NULL,                               // handle to menu
		m_initdata.hInstance,  // application instance
		(void*)this
		);

	// check if window creation failed (hwnd would equal NULL)
	if (!m_hwnd)
	{
        printf("Error create window \n");
		return  E_FAIL;
	}

	m_hDC = GetDC(m_hwnd);
	if(!m_hDC)
	{
	   printf("Error get device context \n");
		return E_FAIL;
	}



	// callback
	if(m_initdata.callback_ogl.funcOnCrateDrawContext)
	{
		hr |= m_initdata.callback_ogl.funcOnCrateDrawContext(
			this, m_initdata.basecallback.pUserParam
			);
	}

	makeHardwStr(m_StringsHardwIndo.sVendor, 
		m_StringsHardwIndo.sRenderer, 
		m_StringsHardwIndo.sVersion);

	if(!ShowWindow(m_hwnd, SW_SHOW))           // display the window
	{
		//printf("Error show window \n");
//		return E_FAIL;

	}

	if(!UpdateWindow(m_hwnd))                 // update the window
	{
		printf("Error update window \n");
		return E_FAIL;
	}




	return   hr;
};

//=========================================================================
HRESULT  ApplOpenGL::run()
{
	HRESULT hr =0;
 
	m_CaptureTimer.start(m_hwnd, 1000 );

	MSG msg; 
	memset(&msg, 0, sizeof(msg) );

	bool exiting = false;
	while (!exiting)
	{
		doRendering();
		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}

	m_CaptureTimer.stop();

	if (m_initdata.bWindowed)
	{
		ChangeDisplaySettings(NULL,0);          // If So Switch Back To The Desktop
		ShowCursor(TRUE);                       // Show Mouse Pointer
	}

#pragma message("KS777: возможно перенести funcOnDestroyDrawContext " __FILE__ )

	// callback
	if(m_initdata.callback_ogl.funcOnDestroyDrawContext)
	{
		hr |= m_initdata.callback_ogl.funcOnDestroyDrawContext(
			this, m_initdata.basecallback.pUserParam
			);
	}

	hr |=  ( HRESULT )msg.wParam;

	////////////////////////////



	return hr;
};

//=========================================================================
HRESULT ApplOpenGL::shutDown(int nExitCode) 
{
  HRESULT hr =0;
  m_bShutDownFlag = TRUE;

#pragma message("KS777: ApplOpenGL::shutDown >> Need correct " __FILE__ )
 
 return hr;
};

//=========================================================================
HRESULT ApplOpenGL::finalize() 
{
  HRESULT hr =0;
  assert(false);

  return hr;
};

////=========================================================================
//HRESULT ApplOpenGL::keybMsgProc(const unsigned int nvkey, bool bDown ) const
//{
//	HRESULT hr =0;
//
//	BOOL bkeybres  =true;
//	if( m_initdata.basecallback.funcOnKeyboard )
//	{
//		// __try {
//		bkeybres =  m_initdata.basecallback.funcOnKeyboard(
//			 m_initdata.basecallback.pUserParam ,nvkey,   bDown 
//			);
//
//		// } __except(1)	  {	  }
//	}
//
//	if(!bkeybres) return hr;
//
//
//
//
//	return hr;
//}


//=========================================================================

} // end ns
} // end ns
} // end ns
} // end ns

#endif // #ifdef WIN32
#endif // #ifdef GB_OPENGL
// end file