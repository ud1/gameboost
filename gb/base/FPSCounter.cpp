﻿//------------------------------------------------------------------------------
//
// GameBoost
//
// copyright:	(c) 2011 GameDev.ru
// authors:		Alexey Egorov (FadeToBlack aka EvilSpirit) anandamide@mail.ru
//
// url:			http://gameboost.googlecode.com/
//				http://www.gamedev.ru/community/gameboost
//
//------------------------------------------------------------------------------

#include <gb/base/FPSCounter.h>

//------------------------------------------------------------------------------
//
// namespace gb
//
//------------------------------------------------------------------------------

namespace gb
{

	//--------------------------------------------------------------------------
	//
	// namespace base
	//
	//--------------------------------------------------------------------------
	
	namespace base
	{

		//----------------------------------------------------------------------
		
		FPSCounter::FPSCounter()
		{
			time = 0.0;
			dt = 0.0f;
			adt = 0.0f;
			fps = 0.0f;
			afps = 0.0f;
			frames = 0;
		}

		//----------------------------------------------------------------------

		void FPSCounter::start()
		{
			timer.startTiming();
		}
		
		//----------------------------------------------------------------------

		float FPSCounter::finish()
		{

			double elaps = timer.timeElapsed();
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
		
		float FPSCounter::getDt() const
		{
			return dt;
		}
		
		//----------------------------------------------------------------------
		
		float FPSCounter::getAverageDt() const
		{
			return adt;
		}
		
		//----------------------------------------------------------------------
		
		float FPSCounter::getFPS() const
		{
			return fps;
		}
		
		//----------------------------------------------------------------------
		
		float FPSCounter::getAverageFPS() const 
		{
			return afps;
		}
		
		//----------------------------------------------------------------------
		
	}

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
