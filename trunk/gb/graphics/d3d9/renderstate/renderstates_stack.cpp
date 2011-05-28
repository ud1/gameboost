

#include "renderstates_stack.h"

#pragma warning("!!!!!!!!!!  MAIN() !!!!!!!!!!!!! " __FILE__)
int main()
{
	return 0;
}

//=====================================================================================
bool StateStack::CheckAllEmpty() const 
{
  bool res = true;
 
  res &= m_stk_D3DRS_ZENABLE.empty();
  res &= m_stk_D3DRS_FILLMODE.empty();
  res &= m_stk_D3DRS_SHADEMODE.empty();
  res &= m_stk_D3DRS_ZWRITEENABLE.empty();
  res &= m_stk_D3DRS_ALPHATESTENABLE.empty();
  res &= m_stk_D3DRS_LASTPIXEL.empty();
  res &= m_stk_D3DRS_SRCBLEND.empty();
  res &= m_stk_D3DRS_DESTBLEND.empty();
  res &= m_stk_D3DRS_CULLMODE.empty();
  res &= m_stk_D3DRS_ZFUNC.empty();
  res &= m_stk_D3DRS_ALPHAREF.empty();
  res &= m_stk_D3DRS_ALPHAFUNC.empty();
  res &= m_stk_D3DRS_DITHERENABLE.empty();
  res &= m_stk_D3DRS_ALPHABLENDENABLE.empty();
  res &= m_stk_D3DRS_FOGENABLE.empty();
  res &= m_stk_D3DRS_SPECULARENABLE.empty();
  res &= m_stk_D3DRS_FOGCOLOR.empty();
  res &= m_stk_D3DRS_FOGTABLEMODE.empty();
  res &= m_stk_D3DRS_FOGSTART.empty();
  res &= m_stk_D3DRS_FOGEND.empty();
  res &= m_stk_D3DRS_FOGDENSITY.empty();
  res &= m_stk_D3DRS_RANGEFOGENABLE.empty();
  res &= m_stk_D3DRS_STENCILENABLE.empty();
  res &= m_stk_D3DRS_STENCILFAIL.empty();
  res &= m_stk_D3DRS_STENCILZFAIL.empty();
  res &= m_stk_D3DRS_STENCILPASS.empty();
  res &= m_stk_D3DRS_STENCILFUNC.empty();
  res &= m_stk_D3DRS_STENCILREF.empty();
  res &= m_stk_D3DRS_STENCILMASK.empty();
  res &= m_stk_D3DRS_STENCILWRITEMASK.empty();
  res &= m_stk_D3DRS_TEXTUREFACTOR.empty();
  res &= m_stk_D3DRS_WRAP0.empty();
  res &= m_stk_D3DRS_WRAP1.empty();
  res &= m_stk_D3DRS_WRAP2.empty();
  res &= m_stk_D3DRS_WRAP3.empty();
  res &= m_stk_D3DRS_WRAP4.empty();
  res &= m_stk_D3DRS_WRAP5.empty();
  res &= m_stk_D3DRS_WRAP6.empty();
  res &= m_stk_D3DRS_WRAP7.empty();
  res &= m_stk_D3DRS_CLIPPING.empty();
  res &= m_stk_D3DRS_LIGHTING.empty();
  res &= m_stk_D3DRS_AMBIENT.empty();
  res &= m_stk_D3DRS_FOGVERTEXMODE.empty();
  res &= m_stk_D3DRS_COLORVERTEX.empty();
  res &= m_stk_D3DRS_LOCALVIEWER.empty();
  res &= m_stk_D3DRS_NORMALIZENORMALS.empty();
  res &= m_stk_D3DRS_DIFFUSEMATERIALSOURCE.empty();
  res &= m_stk_D3DRS_SPECULARMATERIALSOURCE.empty();
  res &= m_stk_D3DRS_AMBIENTMATERIALSOURCE.empty();
  res &= m_stk_D3DRS_EMISSIVEMATERIALSOURCE.empty();
  res &= m_stk_D3DRS_VERTEXBLEND.empty();
  res &= m_stk_D3DRS_CLIPPLANEENABLE.empty();
  res &= m_stk_D3DRS_POINTSIZE.empty();
  res &= m_stk_D3DRS_POINTSIZE_MIN.empty();
  res &= m_stk_D3DRS_POINTSPRITEENABLE.empty();
  res &= m_stk_D3DRS_POINTSCALEENABLE.empty();
  res &= m_stk_D3DRS_POINTSCALE_A.empty();
  res &= m_stk_D3DRS_POINTSCALE_B.empty();
  res &= m_stk_D3DRS_POINTSCALE_C.empty();
  res &= m_stk_D3DRS_MULTISAMPLEANTIALIAS.empty();
  res &= m_stk_D3DRS_MULTISAMPLEMASK.empty();
  res &= m_stk_D3DRS_PATCHEDGESTYLE.empty();
  res &= m_stk_D3DRS_DEBUGMONITORTOKEN.empty();
  res &= m_stk_D3DRS_POINTSIZE_MAX.empty();
  res &= m_stk_D3DRS_INDEXEDVERTEXBLENDENABLE.empty();
  res &= m_stk_D3DRS_COLORWRITEENABLE.empty();
  res &= m_stk_D3DRS_TWEENFACTOR.empty();
  res &= m_stk_D3DRS_BLENDOP.empty();
  res &= m_stk_D3DRS_POSITIONDEGREE.empty();
  res &= m_stk_D3DRS_NORMALDEGREE.empty();
  res &= m_stk_D3DRS_SCISSORTESTENABLE.empty();
  res &= m_stk_D3DRS_SLOPESCALEDEPTHBIAS.empty();
  res &= m_stk_D3DRS_ANTIALIASEDLINEENABLE.empty();
  res &= m_stk_D3DRS_MINTESSELLATIONLEVEL.empty();
  res &= m_stk_D3DRS_MAXTESSELLATIONLEVEL.empty();
  res &= m_stk_D3DRS_ADAPTIVETESS_X.empty();
  res &= m_stk_D3DRS_ADAPTIVETESS_Y.empty();
  res &= m_stk_D3DRS_ADAPTIVETESS_Z.empty();
  res &= m_stk_D3DRS_ADAPTIVETESS_W.empty();
  res &= m_stk_D3DRS_ENABLEADAPTIVETESSELLATION.empty();
  res &= m_stk_D3DRS_TWOSIDEDSTENCILMODE.empty();
  res &= m_stk_D3DRS_CCW_STENCILFAIL.empty();
  res &= m_stk_D3DRS_CCW_STENCILZFAIL.empty();
  res &= m_stk_D3DRS_CCW_STENCILPASS.empty();
  res &= m_stk_D3DRS_CCW_STENCILFUNC.empty();
  res &= m_stk_D3DRS_COLORWRITEENABLE1.empty();
  res &= m_stk_D3DRS_COLORWRITEENABLE2.empty();
  res &= m_stk_D3DRS_COLORWRITEENABLE3.empty();
  res &= m_stk_D3DRS_BLENDFACTOR.empty();
  res &= m_stk_D3DRS_SRGBWRITEENABLE.empty();
  res &= m_stk_D3DRS_DEPTHBIAS.empty();
  res &= m_stk_D3DRS_WRAP8.empty();
  res &= m_stk_D3DRS_WRAP9.empty();
  res &= m_stk_D3DRS_WRAP10.empty();
  res &= m_stk_D3DRS_WRAP11.empty();
  res &= m_stk_D3DRS_WRAP12.empty();
  res &= m_stk_D3DRS_WRAP13.empty();
  res &= m_stk_D3DRS_WRAP14.empty();
  res &= m_stk_D3DRS_WRAP15.empty();
  res &= m_stk_D3DRS_SEPARATEALPHABLENDENABLE.empty();
  res &= m_stk_D3DRS_SRCBLENDALPHA.empty();
  res &= m_stk_D3DRS_DESTBLENDALPHA.empty();
  res &= m_stk_D3DRS_BLENDOPALPHA.empty();

 
  return res;
}

//=======================================================================
HRESULT StateStack::PushState(IDirect3DDevice9* pdevice, D3DRENDERSTATETYPE state) {
  HRESULT hr =0;

  try 
  {

  DWORD dwst = 0;
  hr|=pdevice->GetRenderState( state , &dwst);
  if FAILED(hr) {  return hr; };

  switch(state) 
  {
  
  case D3DRS_ZENABLE: {   m_stk_D3DRS_ZENABLE.push(dwst);  } break;
  case D3DRS_FILLMODE: {   m_stk_D3DRS_FILLMODE.push(dwst);  } break;  
  case D3DRS_SHADEMODE: {   m_stk_D3DRS_SHADEMODE.push(dwst);  } break;
  case D3DRS_ZWRITEENABLE: {   m_stk_D3DRS_ZWRITEENABLE.push(dwst);  } break;
  case D3DRS_ALPHATESTENABLE: {   m_stk_D3DRS_ALPHATESTENABLE.push(dwst);  } break;   
  case D3DRS_LASTPIXEL: {   m_stk_D3DRS_LASTPIXEL.push(dwst);  } break;
  case D3DRS_SRCBLEND: {   m_stk_D3DRS_SRCBLEND.push(dwst);  } break;
  case D3DRS_DESTBLEND: {   m_stk_D3DRS_DESTBLEND.push(dwst);  } break; 

  case D3DRS_CULLMODE: {   m_stk_D3DRS_CULLMODE.push(dwst);  } break;
  case D3DRS_ZFUNC: {   m_stk_D3DRS_ZFUNC.push(dwst);  } break;
  case D3DRS_ALPHAREF: {   m_stk_D3DRS_ALPHAREF.push(dwst);  } break;  
  case D3DRS_ALPHAFUNC: {   m_stk_D3DRS_ALPHAFUNC.push(dwst);  } break;
  case D3DRS_DITHERENABLE: {   m_stk_D3DRS_DITHERENABLE.push(dwst);  } break;
  case D3DRS_ALPHABLENDENABLE: {   m_stk_D3DRS_ALPHABLENDENABLE.push(dwst);  } break;  

  case D3DRS_FOGENABLE: {   m_stk_D3DRS_FOGENABLE.push(dwst);  } break;
  case D3DRS_SPECULARENABLE: {   m_stk_D3DRS_SPECULARENABLE.push(dwst);  } break;
  case D3DRS_FOGCOLOR: {   m_stk_D3DRS_FOGCOLOR.push(dwst);  } break;  
  case D3DRS_FOGTABLEMODE: {   m_stk_D3DRS_FOGTABLEMODE.push(dwst);  } break;
  case D3DRS_FOGSTART: {   m_stk_D3DRS_FOGSTART.push(dwst);  } break;
  case D3DRS_FOGEND: {   m_stk_D3DRS_FOGEND.push(dwst);  } break;  
  case D3DRS_FOGDENSITY: {   m_stk_D3DRS_FOGDENSITY.push(dwst);  } break;
  case D3DRS_RANGEFOGENABLE: {   m_stk_D3DRS_RANGEFOGENABLE.push(dwst);  } break;
  case D3DRS_STENCILENABLE: {   m_stk_D3DRS_STENCILENABLE.push(dwst);  } break;  
  case D3DRS_STENCILFAIL: {   m_stk_D3DRS_STENCILFAIL.push(dwst);  } break;
  case D3DRS_STENCILZFAIL: {   m_stk_D3DRS_STENCILZFAIL.push(dwst);  } break;
  case D3DRS_STENCILPASS: {   m_stk_D3DRS_STENCILPASS.push(dwst);  } break;    
  
  case D3DRS_STENCILFUNC: {   m_stk_D3DRS_STENCILFUNC.push(dwst);  } break;
  case D3DRS_STENCILREF: {   m_stk_D3DRS_STENCILREF.push(dwst);  } break;
  case D3DRS_STENCILMASK: {   m_stk_D3DRS_STENCILMASK.push(dwst);  } break;  
  case D3DRS_STENCILWRITEMASK: {   m_stk_D3DRS_STENCILWRITEMASK.push(dwst);  } break;
  case D3DRS_TEXTUREFACTOR: {   m_stk_D3DRS_TEXTUREFACTOR.push(dwst);  } break;

  case D3DRS_WRAP0: {   m_stk_D3DRS_WRAP0.push(dwst);  } break;    
  case D3DRS_WRAP1: {   m_stk_D3DRS_WRAP1.push(dwst);  } break;
  case D3DRS_WRAP2: {   m_stk_D3DRS_WRAP2.push(dwst);  } break;
  case D3DRS_WRAP3: {   m_stk_D3DRS_WRAP3.push(dwst);  } break;  
  case D3DRS_WRAP4: {   m_stk_D3DRS_WRAP4.push(dwst);  } break;
  case D3DRS_WRAP5: {   m_stk_D3DRS_WRAP5.push(dwst);  } break;
  case D3DRS_WRAP6: {   m_stk_D3DRS_WRAP6.push(dwst);  } break;    
  case D3DRS_WRAP7: {   m_stk_D3DRS_WRAP7.push(dwst);  } break;  
  
  case D3DRS_CLIPPING: {   m_stk_D3DRS_CLIPPING.push(dwst);  } break;
  case D3DRS_LIGHTING: {   m_stk_D3DRS_LIGHTING.push(dwst);  } break;
  case D3DRS_AMBIENT: {   m_stk_D3DRS_AMBIENT.push(dwst);  } break;  
  case D3DRS_FOGVERTEXMODE: {   m_stk_D3DRS_FOGVERTEXMODE.push(dwst);  } break;
  case D3DRS_COLORVERTEX: {   m_stk_D3DRS_COLORVERTEX.push(dwst);  } break;
  case D3DRS_LOCALVIEWER: {   m_stk_D3DRS_LOCALVIEWER.push(dwst);  } break;   
  
  case D3DRS_NORMALIZENORMALS: {   m_stk_D3DRS_NORMALIZENORMALS.push(dwst);  } break;
  case D3DRS_DIFFUSEMATERIALSOURCE: {   m_stk_D3DRS_DIFFUSEMATERIALSOURCE.push(dwst);  } break;
  case D3DRS_SPECULARMATERIALSOURCE: {   m_stk_D3DRS_SPECULARMATERIALSOURCE.push(dwst);  } break;  
  case D3DRS_AMBIENTMATERIALSOURCE: {   m_stk_D3DRS_AMBIENTMATERIALSOURCE.push(dwst);  } break;
  case D3DRS_EMISSIVEMATERIALSOURCE: {   m_stk_D3DRS_EMISSIVEMATERIALSOURCE.push(dwst);  } break;
  case D3DRS_VERTEXBLEND: {   m_stk_D3DRS_VERTEXBLEND.push(dwst);  } break;   
  case D3DRS_CLIPPLANEENABLE: {   m_stk_D3DRS_CLIPPLANEENABLE.push(dwst);  } break;
  case D3DRS_POINTSIZE: {   m_stk_D3DRS_POINTSIZE.push(dwst);  } break;
  case D3DRS_POINTSIZE_MIN: {   m_stk_D3DRS_POINTSIZE_MIN.push(dwst);  } break;  
  case D3DRS_POINTSPRITEENABLE: {   m_stk_D3DRS_POINTSPRITEENABLE.push(dwst);  } break;
  case D3DRS_POINTSCALEENABLE: {   m_stk_D3DRS_POINTSCALEENABLE.push(dwst);  } break;

  case D3DRS_POINTSCALE_A: {   m_stk_D3DRS_POINTSCALE_A.push(dwst);  } break;   
  case D3DRS_POINTSCALE_B: {   m_stk_D3DRS_POINTSCALE_B.push(dwst);  } break;   
  case D3DRS_POINTSCALE_C: {   m_stk_D3DRS_POINTSCALE_C.push(dwst);  } break;   
  
  case D3DRS_MULTISAMPLEANTIALIAS: {   m_stk_D3DRS_MULTISAMPLEANTIALIAS.push(dwst);  } break;
  case D3DRS_MULTISAMPLEMASK: {   m_stk_D3DRS_MULTISAMPLEMASK.push(dwst);  } break;
  case D3DRS_PATCHEDGESTYLE: {   m_stk_D3DRS_PATCHEDGESTYLE.push(dwst);  } break;  
  case D3DRS_DEBUGMONITORTOKEN: {   m_stk_D3DRS_DEBUGMONITORTOKEN.push(dwst);  } break;
  case D3DRS_POINTSIZE_MAX: {   m_stk_D3DRS_POINTSIZE_MAX.push(dwst);  } break;
  case D3DRS_INDEXEDVERTEXBLENDENABLE: {   m_stk_D3DRS_INDEXEDVERTEXBLENDENABLE.push(dwst);  } break;    
  
  case D3DRS_COLORWRITEENABLE: {   m_stk_D3DRS_COLORWRITEENABLE.push(dwst);  } break;
  case D3DRS_TWEENFACTOR: {   m_stk_D3DRS_TWEENFACTOR.push(dwst);  } break;
  case D3DRS_BLENDOP: {   m_stk_D3DRS_BLENDOP.push(dwst);  } break;  
  case D3DRS_POSITIONDEGREE: {   m_stk_D3DRS_POSITIONDEGREE.push(dwst);  } break;
  case D3DRS_NORMALDEGREE: {   m_stk_D3DRS_NORMALDEGREE.push(dwst);  } break;
  case D3DRS_SCISSORTESTENABLE: {   m_stk_D3DRS_SCISSORTESTENABLE.push(dwst);  } break;   
  
  case D3DRS_SLOPESCALEDEPTHBIAS: {   m_stk_D3DRS_SLOPESCALEDEPTHBIAS.push(dwst);  } break;
  case D3DRS_ANTIALIASEDLINEENABLE: {   m_stk_D3DRS_ANTIALIASEDLINEENABLE.push(dwst);  } break;
  case D3DRS_MINTESSELLATIONLEVEL: {   m_stk_D3DRS_MINTESSELLATIONLEVEL.push(dwst);  } break;  
  case D3DRS_MAXTESSELLATIONLEVEL: {   m_stk_D3DRS_MAXTESSELLATIONLEVEL.push(dwst);  } break;
  case D3DRS_ADAPTIVETESS_X: {   m_stk_D3DRS_ADAPTIVETESS_X.push(dwst);  } break;
  
  case D3DRS_ADAPTIVETESS_Y: {   m_stk_D3DRS_ADAPTIVETESS_Y.push(dwst);  } break;  	 
  case D3DRS_ADAPTIVETESS_Z: {   m_stk_D3DRS_ADAPTIVETESS_Z.push(dwst);  } break;
  case D3DRS_ADAPTIVETESS_W: {   m_stk_D3DRS_ADAPTIVETESS_W.push(dwst);  } break; 
  
  case D3DRS_ENABLEADAPTIVETESSELLATION: {   m_stk_D3DRS_ENABLEADAPTIVETESSELLATION.push(dwst);  } break;
  case D3DRS_TWOSIDEDSTENCILMODE: {   m_stk_D3DRS_TWOSIDEDSTENCILMODE.push(dwst);  } break;
  case D3DRS_CCW_STENCILFAIL: {   m_stk_D3DRS_CCW_STENCILFAIL.push(dwst);  } break;  
  case D3DRS_CCW_STENCILZFAIL: {   m_stk_D3DRS_CCW_STENCILZFAIL.push(dwst);  } break;
  case D3DRS_CCW_STENCILPASS: {   m_stk_D3DRS_CCW_STENCILPASS.push(dwst);  } break;
  case D3DRS_CCW_STENCILFUNC: {   m_stk_D3DRS_CCW_STENCILFUNC.push(dwst);  } break;    
  
  case D3DRS_COLORWRITEENABLE1: {   m_stk_D3DRS_COLORWRITEENABLE1.push(dwst);  } break;
  case D3DRS_COLORWRITEENABLE2: {   m_stk_D3DRS_COLORWRITEENABLE2.push(dwst);  } break;
  case D3DRS_COLORWRITEENABLE3: {   m_stk_D3DRS_COLORWRITEENABLE3.push(dwst);  } break;    
  
  case D3DRS_BLENDFACTOR: {   m_stk_D3DRS_BLENDFACTOR.push(dwst);  } break;
  case D3DRS_SRGBWRITEENABLE: {   m_stk_D3DRS_SRGBWRITEENABLE.push(dwst);  } break;
  
 case D3DRS_DEPTHBIAS: {   m_stk_D3DRS_DEPTHBIAS.push(dwst);  } break;   
  
  case D3DRS_WRAP8: {   m_stk_D3DRS_WRAP8.push(dwst);  } break;
  case D3DRS_WRAP9: {   m_stk_D3DRS_WRAP9.push(dwst);  } break;
  case D3DRS_WRAP10: {   m_stk_D3DRS_WRAP10.push(dwst);  } break;  
  case D3DRS_WRAP11: {   m_stk_D3DRS_WRAP11.push(dwst);  } break;
  case D3DRS_WRAP12: {   m_stk_D3DRS_WRAP12.push(dwst);  } break;
  case D3DRS_WRAP13: {   m_stk_D3DRS_WRAP13.push(dwst);  } break; 
  case D3DRS_WRAP14: {   m_stk_D3DRS_WRAP14.push(dwst);  } break;
  case D3DRS_WRAP15: {   m_stk_D3DRS_WRAP15.push(dwst);  } break;
 
  case D3DRS_SEPARATEALPHABLENDENABLE: {   m_stk_D3DRS_SEPARATEALPHABLENDENABLE.push(dwst);  } break;  
  case D3DRS_SRCBLENDALPHA: {   m_stk_D3DRS_SRCBLENDALPHA.push(dwst);  } break;  
  case D3DRS_DESTBLENDALPHA: {   m_stk_D3DRS_DESTBLENDALPHA.push(dwst);  } break;
  case D3DRS_BLENDOPALPHA: {   m_stk_D3DRS_BLENDOPALPHA.push(dwst);  } break;
   
     default: 
	 {
       // unknown
       hr |= E_FAIL;
     }
  
  } // switch

  }
   catch(...)  
  {
   // Exception
	  hr |= E_FAIL;
 };
  
 
  return hr;
}


//=======================================================================
HRESULT StateStack::PopState(IDirect3DDevice9* pdevice, D3DRENDERSTATETYPE state) 
{
  HRESULT hr =0;
  DWORD dwst =  0-1;
  
  try 
  {

  switch(state) 
  {
  
 case D3DRS_ZENABLE: { dwst=m_stk_D3DRS_ZENABLE.pop();  } break; 
 case D3DRS_FILLMODE: { dwst=m_stk_D3DRS_FILLMODE.pop();  } break;   
 case D3DRS_SHADEMODE: { dwst=m_stk_D3DRS_SHADEMODE.pop();  } break;   
 case D3DRS_ZWRITEENABLE: { dwst=m_stk_D3DRS_ZWRITEENABLE.pop();  } break;   
 case D3DRS_ALPHATESTENABLE: { dwst=m_stk_D3DRS_ALPHATESTENABLE.pop();  } break;   
 case D3DRS_LASTPIXEL: { dwst=m_stk_D3DRS_LASTPIXEL.pop();  } break; 
 case D3DRS_SRCBLEND: { dwst=m_stk_D3DRS_SRCBLEND.pop();  } break;   
 case D3DRS_DESTBLEND: { dwst=m_stk_D3DRS_DESTBLEND.pop();  } break;   
 case D3DRS_CULLMODE: { dwst=m_stk_D3DRS_CULLMODE.pop();  } break;   
 case D3DRS_ZFUNC: { dwst=m_stk_D3DRS_ZFUNC.pop();  } break;    
  
  case D3DRS_ALPHAREF: { dwst=m_stk_D3DRS_ALPHAREF.pop();   } break;
  case D3DRS_ALPHAFUNC: { dwst=m_stk_D3DRS_ALPHAFUNC.pop();   } break; 
  case D3DRS_DITHERENABLE: { dwst=m_stk_D3DRS_DITHERENABLE.pop();   } break; 
  case D3DRS_ALPHABLENDENABLE: { dwst=m_stk_D3DRS_ALPHABLENDENABLE.pop();   } break;
  case D3DRS_FOGENABLE: { dwst=m_stk_D3DRS_FOGENABLE.pop();   } break; 
  case D3DRS_SPECULARENABLE: { dwst=m_stk_D3DRS_SPECULARENABLE.pop();   } break;   
  case D3DRS_FOGCOLOR: { dwst=m_stk_D3DRS_FOGCOLOR.pop();   } break;
  case D3DRS_FOGTABLEMODE: { dwst=m_stk_D3DRS_FOGTABLEMODE.pop();   } break; 
  case D3DRS_FOGSTART: { dwst=m_stk_D3DRS_FOGSTART.pop();   } break;  
  
  case D3DRS_FOGEND: { dwst=m_stk_D3DRS_FOGEND.pop();   } break;
  case D3DRS_FOGDENSITY: { dwst=m_stk_D3DRS_FOGDENSITY.pop();   } break;  
  
  case D3DRS_RANGEFOGENABLE: { dwst=m_stk_D3DRS_RANGEFOGENABLE.pop();   } break;
  case D3DRS_STENCILENABLE: { dwst=m_stk_D3DRS_STENCILENABLE.pop();   } break; 
  case D3DRS_STENCILFAIL: { dwst=m_stk_D3DRS_STENCILFAIL.pop();   } break; 
  case D3DRS_STENCILZFAIL: { dwst=m_stk_D3DRS_STENCILZFAIL.pop();   } break;
  case D3DRS_STENCILPASS: { dwst=m_stk_D3DRS_STENCILPASS.pop();   } break; 
  case D3DRS_STENCILFUNC: { dwst=m_stk_D3DRS_STENCILFUNC.pop();   } break;   
  case D3DRS_STENCILREF: { dwst=m_stk_D3DRS_STENCILREF.pop();   } break;
  case D3DRS_STENCILMASK: { dwst=m_stk_D3DRS_STENCILMASK.pop();   } break; 
  case D3DRS_STENCILWRITEMASK: { dwst=m_stk_D3DRS_STENCILWRITEMASK.pop();   } break;   
  
  case D3DRS_TEXTUREFACTOR: { dwst=m_stk_D3DRS_TEXTUREFACTOR.pop();   } break;
  
  case D3DRS_WRAP0: { dwst=m_stk_D3DRS_WRAP0.pop();   } break;
  case D3DRS_WRAP1: { dwst=m_stk_D3DRS_WRAP1.pop();   } break; 
  case D3DRS_WRAP2: { dwst=m_stk_D3DRS_WRAP2.pop();   } break; 
  case D3DRS_WRAP3: { dwst=m_stk_D3DRS_WRAP3.pop();   } break;
  case D3DRS_WRAP4: { dwst=m_stk_D3DRS_WRAP4.pop();   } break; 
  case D3DRS_WRAP5: { dwst=m_stk_D3DRS_WRAP5.pop();   } break;   
  case D3DRS_WRAP6: { dwst=m_stk_D3DRS_WRAP6.pop();   } break;
  case D3DRS_WRAP7: { dwst=m_stk_D3DRS_WRAP7.pop();   } break;   
  
  case D3DRS_CLIPPING: { dwst=m_stk_D3DRS_CLIPPING.pop();   } break;
  case D3DRS_LIGHTING: { dwst=m_stk_D3DRS_LIGHTING.pop();   } break; 
  case D3DRS_AMBIENT: { dwst=m_stk_D3DRS_AMBIENT.pop();   } break; 
  case D3DRS_FOGVERTEXMODE: { dwst=m_stk_D3DRS_FOGVERTEXMODE.pop();   } break;
  case D3DRS_COLORVERTEX: { dwst=m_stk_D3DRS_COLORVERTEX.pop();   } break; 
  case D3DRS_LOCALVIEWER: { dwst=m_stk_D3DRS_LOCALVIEWER.pop();   } break;   
  case D3DRS_NORMALIZENORMALS: { dwst=m_stk_D3DRS_NORMALIZENORMALS.pop();   } break;
  case D3DRS_DIFFUSEMATERIALSOURCE: { dwst=m_stk_D3DRS_DIFFUSEMATERIALSOURCE.pop();   } break; 
  case D3DRS_SPECULARMATERIALSOURCE: { dwst=m_stk_D3DRS_SPECULARMATERIALSOURCE.pop();   } break; 	  
  
  case D3DRS_AMBIENTMATERIALSOURCE: { dwst=m_stk_D3DRS_AMBIENTMATERIALSOURCE.pop();   } break;
  case D3DRS_EMISSIVEMATERIALSOURCE: { dwst=m_stk_D3DRS_EMISSIVEMATERIALSOURCE.pop();   } break; 
  case D3DRS_VERTEXBLEND: { dwst=m_stk_D3DRS_VERTEXBLEND.pop();   } break; 
  case D3DRS_CLIPPLANEENABLE: { dwst=m_stk_D3DRS_CLIPPLANEENABLE.pop();   } break;  
 
  case D3DRS_POINTSIZE: { dwst=m_stk_D3DRS_POINTSIZE.pop();   } break;
  case D3DRS_POINTSIZE_MIN: { dwst=m_stk_D3DRS_POINTSIZE_MIN.pop();   } break; 
  case D3DRS_POINTSPRITEENABLE: { dwst=m_stk_D3DRS_POINTSPRITEENABLE.pop();   } break; 
  case D3DRS_POINTSCALEENABLE: { dwst=m_stk_D3DRS_POINTSCALEENABLE.pop();   } break;
  case D3DRS_POINTSCALE_A: { dwst=m_stk_D3DRS_POINTSCALE_A.pop();   } break; 
  case D3DRS_POINTSCALE_B: { dwst=m_stk_D3DRS_POINTSCALE_B.pop();   } break;   
  case D3DRS_POINTSCALE_C: { dwst=m_stk_D3DRS_POINTSCALE_C.pop();   } break;

  case D3DRS_MULTISAMPLEANTIALIAS: { dwst=m_stk_D3DRS_MULTISAMPLEANTIALIAS.pop();   } break; 
  case D3DRS_MULTISAMPLEMASK: { dwst=m_stk_D3DRS_MULTISAMPLEMASK.pop();   } break; 
 
  case D3DRS_PATCHEDGESTYLE: { dwst=m_stk_D3DRS_PATCHEDGESTYLE.pop();   } break;
  case D3DRS_DEBUGMONITORTOKEN: { dwst=m_stk_D3DRS_DEBUGMONITORTOKEN.pop();   } break; 
  case D3DRS_POINTSIZE_MAX: { dwst=m_stk_D3DRS_POINTSIZE_MAX.pop();   } break; 
  case D3DRS_INDEXEDVERTEXBLENDENABLE: { dwst=m_stk_D3DRS_INDEXEDVERTEXBLENDENABLE.pop();   } break;
  case D3DRS_COLORWRITEENABLE: { dwst=m_stk_D3DRS_COLORWRITEENABLE.pop();   } break; 
  case D3DRS_TWEENFACTOR: { dwst=m_stk_D3DRS_TWEENFACTOR.pop();   } break;   
  case D3DRS_BLENDOP: { dwst=m_stk_D3DRS_BLENDOP.pop();   } break;
  case D3DRS_POSITIONDEGREE: { dwst=m_stk_D3DRS_POSITIONDEGREE.pop();   } break; 
  case D3DRS_NORMALDEGREE: { dwst=m_stk_D3DRS_NORMALDEGREE.pop();   } break;  
  case D3DRS_SCISSORTESTENABLE: { dwst=m_stk_D3DRS_SCISSORTESTENABLE.pop();   } break; 
  case D3DRS_SLOPESCALEDEPTHBIAS: { dwst=m_stk_D3DRS_SLOPESCALEDEPTHBIAS.pop();   } break;
  case D3DRS_ANTIALIASEDLINEENABLE: { dwst=m_stk_D3DRS_ANTIALIASEDLINEENABLE.pop();   } break;
  
  case D3DRS_MINTESSELLATIONLEVEL: { dwst=m_stk_D3DRS_MINTESSELLATIONLEVEL.pop();   } break;
  case D3DRS_MAXTESSELLATIONLEVEL: { dwst=m_stk_D3DRS_MAXTESSELLATIONLEVEL.pop();   } break;  
 
  case D3DRS_ADAPTIVETESS_X: { dwst=m_stk_D3DRS_ADAPTIVETESS_X.pop();   } break;
  case D3DRS_ADAPTIVETESS_Y: { dwst=m_stk_D3DRS_ADAPTIVETESS_Y.pop();   } break; 
  case D3DRS_ADAPTIVETESS_Z: { dwst=m_stk_D3DRS_ADAPTIVETESS_Z.pop();   } break; 
  case D3DRS_ADAPTIVETESS_W: { dwst=m_stk_D3DRS_ADAPTIVETESS_W.pop();   } break; 
 
  case D3DRS_ENABLEADAPTIVETESSELLATION: { dwst=m_stk_D3DRS_ENABLEADAPTIVETESSELLATION.pop();   } break;
  case D3DRS_TWOSIDEDSTENCILMODE: { dwst=m_stk_D3DRS_TWOSIDEDSTENCILMODE.pop();   } break; 
  case D3DRS_CCW_STENCILFAIL: { dwst=m_stk_D3DRS_CCW_STENCILFAIL.pop();   } break; 
  case D3DRS_CCW_STENCILZFAIL: { dwst=m_stk_D3DRS_CCW_STENCILZFAIL.pop();   } break;
  case D3DRS_CCW_STENCILPASS: { dwst=m_stk_D3DRS_CCW_STENCILPASS.pop();   } break; 
  case D3DRS_CCW_STENCILFUNC: { dwst=m_stk_D3DRS_CCW_STENCILFUNC.pop();   } break;   
  case D3DRS_COLORWRITEENABLE1: { dwst=m_stk_D3DRS_COLORWRITEENABLE1.pop();   } break;
  case D3DRS_COLORWRITEENABLE2: { dwst=m_stk_D3DRS_COLORWRITEENABLE2.pop();   } break; 
  case D3DRS_COLORWRITEENABLE3: { dwst=m_stk_D3DRS_COLORWRITEENABLE3.pop();   } break;  
 
  case D3DRS_BLENDFACTOR: { dwst=m_stk_D3DRS_BLENDFACTOR.pop();   } break;
  case D3DRS_SRGBWRITEENABLE: { dwst=m_stk_D3DRS_SRGBWRITEENABLE.pop();   } break; 
  case D3DRS_DEPTHBIAS: { dwst=m_stk_D3DRS_DEPTHBIAS.pop();   } break; 

  case D3DRS_WRAP8: { dwst=m_stk_D3DRS_WRAP8.pop();   } break;
  case D3DRS_WRAP9: { dwst=m_stk_D3DRS_WRAP9.pop();   } break; 
  case D3DRS_WRAP10: { dwst=m_stk_D3DRS_WRAP10.pop();   } break;   
  case D3DRS_WRAP11: { dwst=m_stk_D3DRS_WRAP11.pop();   } break;
  case D3DRS_WRAP12: { dwst=m_stk_D3DRS_WRAP12.pop();   } break; 
  case D3DRS_WRAP13: { dwst=m_stk_D3DRS_WRAP13.pop();   } break; 
  case D3DRS_WRAP14: { dwst=m_stk_D3DRS_WRAP14.pop();   } break; 
  case D3DRS_WRAP15: { dwst=m_stk_D3DRS_WRAP15.pop();   } break;
 
  case D3DRS_SEPARATEALPHABLENDENABLE: { dwst=m_stk_D3DRS_SEPARATEALPHABLENDENABLE.pop();   } break;
  case D3DRS_SRCBLENDALPHA: { dwst=m_stk_D3DRS_SRCBLENDALPHA.pop();   } break; 
  case D3DRS_DESTBLENDALPHA: { dwst=m_stk_D3DRS_DESTBLENDALPHA.pop();   } break; 
  case D3DRS_BLENDOPALPHA: { dwst=m_stk_D3DRS_BLENDOPALPHA.pop();   } break; 
 
    default: 
	{
       // unknown
       hr |= E_FAIL;
    }
	
	
  
  } // switch
  
  } 
  catch(...)  
  {
    // error empty stack
	hr |= E_FAIL;
  }
  
  if FAILED(hr) {  return hr; };
  
  try 
  {
  hr|=pdevice->SetRenderState( state, dwst);
  }
  catch(...)   
  {
  
    hr |= E_FAIL;
  }
 
  return hr;
};
 


// end file