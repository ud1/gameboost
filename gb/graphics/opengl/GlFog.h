/**  \file

// �� ������������ !

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
		
		
			//! ������������� ��������� ������ � ������ ����������. ������� ��������� �����������.
			virtual void begin()
			{
			assert(false);
			}		
			
			//! ���������� ��������� ������. �������������� �������� ���������.
			virtual void end()
			{
			assert(false);
			}
	  
	  };
  
 
  }
 }
}
