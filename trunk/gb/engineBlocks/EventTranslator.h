#pragma once

#include <gb/windowSubsystem/Input.h>
#include <map>
#include <boost/function.hpp>

namespace gb
{
	namespace engine_blocks
	{
		/**
		 * EventTranslator позволяет вызывать пользовательские функции
		 * при приходе сообщение о нажатии или отпускании клавиши
		 */
		class EventTranslator : public window_subsystem::Input
		{
		public:
			typedef boost::function<void (bool /**key_down*/)> KeyEvent;
			
			void addKeyEventCallback(window_subsystem::eKeyCodes::KeyCode key, const KeyEvent &event);
			bool kbd(window_subsystem::KbdMessage msg);
			
		protected:
			typedef std::multimap<window_subsystem::eKeyCodes::KeyCode, KeyEvent> KeyEventMap;
			KeyEventMap key_event_map;
		};
	}
}
