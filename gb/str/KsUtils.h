/*! \file  KsUtils.h
 * \brief Разнообразные классы , типы для разных задач 
 * \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 * \author Reviewer/imported by: kvakvs (kvakvs@yandex.ru)
 */
#pragma once

#include <gb/str/KsDefines.h>
#include <gb/base/Types.h>

#include <windows.h>

#include <exception>
#include <stdexcept>


#pragma warning (push)
#pragma warning (disable : 4290)
#pragma warning (disable : 4996)

namespace gb {
	namespace util {


#ifdef _WIN32

/** \brief Получение точного текущего времени.  */
float getCurrHeightPrecTime() ;

/** \brief  Вычисление текущей позиции курсора на окне по данному хэндлу */
int32_t getCursorWindowPosition(HWND hwnd, POINT* pout) ;

#endif // #ifdef _WIN32




#if 0



/** \brief Класс для вызова инициализирующей  и финальной  функций  в cpp-файле. <br>
\code
ПРИМЕР ИСПОЛЬЗОВАНИЯ:

bool   Initialize(void* pUserData);
bool   Finalize(void* pUserData); 

bool   Initialize(void* pUserData) {
static bool sbFirstCall = true;
if(!sbFirstCall) return true;
sbFirstCall = false;
// ... initialization code

return true;
}

bool   Finalize(void* pUserData) {
static bool sbFirstCall = true;
if(!sbFirstCall) return true;
sbFirstCall = false;
// ... finalization code

return true;
}

SourceInit  __SourceInit( Initialize, Finalize, NULL );

int32_t _tmain(int32_t argc, _TCHAR* argv[]) {
return 0;
}

\endcode
*/


class SourceInit {
public:
   /** \brief Тип обратный вызов инициализирующая функция.   */
   typedef bool (*TFunc_SourceInitialize) (void* pUserData);
   /** \brief Тип обратный вызов финализирующая функция.   */
   typedef bool (*TFunc_SourceFinalize)   (void* pUserData);




	/** funcInit - будет вызвана до входа в main. 
	funcFinal - будет вызвана после выхода из main. 
	pUserData - свой указатель или NULL если не нужен.  */
	SourceInit(TFunc_SourceInitialize funcInit, TFunc_SourceFinalize funcFinal, void* pUserData ) ;
	~SourceInit() ;

private:
	void*    m_pUserData; 
	TFunc_SourceInitialize    m_Func_SourceInitialize; 
	TFunc_SourceFinalize      m_Func_SourceFinalize;
};
// end SourceInit class



/** \brief Класс значений (минимум, максимум, среднее, общее и счётчик) */
class TimeHandleInfo {
public:
	float fMin;
	float fMax;
	float fAver;
	float fTotal;
	uint32_t uiCount;

	TimeHandleInfo() { setzero();  }

	inline void setzero() { fMin=fMin=fAver=fTotal=0.0f; uiCount=0;   }
};




/**  \brief Класс Измеряет промежутки времени  */
class DeltaTimeHandler {
public:

	/** \brief Получить текуще значение времени <br>
	pnfreq - Опционально значение для QueryPerformanceFrequency или NULL для его вычисления в функции.  */
	static float Current(_in_opt LARGE_INTEGER* pnfreq = NULL ) ;

	DeltaTimeHandler() { m_fLastTime = 0.0f; Reset();  }
	virtual   ~DeltaTimeHandler() {}


	/** \brief Главный метод измерения дельты времени с момента последнего вызова  этого метода. <br> 
	Возвращает дельту с момента последнего вызова.  Для сброса использовать ResetOnTimer() . <br>
	\param
	pfCurrTime - [in] Ранее полученое текущее время или NULL если требуется самостоятельное полечение.
	pfOutCurrTime - [out] опциональный параметр. если нужно получить текущее время или NULL если не нужен.  */
	float Tick(_in_opt float* pfInputCurrTime=NULL,  _out_opt float* pfOutCurrTime=NULL) ;

	/** \brief Сброс по таймеру по  данному интервалу таймера (в миллисекундах) */
	void CaptureOnTimer(int32_t itimerInterval, _out_opt TimeHandleInfo* pOutHi = NULL) ;

	void Reset() ;

	inline float GetMinDelta()  const { return m_fMinDelta; }
	inline float GetMaxDelta()  const { return m_fMaxDelta; }
	inline float GetAverDelta() const { return m_fTotalDelta / (float)m_uiCountOnTick ; }
	inline float GetLastDelta() const { return m_lastResDelta; }
	inline float GetTotalDelta() const { return m_fTotalDelta; }
	inline UINT  GetCountOnTick() const  { return m_uiCountOnTick; }


	const char* tostr() const ;

	void print();

private:
	float m_fLastTime;
	float m_lastResDelta;

	float m_fMinDelta;
	float m_fMaxDelta;

	float m_fTotalDelta;

	UINT  m_uiCountOnTick;

	bool m_bFirstCall;	
};
// end class





/** \brief  Класс для  измерения времени между действиями. */
class ElapsedTimeCapture {
public:
	class ElTmCaptInfo {
	public:
		float fMin;
		float fMax;
		float fAver;

		uint32_t uiCountBegin;
		uint32_t uiCountEnd;

		ElTmCaptInfo() { setzero();  }

		inline void setzero() {  fMin= fMax = fAver=0.0f;   uiCountBegin=uiCountEnd=0;   }

		inline void print() {
			printf(" fMin = %f\n fMax = %f\n fAver = %f\n  uiCountBegin = %u \n uiCountEnd = %u", 
				fMin, fMax, fAver, uiCountBegin, uiCountEnd );
		}
	}



	ElapsedTimeCapture() { m_bBegined = false;  Reset() ;  }
	virtual ~ElapsedTimeCapture() {}

	/** \brief Получить время последнего вызова метода Begin */
	inline float GetLastBeginedTime() const { return m_fBegin; }

	/** \brief Начать действие.  После действия вызвать End . <br>
	В параметрах: <br>
	pfInpCurrTime [in] - текущее время  или NULL если требуется самостоятельное получение. <br>  
	pfOutCurrTime  [out] - можно передать указатель для получения текущего времени или NULL если не нужен. <br>
	*/
	void  Begin( _in_opt  float* pfInpCurrTime = NULL, _out_opt float* pfOutCurrTime = NULL) ;

	/** \brief Завершить действие.  Сначала вызвать Begin.  
	Возвращает результат время между Begin и End.  <br>
	pfInpCurrTime [in] - текущее время  или NULL если требуется самостоятельное получение. <br>  
	pfOutCurrTime  [out] - можно передать указатель для получения 
	текущего времени или NULL если не нужен. <br> */
	float End(_in_opt float* pfInpCurrTime = NULL, float* pfOutCurrTime = NULL) ;

	/** \brief Был ли вызван Begin и не вызван End , то есть запущен ли захват.  */
	inline bool isBegined() const {   return m_bBegined;  }

	inline float GetMinValue() const { return m_fMin ; }
	inline float GetMaxValue() const { return m_fMax ; }
	inline float GetTotalValue() const { return m_fTotal ; }
	inline float GetAverValue() const { return m_fTotal / (float)m_uCountBeginEnd ; }

	/** \brief Сброс по таймеру по  данному интервалу таймера (в миллисекундах) */
	void CaptureOnTimer(_in int32_t itimerInterval, 
		_out_opt TimeHandleInfo* pOutHi = NULL, 
		_out_opt ElTmCaptInfo* pOutEci = NULL) ;

	void Reset() ;

	void print() ;


private:

	float m_fMin;
	float m_fMax;
	float m_fTotal;
	float m_fBegin;
	bool m_bBegined;

	uint32_t m_uCountBeginEnd;
	uint32_t m_uCountBegin ;
	uint32_t m_uCountEnd;
	bool m_bFirstCall;
};
// end class

#endif //0


	} // namespace util
} // namespace gb
 
#pragma warning (pop)
