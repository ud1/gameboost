/** \file ViewportStack.h
 \brief 

  // OK !

  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/


#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once

#include <gb/Config.h>
#include <stack>
#include <gb/t/func.h>
#include "d3d9.h"

#include <assert.h>

namespace gb {

namespace graphics {

namespace d3d9 {

namespace stack {

//-------------------------------------------------------------------------


//* \brief Стек вьюпортов для устройства d3d9 .
class ViewPortStack {
public:
    ViewPortStack() { }

inline bool    empty() const { return m_stack.empty(); };
inline size_t  size() const  { return m_stack.size(); };

HRESULT push(IDirect3DDevice9* pdevice) {
	HRESULT hr =0;
	D3DVIEWPORT9 vp;
	hr |= pdevice->GetViewport(&vp);
	m_stack.push(vp);
	return hr;
};

HRESULT pop(IDirect3DDevice9* pdevice) {
	HRESULT hr =0;
	if( empty() ) return S_FALSE;
	D3DVIEWPORT9 vp = m_stack.top();
	hr |= pdevice->SetViewport(&vp);
	m_stack.pop();
	return hr;
};

const D3DVIEWPORT9* getTop() const 
{
	static const char CSTR_ERR [] = "Stack is empty";
	if(m_stack.empty() ) {
		throw_err(CSTR_ERR);
	};
	const D3DVIEWPORT9* res = &m_stack.top(  );
	return res;
};

HRESULT setTop(IDirect3DDevice9* pdevice ) 
{
	HRESULT hr =0;
	if( empty() ) 
	{ 
	  assert(false&&"Stack empty");
		return E_FAIL; 
	};

	D3DVIEWPORT9 vp;
	hr |= pdevice->GetViewport(&vp);
	if FAILED(hr) 
		return hr;

	m_stack.top() = vp;
	return hr;
};

void setTopPVal(const D3DVIEWPORT9* pViewport)   
{
	if( empty() ) 
	{
		throw_err("Viewport stack is empty");
	};
	m_stack.top() = *pViewport;
};

 
private:
  std::stack<D3DVIEWPORT9> m_stack;

  //! бросить исключение
  void throw_err(const char* msg) const
  {
	  throw std::runtime_error(msg);
  }

};
// end class

//-------------------------------------------------------------------------


} // end ns
} // end ns
} // end ns
} // end ns

#endif //#if ( defined(GB_D3D9) && defined(WIN32) )
// end file