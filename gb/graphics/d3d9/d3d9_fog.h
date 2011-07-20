

#pragma once

#include "../Fog.h"


namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  class d3d9_fog : public Fog {
  public:
  
	virtual ~d3d9_fog() {}
	
	
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
