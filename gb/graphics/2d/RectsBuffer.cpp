#include "RectsBuffer.h"

namespace gb
{
	namespace graphics2d
	{
		
		void RectsBuffer::addRects(const Rect1 *rects, size_t size, math::vec3 color)
		{
			compiled = false;
			rect1_vector.insert(rect1_vector.end(), rects, rects + size);
			order.push_back(RectsBucket(0, size, color));
		}
		
		void RectsBuffer::addRects(const Rect9 *rects, size_t size, math::vec3 color)
		{
			compiled = false;
			rect9_vector.insert(rect9_vector.end(), rects, rects + size);
			order.push_back(RectsBucket(1, size, color));
		}
		
		void RectsBuffer::compile()
		{
			if (compiled)
				return;
			
			vertex_buffer.clear();
			index_buffer.clear();
			
			size_t rect1_vector_pos = 0;
			size_t rect9_vector_pos = 0;
			for (size_t i = 0; i < order.size(); ++i)
			{
				RectsBucket &bucket = order[i];
				if (bucket.vector_id == 0)
				{
					addRectsToBuffer(&rect1_vector[rect1_vector_pos], bucket.count, bucket.color);
					rect1_vector_pos += bucket.count;
				}
				else
				{
					addRectsToBuffer(&rect9_vector[rect9_vector_pos], bucket.count, bucket.color);
					rect9_vector_pos += bucket.count;
				}
			}
			compiled = true;
		}
		
		void RectsBuffer::addRectsToBuffer(const Rect1 *rects, size_t size, math::vec3 color)
		{
			Vertex2d vertex;
			vertex.color = color;
			for (const Rect1 *rect = rects; rect < rects + size; ++rect)
			{
				short ind = (short) vertex_buffer.size();
				
				vertex.coord = math::ivec2(rect->left, rect->top);
				vertex.tex_coord = math::ivec2(rect->image_block->left, rect->image_block->top);
				vertex_buffer.push_back(vertex);
				
				vertex.coord.x += rect->width;
				vertex.tex_coord.x += rect->image_block->width;
				vertex_buffer.push_back(vertex);
				
				vertex.coord.y += rect->height;
				vertex.tex_coord.y += rect->image_block->height;
				vertex_buffer.push_back(vertex);
				
				vertex.coord.x = rect->left;
				vertex.tex_coord.x = rect->image_block->left;
				vertex_buffer.push_back(vertex);
				
				index_buffer.push_back(ind + 0);
				index_buffer.push_back(ind + 1);
				index_buffer.push_back(ind + 3);
				
				index_buffer.push_back(ind + 3);
				index_buffer.push_back(ind + 1);
				index_buffer.push_back(ind + 2);
			}
		}
		
		void RectsBuffer::addRectsToBuffer(const Rect9 *rects, size_t size, math::vec3 color)
		{
			for (const Rect9 *rect = rects; rect < rects + size; ++rect)
			{
				const ImageBlock *image_block = rect->image_block;
				int x0 = rect->left;
				int x1 = rect->left + rect->wx;
				int x2 = rect->left + rect->width - rect->ex;
				int x3 = rect->left + rect->width;
				int tx0 = image_block->left;
				int tx1 = image_block->left + rect->wx;
				int tx2 = image_block->left + image_block->width - rect->ex;
				int tx3 = image_block->left + image_block->width;
				
				int y0 = rect->top;
				int y1 = rect->top + rect->ny;
				int y2 = rect->top + rect->height - rect->sy;
				int y3 = rect->top + rect->height;
				int ty0 = image_block->top;
				int ty1 = image_block->top + rect->ny;
				int ty2 = image_block->top + image_block->height - rect->sy;
				int ty3 = image_block->top + image_block->height;
				
				short ind = (short) vertex_buffer.size();
				
				Vertex2d vertex;
				vertex.color = color;
				
				vertex.coord = math::ivec2(x0, y0);
				vertex.tex_coord = math::ivec2(tx0, ty0);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x1, y0);
				vertex.tex_coord = math::ivec2(tx1, ty0);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x2, y0);
				vertex.tex_coord = math::ivec2(tx2, ty0);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x3, y0);
				vertex.tex_coord = math::ivec2(tx3, ty0);
				vertex_buffer.push_back(vertex);


				vertex.coord = math::ivec2(x0, y1);
				vertex.tex_coord = math::ivec2(tx0, ty1);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x1, y1);
				vertex.tex_coord = math::ivec2(tx1, ty1);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x2, y1);
				vertex.tex_coord = math::ivec2(tx2, ty1);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x3, y1);
				vertex.tex_coord = math::ivec2(tx3, ty1);
				vertex_buffer.push_back(vertex);

				
				vertex.coord = math::ivec2(x0, y2);
				vertex.tex_coord = math::ivec2(tx0, ty2);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x1, y2);
				vertex.tex_coord = math::ivec2(tx1, ty2);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x2, y2);
				vertex.tex_coord = math::ivec2(tx2, ty2);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x3, y2);
				vertex.tex_coord = math::ivec2(tx3, ty2);
				vertex_buffer.push_back(vertex);
				
				
				vertex.coord = math::ivec2(x0, y3);
				vertex.tex_coord = math::ivec2(tx0, ty3);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x1, y3);
				vertex.tex_coord = math::ivec2(tx1, ty3);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x2, y3);
				vertex.tex_coord = math::ivec2(tx2, ty3);
				vertex_buffer.push_back(vertex);
				
				vertex.coord = math::ivec2(x3, y3);
				vertex.tex_coord = math::ivec2(tx3, ty3);
				vertex_buffer.push_back(vertex);
				
				for (short i = 0; i < 3; ++i)
				{
					for (short j = 0; j < 3; ++j)
					{
						index_buffer.push_back(ind + 0 + i + 4*j);
						index_buffer.push_back(ind + 1 + i + 4*j);
						index_buffer.push_back(ind + 4 + i + 4*j);
						
						index_buffer.push_back(ind + 4 + i + 4*j);
						index_buffer.push_back(ind + 1 + i + 4*j);
						index_buffer.push_back(ind + 5 + i + 4*j);
					}
				}
			}
		}
		
	}
}
