#pragma once

#include "BaseApplication.h"
#include "InputHandlerMap.h"

namespace gb
{
	namespace engine_blocks
	{
		class GameApplication : public BaseApplication
		{
		public:
			enum ApplicationState
			{
				GAME,
				MENU,
				CONSOLE
			};
			
			GameApplication(bool enable_console);
			ApplicationState getState() const {return game_input_handler->getState();}
			
		protected:
			bool enable_console;
			InputHandlerMap<ApplicationState> *game_input_handler;
			
			void setupInputHandler();
		};
	}
}
