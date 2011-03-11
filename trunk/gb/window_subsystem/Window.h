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
		struct WindowOSSpecParams
		{
			WindowOSSpecParams()
			{
				display = NULL;
				window = NULL;
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
			
			WindowInfo &setSize(size_t width, size_t height)
			{
				this->width = width;
				this->height = height;
				return *this;
			}
			
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

		class Window : public base::IRefCountable
		{
		public:
			virtual const WindowInfo *getWindowInfo() = 0;
			virtual void setSize(size_t width, size_t height) = 0;
			virtual void setPosition(int left, int top) = 0;
			virtual void setTitle(const std::string &title) = 0;
			virtual void show(bool show = true) = 0;
			virtual bool close() = 0;
			virtual	void attachInputHandler(Input *input) = 0;
			virtual void setCursorPosition(int x, int y) = 0;
			virtual void startRendering() = 0;
			virtual void finishRendering() = 0;
		};

	}
}


