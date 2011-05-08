#include "CameraInput.h"
#include <cfloat>

namespace gb
{
	namespace engine_blocks
	{
		using namespace window_subsystem;
		using namespace math;
		using namespace window_subsystem::eKeyCodes;
		
		CameraInput::CameraInput()
		{
			mouse_sens = 0.01;
			mouse_invert = false;
			skip_mouse_move = false;
			velocity = vec3(0.0f, 0.0f, 0.0f);
			up_accel = 0.5f;
			down_accel = 1.0f;
		}
		
		bool CameraInput::mouse(MouseMessage msg)
		{
			InputBase::mouse(msg);
			
			if (msg.type == MouseMessage::MOVE)
			{
				if (skip_mouse_move)
				{
					skip_mouse_move = false;
					return true;
				}
				
				vec2 mouse_delta = mouse_pos - window_center;
				if (length(mouse_delta) > 0.0f)
				{
					mouse_delta *= mouse_sens;
					if (mouse_invert)
						mouse_delta.y = -mouse_delta.y;
					
					turn(0.0f, -mouse_delta.y, -mouse_delta.x);
					skip_mouse_move = true;
					mouseToCenter();
				}
			}
			return true;
		}
		
		void CameraInput::onAttach(window_subsystem::Window *wnd)
		{
			InputBase::onAttach(wnd);
			
			skip_mouse_move = true;
			mouseToCenter();
			wnd->showCursor(false);
		}
		
		void CameraInput::onDetach()
		{
			window->showCursor(true);
		}
		
		void CameraInput::updatePosition(float delta_time)
		{
			if (delta_time <= FLT_MIN)
				return;
			
			vec3 accel = vec3(0.0f, 0.0f, 0.0f);
			
			const vec3 dirs[COUNT] = {
				vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
				vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
				vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)
			};
			
			for (int m = 0; m < COUNT; ++m)
			{
				float v = 0.0f;
				for (int i = 0; i < key_bindings[m].size(); ++i)
					if (check_key(key_bindings[m][i]))
						v = 1.0f;
				accel += dirs[m]*v;
			}
			
			move(velocity*delta_time);
			
			if (dot(accel, accel) > FLT_MIN)
			{
				velocity += normalize(accel) * delta_time * up_accel;
			}
			else
			{
				if (length(velocity) < delta_time*down_accel)
					velocity = vec3(0.0f, 0.0f, 0.0f);
				else velocity -= normalize(velocity) * delta_time * down_accel;
			}
		}
		
		void CameraInput::addKeyBinding(window_subsystem::eKeyCodes::KeyCode k, MoveType m)
		{
			key_bindings[m].push_back(k);
		}
	}
}