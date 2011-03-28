#pragma once

#include "InputHandlerContainer.h"

#include <map>
#include <utility>

namespace gb
{
	namespace engine_blocks
	{
		/**
		 * InputHandlerMap расширяет возможности InputHandlerContainer
		 * позволяя переключаться между обработчиками ввода
		 * с помощью нажатий клавиш.
		 */
		template <typename State>
		class InputHandlerMap : public InputHandlerContainer<State>
		{
		public:
			typedef InputHandlerContainer<State> Parent;
			
			InputHandlerMap(State initial_state) : Parent(initial_state) {}
			
			void addTransition(window_subsystem::eKeyCodes::KeyCode key, State from, State to)
			{
				transitions.insert(std::make_pair(std::make_pair(key, from), to));
			}
			
			bool kbd(window_subsystem::KbdMessage msg)
			{
				if (msg.type == window_subsystem::KbdMessage::KEY_DOWN)
				{
					typename Transitions::iterator it = transitions.find(std::make_pair(msg.key, Parent::getState()));
					if (it != transitions.end())
					{
						setState(it->second);
						return true;
					}
				}
				
				return InputHandlerContainer<State>::kbd(msg);
			}
			
		private:
			typedef std::pair<window_subsystem::eKeyCodes::KeyCode, State> Condition;
			typedef std::map<Condition, State> Transitions;
			Transitions transitions;
		};
	}
}