﻿/** \file common.h
 \brief Общее для d3d9  
*
*  Для использования должен быть определён GB_D3D9
* 
* 
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/


#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once
#define __GB_D3D9_COMMON_H__

#include <gb/graphics/d3d9/d3d9.h>



namespace gb 
{
   namespace graphics 
   {
      namespace d3d9 
	  {
	     //! \brief Общее для d3d9
	     namespace common 
	     {

		 
		 
	  //! \brief Тип обратный вызов для регистрации критически важных событий устройства d3d9 
	  typedef HRESULT (__cdecl *TFuncOnCriticalDeviceEvent) (void* pUsedData);

	  
	  
	  /** \brief Зарегистрировать уведомление на потерю, сброс, удаление устройства d3d9
	  
	         \param  func -  функция, которая будет вызвана пл событию
		\param  pUserData - Пользовательский указатель (параметр для func) или NULL если не нужен.
		\return  S_OK - если успешно. Иначе E_FAIL 
	   */
	  GB_D3D9_API HRESULT registerGlobalCriticalDeviceEventCallback (
	       TFuncOnCriticalDeviceEvent func,  
		   void* pUserData	 
	  );
	  
	  
	  
	  
	  
	  
	     } // end ns common

      } // end ns d3d9

   } // end ns graphics

} // end ns gb

#endif // #if
// end file