/**
 * @defgroup graphics_group gb::graphics
 * Компоненты связанные с графикой
 * 
 * Интерфейс к графической библиотеке
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
 * 
 * Общая структура такова. Создаем оконный менеджер:
 * @code
 * window_manager = base::CreateRFHolder(window_subsystem::createWindowManager("OpenGL"));
 * window_manager->init(std::vector<std::string>());
 * @endcode
 * Так как процедура создания окна в операционных системах почему-то сильно завязано на библиотеке, инициализаций gl занимается именно оконный менеджер а не device, а GLDevice вообще об операционной системе ничего не знает, он кроссплатформенный. 
 * Оконный менеджер сейчас реализован только под линуксом.
 * 
 * Создаем окно:
 * @code
 * main_window = base::CreateRFHolder(window_manager->createWindow(wnd_opts, nullptr));
 * @endcode
 * 
 * Присоединаяем к нему обработчик ввода
 * @code
 * main_window->attachInputHandler(input);
 * @endcode
 * input должен реализовывать интерфейс window_subsystem::Input, и ему будут слаться сообщения о нажатиях клавиш и движениях мыши.
 * 
 * Создаем device
 * @code
 * device = base::CreateRFHolder(graphics::createDevice("OpenGL"));
 * @endcode
 * 
 * Присоединяем окно устройству
 * @code
 * main_window_rt = base::CreateRFHolder(device->createWindowRenderTarget(main_window));
 * @endcode
 * 
 * И основной цикл:
 * @code
 * while(1)
 * {
 * 	window_manager->processMessages(); // Обработка ввода, тут будет функции из input вызываться
 * 	main_window_rt->beginFrame(); // Здесь может glClear вызываться
 * 	render(); // Рендерим что хотим
 * 	main_window_rt->endFrame(); // здесь SwapBuffers() происходит
 * }
 * @endcode
 * 
 * Для того, чтобы что-то нарисовать нужно: 
 * Создать вершинный буффер:
 * @code
 * vertex_buffer = base::CreateRFHolder(device->createVertexBuffer());
 * @endcode
 * 
 * Заполнить его какими-то данными (координатами, вершинными координатами)
 * @code
 * struct Vert
 * {
 * 	vec3 pos;
 * 	vec2 tex_coord;
 * };
 * Vert *verts = ...;
 * vertex_buffer->setElementSize(sizeof(Vert));
 * vertex_buffer->setElementsNumber(count);
 * vertex_buffer->subData(0, 0, (void *) verts);
 * @endcode
 * 
 * Создать шейдерную программу:
 * @code
 * shader_program_2d = CreateRFHolder(device->createShaderProgram());
 * @endcode
 * 
 * Создать вершиный и фрагментный шейдеры, загрузить листинги из файла, скомпилировать
 * @code
 * std::string frag_source, vert_source;
 * readEntireFile(*file_system, "../data/shaders/simple.frag", frag_source);
 * readEntireFile(*file_system, "../data/shaders/simple.vert", vert_source);
 * PShader frag_shd = CreateRFHolder(device->createFragmentShader());
 * frag_shd->setSource(frag_source.c_str());
 * frag_shd->compile();
 * PShader vert_shd = CreateRFHolder(device->createVertexShader());
 * vert_shd->setSource(vert_source.c_str());
 * vert_shd->compile();
 * @endcode
 * 
 * Если хочется, то можно листинги шейдеров хранить в нескольких файлах, делать инклуды, и прочие директивы препроцессора, но тогда надо будет воспользоваться ShaderPreprocessor для загрузки, он фактически является просто С-препроцессором, работает через виртуальную файловую систему gb.
 * 
 * Слинковать программу:
 * @code
 * shader_program_2d->attachShader(frag_shd);
 * shader_program_2d->attachShader(vert_shd);
 * shader_program_2d->link();
 * @endcode
 * 
 * После линковки можно получить список аттрибутов, и даже тут же можно забиндить к ним созданные вершинные буферы:
 * @code
 * size_t n = prg.getAttributesNumber();
 * for (size_t i = 0; i < n; ++i)
 * {
 *	Attribute *attr = prg.getAttribute(i);
 *	if (std::string("position") == attr->getName())
 * 	{
 * 		Layout layout;
 * 		layout.ncomponents = 3;
 * 		layout.offset = 0;
 * 		layout.stride = sizeof(Vert);
 * 		layout.type = Layout::FLOAT;
 * 		attr->setVertexBuffer(vertex_buffer, &layout);
 * 	}
 * 	else if (std::string("tex_coord") == attr->getName())
 * 	{
 * 		Layout layout;
 * 		layout.ncomponents = 2;
 * 		layout.offset = reinterpret_cast<size_t>(&((Vert *) NULL)->tex_coord);
 * 		layout.stride = sizeof(Vert);
 * 		layout.type = Layout::FLOAT;
 * 		attr->setVertexBuffer(vertex_buffer, &layout);
 * 	}
 * }
 * @endcode
 * В структуре Layout описывается то, как данные лежат в буфере, какого они типа, какой размер, какое смещение от начала буффера, через какой интервал они расположены.
 * 
 * Так же можно получить список юниформов и запомнить их, наверняка надо будет переж каждой отрисовкой менять их значения, скажем задавать всякие матрицы, менять цвета, чтобы постоянно не брать их по имени, делаем это только один раз, и сохраняем в переменных
 * @code
 * n = prg.getUniformsNumber();
 * for (size_t i = 0; i < n; ++i)
 * {
 * 	Uniform *uniform = prg.getUniform(i);
 * 	if (std::string("mvp") == uniform->getName())
 * 	{
 * 		mvp_uniform = uniform;
 * 	}
 * 	else if (std::string("tex") == uniform->getName())
 * 	{
 * 		tex_uniform = uniform;
 * 	}
 * }
 * @endcode
 * 
 * Еще загрузим текстурку
 * @code
 * InputStream *file = fs->getInputStream(filename);
 * AutoImage im;
 * im.load(image_loader, *file);
 * file->release();
 * PTexture texture = base::CreateRFHolder<Texture>(device->createTexture(Texture::Texture2D));
 * texture->setImage(&(const Image &)im, 0);
 * @endcode
 * 
 * И присоединим ее к юниформу
 * @code
 * tex_uniform->setSamplerTexture(textures[i]);
 * @endcode
 * 
 * Ну все, можно рисовать
 * @code
 * render()
 * {
 * 	mat4 mvp = ...;
 * 	mvp_uniform->setFloats((const float *) &mvp, 1, false);
 * 	device->draw((ShaderProgram *) prg, 6, 0, Device::TRIANGLES, nullptr);
 * }
 * @endcode
 * 
 * У шейдерной программы есть аттрибуты и юниформы, к ним мы уже подцепили вершинные буферы и текстуры, заполнили константы, при отрисовке они все автоматически прибиндятся. 
 * Последний параметр это индексный буфер, сейчас там передан nullptr.
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

		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс к графической библиотеки такой как gl или dx или softwar.
		 * 
		 * Является тонкой прослойкой к графической библиотеке, и вообще не должна заниматься никакими сложными интеллектуальными вещами, этим должны заниматься другие классы.
		 * Должна создаваться функцией createDevice(...), сейчас реализовано только для gl. 
		 * GLDevice ориентирован ближе к gl3.0, и нигде не использует deprecated функционал, но думаю можно использовать и gl2.1
		 */
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
			
			/** Приводит окно к интерфейсу RenderTarget */
			virtual RenderTarget* createWindowRenderTarget(window_subsystem::Window *wnd) = 0;
			
			/** Размер текущего RenderTarget'а */
			virtual bool getSize(int &width, int &height) = 0;
			/** Регион для scissor теста */
			virtual void setScissorRect(const base::Rectangle &rc) = 0;

			/** Создаёт текстуру указанного типа */
			virtual Texture *createTexture(Texture::Type type) = 0;
			
			/** Создаёт индексный буфер */
			virtual Buffer *createIndexBuffer() = 0;
			
			/** Создаёт вершинныё буфер */
			virtual Buffer *createVertexBuffer() = 0;
			
			/** Возвращает объект для указания глобальных параметров отрисовки таких как включения теста глубины и т.д. */
			virtual RenderState *createRenderState() = 0;
			
			/**
			 * При вызове данной функции происходит установка всех параметров
			 * и текстур в списке юниформов, биндятся все буферы для атрибутов
			 * шейдерной программы, и вызывается непосредственно функция отрисовки
			 * графической библиотеки.
			 * \param prg шейдерная программа
			 * \param count число вершин, которое надо взять из вершинных буферов для отрисовки. Можно передавать 0, если задан индексный буфер,
			 * тогда число count будет автоматически равно размеру индексного буффера с учётом параметра first
			 * \param first смещение внутри индексного буффера, отрисовка идет начиная с этого элемента
			 * \param type тип рисуемых примитивов
			 * \param indexBuffer индексный буффер
			 * \param base смещение внутри вершинных буферов. Внимание! поддерживается только в OpenGL версии 3.2  и выше.
			 */
			virtual void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0) = 0;

			/** Создаёт вершинных шейдер */
			virtual Shader *createVertexShader() = 0;
			
			/** Создаёт геометрический шейдер */
			virtual Shader *createGeometryShader() = 0;
			
			/** Создаёт фрагментный шейдер */
			virtual Shader *createFragmentShader() = 0;
			
			/** Создайт шедерную програму, к ней можео будет потом присоединить шейдеры. */
			virtual ShaderProgram *createShaderProgram() = 0;

			/** Удаляет IRefcountable объекты, чей последний вызов release() был произведен не из Render потока */
			virtual void deleteUnusedObjects() = 0;
			
			/** Очистка ресурсов */
			virtual void clean() = 0;
		};
		
		/**
		 * @ingroup graphics_group
		 * Создает Device
		 */
		Device *createDevice(const char *graphics_library);
		
		typedef base::RefCntHolder<Device> PDevice;
	}
}
