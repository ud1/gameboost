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
				KEY_CHAR
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

		/**
		 * Обработчик ввода. Большинство функций возвращают bool'еаново значение,
		 * которое показывает, было ли данное сообщение обработано
		 * или нет. В случае, если возвращаемое значение - false, то
		 * будет выполнен стандартный обработчик оконной системы. Например,
		 * чтобы предотвратить закрытие окна достаточно чтобы функция close()
		 * возвращала true.
		 */
		class Input
		{
		public:
			virtual ~Input() {}
			virtual bool mouse(MouseMessage msg) {return false;}
			virtual bool kbd(KbdMessage msg) {return false;}
			virtual bool close() {return false;}
			virtual bool reshape() {return false;}
			virtual bool windowMinimized() {return false;}
			virtual void onAttach(Window *wnd) {}
			virtual void onDetach() {}
		};

	}
}
