#pragma once

#include "KeyCodes.h"


namespace gb
{
	namespace window_subsystem
	{
		
		struct MouseMessage
		{
			enum Type
			{
				LB_DOWN,
				LB_UP,
				RB_DOWN,
				RB_UP,
				SCROLL_UP,
				SCROLL_DOWN,
				MOVE,
				CLICK
			} type;
			
			short x, y;

			void init(short x_, short y_, Type type_)
			{
				x = x_;
				y = y_;
				type = type_;
			}
		};

		struct KbdMessage
		{
			enum Type
			{
				KEY_DOWN,
				KEY_UP,
				KEY_CHAR,
			} type;
			
			union
			{
				eKeyCodes::KeyCode key;
				wchar_t ch;
			};

			void init(Type type_, eKeyCodes::KeyCode key_)
			{
				type = type_;
				key = key_;
			}
			
			void init(Type type_, wchar_t ch_)
			{
				type = type_;
				ch = ch_;
			}
		};

		class Window;

		class  Input
		{
		public:
			virtual bool mouse(MouseMessage msg) = 0;
			virtual bool kbd(KbdMessage msg) = 0;
			virtual bool close() = 0;
			virtual bool reshape() = 0;
			virtual bool windowMinimized() = 0;
			virtual bool onAttach(Window *wnd) = 0;
			virtual bool onDetach() = 0;
		};

	}
}
