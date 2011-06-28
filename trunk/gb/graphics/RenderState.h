#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		/**
		 * \brief RenderState предназначен для удобной установки глобальных состояний отрисовки.
		 * 
		 * Принимает на вход текст, каждая строка которого
		 * является устанавливаемым состоянием, например:
		 * @code
		 * DepthTest enable
		 * ScissorTest disable
		 * Wireframe enable
		 * @endcode
		 * Основной целью является уменьшение количества необходимых
		 * в интерфейсах функций, а так же удобная групировка
		 * состояний.
		 * Можно создавать в программе сколько угодно RenderState,
		 * для активации используется функция apply().
		 */
		class RenderState : public base::IRefCountable
		{
		public:
			virtual bool setSource(const char *code) = 0;
			virtual void apply() = 0;
		};
		
		typedef base::RefCntHolder<RenderState> PRenderState;
		
	}
}
