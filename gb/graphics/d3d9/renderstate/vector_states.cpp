#include "d3d9pch.h"


#if ( defined(GB_D3D9) && defined(WIN32) )

#include <gb/graphics/d3d9/renderstate/vector_states.h>
#include <gb/graphics/d3d9/dataconv/dataconv.h>
#include <gb/str/String.h>

#include <assert.h>

namespace gb          
{
namespace graphics    
{
namespace d3d9        
{
namespace renderstate 
{

//=========================================================================



//=========================================================================
//						    StateValues
//=========================================================================

void StateValues::addState(D3DRENDERSTATETYPE rsType, DWORD rsValue) 
{
		StateValue_s sv;
		sv.rsType = rsType;
		sv.dwVal = rsValue;
		m_vector.push_back(sv);
}

//=========================================================================
HRESULT StateValues::beginStates(IDirect3DDevice9* pdevice)
{
 HRESULT hr =0 ;
 assert(pdevice);
 if(m_vector.size() < 1)
 {
   return hr;
 }
 
  DWORD dwoldvalue ;
 for(size_t c=0; c<m_vector.size(); c++)
 {
   dwoldvalue = 0;
   hr |= pdevice->GetRenderState(m_vector[c].rsType , &dwoldvalue );  
   m_vector[c].dwOldVal = dwoldvalue;
   hr |= pdevice->SetRenderState(m_vector[c].rsType , m_vector[c].dwVal );  
 
 
 }
 
 
  return hr;
}
 
//=========================================================================
HRESULT StateValues::endStates(IDirect3DDevice9* pdevice)
{
 HRESULT hr =0 ;
  assert(pdevice);
 if(m_vector.size() < 1)
 {
   return hr;
 }
 
 for(size_t c=0; c<m_vector.size(); c++)
 {
   hr |= pdevice->SetRenderState(m_vector[c].rsType , m_vector[c].dwOldVal );  
 
 
 }
 
 
  return hr;
}



//==================================================================
void  StateValues::writeToStr( std::string& str, char chrItemsSeparator, char chrValueSeparator )
{
	if(m_vector.empty() )
	{
		return ;
	}

	char buf[2];

	buf[0] = '\0';
	buf[1] = '\0';

	for(size_t c=0; c<m_vector.size(); c++)
	{
		D3DRENDERSTATETYPE state;
		DWORD val = 0;
		state = m_vector[c].rsType;
		val = m_vector[c].dwVal;


		str += dataconv::D3DRENDERSTATETYPE_tostr( state );
		buf[0] = chrValueSeparator;
		str +=	buf;
	 	str += dataconv::D3DRENDERSTATEVALUE_tostr( state, val);

		buf[0] = chrItemsSeparator;
		str += buf;
	}



};




//==================================================================
bool StateValues::readFromStr( const std::string& strarg,  char chrItemsSeparator, char chrValueSeparator  ) 
{
	 clear();

	 // чтение из файла
//	std::string str;
//	if(!gb::str::loadStrFromFileA(str, fname) ) {
//		return false;
//	};

	 std::string str;
	gb::str::preprocessCppComments(str, strarg, 0);

	std::vector< std::string > vResult;
	char _str[2];
	_str[0] = chrItemsSeparator;
	_str[1] = '\0';
	gb::str::splitTokens  ( vResult,  str, _str  );

	if(vResult.size() == 0)
	{
		// пусто !
		return true;
	}

	std::string s_itm;
	std::string s_statetype;
	std::string s_statevalue;
	std::vector<std::string> vState;

	for(size_t c=0; c<vResult.size(); c++)
	{

		s_itm = vResult[c];
		s_statetype   = "";
		s_statevalue  = "";
		vState.clear();


		if(s_itm.length() == 0) 
		{
			continue;
		}

		_str[0] = chrValueSeparator;

		gb::str::splitTokens ( vState,  s_itm,  _str );
		if( vState.size() < 2   )
		{
			// error
			return false;
		}


		s_statetype  = vState[0];
		s_statevalue = vState[1];

		gb::str::trim(s_statetype);  
		gb::str::trim(s_statetype);



		// read values
 
		  D3DRENDERSTATETYPE st_type = (D3DRENDERSTATETYPE)0;
	  if(  !d3d9::dataconv::D3DRENDERSTATETYPE_fromstr(st_type, s_statetype  ) )
		{
			return false;
		};

		DWORD dwValue = 0;
		if(  !d3d9::dataconv::D3DRENDERSTATEVALUE_fromstr (dwValue,  st_type, s_statevalue  ) )
		{

			return false;
		};


	  addState(st_type, dwValue);



	}; // for

 
	return true;
};




//==================================================================




//==================================================================


//==================================================================

}
}
}
}


#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file