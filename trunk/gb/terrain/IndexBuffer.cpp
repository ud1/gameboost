
#include "pch.h"
#include <cassert>

#include "IndexBuffer.h"

#include <NvTriStrip.h>

#include <gb/base/Logger.h>

namespace
{
	using namespace gb::terrain;
	
	// Преобразует индекс для вершины на северной стороне в индекс
	// соответсвующей вершины на указанной в flag стороне
	inline short rotate_index(short ind, int flag, int size)
	{
		int size1 = size + 1;
		int x, y;
		switch (flag) {
			case N_FLAG:
				return ind;
			case S_FLAG:
				return size1 * size1 - ind - 1;
			case E_FLAG:
				x = ind % size1;
				y = size1 - ind / size1 - 1;
				return (x*size1 + y);
			case W_FLAG:
				x = size1 - ind % size1 - 1;
				y = ind / size1;
				return (x*size1 + y);
		}
		assert(0);
		return 0;
	}
}

namespace gb
{
	namespace terrain
	{

		void IndexBuffer::computeIndices()
		{
			int size1 = size + 1;
			// Генерируем индексы для 16 типов узлов

			// Индексы для неразрежённой северной стороны
			//  ___________
			//  \ |\ |\ | /
			//   \| \| \|/
			//    -------
 
			short normal_edge_inds[(size-1)*6];

			int c = 0;
			// Первый треугольник
			normal_edge_inds[c++] = 0;
			normal_edge_inds[c++] = 1;
			normal_edge_inds[c++] = size1 + 1;

			// индексы для треугольников в середине
			for (int i = 0; i < size - 2; ++i)
			{
				normal_edge_inds[c++] = size1 + 1 + i;
				normal_edge_inds[c++] = 1 + i;
				normal_edge_inds[c++] = size1 + 2 + i;

				normal_edge_inds[c++] = size1 + 2 + i;
				normal_edge_inds[c++] = 1 + i;
				normal_edge_inds[c++] = 2 + i;
			}

			// Последний треугольник
			normal_edge_inds[c++] = size1 - 2;
			normal_edge_inds[c++] = size1 - 1;
			normal_edge_inds[c++] = 2*size1 - 2;
			assert(c == sizeof(normal_edge_inds)/sizeof(normal_edge_inds[0]));

			// Индексы для разрежённой северной стороны
			//  ___________________
			//  \  /|\  /|\  /|\  /
			//   \/ | \/ | \/ | \/
			//    ---------------
			short sparse_edge[(3*size/2 - 2)*3];
			c = 0;
			// Первые два треугольника
			sparse_edge[c++] = 0;
			sparse_edge[c++] = 2;
			sparse_edge[c++] = size1 + 1;

			sparse_edge[c++] = size1 + 1;
			sparse_edge[c++] = 2;
			sparse_edge[c++] = size1 + 2;

			// Треугольники в середине
			for (int i = 0; i < (size - 4)/2; ++i)
			{
				sparse_edge[c++] = size1 + 2 + 2*i;
				sparse_edge[c++] = 2 + 2*i;
				sparse_edge[c++] = size1 + 3 + 2*i;

				sparse_edge[c++] = size1 + 3 + 2*i;
				sparse_edge[c++] = 2 + 2*i;
				sparse_edge[c++] = 4 + 2*i;

				sparse_edge[c++] = size1 + 3 + 2*i;
				sparse_edge[c++] = 4 + 2*i;
				sparse_edge[c++] = size1 + 4 + 2*i;
			}

			// Последние два треугольника
			sparse_edge[c++] = 2*size1 - 3;
			sparse_edge[c++] = size1 - 3;
			sparse_edge[c++] = 2*size1 - 2;

			sparse_edge[c++] = 2*size1 - 2;
			sparse_edge[c++] = size1 - 3;
			sparse_edge[c++] = size1 - 1;
			assert(c == sizeof(sparse_edge)/sizeof(sparse_edge[0]));

			// строим 16 индесных буфферов
			unsigned short inds[size*size*6*16];
			int inds_size[16];
			for (int i = 0; i < 16; ++i)
			{
				unsigned short *inds_ptr = inds + size*size*6*i;
				inds_size[i] = 0;

				// Добавляем края
				for (int flag = 1; flag < 16; flag <<= 1)
				{
					if (i & flag)
					{
						for (int j = 0; j < sizeof(sparse_edge)/sizeof(sparse_edge[0]); ++j)
						{
							*(inds_ptr++) = rotate_index(sparse_edge[j], flag, size);
						}
						inds_size[i] += sizeof(sparse_edge)/sizeof(sparse_edge[0]);
					}
					else
					{
						for (int j = 0; j < sizeof(normal_edge_inds)/sizeof(normal_edge_inds[0]); ++j)
						{
							*(inds_ptr++) = rotate_index(normal_edge_inds[j], flag, size);
						}
						inds_size[i] += sizeof(normal_edge_inds)/sizeof(normal_edge_inds[0]);
					}
				}

				//  __________
				//  |\ |\ |\ |
				//  | \| \| \|
				//  ----------
				//  |\ |\ |\ |
				//  | \| \| \|
				//  ----------
				//  |\ |\ |\ |
				//  | \| \| \|
				//  ----------
				// Добавляем центральные треугольники узла
				for (int y = 1; y < size-1; ++y)
				{
					for (int x = 1; x < size-1; ++x)
					{
						short offset = y*size1 + x;
						*(inds_ptr++) = 0 + offset;
						*(inds_ptr++) = 1 + offset;
						*(inds_ptr++) = size1 + offset;

						*(inds_ptr++) = size1 + offset;
						*(inds_ptr++) = 1 + offset;
						*(inds_ptr++) = size1 + 1 + offset;
					}
				}

				inds_size[i] += (size-2)*(size-2)*6;

				assert(inds_size[i] <= size*size*6);
			}

			// Используем NvTriStrip для генерации стрипов
			SetCacheSize(CACHESIZE_GEFORCE3);

			// Edges
			PrimitiveGroup *groups[16];
			for (int i = 0; i < 16; ++i)
			{
				MESSAGE_LOG("NvTriStrip start " << i << "/16");
				unsigned short *inds_ptr = inds + size*size*6*i;
				unsigned short numGroups;
				GenerateStrips(inds_ptr, inds_size[i], &groups[i], &numGroups);
				assert(numGroups == 1);
				assert(groups[i]->type == PT_STRIP);
				MESSAGE_LOG("NvTriStrip end " << i << "/16");
			}

			// Кладём всё в один буффер
			inds_offsets[0] = 0;
			for (int i = 1; i < 16; ++i)
			{
				inds_offsets[i] = inds_offsets[i-1] + groups[i-1]->numIndices;
			}
			indsN = inds_offsets[15] + groups[15]->numIndices;

			assert(!this->inds);
			this->inds = new unsigned short[indsN];
			unsigned short *inds_ptr = this->inds;

			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < groups[i]->numIndices; ++j)
				{
					*(inds_ptr++) = groups[i]->indices[j];
				}
				inds_count[i] = groups[i]->numIndices;
			}

			// Чистим за собой
			for (int i = 0; i < 16; ++i)
			{
				delete []groups[i];
			}
		}

		bool IndexBuffer::saveToFile(fs::OutputStream &file)
		{
			if (!inds)
				return false;

			file.write((const char *) inds_offsets, sizeof(inds_offsets));
			file.write((const char *) inds_count, sizeof(inds_count));
			file.write((const char *) &indsN, sizeof(indsN));
			file.write((const char *) inds, sizeof(unsigned short)*indsN);
			return true;
		}

		bool IndexBuffer::loadFromFile(fs::InputStream &file)
		{
			file.read((char *) inds_offsets, sizeof(inds_offsets));
			file.read((char *) inds_count, sizeof(inds_count));
			file.read((char *) &indsN, sizeof(indsN));
			inds = new unsigned short[indsN];
			file.read((char *) inds, sizeof(unsigned short)*indsN);
			return true;
		}

	}
}

