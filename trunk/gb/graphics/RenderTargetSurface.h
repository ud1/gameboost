//
// набросок поверхности отрисовки
//

#pragma once
#include <gb/base/Types.h>
#include <gb/base/Point.h>
#include <gb/base/Rectangle.h>


.........

class RenderTargetSurface {
public:
			RenderTargetSurface()
			{
				m_width = m_height = 0;
			}

   virtual ~RenderTargetSurface() {}

  uint32_t  width()  const    { return  m_width;  }
  uint32_t  height() const    { return  m_height; }
  
  virtual COLOR getPixelColor(const gb::base::Point& pnt) const =0;
  
  virtual int32_t   save_to_image_file(const std::string& fname) const =0;
  
  virtual COLOR compute_aver_color_rect(const gb::base::Rectangle* rec) const =0;

 ..............

protected:
   uint32_t  m_width;
   uint32_t  m_height;



};
