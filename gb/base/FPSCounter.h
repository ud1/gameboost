//------------------------------------------------------------------------------
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

#include "gb/base/Timer.h"

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
		//
		// class FPSCounter
		//
		//----------------------------------------------------------------------
		
		class FPSCounter
		{

			int frames;
			double time;
			float dt;
			float adt;
			float fps;
			float afps;
			
			Timer timer;
			
		public:
			
			FPSCounter();
			
			void start();
			void finish();
			
			float getDt() const;
			float getAverageDt() const;
			float getFPS() const;
			float getAverageFPS() const;
			
		};

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
