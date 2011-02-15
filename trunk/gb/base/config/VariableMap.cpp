
/**
 * @file VariableMap.cpp
 * @brief Заголовок класса VariableMap - контейнера параметров
 * @author Шаров Сергей, Zefick 2010-2011
 */

#include "pch.h"

#include <cstdio>
#include <string>

#include "VariableMap.h"

namespace gb {
namespace base {
namespace config {


VariableMap::VariableMap () {}


VariableMap::~VariableMap () {}


std::string VariableMap::getParamStr (std::string paramName) const {

    if (vmap.find(paramName) != vmap.end()) {
        return vmap.at(paramName);
    }
    return std::string();
}


void VariableMap::setParamStr (
            const std::string & paramName,
            const std::string & paramValue) {
    vmap[paramName] = paramValue;
}


char * VariableMap::openFile (const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    char *text = new char[size+1];
    fread(text, 1, size, file);
    fclose(file);
    text[size] = '\0';
    return text;
}

// namespaces
}}}
