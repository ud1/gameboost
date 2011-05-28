/** \file
 \brief Стек стейтов  устройства d3d9.
  Устройство класса очень простое - каждому стейту свой стек.


  \author ksacvet777

*/

#pragma once
 
#include <d3d9.h>
#include <stack>
#include <stdexcept>
 

//! \brief Стек зачения стейта девайса  
class StateValStack 
{
public:

	StateValStack() 
	{ 

	}

	~StateValStack() {}

	inline bool empty() const 
	{  
	   return m_stack.empty(); 
	}
	
	inline void push(DWORD val) 
	{
	     m_stack.push(val);
	}

	DWORD pop()  throw( std::runtime_error& ) 
	{
	    static const char CSRT_ERR [] = "Stack is empty";
		if( empty() ) 
		{
		throw std::runtime_error( CSRT_ERR );
		}

		DWORD res = top();
		#pragma message("ПРОВЕРИТЬ РАБОТУ СТЕКА ")
		m_stack.pop();
		return res;
	}

	DWORD top() 
	{
	   DWORD res = m_stack.top();
	   return res;
	}

private:
	//int m_stackpos;
	std::stack<DWORD> m_stack;

};

/** \brief Стэк стейтов девайса */
class StateStack {
public:
	    StateStack() {};
       ~StateStack() {};

	bool CheckAllEmpty() const ;

	HRESULT PushState (IDirect3DDevice9* pdevice, D3DRENDERSTATETYPE state);
	HRESULT PopState  (IDirect3DDevice9* pdevice, D3DRENDERSTATETYPE state);


private:

 StateValStack  m_stk_D3DRS_ZENABLE   ;
 StateValStack  m_stk_D3DRS_FILLMODE   ;
 StateValStack  m_stk_D3DRS_SHADEMODE   ;
 StateValStack  m_stk_D3DRS_ZWRITEENABLE   ;
 StateValStack  m_stk_D3DRS_ALPHATESTENABLE   ;
 StateValStack  m_stk_D3DRS_LASTPIXEL   ;
 StateValStack  m_stk_D3DRS_SRCBLEND   ;
 StateValStack  m_stk_D3DRS_DESTBLEND   ;
 StateValStack  m_stk_D3DRS_CULLMODE   ;
 StateValStack  m_stk_D3DRS_ZFUNC   ;
 StateValStack  m_stk_D3DRS_ALPHAREF   ;
 StateValStack  m_stk_D3DRS_ALPHAFUNC   ;
 StateValStack  m_stk_D3DRS_DITHERENABLE   ;
 StateValStack  m_stk_D3DRS_ALPHABLENDENABLE   ;
 StateValStack  m_stk_D3DRS_FOGENABLE   ;
 StateValStack  m_stk_D3DRS_SPECULARENABLE   ;
 StateValStack  m_stk_D3DRS_FOGCOLOR   ;
 StateValStack  m_stk_D3DRS_FOGTABLEMODE   ;
 StateValStack  m_stk_D3DRS_FOGSTART   ;
 StateValStack  m_stk_D3DRS_FOGEND   ;
 StateValStack  m_stk_D3DRS_FOGDENSITY   ;
 StateValStack  m_stk_D3DRS_RANGEFOGENABLE   ;
 StateValStack  m_stk_D3DRS_STENCILENABLE   ;
 StateValStack  m_stk_D3DRS_STENCILFAIL   ;
 StateValStack  m_stk_D3DRS_STENCILZFAIL   ;
 StateValStack  m_stk_D3DRS_STENCILPASS   ;
 StateValStack  m_stk_D3DRS_STENCILFUNC   ;
 StateValStack  m_stk_D3DRS_STENCILREF   ;
 StateValStack  m_stk_D3DRS_STENCILMASK   ;
 StateValStack  m_stk_D3DRS_STENCILWRITEMASK   ;
 StateValStack  m_stk_D3DRS_TEXTUREFACTOR   ;
 StateValStack  m_stk_D3DRS_WRAP0   ;
 StateValStack  m_stk_D3DRS_WRAP1   ;
 StateValStack  m_stk_D3DRS_WRAP2   ;
 StateValStack  m_stk_D3DRS_WRAP3   ;
 StateValStack  m_stk_D3DRS_WRAP4   ;
 StateValStack  m_stk_D3DRS_WRAP5   ;
 StateValStack  m_stk_D3DRS_WRAP6   ;
 StateValStack  m_stk_D3DRS_WRAP7   ;
 StateValStack  m_stk_D3DRS_CLIPPING   ;
 StateValStack  m_stk_D3DRS_LIGHTING   ;
 StateValStack  m_stk_D3DRS_AMBIENT   ;
 StateValStack  m_stk_D3DRS_FOGVERTEXMODE   ;
 StateValStack  m_stk_D3DRS_COLORVERTEX   ;
 StateValStack  m_stk_D3DRS_LOCALVIEWER   ;
 StateValStack  m_stk_D3DRS_NORMALIZENORMALS   ;
 StateValStack  m_stk_D3DRS_DIFFUSEMATERIALSOURCE   ;
 StateValStack  m_stk_D3DRS_SPECULARMATERIALSOURCE  ;
 StateValStack  m_stk_D3DRS_AMBIENTMATERIALSOURCE   ;
 StateValStack  m_stk_D3DRS_EMISSIVEMATERIALSOURCE   ;
 StateValStack  m_stk_D3DRS_VERTEXBLEND   ;
 StateValStack  m_stk_D3DRS_CLIPPLANEENABLE   ;
 StateValStack  m_stk_D3DRS_POINTSIZE   ;
 StateValStack  m_stk_D3DRS_POINTSIZE_MIN   ;
 StateValStack  m_stk_D3DRS_POINTSPRITEENABLE   ;
 StateValStack  m_stk_D3DRS_POINTSCALEENABLE   ;
 StateValStack  m_stk_D3DRS_POINTSCALE_A   ;
 StateValStack  m_stk_D3DRS_POINTSCALE_B   ;
 StateValStack  m_stk_D3DRS_POINTSCALE_C   ;
 StateValStack  m_stk_D3DRS_MULTISAMPLEANTIALIAS   ;
 StateValStack  m_stk_D3DRS_MULTISAMPLEMASK   ;
 StateValStack  m_stk_D3DRS_PATCHEDGESTYLE   ;
 StateValStack  m_stk_D3DRS_DEBUGMONITORTOKEN   ;
 StateValStack  m_stk_D3DRS_POINTSIZE_MAX   ;
 StateValStack  m_stk_D3DRS_INDEXEDVERTEXBLENDENABLE   ;
 StateValStack  m_stk_D3DRS_COLORWRITEENABLE   ;
 StateValStack  m_stk_D3DRS_TWEENFACTOR ;
 StateValStack  m_stk_D3DRS_BLENDOP   ;
 StateValStack  m_stk_D3DRS_POSITIONDEGREE   ;
 StateValStack  m_stk_D3DRS_NORMALDEGREE   ;
 StateValStack  m_stk_D3DRS_SCISSORTESTENABLE   ;
 StateValStack  m_stk_D3DRS_SLOPESCALEDEPTHBIAS   ;
 StateValStack  m_stk_D3DRS_ANTIALIASEDLINEENABLE   ;
 StateValStack  m_stk_D3DRS_MINTESSELLATIONLEVEL   ;
 StateValStack  m_stk_D3DRS_MAXTESSELLATIONLEVEL   ;
 StateValStack  m_stk_D3DRS_ADAPTIVETESS_X   ;
 StateValStack  m_stk_D3DRS_ADAPTIVETESS_Y   ;
 StateValStack  m_stk_D3DRS_ADAPTIVETESS_Z   ;
 StateValStack  m_stk_D3DRS_ADAPTIVETESS_W   ;
 StateValStack  m_stk_D3DRS_ENABLEADAPTIVETESSELLATION   ;
 StateValStack  m_stk_D3DRS_TWOSIDEDSTENCILMODE   ;
 StateValStack  m_stk_D3DRS_CCW_STENCILFAIL   ;
 StateValStack  m_stk_D3DRS_CCW_STENCILZFAIL   ;
 StateValStack  m_stk_D3DRS_CCW_STENCILPASS   ;
 StateValStack  m_stk_D3DRS_CCW_STENCILFUNC   ;
 StateValStack  m_stk_D3DRS_COLORWRITEENABLE1   ;
 StateValStack  m_stk_D3DRS_COLORWRITEENABLE2   ;
 StateValStack  m_stk_D3DRS_COLORWRITEENABLE3   ;
 StateValStack  m_stk_D3DRS_BLENDFACTOR   ;
 StateValStack  m_stk_D3DRS_SRGBWRITEENABLE   ;
 StateValStack  m_stk_D3DRS_DEPTHBIAS   ;
 StateValStack  m_stk_D3DRS_WRAP8   ;
 StateValStack  m_stk_D3DRS_WRAP9  ;
 StateValStack  m_stk_D3DRS_WRAP10   ;
 StateValStack  m_stk_D3DRS_WRAP11   ;
 StateValStack  m_stk_D3DRS_WRAP12   ;
 StateValStack  m_stk_D3DRS_WRAP13   ;
 StateValStack  m_stk_D3DRS_WRAP14   ;
 StateValStack  m_stk_D3DRS_WRAP15  ;
 StateValStack  m_stk_D3DRS_SEPARATEALPHABLENDENABLE   ;
 StateValStack  m_stk_D3DRS_SRCBLENDALPHA   ;
 StateValStack  m_stk_D3DRS_DESTBLENDALPHA   ;
 StateValStack  m_stk_D3DRS_BLENDOPALPHA  ;

 
};
// end class
 

// end file