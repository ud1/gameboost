// OK !

#if ( defined(GB_D3D9) && defined(WIN32) )

#include <gb/graphics/d3d9/stack/rendertargetstack.h>
#include <gb/macro.h>

namespace gb {
namespace graphics {
namespace d3d9 {
namespace stack {


//=========================================================================
void RenderTargetStack::clear() 
{
   for(int c=0; c<GB_D3D9_RENDERTARGETSTACK_MAX_LEN; c++)
   {
	   
     GB_SAFE_REL( m_arr[c].pInterfFromDevice );
      m_arr[c].pExternalSet = NULL;
   };
 m_stackpos = 0-1;
};
 
//=========================================================================
HRESULT RenderTargetStack::set_current(IDirect3DSurface9* prt, 
									   IDirect3DDevice9* pdevice)
{
  HRESULT hr =0;

  if(empty() ) 
	  return E_FAIL;

  if(prt == NULL) 
	  return E_FAIL;

  m_arr[m_stackpos].pExternalSet = prt;

   if( m_arr[m_stackpos].pExternalSet )
   {
      hr |= pdevice->SetRenderTarget( 0, prt );
        if FAILED(hr)
        {
           // error
	       m_arr[m_stackpos].pExternalSet = NULL;
	       return hr;
        };
   
   };

  return hr;
};

//=========================================================================
HRESULT RenderTargetStack::get_current(IDirect3DSurface9** ppOut , IDirect3DDevice9* pdevice) 
{  
	HRESULT hr =0;
	 *ppOut = NULL;

 if( empty() ) 
 { 
	 //throw std::runtime_error("Stack empty");  
	 return E_FAIL;
 }; 

 // �������� ������� �� ������������ �� ���
  if(  m_arr[m_stackpos].pExternalSet )
  {
   *ppOut = m_arr[m_stackpos].pExternalSet;
   return hr;
  };

  //  �������� �� ������������ �� �������
  if( m_arr[m_stackpos].pInterfFromDevice )
  {
	  // ���������� ���
   *ppOut = m_arr[m_stackpos].pInterfFromDevice;
   return hr;
  }
  else
  {
    // ����� �� ������� ���� ..������ �� �������
	  hr |= pdevice->GetRenderTarget( 0 , &m_arr[m_stackpos].pInterfFromDevice );
	  if FAILED(hr)
	  {
	   // error
	   m_arr[m_stackpos].pInterfFromDevice = NULL;
	   return hr;
	  };

   *ppOut = m_arr[m_stackpos].pInterfFromDevice;
  
  };


  return  hr;
};

//================================================
HRESULT RenderTargetStack::push(IDirect3DDevice9* pdevice) 
{
	HRESULT hr =0;

   if( full() ) 
   {  
     #ifdef _DEBUG   
	  GB_MBOX("Rendertarget stack full");
     #endif	   
	  // throw std::runtime_error("Rendertarget stack  full"); 
	  return E_FAIL; 
   }; 
 
 

  if( size() > 0 )
  {
   // � ����� ��� ���� ��������
	  // �������� ������� ������� � �������
   m_arr[m_stackpos+1].pExternalSet = m_arr[m_stackpos].pExternalSet;
  
  }
  else
  {
    // � ����� �� ���������. ������ �������� �������
	  m_arr[m_stackpos+1].pExternalSet = NULL;

  };

   m_stackpos++; // inc counter

   // get device render target
   m_arr[m_stackpos].pInterfFromDevice = NULL;
   hr |= pdevice->GetRenderTarget( 0 , &m_arr[m_stackpos].pInterfFromDevice );

 
  return hr;
};
 
//=========================================================================
HRESULT RenderTargetStack::pop(IDirect3DDevice9* pdevice) {
  HRESULT hr =0;

   if (empty() ) { 
	   // throw std::runtime_error("Stack empty"); 
	   return S_FALSE;
   };


   // �������� �������
  m_arr[m_stackpos].pExternalSet = NULL;
  // ������� ���������
   if(m_arr[m_stackpos].pInterfFromDevice)
   {
	   IDirect3DSurface9* ps = m_arr[m_stackpos].pInterfFromDevice;
	   
    GB_SAFE_EXC_RELEASE(  ps );
    m_arr[m_stackpos].pInterfFromDevice = NULL;
   };

 // ���������
   m_stackpos--;

   // �������������� �������� ���� ����
   if( !empty() )
   {
     if( m_arr[m_stackpos].pExternalSet )
	 {
	  hr |=  pdevice->SetRenderTarget( 0, m_arr[m_stackpos].pExternalSet );
	 }
	 else
	 {
	     // ������������� ����� ���. ������ ��������� ���� ����
		 if( m_arr[m_stackpos].pInterfFromDevice )
		 {
		  hr |=  pdevice->SetRenderTarget( 0, m_arr[m_stackpos].pInterfFromDevice );
		 };
		 
	 };
   
   }
   else
   {
    // �����.. ������ �� ������
   
   };
 
  return hr;
};




} // end ns
} // end ns
} // end ns
} // end ns


#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file