/** \file winappl.h
 \brief базовый класс и сопутствующие типы оконного windows приложения 
       для вывода графики.
*
* Залит для проведения отладки. 
* Для класса Appl3D декларированы классы приложений для D3D9 и для OpenGL .
*
* Пока сыро , но всё работает,  для экспериментов годится.
*
 \todo Сделать общей статик функцию обработки сообщений окна
*
* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if (defined(WIN32) )


#pragma once
#define __WINAPPL_H__

#include <gb/config.h>
#include <gb/base/Types.h>

#include <gb/math/math.h>

#include <windows.h>
#include <mmsystem.h>
 

#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string>

#include <assert.h>

namespace gb 
{

  namespace system
  {
  
    /** \brief базовый класс и сопутствующие типы оконного windows приложения  
	   Думал , где же ему место.  Пусть пока поживёт здесь.	*/
    namespace winappl
	{
	
//-------------------------------------------------------------------------

class Appl3D;


//! \brief размер строки надпись окна для APPL_3D_INIT_DATA::strWindowTitle
static const int  APPL3D_WINDOW_TITLE_BUF_LEN  = 32;

//!  \brief Данные инициализации для Appl3D 
class APPL_3D_INIT_DATA {
public:

	//! \brief Цвет очистки устройства.
	struct CLEARCOLOR
	{
		float red, green, blue;
	};

	struct BASECALLBACKDATA 
	{
		void* pUserParam;

	typedef HRESULT (__cdecl *TFuncOnMessage)(void* pUserParam, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* pbNeedProcessAgain );
	typedef HRESULT (__cdecl *TFuncOnKeyboard)(void* pUserParam, int nVirtualKey, bool bKeyDown);
	typedef HRESULT (__cdecl *TFuncOnMouse)(void* pUserParam, POINT pntMouseCoord );

	TFuncOnMessage    funcOnMessage;
	TFuncOnKeyboard   funcOnKeyboard;
	TFuncOnMouse      funcOnMouse;


	};

	BASECALLBACKDATA  basecallback;



	HINSTANCE hInstance;

	BOOL bWindowed;

	UINT nWindowWidth; 
	UINT nWindowHeight;

	BOOL bVSyncOn;

	CLEARCOLOR clearColor;

	/*
	BOOL bParseCommandLine; 
	BOOL bHandleDefaultHotkeys; 
	BOOL bShowMsgBoxOnError; 
	BOOL bHandleAltEnter;
	*/

	BOOL bShowCursorWhenFullScreen; 
	BOOL bClipCursorWhenFullScreen;

	BOOL bUsePrepareRenderBeforeFrameDraw;



	WCHAR strWindowTitle [ APPL3D_WINDOW_TITLE_BUF_LEN ];

 

	APPL_3D_INIT_DATA()
	{
		clearColor.red   =  0.17f;
		clearColor.green =  0.2f;
		clearColor.blue  =  0.66f;

		memset(&basecallback, 0, sizeof(basecallback) );

		hInstance = 0;

		bWindowed = TRUE;

		nWindowWidth  = 800; 
		nWindowHeight = 600;

		bVSyncOn =  FALSE; 	   

		bShowCursorWhenFullScreen = TRUE; 
		bClipCursorWhenFullScreen = TRUE;

		bUsePrepareRenderBeforeFrameDraw = TRUE; 


		memset(strWindowTitle , 0, sizeof(strWindowTitle) ); 



	}


};


inline  float getCurrSysHeightPrecTime() 
{
	LARGE_INTEGER tm, freq;   
	QueryPerformanceCounter(&tm);
	QueryPerformanceFrequency(&freq);
	return   (   ( (float)tm.QuadPart ) / ( (float)freq.QuadPart )   );
};


class  PerfomanceMonData {
public:

	UINT nFrameDrawCount;
	std::string str;

	PerfomanceMonData() { nFrameDrawCount=0; };
};

struct WMPARAMS {

	WPARAM wPar; 
	LPARAM lPar;

};

class FpsMonData {
public:

	uint32_t nCapturedFps;
	uint32_t nCountFrames;
	std::string str;

	void capture(uint32_t nIntervalMs=1000)
	{
		nCapturedFps =  (unsigned int) ( (float)nCountFrames/( (float)nIntervalMs/1000.0f) );
		nCountFrames = 0;

		str = "Fps: ";

		char buffer[32];
#pragma warning (push)
#pragma warning ( disable : 4996 )
#pragma warning ( disable : 4995 )
		sprintf(buffer, "%u", nCapturedFps );
#pragma warning (pop)

		str += buffer;

	}


	FpsMonData() 
	{ 
		nCapturedFps = 0;
		nCountFrames = 0;

	};

};


class FrameDrawTimeMonData {
public:

	BOOL m_bIsBeginCall;
	float  m_fLastTime;
	unsigned int m_nCount;
	float m_fCurrentBegin;
	float m_fTotal;
	float m_fCaptured;
	std::string m_str;

	FrameDrawTimeMonData() 
	{
		setzero();
		m_str.reserve(64);
	};

	void beginFrameDraw() 
	{
		m_fCurrentBegin = getCurrSysHeightPrecTime();

		m_bIsBeginCall = TRUE;

	};

	void endFrameDraw()
	{
		m_fLastTime = getCurrSysHeightPrecTime() - m_fCurrentBegin;
		if (m_fLastTime < 0.0f) m_fLastTime = 0.0f;

		m_fTotal += m_fLastTime;
		m_nCount++;

		m_bIsBeginCall = FALSE;
	};

	void capture(unsigned int nIntervalMs=1000)
	{
		m_fCaptured = ( m_fTotal / (float)m_nCount ) ; //

		// ( (float)nIntervalMs / 1000.0f )  ;

		m_str = "Frame draw time: ";
		char buf[32];
#pragma warning(push)
#pragma warning(disable : 4996)
		sprintf(buf, "%f", m_fCaptured*1000.0f );
 #pragma warning(pop)
		m_str += buf;
		m_str += "  ms";

		float temp = m_fCaptured;
		setzero();
		m_fCaptured = temp;

	}

	void setzero() 
	{
		m_bIsBeginCall = FALSE;
		m_nCount = 0;
		m_fCurrentBegin = 0.0f;

		m_fTotal = 0.0f;
		m_fLastTime = 0.0f;
		m_fCaptured = 0.0f;


	}

};



class TimeData {
public:
	float m_fCurrentTime;
	float m_fDeltaTime;

	TimeData() { m_fCurrentTime=m_fDeltaTime=0.0f; };
};


class CaptureTimer {
private:
	FpsMonData* m_fpsMonData;
	FrameDrawTimeMonData*  m_frDrawTimeMonData;


public:
	CaptureTimer(  FpsMonData* pmdata, FrameDrawTimeMonData* pfdtmd ) 
		: m_fpsMonData(pmdata), m_frDrawTimeMonData(pfdtmd)   
	{    
		m_uiTimerId = 0; 
		m_uElapse=0; 
		m_dwLastTickTime=0; 
		m_nIDEvent=0;	
	};

	virtual ~CaptureTimer() 
	{ 
		stop(); 	
	};

	virtual void onTick(HWND hwnd, UINT uMsg, DWORD dwTime, DWORD dwDelta) 
	{
		m_fpsMonData->capture();
		printf("%s \n" , m_fpsMonData->str.c_str() );
		m_frDrawTimeMonData->capture();
		printf("%s \n" , m_frDrawTimeMonData->m_str.c_str() );

	};


	int start(HWND hWnd, UINT uElapse ) 
	{
		m_uElapse = uElapse;
		if(m_uiTimerId) 
		{
			// error 
			return -1;
		};

		m_nIDEvent = (UINT_PTR)this;
		m_uiTimerId = SetTimer(hWnd, 
			m_nIDEvent, 
			m_uElapse,  
			WINAPI_TIMERPROC);

		if(m_uiTimerId==0 ) 
		{
			// error
			return -1;
		};

		m_hwnd = hWnd;

		return 0;
	};


	int stop() 
	{
		int res=0;
		if(m_uiTimerId==0) return 0;
		if( !KillTimer(m_hwnd, m_nIDEvent ) ) 
		{
			// error !!!
			res =  -1;
		};

		m_uiTimerId =0;
		m_hwnd = 0;
		m_uElapse = 0;
		m_dwLastTickTime = 0;
		m_nIDEvent = 0;
		return res;
	};


	inline UINT  getTimerInterval() const { return m_uElapse; };
	inline bool  isStarted() const { return m_uiTimerId > 0;  };

private:

	void  timerProc(HWND hwnd,	UINT uMsg,  DWORD dwTime) 
	{
		//__try {
		
			DWORD dwDelta;
			if(m_dwLastTickTime == 0) 
			{
				dwDelta = 0;
			}
			else
			{
				dwDelta = dwTime - m_dwLastTickTime;
			}

			onTick( hwnd, uMsg,  dwTime, dwDelta );
			m_dwLastTickTime = dwTime;
			
		//}		__except(1) {		};
	};


	static VOID  CALLBACK   WINAPI_TIMERPROC (HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) 
	{
		CaptureTimer* pit = (CaptureTimer*)idEvent;

		//__try {
			pit->timerProc(  hwnd, uMsg,   dwTime);
		//} __except(1) {
			//* warn !!!
			//throw std::runtime_error("Timer error");
		//};
	};

	UINT_PTR m_uiTimerId;
	UINT m_uElapse;
	HWND m_hwnd;
	DWORD m_dwLastTickTime;
	UINT_PTR m_nIDEvent;

};
//  end class


/*
template <typename T, unsigned int _SIZE>
class Array {
public:
Array() { memset(m_arr, 0, sizeof(m_arr) );  };
~Array(){};

void clear()
{
for(size_t c=0; c<_SIZE; c++) m_arr[c].setzero();
}

unsigned int size() const { return _SIZE; };

T& operator [] (unsigned int indx)throw()
{
if(indx>=_SIZE) { throw std::runtime_error("invalid index"); };
return m_arr[indx];
}


void add(const T& val) throw() {
for(size_t c=0; c<_SIZE;c++)
{
if( m_arr[c].empty() )
{
m_arr[c] = val;
return ;
}
}
throw std::runtime_error("full");
};

bool erase(const T& val ) throw() {
bool bfound = false;
for(size_t c=0; c<_SIZE; c++)
{
if( m_arr[c] == val )
{
m_arr[c].setzero();
bfound = true;
};
}
return bfound;
};

private:
T m_arr[_SIZE];
};
*/


//!  базовое win-приложение для вывода графики .
class Appl3D  {
public:
	          Appl3D();
	virtual  ~Appl3D();


virtual HRESULT run() =0;
virtual HRESULT shutDown(int nExitCode) =0;
virtual HRESULT finalize() = 0;


inline float getTime() const { return m_timeData.m_fCurrentTime;  };
inline float getDeltaTime() const { return m_timeData.m_fDeltaTime;  };

virtual uint32_t getFps() const { return  m_fpsMonData.nCapturedFps; }; 

inline HWND  getWindowHandle() const { return m_hwnd; };
inline uint32_t getWindowClientWidth() const { return m_windowinfo.rcClient.right-m_windowinfo.rcClient.left; };
inline uint32_t getWindowClientHeight() const { return m_windowinfo.rcClient.bottom-m_windowinfo.rcClient.top; };


inline POINT getPointCursorPosOnWindow() const  { return m_pntCursorPos; };

protected:

virtual APPL_3D_INIT_DATA* getAppl3dInitData() = 0;
virtual HRESULT doBeginFrameDraw();
virtual HRESULT doHandleResizeWindow(int nNewWidth, int nNewHeight) = 0;

HRESULT keybMsgProc(const unsigned int nvkey, bool bDown );
HRESULT mouseMsgProc(POINT pnt);
HRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* pbNeedProcessAgain );


	HWND        m_hwnd ;
	WINDOWINFO  m_windowinfo;
	POINT       m_pntCursorPos;
	BOOL  m_bShutDownFlag;  ///< флаг - команда выхода
	TimeData    m_timeData;
	CaptureTimer  m_CaptureTimer;
	FpsMonData    m_fpsMonData;
	PerfomanceMonData     m_perfMonData;
	FrameDrawTimeMonData  m_frameDrawTimeMonData;



};

//-------------------------------------------------------------------------

    } // end ns winappl

  } // end ns system

} // end ns gb

#endif
// end file