
#include "pch.h"

#if (defined(WIN32) )


#include <gb/system/winappl/winappl.h>

#define PRINT_FUNC printf("%s\n", __FUNCTION__);

namespace gb {
namespace system {
namespace winappl {

//=========================================================================




//=========================================================================
//               Appl3D
//=========================================================================


//=========================================================================
Appl3D::Appl3D() : m_CaptureTimer(&m_fpsMonData, &m_frameDrawTimeMonData) 
{
		m_hwnd = 0;
		memset(&m_windowinfo, 0, sizeof(m_windowinfo) );
		m_pntCursorPos.x = 0;
		m_pntCursorPos.y = 0;
   m_bShutDownFlag = FALSE;

}

//=========================================================================
Appl3D::~Appl3D()
{


};

//=========================================================================
HRESULT Appl3D::keybMsgProc(const unsigned int nvkey, bool bDown )
{
	PRINT_FUNC
		HRESULT hr =0;

	if(getAppl3dInitData()->basecallback.funcOnKeyboard)
	{
		__try {
			hr |=  getAppl3dInitData()->basecallback.funcOnKeyboard(
				getAppl3dInitData()->basecallback.pUserParam, nvkey, bDown
				);
		}
		__except(1)
		{
			// ?????  except  todo : insert handler
			return E_FAIL;
		};
	}

	if(bDown)
	{
		if(nvkey == 27) // esc
		{
			// 		::SendMessageA(m_hwnd , xxxx,  www, lll );
			//#pragma message("НЕПРАВИЛЬНО !!!"  __FILE__ )
			//PostQuitMessage( 0 );
			this->shutDown(0);
			//PostShutDownCommand();
			return hr;
		}

	}


	// ??????????
	//hr = 535;


	return hr;

};

//=========================================================================
HRESULT Appl3D::mouseMsgProc(POINT pnt)
{
  HRESULT hr =0;
    assert(false);

  return hr;
};

//=========================================================================
HRESULT Appl3D::messageProc(HWND hWnd, UINT msg, 
							WPARAM wParam, LPARAM lParam, 
							BOOL* pbNeedProcessAgain )
{
	HRESULT hr =0;

	APPL_3D_INIT_DATA* pidata = getAppl3dInitData();

  if( pidata->basecallback.funcOnMessage )
  {
    pidata->basecallback.funcOnMessage(
	  pidata->basecallback.pUserParam, hWnd, msg, wParam, lParam,
	  pbNeedProcessAgain  );

  }
 

  return hr;
};


//=========================================================================
HRESULT Appl3D::doBeginFrameDraw()
{
	HRESULT hr = 0;
 

	// update time
	static float laseTime = 0.0f;
	if(laseTime == 0.0f )
	{
		// first call
		 laseTime = ((float)timeGetTime()) / 1000.0f;
	    m_timeData.m_fDeltaTime = 0.0f;
	}
	else
	{
	  float fcurr = ((float)timeGetTime()) / 1000.0f;
	  m_timeData.m_fDeltaTime =  fcurr - laseTime ;
	  m_timeData.m_fCurrentTime += m_timeData.m_fDeltaTime;

	  laseTime = fcurr;
	}
 
	/*
	  float fOldTime = m_timeData.m_fCurrentTime;

		m_timeData.m_fCurrentTime = 

		m_timeData.m_fDeltaTime = m_timeData.m_fCurrentTime - fOldTime;
 
	 laseTime = (float)timeGetTime();
	 */


	// update window info >> ВОЗМОЖНО ПЕРЕНЕСТИ ДЛЯ УСТРАНЕНИЯ ВЫЗОВОВ 
	// В КАЖДОМ КАДРЕ
	if( ! ::GetWindowInfo(m_hwnd , &m_windowinfo) )
	{
		// error get window info
		hr |= E_FAIL;

	};




	if(! ::GetCursorPos( &m_pntCursorPos ) )
	{
		printf("Error get cursor pos \n");
		return E_FAIL;
	}

	if( !::ScreenToClient(  m_hwnd , &m_pntCursorPos ) )
	{
		printf("SCreen to client \n");
		return E_FAIL;
	}



	return  hr;
}



//=========================================================================



//=========================================================================

//=========================================================================

//=========================================================================

//=========================================================================

#undef PRINT_FUNC

} // end ns
} // end ns
} // end ns

#endif
// end file