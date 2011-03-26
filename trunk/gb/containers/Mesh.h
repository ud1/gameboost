#pragma once

#include <string>

#include <gb/base/Types.h>
#include <gb/graphics/Device.h>
#include <gb/fs/Stream.h>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace gb
{
	namespace containers
	{

		/**
		 * \brief Класс для хранения геометрии
		 * 
		 * Mesh состоит из набора SubMesh'ей, и Stream'ов. Каждый Stream это массив
		 * элементов, тип которых задается с помощью StreamElemType, и может быть
		 * массивом индексов или векторов задающих нормаль/координаты и т.д.
		 * В меше может быть несколько стримов индексов, другие стримы являются общими
		 * для всех сабмешей.
		 * Каждый SubMesh хранит имя используемого стрима индексов и тип примитивов.
		 * Стримы используемые при рендеринге (координаты/нормали/бинормали и т.д.)
		 * определяются материалом.
		 * Для удобства при хранении меша на диске, метаданные и сами данные (массивы
		 * элементов стримов) разделены, и метаданные представлены в текстовом формате.
		 */
		struct Mesh
		{
			enum StreamElemType
			{
				ET_USHORT,	// 2 байта
				ET_INT,		// 4 байта
				ET_FLOAT,
				ET_FLOAT2,
				ET_FLOAT3,
				ET_FLOAT4,
				STREAM_ELEM_TYPE_COUNT
			};
			
			/** Возвращает StreamElemType по его имени, и STREAM_ELEM_TYPE_COUNT если такой тип не найден */
			static StreamElemType getElemTypeByName(const std::string &name);
			/** Возвращает развер элемента StreamElemType в байтах */
			static StreamElemType getElemSizeByType(StreamElemType type);
			/** Возвращает строковое представление типа элемента */
			static const char *getElemTypeName(StreamElemType type);

			struct Stream
			{
				Stream() {ptr = NULL;}
				~Stream();
				StreamElemType type;
				size_t size;
				union
				{
					uint16_t *short_ptr;
					int32_t *int_ptr;
					float *float_ptr;
					void *ptr;
				};
			};

			struct SubMesh
			{
				std::string name;
				std::string indices_stream_name;
				std::string material_name;
				size_t min_index, max_index;
				graphics::Device::PrimitiveType prims_type;
			};

			bool load(fs::InputStream &metafile, fs::InputStream &datafile);
			bool save(fs::OutputStream &metafile, fs::OutputStream &datafile) const;

			size_t subMeshNumber() const
			{
				return sub_meshes.size();
			}

			const SubMesh *getSubMesh(size_t i) const
			{
				return &sub_meshes[i];
			}

			const Stream *getStream(const std::string &name) const
			{
				Streams::const_iterator it = streams.find(name);
				if (it != streams.end())
					return it->second;
				return NULL;
			}

			typedef boost::ptr_map<std::string, Stream> Streams;
			Streams streams;
			boost::ptr_vector<SubMesh> sub_meshes;
		};
	}
}