#include "precompiled_headers.h"
#include "system/path.h"
#include "base/String.h"

#ifdef _WIN32

using namespace gb;
using namespace system;

#if ! GB_ALLOW_BOOST_LIBRARY__PATH
Path Path::initialPath_( true );
#endif


Path initialDir()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( boost::filesystem::initial_path() );
#else
	return Path::initialPath_;
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
	// TODO!
	throw "up";
#endif
}

Path Path::getParent()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return Path( value.branch_path() );
#else
	// TODO!
	throw "up";
#endif
}

bool Path::isAbsolute()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return value.is_complete();
#else
	// TODO: Этот код не проверяет сетевые имена, и хитрые имена, стартующие "\\" или "\\.\"
	return str::startsWith( value, "/" )
		|| str::startsWith( value, "\\" )
		|| (value.size() >= 2 && value[1] == ':');
#endif
}

std::string Path::getExtension()
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	return boost::filesystem::extension( value );
#else
	// TODO:
	throw "up";
#endif
}

void Path::changeExtension( const std::string & new_ext )
{
#if GB_ALLOW_BOOST_LIBRARY__PATH
	boost::filesystem::change_extension( value, new_ext );
#else
	// TODO:
	throw "up";
#endif
}


#endif //_WIN32
