#pragma once

#include <gb/fs/Stream.h>
#include <gb/base/nullptr.h>

namespace gb
{
	namespace terrain
	{
		
		enum EDGE_FLAGS
		{
			N_FLAG = 1,
			S_FLAG = 2,
			E_FLAG = 4,
			W_FLAG = 8,
		};

		/**
		 * \brief Индесный буффер для патчей террейна.
		 * 
		 * Сожержит индексы для 16 видов узлов.
		 * Узлы отличаются типом сторон, каждая сторона может иметь два типа детализации,
		 * полный и разрежённый. Тип сторон определяется по номеру буффера, номер равен
		 * сумме EDGE_FLAGS, где если какой-то флаг установлен, то данная сторона имеет разрежённую детализацию.
		 */
		struct IndexBuffer
		{
			/** Массив смещений индексов в inds */
			int inds_offsets[16];
			/** Массив числа индексов для каждого типа узла */
			int inds_count[16];
			/** Общее количество индексов */
			int indsN;
			/** Число треугольников в одной стороне узла */
			int size;
			/** Массив всех индексов */
			unsigned short *inds;

			IndexBuffer(int size_)
			{
				indsN = 0;

#error ks777:   VC:	 Error	31	error C2065: 'nullptr' : undeclared identifier	z:\!!gb\gameboost\gb\terrain\indexbuffer.h	43
				inds = nullptr;

				size = size_;
			}

			~IndexBuffer()
			{
				delete []inds;
			}

			void computeIndices();
			bool saveToFile(fs::OutputStream &file);
			bool loadFromFile(fs::InputStream &file);
		};

	}
}
