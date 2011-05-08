#pragma once
#include "InputBase.h"
#include <gb/base/Camera.h>
#include <gb/math/math.h>
#include <gb/window_subsystem/KeyCodes.h>

namespace gb
{
	namespace engine_blocks
	{
		
		class CameraInput : public InputBase, public base::Camera
		{
		public:
			enum MoveType
			{
				LEFT, RIGHT,
				FORWARD, BACKWARD,
				UPWARD, DOWNWARD,
				COUNT
			};
			CameraInput();
			
			bool mouse(window_subsystem::MouseMessage msg);
			void onAttach(window_subsystem::Window *wnd);
			void onDetach();
			
			void updatePosition(float delta_time);
			
			void addKeyBinding(window_subsystem::eKeyCodes::KeyCode, MoveType m);
			
			float mouse_sens;
			bool mouse_invert;
			math::vec3 velocity;
			float up_accel;
			float down_accel;
			
		private:
			bool skip_mouse_move;
			std::vector<window_subsystem::eKeyCodes::KeyCode> key_bindings[COUNT];
		};
		
	}
}