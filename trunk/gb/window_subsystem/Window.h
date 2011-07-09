#pragma once

#include <vector>
#include <string>

#include <gb/base/IRefCountable.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif
		
namespace gb
{
	namespace window_subsystem
	{

		#ifdef _WIN32
		/**
		 * @ingroup window_subsystem_group
		 * \brief Параметры окна, специфичные для операционной системы
		 */
		struct WindowOSSpecParams
		{
			WindowOSSpecParams()
			{
				hDC = NULL;
				hWnd = NULL;
			}
			
			WindowOSSpecParams(const WindowOSSpecParams &o)
			{
				hDC = o.hDC;
				hWnd = o.hWnd;
			}
			
			WindowOSSpecParams &operator=(const WindowOSSpecParams &o)
			{
				hDC = o.hDC;
				hWnd = o.hWnd;
				return *this;
			}

			HDC hDC;
			HWND	hWnd;
		};
		#else
		/**
		 * @ingroup window_subsystem_group
		 * \brief Параметры окна, специфичные для операционной системы
		 */
		struct WindowOSSpecParams
		{
			WindowOSSpecParams()
			{
				display = NULL;
				window = 0;
			}
			
			WindowOSSpecParams(const WindowOSSpecParams &o)
			{
				display = o.display;
				window = o.window;
			}
			
			WindowOSSpecParams &operator=(const WindowOSSpecParams &o)
			{
				display = o.display;
				window = o.window;
				return *this;
			}

			Display *display;
			::Window window;
		};
		#endif // _WIN32

		/**
		 * @ingroup window_subsystem_group
		 * \brief Параметры окна
		 */
		struct WindowInfo : public WindowOSSpecParams
		{
			WindowInfo()
			{
				width = height = 4;
				x = y = 0;
				is_visible = false;
			}
			
			WindowInfo(const WindowInfo &o)
			{
				*this = o;
			}
			
			WindowInfo &operator = (const WindowInfo &o)
			{
				width = o.width;
				height = o.height;
				x = o.x;
				y = o.y;
				is_visible = o.is_visible;
				title = o.title;
				(WindowOSSpecParams &)*this = o;
				return *this;
			}
			
			/** Задаёт размер */
			WindowInfo &setSize(size_t width, size_t height)
			{
				this->width = width;
				this->height = height;
				return *this;
			}
			
			/** Задаёт положение левого верхнего угла окна */
			WindowInfo &setPosition(int x, int y)
			{
				this->x = x;
				this->y = y;
				return *this;
			}

			size_t	width, height;
			int		x, y;
			bool	is_visible;
			std::string	title;
		};

		class Input;

		/**
		 * @ingroup window_subsystem_group
		 * \brief Интерфейс окна
		 */
		class Window : public base::IRefCountable
		{
		public:
			/** \return Параметры окна */
			virtual const WindowInfo *getWindowInfo() = 0;
			
			/** Изменяет размер окна */
			virtual void setSize(size_t width, size_t height) = 0;
			
			/** Изменяет координаты окна */
			virtual void setPosition(int left, int top) = 0;
			
			/** Изменяет заголовок */
			virtual void setTitle(const std::string &title) = 0;
			
			/** Делает окно видимым/не видимым */
			virtual void show(bool show = true) = 0;
			
			/** Закрывает окно */
			virtual bool close() = 0;
			
			/** Присоединение обработчика ввода */
			virtual	void attachInputHandler(Input *input) = 0;
			
			/** Свигает курсор */
			virtual void setCursorPosition(int x, int y) = 0;
			
			/** Начало рендеринга */
			virtual void startRendering() = 0;
			
			/** Окончание рендеринга */
			virtual void finishRendering() = 0;
			
			/** Делает курсор видимым/не видимым */
			virtual void showCursor(bool v) = 0;
		};

		typedef base::RefCntHolder<Window> PWindow;
	}
}


