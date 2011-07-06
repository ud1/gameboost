 
#pragma once
#include <gb/base/IRefCountable.h>


namespace gb
{

namespace graphic
{
 
//----------------------------------------------------------------------


namespace renderTargetSurfaceSize_e
{

  enum e
  {
  
   

  };

}



class RenderTargetSurface : public base::IRefCountable  {
public:

	uint32_t width()  const { return _width;  }
	uint32_t hieght() const { return _hieght; }

	virtual int32_t copy_from(const RenderTargetSurface* rt) =0;
	virtual uint32_t read_pixel_color(int32_t x, int32_t y) const =0;

protected:

	   RenderTargetSurface() 
	   {
		  _width  = 0;
		  _hieght = 0;
	   }

	uint32_t _width;
	uint32_t _hieght;

};



class Render_Target : public base::IRefCountable {
public:
	int ttrtetretghfgh;

protected:
	Render_Target() {}
};



//template <>
class RenderTargetBuffer
{




};




//----------------------------------------------------------------------

}
}

// end file