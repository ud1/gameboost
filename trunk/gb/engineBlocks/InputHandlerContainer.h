#pragma once

#include <gb/window_subsystem/Input.h>
#include <map>
#include <cstdlib>
#include <cassert>

namespace gb
{
	namespace engine_blocks
	{
		/**
		 * InputHandlerContainer позволяет хранить в себе
		 * несколько обработчиков ввода и переключаться между ними
		 * по вызову функции setState().
		 */
		template<typename State>
		class InputHandlerContainer : public window_subsystem::Input
		{
		public:
			
			InputHandlerContainer(State initial_state) : state(initial_state) {};
			
			void addInputHandler(State state, window_subsystem::Input *handler)
			{
				bool inserted = handlers.insert(std::make_pair(state, handler)).second;
				assert(inserted || "Input handler already exists");
				
				if (state == getState() && window)
					handler->onAttach(window);
			}
			
			void setState(State new_state)
			{
				if (state != new_state)
					resetState(new_state);
			}
			
			State getState() const {return state;}
			
			void onAttach(window_subsystem::Window *wnd)
			{
				if (window != wnd)
				{
					window = wnd;
					resetState(state);
				}
			}
			
			bool mouse(window_subsystem::MouseMessage msg)
			{
				Handler *handler;
				if (handler = getHandler(state))
					return handler->mouse(msg);
				return false;
			}
			
			bool kbd(window_subsystem::KbdMessage msg)
			{
				Handler *handler;
				if (handler = getHandler(state))
					return handler->kbd(msg);
				return false;
			}
			
			bool close()
			{
				Handler *handler;
				if (handler = getHandler(state))
					return handler->close();
				return false;
			}
			
			bool reshape()
			{
				Handler *handler;
				if (handler = getHandler(state))
					return handler->reshape();
				return false;
			}
			
			bool windowMinimized()
			{
				Handler *handler;
				if (handler = getHandler(state))
					return handler->windowMinimized();
				return false;
			}
			
		private:
			typedef window_subsystem::Input Handler;
			typedef std::map<State, Handler *> Handlers;
			Handlers handlers;
			
			State state;
			
			window_subsystem::PWindow window;
			
			Handler *getHandler(State state)
			{
				typename Handlers::iterator it = handlers.find(state);
				if (it != handlers.end())
					return it->second;
				
				return NULL;
			}
			
			void resetState(State new_state)
			{
				Handler *handler;
				if (handler = getHandler(state))
					handler->onDetach();
				
				if ((handler = getHandler(new_state)) && window)
					handler->onAttach(window);
				
				state = new_state;
			}
		};
	}
}
