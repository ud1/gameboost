/** \file RenderTargetStack.h 
 \brief ���� �������������� ��� �������


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

//! \brief �������� ������������ �� d3d9. ����� ��������� � ������� ��� d3d9
namespace stack {

//-------------------------------------------------------------------------


	//! \brief ������ ������� ����� ��� RenderTargetStack
#define GB_D3D9_RENDERTARGETSTACK_MAX_LEN  16

//! \brief ���� �������������� ��� ���������� d3d9 
class RenderTargetStack {
public:
	  //! \brief ����� �����.
      class StackItem {
	  public:
               IDirect3DSurface9*  pExternalSet; ///< ������������ �� ���.
	           IDirect3DSurface9*  pInterfFromDevice; ///< ��������� �� �������. ������ ���� �������.
      };

  RenderTargetStack() 
  { 
	  m_stackpos=0-1; memset( m_arr, 0, sizeof(m_arr) ); 
  };

//! \brief ���� ���� ?
bool empty() const { return  m_stackpos < 0; };
//! \brief ����  ��� ������� �������� ?
bool full()  const { return  m_stackpos >=GB_D3D9_RENDERTARGETSTACK_MAX_LEN-1;  };
//! \brief  �������� ������� ������ ����� 
int  size()  const { return  m_stackpos + 1; };
//! \brief �������� ���� .
void clear() ;

/** \brief ���������� ����������� ��� ������� ���������. 
����������� ������ ���� �������  � ������ rendertarget */
HRESULT set_current(IDirect3DSurface9* prt, IDirect3DDevice9* pdevice) ;

/** \brief �������� ������� �����������  (������� ������������). */ 
HRESULT get_current(IDirect3DSurface9** ppOut , IDirect3DDevice9* pdevice);

//! \brief  �������� ������� ���������� (������� ������������ ) � ����. 
HRESULT push(IDirect3DDevice9* pdevice) ;
//! \brief  ������������ ������� ���������� (������� ������������ ). 
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