#include "Mesh.h"
#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace
{
	
	size_t StreamElemTypeSize[] =
	{
		sizeof(uint16_t),
		sizeof(int32_t),
		sizeof(float),
		sizeof(float)*2,
		sizeof(float)*3,
		sizeof(float)*4
	};

	const char *StreamElemTypeName[] =
	{
		"ET_USHORT",
		"ET_INT",
		"ET_FLOAT",
		"ET_FLOAT2",
		"ET_FLOAT3",
		"ET_FLOAT4"
	};
	
}

namespace gb
{
	namespace containers
	{
		
		Mesh::StreamElemType Mesh::getElemTypeByName(const std::string &name)
		{
			for (size_t i = 0; i < Mesh::STREAM_ELEM_TYPE_COUNT; ++i)
			{
				if (name == StreamElemTypeName[i])
					return (Mesh::StreamElemType) i;
			}
			return Mesh::STREAM_ELEM_TYPE_COUNT;
		}
		
		const char *Mesh::getElemTypeName(StreamElemType type)
		{
			return StreamElemTypeName[type];
		}
		
		Mesh::Stream::~Stream()
		{
			if (!ptr)
				return;
			
			switch (type)
			{
				case Mesh::ET_USHORT:
					delete []short_ptr;
					break;
				case Mesh::ET_INT:
					delete []int_ptr;
					break;
				default:
					delete []float_ptr;
			}
		}

		bool Mesh::save(fs::OutputStream &metafile, fs::OutputStream &datafile) const
		{
			std::ostringstream oss;

			oss << "<mesh>\n";

			// streams
			if (!streams.empty())
			{
				oss << "\t<streams>\n";
			}
			
			for (Streams::const_iterator it = streams.begin(); it != streams.end(); ++it)
			{
				oss << "\t\t<stream>\n";
				
				const Stream *stream = it->second;

				oss << "\t\t\t<name>" << it->first << "</name>\n";
				oss << "\t\t\t<type>" << getElemTypeName(stream->type) << "</type>\n";
				oss << "\t\t\t<size>" << stream->size << "</size>\n";
				oss << "\t\t\t<offset>" << datafile.tell() << "</offset>\n";

				int bytes = stream->size * StreamElemTypeSize[stream->type];
				datafile.write((const char *) stream->ptr, bytes);
				
				oss << "\t\t</stream>\n";
			}

			if (!streams.empty())
			{
				oss << "\t</streams>\n";
			}

			// submeshes
			if (!sub_meshes.empty())
			{
				oss << "\t<sub_meshes>\n";
			}

			for (size_t i = 0; i < sub_meshes.size(); ++i)
			{
				oss << "\t\t<sub_mesh>\n";
				const SubMesh &mesh = sub_meshes[i];

				oss << "\t\t\t<name>" << mesh.name << "</name>\n";
				oss << "\t\t\t<indices_stream_name>" << mesh.indices_stream_name << "</indices_stream_name>\n";
				oss << "\t\t\t<material_name>" << mesh.material_name << "</material_name>\n";
				oss << "\t\t\t<min_index>" << mesh.min_index << "</min_index>\n";
				oss << "\t\t\t<max_index>" << mesh.max_index << "</max_index>\n";
				oss << "\t\t\t<prims_type>" << graphics::Device::getPrimTypeName(mesh.prims_type) << "</prims_type>\n";

				oss << "\t\t</sub_mesh>\n";
			}

			if (!sub_meshes.empty())
			{
				oss << "\t</sub_meshes>\n";
			}
			
			oss << "</mesh>\n";

			metafile.write(oss.str().c_str(), oss.str().size());

			return true;
		}


		bool Mesh::load(fs::InputStream &metafile, fs::InputStream &datafile)
		{
			std::string meta;
			readEntireFile(metafile, meta);

			std::istringstream iss(meta);
			
			using namespace boost::property_tree;
			typedef basic_ptree<std::string, std::string> PTree;
			PTree pt;
			Stream *stream = NULL;
			SubMesh *sub_mesh = NULL;
			try
			{
				read_xml(iss, pt);
				
				boost::optional<PTree &> streams_pt = pt.get_child_optional("mesh.streams");
				if (streams_pt)
				{
					std::pair<PTree::const_assoc_iterator, PTree::const_assoc_iterator> ms = streams_pt->equal_range("stream");
					for (PTree::const_assoc_iterator it = ms.first; it != ms.second; ++it)
					{
						const PTree &stream_pt = it->second;
						stream = new Stream;
						
						std::string name = stream_pt.get<std::string>("name");
						
						stream->type = getElemTypeByName(stream_pt.get<std::string>("type"));
						if (stream->type == STREAM_ELEM_TYPE_COUNT)
							throw;
						
						stream->size = stream_pt.get<size_t>("size");
						
						fs::off_t offset = stream_pt.get<fs::off_t>("offset");
						
						if (stream->type == ET_USHORT)
						{
							stream->short_ptr = new unsigned short[stream->size];
						}
						else if (stream->type == ET_INT)
						{
							stream->int_ptr = new int[stream->size];
						}
						else
						{
							stream->float_ptr = new float[stream->size * getElemSizeByType(stream->type) / sizeof(float)];
						}

						int bytes = stream->size * getElemSizeByType(stream->type);
						datafile.seek(offset, fs::eSeekType::HEAD);
						if (datafile.read((char *) stream->ptr, bytes) != bytes)
							throw;

						streams.insert(name, stream);
					}
				}
				
				boost::optional<PTree &> sub_meshes_pt = pt.get_child_optional("mesh.sub_meshes");
				if (sub_meshes_pt)
				{
					std::pair<PTree::const_assoc_iterator, PTree::const_assoc_iterator> sm = streams_pt->equal_range("stream");
					for (PTree::const_assoc_iterator it = sm.first; it != sm.second; ++it)
					{
						const PTree &sub_mesh_pt = it->second;
						sub_mesh = new SubMesh;

						sub_mesh->name = sub_mesh_pt.get<std::string>("name");
						sub_mesh->indices_stream_name = sub_mesh_pt.get<std::string>("indices_stream_name");
						sub_mesh->material_name = sub_mesh_pt.get<std::string>("material_name");
						sub_mesh->min_index = sub_mesh_pt.get<size_t>("min_index");
						sub_mesh->max_index = sub_mesh_pt.get<size_t>("max_index");
						sub_mesh->prims_type = graphics::Device::getPrimTypeByName(sub_mesh_pt.get<std::string>("prims_type"));

						if (sub_mesh->prims_type == graphics::Device::PRIMITIVE_TYPES_COUNT)
							throw;

						sub_meshes.push_back(sub_mesh);
					}
				}
			}
			catch (xml_parser_error &err) {
				ERROR_LOG(err.what());
				delete stream;
				delete sub_mesh;
				return false;
			}
			catch (...)
			{
				delete stream;
				delete sub_mesh;
				return false;
			}

			return true;
		}

	}
}