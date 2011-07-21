#pragma once

#include <string>

#include "Buffer.h"
#include "Layout.h"

namespace gb
{
	namespace graphics
	{
		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс для аттрибута шейдерной программы
		 */
		class Attribute
		{
		public:
			/** Имя */
			const char *getName() const {return name.c_str();}
			
			/**
			 * Биндит вершинных буффер к аттрибуту
			 * \param buf вершинный буфер
			 * \param l задаёт расположение и тип данных внутри буфера
			 */
			virtual bool setVertexBuffer(Buffer *buf, const Layout &l) = 0;
			
		protected:
			std::string name;
		};
		
	}
}
