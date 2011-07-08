#pragma once

#include "rects.h"
#include <gb/math/math.h>
#include <vector>

namespace gb
{
	namespace graphics
	{
		
		struct Vertex2d
		{
			math::ivec2 coord, tex_coord;
		};
		
		class RectsBuffer
		{
		public:
			
			typedef std::vector<Vertex2d> VertexBuffer;
			typedef std::vector<short> IndexBuffer;
			
			void clear()
			{
				vertex_buffer.clear();
				index_buffer.clear();
			}
			
			const VertexBuffer &getVertexBuffer() const
			{
				return vertex_buffer;
			}
			
			const IndexBuffer &getIndexBuffer() const
			{
				return index_buffer;
			}
			
			void addRects(const Rect1 *rects, size_t size);
			void addRects(const Rect9 *rects, size_t size);
			
		private:
			VertexBuffer vertex_buffer;
			IndexBuffer index_buffer;
		};
		
	}
}
