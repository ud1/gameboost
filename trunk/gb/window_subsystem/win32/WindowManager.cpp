#ifdef _WIN32

#include "../Input.h"
#include "../WindowManager.h"
#include "../KeyCodes.h"
#include <gb/base/Logger.h>
#include <gb/base/nullptr.h>
#include <gb/str/UnicodeHelpers.h>
#include <gb/t/clamp.h>

#include <boost/program_options.hpp>

#include <Windows.h>
#include <vector>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL3/gl3.h>

namespace po = boost::program_options;

namespace
{
	const char* window_class_name = "Gameboost_window_class";
	bool is_window_class_registered = false;

	namespace ws = gb::window_subsystem;
	namespace kk = gb::window_subsystem::eKeyCodes;
	using namespace std;

	class WGLWindow;
	typedef vector <WGLWindow *> WindowList;
	WindowList list;

	class WGLWindow : public ws::Window
	{
	public:
		const ws::WindowInfo *getWindowInfo()
		{
			return &info;
		}

		void setSize(size_t width, size_t height)
		{
			tagRECT scrRect = {info.x, info.y, 
				info.x + width, info.y + height};
			AdjustWindowRectEx(&scrRect, window_style, false, window_extended_style);

			info.width = width;
			info.height = height;

			if (is_window_created)
			{
				MoveWindow(info.hWnd, scrRect.left, scrRect.top, 
					scrRect.right - scrRect.left, 
					scrRect.bottom - scrRect.top, FALSE);
			}
		}

		void setPosition(int left, int top)
		{
			tagRECT scr_rect = {left, top, left + info.width, top + info.height};
			AdjustWindowRectEx(&scr_rect, window_style, false, window_extended_style);

			info.x = left;
			info.y = top;

			if (is_window_created)
			{
				MoveWindow(info.hWnd, scr_rect.left, scr_rect.top, 
					scr_rect.right - scr_rect.left, 
					scr_rect.bottom - scr_rect.top, FALSE);
			}
		}

		void setTitle(const std::string &title)
		{
			info.title = title;
			if (is_window_created)
			{
				SetWindowTextW(info.hWnd, gb::str::utf8ToWstring(info.title).c_str());
			}
		}

		void show(bool show)
		{
			if (!is_window_created)
				return;
			info.is_visible = show;
			ShowWindow(info.hWnd, show ? SW_SHOW : SW_HIDE);
		}

		bool close()
		{
			return SendMessage(info.hWnd, WM_CLOSE, 0, 0);
		}

		void attachInputHandler(ws::Input *input_)
		{
			if (input && input != input_)
				input->onDetach();
			input = input_;
			input_->onAttach(this);
		}

		void setCursorPosition(int x, int y)
		{
			if (!info.hWnd)
				return;
			POINT pt;
			pt.x = x;
			pt.y = y;
			ClientToScreen(info.hWnd,&pt);
			SetCursorPos(pt.x, pt.y);
		}

		void startRendering()
		{
			wglMakeCurrent(info.hDC, info.hRC);
		}

		void finishRendering()
		{
			SwapBuffers(info.hDC);
		}

		void showCursor(bool v)
		{
			ShowCursor(v);
		}

		WGLWindow()
		{
			input = nullptr;
			is_window_created = false;
			window_style = WS_OVERLAPPEDWINDOW;
			window_extended_style = WS_EX_APPWINDOW;
		}

		~WGLWindow()
		{
			unsigned int i;
			for (i=0; i<list.size(); i++)
			{
				if (list[i] == this)
				{
					list.erase(list.begin() + i);
					break;
				}
			}
			if (input)
				input->onDetach();
		}

		ws::WindowInfo info;
		bool is_window_created;
		ws::Input *input;
		DWORD	window_style;
		DWORD	window_extended_style;
	};

	bool ChangeScreenResolution (int width, int height, int bitsPerPixel)
	{
		DEVMODE dmScreenSettings;
		ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));
		dmScreenSettings.dmSize = sizeof (DEVMODE);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bitsPerPixel;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			return false;
		}
		return true;
	}

	bool createWin32Window(WGLWindow *wnd)
	{
		tagRECT scrRect = {wnd->info.x, wnd->info.y, 
			wnd->info.x + wnd->info.width, wnd->info.y + wnd->info.height};
		AdjustWindowRectEx(&scrRect, wnd->window_style, false, wnd->window_extended_style);

		wnd->info.hWnd = CreateWindowExW(
			wnd->window_extended_style,
			gb::str::utf8ToWstring(window_class_name).c_str(),
			gb::str::utf8ToWstring(wnd->info.title).c_str(),
			wnd->window_style,
			scrRect.left, scrRect.top,
			scrRect.right - scrRect.left,
			scrRect.bottom - scrRect.top,
			HWND_DESKTOP,
			0,
			GetModuleHandle(NULL),
			wnd);

		if ( !wnd->info.hWnd )
		{
			ERROR_LOG("CreateWindowEx failed");
			return false;
		}

		list.push_back(wnd);
		wnd->is_window_created = true;
		SetWindowTextW(wnd->info.hWnd, gb::str::utf8ToWstring(wnd->info.title).c_str());
		wnd->info.hDC = GetDC(wnd->info.hWnd);

		return true;
	}

	//
	// CWindowManager
	//

	LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		unsigned int i;
		for (i=0; i<list.size(); i++)
		{
			if (list[i]->info.hWnd == hWnd)
				break;
		}

		WGLWindow *window = nullptr;
		if (i == list.size())
		{
			return DefWindowProc (hWnd, msg, wParam, lParam);
		}
		else
		{
			window = list[i];
		}

		ws::KbdMessage kbd_msg;
		ws::MouseMessage mouse_msg;

		switch (msg)
		{
			case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:
					case SC_MONITORPOWER:
					return 0;												
				}
				break;
			}
			break;

			case WM_CREATE:
			break;

			case WM_CLOSE:											
				if (window->input && window->input->close())
					return 0;
				window->info.is_visible = false;
				window->is_window_created = false;
				ReleaseDC(window->info.hWnd, window->info.hDC);
				window->info.hWnd = NULL;
				window->info.hDC = NULL;
			break;

			case WM_SIZE:					
				switch (wParam)
				{									
					case SIZE_MINIMIZED:
						window->info.is_visible = false;
						if (window->input && window->input->windowMinimized())
							return 0;
					break;

					case SIZE_MAXIMIZED:
						window->info.is_visible = true;
						window->info.width = LOWORD(lParam);
						window->info.height = HIWORD(lParam);
						if (window->input && window->input->reshape())
							return 0;
					break;

					case SIZE_RESTORED:									
						window->info.is_visible = true;				
						window->info.width = LOWORD(lParam);
						window->info.height = HIWORD(lParam);
						if (window->input && window->input->reshape())
							return 0;
					break;
				}
			break;	

			case WM_KEYDOWN:
				if (window->input)
				{
					kbd_msg.type = ws::KbdMessage::KEY_DOWN;
					kbd_msg.key = (ws::eKeyCodes::KeyCode) wParam;
					if (window->input->kbd(kbd_msg))
						return 0;
				}
			break;

			case WM_KEYUP:
				if (window->input)
				{
					kbd_msg.type = ws::KbdMessage::KEY_UP;
					kbd_msg.key = (ws::eKeyCodes::KeyCode) wParam;
					if (window->input->kbd(kbd_msg))
						return 0;
				}	
			break;

			case WM_CHAR:
				if (window->input) {
					kbd_msg.type = ws::KbdMessage::KEY_CHAR;
					kbd_msg.ch = (wchar_t) wParam;
					if (window->input->kbd(kbd_msg))
						return 0;
				}
			break;

			case WM_LBUTTONDOWN:
				if (window->input)
				{
					mouse_msg.init(LOWORD(lParam), HIWORD(lParam), ws::MouseMessage::LB_DOWN);
					if (window->input->mouse(mouse_msg))
						return 0;
				}
			break;

			case WM_RBUTTONDOWN:
				if (window->input)
				{
					mouse_msg.init(LOWORD(lParam), HIWORD(lParam), ws::MouseMessage::RB_DOWN);
					if (window->input->mouse(mouse_msg))
						return 0;
				}
			break;

			case WM_LBUTTONUP:
				if (window->input)
				{
					mouse_msg.init(LOWORD(lParam), HIWORD(lParam), ws::MouseMessage::LB_UP);
					if (window->input->mouse(mouse_msg))
						return 0;
				}
			break;

			case WM_RBUTTONUP:
				if (window->input)
				{
					mouse_msg.init(LOWORD(lParam), HIWORD(lParam), ws::MouseMessage::RB_UP);
					if (window->input->mouse(mouse_msg))
						return 0;
				}
			break;

			case WM_MOUSEMOVE:
				if (window->input)
				{
					mouse_msg.init(LOWORD(lParam), HIWORD(lParam), ws::MouseMessage::MOVE);
					if (window->input->mouse(mouse_msg))
						return 0;
				}
			break;

			case WM_QUIT:

			break;
		}

		return DefWindowProc (hWnd, msg, wParam, lParam);

	}

	bool registerWindowClass()
	{
		WNDCLASSEX windowClass;
		ZeroMemory( &windowClass, sizeof( WNDCLASSEX ) );
		windowClass.cbSize = sizeof (WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = (WNDPROC)(windowProc);
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
		windowClass.hCursor	= LoadCursor(NULL, IDC_ARROW);
		windowClass.lpszClassName = window_class_name;
		if (RegisterClassEx (&windowClass) == 0)
		{
			return false;
		}
		return true;
	}

	class WGLWindowManager : public ws::WindowManager
	{
	public:
		static WGLWindowManager *create();

		WGLWindowManager();
		~WGLWindowManager();

		bool init(const std::vector<std::string> &options);
		ws::Window *createWindow(const std::vector<std::string> &params, ws::WindowInfo *info);
		void processMessages();
		void quit();

	protected:
		WGLWindow *createWindow_(const std::vector<std::string> &params, ws::WindowInfo *info, po::variables_map &vm);
		bool initialized;
	};

	WGLWindowManager::WGLWindowManager()
	{
		initialized = false;
	}

	WGLWindowManager::~WGLWindowManager()
	{
		if (is_window_class_registered)
			UnregisterClass (window_class_name, GetModuleHandle(NULL));
	}

	bool setPixelFormatAndMakeCurent(ws::WindowInfo &info, int pixelFormat)
	{
		if (SetPixelFormat (info.hDC, pixelFormat, NULL) == FALSE)
		{
			ERROR_LOG("SetPixelFormat() error");
			return false;
		}

		info.hRC = wglCreateContext(info.hDC);
		if (!info.hRC)
		{
			ERROR_LOG("wglCreateContext() error");
			return false;
		}

		if (wglMakeCurrent(info.hDC, info.hRC) == FALSE)
		{
			ERROR_LOG("wglMakeCurrent() error");
			wglDeleteContext (info.hRC);
			info.hRC = 0;
			return false;
		}

		return true;
	}

	bool initializeGL(WGLWindow *dummy_window)
	{
		ws::WindowInfo *info = &dummy_window->info;

		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize			= sizeof (PIXELFORMATDESCRIPTOR);	
		pfd.nVersion		= 1;
		pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType		= PFD_TYPE_RGBA;
		pfd.cColorBits		= 24;
		pfd.cRedBits		=
			pfd.cRedShift	=
			pfd.cGreenBits	=
			pfd.cGreenShift	=
			pfd.cBlueBits	=
			pfd.cBlueShift	= 0;
		pfd.cAlphaBits		=
			pfd.cAlphaShift	= 0;
		pfd.cAccumBits		= 0;
		pfd.cAccumRedBits	=
			pfd.cAccumGreenBits =
			pfd.cAccumBlueBits	= 
			pfd.cAccumAlphaBits	= 0;

		pfd.cDepthBits		= 16;
		pfd.cStencilBits	= 0;
		pfd.cAuxBuffers		= 0;
		pfd.iLayerType		= 0;
		pfd.bReserved		= 0;
		pfd.dwLayerMask		= 0;
		pfd.dwVisibleMask	= 0;
		pfd.dwDamageMask	= 0;

		int pixelFormat = ChoosePixelFormat (info->hDC, &pfd);
		if (pixelFormat == 0)
		{
			ERROR_LOG("Pixel format not found");
			return false;
		}
		if (!setPixelFormatAndMakeCurent(*info, pixelFormat))
			return FALSE;

		if (glewInit() != GLEW_OK)
		{
			ERROR_LOG("glewInit() error");
			return FALSE;
		}

		return TRUE;
	}

	WGLWindow *WGLWindowManager::createWindow_(const std::vector<std::string> &params, ws::WindowInfo *info, po::variables_map &vm)
	{
		setlocale(LC_ALL, "ru_RU.UTF-8");

		ws::WindowInfo win_info;
		if (info)
			win_info = *info;

		po::options_description desc;
		desc.add_options()
			("width", po::value<size_t>(&win_info.width), "window width")
			("height", po::value<size_t>(&win_info.height), "window height")
			("abs_x", po::value<int>(&win_info.x), "window x coordinate")
			("abs_y", po::value<int>(&win_info.y), "window y coordinate")
			("rel_x", po::value<double>(), "window relative x coordinate in range [0..1]")
			("rel_y", po::value<double>(), "window relative y coordinate in range [0..1]")
			("rel_width", po::value<double>(), "window relative width in range [0..1]")
			("rel_height", po::value<double>(), "window relative height in range [0..1]")
			("gl_version", po::value<int>(), "gl version = 10 * major_version + minor_version")
			("forward_compatible", po::value<bool>(), "if gl_version >= 30, create forward compatible context")
			("title", po::value<std::string>(&win_info.title), "window title")
			;

		po::store(po::command_line_parser(params).options(desc).run(), vm);
		po::notify(vm);

		size_t display_w = GetSystemMetrics(SM_CXSCREEN);
		size_t display_h = GetSystemMetrics(SM_CYSCREEN);

		if (vm.count("rel_x"))
		{
			win_info.x = display_w*vm["rel_x"].as<double>();
		}

		if (vm.count("rel_y"))
		{
			win_info.y = display_h*vm["rel_y"].as<double>();
		}

		if (vm.count("rel_width"))
		{
			win_info.width = display_w*vm["rel_width"].as<double>();
		}

		if (vm.count("rel_height"))
		{
			win_info.height = display_h*vm["rel_height"].as<double>();
		}

		gb::t::clamp(win_info.width, (size_t) 0, display_w);
		gb::t::clamp(win_info.height, (size_t) 0, display_h);

		WGLWindow *wnd = new WGLWindow;
		wnd->info = win_info;

		if (!createWin32Window(wnd))
		{
			ERROR_LOG("createWin32Window() failed");
			delete wnd;
			return nullptr;
		}

		return wnd;
	}

	ws::Window *WGLWindowManager::createWindow(const std::vector<std::string> &params, ws::WindowInfo *info)
	{
		if (!initialized)
			return nullptr;

		po::variables_map vm;
		WGLWindow *result = createWindow_(params, info, vm);
		if (!result)
			return false;

		std::vector<int> attribs;
		attribs.push_back(WGL_SUPPORT_OPENGL_ARB);
		attribs.push_back(GL_TRUE);

		attribs.push_back(WGL_ACCELERATION_ARB);
		attribs.push_back(WGL_FULL_ACCELERATION_ARB);

		attribs.push_back(WGL_DOUBLE_BUFFER_ARB);
		attribs.push_back(GL_TRUE);

		attribs.push_back(WGL_DRAW_TO_WINDOW_ARB);
		attribs.push_back(GL_TRUE);

		attribs.push_back(WGL_DEPTH_BITS_ARB);
		attribs.push_back(24);

		attribs.push_back(WGL_COLOR_BITS_ARB);
		attribs.push_back(32);

		attribs.push_back(WGL_ALPHA_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_RED_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_GREEN_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_BLUE_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_STENCIL_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_STENCIL_BITS_ARB);
		attribs.push_back(8);

		attribs.push_back(WGL_ACCUM_BITS_ARB);
		attribs.push_back(0);

		int gl_version = 30;
		if (vm.count("gl_version"))
			gl_version = vm["gl_version"].as<int>();

		attribs.push_back(WGL_CONTEXT_MAJOR_VERSION_ARB);
		attribs.push_back(gl_version/10);

		attribs.push_back(WGL_CONTEXT_MINOR_VERSION_ARB);
		attribs.push_back(gl_version%10);

		bool forward_compatible = true;
		if (vm.count("forward_compatible"))
			forward_compatible = vm["forward_compatible"].as<bool>();

		if (gl_version >= 30 && forward_compatible)
		{
			attribs.push_back(WGL_CONTEXT_FLAGS_ARB);
			attribs.push_back(WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB);
		}

		attribs.push_back(0);
		attribs.push_back(0);

		result->info.hRC = wglCreateContextAttribsARB(result->info.hDC, 0, &attribs[0]);

		if (!result->info.hRC)
		{
			ERROR_LOG("wglCreateContextAttribsARB() error");
			delete result;
			return nullptr;
		}

		return result;
	}

	bool WGLWindowManager::init(const std::vector<std::string> &options)
	{
		if (initialized)
			return true;

		if ( !is_window_class_registered )
		{
			if ( !registerWindowClass() )
			{
				ERROR_LOG("RegisterClassEx Failed!");
				return false;
			}
		}
		is_window_class_registered = true;

		WGLWindow *dummy_window = createWindow_(std::vector<std::string>(), nullptr, po::variables_map());
		if (!dummy_window)
		{
			ERROR_LOG("create dummy window failed");
			return false;
		}

		if (!initializeGL(dummy_window))
		{
			ERROR_LOG("OpenGL initialization failed");
			delete dummy_window;
			return false;
		}
		delete dummy_window;
		initialized = true;
		return true;
	}

	void WGLWindowManager::processMessages()
	{
		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage (&msg);
		}
	}
};

void WGLWindowManager::quit() {}

namespace gb
{
	namespace window_subsystem
	{
		WindowManager *createWindowManager(const char *)
		{
			return new WGLWindowManager;
		}
	}
}

#endif