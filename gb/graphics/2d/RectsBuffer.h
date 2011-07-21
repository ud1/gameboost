#pragma once

#include "rects.h"
#include <gb/math/math.h>
#include <vector>

namespace gb
{
	namespace graphics2d
	{
		
		struct Vertex2d
		{
			math::vec2 coord, tex_coord;
			math::vec3 color;
		};
		
		class RectsBuffer
		{
		public:
			
			typedef std::vector<Vertex2d> VertexBuffer;
			typedef std::vector<short> IndexBuffer;
			
			RectsBuffer() {compiled = true;}
			
			void clear()
			{
				vertex_buffer.clear();
				index_buffer.clear();
				order.clear();
			}
			
			const VertexBuffer &getVertexBuffer()
			{
				compile();
				return vertex_buffer;
			}
			
			const IndexBuffer &getIndexBuffer()
			{
				compile();
				return index_buffer;
			}
			
			void addRects(const Rect1 *rects, size_t size, math::vec3 color);
			void addRects(const Rect9 *rects, size_t size, math::vec3 color);
			
		private:
			VertexBuffer vertex_buffer;
			IndexBuffer index_buffer;
			
			std::vector<Rect1> rect1_vector;
			std::vector<Rect9> rect9_vector;
			
			struct RectsBucket
			{
				RectsBucket(int vector_id, size_t count, math::vec3 color) : vector_id(vector_id), count(count), color(color) {}
				
				int vector_id; // 0 - rect1_vector, 1 - rect9_vector
				size_t count;
				math::vec3 color;
			};
			std::vector<RectsBucket> order;
			
			void addRectsToBuffer(const Rect1 *rects, size_t size, math::vec3 color);
			void addRectsToBuffer(const Rect9 *rects, size_t size, math::vec3 color);
			
			bool compiled;
			void compile();
		};
		
	}
}
