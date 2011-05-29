/*=============================================*\
 * file:      gb/graphics/opengl/shaders.h     *
 * author:    Sharov "Zefick" Sergey           *
 * version:   2.0                              *
 * date:      28.05.2011                       *
\*=============================================*/

#ifndef OPENGL_SHADERS_H
#define OPENGL_SHADERS_H

//#include <gl/gl.h>
#include <gl/glee.h>

namespace gb {
namespace graphics {
namespace opengl {

class ShaderBase;

/**
 * Класс шейдерной программы.
 * Необходимо подключать шейдеры и линковать перед использованием.
 *
 * Пока логирование осуществляется через MessageBox в Windows. Чтобы изменить
 * поведение см. функцию printInfoLog в файле реализации.
 */
class ShaderProgram {
public:

    ShaderProgram ();

    /**
     * Деструктор
     * Отключает программу и освобождает все занятые ею объекты
     * Шейдеры отключаются, но не удаляются. Удаление шейдеров происходит в
     * их собственных конструкторах.
     */
    ~ShaderProgram ();

    /**
     * Проверка поддержки всех необходимых функций для работы с шейдерами
     * @return <code>true</code> если все функции поддерживаются
     * или <code>false</code>, если нет
     */
    static bool GLSLcheck ();

    /**
     * Присоединение шейдера к программе. Тип шейдера может быть любой,
     * унаследованный от ShaderBase (пока это VertexShader и FragmentShader).
     */
    void attachShader (ShaderBase const & shader);

    /**
     * Компановка всех присоединённых шейдеров в один программный объект,
     * который можно использовать в конвейере OpenGL
     * @param log
     *      если true, то будет выведена информация из лога
     *      шейдерной программы
     */
    void link (bool log = false);

    /**
     * Валидация программного объекта с выводом возможностью лога.
     * @param log
     *      если true, то будет выведена информация из лога
     *      шейдерной программы
     */
    void validate (bool log = false);

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
     * Исключение любой шейдерной программы из конвейера OpenGL
     */
    static void off();

private:

    GLuint sh_program_object;

    GLuint shaders[10];

    int sh_num;

    bool logs;
};

/**
 * Базовый класс для шейдерных программ
 *
 * Шейдер компилируется при создании и существует независимо от программы,
 * может быть присоединен к нескольким программам. Код шейдера может быть
 * получен из объекта в любой момент, если только объект ещё не удалён.
 *
 * Согласно документации OpenGL (http://www.opengl.org/sdk/docs/man/xhtml/glDeleteShader.xml)
 * шейдеры могут быть удалены после подключения к программе и это не повлияет
 * на её работоспособность, поэтому не обязательно, чтобы объекты шейдеров
 * существовали дольше рабочего цикла программмного объекта.
 */
class ShaderBase {

protected:

    char * source;
    GLuint sh_object;

    ShaderBase (const char *filename);

public:

    virtual ~ShaderBase ();

    /**
     * Получение кода шейдера.
     */
    const char * getSource () const;

    /**
     * Получение внутреннего номера шейдера в OpenGL
     */
    GLuint getHandle () const;
};

/**
 * Класс вершинного шейдера
 */
class VertexShader : public ShaderBase {
public:
    /**
     * Конструктор
     * @param filename путь к файлу с исходным кодом шейдера
     * @param log надо ли выводить лог компиляции
     */
    VertexShader (const char *filename, bool log = false);
};


/**
 * Класс фрагментного шейдера
 */
class FragmentShader : public ShaderBase {
public:
    /**
     * Конструктор
     * @param filename путь к файлу с исходным кодом шейдера
     * @param log надо ли выводить лог компиляции
     */
    FragmentShader (const char *filename, bool log = false);
};

}}} // namespaces

#endif // SHADERS_H_INCLUDED
