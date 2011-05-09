#include <math.h>
#include <sstream>
#include <fstream>
#include <cassert>
#include <vector>
#include <gb/terrain/ElevationData.h>
#include <gb/math/math.h>
#include <gb/loaders/images/BmpLoader.h>
#include <gb/loaders/images/JpegLoader.h>
#include <gb/fs/LocalFS.h>
#include <gb/containers/Image.h>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/concept_check.hpp>

namespace po = boost::program_options;

using namespace gb;
using namespace gb::loaders;
using namespace gb::terrain;
using namespace gb::containers;

struct NormalsInfo
{
	int l, x, y;
	std::string filename;
};

std::vector<NormalsInfo *> normals_filenames;

fs::LocalFS *file_system;
BmpLoader bmp_loader;
JpegLoader jpg_loader;
std::string image_format = "jpg";

const int NORMALS_SIZE = 256;
const int BORDER_SIZE = 4;

void initElevationData(ElevationData *el_data, float *data, int line_stride, bool e_edge, bool s_edge)
{
	for (int i = 0; i < TER_NODE_SIZE1; ++i)
	{
		for (int j = 0; j < TER_NODE_SIZE1; ++j)
		{
			el_data->data[i*TER_NODE_SIZE_WITH_PADDING + j] = 0;
		}
	}
	
	for (int i = 0; i < TER_NODE_SIZE; ++i)
	{
		float *ptr = data + i*line_stride;
		for (int j = 0; j < TER_NODE_SIZE; ++j)
		{
			el_data->data[i*TER_NODE_SIZE_WITH_PADDING + j] = (ElevationData::height_t) ptr[j];
		}
		
		if (!e_edge)
		{
			el_data->data[i*TER_NODE_SIZE_WITH_PADDING + TER_NODE_SIZE] = (ElevationData::height_t) ptr[TER_NODE_SIZE];
		}
		else
		{
			el_data->data[i*TER_NODE_SIZE_WITH_PADDING + TER_NODE_SIZE] = el_data->data[i*TER_NODE_SIZE_WITH_PADDING + TER_NODE_SIZE-1];
		}
	}
	
	float *ptr = data + TER_NODE_SIZE*line_stride;
	for (int i = 0; i <= TER_NODE_SIZE; ++i)
	{
		if (!s_edge)
		{
			el_data->data[TER_NODE_SIZE*TER_NODE_SIZE_WITH_PADDING + i] = (ElevationData::height_t) ptr[i];
		}
		else
		{
			el_data->data[TER_NODE_SIZE*TER_NODE_SIZE_WITH_PADDING + i] = el_data->data[(TER_NODE_SIZE-1)*TER_NODE_SIZE_WITH_PADDING + i];
		}
	}
}

void initBucket(ElevationDataBucket *buck, float *data, int line_stride, bool e_edge_, bool s_edge_)
{
	for (int i = 0; i < ELEVATION_DATA_BUCKET_SIZE; ++i)
	{
		for (int j = 0; j < ELEVATION_DATA_BUCKET_SIZE; ++j)
		{
			float *ptr = data + i*TER_NODE_SIZE*line_stride + j*TER_NODE_SIZE;
			bool e_edge = e_edge_ && (j == ELEVATION_DATA_BUCKET_SIZE-1);
			bool s_edge = s_edge_ && (i == ELEVATION_DATA_BUCKET_SIZE-1);
			initElevationData(&buck->data[i*ELEVATION_DATA_BUCKET_SIZE+j], ptr, line_stride, e_edge, s_edge);
		}
	}
}

// lev_x, lev_y -- bucket's lods ( equal to elevation data lods + LOG2_ELEVATION_DATA_BUCKET_SIZE )
void saveIntoBuckets(float *data, int width, int lev, const std::string &path)
{
	assert(width % (TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE) == 0);
	int w = width/(TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE);

	ElevationDataBucket *el = new ElevationDataBucket[w*w];
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			float *ptr = data + i*TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE*width + j*TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE;
			bool e_edge = (j == w-1);
			bool s_edge = (i == w-1);
			initBucket(&el[i*w+j], ptr, width, e_edge, s_edge);
		}
	}

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			el[i*w + j].computeErrors();
			std::stringstream ss;
			ss << path << "l" << lev << "x" << j << "y" << i << ".raw";
			fs::OutputStream *file = file_system->getOutputStream(ss.str(), true);
			el[i*w + j].saveToFile(file);
			file->release();
		}
	}

	delete []el;
}

void addIntoRootNode(float *data, int width, int lev, RootElevationDataBucket *root)
{
	int size = 1 << lev;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			float *ptr = data + i*TER_NODE_SIZE*width + j*TER_NODE_SIZE;
			ElevationData *el_data = root->get(lev, j, i);
			initElevationData(el_data, ptr, width, j == size-1, i == size-1);
			el_data->computeErrors();
		}
	}
}

void computeNormals(ElevationData::height_t *buf, int width, float lin_x, float lin_y, math::vec3 *out_normals)
{
	const float TNSRX = lin_x / width;
	const float TNSRY = lin_y / width;
	// Compute normals at center
	math::vec3 dx = math::vec3(TNSRX, 0.0f, 0.0f);
	math::vec3 dy = math::vec3(0.0f, TNSRY, 0.0f);
	math::vec3 dz = math::vec3(0.0f, 0.0f, 1.0f);
	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float H = buf[y*width + x];
			//       | nv
			//       |
			//  wv   !    ev
			//  ----->----->
			//       |
			//       |
			//       ! sv
			math::vec3 wv, ev, nv, sv;
			float h;
			if (x > 0)
			{
				h = buf[y*width + x - 1];
				wv = dx + dz*(H - h);
				wv = math::normalize(wv);
			}
			else
			{
				h = buf[y*width + x + 1];
				ev = dx + dz*(h - H);
				ev = math::normalize(ev);
			}
			
			if (x < width-1)
			{
				h = buf[y*width + x + 1];
				ev = dx + dz*(h - H);
				ev = math::normalize(ev);
			}
			else
			{
				h = buf[y*width + x - 1];
				wv = dx + dz*(H - h);
				wv = math::normalize(wv);
			}
			
			if (y > 0)
			{
				h = buf[(y - 1)*width + x];
				nv = dy + dz*(H - h);
				nv = math::normalize(nv);
			}
			else
			{
				h = buf[(y + 1)*width + x];
				sv = dy + dz*(h - H);
				sv = math::normalize(sv);
			}
			
			if (y < width-1)
			{
				h = buf[(y + 1)*width + x];
				sv = dy + dz*(h - H);
				sv = math::normalize(sv);
			}
			else
			{
				h = buf[(y - 1)*width + x];
				nv = dy + dz*(H - h);
				nv = math::normalize(nv);
			}

			math::vec3 tx = wv + ev;
			math::vec3 ty = nv + sv;
			// Compute normal
			out_normals[y*width + x] = math::normalize(math::cross(tx, ty));
		}
	}
}

bool is_pow_of_2(int w)
{
	for (int i = 0; i < sizeof(int)*8-1; ++i)
	{
		if (w == (1 << i))
			return true;
	}
	return false;
}

bool readInputRawFile(ElevationData::height_t *buf, const std::string &file_in, int width)
{
	fs::InputStream *file = file_system->getInputStream(file_in);
	if (!file)
	{
		std::cout << "Input file not found\n";
		return false;
	}
	int bytes_readed = file->read((char *) buf, width*width*sizeof(ElevationData::height_t));
	file->release();
	if (bytes_readed != width*width*sizeof(ElevationData::height_t))
	{
		std::cout << "Input file is too small\n";
		return false;
	}
	return true;
}

void saveImage(const std::string &filename, const Image &im)
{
	fs::OutputStream *file = file_system->getOutputStream(filename, true);
	if (image_format == "bmp")
		bmp_loader.saveImage(*file, im);
	else jpg_loader.saveImage(*file, im);
	file->release();
}

void saveNormals(math::vec3 *normals, int width, int lod, const std::string &path)
{
	enum {N = 1, S = 2, E = 4, W = 8};
	int nx = width / NORMALS_SIZE;
	int ny = width / NORMALS_SIZE;
	Image image;
	image.width = NORMALS_SIZE+2*BORDER_SIZE;
	image.height = NORMALS_SIZE+2*BORDER_SIZE;
	image.pixel_format = ePixelFormat::BGR_888;
	image.pitch = (NORMALS_SIZE+2*BORDER_SIZE)*3;
	image.data = new char[(NORMALS_SIZE+2*BORDER_SIZE)*(NORMALS_SIZE+2*BORDER_SIZE)*3];
	for (int i = 0; i < ny; ++i)
	{
		for (int j = 0; j < nx; ++j)
		{
			int flag = 0;
			if (i == 0)
				flag |= N;
			if (i == ny-1)
				flag |= S;
			if (j == 0)
				flag |= W;
			if (j == nx-1)
				flag |= E;
			math::vec3 *ptr = &normals[i*NORMALS_SIZE*width + j*NORMALS_SIZE];
			for (int y = -BORDER_SIZE; y < NORMALS_SIZE+BORDER_SIZE; ++y)
			{
				for (int x = -BORDER_SIZE; x < NORMALS_SIZE+BORDER_SIZE; ++x)
				{
					unsigned char *im_data_ptr = (unsigned char *) &image.data[((y+BORDER_SIZE)*(NORMALS_SIZE+2*BORDER_SIZE)+(x+BORDER_SIZE))*3];
					int rx = x, ry = y;
					if (rx < 0 && (flag & W))
						rx = 0;
					if (ry < 0 && (flag & N))
						ry = 0;
					if (rx >= NORMALS_SIZE && (flag & E))
						rx = NORMALS_SIZE - 1;
					if (ry >= NORMALS_SIZE && (flag & S))
						ry = NORMALS_SIZE-1;
					math::vec3 normal = ((math::normalize(ptr[ry*width+rx])*0.5f)+0.5f)*255.0f;
					im_data_ptr[0] = (unsigned char) normal.z;
					im_data_ptr[1] = (unsigned char) normal.y;
					im_data_ptr[2] = (unsigned char) normal.x;
				}
			}
			std::stringstream ss;
			ss << "l" << lod << "x" << j << "y" << i << "." << image_format;
			NormalsInfo *info = new NormalsInfo;
			info->l = lod;
			info->x = j;
			info->y = i;
			info->filename = ss.str();
			normals_filenames.push_back(info);
			saveImage(path + ss.str(), image);
		}
	}
	delete []image.data;
}

int main(int argc, char **argv) {
	std::string input_file="data.raw", output_file="terrain";
	float size_x=4096.f, size_y=4096.f, lin_scale_z=1.0f/90.0f;
	int width = 4096;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("raw_data_in", po::value<std::string>(&input_file), "input raw data file with heights (16 bit)")
		("w", po::value<int>(&width), "size of the input heightmap image")
		("size_x", po::value<float>(&size_x), "x-dimension size of the terrain in meters")
		("size_y", po::value<float>(&size_y), "y-dimension of the terrain in meters")
		("scale_z", po::value<float>(&lin_scale_z), "size of one height unit of the input heightmap in meters")
		("out", po::value<std::string>(&output_file), "output_file_heights directory will store the heights, output_file_normals.big_image file - metadata, output_file_normals directory - normals")
		("image_format", po::value<std::string>(&image_format), "image format for normals, jpg/bmp")
	;
	
	if (image_format != "jpg" && image_format != "bmp")
	{
		std::cout << "invalid image format " << image_format << "\n";
		return 0;
	}

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	file_system = new fs::LocalFS;

	if (width < TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE || !is_pow_of_2(width)) {
		std::cout << "w must be power of 2, greater than " << TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE << "\n";
		return 1;
	}

	std::string path_height, path_normals, normals_metadata;
	path_height = output_file + "_heights/";
	path_normals = output_file + "_normals/";
	normals_metadata = output_file + "_normals.big_image";
	boost::filesystem::create_directory((output_file+"_heights").c_str());
	boost::filesystem::create_directory((output_file+"_normals").c_str());

	ElevationData::height_t *buf_raw = new ElevationData::height_t[width*width];
	if(!readInputRawFile(buf_raw, input_file, width))
	{
		delete []buf_raw;
		return 0;
	}

	float *buf = new float[width*width];
	std::copy(buf_raw, buf_raw + width*width, buf);

	// maximum lod
	int lod = math::ilog2(width / (TER_NODE_SIZE));
	RootElevationDataBucket root_bucket;

	int buf_width = width;
	for(;;)
	{
		std::cout << "lod " << lod << "\n";


		if (buf_width >= TER_NODE_SIZE*ELEVATION_DATA_BUCKET_SIZE)
		{
			saveIntoBuckets(buf, buf_width, lod - LOG2_ELEVATION_DATA_BUCKET_SIZE, path_height);
		}
		else
		{
			addIntoRootNode(buf, buf_width, lod, &root_bucket);
		}

		if ((buf_width /= 2) < TER_NODE_SIZE)
			break;

		float *new_buf = new float[buf_width * buf_width];
		for (int i = 0; i < buf_width; ++i)
		{
			for (int j = 0; j < buf_width; ++j)
			{
				if (i % TER_NODE_SIZE && j % TER_NODE_SIZE)
				{
					new_buf[i*buf_width+j] = (
						buf[(2*i+0)*2*buf_width+2*j+0] + 
						buf[(2*i+0)*2*buf_width+2*j+1] + 
						buf[(2*i+1)*2*buf_width+2*j+0] + 
						buf[(2*i+1)*2*buf_width+2*j+1]) / 4.0f;
				}
				else
				{
					new_buf[i*buf_width+j] = buf[2*i*2*buf_width+2*j];
				}
			}
		}

		delete []buf;
		buf = new_buf;
		--lod;
	}
	
	delete []buf;

	root_bucket.computeErrors();
	fs::OutputStream *file = file_system->getOutputStream((path_height + "root.raw").c_str(), true);
	root_bucket.saveToFile(file);
	file->release();
	
	//////////----------- Compute normals -------------/////////////
	std::cout << "Compute normals\n";

	math::vec3 *normals = new math::vec3[width*width];
	computeNormals(buf_raw, width, size_x/lin_scale_z, size_y/lin_scale_z, normals);
	delete []buf_raw;

	std::cout << "Save normals\n";
	lod = math::ilog2(width / (NORMALS_SIZE));
	buf_width = width;
	for(;;)
	{
		std::cout << "lod " << lod << "\n";
		saveNormals(normals, buf_width, lod, path_normals);

		if ((buf_width /= 2) < NORMALS_SIZE)
			break;

		math::vec3 *new_normals = new math::vec3[buf_width * buf_width];
		for (int i = 0; i < buf_width; ++i)
		{
			for (int j = 0; j < buf_width; ++j)
			{
				new_normals[i*buf_width+j] =
					normals[(2*i+0)*2*buf_width+j+0] +
					normals[(2*i+1)*2*buf_width+j+0] +
					normals[(2*i+0)*2*buf_width+j+1] +
					normals[(2*i+1)*2*buf_width+j+1];
			}
		}

		delete []normals;
		normals = new_normals;

		--lod;
	}

	delete []normals;

	// Write BigImage file
	std::stringstream oss;
	oss << "width " << width << "\n";
	oss << "height " << width << "\n";
	oss << "node_size " << NORMALS_SIZE << "\n";
	oss << "border_size " << BORDER_SIZE << "\n";
	oss << "path " << path_normals << "\n\n";

	for (size_t i = 0; i < normals_filenames.size(); ++i)
	{
		NormalsInfo *info = normals_filenames[i];
		oss << "sub_image "
			<< info->l << " "
			<< info->x << " "
			<< info->y << " "
			<< info->filename << "\n";
		delete info;
	}
	
	fs::OutputStream *normals_meta_file = file_system->getOutputStream(normals_metadata, true);
	if (!normals_meta_file)
		return 0;
	
	normals_meta_file->write(oss.str().c_str(), oss.str().size());
	normals_meta_file->release();
	
	delete file_system;
	return 0;
}
