#include "GLDevice.h"
#include <gb/containers/Image.h>
#include <cassert>
#include <gb/mt/ThreadPolicy.h>
#include <gb/t/debug_cast.h>
#include <gb/base/Logger.h>
#include <gb/window_subsystem/Window.h>

#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif

#include <GL3/gl3.h>

#include <vector>
#include <map>

#include <boost/tokenizer.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <sstream>
#include <boost/concept_check.hpp>

#ifdef WIN32
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glew32.lib" )
#endif

//------------------- Safe opengl refcountable objects deletion macros---------

#define SAFE_OBJECT_DELETION													\
	void DestroyThis() {														\
		if (ThreadMapping::getCurrentThreadGroup() == RENDER_THREAD_GROUP) {	\
			delete this;														\
			return;																\
		}																		\
		device->forDeletion_(this); /*delete later by render thread*/			\
	}
	

	
namespace
{
	using namespace gb::graphics;
	using namespace gb::base;
	using namespace gb::containers;
	using namespace gb::mt;
	using gb::t::debug_cast;
	namespace ws = gb::window_subsystem;
	
	//------------------------------ Texture --------------------------------------

	const GLenum MagMinFilter[] =
	{
		GL_NEAREST,
		GL_LINEAR,
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR,
	};

	const GLenum CubeMapFace[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};

	const GLenum Target[] =
	{
		GL_TEXTURE_2D, 
		GL_TEXTURE_3D,
		GL_TEXTURE_CUBE_MAP,
	};

	bool getGLPixelFormat(ePixelFormat::PixelFormat pf, GLenum &data_format, GLenum &data_type, GLuint &internal_format)
	{
		switch (pf)
		{
			case ePixelFormat::R_8:
				data_format = GL_RED;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = 1;
				return true;
			case ePixelFormat::RGB_888:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::RGBA_8888:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGBA;
			case ePixelFormat::RGBA_16_16_16_16:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT;
				internal_format = GL_RGBA16;
				return true;
			case ePixelFormat::BGR_888:
				data_format = GL_BGR;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::BGRA_8888:
				data_format = GL_BGRA;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGBA;
				return true;
			case ePixelFormat::RGB_332:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_BYTE_3_3_2;
				internal_format = GL_R3_G3_B2;
				return true;
			case ePixelFormat::RGB_565:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_SHORT_5_6_5;
				internal_format = GL_RGB5;
				return true;
			case ePixelFormat::RGBA_4444:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT_4_4_4_4;
				internal_format = GL_RGBA4;
				return true;
			case ePixelFormat::RGBA_5551:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT_5_5_5_1;
				internal_format = GL_RGB5_A1;
				return true;
			case ePixelFormat::RGBA_10_10_10_2:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_INT_10_10_10_2;
				internal_format = GL_RGB10_A2;
				return true;
			case ePixelFormat::GRAYSCALE8:
				data_format = GL_LUMINANCE;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_LUMINANCE;
				return true;
			case ePixelFormat::GRAYSCALE16:
				data_format = GL_LUMINANCE;
				data_type = GL_UNSIGNED_SHORT;
				internal_format = GL_LUMINANCE16;
				return true;
			case ePixelFormat::FGRAYSCALE:
				data_format = GL_LUMINANCE;
				data_type = GL_FLOAT;
				internal_format = GL_LUMINANCE16;
				return true;
			case ePixelFormat::FR:
				data_format = GL_RED;
				data_type = GL_FLOAT;
				internal_format = 1;
				return true;
			case ePixelFormat::FRGB:
				data_format = GL_RGB;
				data_type = GL_FLOAT;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::FRGBA:
				data_format = GL_RGBA;
				data_type = GL_FLOAT;
				internal_format = GL_RGBA;
				return true;
		};
		
		return false;
	}
	
	class CTexture : public Texture
	{
	public:
		SAFE_OBJECT_DELETION

		CTexture(Type _type, GLDevice *device_)
		{
			device = device_;
			type = _type;
			is_autogenerate_mipmaps = true;
			glGenTextures(1, &textureID);
			setBorderType(TB_REPEAT);
			setMinFilter(TF_LINEAR_MIPMAP_LINEAR);
			setMagFilter(TF_LINEAR);
			mip_levels = 1;
		}
		
		~CTexture()
		{
			glDeleteTextures(1, &textureID);
		}
		
		bool setImage(const Image *im, size_t mipLevel)
		{
			return setImageOnCubeFace(im, PosX, mipLevel);
		}

		bool setImageOnCubeFace(const Image *im, CubeFace face, size_t mipLevel)
		{
			if ((size_t) im->data & 3)
			{
				// Данные не выровнены, придется сначала скопировать
				AutoImage auto_image;
				auto_image.copyFrom(*im, im->pixel_format);
				return setImageOnCubeFace(&(const Image &)auto_image, face, mipLevel);
			}
			
			bind();

			GLuint internal_format;
			GLenum data_format;
			GLenum data_type;

			if (!getGLPixelFormat(im->pixel_format, data_format, data_type, internal_format))
				return false;

			GLint row_len = im->pitch / (getPFDescription(im->pixel_format)->bits/8);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, row_len);
			
			switch (type)
			{
				case Texture2D:
					width = im->width;
					height = im->height;
					glTexImage2D(target, mipLevel, internal_format, im->width, im->height, 0, data_format, data_type, im->data);
					break;
				case Texture3D:
					width = im->width;
					height = im->height;
					depth = im->depth;
					glTexImage3D(target, mipLevel, internal_format, im->width, im->height, im->depth, 0, data_format, data_type, im->data);
					break;
				case TextureCube:
					width = im->width;
					height = im->height;
					glTexImage2D(CubeMapFace[face], mipLevel, internal_format, im->width, im->height, 0, data_format, data_type, im->data);
					break;
				default:
					unbind();
					return false;
			}

			if (im->data && is_autogenerate_mipmaps && min_filter > TF_LINEAR)
			{
				glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, mipLevel);
				glGenerateMipmap(target);
			}

			unbind();
			return true;
		}

		void generateMipMaps()
		{
			if (min_filter > TF_LINEAR)
			{
				bind();
				glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
				glGenerateMipmap(target);
				unbind();
			}
		}

		bool setSubImage(const Image *im, int xoff, int yoff, int zoff, size_t mipLevel)
		{
			return setSubImageOnCubeFace(im, xoff, yoff, zoff, PosX, mipLevel);
		}

		bool setSubImageOnCubeFace(const Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel)
		{
			if ((size_t) im->data & 3)
			{
				// Данные не выровнены, придется сначала скопировать
				AutoImage auto_image;
				auto_image.copyFrom(*im, im->pixel_format);
				return setImageOnCubeFace(&(const Image &)auto_image, face, mipLevel);
			}
			
			bind();

			GLuint internal_format;
			GLenum data_format;
			GLenum data_type;

			getGLPixelFormat(im->pixel_format, data_format, data_type, internal_format);

			GLint row_len = im->pitch / (getPFDescription(im->pixel_format)->bits/8);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, row_len);
			
			switch (type)
			{
				case Texture2D:
					glTexSubImage2D(target, mipLevel, xoff, yoff, im->width, im->height, data_format, data_type, im->data);
					break;
				case Texture3D:
					glTexSubImage3D(target, mipLevel, xoff, yoff, zoff, im->width, im->height, im->depth, data_format, data_type, im->data);
					break;
				case TextureCube:
					glTexSubImage2D(CubeMapFace[face], mipLevel, xoff, yoff, im->width, im->height, data_format, data_type, im->data);
					break;
				default:
					unbind();
					return false;
			}

			if (im->data && is_autogenerate_mipmaps && min_filter > TF_LINEAR)
			{
				glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, mipLevel);
				glGenerateMipmap(target);
			}

			unbind();
			return true;
		}

		void setMinFilter(TextureFilter filter)
		{
			bind();
			min_filter = filter;
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MagMinFilter[min_filter]);	
			unbind();
		}

		void setMagFilter(TextureFilter filter)
		{
			bind();
			mag_filter = filter;
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagMinFilter[mag_filter]);	
			unbind();
		}

		void setMaxLod(float lod)
		{
			bind();
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, lod);
			unbind();
		}

		void setBorderType(TextureBorder border_type_)
		{
			bind();
			GLuint brd_type; 
			border_type = border_type_;
			switch (border_type)
			{
				case TB_CLAMP:
					brd_type = GL_CLAMP_TO_EDGE;
					break;

				case TB_REPEAT:
					brd_type = GL_REPEAT;
					break;
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, brd_type);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, brd_type);
			unbind();
		}

		void bind()
		{
			target = Target[type];
			glBindTexture(target, textureID);
		}

		void unbind()
		{
			glBindTexture(target, 0);
		}

		RefCntHolder<GLDevice> device;
		GLuint textureID;
		TextureFilter min_filter, mag_filter;
		TextureBorder border_type;
		GLenum target;
	};

	//------------------------------ Buffer ---------------------------------------
	class CBuffer;
	typedef std::vector<RefCntHolder<CBuffer> > BindedBuffers;
	BindedBuffers binded_buffers;
	
	class CBuffer : public Buffer
	{
	public:
		SAFE_OBJECT_DELETION

		CBuffer(GLenum _target, GLDevice *device_)
		{
			device = device_;
			glGenBuffers(1, &bufId);
			is_created = false;
			target = _target;
		}

		~CBuffer()
		{
			glDeleteBuffers(1, &bufId);
		}

		void* map(size_t offset_bytes, size_t size) {
			assert(offset_bytes + size <= nelements * element_size);
			bind();
			if (!is_created)
			{
				glBufferData(target, nelements * element_size, 0, GL_STATIC_DRAW);
				is_created = true;
			}
			
			void *res;
			if (size == 0)
			{
				res = glMapBuffer(target, GL_WRITE_ONLY);
			}
			else
			{
				res = glMapBufferRange(target, offset_bytes, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
			}
			unbind();
			return res;
		}

		void unmap()
		{
			bind();
			glUnmapBuffer(target);
			unbind();
		}
		
		void subData(size_t offset_bytes, size_t size, void *data)
		{
			if (!size)
				size = nelements * element_size - offset_bytes;
			assert(offset_bytes + size <= nelements * element_size);
			
			bind();
			if (!is_created)
			{
				glBufferData(target, nelements * element_size, 0, GL_STATIC_DRAW);
				is_created = true;
			}
			
			glBufferSubData(target, offset_bytes, size, data);
			unbind();
		}

		void bind()
		{
			if (!is_binded)
			{
				glBindBuffer(target, bufId);
				is_binded = true;
				binded_buffers.push_back(this);
			}
		}

		void unbind()
		{
			BindedBuffers::iterator it, it_end;
			it = binded_buffers.begin();
			it_end = binded_buffers.end();
			for (;it != it_end; ++it)
			{
				(*it)->is_binded = false;
			}
			binded_buffers.clear();
			glBindBuffer(target, 0);
		}

	protected:
		GLDevice *device;
		GLuint bufId;
		GLenum target;
		bool is_binded;
	};

	//------------------------------ Shaders ---------------------------------------

	class CShader : public Shader
	{
	public:
		SAFE_OBJECT_DELETION

		CShader(GLenum type, GLDevice *device_)
		{
			device = device_;
			gl_shader = glCreateShader(type);
		}
		
		~CShader()
		{
			glDeleteShader(gl_shader);
		}
		
		void setSource(const char *str)
		{
			glShaderSource(gl_shader, 1, &str, NULL);
		}
		
		bool compile()
		{
			GLint status;
			glCompileShader(gl_shader);
			glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &status);

			GLint len;
			glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &len);
			if (len) {
				char *buf = new char[len+1];
				glGetShaderInfoLog(gl_shader, len+1, NULL, buf);
				printf("%s\n", buf);
			}
			return status;
		}

		GLDevice *device;
		GLuint gl_shader;
	};

	GLenum AttrTypes[] =
	{
		GL_FLOAT,
		GL_DOUBLE,
	};

	class CAttribute : public Attribute
	{
	public:
		bool setVertexBuffer(Buffer *buf, const Layout *l)
		{
			layout = *l;
			buffer = debug_cast<CBuffer *> (buf);
			return true;
		}

		void BindBuffer()
		{
			buffer->bind();
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, layout.ncomponents, AttrTypes[layout.type], 
				GL_FALSE, layout.stride, (char *)NULL + layout.offset);
		}

		void unbindBuffer()
		{
			glDisableVertexAttribArray(location);
		}

		GLint location;
		Layout layout;
		RefCntHolder<CBuffer> buffer;
		using Attribute::name;
	};

	class CUniform : public Uniform
	{
	public:
		CUniform()
		{
			values = NULL;
		}

		~CUniform()
		{
			delete []values;
		}

		bool setFloats(const float *_values, size_t _count, bool _transpose)
		{
			if (!_count)
				_count = size;
			count = _count;
			transpose = _transpose;
			if (!values)
				values = new float[width*height*size];
			memcpy(values, _values, width*height*count*sizeof(float));
			return true;
		}

		bool setValues(int &tex_bind) {
			if (!is_sampler)
			{
				switch (width)
				{
				case 1:
					switch (height)
					{
					case 1:
						glUniform1fv(location, count, values);
						break;
					case 2:
						glUniform2fv(location, count, values);
						break;
					case 3:
						glUniform3fv(location, count, values);
						break;
					case 4:
						glUniform4fv(location, count, values);
						break;
					}
					break;
				case 2:
					switch (height)
					{
					case 2:
						glUniformMatrix2fv(location, count, transpose, values);
						break;
					case 3:
						glUniformMatrix2x3fv(location, count, transpose, values);
						break;
					case 4:
						glUniformMatrix2x4fv(location, count, transpose, values);
						break;
					}
					break;
				case 3:
					switch (height)
					{
					case 2:
						glUniformMatrix3x2fv(location, count, transpose, values);
						break;
					case 3:
						glUniformMatrix3fv(location, count, transpose, values);
						break;
					case 4:
						glUniformMatrix3x4fv(location, count, transpose, values);
						break;
					}
					break;
				case 4:
					switch (height)
					{
					case 2:
						glUniformMatrix4x2fv(location, count, transpose, values);
						break;
					case 3:
						glUniformMatrix4x3fv(location, count, transpose, values);
						break;
					case 4:
						glUniformMatrix4fv(location, count, transpose, values);
						break;
					}
					break;
				default:
					return false;
				}
			}
			else
			{
				glActiveTexture(GL_TEXTURE0 + tex_bind);
				texture->bind();
				glUniform1i(location, tex_bind++);
			}
			return true;
		}

		void unsetValues(int &tex_bind)
		{
			if (is_sampler)
			{
				glActiveTexture(GL_TEXTURE0 + tex_bind++);
				texture->unbind();
			}
		}

		bool setSamplerTexture(Texture *tex)
		{
			if (is_sampler)
			{
				texture = debug_cast<CTexture *> (tex);
				return true;
			}
			return false;
		}

		GLint location;
		RefCntHolder<CTexture> texture;
		float *values;
		size_t count;
		bool transpose;
		
		using Uniform::name;
		using Uniform::width;
		using Uniform::height;
		using Uniform::size;
		using Uniform::is_sampler;
	};

	class CShaderProgram : public ShaderProgram
	{
	public:
		SAFE_OBJECT_DELETION

		CShaderProgram(GLDevice *device_)
		{
			device = device_;
			is_linked = false;
			gl_program = glCreateProgram();
		}

		~CShaderProgram()
		{
			clear();
			glDeleteProgram(gl_program);
		}

		void attachShader(Shader *shd)
		{
			is_linked = false;
			CShader *shader = debug_cast<CShader *> (shd);
			glAttachShader(gl_program, shader->gl_shader);
		}

		void detachShader(Shader *shd)
		{
			is_linked = false;
			CShader *shader = debug_cast<CShader *> (shd);
			glDetachShader(gl_program, shader->gl_shader);
		}

		bool link()
		{
			if (is_linked)
				return true;
			GLint status;
			glLinkProgram(gl_program);
			glGetProgramiv(gl_program, GL_LINK_STATUS, &status);

			if (status == GL_TRUE)
				clear();

			GLint len;
			glGetProgramiv(gl_program, GL_INFO_LOG_LENGTH, &len);
			if (len && status == GL_FALSE)
			{
				char *buf = new char[len+1];
				glGetProgramInfoLog(gl_program, len+1, NULL, buf);
				ERROR_LOG(buf);
			}

			is_linked = status == GL_TRUE;
			if (!is_linked)
				return false;
			
			GLint nattr;
			glGetProgramiv(gl_program, GL_ACTIVE_ATTRIBUTES, &nattr);
			glGetProgramiv(gl_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
			char *buf = new char[len + 1];
			for (GLint i = 0; i < nattr; ++i)
			{
				GLint size;
				GLenum type;
				glGetActiveAttrib(gl_program, i, len+1, NULL, &size, &type, buf);
				CAttribute *attribute = new CAttribute;
				attribute->name = buf;
				attribute->location = glGetAttribLocation(gl_program, buf);
				attributes.push_back(attribute);
			}
			delete []buf;

			GLint nuni;
			glGetProgramiv(gl_program, GL_ACTIVE_UNIFORMS, &nuni);
			//GLint len;
			glGetProgramiv(gl_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
			buf = new char[len + 1];
			for (GLint i = 0; i < nuni; ++i)
			{
				GLint size;
				GLenum type;
				glGetActiveUniform(gl_program, i, len+1, NULL, &size, &type, buf);
				CUniform *uniform = new CUniform;
				uniform->name = buf;
				uniform->size = size;
				uniform->location = glGetUniformLocation(gl_program, buf);
				switch (type) {
					case GL_FLOAT:
						uniform->width = 1;
						uniform->height = 1;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_VEC2:
						uniform->width = 1;
						uniform->height = 2;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_VEC3:
						uniform->width = 1;
						uniform->height = 3;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_VEC4:
						uniform->width = 1;
						uniform->height = 4;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT2:
						uniform->width = 2;
						uniform->height = 2;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT3:
						uniform->width = 3;
						uniform->height = 3;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT4:
						uniform->width = 4;
						uniform->height = 4;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT2x3:
						uniform->width = 2;
						uniform->height = 3;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT2x4:
						uniform->width = 2;
						uniform->height = 4;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT3x2:
						uniform->width = 3;
						uniform->height = 2;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT3x4:
						uniform->width = 3;
						uniform->height = 4;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT4x2:
						uniform->width = 4;
						uniform->height = 2;
						uniform->is_sampler = false;
						break;
					case GL_FLOAT_MAT4x3:
						uniform->width = 4;
						uniform->height = 3;
						uniform->is_sampler = false;
						break;
					case GL_SAMPLER_1D:
						uniform->is_sampler = true;
						break;
					case GL_SAMPLER_2D:
						uniform->is_sampler = true;
						break;
					case GL_SAMPLER_3D:
						uniform->is_sampler = true;
						break;
					case GL_SAMPLER_CUBE:
						uniform->is_sampler = true;
						break;
				}
				uniforms.push_back(uniform);
			}
			
			return status;
		}

		bool activate() {
			for (std::vector<CAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
				(*it)->BindBuffer();
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glUseProgram(gl_program);
			int tex_bind = 0;
			for (std::vector<CUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
				(*it)->setValues(tex_bind);
			}
			return true;
		}

		void deactivate() {
			for (std::vector<CAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
				(*it)->unbindBuffer();
			}
			int tex_bind = 0;
			for (std::vector<CUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
				(*it)->unsetValues(tex_bind);
			}
			glUseProgram(0);
		}

		size_t getUniformsNumber() {
			return uniforms.size();
		}

		Uniform *getUniform(size_t i) {
			return uniforms[i];
		}

		size_t getAttributesNumber() {
			return attributes.size();
		}

		Attribute *getAttribute(size_t i)
		{
			return attributes[i];
		}

		void clear() {
			for (std::vector<CUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
				delete *it;
			}
			uniforms.clear();

			for (std::vector<CAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
				delete *it;
			}
			attributes.clear();
		}

		GLDevice *device;
		GLuint gl_program;
		std::vector<CUniform *> uniforms;
		std::vector<CAttribute *> attributes;
		bool is_linked;
	};

	class CShaderServer : public ShaderServer
	{
	public:
		CShaderServer(GLDevice *device_)
		{
			device = device_;
		}

		Shader *createVertexShader()
		{
			return new CShader(GL_VERTEX_SHADER, device);
		}

		Shader *createGeometryShader()
		{
			return new CShader(GL_GEOMETRY_SHADER, device);
		}

		Shader *createFragmentShader()
		{
			return new CShader(GL_FRAGMENT_SHADER, device);
		}

		ShaderProgram *createShaderProgram()
		{
			return new CShaderProgram(device);
		}

		GLDevice *device;
	};

	//------------------------------ Render Target --------------------------------

	static bool isGLInitialized = false;

	class CRenderTarget;
	CRenderTarget *currentRenderTarget;

	class CRenderTarget : public RenderTarget
	{
	public:
		SAFE_OBJECT_DELETION

		CRenderTarget(GLDevice *device_)
		{
			device = device_;
			isClearColor = isClearDepth = true;
			viewport_changed = false;
		}
		
		bool initialize(ws::Window *wnd_)
		{
			wnd = wnd_;
			return true;
		}

		void reshape()
		{
			viewport_changed = true;
		}

		void beginFrame()
		{
			currentRenderTarget = this;
			wnd->startRendering();
			glDisable(GL_SCISSOR_TEST);
			
			if (viewport_changed)
			{
				viewport_changed = false;
				const ws::WindowInfo *info = wnd->getWindowInfo();
				glViewport (0, 0, (GLsizei)(info->width), (GLsizei)(info->height));
			}
			
			if (isClearColor)
			{
				glClearColor(cl_r, cl_g, cl_b, cl_a);
				if (isClearDepth)
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				else glClear(GL_COLOR_BUFFER_BIT);
				return;
			}
			
			if (isClearDepth)
			{
				glClear(GL_DEPTH_BUFFER_BIT);
			}
		}
		void endFrame()
		{
			wnd->finishRendering();
		}

		bool getSize(int &width, int &height)
		{
			if (wnd)
			{
				const ws::WindowInfo *info = wnd->getWindowInfo();
				width = info->width;
				height = info->height;
				return true;
			}
			return false;
		}

// 		void makeScreenShot(CImageLoader *loader, TCHAR *fileName) {
	// 		Assert(loader, TEXT("loader is NULL"));
	// 		// Выбираем буффер экрана
	// 		glReadBuffer(GL_FRONT);
	// 		const SWindowInfo *winfo = wnd->getWindowInfo();
	// 		size_t imageSize = winfo->width * 3;
	// 		imageSize = (imageSize + 3) & ~3;
	// 		imageSize *= winfo->height;
	// 		char *data = new char[imageSize];
	// 		// Читаем в неё весь экран
	// 		glReadPixels(0, 0, winfo->width, winfo->height, GL_RGB,GL_UNSIGNED_BYTE, data);
	// 		Image image;
	// 		image.width = winfo->width;
	// 		image.height = winfo->height;
	// 		image.format = Image::IF_RGB888;
	// 		image.data = data;
	// 		loader->SaveToFile(fileName, &image, true);
	// 		delete []data;
// 		}

		GLDevice *device;
		ws::PWindow wnd;
		bool viewport_changed;
	};

	//------------------------------ RenderState ----------------------------------

	class CRenderState : public RenderState
	{
	public:
		bool setSource(const char *code)
		{
			stateFunctions.clear();
			std::stringstream stream(code);
			int lineN = 0;
			for (std::string line; std::getline(stream, line); ++lineN)
			{
				boost::tokenizer<> tok(line);
				boost::tokenizer<>::iterator it = tok.begin();
				if (it != tok.end())
				{
					if (*it == "DepthTest")
					{
						if (++it == tok.end())
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						
						if (*it == "enable")
						{
							stateFunctions.push_back(boost::bind<void>(glEnable, GL_DEPTH_TEST));
						}
						else if (*it == "disable")
						{
							stateFunctions.push_back(boost::bind<void>(glDisable, GL_DEPTH_TEST));
						}
						else
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						continue;
					}
					else if (*it == "ScissorTest")
					{
						if (++it == tok.end())
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						if (*it == "enable")
						{
							stateFunctions.push_back(boost::bind<void>(glEnable, GL_SCISSOR_TEST));
						}
						else if (*it == "disable")
						{
							stateFunctions.push_back(boost::bind<void>(glDisable, GL_SCISSOR_TEST));
						}
						else
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						continue;
					}
					else if (*it == "Wireframe")
					{
						if (++it == tok.end())
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						if (*it == "enable")
						{
							stateFunctions.push_back(boost::bind<void>(glPolygonMode, GL_FRONT_AND_BACK, GL_LINE));
						}
						else if (*it == "disable")
						{
							stateFunctions.push_back(boost::bind<void>(glPolygonMode, GL_FRONT_AND_BACK, GL_FILL));
						}
						else
						{
							ERROR_LOG("RenderState syntax error " << lineN << ": " << line);
							return false;
						}
						continue;
					}
				}
				return true;
			}
		}
		
		void apply()
		{
			for (std::vector<stateFunc>::iterator it = stateFunctions.begin(); it != stateFunctions.end(); ++it)
				(*it)();
		}

		typedef boost::function< void () > stateFunc;
		std::vector<stateFunc> stateFunctions;
	};

}

namespace gb
{
	namespace graphics
	{
		//------------------------------ Device ---------------------------------------

		RenderTarget *GLDevice::createWindowRenderTarget(ws::Window *wnd)
		{
			CRenderTarget *rt = new CRenderTarget(this);
			if (rt->initialize(wnd))
				return rt;
			
			delete rt;
			return NULL;
		}

		bool GLDevice::getSize(int &width, int &height)
		{
			if (currentRenderTarget)
				return currentRenderTarget->getSize(width, height);
			
			return false;
		}

		void GLDevice::setScissorRect(const Rectangle &rc)
		{
			int w, h;
			getSize(w, h);
			glScissor(rc.left, h - rc.top - rc.height, rc.width, rc.height);
		}

		ShaderServer *GLDevice::createShaderServer()
		{
			return new CShaderServer(this);
		}

		Texture *GLDevice::createTexture(Texture::Type type)
		{
			return new CTexture(type, this);
		}

		Buffer *GLDevice::createIndexBuffer()
		{
			return new CBuffer(GL_ELEMENT_ARRAY_BUFFER, this);
		}

		Buffer *GLDevice::createVertexBuffer()
		{
			return new CBuffer(GL_ARRAY_BUFFER, this);
		}

		RenderState *GLDevice::createRenderState()
		{
			return new CRenderState;
		}

		static GLenum PrimitiveTypes[] =
		{
			GL_POINTS,
			GL_LINE_STRIP,
			GL_LINE_LOOP,
			GL_LINES,
			GL_TRIANGLE_STRIP,
			GL_TRIANGLE_FAN,
			GL_TRIANGLES,
		};

		void GLDevice::draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType ptype, Buffer *indexBuffer, int base)
		{
			CShaderProgram *program = debug_cast<CShaderProgram *>(prg);
			if (activated_program && activated_program != prg)
			{
				debug_cast<CShaderProgram *>((ShaderProgram *&) activated_program)->deactivate();
			}
			program->activate();
			activated_program = program;

			if (indexBuffer)
			{
				CBuffer *ind_buf = debug_cast<CBuffer *> (indexBuffer);
				ind_buf->bind();
				GLenum type;
				switch (ind_buf->getElementSize())
				{
					case 1:
						type = GL_UNSIGNED_BYTE;
						break;
					case 2:
						type = GL_UNSIGNED_SHORT;
						break;
					case 4:
						type = GL_UNSIGNED_INT;
						break;
				}
				char *ptr = NULL;
				ptr += ind_buf->getElementSize() * first;
				if (!count)
					count = indexBuffer->getElementsNumber();
				if (!base)
					glDrawElements(PrimitiveTypes[ptype], count, type, ptr);
				else glDrawElementsBaseVertex(PrimitiveTypes[ptype], count, type, ptr, base);
				ind_buf->unbind();
			}
			else
			{
				glDrawArrays(PrimitiveTypes[ptype], first, count);
			}
			GLenum er = glGetError();
			//program->Deactivate();
		}

		void GLDevice::deleteUnusedObjects()
		{
			boost::lock_guard<boost::mutex> guard(for_deletion_guard);
			for (size_t i = 0; i < for_deletion.size(); ++i)
			{
				delete for_deletion[i];
			}
			for_deletion.clear();
		}

		void GLDevice::forDeletion_(IRefCountable *res)
		{
			boost::lock_guard<boost::mutex> guard(for_deletion_guard);
			for_deletion.push_back(res);
		}
	
		
	}
}