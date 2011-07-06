/**
 * @page device Интерфейс к графической библиотеке
 * Данный модуль является интерфесом к графической библиотеке, и
 * любые вызовы графических функций должны производиться исключительно
 * с помощью него, и нигде больше в программе.
 * Для создания устройсва к графической библиотеке применяется
 * функция createDevice(), чей параметр является именем библиотеки,
 * например "OpenGL", "DirectX", "Software". На данный момент
 * этот параметр игнориуется, и создается OpenGL устройство.
 * 
 * Большинство функций можно вызывать только из Render потока,
 * IRefCountable объекты могут освобождаться из любого потока,
 * при этом если освобождение происходит из Render потока, то
 * объект уничтожается незамедлительно, в противном случае
 * он помещается во внутренюю очередь, и может быть позже
 * уничтожен функцией Device::deleteUnusedObjects().
 */


#pragma once

#include <gb/base/IRefCountable.h>
#include <gb/window_subsystem/Window.h>
#include <gb/base/Rectangle.h>

#include "Attribute.h"
#include "Buffer.h"
#include "Layout.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Uniform.h"

namespace gb
{
	namespace graphics
	{

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
			
			/** Возвращает PrimitiveType по его имени, и PRIMITIVE_TYPES_COUNT если такой тип не найден */
			static PrimitiveType getPrimTypeByName(const std::string &name);
			/** Возвращает строковое представление типа примитива */
			static const char *getPrimTypeName(PrimitiveType type);
			
			virtual Render_Target* createWindowRenderTarget(window_subsystem::Window *wnd) = 0;
			virtual bool getSize(int &width, int &height) = 0;
			virtual void setScissorRect(const base::Rectangle &rc) = 0;

			virtual Texture *createTexture(Texture::Type type) = 0;
			virtual Buffer *createIndexBuffer() = 0;
			virtual Buffer *createVertexBuffer() = 0;
			virtual RenderState *createRenderState() = 0;
			
			/**
			 * При вызове данной функции происходит установка всех параметров
			 * и текстур в списке юниформов, биндятся все буферы для атрибутов
			 * шейдерной программы, и вызывается непосредственно функция отрисовки
			 * графической библиотеки.
			 */
			virtual void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0) = 0;

			virtual Shader *createVertexShader() = 0;
			virtual Shader *createGeometryShader() = 0;
			virtual Shader *createFragmentShader() = 0;
			virtual ShaderProgram *createShaderProgram() = 0;

			virtual void deleteUnusedObjects() = 0;
			virtual void clean() = 0;
		};
		
		Device *createDevice(const char *graphics_library);
		
		typedef base::RefCntHolder<Device> PDevice;
	}
}
