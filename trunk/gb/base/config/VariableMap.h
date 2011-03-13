
/**
 * @file VariableMap.h
 * @brief Заголовок класса VariableMap - контейнера параметров
 * @author Шаров Сергей, Zefick 2010-2011
 */

#ifndef VARIABLE_MAP
#define VARIABLE_MAP

#include <string>
#include <sstream>
#include <map>
#include <gb/base/Logger.h>

namespace gb {
namespace base {
namespace config {

/**
 * Исключение, которое должны выбрасывать парсеры при ошибке разбора
 */
struct parseException {
    std::string message;
    parseException (const std::string & msg) : message(msg) {}
    const char * what () {return message.c_str();}
};

/**
 * Интерфейс парсера конфигурационного файла
 */
class IParser {
protected:
    friend class VariableMap;
    void parse(const char *text, class VariableMap *conf);
};

/**
 * Класс для хранения именованных значений
 */
class VariableMap : public std::map<std::string, std::string> {

    public:

        VariableMap();

        ~VariableMap();

        /**
         * Получение строки, хранящей значение параметра
         * @param name имя параметра
         * @return значение параметра в виде строки
         */
        std::string getParamStr (std::string name) const;

        /**
         * Задание значения параметра
         * @param name имя параметра
         * @param value задаваемое значение параметра
         */
        void setParamStr (const std::string & name, const std::string & value);

        /**
         * Чтение набора параметров из файла с помощью специализированного парсера.
         * @param Parser класс парсера
         * @param filename путь к файлу
         */
        template <class Parser>
        bool parseFile (const char * filename) {
			bool result = false;
            const char *text = NULL;
            try {
                Parser parser;
                text = openFile(filename);
                parser.parse(text, this);
				result = true;
            }
            catch (parseException ex) {
                ERROR_LOG(ex.what());
            }
            delete[] text;
			return result;
        }

        /**
         * Чтение набора параметров из строки с помощью специализированного парсера.
         * @param Parser класс парсера
         * @param filename путь к файлу
         */
        template <class Parser>
        bool parse (const char * text) {
            try {
                Parser parser;
                parser.parse(text, this);
            }
            catch (parseException ex) {
                ERROR_LOG(ex.what());
				return false;
            }
            return true;
        }

        /**
         * Получение значения параметра заданного типа.
         * @param T нужный тип
         * @param name имя параметра
         * @param def_value значение по умолчанию для незаданного параметра
         */
        template <typename T>
        T get (const std::string name, T def_value = T()) const {
            T res = def_value;
            std::string str = getParamStr(name);
            if (!str.empty()) {
                std::istringstream S(str);
                S >> res;
            }
            return res;
        }

        /**
         * Задание значения параметра заданного типа
         * @param T нужный тип
         * @param name имя параметра
         * @param value задаваемое значение параметра
         */
        template <typename T>
        void set (const char* name, const T& value) {
            std::ostringstream S;
            S << value;
            setParamStr(name, S.str());
        }

    private:

        char * openFile (const char *filename);
};

// namespaces
}}}

#endif // VARIABLE_MAP
