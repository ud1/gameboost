

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma message ("KS777: GB_D3D9 COMMON.H  НЕ ДОДЕЛАН НИХЕРА !!!!  "  __FILE__)

#include <gb/graphics/d3d9/common.h>
#include <assert.h>

namespace gb       
{
namespace graphics 
{
namespace d3d9     
{
namespace common   
{
	
//======================================================================

struct SFuncOnCriticalDeviceEvent
{
  TFuncOnCriticalDeviceEvent func;
  void* pUserData;
};

// размер массива из SFuncOnCriticalDeviceEvent
#define ARRAY_ONCRITICALDEVICEEVENT_LEN  64
// массив зарегистрировавшихся.  STD-списки не подходят.
static 	SFuncOnCriticalDeviceEvent g_arr_onCriticalDeviceEvent[ARRAY_ONCRITICALDEVICEEVENT_LEN];
	
	
//! уведомление о критическом событии	
//////static TFuncOnCriticalDeviceEvent  g_funcOnCriticalDeviceEvent	 = NULL;
/////static void* g_pUserData_funcOnCriticalDeviceEvent = NULL;

//! хранит указатели на функции переключения режима.
struct SFuncGetSetHolder 
{
  TFuncGetFullScreenMode  funcGet;  
  TFuncSetFullScreenMode  funcSet;
  void* pUsedData;
};  
//* функции  переключения экранного режима
static SFuncGetSetHolder  g_FuncGetSetHolde;


//=============================================================================
//
//=============================================================================

//	

//====================================================================	
GB_D3D9_API HRESULT registerGlobalCriticalDeviceEventCallback (
	       TFuncOnCriticalDeviceEvent func,   void* pUserData )
{
  HRESULT hr =0;
  
  { //  BEGIN once code
   static bool stb_firstcall = true;
   if(stb_firstcall)
   {
    stb_firstcall=false;
	
	// set zero
	for(int c=0; c<ARRAY_ONCRITICALDEVICEEVENT_LEN; c++)
	{
	g_arr_onCriticalDeviceEvent[c].func=NULL;
	g_arr_onCriticalDeviceEvent[c].pUserData=NULL;	
	}
   }
  
  } // END once code
  
  // search first null
  int nIndex = -1; // < search result index
  for(int c=0; c<ARRAY_ONCRITICALDEVICEEVENT_LEN; c++)
  {
    if( NULL == g_arr_onCriticalDeviceEvent[c].func )
    {
      nIndex = c; // found
	  break;
    }
  
  }
  
  // check found
  if(nIndex < 0)
  {
  //#ifdef _DEBUG
  assert(false&&"ошибка регистрации обратного вызова");
   return E_FAIL;
  //#endif
  
  }
  
  // register
  g_arr_onCriticalDeviceEvent[nIndex].func = func;
  g_arr_onCriticalDeviceEvent[nIndex].pUserData = pUserData;
  
  
  
  
  /*
  if(g_funcOnCriticalDeviceEvent)
  {
   hr |= S_FALSE;
   
  #ifdef _DEBUG_
   GB_MBOX("ПО какой-то причине функция registerGlobalCriticalDeviceEventCallback  вызвана дважды")
  #endif
  
  }
  */
  

  assert(false);
  /*
  g_funcOnCriticalDeviceEvent = func;
  g_pUserData_funcOnCriticalDeviceEvent = pUserData;
  */
  

   return hr;
};


//=====================================================================
GB_D3D9_API HRESULT registerFuncFullScreenMode(TFuncGetFullScreenMode  funcGet,  
												TFuncSetFullScreenMode funcSet, 
												void* pUsedData)
{
  HRESULT hr =0;
  
  // проверить на уже зарегистрированые
  
 
  g_FuncGetSetHolde.funcGet = funcGet;
  g_FuncGetSetHolde.funcSet = funcSet;
  g_FuncGetSetHolde.pUsedData = pUsedData;

  return hr;
};
	
	
	
	
	
	
	
//======================================================================
	
} // end ns
} // end ns
} // end ns
} // end ns

#endif // #if
// end file