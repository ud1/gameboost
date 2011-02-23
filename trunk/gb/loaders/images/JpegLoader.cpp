#include "JpegLoader.h"
#include <gb/base/Types.h>

#include <cassert>
#include <cstring>
#include <jpeglib.h>

#include <gb/base/Logger.h>

namespace
{
	using namespace gb::fs;
	using namespace gb::containers;
	
	const size_t BUFFSIZE = 1024*10;
	
	struct SFileData
	{
		InputStream *in;
		OutputStream *out;
		char buffer[BUFFSIZE];
		size_t count;
		bool was_error;
	};

	METHODDEF(void) my_init_source(j_decompress_ptr pcinfo)
	{
		SFileData *data = (SFileData *) pcinfo->client_data;
		data->in->seek(0, eSeekType::HEAD);
		data->count = data->in->read(data->buffer, BUFFSIZE);
		pcinfo->src->next_input_byte = (JOCTET *) data->buffer;
		pcinfo->src->bytes_in_buffer = data->count;
	}

	METHODDEF(boolean) my_fill_input_buffer(j_decompress_ptr pcinfo)
	{
		SFileData *data = (SFileData *) pcinfo->client_data;
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
			SFileData *data = (SFileData *) pcinfo->client_data;
			data->in->seek(num_bytes - pcinfo->src->bytes_in_buffer, eSeekType::CURRENT);
			data->count = data->in->read(data->buffer, BUFFSIZE);
			pcinfo->src->next_input_byte = (JOCTET *) data->buffer;
			pcinfo->src->bytes_in_buffer = data->count;
		}
	}

	METHODDEF(void) my_init_destination (j_compress_ptr cinfo)
	{
		SFileData *data = (SFileData *) cinfo->client_data;
		cinfo->dest->next_output_byte = (JOCTET *) data->buffer;
		cinfo->dest->free_in_buffer = BUFFSIZE;
	}
	
	METHODDEF(boolean) my_empty_output_buffer(j_compress_ptr cinfo)
	{
		SFileData *data = (SFileData *) cinfo->client_data;
		if (data->out->write(data->buffer, BUFFSIZE) != BUFFSIZE)
			data->was_error = true;
		cinfo->dest->next_output_byte = (JOCTET *) data->buffer;
		cinfo->dest->free_in_buffer = BUFFSIZE;
		return TRUE;
	}

	METHODDEF(void) my_term_destination (j_compress_ptr cinfo)
	{
		SFileData *data = (SFileData *) cinfo->client_data;
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
		SFileData *data = (SFileData *) cinfo->client_data;
		data->was_error = true;
		/* Always display the message */
		(*cinfo->err->output_message) (cinfo);
		
		/* Let the memory manager delete any temp files before we die */
		jpeg_destroy(cinfo);
	}

	METHODDEF(void) my_emit_message (j_common_ptr cinfo, int msg_level)
	{
		struct jpeg_error_mgr * err = cinfo->err;
		
		if (msg_level < 0) {
		/* It's a warning message.  Since corrupt files may generate many warnings,
		* the policy implemented here is to show only the first warning,
		* unless trace_level >= 3.
			*/
			if (err->num_warnings == 0 || err->trace_level >= 3)
				(*err->output_message) (cinfo);
			/* Always count warnings in num_warnings. */
			err->num_warnings++;
		} else {
			/* It's a trace message.  Show it if trace_level >= msg_level. */
			if (err->trace_level >= msg_level)
				(*err->output_message) (cinfo);
		}
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

	/* Format a message string for the most recent JPEG error or message */
	METHODDEF(void) my_format_message (j_common_ptr cinfo, char * buffer)
	{
		struct jpeg_error_mgr * err = cinfo->err;
		int msg_code = err->msg_code;
		const char * msgtext = NULL;
		const char * msgptr;
		char ch;
		boolean isstring;
		
		/* Look up message string in proper table */
		if (msg_code > 0 && msg_code <= err->last_jpeg_message)
		{
			msgtext = err->jpeg_message_table[msg_code];
		}
		else if (err->addon_message_table != NULL &&
			msg_code >= err->first_addon_message &&
			msg_code <= err->last_addon_message)
		{
			msgtext = err->addon_message_table[msg_code - err->first_addon_message];
		}
		
		/* Defend against bogus message number */
		if (msgtext == NULL)
		{
			err->msg_parm.i[0] = msg_code;
			msgtext = err->jpeg_message_table[0];
		}
		
		/* Check for string parameter, as indicated by %s in the message text */
		isstring = false;
		msgptr = msgtext;
		while ((ch = *msgptr++) != '\0')
		{
			if (ch == '%')
			{
				if (*msgptr == 's') isstring = true;
				break;
			}
		}
		
		/* Format the message into the passed buffer */
		if (isstring)
			sprintf(buffer, msgtext, err->msg_parm.s);
		else
			sprintf(buffer, msgtext,
			err->msg_parm.i[0], err->msg_parm.i[1],
			err->msg_parm.i[2], err->msg_parm.i[3],
			err->msg_parm.i[4], err->msg_parm.i[5],
			err->msg_parm.i[6], err->msg_parm.i[7]);
	}
	
	void loadHeader(SFileData &my_data, jpeg_decompress_struct &cinfo, Image2dHeader &header_out)
	{
		jpeg_error_mgr jerr;
		cinfo.client_data = (void *) &my_data;
		cinfo.err = jpeg_std_error(&jerr);
		cinfo.marker = NULL;
		cinfo.inputctl = NULL;
		jerr.error_exit = my_error_exit;
		jerr.emit_message = my_emit_message;
		jerr.output_message = my_output_message;
		jerr.format_message = my_format_message;

		jpeg_create_decompress(&cinfo);
		jpeg_source_mgr src_mgr;

		src_mgr.init_source = my_init_source;
		src_mgr.fill_input_buffer = my_fill_input_buffer;
		src_mgr.skip_input_data = my_skip_input_data;
		src_mgr.resync_to_restart = my_resync_to_restart;
		src_mgr.term_source = my_init_source;
		
		cinfo.src = &src_mgr;
		jpeg_read_header(&cinfo, true);
		jpeg_start_decompress(&cinfo);
		
		int components = cinfo.out_color_components;
		if (components == 3)
		{
			header_out.pixel_format = ePixelFormat::RGB_888;
		}
		else if (components == 1)
		{
			header_out.pixel_format = ePixelFormat::R_8;
		}
		
		header_out.width = cinfo.output_width;
		header_out.height = cinfo.output_height;
		header_out.calculateDataSize();
	}
}

namespace gb
{
	namespace loaders
	{
		using namespace gb::fs;
		using namespace gb::containers;
		
		bool JpegLoader::loadImage2dHeader(InputStream &input, Image2dHeader &header_out)
		{
			SFileData my_data;
			my_data.in = &input;
			my_data.was_error = false;
			jpeg_decompress_struct cinfo;
			loadHeader(my_data, cinfo, header_out);
			
			jpeg_finish_decompress(&cinfo);
			jpeg_destroy_decompress(&cinfo);
			return !my_data.was_error;
		}
		
		bool JpegLoader::loadImage2d(fs::InputStream &input, containers::Image2d &image_out)
		{
			SFileData my_data;
			my_data.in = &input;
			my_data.was_error = false;
			jpeg_decompress_struct cinfo;
			loadHeader(my_data, cinfo, image_out);
			
			for (size_t rows = 0; rows < image_out.height && !my_data.was_error;)
			{
				const int max_rows_per_read = 1;
				JSAMPROW row_pointers[max_rows_per_read];
				for(int row = 0; row < max_rows_per_read; ++row)
				{
					row_pointers[row] = (JSAMPLE *) &image_out.data[(rows + row) * image_out.row_size_in_bytes];
				}
				
				rows += jpeg_read_scanlines(&cinfo, row_pointers, max_rows_per_read);
			}
			
			jpeg_finish_decompress(&cinfo);
			jpeg_destroy_decompress(&cinfo);
			return !my_data.was_error;
		}
		
		bool JpegLoader::saveImage2d(fs::OutputStream &output, const containers::Image2d &image)
		{
			if (!(image.pixel_format == ePixelFormat::RGB_888 || image.pixel_format == ePixelFormat::R_8))
			{
				Image2d temp;
				temp.width = image.width;
				temp.height = image.height;
				
				if (getPFDescription(image.pixel_format)->components == 1)
					temp.pixel_format = ePixelFormat::R_8;
				else temp.pixel_format = ePixelFormat::RGB_888;
				
				temp.calculateDataSize();
				temp.data = new char[temp.data_size];
				
				convert(image, temp);
				
				bool res = saveImage2d(output, temp);
				
				delete []temp.data;
				return res;
			}
			
			jpeg_compress_struct cinfo;
			jpeg_error_mgr jerr;
			JSAMPROW row_pointer[1];
			int row_stride;
			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_compress(&cinfo);
		
			SFileData my_data;
			my_data.out = &output;
			my_data.was_error = false;

			jpeg_destination_mgr dest;
			dest.empty_output_buffer = my_empty_output_buffer;
			dest.init_destination = my_init_destination;
			dest.term_destination = my_term_destination;

			cinfo.client_data = (void *) &my_data;
			cinfo.image_width = image.width; 	/* image width and height, in pixels */
			cinfo.image_height = image.height;

			if (image.pixel_format == ePixelFormat::R_8)
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
				row_pointer[0] = (JSAMPLE *) &image.data[cinfo.next_scanline * image.row_size_in_bytes];
				jpeg_write_scanlines(&cinfo, row_pointer, 1);
			}
			
			jpeg_finish_compress(&cinfo);
			jpeg_destroy_compress(&cinfo);

			return !my_data.was_error;
		}
	}
}
