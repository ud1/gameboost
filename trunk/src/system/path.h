#pragma once
/*!	\file Path.h
 *  Пути к файлам и ресурсам, работа с директориями и путями
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */

#include "Config.h"

// здесь можно локально отключить использование Boost, если вдруг Вам не нравится
// Boost.Filesystem.Path и хочется простых русских std::string
#define GB_ALLOW_BOOST_LIBRARY__PATH GB_ALLOW_BOOST_LIBRARY
//#define GB_ALLOW_BOOST_LIBRARY__PATH 1
//#define GB_ALLOW_BOOST_LIBRARY__PATH 0

#if GB_ALLOW_BOOST_LIBRARY__PATH
#include <boost/filesystem.hpp>
#endif

namespace gb
{
    namespace system
    {



class Path
{
private:
#if GB_ALLOW_BOOST_LIBRARY__PATH
    boost::filesystem::path value;
#else
    std::string value;
#endif

public:
    Path()
	{
    }
    Path( const std::string & p ): value(p)
	{
    }
    Path( const char * p ): value(p)
	{
    }

#if GB_ALLOW_BOOST_LIBRARY__PATH
	Path( const boost::filesystem::path & p ): value(p)
	{
	}
#endif

	inline bool operator < ( const Path & other ) const
	{
		return value < other.value;
	}

	Path operator / ( const Path & other ) const;
	Path & operator /= ( const Path & other );

	//! Существует ли в каталоге файловой системы запись, на которую указывает Path
	//! (директория или файл, или что-нибудь другое - неважно)
	bool exists();
			
	//! Существует ли и является ли директорией данный Path?
	bool isDirectory();

	//! Создать одну директорию по пути, указанному в Path, не создаёт ничего, если родительская папка
	//! для будущей директории тоже ещё не существует. Используйте createDirectories() в таком случае.
	void createDir();

	//! Создать все несуществующие директории в Path
	void createDirectories();

	std::string toString();
	std::wstring toWstring();
#if GB_ALLOW_BOOST_LIBRARY__PATH
	boost::filesystem::wpath toWpath();
#endif
	void normalize();

	//---------------------------------------
	// Функции декомпозиции и композиции
	// http://www.solarix.ru/for_developers/cpp/boost/filesystem/ru/path.shtml
	// http://www.boost.org/doc/libs/1_32_0/libs/filesystem/doc/path.htm
	//---------------------------------------

	//! Возвращает последнюю часть пути - имя файла или директории
	std::string getLeaf();
			
	//! Возвращает родительскую директорию для пути
	Path getParent();

	//! Проверка на пустое значение
	inline bool empty() {
		return value.empty();
	}

	//! Привязан ли путь к корневой директории и имени диска, или является относительным?
	bool isAbsolute();

	//! Получить расширение файла с точкой, или пустую строку
	std::string getExtension();

	//! Установить расширение файла, параметр должен включать точку
	void changeExtension( const std::string & new_ext );
};



//! Путь к папке C:/Users/%LOGIN%/AppData/%COMPANY_NAME%/%APP_NAME%, создаётся если не было
Path applicationDataDir( const std::string & company_name, const std::string & app_name );

//! Путь к папке C:/Users/%LOGIN%/AppData/%APP_NAME%, создаётся если не было
Path applicationDataDir( const std::string & app_name );

//! Путь к папке C:/Users/%LOGIN%/AppData
Path applicationDataDir();

//! Путь к папке с документами пользователя
Path myDocumentsDir();

//! Путь к папке с ресурсами игры (в MacOSX может отличаться от папки процесса!)
Path resourcesDir();

//! Текущая папка процесса
Path currentDir();

//! Стартовая папка процесса
Path initialDir();



    } // namespace sys
} // namespace gb
