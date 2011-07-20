/**  \file

// не окончательно !

*/



#pragma once

#include "../Fog.h"

namespace gb
{

 namespace graphics
 {

  namespace opengl
  {
  
	  class GLFog : public Fog {
	  public:
	  
		virtual ~GLFog() {}
		
		
			//! устанавливает состояние тумана в рендер устройство. Прежнее состояние сохраняется.
			virtual void begin()
			{
			assert(false);
			}		
			
			//! завершение состояния тумана. ВОсстановление прежнего состояния.
			virtual void end()
			{
			assert(false);
			}
	  
	  };
  
 
  }
 }
}
