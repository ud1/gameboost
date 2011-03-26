#include "Obj.h"

#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <boost/algorithm/minmax_element.hpp>

#include <NvTriStrip.h>

namespace gb
{
	namespace loaders
	{
		namespace models
		{
			using namespace gb::fs;
			using namespace gb::math;
			using namespace gb::containers;
			
			bool Obj::Vertex::operator < (const Vertex &o) const
			{
				return boost::make_tuple(vertex_index, texture_coord_index, normal_index) <
					boost::make_tuple(o.vertex_index, o.texture_coord_index, o.normal_index);
			}

			Obj::Obj()
			{
				texture_coords_have_third_component = false;
			}

			bool Obj::load(InputStream &file)
			{
				Group *last_group = NULL;
				std::string content;
				readEntireFile(file, content);

				std::istringstream iss(content);
				char str[1024];
				while (1)
				{
					if (iss.getline(str, 1024).fail())
						break;

					if (str[0] == '#') // comments
						continue;

					if (strlen(str) < 3)
						continue;

					std::stringstream ss(str);
					std::string command;
					ss >> command;

					if (command == "v")
					{
						vec3 v;
						if ((ss >> v.x >> v.y >> v.z).fail())
							return false;

						vertices.push_back(v);
					}
					else if (command == "vn")
					{
						vec3 vn;
						if ((ss >> vn.x >> vn.y >> vn.z).fail())
							return false;

						normals.push_back(vn);
					}
					else if (command == "vt")
					{
						vec3 vt;
						if ((ss >> vt.x >> vt.y).fail())
							return false;

						if ((ss >> vt.z).fail())
							vt.z = 0.0f;

						if (vt.z != 0.0f)
							texture_coords_have_third_component = true;

						texture_coords.push_back(vt);
					}
					else if (command == "g")
					{
						last_group = new Group;
						if ((ss >> last_group->name).fail())
							last_group->name = "unnamed";

						groups.push_back(last_group);
					}
					else if (command == "f")
					{
						if (!last_group)
							return false;

						TriFace face;
						int n = sscanf(str, "f %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld",
							&face.vertices[0].vertex_index, &face.vertices[0].texture_coord_index, &face.vertices[0].normal_index,
							&face.vertices[1].vertex_index, &face.vertices[1].texture_coord_index, &face.vertices[1].normal_index,
							&face.vertices[2].vertex_index, &face.vertices[2].texture_coord_index, &face.vertices[2].normal_index);

						if (n == 9)
						{
							last_group->faces.push_back(face);
						}
						else
						{
							ERROR_LOG("Parse error " << str);
							return false;
						}
					}
				}
				return true;
			}

			Mesh *Obj::convertToMesh() const
			{
				std::map<Vertex, unsigned short> verts; // unique vertices sorted
				std::map<Vertex, unsigned short>::iterator it;
				std::vector<Vertex> verts_vector; // unique vertices, not sorted

				std::vector<PrimitiveGroup *> prim_groups(groups.size());

				for (size_t i = 0; i < groups.size(); ++i)
				{
					const Group &g = groups[i];
					
					std::vector<unsigned short> inds;
					inds.reserve(g.faces.size() * 3);

					for (size_t j = 0; j < g.faces.size(); ++j) {
						const TriFace &face = g.faces[j];
						for (size_t k = 0; k < 3; ++k) {
							it = verts.find(face.vertices[k]);
							if (it == verts.end()) {
								inds.push_back(verts_vector.size());
								verts.insert(std::make_pair(face.vertices[k], verts_vector.size()));
								verts_vector.push_back(face.vertices[k]);
							} else {
								inds.push_back(it->second);
							}
						}
					}

					unsigned short groups_out_n;
					GenerateStrips(&inds[0], inds.size(), &prim_groups[i], &groups_out_n);
					assert(groups_out_n == 1);
					assert(prim_groups[i]->type == PT_STRIP);
				}

				// create mesh
				Mesh *mesh = new Mesh;
				Mesh::Stream *vertices_stream = new Mesh::Stream;
				Mesh::Stream *tex_coords_stream = new Mesh::Stream;
				Mesh::Stream *normals_stream = new Mesh::Stream;

				// create vertex/normals/tex_coords streams from verts_vector
				vertices_stream->size = tex_coords_stream->size = normals_stream->size = verts_vector.size();
				
				vertices_stream->type = Mesh::ET_FLOAT3;
				vertices_stream->float_ptr = new float[verts_vector.size() * 3];

				normals_stream->type = Mesh::ET_FLOAT3;
				normals_stream->float_ptr = new float[verts_vector.size() * 3];

				if (texture_coords_have_third_component)
				{
					tex_coords_stream->type = Mesh::ET_FLOAT3;
					tex_coords_stream->float_ptr = new float[verts_vector.size() * 3];
				}
				else
				{
					tex_coords_stream->type = Mesh::ET_FLOAT2;
					tex_coords_stream->float_ptr = new float[verts_vector.size() * 2];
				}

				for (size_t i = 0; i < verts_vector.size(); ++i)
				{
					const Vertex &vert = verts_vector[i];

					const vec3 &vertex = vertices[vert.vertex_index];
					((vec3 *) vertices_stream->float_ptr)[i] = vertex;

					const vec3 &normal = normals[vert.normal_index];
					((vec3 *) normals_stream->float_ptr)[i] = normal;

					const vec3 &tex_coord = texture_coords[vert.texture_coord_index];
					if (texture_coords_have_third_component)
					{
						((vec3 *) tex_coords_stream->float_ptr)[i] = tex_coord;
					}
					else
					{
						((vec2 *) tex_coords_stream->float_ptr)[i].x = tex_coord.x;
						((vec2 *) tex_coords_stream->float_ptr)[i].y = tex_coord.y;
					}
				}

				std::string key;
				mesh->streams.insert(key = "vertices", vertices_stream);
				mesh->streams.insert(key = "normals", normals_stream);
				mesh->streams.insert(key = "tex_coords", tex_coords_stream);

				// Create submeshes from groups
				for (size_t i = 0; i < groups.size(); ++i)
				{
					PrimitiveGroup *prim_group = prim_groups[i];
					Mesh::Stream *indices_stream = new Mesh::Stream;
					indices_stream->type = Mesh::ET_USHORT;
					indices_stream->size = prim_group->numIndices;
					indices_stream->short_ptr = new unsigned short[indices_stream->size];
					std::copy(prim_group->indices, prim_group->indices + indices_stream->size, indices_stream->short_ptr);
					std::pair<unsigned short *, unsigned short *> int_pair = boost::minmax_element(prim_group->indices, prim_group->indices + indices_stream->size);
					std::ostringstream oss;
					oss << "indices" << i;
					mesh->streams.insert(key = oss.str(), indices_stream);

					Mesh::SubMesh *sub_mesh = new Mesh::SubMesh;
					sub_mesh->indices_stream_name = oss.str();
					sub_mesh->name = groups[i].name;
					sub_mesh->material_name = "standard.solid";
					sub_mesh->prims_type = graphics::Device::TRI_STRIP;
					sub_mesh->min_index = *int_pair.first;
					sub_mesh->max_index = *int_pair.second;

					mesh->sub_meshes.push_back(sub_mesh);

					delete []prim_group;
				}

				return mesh;
			}

		}
	}
}