#pragma once
#include <gb/base/IRefCountable.h>

#include "Attribute.h"
#include "Shader.h"
#include "Uniform.h"

namespace gb
{
	namespace graphics
	{
		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс шейдерной программы
		 */
		class ShaderProgram : public base::IRefCountable
		{
		public:
			/** Присоединяет шейдер (вершинный, фрагментный ... */
			virtual void attachShader(Shader *shd) = 0;
			
			/** Отсоединяет шейдер */
			virtual void detachShader(Shader *shd) = 0;
			
			/**
			 * Линковка программы. Ошибки пишутся в лог.
			 * \return true в случае успешной линковки
			 */
			virtual bool link() = 0;
			
			/**
			 * Число юниформов, доступно только после успешной линковки программы
			 */
			virtual size_t getUniformsNumber() = 0;
			
			/**
			 * Возврашает юниформ по его номеру, время жизни юниформа равно времени жизни шейдерной программы или до другого удачного вызова link()
			 */
			virtual Uniform *getUniform(size_t i) = 0;
			
			/**
			 * Число аттрибутов, доступно только после успешной линковки программы.
			 */
			virtual size_t getAttributesNumber() = 0;
			
			/**
			 * Возврашает аттрибут по его номеру, время жизни юниформа равно времени жизни шейдерной программы или до другого удачного вызова link()
			 */
			virtual Attribute *getAttribute(size_t i) = 0;
		};
		
		typedef base::RefCntHolder<ShaderProgram> PShaderProgram;
		
	}
}