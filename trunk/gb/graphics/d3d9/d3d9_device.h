

#pragma once

#include "../Device.h"


namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  
	  class d3d9_device : public Device {
	  public:
	  
	  
 
			virtual RenderTarget* createWindowRenderTarget(window_subsystem::Window *wnd) 
			{
			 #pragma message(" need code "  __FILE__ )	
			 assert(false && "no code"); 
			}
			
			virtual bool getSize(int &width, int &height)
			{

			 #pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
 
			virtual void setScissorRect(const base::Rectangle &rc)
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}

			virtual Texture *createTexture(Texture::Type type)
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
			
			virtual Buffer *createIndexBuffer()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
		
			virtual Buffer *createVertexBuffer()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
			
			virtual RenderState *createRenderState()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}

			virtual void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0)
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}

			virtual Shader *createVertexShader()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			
			}
			
			virtual Shader *createGeometryShader()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			
			}
 
			virtual Shader *createFragmentShader()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 		
			}
			
			virtual ShaderProgram *createShaderProgram()
			{

				#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}

			virtual void deleteUnusedObjects()
			{

#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
			
			virtual void clean() 
			{

#pragma message(" need code "  __FILE__ )	
				assert(false && "no code"); 
			}
	  
	  
	  
	  
	  
	  
	  
	  };
  
  
  
  
  
  
  
  
  
  
  }
 }
}
