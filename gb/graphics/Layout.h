#pragma once

namespace gb
{
	namespace graphics
	{
		
		/**
		 * Определяет формат хранения данных в буфере.
		 */
		struct Layout
		{
			enum Type
			{
				FLOAT,
				DOUBLE
			};

			Type type;
			size_t ncomponents;
			size_t stride;
			size_t offset;
		};
		
	}
}
