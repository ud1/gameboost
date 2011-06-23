/** \file
 \brief Абстрактные интерфейсы  для воспроизведения звука

 \author ksacvet777
*/

#pragma once
#include <gb/base/Types.h>

namespace gb
{

 namespace audio
 {

  
  class ISound {
  pubic:
    virtual ~ISound() {}
  
   int32_t   play(bool looped) =0;
   int32_t   stop() =0;
   
   bool      isPlay() const =0;
   
   void      volume(uint32_t value) =0;
   uint32_t  volume() const =0;
  
  
  
  
  
  };


 }
}

// end file