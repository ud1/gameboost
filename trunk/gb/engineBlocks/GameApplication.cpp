#include "GameApplication.h"


namespace gb
{
	namespace engine_blocks
	{
		using namespace window_subsystem;
		
		GameApplication::GameApplication(bool enable_console_)
		{
			enable_console = enable_console_;
		}
		
		void GameApplication::setupInputHandler()
		{
			struct GameInputHandler : public InputHandlerMap<ApplicationState>
			{
				typedef InputHandlerMap<ApplicationState> Parent;
				GameInputHandler(GameApplication *app) : Parent(MENU), app_handler(app) {}
				bool close() {return app_handler.close();}
				BaseApplicationInputHandler app_handler;
			};
			
			input = game_input_handler = new GameInputHandler(this);
			
			game_input_handler->addTransition(eKeyCodes::KEY_ESCAPE, GAME, MENU);
			game_input_handler->addTransition(eKeyCodes::KEY_ESCAPE, MENU, GAME);
			
			if (enable_console)
			{
				game_input_handler->addTransition(eKeyCodes::KEY_TILDE, GAME, CONSOLE);
				game_input_handler->addTransition(eKeyCodes::KEY_ESCAPE, CONSOLE, GAME);
				game_input_handler->addTransition(eKeyCodes::KEY_TILDE, CONSOLE, MENU);
				game_input_handler->addTransition(eKeyCodes::KEY_TILDE, MENU, CONSOLE);
			}
		}
	}
}