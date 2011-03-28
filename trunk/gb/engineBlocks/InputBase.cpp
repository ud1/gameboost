#include "InputBase.h"

#include <algorithm>

namespace gb
{
	namespace engine_blocks
	{
		using namespace window_subsystem;
		using namespace math;
		
		InputBase::InputBase()
		{
			reset();
		}
		
		bool InputBase::mouse(MouseMessage msg)
		{
			switch (msg.type)
			{
				case MouseMessage::LB_DOWN:
					mouse_buttons_pressed[MB_LEFT]=true;
					break;
				case MouseMessage::RB_DOWN:
					mouse_buttons_pressed[MB_RIGHT]=true;
					break;
				case MouseMessage::LB_UP:
					mouse_buttons_pressed[MB_LEFT]=false;
					break;
				case MouseMessage::RB_UP:
					mouse_buttons_pressed[MB_RIGHT]=false;
					break;
				case MouseMessage::MOVE:
					mouse_pos = vec2((float)msg.x,(float)msg.y);
					break;
			}
			return true;
		}
		
		bool InputBase::kbd(KbdMessage msg)
		{
			if (msg.key >= 0 && msg.key <= 255)
			{
				if (msg.type == KbdMessage::KEY_DOWN)
				{
					keys_pressed[msg.key] = true;
				}
				else if (msg.type == KbdMessage::KEY_UP)
				{
					keys_pressed[msg.key] = false;
				}
			} 
			return false;
		}
		
		void InputBase::onAttach(Window *wnd)
		{
			window = wnd;
		}
		
		void InputBase::onDetach()
		{
			reset();
		}
		
		void InputBase::mouseToCenter()
		{
			if (!window)
				return;
			const WindowInfo *info = window->getWindowInfo();
			int x = info->width/2;
			int y = info->height/2;
			window_center = vec2((float)x, (float)y);
			mouse_pos = vec2(window_center);
			window->setCursorPosition(x, y); 
		}
		
		void InputBase::reset()
		{
			std::fill_n(keys_pressed, sizeof(keys_pressed)/sizeof(keys_pressed[0]), false);
			std::fill_n(mouse_buttons_pressed, sizeof(mouse_buttons_pressed)/sizeof(mouse_buttons_pressed[0]), false);
		}
	}
}