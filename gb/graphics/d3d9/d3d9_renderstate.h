


#pragma once

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  
		class d3d9_renderstate : public RenderState
		{
		public:
		
		
			virtual ~d3d9_renderstate() {}
		
		
		
			bool setSource(const char *code) 
			{
				assert(false);
			}
			
			void apply()
			{
				assert(false);
			}
			
			
		private:
			//typedef boost::function< void () > stateFunc;
			//std::vector<stateFunc> stateFunctions;
		};
  

  
  }
 }
}
