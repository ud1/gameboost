#pragma once

#include <gb/math/math.h>
#include <gb/fs/Stream.h>
#include <gb/containers/Mesh.h>

#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

namespace gb
{
	namespace loaders
	{
		namespace models
		{
			/** Простенькая структура для загрузки *.obj файлов */
			struct Obj
			{
				std::vector<gb::math::vec3> vertices, normals, texture_coords;
				bool texture_coords_have_third_component;
				struct Vertex
				{
					long vertex_index, texture_coord_index, normal_index;

					bool operator < (const Vertex &o) const;
				};

				struct TriFace
				{
					Vertex vertices[3];
				};

				struct Group
				{
					std::string name;
					std::vector<TriFace> faces;
				};

				boost::ptr_vector<Group> groups;

				Obj();
				bool load(fs::InputStream &file);
				gb::containers::Mesh *convertToMesh() const;
			};
		}
	}
}
