/*=============================================*\
 * file:      gb/graphics/opengl/shaders.cpp   *
 * author:    Sharov "Zefick" Sergey           *
 * version    2.1                              *
 * date:      05.06.2011                       *
\*=============================================*/

#include "shaders.h"

#include <cstdio>
#include <cstdlib>

namespace gb {
namespace graphics {
namespace opengl {

char * loadFromFile(const char *fn);
void printShaderInfoLog(GLuint obj, const char *title);
void printProgramInfoLog(GLuint obj, const char *title);


ShaderProgram::ShaderProgram() {
    sh_num = 0;
    sh_program_object = glCreateProgram();
}


ShaderProgram::~ShaderProgram() {
    off();
    for (int i=0; i<sh_num; ++i) {
        glDetachShader(sh_program_object, shaders[i]);
    }
}


void ShaderProgram::on() {
    glUseProgram(sh_program_object);
}


void ShaderProgram::off() {
    glUseProgram(0);
}


void ShaderProgram::attachShader (ShaderBase const & shader) {
    glAttachShader(sh_program_object, shader.getHandle());
    ++sh_num;
}


void ShaderProgram::link (bool log) {
    glLinkProgram(sh_program_object);

    GLint status;
    glGetProgramiv(sh_program_object, GL_LINK_STATUS, &status);
    if (log && status != GL_TRUE)
        printProgramInfoLog(sh_program_object, "Shader Program linking");
}


void ShaderProgram::validate (bool log) {
    glValidateProgram(sh_program_object);

    GLint status;
    glGetProgramiv(sh_program_object, GL_VALIDATE_STATUS, &status);
    if (log && status != GL_TRUE)
        printProgramInfoLog(sh_program_object, "Shader Program validating");
}


// Проверка поддержки шейдеров
bool ShaderProgram::GLSLcheck() {
    char *szGLExtensions = (char*) glGetString(GL_EXTENSIONS);
    if (!strstr(szGLExtensions, "GL_ARB_shader_objects ")) {
        //MessageBoxA(0, "Расширение для работы с шейдерами не поддерживается!", "Error", MB_OK);
        return false;
    }
    if (!glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB
            || !glCreateShaderObjectARB || !glCompileShaderARB
            || !glAttachObjectARB || !glLinkProgramARB || !glDetachObjectARB) {
        //MessageBoxA(0, "Одна или более функций для работы с шейдерами не поддерживается",
        //        "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }
    return true;
}


void ShaderProgram::setUniform1i (const char *uname, int v) {
    GLint p = glGetUniformLocation(sh_program_object, uname);
    glUniform1i(p, v);
}


void ShaderProgram::setUniform1f (const char *uname, float v) {
    GLint p = glGetUniformLocation(sh_program_object, uname);
    glUniform1f(p, v);
}


///////////////////////////////////////////////////////////
// Shader Base
///////////////////////////////////////////////////////////


ShaderBase::ShaderBase (const char * filename) {
    source = loadFromFile(filename);
}


ShaderBase::~ShaderBase () {
    delete source;
    glDeleteShader(sh_object);
}


const char * ShaderBase::getSource () const {
    return source;
}


GLuint ShaderBase::getHandle () const {
    return sh_object;
}


// Vertex Shader
//#########################################################

VertexShader::VertexShader (const char * filename, bool log)
        : ShaderBase (filename) {
    sh_object = glCreateShaderObjectARB(GL_VERTEX_SHADER);
    glShaderSourceARB(sh_object, 1, (const char**) &source, NULL);
    glCompileShaderARB(sh_object);

    GLint status;
    glGetShaderiv(sh_object, GL_COMPILE_STATUS, &status);
    if (log && status != GL_TRUE) {
        printShaderInfoLog(sh_object, filename);
    }
}


// Fragment Shader
//#########################################################

FragmentShader::FragmentShader (const char * filename, bool log)
        : ShaderBase (filename) {
    sh_object = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
    glShaderSourceARB(sh_object, 1, (const char**) &source, NULL);
    glCompileShaderARB(sh_object);

    GLint status;
    glGetShaderiv(sh_object, GL_COMPILE_STATUS, &status);
    if (log && status != GL_TRUE) {
        printShaderInfoLog(sh_object, filename);
    }
}


// Utils
//#########################################################

// Загрузка кода шейдера из файла
char * loadFromFile(const char *fn) {
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


// Вывод лога компиляции шейдера
void printShaderInfoLog(GLuint obj, const char *title) {
    int len = 0, chWritten = 0;
    char *infoLog;
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);

    if (len > 1) {
        infoLog = new char [len+1];
        glGetShaderInfoLog(obj, len, &chWritten, infoLog);
        MessageBoxA(NULL, infoLog, title, 0);
        delete[] infoLog;
    }
    else MessageBoxA(NULL, "all right", title, 0);
}


// Вывод лога компиляции программы
void printProgramInfoLog(GLuint obj, const char *title) {
    int len = 0, chWritten = 0;
    char *infoLog;
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);

    if (len > 1) {
        infoLog = new char [len+1];
        glGetProgramInfoLog(obj, len, &chWritten, infoLog);
        MessageBoxA(NULL, infoLog, title, 0);
        delete[] infoLog;
    }
    else MessageBoxA(NULL, "all right", title, 0);
}

}}} // namespaces
