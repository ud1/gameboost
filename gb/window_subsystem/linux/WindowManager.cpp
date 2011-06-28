#ifndef _WIN32

#include <unistd.h>

#include <GL/glew.h>
#include <GL3/gl3.h>

#include <GL/glx.h>

#include <boost/program_options.hpp>
#include <boost/scope_exit.hpp>

#include <X11/cursorfont.h>

#include <cassert>
#include <map>
#include <vector>

#include "../Input.h"
#include "../WindowManager.h"
#include "../KeyCodes.h"
#include <gb/base/Logger.h>
#include <gb/t/clamp.h>

namespace po = boost::program_options;

namespace
{
	namespace ws = gb::window_subsystem;
	namespace kk = gb::window_subsystem::eKeyCodes;
	
	class CGLXWindow : public ws::Window
	{
	public:
		ws::WindowInfo info;
		GLXContext ctx;
		Colormap cmap;
		
		CGLXWindow(const ws::WindowInfo &i)
		{
			windowExist = true;
			info = i;
			registerWindow(info.window, this);
			input = NULL;
			last_release_event_set = false;
			
			delete_window_protocol = XInternAtom (info.display, "WM_DELETE_WINDOW", True);
			wm_protocols = XInternAtom (info.display, "WM_PROTOCOLS", True);
			XSetWMProtocols(info.display, info.window, &delete_window_protocol, 1);
			
			initializeKeyCodesTable();
			
			xim = NULL;
			xic = NULL;
		}
		
		~CGLXWindow()
		{
			destroyWindow();
		}
		
		const ws::WindowInfo *getWindowInfo()
		{
			return &info;
		}
		
		void setSize(size_t width, size_t height)
		{
			if (!windowExist)
				return;
			
			XResizeWindow(info.display, info.window, width, height);
		}
		
		void setPosition(int left, int top)
		{
			if (!windowExist)
				return;
			
			XMoveWindow(info.display, info.window, left, top);
		}
		
		void setTitle(const std::string &title)
		{
			if (!windowExist)
				return;
			
			XStoreName(info.display, info.window, title.c_str());
		}
		
		void show(bool show_ = true)
		{
			if (!windowExist)
				return;
			
			info.is_visible = show_;
			if (show_)
			{
				XMapWindow(info.display, info.window);
			}
			else
			{
				XUnmapWindow(info.display, info.window);
			}
		}
		
		bool close()
		{
			if (!windowExist)
				return true;
			
			if (!input || !input->close())
			{
				destroyWindow();
				return false;
			}
			return true;
		}
		
		void attachInputHandler(ws::Input *input_)
		{
			if (input)
				input->onDetach();
			
			input = input_;
			
			if (input)
				input->onAttach(this);
		}
		
		void setCursorPosition(int x, int y)
		{
			if (!windowExist)
				return;
			
			XWarpPointer(info.display, 0, info.window, 0, 0, 0, 0, x, y);
		}
		
		void startRendering()
		{
			if (!windowExist)
				return;
			
			glXMakeCurrent(info.display, info.window, ctx);
		}
		
		void finishRendering()
		{
			if (!windowExist)
				return;
			
			glXSwapBuffers(info.display, info.window);
		}

		static bool event_s(::Window w, const XEvent &e)
		{
			Windows::iterator it = windows.find(w);
			if (it != windows.end()) {
				return it->second->event(e);
			}
		}
		
		static bool flush_s()
		{
			Windows::iterator it = windows.begin();
			for (; it != windows.end(); ++it)
			{
				return it->second->flush();
			}
		}
		
		virtual void showCursor(bool v) 
		{
			if (!v)
			{
				Cursor invisibleCursor;
				Pixmap bitmapNoData;
				XColor black;
				static char noData[] = { 0,0,0,0,0,0,0,0 };
				black.red = black.green = black.blue = 0;

				bitmapNoData = XCreateBitmapFromData(info.display, info.window, noData, 8, 8);
				invisibleCursor = XCreatePixmapCursor(info.display, bitmapNoData, bitmapNoData, 
													&black, &black, 0, 0);
				XDefineCursor(info.display, info.window, invisibleCursor);
				XFreeCursor(info.display, invisibleCursor);
			}
			else
			{
				Cursor cursor;
				cursor=XCreateFontCursor(info.display, XC_left_ptr);
				XDefineCursor(info.display, info.window, cursor);
				XFreeCursor(info.display, cursor);
			}
		}
		
	private:
		typedef std::map< ::Window, CGLXWindow *> Windows;
		static Windows windows;
		static void registerWindow(::Window w, CGLXWindow *pw)
		{
			windows[w] = pw;
		}
		
		static void unregisterWindow(::Window w)
		{
			windows.erase(w);
		}
		
		bool flush()
		{
			ws::KbdMessage kbd;
			if (last_release_event_set)
			{
				last_release_event_set = false;
				if (input)
				{
					kbd.init(ws::KbdMessage::KEY_UP, convertKey(last_release_event.keycode));
					return input->kbd(kbd);
				}
			}
		}
		
		bool event(const XEvent &e)
		{
			if (!input)
				return false;
		
			ws::MouseMessage ms;
			switch (e.type)
			{
				case ButtonPress:
				case ButtonRelease:
					ms.x = e.xbutton.x;
					ms.y = e.xbutton.y;
					if (e.xbutton.type == ButtonPress)
					{
						switch (e.xbutton.button)
						{
							case Button1:
								ms.type = ws::MouseMessage::LB_DOWN;
								break;
							case Button3:
								ms.type = ws::MouseMessage::RB_DOWN;
								break;
							case Button4:
								ms.type = ws::MouseMessage::SCROLL_UP;
								break;
							case Button5:
								ms.type = ws::MouseMessage::SCROLL_DOWN;
								break;
						}
					}
					else if (e.xbutton.type == ButtonRelease)
					{
						printf("mouse release %d\n", e.xbutton.button);
						switch (e.xbutton.button)
						{
							case Button1:
								ms.type = ws::MouseMessage::LB_UP;
								break;
							case Button3:
								ms.type = ws::MouseMessage::RB_UP;
								break;
						}
					}
					if (input)
						return input->mouse(ms);
					return true;
				case MotionNotify:
					ms.init(e.xmotion.x, e.xmotion.y, ws::MouseMessage::MOVE);
					if (input)
						return input->mouse(ms);
					return true;
				case KeyPress:
					return keyPress(e.xkey);
				case KeyRelease:
					return keyRelease(e.xkey);
				case ConfigureNotify:
					info.width = e.xconfigure.width;
					info.height = e.xconfigure.height;
					if (input)
						return input->reshape();
					return true;
				case ClientMessage:
					if (e.xclient.message_type == wm_protocols)
					{
						if (e.xclient.data.l[0] == delete_window_protocol)
						{
							return close();
						}
					}
			}
			
			return true;
		}
		
		bool keyPress(const XKeyPressedEvent &e)
		{
			if (!xim)
				xim = XOpenIM (info.display, 0, 0, 0);
			
			if (!xic)
				xic = XCreateIC (xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
								XNClientWindow, e.window, NULL);
			if (!xic)
			{
				return false;
			}
			
			wchar_t str[16];
			kk::KeyCode keysym;
			KeySym temp;
			Status status;
			XKeyPressedEvent ev = e;
			int len = XwcLookupString(xic, &ev, str, 16, &temp, &status);
			keysym = convertKey(e.keycode);

			switch (status)
			{
				case XLookupNone:
					return false;
				case XLookupKeySym:
					return keyDown(keysym, e);
				case XLookupChars:
					charInput(str, len);
					return true;
				case XLookupBoth:
					charInput(str, len);
					return keyDown(keysym, e);
				case XBufferOverflow:
					// WTF???
					assert(0);
					break;
			}
			return false;
		}
		
		bool keyRelease(const XKeyReleasedEvent &e)
		{
			if (last_release_event_set)
				flush();
			last_release_event = e;
			last_release_event_set = true;
			return true;
		}
		
		bool keyDown(KeyCode key, const XKeyPressedEvent &e)
		{
			if (last_release_event_set && e.keycode == last_release_event.keycode && e.time == last_release_event.time)
			{
				last_release_event_set = false;
				return false;
			}
			ws::KbdMessage kbd;
			kbd.init(ws::KbdMessage::KEY_DOWN, key);
			if (input)
				return input->kbd(kbd);
			
			return false;
		}
		
		void charInput(const wchar_t *str, int len)
		{
			if (!input)
				return;
			
			ws::KbdMessage kbd;
			kbd.type = ws::KbdMessage::KEY_CHAR;
			for (int i = 0; i < len; ++i)
			{
				kbd.ch = str[i];
				input->kbd(kbd);
			}
		}
		
		void destroyWindow()
		{
			if (!windowExist)
				return;
			
			windowExist = false;
			glXMakeCurrent(info.display, 0, 0);
			glXDestroyContext(info.display, ctx);
			XDestroyWindow(info.display, info.window);
			XFreeColormap(info.display, cmap);
			unregisterWindow(info.window);
		
			
			if (xic)
				XDestroyIC(xic);
			
			if (xim)
				XCloseIM(xim);
		}
		
		void initializeKeyCodesTable()
		{
			memset(keyCodesConverter, 0, sizeof(keyCodesConverter));
			
			kk::KeyCode code;
			unsigned symkey;
			
			for (code = kk::KEY_KEY_0, symkey = XK_0; code <= kk::KEY_KEY_9; ++(int &)code, ++symkey)
				addCode(XKeysymToKeycode(info.display, symkey), code);
			
			for (code = kk::KEY_KEY_A, symkey = XK_A; code <= kk::KEY_KEY_Z; ++(int &)code, ++symkey)
				addCode(XKeysymToKeycode(info.display, symkey), code);
			
			for (code = kk::KEY_F1, symkey = XK_F1; code <= kk::KEY_F12; ++(int &)code, ++symkey)
				addCode(XKeysymToKeycode(info.display, symkey), code);
			
			addCode(XKeysymToKeycode(info.display, XK_BackSpace), kk::KEY_BACK);
			addCode(XKeysymToKeycode(info.display, XK_Tab), kk::KEY_TAB);
			addCode(XKeysymToKeycode(info.display, XK_Return), kk::KEY_ENTER);
			addCode(XKeysymToKeycode(info.display, XK_Shift_L), kk::KEY_LSHIFT);
			addCode(XKeysymToKeycode(info.display, XK_Shift_R), kk::KEY_RSHIFT);
			addCode(XKeysymToKeycode(info.display, XK_Control_L), kk::KEY_LCONTROL);
			addCode(XKeysymToKeycode(info.display, XK_Control_R), kk::KEY_RCONTROL);
			addCode(XKeysymToKeycode(info.display, XK_Alt_L), kk::KEY_LALT);
			addCode(XKeysymToKeycode(info.display, XK_Alt_R), kk::KEY_RALT);
			addCode(XKeysymToKeycode(info.display, XK_Pause), kk::KEY_PAUSE);
			addCode(XKeysymToKeycode(info.display, XK_Escape), kk::KEY_ESCAPE);
			addCode(XKeysymToKeycode(info.display, XK_space), kk::KEY_SPACE);
			addCode(XKeysymToKeycode(info.display, XK_Page_Up), kk::KEY_PAGE_UP);
			addCode(XKeysymToKeycode(info.display, XK_Page_Down), kk::KEY_PAGE_DOWN);
			addCode(XKeysymToKeycode(info.display, XK_End), kk::KEY_END);
			addCode(XKeysymToKeycode(info.display, XK_Home), kk::KEY_HOME);
			addCode(XKeysymToKeycode(info.display, XK_Left), kk::KEY_LEFT);
			addCode(XKeysymToKeycode(info.display, XK_Up), kk::KEY_UP);
			addCode(XKeysymToKeycode(info.display, XK_Right), kk::KEY_RIGHT);
			addCode(XKeysymToKeycode(info.display, XK_Down), kk::KEY_DOWN);
			addCode(XKeysymToKeycode(info.display, XK_Insert), kk::KEY_INSERT);
			addCode(XKeysymToKeycode(info.display, XK_Delete), kk::KEY_DELETE);
			addCode(XKeysymToKeycode(info.display, XK_grave), kk::KEY_TILDE);
		}
		
		kk::KeyCode convertKey(unsigned xKeyCode)
		{
			if (xKeyCode >= 0 && xKeyCode < 256 && keyCodesConverter[xKeyCode] != 0)
				return keyCodesConverter[xKeyCode];
			
			return kk::KEY_NONE;
		}
		
		void addCode(unsigned xKeyCode, kk::KeyCode keyCode)
		{
			if (xKeyCode >= 0 && xKeyCode < 256)
				keyCodesConverter[xKeyCode] = keyCode;
		}
		
		ws::Input *input;
		bool windowExist;
		Atom delete_window_protocol, wm_protocols;
		XKeyReleasedEvent last_release_event;
		bool last_release_event_set;
		XIM xim;
		XIC xic;
		
		kk::KeyCode keyCodesConverter[256];
	};

	CGLXWindow::Windows CGLXWindow::windows;

	class GLXWindowManager : public ws::WindowManager
	{
	public:
		static GLXWindowManager *create();
		
		GLXWindowManager();
		
		bool init(const std::vector<std::string> &options);
		ws::Window *createWindow(const std::vector<std::string> &params, ws::WindowInfo *info);
		void processMessages();
		void quit();

	protected:
		Display *display;
		bool is_message_loop_active;
		bool initialized;
	}; 
	
	GLXWindowManager::GLXWindowManager()
	{
		display = NULL;
		is_message_loop_active = false;
		initialized = false;
	}

	typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;

	bool GLXWindowManager::init(const std::vector<std::string> &options)
	{
		po::options_description desc;
		desc.add_options()
			("display", po::value<std::string>(), "display")
			;
			
		po::variables_map vm;
		po::store(po::command_line_parser(options).options(desc).run(), vm);
		po::notify(vm);
		
		if (vm.count("display"))
		{
			display = XOpenDisplay(vm["display"].as<std::string>().c_str());
		}
		else
		{
			display = XOpenDisplay(0);
		}
		
		if (!display)
		{
			ERROR_LOG("Failed to open X display");
			return false;
		}
		
		int glx_major, glx_minor;
		// FBConfigs were added in GLX version 1.3.
		if ( !glXQueryVersion( display, &glx_major, &glx_minor ) || 
			( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
		{
			ERROR_LOG("GLX version must be 1.3 or higher (current = " << glx_major << "." << glx_minor << ")");
			return false;
		}
		
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
			glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
			
		if (!glXCreateContextAttribsARB)
		{
			ERROR_LOG("glXCreateContextAttribsARB not found");
			return false;
		}
		
		initialized = true;
		return true;
	}

	ws::Window *GLXWindowManager::createWindow(const std::vector<std::string> &params, ws::WindowInfo *info)
	{
		if (!initialized)
			return NULL;
		
		int gl_version = 33;
		bool forward_compatible = true;
		
		setlocale(LC_ALL, "ru_RU.UTF-8");
		
		// Fill win_info with correct values
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
			("gl_version", po::value<int>(&gl_version), "gl version = 10 * major_version + minor_version")
			("forward_compatible", po::value<bool>(&forward_compatible), "if gl_version >= 30, create forward compatible context")
			("title", po::value<std::string>(&win_info.title), "window title")
			;
			
		po::variables_map vm;
		po::store(po::command_line_parser(params).options(desc).run(), vm);
		po::notify(vm);
		
		size_t display_w = DisplayWidth(display, DefaultScreen(display));
		size_t display_h = DisplayHeight(display, DefaultScreen(display));
		
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
		
		// Create OpenGL window
		
		int visual_attribs[] = {
			GLX_X_RENDERABLE    , True,
			GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
			GLX_RENDER_TYPE     , GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
			GLX_RED_SIZE        , 8,
			GLX_GREEN_SIZE      , 8,
			GLX_BLUE_SIZE       , 8,
			GLX_ALPHA_SIZE      , 8,
			GLX_DEPTH_SIZE      , 24,
			GLX_STENCIL_SIZE    , 8,
			GLX_DOUBLEBUFFER    , True,
			//GLX_SAMPLE_BUFFERS  , 1,
			//GLX_SAMPLES         , 4,
			None
		};
		
		// Get framebuffer configs
		int fb_count;
		GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fb_count);
		if (!fbc)
		{
			ERROR_LOG("Failed to retrieve a framebuffer config");
			return NULL;
		}
		
		DEBUG_LOG("Found " << fb_count << " matching FB configs");
		
		// First config will be fine
		GLXFBConfig our_fbc = fbc[0];
		
		XFree(fbc);
		
		XVisualInfo *vi = glXGetVisualFromFBConfig(display, our_fbc);
		BOOST_SCOPE_EXIT( (&vi) ) { XFree(vi); } BOOST_SCOPE_EXIT_END
		
		XSetWindowAttributes swa;
		
		swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
		
		swa.background_pixmap = None;
		swa.border_pixel = 0;
		swa.event_mask = StructureNotifyMask;

		Window win = win_info.window = XCreateWindow(display, RootWindow(display, vi->screen ), 
								win_info.x, win_info.y, win_info.width, win_info.height, 0 /*border*/,
								vi->depth, InputOutput,
								vi->visual, 
								CWBorderPixel|CWColormap|CWEventMask, &swa );
		if (!win)
		{
			ERROR_LOG("Failed to create window");
			XFreeColormap(display, swa.colormap);
			return NULL;
		}

		win_info.display = display;
		CGLXWindow *result = new CGLXWindow(win_info);
		result->cmap = swa.colormap;
		
		result->setTitle(win_info.title);
		
		std::vector<int> context_attribs;
		context_attribs.push_back(GLX_CONTEXT_MAJOR_VERSION_ARB);
		context_attribs.push_back(gl_version / 10);
		context_attribs.push_back(GLX_CONTEXT_MINOR_VERSION_ARB);
		context_attribs.push_back(gl_version % 10);
		
		if (forward_compatible && gl_version >= 30)
		{
			context_attribs.push_back(GLX_CONTEXT_FLAGS_ARB);
			context_attribs.push_back(GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB);
		}
		
		context_attribs.push_back(0);

		result->ctx = glXCreateContextAttribsARB(display, our_fbc, 0, True, &context_attribs[0]);
		
		if (!result->ctx)
		{
			delete result;
			ERROR_LOG("Failed to create GL context");
			return NULL;
		}
		
		// Verifying that context is a direct context
		if ( ! glXIsDirect ( display, result->ctx ) )
		{
			DEBUG_LOG("Indirect GLX rendering context obtained");
		}
		else
		{
			DEBUG_LOG("Direct GLX rendering context obtained");
		}

		long event_mask =
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
			StructureNotifyMask;
			
		XSelectInput(display, win, event_mask);
		
		GLenum err = glGetError();
		glXMakeCurrent(result->info.display, result->info.window, result->ctx);
		err = glGetError();
			
		static bool glew_initialized = false;
		if (!glew_initialized)
		{
			glew_initialized = true;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				CRITICAL_LOG(glewGetErrorString(err));
			}
			MESSAGE_LOG("Using GLEW " << glewGetString(GLEW_VERSION));
		}
		
		MESSAGE_LOG("GL Version: " << glGetString(GL_VERSION));
		MESSAGE_LOG("Vendor: " << glGetString(GL_VENDOR));
		MESSAGE_LOG("Renderer: " << glGetString(GL_RENDERER));
		MESSAGE_LOG("GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION));
		
		return result;
	}

	void GLXWindowManager::processMessages()
	{
		while (XPending(display))
		{
			XEvent event;
			XNextEvent(display, &event);
			CGLXWindow::event_s(event.xany.window, event);
		}
		CGLXWindow::flush_s();
	}

	void GLXWindowManager::quit()
	{
		
	}
}

namespace gb
{
	namespace window_subsystem
	{
		WindowManager *createWindowManager(const char *)
		{
			return new GLXWindowManager;
		}
	}
}

#endif // _WIN32

