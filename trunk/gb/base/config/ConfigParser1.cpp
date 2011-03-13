
/**
 * @file ConfigParser1.cpp
 * @brief Реализация функций класса ConfigParser1 - парсера файла с параметрами
 * @author Zefick 2010-2011
 */

//#include "pch.h"

#include <cstdio>
#include <cstring>

#include "ConfigParser1.h"

namespace gb {
namespace base {
namespace config {


ConfigParser1::ConfigParser1 () {}

ConfigParser1::~ConfigParser1 () {
    if (heap)
        delete[] heap;
}

//! Лексический разбор текста
void ConfigParser1::tokenize (const char *str) {

    heap = new char[strlen(str)*2];
    char * top = heap;

    for (; *str!='\0'; ++str) {
        if (*str == '=') {
            mas.push_back(token(assign, top));
            *top++ = '=';
            *top++ = '\0';
        }
        else if (*str == '{') {
            mas.push_back(token(lbrace, top));
            *top++ = '{';
            *top++ = '\0';
        }
        else if (*str == '}') {
            mas.push_back(token(rbrace, top));
            *top++ = '}';
            *top++ = '\0';
        }
        // skip comments
        else if (str[0] == '/' && str[1]=='/') {
            while(*str != '\n') str++;
        }
        // quoted string
        else if (*str == '"') {
            mas.push_back(token(word, top));
            str++;
            while(*str != '"') *top++ = *str++;
            *top++ = '\0';
        }
        // unquoted value
        else if (isalnum(*str) || *str=='_') {
            mas.push_back(token(word, top));
            while(isalnum(*str) || *str=='_') *top++ = *str++;
            *top++ = '\0';
            str--;
        }
    }
    mas.push_back(token(end, NULL));
}

std::vector<ConfigParser1::token>::iterator it;

//! Начало разбора
void ConfigParser1::parse (const char *text, VariableMap *_conf) {
    config = _conf;
    tokenize(text);
    it = mas.begin();
    U("");
}

//! Печать ошибки о неправильной лексеме
void ConfigParser1::illegal (const char *t) {
    char message[200];
    sprintf(message, "illegal token: \"%s\" !", t);
    throw parseException(message);
}


/*
  U :: NSU | e
  S :: {U} | = V | V
  N :: <name>
  V :: <value>
*/

void ConfigParser1::U (const std::string section) {

    while (it->first == word) {
        std::string newSection = section + it->second;
        ++it;
        //puts(newSection.c_str());
        S (newSection);
    }
    return;
}


void ConfigParser1::S (const std::string section) {

    if (it->first == lbrace) {
        ++it;
        U (section + ".");
        if (it->first == rbrace) {
            ++it;
            return;
        }
        else illegal(it->second);
    }
    else if (it->first == assign) {
        ++it;
        if (it->first != word)
            illegal(it->second);
        config->setParamStr(section, it->second);  /**/
        ++it;
        return;
    }
    else
        illegal(it->second);
}

// namespaces
}}}
