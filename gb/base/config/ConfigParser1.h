
/**
 * @file ConfigParser1.h
 * @brief Заголовок класса ConfigParser1 - парсер файла с параметрами
 * @author Шаров Сергей, Zefick 2010-2011
 */

#ifndef CONFIG_PARSER1_H
#define CONFIG_PARSER1_H

#include <utility>
#include <vector>

#include "VariableMap.h"

namespace gb {
namespace base {
namespace config {

/**
 * Класс парсера конфига
 */
class ConfigParser1 : IParser {
    friend class VariableMap;

    protected:
        ConfigParser1();
        virtual ~ConfigParser1();

        void parse(const char *text, VariableMap *conf);

        enum tokenType {
            word, lbrace, rbrace, assign, end
        };
        typedef std::pair<tokenType, const char*> token;

        void tokenize(const char *text);

        void U(const std::string section);
        void S(const std::string section);

        void illegal(const char *t);

    private:
        std::vector<token> mas;
        VariableMap *config;
        char *heap;
};

// namespaces
}}}

#endif // CONFIG_PARSER1_H
