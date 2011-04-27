/** \file
 \brief Класс для вывода функций инициализации и финализации в исходнике.
 

*/

#pragma once


namespace gb
{

namespace util
{


/** \brief Класс для вызова инициализирующей  и финальной функций  в cpp-файле. <br>
\code
ПРИМЕР ИСПОЛЬЗОВАНИЯ: и он же шаблон для копипасты.

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



}

}

// end file