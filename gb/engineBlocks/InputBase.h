#pragma once

#include <gb/window_subsystem/Input.h>
#include <gb/window_subsystem/Window.h>
#include <gb/math/math.h>
#include <gb/window_subsystem/KeyCodes.h>

namespace gb
{
	namespace engine_blocks
	{
		
		class InputBase : public window_subsystem::Input
		{
		public:
			enum MouseButton
			{
				MB_LEFT,
				MB_RIGHT,
				
				MB_COUNT
			};
			
			InputBase();
			bool mouse(window_subsystem::MouseMessage msg);
			bool kbd(window_subsystem::KbdMessage msg);
			void onAttach(window_subsystem::Window *wnd);
			void onDetach();
			void mouseToCenter();
			
			bool check_key(window_subsystem::eKeyCodes::KeyCode key) const {return keys_pressed[key];}
			bool check_mouse_button(MouseButton btn) const {return mouse_buttons_pressed[btn];}
			math::vec2 getMousePosition() const {return mouse_pos;}
			
		protected:
			math::vec2 window_center;
			math::vec2 mouse_pos;
			
		private:
			bool keys_pressed[256];
			bool mouse_buttons_pressed[MB_COUNT];
			window_subsystem::PWindow window;
			
			void reset();
		};
		
	}
}
