/** \file ogl.h

  Я хз  пока пусто...   Коммитете ^=^



*/

#ifdef GB_OPENGL

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>

#include <gb/math/math.h>
 

  // незнаю как там в линухе и пр..  поправьте пожста
#if defined(WIN32) 

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>

#endif


namespace gb
{

 namespace graphics
 {
 
  namespace opengl
  {
  //--------------------------------------------------------------------------------
 
 
  
inline void set_GL_ALPHA_TEST (bool val)   { if(val){ glEnable(GL_ALPHA_TEST); } else { glDisable(GL_ALPHA_TEST);};  }
inline void set_GL_DEPTH_TEST (bool val)   { if(val){ glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST);};  }  
inline void set_GL_DITHER     (bool val)   { if(val){ glEnable(GL_DITHER); } else { glDisable(GL_DITHER);};  }  
inline void set_GL_FOG        (bool val)   { if(val){ glEnable(GL_FOG); } else { glDisable(GL_FOG);};  } 

inline void set_GL_LINE_SMOOTH(bool val)   { if(val){ glEnable(GL_LINE_SMOOTH); } else { glDisable(GL_LINE_SMOOTH);};  } 
inline void set_GL_LOGIC_OP   (bool val)   { if(val){ glEnable(GL_LOGIC_OP); } else { glDisable(GL_LOGIC_OP);};  }	 
  
inline void set_GL_NORMALIZE  (bool val)   { if(val){ glEnable(GL_NORMALIZE); } else { glDisable(GL_NORMALIZE);};  }
	     
inline void set_GL_STENCIL_TEST(bool val)   { if(val){ glEnable(GL_STENCIL_TEST); } else { glDisable(GL_STENCIL_TEST);};  }
 /*
inline void set_xxx  (bool val)   { if(val){ glEnable(xxx); } else { glDisable(xxx);};  }
inline void set_xxx  (bool val)   { if(val){ glEnable(xxx); } else { glDisable(xxx);};  }	
 */
	 


  
  
  
   //-------------------------------------------------------------------------------- 
  } // end ns
 } // end ns
} // end ns

#endif
// end file