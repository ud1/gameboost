/*!	\file Path.cpp
 *  Пути к файлам и ресурсам, работа с директориями и путями. Платформонезависимая часть.
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include <gb/system/Path.h>
#include <gb/str/String.h>

#ifdef _WIN32

#include <Windows.h>
#include <Shlobj.h>

namespace gb
{
	namespace system
	{


#if ! GB_ALLOW_BOOST_LIBRARY__PATH

class AutoInitialPath
{
public:
	static wchar_t initialPath_[MAX_PATH];
public:
	//! Скрытый конструктор для initialPath - на старте программы берёт текущий каталог процесса
	AutoInitialPath()
	{
		_wgetcwd( initialPath_, sizeof( initialPath_ ) );
    }
};

wchar_t AutoInitialPath::initialPath_[MAX_PATH];
AutoInitialPath autoInitialPath;

#endif // ! GB_ALLOW_BOOST_LIBRARY__PATH


Path initialDir()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( boost::filesystem::initial_path() );
#else
	return Path( str::toUtf8( AutoInitialPath::initialPath_ ) );
#endif
}

std::string Path::toString()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return value.string();
#else
	return value;
#endif
}

std::wstring Path::toWstring()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return str::toWide( value.string() );
#else
	return str::toWide( value );
#endif
}

#if GB_ALLOW_BOOST_LIBRARY__PATH
boost::filesystem::wpath Path::toWpath()
{
	// TODO: Выглядит ужасно, работает наверное медленно
	return boost::filesystem::wpath( str::toWide( value.string() ) );
}
#endif



Path Path::operator / ( const Path & other ) const
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( value / other.value );
#else
	// TODO!
	throw "up";
#endif
}



Path & Path::operator /= ( const Path & other )
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	value /= other.value;
	return * this;
#else
	// TODO!
	throw "up";
#endif
}



std::string Path::getLeaf()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return value.leaf();
#else
	
	size_t slashpos = value.rfind( '/' );
#ifdef _WIN32
	size_t rslashpos = value.rfind( '\\' );

	if (slashpos != std::string::npos && slashpos > rslashpos) {
		return value.substr( slashpos+1 );
	}
	if (rslashpos != std::string::npos && rslashpos > slashpos) {
		return value.substr( rslashpos+1 );
	}
#endif // _WIN32

	if (slashpos != std::string::npos) {
		return value.substr( slashpos+1 );
	}

	return "";
#endif
}



Path Path::getParent()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( value.branch_path() );
#else
	// TODO: поддержка /./ и /../
	throw "up";
#endif
}



bool Path::isAbsolute()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return value.is_complete();
#else
	// TODO: Этот код не проверяет сетевые имена, и хитрые имена, начинающиеся с "\\" или "\\.\"
	return str::startsWith( value, "/" )
		|| str::startsWith( value, "\\" )
		|| (value.size() >= 2 && value[1] == ':');
#endif
}



std::string Path::getExtension()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return boost::filesystem::extension( value );
#else // no boost

	size_t dotpos = value.rfind( '.' );
	size_t slashpos = value.rfind( '/' );
#ifdef _WIN32
	size_t rslashpos = value.rfind( '\\' );
#endif // _WIN32

	// нет точки - нет расширения
	if (dotpos == std::string::npos) return "";
	// есть слеш, и есть точка, и точка идёт раньше слеша - нет расширения
	if (slashpos != std::string::npos && slashpos > dotpos) return "";
#ifdef _WIN32
	// есть обратный слеш, и есть точка, и точка идёт раньше обратного слеша - нет расширения
	if (rslashpos != std::string::npos && slashpos > dotpos) return "";
#endif // _WIN32
	return value.substr( dotpos );

#endif // GB_ALLOW_BOOST_LIBRARY__PATH
}



void Path::changeExtension( const std::string & new_ext )
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	value = boost::filesystem::change_extension( value, new_ext );
#else
	// TODO:
	throw "up";
#endif
}


void Path::createDirectories()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	boost::filesystem::create_directories( toWstring() );
#else

#ifdef _WIN32
	SHCreateDirectoryExW( NULL, toWstring().c_str(), NULL );
#else
	throw "up";
#endif

#endif
}



	} // namespace system
} // namespace gb

#endif //_WIN32

