#pragma once

#include "KeyCodes.h"


namespace gb
{
	namespace window_subsystem
	{
		/**
		 * @ingroup window_subsystem_group
		 * \brief Сообщение от мыши
		 */
		struct MouseMessage
		{
			/** Тип сообщения */
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
			
			/** Координаты мыши */
			short x, y;

			void init(short x_, short y_, Type type_)
			{
				x = x_;
				y = y_;
				type = type_;
			}
		};

		/**
		 * @ingroup window_subsystem_group
		 * \brief Сообщение от клавиатуры
		 */
		struct KbdMessage
		{
			/** Тип сообщения */
			enum Type
			{
				KEY_DOWN,
				KEY_UP,
				KEY_CHAR
			} type;
			
			union
			{
				/** Код клавиши */
				eKeyCodes::KeyCode key;
				/** Символ */
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
		 * @ingroup window_subsystem_group
		 * \brief Обработчик ввода.
		 * 
		 * Большинство функций возвращают bool'еаново значение,
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
			/** Вызывается при приходе сообщений мыши */
			virtual bool mouse(MouseMessage msg) {return false;}
			
			/** Вызывается при приходе сообщений клавиатуры */
			virtual bool kbd(KbdMessage msg) {return false;}
			
			/** Вызывается при попытке закрытия окна */
			virtual bool close() {return false;}
			
			/** Вызывается при изменении размера окна */
			virtual bool reshape() {return false;}
			
			/** Вызывается, если окно было свёрнуто */
			virtual bool windowMinimized() {return false;}
			
			/** Вызывается при присоединении данного обработчика к окну */
			virtual void onAttach(Window *wnd) {}
			
			/** Вызывается при отсоединении данного обработчика к окну */
			virtual void onDetach() {}
		};

	}
}
