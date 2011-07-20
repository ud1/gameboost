/**	 \file
  \brief  “уман.
 *
 *
 *
 *
 *
 *
 **/


#pragma once


#include "../color/color3.h"
#include <assert.h>

namespace gb
{

	namespace graphics
	{


		class Fog {
		public:
	
		/*
		GL_FOG_MODE
		params is a single integer or floating-point value that specifies the equation to be used to compute the fog blend factor, f . Three symbolic constants are accepted: GL_LINEAR, GL_EXP, and GL_EXP2. The equations corresponding to these symbolic constants are defined below. The initial fog mode is GL_EXP.
		GL_FOG_DENSITY
		params is a single integer or floating-point value that specifies density , the fog density used in both exponential fog equations. Only nonnegative densities are accepted. The initial fog density is 1.
		GL_FOG_START
		params is a single integer or floating-point value that specifies start , the near distance used in the linear fog equation. The initial near distance is 0.
		GL_FOG_END
		params is a single integer or floating-point value that specifies end , the far distance used in the linear fog equation. The initial far distance is 1.
		GL_FOG_INDEX
		params is a single integer or floating-point value that specifies i f , the fog color index. The initial fog index is 0.
		GL_FOG_COLOR
		*/
	
			struct fog_mode_e 
			{
				enum e
				{
					linear,
					exp, 
					exp2
				};
			
				static std::string tostr(const e value);
				static e fromstr(const std::string&) throw();
			
			
			};
	
			struct fog_data 
			{
		
				bool enabled;
				fog_mode_e mode;
		
				float start;
				float end;
				gb::color::color4<float> color;
			
			
			
				/*
				BOOL bFogEnable;
				D3DFOGMODE fogmode;
				FLOAT fFOGSTART;
				FLOAT fFOGEND;
				FLOAT fFOGDENSITY;

				BOOL bRANGEFOGENABLE;
				D3DFOGMODE fogVertexMode;
				D3DCOLOR fogColor;
			*/
		
		
		
				fog_data() { memset( &enabled, 0, sizeof(fog_data) ); }
			};

			enum type_e
			{

			undefined = 0,

			cxzxcczxc,
			czxczxczxczxc  // ?????



			};





			// Fog() {}
			~Fog() {}


			//! устанавливает состо€ние тумана в рендер устройство. ѕрежнее состо€ние сохран€етс€.
			virtual void begin() =0;

			//! завершение состо€ни€ тумана. ¬осстановление прежнего состо€ни€.
			virtual void end() =0;
		
		
			inline operator fog_data() const 
			{
				return _fog_data;
			}
		
			inline void operator = (const fog_data& fd)
			{
				_fog_data = fd;
			}

		
		protected:
			fog_data  _fog_data;

		};


	}
}

