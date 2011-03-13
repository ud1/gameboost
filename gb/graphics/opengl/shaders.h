/*=============================================*\
 * file:      gb/graphics/opengl/shaders.h     *
 * author:    Sharov "Zefick" Sergey           *
 * date:      13.03.2011                       *
\*=============================================*/

#ifndef OPENGL_SHADERS_H
#define OPENGL_SHADERS_H

#include <gl/gl.h>
//#include <gl/glee.h>

namespace gb {
namespace graphics {
namespace opengl {

/**
 * Класс шейдерной программы.
 * Поддерживает возможность подключение вершинного и фрагментного шейдеров.
 */
class ShaderProgram {
public:

	/**
	 * Конструктор
	 * @paran vs путь к файлу с кодом вершинного шейдера
	 * @param fs путь к файлу с кодом фрагментного шейдера
	 * @param slog устанавливает будет ли выводиться лог шейдера
	 */
    ShaderProgram (const char *vs, const char *fs, bool slog);
	
	/**
	 * Деструктор
	 * Отключает программу и освобождает все занятые ею объекты
	 */
    ~ShaderProgram ();

	/**
	 * Проверка поддержки всех необходимых функций для работы с шейдерами
	 * @return <code>true</code> если все функции поддерживаются
	 * или <code>false</code>, если нет
	 */
    static bool GLSLcheck ();

	/**
	 * Подключение вершинного шейдера к программе
	 * @param filename путь к файлу с кодом вершинного шейдера
	 */
    void loadVertShader (const char * filename);
		
	/**
	 * Подключение фрагментного шейдера к программе
	 * @param filename путь к файлу с кодом фрагментного шейдера
	 */
    void loadFragShader (const char * filename);
    
	/**
	 * Установка значения uniform-переменной типа int в шейдерной программе
	 * @param uname имя переменной в программе
	 * @param value новое значение переменной
	 */
    void setUniform1i (const char *uname, int value);
	
	/**
	 * Установка значения uniform-переменной типа float в шейдерной программе
	 * @param uname имя переменной в программе
	 * @param value новое значение переменной
	 */
    void setUniform1f (const char *uname, float value);

	/**
	 * Включение программы в графический конвейер
	 */
    void on();
	
	/**
	 * Отключение шейдерной программы
	 */
    static void off();

private:

	/**
	 * Загрузка кода шейдера из файла
	 * @param filename путь к файлу с кодом шейдера
	 * @return C-строка с кодом шейдера
	 */
    char * LoadFromFile (const char *filename);
	
	/**
	 * Вывод на экран сообщения из лога компиляции шейдера
	 * @param obj объект, для которого надо вывести лог
	 * @param title заголовок окна сообщения
	 */
    void printInfoLog (GLhandleARB obj, const char *title);

    GLhandleARB
        sh_program_object,   // Объект программы
        vsh_object,          // Объект вершинного шейдера
        fsh_object;          // Объект фрагментного шейдера

    bool logs;               // Надо ли выводить логи на экран
};

}}} // namespaces

#endif // SHADERS_H_INCLUDED
