#include "EventTranslator.h"

namespace gb
{
	namespace engine_blocks
	{
		using namespace window_subsystem;
		
		void EventTranslator::addKeyEventCallback(eKeyCodes::KeyCode key, const KeyEvent &event)
		{
			key_event_map.insert(std::make_pair(key, event));
		}
		
		bool EventTranslator::kbd(KbdMessage msg)
		{
			if (msg.type == KbdMessage::KEY_DOWN || msg.type == KbdMessage::KEY_UP)
			{
				std::pair<KeyEventMap::iterator, KeyEventMap::iterator> events = key_event_map.equal_range(msg.key);
				for (KeyEventMap::iterator it = events.first; it != events.second; ++it)
				{
					it->second(msg.type == KbdMessage::KEY_DOWN);
				}
				return true;
			}
			return false;
		}
	}
}