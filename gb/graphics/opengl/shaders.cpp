/*=============================================*\
 * file:      gb/graphics/opengl/shaders.cpp   *
 * author:    Sharov "Zefick" Sergey           *
 * date:      13.03.2011                       *
\*=============================================*/

#include "shaders.h"

#include <io.h>
#include <сstdio>
#include <сstdlib>

namespace gb {
namespace graphics {
namespace opengl {


ShaderProgram::ShaderProgram(const char *vs, const char *fs, bool L) {
    logs = L;
    sh_program_object = glCreateProgramObjectARB();

    if (vs) loadVertShader(vs);
    if (fs) loadFragShader(fs);

    glLinkProgramARB(sh_program_object);
    //glValidateProgramARB(sh_program_object);

    GLint status;
    glGetProgramiv(sh_program_object, GL_LINK_STATUS, &status);
    if (logs && status != GL_TRUE)
        printInfoLog(sh_program_object, "Shader Program");
}


ShaderProgram::~ShaderProgram() {
    glUseProgramObjectARB(0);
    glDetachObjectARB(sh_program_object, vsh_object);
    glDetachObjectARB(sh_program_object, fsh_object);
    glDeleteObjectARB(vsh_object);
    glDeleteObjectARB(fsh_object);
}


void ShaderProgram::on() {
    glUseProgramObjectARB(sh_program_object);
}


void ShaderProgram::off() {
    glUseProgramObjectARB(0);
}


// Подключение вершинного шейдера
void ShaderProgram::loadVertShader(const char * filename) {
    if (access(filename, 0)) return;
    const char * sh_code = LoadFromFile(filename);

    GLhandleARB sh_object = glCreateShaderObjectARB(GL_VERTEX_SHADER);
    glShaderSourceARB(sh_object, 1, &sh_code, NULL);
    glCompileShaderARB(sh_object);

    GLint status;
    glGetShaderiv(sh_object, GL_COMPILE_STATUS, &status);
    if (logs && status != GL_TRUE)
        printInfoLog(sh_object, "Vertex shader");

    glAttachObjectARB(sh_program_object, sh_object);

    vsh_object = sh_object;
    delete[] sh_code;
}


// Подключение фрагментного шейдера
void ShaderProgram::loadFragShader(const char * filename) {
    if (access(filename, 0)) return;
    const char * sh_code = LoadFromFile(filename);

    GLhandleARB sh_object = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
    glShaderSourceARB(sh_object, 1, &sh_code, NULL);
    glCompileShaderARB(sh_object);


    GLint status;
    glGetShaderiv(sh_object, GL_COMPILE_STATUS, &status);
    if (logs && status != GL_TRUE)
        printInfoLog(sh_object, "Fragment shader");

    glAttachObjectARB(sh_program_object, sh_object);

    fsh_object = sh_object;
    delete[] sh_code;
}


// Проверка поддержки шейдеров
bool ShaderProgram::GLSLcheck() {
    char *szGLExtensions = (char*) glGetString(GL_EXTENSIONS);
    if (!strstr(szGLExtensions, "GL_ARB_shader_objects ")) {
        MessageBoxA(0, "Расширение для работы с шейдерами не поддерживается!", "Error", MB_OK);
        return false;
    }
    if (!glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB
            || !glCreateShaderObjectARB || !glCompileShaderARB
            || !glAttachObjectARB || !glLinkProgramARB || !glDetachObjectARB) {
        MessageBoxA(0, "Одна или более функций для работы с шейдерами не поддерживается",
                "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }
    return true;
}


void ShaderProgram::setUniform1i (const char *uname, int v) {
    GLint p = glGetUniformLocationARB(sh_program_object, uname);
    glUniform1iARB(p, v);
}


void ShaderProgram::setUniform1f (const char *uname, float v) {
    GLint p = glGetUniformLocationARB(sh_program_object, uname);
    glUniform1fARB(p, v);
}

// PRIVATE
//###################################################################


// Вывод лога компиляции
void ShaderProgram::printInfoLog(GLhandleARB obj, const char *title) {
    int len = 0, chWritten = 0;
    char *infoLog;
    glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &len);

    if (len > 1) {
        infoLog = new char [len+1];
        glGetInfoLogARB(obj, len, &chWritten, infoLog);
        MessageBoxA(NULL, infoLog, title, 0);
        delete[] infoLog;
    }
    else MessageBoxA(NULL, "all right", title, 0);
}


// Загрузка кода шейдера из файла
char * ShaderProgram::LoadFromFile(const char *fn) {
    FILE *file;
    char *content = NULL;
    int count = 0;

    if (!fn || !(file = fopen(fn, "rt")))
        return NULL;

    fseek(file, 0, SEEK_END);
    count = ftell(file);
    rewind(file);
    if (count > 0) {
        content = new char[count+1];
        count = fread(content, 1, count, file);
        content[count] = '\0';
    }
    fclose(file);
    return content;
}

}}} // namespaces
