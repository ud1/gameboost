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

		class Input
		{
		public:
			virtual bool mouse(MouseMessage msg) {return true;}
			virtual bool kbd(KbdMessage msg) {return true;}
			virtual bool close() {return true;}
			virtual bool reshape() {return true;}
			virtual bool windowMinimized() {return true;}
			virtual bool onAttach(Window *wnd) {return true;}
			virtual bool onDetach() {return true;}
		};

	}
}
