/*!	\file Path_win32.cpp
 *  Пути к файлам и ресурсам, работа с директориями и путями. Win32 реализация.
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include "pch.h"

#include <gb/system/Path.h>
#include <gb/str/String.h>

#ifdef _WIN32

#include <Windows.h>
#include <Shlobj.h>
#include <direct.h>

namespace gb
{
	namespace system
	{

Path applicationDataDir( const std::string & company_name, const std::string & app_name )
{
	Path result = applicationDataDir( app_name ) / company_name;
	if (! result.exists() ) {
		result.createDir();
	}
	return result;
}

Path applicationDataDir( const std::string & app_name )
{
	Path result = applicationDataDir() / app_name;
	if (! result.exists() ) {
		result.createDir();
	}
	return result;
}

Path applicationDataDir()
{
	wchar_t outPath [MAX_PATH];
	SHGetFolderPathW( NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, (LPWSTR)outPath );
	return Path( str::toUtf8( outPath ) );
}

Path myDocumentsDir()
{
	wchar_t outPath [MAX_PATH];
	SHGetFolderPathW( NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, outPath );
	return Path( str::toUtf8( outPath ) );
}

Path resourcesDir()
{
	return initialDir();
}

Path currentDir()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( boost::filesystem::current_path() );
#else
	wchar_t currentPath [MAX_PATH];
	_wgetcwd( currentPath, sizeof(currentPath) );
	return Path( str::toUtf8( currentPath ) );
#endif
}


bool Path::exists()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return boost::filesystem::exists( toWstring() );
#else
	return GetFileAttributesW( toWstring().c_str() ) != INVALID_FILE_ATTRIBUTES; 
#endif
}


void Path::createDir()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	boost::filesystem::create_directory( toWstring() );
#else
	CreateDirectoryW( toWstring().c_str(), NULL );
#endif
}

bool Path::isDirectory()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return boost::filesystem::is_directory( toWpath() );
#else
	return GetFileAttributesW( toWstring().c_str() ) & FILE_ATTRIBUTE_DIRECTORY == FILE_ATTRIBUTE_DIRECTORY; 
#endif
}


	} // namespace system
} // namespace gb

#endif //_WIN32
