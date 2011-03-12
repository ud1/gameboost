#pragma once

#include <gb/base/IRefCountable.h>
#include <gb/window_subsystem/Window.h>
#include <gb/base/Rectangle.h>
#include "Texture.h"

namespace gb
{
	namespace graphics
	{
		class Shader : public base::IRefCountable
		{
		public:
			virtual void setSource(const char *str) = 0;
			virtual bool compile() = 0;
		};
		
		typedef base::RefCntHolder<Shader> PShader;

		struct Layout
		{
			enum Type
			{
				FLOAT,
				DOUBLE, 
			};

			Type type;
			size_t ncomponents;
			size_t stride;
			size_t offset;
		};

		class Buffer : public base::IRefCountable
		{
		public:
			void setElementSize(size_t bytes)
			{
				element_size = bytes;
				is_created = false;
			}

			void setElementsNumber(size_t num)
			{
				nelements = num;
				is_created = false;
			}

			size_t getElementSize() const {return element_size;}
			size_t getElementsNumber() const {return nelements;}
			
			virtual void* map(size_t offset_bytes, size_t size_in_bytes) = 0;
			virtual void unmap() = 0;
			virtual void subData(size_t offset_bytes, size_t size_in_bytes, void *data) = 0;
			
		protected:
			bool is_created;
			size_t nelements, element_size;
		};
		
		typedef base::RefCntHolder<Buffer> PBuffer;

		class Attribute
		{
		public:
			const char *getName() const {return name.c_str();}
			
			virtual bool setVertexBuffer(Buffer *buf, const Layout *l) = 0;
			
		protected:
			std::string name;
		};

		/**
		 * Uniform может представлять либо массив из size матриц размером width*height каждая,
		 * либо семплер. Если uniform переменная не является массивом, то size = 1.
		 * В случае если Uniform представляет только одно число, то
		 * width = height = 1.
		 */
		class Uniform
		{
		public:
			bool setFloat(float v) {return setFloats(&v, 1, false);}

			virtual bool setFloats(const float *values, size_t count, bool transpose) = 0;
			virtual bool setSamplerTexture(Texture *tex) = 0;
			
			size_t getWidth() {return width;}
			size_t getHeight() {return height;}
			size_t getSize() {return size;}
			bool isSampler() {return is_sampler;}
			const char *getName() {return name.c_str();}
		
		protected:
			size_t width, height, size;
			bool is_sampler;
			std::string name;
		};

		class ShaderProgram : public base::IRefCountable
		{
		public:
			virtual void attachShader(Shader *shd) = 0;
			virtual void detachShader(Shader *shd) = 0;
			virtual bool link() = 0;
			virtual size_t getUniformsNumber() = 0;
			virtual Uniform *getUniform(size_t i) = 0;
			virtual size_t getAttributesNumber() = 0;
			virtual Attribute *getAttribute(size_t i) = 0;
		};
		
		typedef base::RefCntHolder<ShaderProgram> PShaderProgram;

		class ShaderServer : public base::IRefCountable
		{
		public:
			virtual Shader *createVertexShader() = 0;
			virtual Shader *createGeometryShader() = 0;
			virtual Shader *createFragmentShader() = 0;

			virtual ShaderProgram *createShaderProgram() = 0;
		};
		
		typedef base::RefCntHolder<ShaderServer> PShaderServer;

		class RenderTarget : public base::IRefCountable
		{
		public:
			void setClearColor(float r, float g, float b, float a)
			{
				cl_r = r;
				cl_g = g;
				cl_b = b;
				cl_a = a;
			}

			void clearColor(bool b) {isClearColor = b;}
			void clearDepth(bool b) {isClearDepth = b;}
		
			virtual void reshape() = 0;
			virtual void beginFrame() = 0;
			virtual void endFrame() = 0;

			virtual bool getSize(int &width, int &height) = 0;
			//virtual void makeScreenShot(ImageLoader *loader, TCHAR *fileName) = 0;
			
		protected:
			float cl_r, cl_g, cl_b, cl_a;
			bool isClearColor, isClearDepth;
		};
		
		typedef base::RefCntHolder<RenderTarget> PRenderTarget;

		class RenderState
		{
		public:
			virtual bool setSource(const char *code) = 0;
			virtual void apply() = 0;
		};
		
		class Device : public base::IRefCountable
		{
		public:
			enum PrimitiveType
			{
				POINTS,
				LINE_STRIP,
				LINE_LOOP,
				LINES,
				TRI_STRIP,
				TRI_FAN,
				TRIANGLES,
				PRIMITIVE_TYPES_COUNT
			};
			
			virtual RenderTarget *createWindowRenderTarget(window_subsystem::Window *wnd) = 0;
			virtual bool getSize(int &width, int &height) = 0;
			virtual void setScissorRect(const base::Rectangle &rc) = 0;

			virtual Texture *createTexture(Texture::Type type) = 0;
			virtual Buffer *createIndexBuffer() = 0;
			virtual Buffer *createVertexBuffer() = 0;
			virtual RenderState *createRenderState() = 0;
			virtual void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0) = 0;

			virtual ShaderServer *createShaderServer() = 0;

			virtual void deleteUnusedObjects() = 0;
		};
		
		Device *createDevice(const char *graphics_library);
		
		typedef base::RefCntHolder<Device> PDevice;
	}
}