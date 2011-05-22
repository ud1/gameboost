/**   \file
\brief  Вектор состояний устройства d3d9

 \author ksacvet777
 
*/


#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once

#include <d3d9.h>
#include <vector>
#include <stdexcept>

namespace gb 
{
 namespace graphics 
 {
  namespace d3d9 
  {
   namespace renderstate
   {

//--------------------------------------------------------------------

//! \brief Собрка значений : стейт, значение и старое значение.
struct StateValue_s 
{
	  D3DRENDERSTATETYPE rsType; ///<  какой стейт устанавливать/восстанавливать
	  DWORD dwVal; ///< значение стейта.
	  DWORD dwOldVal; ///< прежнее значение стейта. Для восстановления.
};

//! \brief  НАбор стейтов на основе вектора.
class StateValues {
public:

	StateValues(int nVectorReserve=32) 
	{  
		m_vector.reserve(nVectorReserve);
	}
	
	void clear() { m_vector.clear(); }

	//! \brief Добавить стейт в вектор .
	void addState(D3DRENDERSTATETYPE rsType, DWORD rsValue);
	//! \brief Установить стейты. запомнить прежние стейты
	HRESULT beginStates(IDirect3DDevice9* pdevice);	
	//! \brief Восстановить прежние стейты
	HRESULT endStates(IDirect3DDevice9* pdevice);

	/** \brief  Прочитать стейты из строки str      
	  \param  str - строка из которой требуется проичтать стейты
	  \param  chrItemsSeparator - символ разделитель пунктов (обычно это перенос строки '\n' )
	  \param  chrValueSeparator - символ разделитель стейт=значение (обычно это '=' )
	  \return  вернёт true  если парсин строки успешен. 	*/
	bool readFromStr(  const std::string& str, char chrItemsSeparator, char chrValueSeparator );

	//! \brief  записать стейты в текстовый вид. Прочитать можно   методом	readFromStr
	void  writeToStr( std::string& str, char chrItemsSeparator, char chrValueSeparator );


  const StateValue_s& operator [] (const size_t index) const  throw() 
  {
	  if( ( index >= m_vector.size() ) || (index<0)  )
	  {
		  throw std::runtime_error("bad index");
	  }

	  return m_vector[index];
  }

  StateValue_s& operator [] (const size_t index)  throw() 
  {
	  if( ( index >= m_vector.size() ) || (index<0)  )
	  {
		  throw std::runtime_error("bad index");
	  }

	  return m_vector[index];
  }


	std::vector<StateValue_s>  m_vector;
};





   
//--------------------------------------------------------------------   
   
   }
  }
 }
}

#endif   // #if ( defined(GB_D3D9) && defined(WIN32) )

// end file