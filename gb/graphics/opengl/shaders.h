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
 * ����� ��������� ���������.
 * ���������� ���������� ������� � ��������� ����� ��������������.
 *
 * ���� ����������� �������������� ����� MessageBox � Windows. ����� ��������
 * ��������� ��. ������� printInfoLog � ����� ����������.
 */
class ShaderProgram {
public:

    ShaderProgram ();

    /**
     * ����������
     * ��������� ��������� � ����������� ��� ������� �� �������
     * ������� �����������, �� �� ���������. �������� �������� ���������� �
     * �� ����������� �������������.
     */
    ~ShaderProgram ();

    /**
     * �������� ��������� ���� ����������� ������� ��� ������ � ���������
     * @return <code>true</code> ���� ��� ������� ��������������
     * ��� <code>false</code>, ���� ���
     */
    static bool GLSLcheck ();

    /**
     * ������������� ������� � ���������. ��� ������� ����� ���� �����,
     * �������������� �� ShaderBase (���� ��� VertexShader � FragmentShader).
     */
    void attachShader (ShaderBase const & shader);

    /**
     * ���������� ���� ������������� �������� � ���� ����������� ������,
     * ������� ����� ������������ � ��������� OpenGL
     * @param log
     *      ���� true, �� ����� �������� ���������� �� ����
     *      ��������� ���������
     */
    void link (bool log = false);

    /**
     * ��������� ������������ ������� � ������� ������������ ����.
     * @param log
     *      ���� true, �� ����� �������� ���������� �� ����
     *      ��������� ���������
     */
    void validate (bool log = false);

    /**
     * ��������� �������� uniform-���������� ���� int � ��������� ���������
     * @param uname ��� ���������� � ���������
     * @param value ����� �������� ����������
     */
    void setUniform1i (const char *uname, int value);

    /**
     * ��������� �������� uniform-���������� ���� float � ��������� ���������
     * @param uname ��� ���������� � ���������
     * @param value ����� �������� ����������
     */
    void setUniform1f (const char *uname, float value);

    /**
     * ��������� ��������� � ����������� ��������
     */
    void on();

    /**
     * ���������� ����� ��������� ��������� �� ��������� OpenGL
     */
    static void off();

private:

    GLuint sh_program_object;

    GLuint shaders[10];

    int sh_num;

    bool logs;
};

/**
 * ������� ����� ��� ��������� ��������
 *
 * ������ ������������� ��� �������� � ���������� ���������� �� ���������,
 * ����� ���� ����������� � ���������� ����������. ��� ������� ����� ����
 * ������� �� ������� � ����� ������, ���� ������ ������ ��� �� �����.
 *
 * �������� ������������ OpenGL (http://www.opengl.org/sdk/docs/man/xhtml/glDeleteShader.xml)
 * ������� ����� ���� ������� ����� ����������� � ��������� � ��� �� ��������
 * �� � �����������������, ������� �� �����������, ����� ������� ��������
 * ������������ ������ �������� ����� ������������� �������.
 */
class ShaderBase {

protected:

    char * source;
    GLuint sh_object;

    ShaderBase (const char *filename);

public:

    virtual ~ShaderBase ();

    /**
     * ��������� ���� �������.
     */
    const char * getSource () const;

    /**
     * ��������� ����������� ������ ������� � OpenGL
     */
    GLuint getHandle () const;
};

/**
 * ����� ���������� �������
 */
class VertexShader : public ShaderBase {
public:
    /**
     * �����������
     * @param filename ���� � ����� � �������� ����� �������
     * @param log ���� �� �������� ��� ����������
     */
    VertexShader (const char *filename, bool log = false);
};


/**
 * ����� ������������ �������
 */
class FragmentShader : public ShaderBase {
public:
    /**
     * �����������
     * @param filename ���� � ����� � �������� ����� �������
     * @param log ���� �� �������� ��� ����������
     */
    FragmentShader (const char *filename, bool log = false);
};

}}} // namespaces

#endif // SHADERS_H_INCLUDED
