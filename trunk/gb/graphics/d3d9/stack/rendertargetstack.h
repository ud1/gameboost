/** \file RenderTargetStack.h 
 \brief Стэк рендертаргетов для девайса

 // OK !

  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once

#include <gb/Config.h>

#include "d3d9.h"


namespace gb {

namespace graphics {

namespace d3d9 {

//! \brief Дочернее пространство от d3d9. Стеки состояний и прочего для d3d9
namespace stack {

//-------------------------------------------------------------------------


	//! \brief размер массива стека для RenderTargetStack
#define GB_D3D9_RENDERTARGETSTACK_MAX_LEN  16

//! \brief Стек рендертаргетов для устройства d3d9 
class RenderTargetStack {
public:
	  //! \brief пункт стека.
      class StackItem {
	  public:
               IDirect3DSurface9*  pExternalSet; ///< установленое из вне.
	           IDirect3DSurface9*  pInterfFromDevice; ///< полученое из девайса. должно быть удалено.
      };

  RenderTargetStack() 
  { 
	  m_stackpos=0-1; memset( m_arr, 0, sizeof(m_arr) ); 
  };

//! \brief стек пуст ?
bool empty() const { return  m_stackpos < 0; };
//! \brief стек  под завязку заполнен ?
bool full()  const { return  m_stackpos >=GB_D3D9_RENDERTARGETSTACK_MAX_LEN-1;  };
//! \brief  получить текущий размер стека 
int  size()  const { return  m_stackpos + 1; };
//! \brief очистить стек .
void clear() ;

/** \brief Установить поверхность как текущую отрисовку. 
Поверхность должна быть создана  с флагом rendertarget */
HRESULT set_current(IDirect3DSurface9* prt, IDirect3DDevice9* pdevice) ;

/** \brief Получить текущую поверхность  (текущий рендертаргет). */ 
HRESULT get_current(IDirect3DSurface9** ppOut , IDirect3DDevice9* pdevice);

//! \brief  Положить текущую поврхность (текущий рендертаргет ) в стек. 
HRESULT push(IDirect3DDevice9* pdevice) ;
//! \brief  Восстановить текущую поврхность (текущий рендертаргет ). 
HRESULT pop(IDirect3DDevice9* pdevice) ;

private:

  int m_stackpos;
  StackItem m_arr[GB_D3D9_RENDERTARGETSTACK_MAX_LEN];

};
// end class


//-------------------------------------------------------------------------

} // end ns
} // end ns
} // end ns
} // end ns



#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
 // end file