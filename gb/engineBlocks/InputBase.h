#pragma once

#include <gb/windowSubsystem/Input.h>
#include <gb/windowSubsystem/Window.h>
#include <gb/math/math.h>
#include <gb/windowSubsystem/KeyCodes.h>

namespace gb
{
	namespace engine_blocks
	{
		
		class InputBase : public window_subsystem::Input
		{
		public:
			enum MouseButton
			{
				GB_MB_LEFT,
				GB_MB_RIGHT,
				
				GB_MB_COUNT
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
			window_subsystem::PWindow window;
			
		private:
			bool keys_pressed[256];
			bool mouse_buttons_pressed[GB_MB_COUNT];
			
			void reset();
		};
		
	}
}
