/** \file StatesValueStack.h
 \brief Стек наборов состояний устройства.



  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586

  \todo можно переделать набор состояний не фиксированый размер , а динамический

  // OK !
*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once

#include <gb/Config.h>
#include "d3d9.h"

namespace gb {

namespace graphics {

namespace d3d9 {

namespace stack {

//-------------------------------------------------------------------------

//! \brief  размер набора  состояний
#define  GB_D3D9_STATES_ARR_LEN  32

//! \brief набор состояний для  стека
class StatesValue {
public:
   StatesValue() { nNumUsed=0; };

 int nNumUsed; ///< сколько использовано.

D3DRENDERSTATETYPE states[GB_D3D9_STATES_ARR_LEN];
DWORD dwvalues[GB_D3D9_STATES_ARR_LEN];


};
// end class



#define GB_D3D9_STATES_MAX_STACK_LEN 32


//! \brief Стек наборов состояний устройства.
class StatesValueStack {
public:
  StatesValueStack() { m_stackpos=0; };

 inline bool empty() const { return m_stackpos==0; };
 inline bool full() const { return  m_stackpos>=GB_D3D9_STATES_MAX_STACK_LEN-1; };

HRESULT push (IDirect3DDevice9* pdevice, const D3DRENDERSTATETYPE* pStates, const int num);
HRESULT pop  (IDirect3DDevice9* pdevice );

static HRESULT getStates  (IDirect3DDevice9* pdevice, DWORD* pOutDwords, const D3DRENDERSTATETYPE* pStates, const int num);
static HRESULT setStates  (IDirect3DDevice9* pdevice, const DWORD* pdwValues, const D3DRENDERSTATETYPE* pStates, const int num);


private:
  int m_stackpos;

 StatesValue   m_values[GB_D3D9_STATES_MAX_STACK_LEN];

};
// end class

 
//-------------------------------------------------------------------------

} // end ns
} // end ns
} // end ns
} // end ns

#endif   //#if ( defined(GB_D3D9) && defined(WIN32) )
// end file