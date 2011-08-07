#include "JpegLoader.h"
#include <gb/base/Types.h>
#include <gb/fs/Stream.h>
#include <gb/containers/Image.h>

#include <cassert>
#include <cstring>
#include <jpeglib.h>

#include <gb/logging/Logger.h>

namespace
{
	using namespace gb::fs;
	using namespace gb::containers;
	
	const size_t BUFFSIZE = 1024*10;
	
	struct FileData
	{
		InputStream *in;
		OutputStream *out;
		char buffer[BUFFSIZE];
		size_t count;
		bool was_error;
	};

	struct DecompressData
	{
		jpeg_source_mgr src_mgr;
		jpeg_decompress_struct cinfo;
		jpeg_error_mgr jerr;
		FileData my_data;
	};

	METHODDEF(void) my_init_source(j_decompress_ptr pcinfo)
	{
		FileData *data = (FileData *) pcinfo->client_data;
		data->in->seek(0, eSeekType::HEAD);
		data->count = data->in->read(data->buffer, BUFFSIZE);
		pcinfo->src->next_input_byte = (JOCTET *) data->buffer;
		pcinfo->src->bytes_in_buffer = data->count;
	}

	METHODDEF(boolean) my_fill_input_buffer(j_decompress_ptr pcinfo)
	{
		FileData *data = (FileData *) pcinfo->client_data;
		data->count = data->in->read(data->buffer, BUFFSIZE);
		if (!data->count)
			return FALSE;
		pcinfo->src->next_input_byte = (JOCTET *) data->buffer;
		pcinfo->src->bytes_in_buffer = data->count;
		return TRUE;
	}

	METHODDEF(boolean) my_resync_to_restart(j_decompress_ptr pcinfo, int desired)
	{
		return false;
	}

	METHODDEF(void) my_skip_input_data(j_decompress_ptr pcinfo, long num_bytes)
	{
		if (pcinfo->src->bytes_in_buffer > num_bytes)
		{
			pcinfo->src->next_input_byte += (size_t) num_bytes;
			pcinfo->src->bytes_in_buffer -= (size_t) num_bytes;
		}
		else
		{
			FileData *data = (FileData *) pcinfo->client_data;
			data->in->seek(num_bytes - pcinfo->src->bytes_in_buffer, eSeekType::CURRENT);
			data->count = data->in->read(data->buffer, BUFFSIZE);
			pcinfo->src->next_input_byte = (JOCTET *) data->buffer;
			pcinfo->src->bytes_in_buffer = data->count;
		}
	}

	METHODDEF(void) my_init_destination (j_compress_ptr cinfo)
	{
		FileData *data = (FileData *) cinfo->client_data;
		cinfo->dest->next_output_byte = (JOCTET *) data->buffer;
		cinfo->dest->free_in_buffer = BUFFSIZE;
	}
	
	METHODDEF(boolean) my_empty_output_buffer(j_compress_ptr cinfo)
	{
		FileData *data = (FileData *) cinfo->client_data;
		if (data->out->write(data->buffer, BUFFSIZE) != BUFFSIZE)
			data->was_error = true;
		cinfo->dest->next_output_byte = (JOCTET *) data->buffer;
		cinfo->dest->free_in_buffer = BUFFSIZE;
		return TRUE;
	}

	METHODDEF(void) my_term_destination (j_compress_ptr cinfo)
	{
		FileData *data = (FileData *) cinfo->client_data;
		size_t size = BUFFSIZE - cinfo->dest->free_in_buffer;
		if (size)
		{
			data->out->write(data->buffer, size);
			cinfo->dest->next_output_byte = (JOCTET *) data->buffer;
			cinfo->dest->free_in_buffer = BUFFSIZE;
		}	
	}

	METHODDEF(void) my_error_exit(j_common_ptr cinfo)
	{
		FileData *data = (FileData *) cinfo->client_data;
		data->was_error = true;
		/* Always display the message */
		(*cinfo->err->output_message) (cinfo);
		
		/* Let the memory manager delete any temp files before we die */
		jpeg_destroy(cinfo);
	}

	/* Routine that actually outputs a trace or error message */
	METHODDEF(void) my_output_message (j_common_ptr cinfo)
	{
		char buffer[JMSG_LENGTH_MAX];
		
		/* Create the message */
		(*cinfo->err->format_message) (cinfo, buffer);

		/* Send it to stderr, adding a newline */
		WARNING_LOG(buffer);
	}
	
	void loadHeader(DecompressData &ddata, ImageHeader &header_out)
	{
		ddata.my_data.was_error = false;
		ddata.cinfo.client_data = (void *) &ddata.my_data;
		ddata.cinfo.err = jpeg_std_error(&ddata.jerr);
		ddata.cinfo.marker = NULL;
		ddata.cinfo.inputctl = NULL;
		ddata.jerr.error_exit = my_error_exit;
		ddata.jerr.output_message = my_output_message;

		jpeg_create_decompress(&ddata.cinfo);

		ddata.src_mgr.init_source = my_init_source;
		ddata.src_mgr.fill_input_buffer = my_fill_input_buffer;
		ddata.src_mgr.skip_input_data = my_skip_input_data;
		ddata.src_mgr.resync_to_restart = my_resync_to_restart;
		ddata.src_mgr.term_source = my_init_source;
		
		ddata.cinfo.src = &ddata.src_mgr;
		jpeg_read_header(&ddata.cinfo, true);
		jpeg_start_decompress(&ddata.cinfo);
		
		int components = ddata.cinfo.out_color_components;
		if (components == 3)
		{
			header_out.pixel_format = ePixelFormat::RGB_888;
		}
		else if (components == 1)
		{
			header_out.pixel_format = ePixelFormat::R_8;
		}
		
		header_out.width = ddata.cinfo.output_width;
		header_out.height = ddata.cinfo.output_height;
		header_out.calculateDataSize();
	}
}

namespace gb
{
	namespace loaders
	{
		using namespace gb::fs;
		using namespace gb::containers;
		
		bool JpegLoader::loadImageHeader(InputStream &input, ImageHeader &header_out)
		{
			DecompressData ddata;
			ddata.my_data.in = &input;
			loadHeader(ddata, header_out);
			
			jpeg_destroy_decompress(&ddata.cinfo);
			return !ddata.my_data.was_error;
		}
		
		bool JpegLoader::loadImage(fs::InputStream &input, containers::Image &image_out)
		{
			DecompressData ddata;
			ddata.my_data.in = &input;
			
			loadHeader(ddata, image_out);
			
			for (size_t rows = 0; rows < image_out.height && !ddata.my_data.was_error;)
			{
				const int max_rows_per_read = 8;
				JSAMPROW row_pointers[max_rows_per_read];
				for(int row = 0; row < max_rows_per_read; ++row)
				{
					row_pointers[row] = (JSAMPLE *) &image_out.data[(rows + row) * image_out.pitch];
				}
				
				rows += jpeg_read_scanlines(&ddata.cinfo, row_pointers, max_rows_per_read);
			}
			
			jpeg_finish_decompress(&ddata.cinfo);
			jpeg_destroy_decompress(&ddata.cinfo);
			return !ddata.my_data.was_error;
		}
		
		bool JpegLoader::saveImage(fs::OutputStream &output, const containers::Image &image)
		{
			if (!(image.pixel_format == ePixelFormat::RGB_888 || image.pixel_format == ePixelFormat::GRAYSCALE8))
			{
				Image temp;
				temp.width = image.width;
				temp.height = image.height;
				
				if (getPFDescription(image.pixel_format)->components == 1)
					temp.pixel_format = ePixelFormat::GRAYSCALE8;
				else temp.pixel_format = ePixelFormat::RGB_888;
				
				temp.calculateDataSize();
				temp.pitch = temp.row_size + temp.padding_bytes;
				temp.data = new char[temp.data_size];
				
				convert(image, temp);
				
				bool res = saveImage(output, temp);
				
				delete []temp.data;
				return res;
			}
			
			jpeg_compress_struct cinfo;
			jpeg_error_mgr jerr;
			JSAMPROW row_pointer[1];
			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_compress(&cinfo);
		
			FileData my_data;
			my_data.out = &output;
			my_data.was_error = false;

			jpeg_destination_mgr dest;
			dest.empty_output_buffer = my_empty_output_buffer;
			dest.init_destination = my_init_destination;
			dest.term_destination = my_term_destination;

			cinfo.client_data = (void *) &my_data;
			cinfo.image_width = image.width; 	/* image width and height, in pixels */
			cinfo.image_height = image.height;

			if (image.pixel_format == ePixelFormat::GRAYSCALE8)
			{
				cinfo.input_components = 1;
				cinfo.in_color_space = JCS_GRAYSCALE;
			}
			else
			{
				cinfo.input_components = 3;
				cinfo.in_color_space = JCS_RGB;
			}
			
			cinfo.dest = &dest;
			
			jpeg_set_defaults(&cinfo);
			jpeg_set_quality(&cinfo, quality, true);

			jpeg_start_compress(&cinfo, true);
			
			while (cinfo.next_scanline < cinfo.image_height && !my_data.was_error)
			{
				row_pointer[0] = (JSAMPLE *) &image.data[cinfo.next_scanline * image.pitch];
				jpeg_write_scanlines(&cinfo, row_pointer, 1);
			}
			
			jpeg_finish_compress(&cinfo);
			jpeg_destroy_compress(&cinfo);

			return !my_data.was_error;
		}
	}
}
