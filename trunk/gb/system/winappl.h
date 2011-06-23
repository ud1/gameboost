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

#ifdef WIN32


#pragma once
#define __WINAPPL_H__

#include <gb/config.h>
#include <gb/base/Types.h>

#include <gb/fmath/fmath.h>

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


//!  \brief Данные инициализации для Appl3D. Базовые. 
class APPL_3D_INIT_DATA {
public:

	//! \brief Цвет очистки устройства.
	struct CLEARCOLOR
	{
		float red; 
		float green; 
		float blue;
	};

	//! \brief базовые обратные вызовы. Общие для всех приложений использующих разные граф-API
	struct BASECALLBACKDATA 
	{
		void* pUserParam; ///< Пользовательский указатель для функций обратного вызова (функции ниже). 

	typedef HRESULT (__cdecl *TFuncOnMessage)(void* pUserParam, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* pbNeedProcessAgain );
	typedef HRESULT (__cdecl *TFuncOnKeyboard)(void* pUserParam, int nVirtualKey, bool bKeyDown);
	typedef HRESULT (__cdecl *TFuncOnMouse)(void* pUserParam, POINT pntMouseCoord );

	typedef HRESULT (__cdecl *TFuncOnResize)(void* pUserParam, int nNewWidth, int nNewHeoght);

	TFuncOnMessage    funcOnMessage;
	TFuncOnKeyboard   funcOnKeyboard;
	TFuncOnMouse      funcOnMouse;

	TFuncOnResize     funcOnResize;


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

//! \brief Получить точное текущее время
inline  float getCurrSysHeightPrecTime() 
{
	LARGE_INTEGER tm, freq;   
	QueryPerformanceCounter(&tm);
	QueryPerformanceFrequency(&freq);
	return   (   ( (float)tm.QuadPart ) / ( (float)freq.QuadPart )   );
};


//! \brief Сборка для хранения данных для мониторинга производительности приложения
class  PerfomanceMonData {
public:

	UINT nFrameDrawCount;
	std::string str;

	PerfomanceMonData() { nFrameDrawCount=0; };
};
 

//! \brief  Сборка для хранения данных для мониторинга FPS
class FpsMonData {
public:

	uint32_t nCapturedFps;
	uint32_t nCountFrames;
	std::string str;

	//! \brief Захватить по тику таймера. В параметре nIntervalMs - интервал таймера в мс
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
	}

};


//!  \brief Класс для мониторинга времени отрисовки кадра 
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

	//! \brief Сигнал о начале отрисовки кадра
	void beginFrameDraw() 
	{
		m_fCurrentBegin = getCurrSysHeightPrecTime();

		m_bIsBeginCall = TRUE;

	};

	//! \brief Сигнал об окончании отрисовки кадра
	void endFrameDraw()
	{
		m_fLastTime = getCurrSysHeightPrecTime() - m_fCurrentBegin;
		if (m_fLastTime < 0.0f) m_fLastTime = 0.0f;

		m_fTotal += m_fLastTime;
		m_nCount++;

		m_bIsBeginCall = FALSE;
	};

	//! \brief Захватить по тику таймера. В параметре nIntervalMs - интервал таймера в мс
	void capture(unsigned int nIntervalMs=1000)
	{
		m_fCaptured = ( m_fTotal / (float)m_nCount ) ;  

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

	//! \brief обнулить все поля.  Сбросить.
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


//! \brief Сборка для хранения временнЫх значений
class TimeData {
public:
	float m_fCurrentTime;
	float m_fDeltaTime;

	TimeData() { m_fCurrentTime=m_fDeltaTime=0.0f; };
};


//! \brief  Таймер для захвата данных мониторинга
class CaptureTimer {
private:
	FpsMonData* m_fpsMonData;
	FrameDrawTimeMonData*  m_frDrawTimeMonData;


public:
	//! \brief В конструкторе передать адреса структур для захвата по тику таймера
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

	//! \brief СОбытие тик таймера
	virtual void onTick(HWND hwnd, UINT uMsg, DWORD dwTime, DWORD dwDelta) 
	{
		m_fpsMonData->capture();
		//printf("%s \n" , m_fpsMonData->str.c_str() );
		m_frDrawTimeMonData->capture();
		//printf("%s \n" , m_frDrawTimeMonData->m_str.c_str() );

	};

	//! \brief Запустить таймер. В параметрах: хэндл окна и интервал в миллисекундах
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


	//! \brief Остановить таймер
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

	//! \brief Получить интевал таймера
	inline UINT  getTimerInterval() const { return m_uElapse; };
	//! \brief Запущен ли таймер
	inline bool  isStarted() const { return m_uiTimerId > 0;  };

private:

	//! \brief Событие  тик таймера
	void  timerProc(HWND hwnd,	UINT uMsg,  DWORD dwTime) 
	{
		
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
 
	};

	//! \brief ???????
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

 

//! \brief  базовое windows-приложение для вывода графики .
class Appl3D  {
public:
	          Appl3D();
	virtual  ~Appl3D();


//! \brief   запуск главного цикла. Вызывается после успешной инициализации
virtual HRESULT run() =0;
//! \brief   Принудительный останов приложения.
virtual HRESULT shutDown(int nExitCode) =0;
//! \brief   Завершение УБРАТЬ !!!!
virtual HRESULT finalize() = 0;


//! \brief   Получить текущее время для выполнения отрисовки, анимации и т.д.
inline float getTime() const { return m_timeData.m_fCurrentTime;  }
//! \brief   Получить задержку между предидущим кадром.
inline float getDeltaTime() const { return m_timeData.m_fDeltaTime;  }
//! \brief   Получить текущее захваченое значение FPS
virtual uint32_t getFps() const { return  m_fpsMonData.nCapturedFps; } 
//! \brief   Получить хэндл окна отрисовки
inline HWND  getWindowHandle() const { return m_hwnd; }

//! \brief   Получить ширину клиентской области окна
inline uint32_t getWindowClientWidth() const  { return m_windowinfo.rcClient.right-m_windowinfo.rcClient.left; }
//! \brief   Получить высоту клиентской области окна
inline uint32_t getWindowClientHeight() const { return m_windowinfo.rcClient.bottom-m_windowinfo.rcClient.top; }

//! \brief   Получить координату курсора мыши на окне отрисовки
inline POINT getPointCursorPosOnWindow() const  { return m_pntCursorPos; }

//! \brief  Установить новый цвет очистки
void setClearColor(float r, float g, float b)
{
	APPL_3D_INIT_DATA* pinitdata = getAppl3dInitData(); 
	  pinitdata->clearColor.red=r;
	  pinitdata->clearColor.green=g;
	  pinitdata->clearColor.blue=b;
}

protected:

//! \brief Новая процедура (общая) обработки сообщений 
static LRESULT WINAPI  newMainWindowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
 	HRESULT hr =0;
	static Appl3D* pAppl3D = NULL;

	// begin (запрос обработки сообщения)
	//
	{

	if(pAppl3D)
	{
	   BOOL bProcessAgain = TRUE;
  
	    const APPL_3D_INIT_DATA* pApidata = pAppl3D->getAppl3dInitData();
		if( pApidata->basecallback.funcOnMessage )
		{
			  hr |= pApidata->basecallback.funcOnMessage (
			      pApidata->basecallback.pUserParam,
			      hWnd,  msg,  wParam,  lParam, &bProcessAgain  );

		} 

 
	if(!bProcessAgain) return 0;
	} // if if(pAppl3D)

    }// end (запрос обработки сообщения)

	

//  msg handle

	unsigned int vkey = 0;
 
	int width  = 0;
	int height = 0;
	
	switch( msg )
	{

	case WM_CREATE:
		{
	    LPCREATESTRUCT pcrstr = NULL;
		pcrstr  = (LPCREATESTRUCT)lParam;
		pAppl3D = (Appl3D*)pcrstr->lpCreateParams;
		}

		break;

	case WM_CLOSE:
 
		break;

	case WM_QUIT:
 
		break;

	case WM_MOVE:
 
		break;

	case WM_ACTIVATE:
 
		break;

	case WM_SIZE: 
		assert(pAppl3D);
		height = HIWORD(lParam);      
		width  = LOWORD(lParam);
		hr |= pAppl3D->doHandleResizeWindow( width , height );

		break;

	case WM_ENABLE:
 
		break;


	case WM_DESTROY:
		assert(pAppl3D);
		pAppl3D->m_bShutDownFlag= TRUE;

		assert(false && "INSERT CODE");
		//hr |= pAppl3D->destroyDevice();

		Sleep(10);

		PostQuitMessage( 0 );
		return 0;


	case WM_HOTKEY:
 
		break;


	case WM_KEYDOWN:
		assert(pAppl3D);
		vkey = (unsigned int)wParam;
		hr |= pAppl3D->keybMsgProc(vkey, true );
		if(pAppl3D->m_bShutDownFlag)
		{
			Sleep(10);
			PostQuitMessage( 0 ); 
		}

		break;

	case WM_KEYUP:
		assert(pAppl3D);
		vkey = (unsigned int)wParam;
		hr |= pAppl3D->keybMsgProc(vkey, false );

		break;

	case WM_CHAR:
 
		break;



   //  case WM_KEYFIRST: 

   //	  break;

	case WM_KEYLAST: 
 
		break;

	case WM_SYSKEYDOWN :
 
		break;

	case WM_SYSKEYUP : 
 
		break;
 



	default:
		{
	 
		}


	}// switch

	return DefWindowProc( hWnd, msg, wParam, lParam );
};



//! \brief   Получить базовую структуру инициализации
virtual APPL_3D_INIT_DATA* getAppl3dInitData() = 0;

//! \brief  Выполнить подготовительные операции перед отрисовкой кадра
virtual HRESULT doBeginFrameDraw();
//! \brief   Обработать событие изменения размеров окна
virtual HRESULT doHandleResizeWindow(int nNewWidth, int nNewHeight) = 0;

//! \brief   Обработать событие клавиатуры (nvkey-код клавиши,  bDown-нажата или нет)
HRESULT keybMsgProc(const unsigned int nvkey, bool bDown );
//! \brief   Обработать событие мыши
HRESULT mouseMsgProc(POINT pnt);
 //! \brief   Обработать новое сообщение.
HRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* pbNeedProcessAgain );


	HWND        m_hwnd ;         ///<  хэндл окна отрисовки
	WINDOWINFO  m_windowinfo;    ///<  инфа окна отрисовки
	POINT       m_pntCursorPos;	 ///<  координата позиции курсора на окне

	BOOL  m_bShutDownFlag;    ///< флаг - команда выхода

	TimeData    m_timeData;	  ///<  хранит временнЫе параметры 

	CaptureTimer  m_CaptureTimer;     ///<  таймер захвата FPS
	FpsMonData    m_fpsMonData;	      ///<  хранит данные для мониторинга FPS
	PerfomanceMonData     m_perfMonData;    ///<  хранит данные для мониоринга скорости
	FrameDrawTimeMonData  m_frameDrawTimeMonData; ///<  хранит данные о времени выполнения обратного вызова отрисовки кадра


};

//-------------------------------------------------------------------------

    } // end namespace winappl

  } // end namespace system

} // end namespace gb

#endif // #ifdef WIN32
// end file