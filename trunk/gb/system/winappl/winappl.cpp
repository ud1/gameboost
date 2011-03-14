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

	////  // update time
	//m_timeData.m_fCurrentTime =	 (float)timeGetTime();
	//static float fprevtime = 0.0f;
	//m_timeData.m_fDeltaTime = m_timeData.m_fCurrentTime - fprevtime;
	//fprevtime = m_timeData.m_fCurrentTime;

	// update time
	{
		const float fOldTime = m_timeData.m_fCurrentTime;
		m_timeData.m_fCurrentTime = (float)timeGetTime();
		m_timeData.m_fDeltaTime = m_timeData.m_fCurrentTime - fOldTime;
	}



	// update window info >> ВОЗМОЖНО ПЕРЕНЕСТИ ДЛЯ УСТРАНЕНИЯ ВЫЗОВОВ 
	// В КАЖДОМ КАДРЕ
	if( ! ::GetWindowInfo(m_hwnd , &m_windowinfo) )
	{
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