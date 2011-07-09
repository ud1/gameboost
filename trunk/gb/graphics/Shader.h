#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс для шейдеров
		 */
		class Shader : public base::IRefCountable
		{
		public:
			/** Устанавливает листинг шейдера */
			virtual void setSource(const char *str) = 0;
			
			/**
			 * Компиляция шейдера, ошибки будут писаться в лог
			 * \return true в случае успешной компиляции
			 */
			virtual bool compile() = 0;
		};
		
		typedef base::RefCntHolder<Shader> PShader;
		
	}
}
