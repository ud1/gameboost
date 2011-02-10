#include "base/Timer.h"

namespace gb
{
	namespace base
	{

		//----------------------------------------------------------------------

		FPSTimer::FPSTimer()
		{
			time = 0.0;
			dt = 0.0f;
			adt = 0.0f;
			fps = 0.0f;
			afps = 0.0f;
			frames = 0;
		}

		//----------------------------------------------------------------------

		float FPSTimer::finishTiming()
		{

			double elaps = timeElapsed();
			dt = float(elaps);

			if (elaps > 1e-10) {
				fps	= float(1.0 / elaps);
			} else {
				fps = 0.0f;
			}

			time += elaps;
			frames ++;

			if (time > 1.0) {
				afps = float(double(frames) / time);
				time = 0.0;
				frames = 0;
			}
			adt = adt * 0.5f + dt * 0.5f;
			return fps;
		}

		//----------------------------------------------------------------------
		
		float getDt() const {
			return dt;
		}
		
		//----------------------------------------------------------------------
		
		float getAverageDt() const
		{
			return adt;
		}
		
		//----------------------------------------------------------------------
		
		float getFPS() const
		{
			return fps;
		}
		
		//----------------------------------------------------------------------
		
		float getAverageFPS() const 
		{
			return afps
		}
		
		//----------------------------------------------------------------------
		
	}

}
