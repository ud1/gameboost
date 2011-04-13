// OK !

#if ( defined(GB_D3D9) && defined(WIN32) )
 

#include <stdio.h>
#include <gb/macro.h>
#include <gb/graphics/d3d9/stack/StatesValueStack.h>
//#include "Z:\\CODE_EXPERIMENT\\dapplLibr\\dapplLibr\\source\\internal_headers\\StatesValueStack.h"

namespace gb {
namespace graphics {
namespace d3d9 {
namespace stack {

	//=====================================================


 
//=========================================================
HRESULT StatesValueStack::push(IDirect3DDevice9* pdevice, 
							   const D3DRENDERSTATETYPE* pStates, 
							   const int num)
{
 HRESULT hr =0;

	if(full() ) {
	 // FULL !
 
	  GB_MONPRINT("Error: states stack is full");
	 return E_FAIL;
	};


if(num >= GB_D3D9_STATES_ARR_LEN) {
 
  GB_MONPRINT(" big value ");
  hr |= E_FAIL;
   return hr;
};

__try 
{
  for(int c=0; c<num; c++)
  {
   const D3DRENDERSTATETYPE currstate = *(pStates + c);
   DWORD currval = 0-1;
   hr |= pdevice->GetRenderState( currstate , &currval );

   m_values[m_stackpos].states[c] = currstate; 
   m_values[m_stackpos].dwvalues[c] =  currval;


  }; // for
 } // try
__except(1) 
{
  hr |= E_FAIL;
   
};


  if FAILED(hr) return hr;  


// end

m_values[m_stackpos].nNumUsed = num;

m_stackpos++;

#pragma message(" опнбепхрэ йнд !!!!")
  return hr;
};


//=========================================================
HRESULT StatesValueStack::pop(IDirect3DDevice9* pdevice )
{
 HRESULT hr =0;

 if(empty() ) {
 
  GB_MONPRINT("stack is empty");
  return E_FAIL;
 };


 __try {

  for(int c=0; c< m_values[m_stackpos].nNumUsed; c++)
  {
   const D3DRENDERSTATETYPE currstate =  m_values[m_stackpos].states[c];
   DWORD currval = m_values[m_stackpos].dwvalues[c];
   hr |= pdevice->SetRenderState( currstate ,  currval );

   m_values[m_stackpos].states[c] = currstate; 
   m_values[m_stackpos].dwvalues[c] =  currval;


  }; // for

 } __except(1) 
 {
	 GB_MONPRINT("Exception: StatesValueStack pop");
  hr |= E_FAIL;
   
};

 // end
  m_values[m_stackpos].nNumUsed = 0;


  m_stackpos--;

  #pragma message(" опнбепхрэ йнд !!!!")
  return hr;
};



//===================================================
HRESULT StatesValueStack::getStates (IDirect3DDevice9* pdevice, 
									    DWORD* pOutDwords, 
									  const D3DRENDERSTATETYPE* pStates,
									  const int num) 
{
  HRESULT hr =0;

 D3DRENDERSTATETYPE currState;
   DWORD currval;

__try {
 for(int c=0;  c<num; c++)
 {
   currState = *(pStates + c);
   hr |= pdevice->GetRenderState(currState , &currval);
   *(pOutDwords + c) = currval;
     
 }

}
 __except(1) {
  hr |= E_FAIL;
  GB_MONPRINT("Exception: get stack values");
};


  return hr;
};

//===================================================
HRESULT StatesValueStack::setStates  (IDirect3DDevice9* pdevice, 
									  const DWORD* pdwValues,
									  const D3DRENDERSTATETYPE* pStates, 
									  const int num)
{
  HRESULT hr =0;

 
   D3DRENDERSTATETYPE currState;
   DWORD currval;

__try {

	for(int c=0; c<num; c++) 
	{
		currState = *(pStates + c);
		currval = *(pdwValues + c);
	  hr |= pdevice->SetRenderState(currState ,  currval);

	};

} 
	__except(1) //  __exc_mon
{
 hr |= E_FAIL;
 
   GB_MONPRINT("Except: set render states");
};


  return hr;
};


//=============================================
} } } } // end namespaces
 
#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file