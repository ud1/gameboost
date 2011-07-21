#pragma once

#include <gb/math/typeTraits.h>
#include <gb/base/nullptr.h>

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
		
		template <typename Class, typename VarType>
		Layout getLayoutOf(VarType Class::* ptr)
		{
			Layout result;
			result.type = Layout::FLOAT; // FIXME
			result.ncomponents = math::rows_number<VarType>::value;
			result.stride = sizeof(Class);
			result.offset = reinterpret_cast<size_t>(&(((Class *) nullptr)->*ptr));
			return result;
		}
	}
}
