//
// набросок поверхности отрисовки
//

#pragma once
#include <gb/base/Types.h>
#include <gb/base/Point.h>

.........

class RenderTargetSurface {
public:
   virtual ~RenderTargetSurface() {}

  uint32_t  width()  const    { return  m_width;  }
  uint32_t  height() const    { return  m_height; }
  
  virtual COLOR getPixelColor(const gb::base::Point& pnt) const =0;
  
  virtual int32_t   save_to_image_file(const std::string& fname) =0;

 ..............

protected:
   uint32_t  m_width;
   uint32_t  m_height;



};
