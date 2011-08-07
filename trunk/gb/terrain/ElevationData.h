#pragma once

#include <algorithm>
#include <cassert>

#include <gb/base/Types.h>
#include <gb/base/nullptr.h>
#include <gb/fs/Stream.h>
#include <gb/base/t/clamp.h>

namespace gb
{
	namespace terrain
	{
		
		/** Число треугольников в одном узле TER_NODE_SIZE*TER_NODE_SIZE для узла с нормальной детализацией*/
		const int TER_NODE_SIZE = 32;
		/** Так как размер данных для одного блока слишком мал группируем их по ELEVATION_DATA_BUCKET_SIZE*ELEVATION_DATA_BUCKET_SIZE штук */
		const int ELEVATION_DATA_BUCKET_SIZE = 8;
		/** log2(ELEVATION_DATA_BUCKET_SIZE) */
		const int LOG2_ELEVATION_DATA_BUCKET_SIZE = 3;
		/** Число вершин на стороне узла */
		const int TER_NODE_SIZE1 = TER_NODE_SIZE + 1;
		/** Число вершин у узла сохранённого в файл */
		const int TER_NODE_SIZE_WITH_PADDING = TER_NODE_SIZE1;


		/** \brief Данные высот для одного узла дерева */
		struct ElevationData
		{
			typedef int16_t height_t;
			height_t data[TER_NODE_SIZE_WITH_PADDING*TER_NODE_SIZE1];
			
			/** Минимальная и максимальная высоты */
			height_t min_val, max_val;
			/** Средняя и максимальная ошибка приближения данного лода от самого детализированного лода */
			float avg_error_x, avg_error_y, max_error_x, max_error_y;

			/** Вычисление ошибок, для простоты просто оценивается кривизна поверхности */
			void computeErrors()
			{
				avg_error_x = avg_error_y = max_error_x = max_error_y = 0.0f;
				float err;
				int c = 0;
				for (int i = 0; i < TER_NODE_SIZE1 - 2; ++i)
				{
					for (int j = 0; j < TER_NODE_SIZE1 - 2; ++j)
					{
						err = ((float) data[i*TER_NODE_SIZE_WITH_PADDING+j] - 2.0f*data[i*TER_NODE_SIZE_WITH_PADDING+j+1] + (float) data[i*TER_NODE_SIZE_WITH_PADDING+j+2])/4.0f;
						if (err < 0.0f)
							err = -err;
						if (max_error_x < err)
							max_error_x = err;
						avg_error_x += err;
						err = ((float) data[i*TER_NODE_SIZE_WITH_PADDING+j] - 2.0f*data[(i+1)*TER_NODE_SIZE_WITH_PADDING+j] + (float) data[(i+2)*TER_NODE_SIZE_WITH_PADDING+j])/4.0f;
						if (err < 0.0f)
							err = -err;
						if (max_error_y < err)
							max_error_y = err;
						avg_error_y += err;
						++c;
					}
				}
				avg_error_x /= c;
				avg_error_y /= c;
				min_val = max_val = data[0];
				for (int i = 0; i < TER_NODE_SIZE1; ++i)
				{
					for (int j = 0; j < TER_NODE_SIZE1; ++j)
					{
						height_t val = data[i*TER_NODE_SIZE_WITH_PADDING + j];
						if (val > max_val)
							max_val = val;
						if (val < min_val) 
							min_val = val;
					}
				}
			}
		};

		/** \brief Набор данных высот для узлов с лодами от 0 до LOG2_ELEVATION_DATA_BUCKET_SIZE-1 */
		struct RootElevationDataBucket
		{
			ElevationData *data;

			RootElevationDataBucket()
			{
				count = 0;
				for (int i = 1; i < ELEVATION_DATA_BUCKET_SIZE; i*=2)
				{
					count += i*i;
				}
				data = new ElevationData[count];
			}

			~RootElevationDataBucket()
			{
				delete []data;
			}

			void computeErrors()
			{
				for (int i = 0; i < count; ++i)
				{
					data[i].computeErrors();
				}
			}

			bool saveToFile(fs::OutputStream *file) const
			{
				return file->write((const char *) data, sizeof(ElevationData)*count);
			}

			bool loadFromFile(fs::InputStream *file)
			{
				return file->read((char *) data, sizeof(ElevationData)*count) == sizeof(ElevationData)*count;
			}

			/** Возвращает блок данных высот с указанными параметрами */
			ElevationData *get(int lod, int x, int y)
			{
				assert(lod < LOG2_ELEVATION_DATA_BUCKET_SIZE);

				if (lod < 0)
					return nullptr;

				int off = 0;
				int i;
				for (i = 1; lod--; i*=2)
				{
					off += i*i;
				}

				off += i*y + x;

				assert(off < count);

				return &data[off];
			}

			int count;
		};

		/**
		 * \brief Объединение блоков ElevationData в более большие
		 */
		struct ElevationDataBucket
		{
			ElevationData data[ELEVATION_DATA_BUCKET_SIZE*ELEVATION_DATA_BUCKET_SIZE];

			// Calculate terrain irregularity
			void computeErrors()
			{
				for (int i = 0; i < ELEVATION_DATA_BUCKET_SIZE*ELEVATION_DATA_BUCKET_SIZE; ++i)
				{
					data[i].computeErrors();
				}
			}

			bool saveToFile(fs::OutputStream *file) const
			{
				return file->write((const char *) this, sizeof(*this));
			}

			bool loadFromFile(fs::InputStream *file)
			{
				return file->read((char *) this, sizeof(*this)) == sizeof(*this);
			}
		};
	}
}

