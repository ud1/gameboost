/**
 * Данный модуль предназначен для создания окна и 
 * обработки сообщений. Т.к. процедура инициализации
 * графической библиотеки сушественно зависит как
 * от операционной системы, так и от самой библиотеки,
 * данный модуль акже проводит её инициализацию
 * при создании окна.
 * 
 * Количество окон может быть любым.
 */


#pragma once

#include "Window.h"
#include <string>

namespace gb
{
	namespace window_subsystem
	{
		class WindowManager : public base::IRefCountable
		{
		public:
			/**
			 * Список опций зависит от операционной системы
			 */
			virtual bool init(const std::vector<std::string> &options) = 0;
			
			/**
			 * Создает окно, используя параметры из params и info. Параметры params имеют более
			 * высокий приоритет, и могут заменять собой парамтры из info.
			 * Список опций params также зависит от операционной системы, но
			 * гарантируется наличие следующих опций:
			 * <div>
			 * width, height - ширина и высота окна в пикселях
			 * abs_x, abs_y - координаты левого верхнего угла окна, могут игнорироваться некоторыми оконными менеджерами
			 * rel_width, rel_height - ширина и высота в относительных относительно экрана единицах, диапазон значений 0.0-1.0
			 * rel_x, rel_y - координаты левого верхнего угла окна в относительных относительно экрана единицах, диапазон значений 0.0-1.0
			 * 
			 * Для OpenGL:
			 * gl_version - для OpenGL менеджера определяет номер версии в виде числа 10 * major_version + minor_version
			 * forward_compatible - Если версия OpenGL >= 30, то определяет необходимость создания forward compatible context'а
			 * </div>
			 */
			virtual Window *createWindow(const std::vector<std::string> &params, WindowInfo *info) = 0;
			virtual void processMessages() = 0;
			virtual void quit() = 0;
		};
		
		typedef base::RefCntHolder<WindowManager> PWindowManager;
		
		/**
		 * @param graphics_library может принимать значения например "OpenGL" или "DirectX"
		 */
		WindowManager *createWindowManager(const char *graphics_library);
	}
}