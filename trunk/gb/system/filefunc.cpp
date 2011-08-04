
//#include "pch.h"

#ifdef WIN32 // only windows

#include <gb/Config.h>
#include <gb/system/filefunc.h>

/*
#if GB_ALLOW_BOOST_LIBRARY
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#endif
*/

#include <gb/t/func.h>


// kst template library
// http://code.google.com/p/kst/
#include <kst/func.hpp>



#ifdef WIN32
#include "Strsafe.h"
#endif

#pragma warning(push)
#pragma warning( disable : 4995 )
#pragma warning( disable : 4290 ) // пока отключено
#pragma warning( disable : 4297 )

//=========================================================================


namespace gb 
{
namespace system 
{
namespace filefunc 
{

//==============================================================

	static HRESULT Safe_strcpy(char* dest, const char* src ) 
	{
		try { strcpy(dest, src); } catch(...) { return E_FAIL; }; return 0;
	};

	static HRESULT Safe_strncpy(char* dest, const char* src, size_t num) 
	{
		try { strncpy(dest, src, num); } catch(...) { return E_FAIL; }; return 0;
	};

	static HRESULT Safe_wcstrcpy(wchar_t* dest, const wchar_t* src ) 
	{
		try { wcscpy(dest, src); } catch(...) { return E_FAIL; }; return 0;
	};

	static HRESULT Safe_wcstrncpy(wchar_t* dest, const wchar_t* src, size_t num) 
	{
		try { wcsncpy(dest, src, num); } catch(...) { return E_FAIL; }; return 0;
	};



	static HRESULT SafeMemZero(void* pdest,  const unsigned int numBytes) {
		try { memset(pdest, 0 , (size_t)numBytes );  } 
		catch(...) { return E_FAIL;  }; 
		return 0;
	}




// \brief  std вектор для PathDataA  
typedef std::vector<PathDataA> VEC_PathDataA;

// \brief  std вектор для PathDataW  
typedef std::vector<PathDataW> VEC_PathDataW; 	

} // end ns
} // end ns
} // end ns

//==================================================




class GlobalArrS_BufferA {
public:
	GlobalArrS_BufferA() {};

	void operator = (const gb::system::filefunc::PathDataA& pd) {
		strcpy(buffer, pd.path );	
	};

	void setzero() {  memset(buffer, 0, sizeof(buffer) ); };
	bool empty() const { return ( buffer[0] == 0 ); };

	gb::system::filefunc::PathDataA as_PathDataA() {
		gb::system::filefunc::PathDataA pd;
		pd = buffer;

		return pd;
	};

	CHAR buffer[MAX_PATH+1];
};

class GlobalArrSearchPathA 
{
public:
	GlobalArrSearchPathA() {
		__Init();


	};

	void clear() {
#pragma message("ks777^^sys::filefunc После перерефр.  надо проверить")
		kst::setzero_buffer<GlobalArrS_BufferA>(m_arr, gb::system::filefunc::MAX_GLOBALSEARCHPATH );	

	};

	bool Add(gb::system::filefunc::PathDataA& _path) {
		__Init();
		const int NFREEINDEX = kst::findFirstEmptyFromBuffer(m_arr, gb::system::filefunc::MAX_GLOBALSEARCHPATH);
		if(NFREEINDEX == -1) 
			return false;

		m_arr[NFREEINDEX] = _path;
		m_numUsed ++;
		return true;	
	};

	unsigned int size()   {
		__Init();
		return m_numUsed;

	};

	gb::system::filefunc::PathDataA at(const unsigned int indx) throw(char*) {
		__Init();
		if( indx >= gb::system::filefunc::MAX_GLOBALSEARCHPATH ) {
			throw std::runtime_error("Illegal index");
			static const int __ZERO = 0;

			//#pragma warning (push)
			//#pragma warning (disable : 4172)
			return (gb::system::filefunc::PathDataA&)__ZERO;
			//#pragma warning (pop)


		};

		return m_arr[indx].as_PathDataA() ;
	};

	gb::system::filefunc::PathDataA  operator [] (const unsigned int indx) throw(char*) {
		__Init();
		return at(indx);	
	};

private:
	void __Init() {
		static bool stb_firstcall = true;
		if(stb_firstcall==false) return;
		stb_firstcall = false;
		// init code
		m_numUsed = 0;
		for(unsigned int c=0; c<gb::system::filefunc::MAX_GLOBALSEARCHPATH; c++) {
			m_arr[c].setzero();  
		};


	};

	unsigned int m_numUsed;
	GlobalArrS_BufferA m_arr[gb::system::filefunc::MAX_GLOBALSEARCHPATH];
};
// end class

static GlobalArrSearchPathA  g_GlobalArrSearchPathA;



class GlobalArrS_BufferW {
public:
	GlobalArrS_BufferW() {};

	void operator = (const gb::system::filefunc::PathDataW& pd) {
		wcscpy  (buffer, pd.path );	
	};

	void setzero() {  memset(buffer, 0, sizeof(buffer) ); };
	bool empty() const { return ( buffer[0] == 0 ); };

	gb::system::filefunc::PathDataW as_PathDataW() {
		gb::system::filefunc::PathDataW pd;
		pd = buffer;

		return pd;
	};

	WCHAR buffer[MAX_PATH+1];
};

class GlobalArrSearchPathW 
{
public:
	GlobalArrSearchPathW() {
		__Init();


	};

	void clear() {
		kst::setzero_buffer(m_arr, gb::system::filefunc::MAX_GLOBALSEARCHPATH );	

	};

	bool Add(gb::system::filefunc::PathDataW& _path) {
		__Init();
		const int NFREEINDEX = kst::findFirstEmptyFromBuffer(m_arr, gb::system::filefunc::MAX_GLOBALSEARCHPATH);
		if(NFREEINDEX == -1) 
			return false;

		m_arr[NFREEINDEX] = _path;
		m_numUsed ++;
		return true;	
	};

	unsigned int size()   {
		__Init();
		return m_numUsed;

	};

	gb::system::filefunc::PathDataW at(const unsigned int indx) throw() 
	{
		__Init();
		if( indx >= gb::system::filefunc::MAX_GLOBALSEARCHPATH ) {
			throw std::runtime_error("Illegal index");
			static const int __ZERO = 0;

			//#pragma warning (push)
			//#pragma warning (disable : 4172)
			return (gb::system::filefunc::PathDataW&)__ZERO;
			//#pragma warning (pop)


		};

		return m_arr[indx].as_PathDataW() ;
	};

	gb::system::filefunc::PathDataW  operator [] (const unsigned int indx) throw() 
	{
		__Init();
		return at(indx);	
	};

private:
	void __Init() {
		static bool stb_firstcall = true;
		if(stb_firstcall==false) return;
		stb_firstcall = false;
		// init code
		m_numUsed = 0;
		for(unsigned int c=0; c<gb::system::filefunc::MAX_GLOBALSEARCHPATH; c++) {
			m_arr[c].setzero();  
		};


	};

	unsigned int m_numUsed;
	GlobalArrS_BufferW m_arr[gb::system::filefunc::MAX_GLOBALSEARCHPATH];
};
// end class

static GlobalArrSearchPathW  g_GlobalArrSearchPathW;



//kst::FixedArray<gb::system::filefunc::PathDataA, gb::system::filefunc::MAX_GLOBALSEARCHPATH> g_GlobalArrSearchPathA;
//kst::FixedArray<gb::system::filefunc::PathDataW, gb::system::filefunc::MAX_GLOBALSEARCHPATH> g_GlobalArrSearchPathW;

 

//===========  времянки для совместимости (убрать) =================
 
 
//==================================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtApendGlobalSearchPathA(const gb::system::filefunc::PathDataA* path) {
	HRESULT hr =0;
	gb::system::filefunc::PathDataA _path = *path;

	// old code
	// g_GlobalArrSearchPathA.push_back( _path );

	// new code

	//const int FREE_INDEX = kst::FindFirstEmptyFromBuffer(g_GlobalArrSearchPathA.ptr(),  gb::system::filefunc::MAX_GLOBALSEARCHPATH );
	//if(FREE_INDEX == -1) {
	//	// not found. buffer is FULL !!
	//	return E_FAIL;
	//	}
	//
	//g_GlobalArrSearchPathA[FREE_INDEX] = _path;

	// new 2
	if( !g_GlobalArrSearchPathA.Add(_path) ) {
		// error add
		return E_FAIL;
	};


	return   hr;
};

//==================================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtApendGlobalSearchPathW(const gb::system::filefunc::PathDataW* path) {
	HRESULT hr =0;
	gb::system::filefunc::PathDataW _path = *path;

	//	const int FREE_INDEX = kst::FindFirstEmptyFromBuffer(g_GlobalArrSearchPathW.ptr(), g_GlobalArrSearchPathW.arrSize() );
	//if(FREE_INDEX == -1) {
	//	// not found. buffer is FULL !!
	//	return E_FAIL;
	//	}
	//
	//g_GlobalArrSearchPathW[FREE_INDEX] = _path;



	// old code
	// g_GlobalArrSearchPathW.push_back(*path);

	if( !g_GlobalArrSearchPathW.Add(_path) ) {
		// error add
		return E_FAIL;
	};


	return hr;
};






//
//

CHAR*  FileUtMediaSearchPathA()
{
	static CHAR s_strMediaSearchPath[MAX_PATH] = {0};
	return s_strMediaSearchPath;
}

WCHAR*  FileUtMediaSearchPathW()
{
	static WCHAR s_strMediaSearchPath[MAX_PATH] = {0};
	return s_strMediaSearchPath;

} 

LPSTR  FileUtGetMediaSearchPathA()
{
	return  FileUtMediaSearchPathA();
}

GB_FF_API  HRESULT gb::system::filefunc::FileUtGetSearchPathA(gb::system::filefunc::PathDataA* pOut) 
{
	HRESULT hr =0;
	__try {
		strncpy(  pOut->path , FileUtGetMediaSearchPathA() , MAX_PATH );
	}
	__except(EXCEPTION_EXECUTE_HANDLER) { hr |= E_FAIL; };
	return hr;
};

//======================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtExecuteFindA(gb::system::filefunc::PathDataA* path) {
	HRESULT hr =0;
	static CHAR ss[MAX_PATH]; ss[0]=0; 
	__try {
		hr |= FileUtFindFileCchA(ss, MAX_PATH, path->path  );
		if FAILED(hr) { return hr;  };
		strncpy(path->path , ss, MAX_PATH );

	}  // try
	__except(EXCEPTION_EXECUTE_HANDLER) {
		hr |=  E_FAIL;
	}
	return hr;
};

//===================================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtExecFindWithGLobalSearchPathA(gb::system::filefunc::PathDataA* path) {
	HRESULT hr  =0;

	static CHAR spathOut[MAX_PATH];       spathOut[0]=0;


	if(g_GlobalArrSearchPathA.size() == 0 )
	{
		// search path is empty
		return FileUtExecuteFindA(path);
	}
	else
	{
		// has search path
		static gb::system::filefunc::PathDataA  pathSearch;  pathSearch.path[0]=0;
		static CHAR defaultSearchPath[MAX_PATH];   defaultSearchPath[0]=0;

		hr |= Safe_strncpy(defaultSearchPath,  FileUtMediaSearchPathA(), MAX_PATH );
		if FAILED(hr) return hr;

		hr = E_FAIL;
		for(size_t c=0; c<g_GlobalArrSearchPathA.size(); c++) {
			pathSearch =   g_GlobalArrSearchPathA.at( (unsigned int)c );
			if( pathSearch.empty() ) continue;

			FileUtSetMediaSearchPathA (  pathSearch.path  );
			hr = FileUtFindFileCchA(spathOut,  MAX_PATH, path->path  );

			if( hr == 0 ) {
				break;
			};

		} // for

		if(hr == S_OK) {
			// succes
			hr |= Safe_strncpy(path->path , spathOut, sizeof(PathDataA) );
		}
		else
		{
			// failed
			return hr;
		}



		// restore default search path
		hr |= Safe_strncpy( FileUtMediaSearchPathA(), defaultSearchPath,  MAX_PATH );
		// ?????????????????


	}; // if

	return hr;
}; 

//===================================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtExecFindWithGLobalSearchPathW(gb::system::filefunc::PathDataW* path) {
	HRESULT hr  =0;

	static WCHAR spathOut[MAX_PATH];   spathOut[0]=0;


	if(g_GlobalArrSearchPathW.size() == 0 )
	{
		// search path is empty
		return FileUtExecuteFindW(path);
	}
	else
	{
		// has search path
		static gb::system::filefunc::PathDataW  pathSearch;  pathSearch.path[0]=0;
		static WCHAR defaultSearchPath[MAX_PATH];   defaultSearchPath[0]=0;

		hr |= Safe_wcstrncpy(defaultSearchPath,  FileUtMediaSearchPathW(), MAX_PATH );
		if FAILED(hr) return hr;

		for(size_t c=0; c<g_GlobalArrSearchPathW.size(); c++) {
			pathSearch =   g_GlobalArrSearchPathW.at( (unsigned int)c );
			if( pathSearch.empty() ) continue;

			FileUtSetMediaSearchPathW (  pathSearch.path  );
			hr = FileUtFindFileCchW(spathOut,  MAX_PATH, path->path  );
			if( hr == 0 ) {
				break;
			};

		} // for

		if(hr == S_OK) {
			// succes
			hr |= Safe_wcstrncpy(path->path , spathOut, sizeof(PathDataA) );
		}
		else
		{
			// failed
		}



		// restore default search path
		hr |= Safe_wcstrncpy( FileUtMediaSearchPathW(), defaultSearchPath,  MAX_PATH );
		// ?????????????????


	}; // if

	return hr;
}; 

//=================================================
GB_FF_API  HRESULT gb::system::filefunc::FileUtExecuteFindW(gb::system::filefunc::PathDataW* path)  {
	HRESULT hr =0;
	static WCHAR ss[MAX_PATH]; ss[0]=0; 
	__try {
		hr |= FileUtFindFileCchW(ss, MAX_PATH, path->path  );
		if FAILED(hr) { return hr;  };
		wcsncpy (path->path , ss, MAX_PATH );
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
		hr |=  E_FAIL;
	}
	return hr;
};

GB_FF_API  HRESULT gb::system::filefunc::FileUtSetMediaSearchPathA( LPSTR strPath )
{
	HRESULT hr;
	if(strPath == NULL) {
		hr |= SafeMemZero( FileUtMediaSearchPathA(), MAX_PATH * sizeof(CHAR) );
		return hr;
	};

	CHAR* s_strSearchPath =  FileUtMediaSearchPathA();

	hr = StringCchCopyA( s_strSearchPath, MAX_PATH, strPath );   
	if( SUCCEEDED(hr) )
	{
		// append slash if needed
		size_t ch;
		hr = StringCchLengthA( s_strSearchPath, MAX_PATH, &ch );
		if( SUCCEEDED(hr) && s_strSearchPath[ch-1] != '\\')
		{
			hr = StringCchCatA( s_strSearchPath, MAX_PATH, "\\" );   
		}
	}

	return hr;

}

GB_FF_API   HRESULT gb::system::filefunc::FileUtFindFileCchA( CHAR* strDestPath, int cchDest, LPSTR strFilename )
{
	bool bFound;
	CHAR strSearchFor[MAX_PATH];

	if( NULL==strFilename || strFilename[0] == 0 || NULL==strDestPath || cchDest < 10 )
		return E_INVALIDARG;

	// Get the exe name, and exe path
	CHAR strExePath[MAX_PATH] = {0};
	CHAR strExeName[MAX_PATH] = {0};
	CHAR* strLastSlash = NULL;
	GetModuleFileNameA( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash =  strrchr(strExePath, '\\' ); //  wcsrchr( strExePath, '\\' );
	if( strLastSlash )
	{
		StringCchCopyA( strExeName, MAX_PATH, &strLastSlash[1] );

		// Chop the exe name from the exe path
		*strLastSlash = 0;

		// Chop the .exe from the exe name
		strLastSlash = strrchr( strExeName,  '.' );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	// Typical directories:
	//      .\
	//      ..\
	//      ..\..\
	//      %EXE_DIR%\
	//      %EXE_DIR%\..\
	//      %EXE_DIR%\..\..\
	//      %EXE_DIR%\..\%EXE_NAME%
	//      %EXE_DIR%\..\..\%EXE_NAME%

	// Typical directory search
	bFound = gb::system::filefunc::FileUtFindMediaSearchTypicalDirsA( strDestPath, cchDest, strFilename, strExePath, strExeName );
	if( bFound )
		return S_OK;

	// Typical directory search again, but also look in a subdir called "\media\" 
	StringCchPrintfA( strSearchFor, MAX_PATH,  "media\\%s", strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchTypicalDirsA( strDestPath, cchDest, strSearchFor, strExePath, strExeName );
	if( bFound )
		return S_OK;

	CHAR strLeafName[MAX_PATH] = {0};

	// Search all parent directories starting at .\ and using strFilename as the leaf name
	StringCchCopyA( strLeafName, MAX_PATH, strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsA( strDestPath, cchDest,  ".", strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at the exe's dir and using strFilename as the leaf name
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsA( strDestPath, cchDest, strExePath, strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at .\ and using "media\strFilename" as the leaf name
	StringCchPrintfA( strLeafName, MAX_PATH,  "media\\%s", strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsA( strDestPath, cchDest,  ".", strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at the exe's dir and using "media\strFilename" as the leaf name
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsA( strDestPath, cchDest, strExePath, strLeafName );
	if( bFound )
		return S_OK;

	// On failure, return the file as the path but also return an error code
	StringCchCopyA( strDestPath, cchDest, strFilename );

	return E_FAIL; //  gb::system::filefunc::FileUtERR_MEDIANOTFOUND;

}

GB_FF_API  bool gb::system::filefunc::FileUtFindMediaSearchTypicalDirsA( CHAR* strSearchPath, int cchSearch, LPSTR strLeaf,  CHAR* strExePath, CHAR* strExeName )
{
	// Typical directories:
	//      .\
	//      ..\
	//      ..\..\
	//      %EXE_DIR%\
	//      %EXE_DIR%\..\
	//      %EXE_DIR%\..\..\
	//      %EXE_DIR%\..\%EXE_NAME%
	//      %EXE_DIR%\..\..\%EXE_NAME%
	//      DXSDK media path

	// Search in .\  
	StringCchCopyA( strSearchPath, cchSearch, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\  
	StringCchPrintfA( strSearchPath, cchSearch,  "..\\%s", strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\..\ 
	StringCchPrintfA( strSearchPath, cchSearch,  "..\\..\\%s", strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\..\ 
	StringCchPrintfA( strSearchPath, cchSearch,  "..\\..\\%s", strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\ 
	StringCchPrintfA( strSearchPath, cchSearch,  "%s\\%s", strExePath, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\..\ 
	StringCchPrintfA( strSearchPath, cchSearch,  "%s\\..\\%s", strExePath, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\..\..\ 
	StringCchPrintfA( strSearchPath, cchSearch,  "%s\\..\\..\\%s", strExePath, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in "%EXE_DIR%\..\%EXE_NAME%\".  This matches the DirectX SDK layout
	StringCchPrintfA( strSearchPath, cchSearch,  "%s\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in "%EXE_DIR%\..\..\%EXE_NAME%\".  This matches the DirectX SDK layout
	StringCchPrintfA( strSearchPath, cchSearch,  "%s\\..\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
	if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in media search dir 
	CHAR* s_strSearchPath =  FileUtMediaSearchPathA();
	if( s_strSearchPath[0] != 0 )
	{
		StringCchPrintfA( strSearchPath, cchSearch,  "%s%s", s_strSearchPath, strLeaf ); 
		if( GetFileAttributesA( strSearchPath ) != 0xFFFFFFFF )
			return true;
	}

	return false;

}

GB_FF_API  bool gb::system::filefunc::FileUtFindMediaSearchParentDirsA( CHAR* strSearchPath, int cchSearch, CHAR* strStartAt, CHAR* strLeafName )
{
	CHAR strFullPath[MAX_PATH] = {0};
	CHAR strFullFileName[MAX_PATH] = {0};
	CHAR strSearch[MAX_PATH] = {0};
	CHAR* strFilePart = NULL;

	GetFullPathNameA( strStartAt, MAX_PATH, strFullPath, &strFilePart );
	if( strFilePart == NULL )
		return false;

	while( strFilePart != NULL && *strFilePart != '\0' )
	{
		StringCchPrintfA( strFullFileName, MAX_PATH,  "%s\\%s", strFullPath, strLeafName ); 
		if( GetFileAttributesA( strFullFileName ) != 0xFFFFFFFF )
		{
			StringCchCopyA( strSearchPath, cchSearch, strFullFileName ); 
			return true;
		}

		StringCchPrintfA( strSearch, MAX_PATH,  "%s\\..", strFullPath ); 
		GetFullPathNameA( strSearch, MAX_PATH, strFullPath, &strFilePart );
	}

	return false;


};





//--------------------------------------------------------------------------------------
LPCWSTR  FileUtGetMediaSearchPathW()
{
	return  FileUtMediaSearchPathW();
}

GB_FF_API  HRESULT gb::system::filefunc::FileUtGetSearchPathW(gb::system::filefunc::PathDataW* pOut) {
	HRESULT hr =0;
	__try {
		wcsncpy(  pOut->path , FileUtGetMediaSearchPathW() , MAX_PATH );
	}
	__except(EXCEPTION_EXECUTE_HANDLER) { hr |= E_FAIL; };
	return hr;

};


//--------------------------------------------------------------------------------------
GB_FF_API   HRESULT gb::system::filefunc::FileUtSetMediaSearchPathW( LPCWSTR strPath )
{
	HRESULT hr;
	if(strPath == NULL) {
		hr |= SafeMemZero( FileUtMediaSearchPathW(), MAX_PATH * sizeof(WCHAR) );
		return hr;
	};


	WCHAR* s_strSearchPath =  FileUtMediaSearchPathW();

	hr = StringCchCopy( s_strSearchPath, MAX_PATH, strPath );   
	if( SUCCEEDED(hr) )
	{
		// append slash if needed
		size_t ch;
		hr = StringCchLength( s_strSearchPath, MAX_PATH, &ch );
		if( SUCCEEDED(hr) && s_strSearchPath[ch-1] != L'\\')
		{
			hr = StringCchCat( s_strSearchPath, MAX_PATH, L"\\" );
		}
	}

	return hr;
}


//--------------------------------------------------------------------------------------
// Tries to find the location of a SDK media file
//       cchDest is the size in WCHARs of strDestPath.  Be careful not to 
//       pass in sizeof(strDest) on UNICODE builds.
//--------------------------------------------------------------------------------------
GB_FF_API   HRESULT gb::system::filefunc::FileUtFindFileCchW( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename )
{
	bool bFound;
	WCHAR strSearchFor[MAX_PATH];

	if( NULL==strFilename || strFilename[0] == 0 || NULL==strDestPath || cchDest < 10 )
		return E_INVALIDARG;

	// Get the exe name, and exe path
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileName( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{
		StringCchCopy( strExeName, MAX_PATH, &strLastSlash[1] );

		// Chop the exe name from the exe path
		*strLastSlash = 0;

		// Chop the .exe from the exe name
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	// Typical directories:
	//      .\
	//      ..\
	//      ..\..\
	//      %EXE_DIR%\
	//      %EXE_DIR%\..\
	//      %EXE_DIR%\..\..\
	//      %EXE_DIR%\..\%EXE_NAME%
	//      %EXE_DIR%\..\..\%EXE_NAME%

	// Typical directory search
	bFound = gb::system::filefunc::FileUtFindMediaSearchTypicalDirsW( strDestPath, cchDest, strFilename, strExePath, strExeName );
	if( bFound )
		return S_OK;

	// Typical directory search again, but also look in a subdir called "\media\" 
	StringCchPrintf( strSearchFor, MAX_PATH, L"media\\%s", strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchTypicalDirsW( strDestPath, cchDest, strSearchFor, strExePath, strExeName );
	if( bFound )
		return S_OK;

	WCHAR strLeafName[MAX_PATH] = {0};

	// Search all parent directories starting at .\ and using strFilename as the leaf name
	StringCchCopy( strLeafName, MAX_PATH, strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsW( strDestPath, cchDest, L".", strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at the exe's dir and using strFilename as the leaf name
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsW( strDestPath, cchDest, strExePath, strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at .\ and using "media\strFilename" as the leaf name
	StringCchPrintf( strLeafName, MAX_PATH, L"media\\%s", strFilename ); 
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsW( strDestPath, cchDest, L".", strLeafName );
	if( bFound )
		return S_OK;

	// Search all parent directories starting at the exe's dir and using "media\strFilename" as the leaf name
	bFound = gb::system::filefunc::FileUtFindMediaSearchParentDirsW( strDestPath, cchDest, strExePath, strLeafName );
	if( bFound )
		return S_OK;

	// On failure, return the file as the path but also return an error code
	StringCchCopy( strDestPath, cchDest, strFilename );

	return E_FAIL; //  gb::system::filefunc::FileUtERR_MEDIANOTFOUND;
}


//--------------------------------------------------------------------------------------
// Search a set of typical directories
//--------------------------------------------------------------------------------------
GB_FF_API   bool gb::system::filefunc::FileUtFindMediaSearchTypicalDirsW( WCHAR* strSearchPath, int cchSearch, LPCWSTR strLeaf, 
														   WCHAR* strExePath, WCHAR* strExeName )
{
	// Typical directories:
	//      .\
	//      ..\
	//      ..\..\
	//      %EXE_DIR%\
	//      %EXE_DIR%\..\
	//      %EXE_DIR%\..\..\
	//      %EXE_DIR%\..\%EXE_NAME%
	//      %EXE_DIR%\..\..\%EXE_NAME%
	//      DXSDK media path

	// Search in .\  
	StringCchCopy( strSearchPath, cchSearch, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\  
	StringCchPrintf( strSearchPath, cchSearch, L"..\\%s", strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\..\ 
	StringCchPrintf( strSearchPath, cchSearch, L"..\\..\\%s", strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in ..\..\ 
	StringCchPrintf( strSearchPath, cchSearch, L"..\\..\\%s", strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\ 
	StringCchPrintf( strSearchPath, cchSearch, L"%s\\%s", strExePath, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\..\ 
	StringCchPrintf( strSearchPath, cchSearch, L"%s\\..\\%s", strExePath, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in the %EXE_DIR%\..\..\ 
	StringCchPrintf( strSearchPath, cchSearch, L"%s\\..\\..\\%s", strExePath, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in "%EXE_DIR%\..\%EXE_NAME%\".  This matches the DirectX SDK layout
	StringCchPrintf( strSearchPath, cchSearch, L"%s\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in "%EXE_DIR%\..\..\%EXE_NAME%\".  This matches the DirectX SDK layout
	StringCchPrintf( strSearchPath, cchSearch, L"%s\\..\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
	if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
		return true;

	// Search in media search dir 
	WCHAR* s_strSearchPath =  FileUtMediaSearchPathW();
	if( s_strSearchPath[0] != 0 )
	{
		StringCchPrintf( strSearchPath, cchSearch, L"%s%s", s_strSearchPath, strLeaf ); 
		if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
			return true;
	}

	return false;
}



//--------------------------------------------------------------------------------------
// Search parent directories starting at strStartAt, and appending strLeafName
// at each parent directory.  It stops at the root directory.
//--------------------------------------------------------------------------------------
GB_FF_API  bool gb::system::filefunc::FileUtFindMediaSearchParentDirsW( WCHAR* strSearchPath, int cchSearch, WCHAR* strStartAt, WCHAR* strLeafName )
{
	WCHAR strFullPath[MAX_PATH] = {0};
	WCHAR strFullFileName[MAX_PATH] = {0};
	WCHAR strSearch[MAX_PATH] = {0};
	WCHAR* strFilePart = NULL;

	GetFullPathName( strStartAt, MAX_PATH, strFullPath, &strFilePart );
	if( strFilePart == NULL )
		return false;

	while( strFilePart != NULL && *strFilePart != '\0' )
	{
		StringCchPrintf( strFullFileName, MAX_PATH, L"%s\\%s", strFullPath, strLeafName ); 
		if( GetFileAttributes( strFullFileName ) != 0xFFFFFFFF )
		{
			StringCchCopy( strSearchPath, cchSearch, strFullFileName ); 
			return true;
		}

		StringCchPrintf( strSearch, MAX_PATH, L"%s\\..", strFullPath ); 
		GetFullPathName( strSearch, MAX_PATH, strFullPath, &strFilePart );
	}

	return false;
}

 
typedef std::vector<gb::system::filefunc::FileNameABuffer*> TVector_FileNameABuffer;


/*************************

//==============================================================
//    FileNamesAList
//==============================================================
gb::system::filefunc::FileNamesAList::FileNamesAList() 
{
	TVector_FileNameABuffer* pvector = new	TVector_FileNameABuffer;
	m_vector = (void*)pvector;
};

gb::system::filefunc::FileNamesAList::~FileNamesAList() {	
	Clear(); 

	TVector_FileNameABuffer* pvector = (TVector_FileNameABuffer*)m_vector;
	delete pvector;
	m_vector = NULL;
};

void gb::system::filefunc::FileNamesAList::Clear()
{   
	FileNameABuffer* buff;
	TVector_FileNameABuffer* pvector = (TVector_FileNameABuffer*)m_vector;

	while(pvector->size() > 0) { 
		buff = pvector->back();
		delete[]buff;
		pvector->pop_back();
	}
};

int gb::system::filefunc::FileNamesAList::GetSize() {
	TVector_FileNameABuffer* pvector = (TVector_FileNameABuffer*)m_vector;
	return (int)pvector->size(); 
};

void gb::system::filefunc::FileNamesAList::Add(const CHAR* lpszFileName) { 
	FileNameABuffer* buff = new FileNameABuffer[MAX_PATH];
	TVector_FileNameABuffer* pvector = (TVector_FileNameABuffer*)m_vector;

	ZeroMemory(buff, sizeof(FileNameABuffer));
	strcpy(*buff, lpszFileName);
	pvector->push_back(buff);
};


//   Получить буфер имени файла по индексу 
gb::system::filefunc::FileNameABuffer* gb::system::filefunc::FileNamesAList::GetFile(int indx) {
	TVector_FileNameABuffer* pvector = (TVector_FileNameABuffer*)m_vector;

	FileNameABuffer* pResult = NULL;
	pResult = pvector->at(indx);
	return pResult; 
};

typedef std::vector<gb::system::filefunc::FileNameWBuffer*> TVector_FileNameWBuffer;

//
//    FileNamesWList
//
gb::system::filefunc::FileNamesWList::FileNamesWList() 
{ 
	m_vector = NULL;
	TVector_FileNameWBuffer* pvector = new  TVector_FileNameWBuffer;
	m_vector = (void*)pvector;
};

gb::system::filefunc::FileNamesWList::~FileNamesWList() 
{	
	Clear(); 

	TVector_FileNameWBuffer* pvector = (TVector_FileNameWBuffer*)m_vector;
	delete pvector;
	m_vector = NULL;
};

void gb::system::filefunc::FileNamesWList::Clear()
{     
	FileNameWBuffer* buff;
	TVector_FileNameWBuffer* pvector = (TVector_FileNameWBuffer*)m_vector;

	while(pvector->size() > 0) { 
		buff = pvector->back();
		delete[]buff;
		pvector->pop_back();
	}
};

int gb::system::filefunc::FileNamesWList::GetSize() { 
	TVector_FileNameWBuffer* pvector = (TVector_FileNameWBuffer*)m_vector;
	return (int)pvector->size(); 
};

void gb::system::filefunc::FileNamesWList::Add(const WCHAR* lpszwFileName) { 
	FileNameWBuffer* buff = new FileNameWBuffer[MAX_PATH];
	TVector_FileNameWBuffer* pvector = (TVector_FileNameWBuffer*)m_vector;

	ZeroMemory(buff, sizeof(FileNameABuffer));
	wcscpy(*buff, lpszwFileName);
	pvector->push_back(buff);
};

gb::system::filefunc::FileNameWBuffer* gb::system::filefunc::FileNamesWList::GetFile(int indx) 
{ 
	TVector_FileNameWBuffer* pvector = ( TVector_FileNameWBuffer*)m_vector;
	return pvector->at(indx); 
};

*************************************/



 

//=================================================================
	GB_FF_API BOOL   gb::system::filefunc::searchFilesA(char* lpszFileName, TFUNCFOUNDFILEA  lpSearchFunc, void* pUserData,   BOOL bInnerFolders )
	{
		LPSTR part;
		char tmp[MAX_PATH]; // временный массив
		char name[MAX_PATH];

		HANDLE hSearch = NULL;
		WIN32_FIND_DATAA  afd ;//= new WIN32_FIND_DATAA;
		memset(&afd, 0, sizeof(WIN32_FIND_DATAA));

		// сначало поиск внутри вложенных папках ...
		if(bInnerFolders)
		{
			if(GetFullPathNameA(lpszFileName, 
				MAX_PATH, 
				tmp, 
				&part) == 0) { /*delete afd;*/ return FALSE; };
			strcpy(name, part);
			strcpy(part, "*.*");

			// если папки существуют, то делаем поиск
			afd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			if (!((hSearch = FindFirstFileA(tmp, &afd)) == INVALID_HANDLE_VALUE))
				do
				{
					// в каждой папке есть две папки с именами "." и ".."
					// и эти папки мы не трогаем

					// пропускаем папки "." и ".."
					if (!strncmp(afd.cFileName, ".", 1) || !strncmp(afd.cFileName, "..", 2))            
						continue;

					if (afd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если мы нашли папку
					{
						char next[MAX_PATH];
						if(GetFullPathNameA(lpszFileName, MAX_PATH, next, &part) == 0){ return FALSE; }
						strcpy(part, afd.cFileName);
						strcat(next, "\\");
						strcat(next, name);

						gb::system::filefunc::searchFilesA(next, lpSearchFunc, pUserData, TRUE);
					}
				}
				while (FindNextFileA(hSearch, &afd)); // ищем следующий файл

				FindClose (hSearch); // заканчиваем поиск
		}

		if ((hSearch = FindFirstFileA(lpszFileName, &afd)) == INVALID_HANDLE_VALUE) 
		{   return TRUE; } // в противном случае выходим
		do
		if (!(afd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // если мы нашли файл
		{
			char file[MAX_PATH];
			if(GetFullPathNameA(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
			strcpy(part, afd.cFileName);

			lpSearchFunc(&file[0], pUserData );
		}
		while (FindNextFileA(hSearch, &afd)); // ищем следующий файл
		FindClose (hSearch); // заканчиваем поиск


		return TRUE;
	};

	//==============================================================================================
	GB_FF_API  BOOL gb::system::filefunc::searchDirFilesA(const char* lpszDir, const char* lpszMask, TFUNCFOUNDFILEA  lpSearchFunc, void* pUserData,   BOOL bInnerFolders  )
	{
		char  fname[MAX_PATH];
		memset(&fname[0], 0, sizeof(char) * MAX_PATH);
		strcpy(&fname[0], lpszDir);
		strcat(&fname[0], lpszMask);
		return gb::system::filefunc::searchFilesA(&fname[0], lpSearchFunc, pUserData, bInnerFolders);
	}

	//====================================================================================
	GB_FF_API  BOOL gb::system::filefunc::searchDirFilesW(const WCHAR* lpszwDir, const WCHAR* lpszwMask, TFUNCFOUNDFILEW  lpSearchFunc, void* pUserData, BOOL bInnerFolders  )
	{
		WCHAR  fname[MAX_PATH];
		memset(&fname[0], 0, sizeof(WCHAR) * MAX_PATH);
		wcscpy(&fname[0], lpszwDir);
		wcscat(&fname[0], lpszwMask);
		return searchFilesW(&fname[0], lpSearchFunc, pUserData, bInnerFolders);
	}


	//==============================================================================================
	GB_FF_API BOOL  gb::system::filefunc::searchFilesW(WCHAR* lpszFileName, TFUNCFOUNDFILEW lpSearchFunc,  void* pUserData,  BOOL bInnerFolders)
	{
		LPWSTR part;
		WCHAR tmp[MAX_PATH];  
		WCHAR name[MAX_PATH];

		HANDLE hSearch = NULL;
		WIN32_FIND_DATAW  wfd ; 
		memset(&wfd, 0, sizeof(WIN32_FIND_DATAW));

		// сначало поиск внутри вложенных папках ...
		if(bInnerFolders)
		{
			if(GetFullPathNameW(lpszFileName, 
				MAX_PATH, 
				tmp, 
				&part) == 0) {   return FALSE; };

			wcscpy(name, part);
			wcscpy(part, L"*.*");

			// если папки существуют, то делаем поиск
			wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			if (!((hSearch = FindFirstFileW(tmp, &wfd)) == INVALID_HANDLE_VALUE))
				do
				{
					// в каждой папке есть две папки с именами "." и ".."
					// и эти папки мы не трогаем

					// пропускаем папки "." и ".."
					if (!wcsncmp(wfd.cFileName, L".", 1) || !wcsncmp(wfd.cFileName, L"..", 2))            
						continue;

					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если мы нашли папку
					{
						WCHAR next[MAX_PATH];
						if(GetFullPathNameW(lpszFileName, MAX_PATH, next, &part) == 0){  return FALSE; }
						wcscpy(part, wfd.cFileName);
						wcscat(next, L"\\");
						wcscat(next, name);

						gb::system::filefunc::searchFilesW(next, lpSearchFunc, pUserData,   TRUE);
					}
				}
				while (FindNextFileW(hSearch, &wfd)); // ищем следующий файл

				FindClose (hSearch); // заканчиваем поиск
		}

		if ((hSearch = FindFirstFileW(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE) 
		{   return TRUE; } // в противном случае выходим
		do
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // если мы нашли файл
		{
			WCHAR file[MAX_PATH];
			if(GetFullPathNameW(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
			wcscpy(part, wfd.cFileName);

			lpSearchFunc(&file[0], pUserData );
		}
		while (FindNextFileW(hSearch, &wfd)); // ищем следующий файл
		FindClose (hSearch); // заканчиваем поиск


		return TRUE;
	};

	//======================================================================
	GB_FF_API  void gb::system::filefunc::stringCopyA(CHAR* szDest, const CHAR* szSrc)
	{
		strcpy(szDest, szSrc);
	};

	//======================================================================
	GB_FF_API  void gb::system::filefunc::stringCopyW(WCHAR* szwDest, const WCHAR* szwSrc)
	{
		wcscpy(szwDest, szwSrc);
	};


	//======================================================================
	GB_FF_API  void gb::system::filefunc::stringConcatA(CHAR* szStr, const CHAR* szSrc) 
	{
		strcat(szStr, szSrc);
	};

	//======================================================================
	GB_FF_API  void gb::system::filefunc::stringConcatW(WCHAR* szwStr, const WCHAR* szwSrc) 
	{
		wcscat(szwStr, szwSrc);
	};



	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFilePathA(char* lpBuffer, const char* lpFilePath)
	{
		*lpBuffer = 0;
		for (unsigned i = (unsigned) strlen (lpFilePath)-1; i > 0; i--) {
			if (lpFilePath [i] == '\\') {
				memcpy (lpBuffer, lpFilePath, i+1);
				lpBuffer [i+1] = '\0';
				return true;
			}
		}
		return false;
	}


	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFilePathW(WCHAR* lpBuffer, const WCHAR* lpFilePath)
	{
		for (unsigned i = (unsigned) wcslen ((wchar_t*)lpFilePath)-1; i > 0; i--) 
		{
			if (  *(lpFilePath +i) == L'\\') 
			{
				memcpy (lpBuffer, lpFilePath, (i+1) * sizeof(WCHAR)   );
				lpBuffer [i+1] = '\0';
				return true;
			}
		}
		return false;
	}

	GB_FF_API  bool gb::system::filefunc::filePathDecomposeA(CHAR* szDir, CHAR* szFile, CHAR* szExt, const CHAR* szSrcFilePath)
	{
		if (!gb::system::filefunc::extractFilePathA(szDir, szSrcFilePath) ) return false;
		if (!gb::system::filefunc::extractFileNameA(szFile, szSrcFilePath)  )   return false;
		if (!gb::system::filefunc::extractFileExtentionA(szExt, szFile)  )   return false;


		for (unsigned i = (unsigned) strlen (szFile)-1; i > 0; i--) {
			if (szFile [i] == '.') {
				szFile[i] = 0;
				return true;
			}
			szFile[i] = 0;
		}

		return false;
	}

	GB_FF_API  bool gb::system::filefunc::filePathDecomposeW(WCHAR* szDir, WCHAR* szFile, WCHAR* szExt, const WCHAR* szSrcFilePath)
	{
		if (!gb::system::filefunc::extractFilePathW(szDir, szSrcFilePath) ) return false;
		if (!gb::system::filefunc::extractFileNameW(szFile, szSrcFilePath)  )   return false;
		if (!gb::system::filefunc::extractFileExtentionW(szExt, szFile)  )   return false;


		for (unsigned i = (unsigned) wcslen (szFile)-1; i > 0; i--) {
			if (szFile [i] == L'.') {
				szFile[i] = 0;
				return true;
			}
			szFile[i] = 0;
		}

		return false;
	}

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFileNameA(char* lpBuffer, const char* lpFilePath)
	{
		*lpBuffer = 0;
		for (unsigned i = (unsigned) strlen (lpFilePath)-1; i > 0; i--) {
			if (lpFilePath [i] == '\\') {
				memcpy (&lpBuffer[0], &lpFilePath[i+1], (unsigned) strlen (lpFilePath)-i+1);
				return true;
			}
		}
		return false;
	}

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFileNameW (WCHAR* lpBuffer, const WCHAR* lpFilePath)
	{
		for (unsigned i = (unsigned) wcslen (lpFilePath)-1; i > 0; i--) {
			if (lpFilePath [i] == L'\\') {
				memcpy (&lpBuffer[0], &lpFilePath[i+1], ((unsigned) wcslen(lpFilePath)-i+1) * sizeof(WCHAR) );
				return true;
			}
		}
		return false;
	};

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFileExtentionA (char* lpBuffer, const char* lpFilePath)
	{
		*lpBuffer = 0;
		for (unsigned i = (unsigned) strlen (lpFilePath)-1; i > 0; i--) {
			if (lpFilePath [i] == '.') {
				memcpy (&lpBuffer[0], &lpFilePath[i+1], ((unsigned) strlen (lpFilePath)-i+1) * sizeof(CHAR) );
				return true;
			}
		}
		return false;
	}

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::extractFileExtentionW (WCHAR* lpBuffer, const WCHAR* lpFilePath)
	{
       *lpBuffer = 0;
		for (unsigned i = (unsigned) wcslen (lpFilePath)-1; i > 0; i--) {
			if (lpFilePath [i] == L'.') {
				memcpy (&lpBuffer[0], &lpFilePath[i+1], ((unsigned) wcslen (lpFilePath)-i+1) * sizeof(WCHAR) );
				return true;
			}
		}
		return false;
	}

	//======================================================================
	// !!!  Пересмотреть нужны ли   GB_FF_API  ?????
	// 

	bool gb::system::filefunc::fileExistsA (const LPCSTR fname)   
	{    
		return ::GetFileAttributesA(fname) != DWORD(-1);
	}

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::fileExistsW (const LPCTSTR fname)
	{    
		return ::GetFileAttributesW(fname) != DWORD(-1);
	}

	GB_FF_API bool gb::system::filefunc::zeroFileExtentionA(CHAR* buf)
	{
		for (unsigned i = (unsigned) strlen (buf)-1; i > 0; i--) {
			if (buf [i] == '.') { 
				return true;
			}
			buf [i] = 0;
		}

		return false;
	}

	GB_FF_API bool gb::system::filefunc::zeroFileExtentionW(WCHAR* buf)
	{
		for (unsigned i = (unsigned) wcslen (buf)-1; i > 0; i--) {
			if (buf [i] == L'.') {
				return true;
			}
			buf [i] = 0;
		}

		return false;
	}




	//======================================================================
	GB_FF_API  bool gb::system::filefunc::directoryExistA(const LPSTR dir)
	{
		int rv = GetFileAttributesA(dir);
		if(rv == -1) return false;
#pragma warning(push)
#pragma warning(disable : 4800)
		return (bool)(rv & FILE_ATTRIBUTE_DIRECTORY);
#pragma warning(pop)
	}

	//======================================================================
	GB_FF_API  bool gb::system::filefunc::directoryExistW(const LPWSTR dir)
	{
		int rv = GetFileAttributesW(dir);
		if(rv == -1) return false;
#pragma warning(push)
#pragma warning(disable : 4800)
		return (rv & FILE_ATTRIBUTE_DIRECTORY);
#pragma warning(pop)
	}




	//======================================================================
	GB_FF_API  bool gb::system::filefunc::changeFileExtentionA(CHAR* lpbuff, const CHAR* szFilename, const CHAR* szNewExt)
	{
		int sLen = (int)strlen(szFilename);
		if (sLen == 1) return false;
		// int posPoint = -1;  
		CHAR tempChr;
		for(int c = sLen-1; c >= 0; c--)
		{
			tempChr = *(szFilename + c);
			if ( strncmp(szFilename + c, ".", 1) == 0)
			{
				// posPoint = sLen;
				memcpy(lpbuff, szFilename, sizeof(CHAR) * c );
				*(lpbuff + c  ) = 0;
				strcat(lpbuff, ".");
				strcat(lpbuff, szNewExt);
				*(lpbuff + c + strlen(szNewExt) + 1) = 0;
				return true;
			}

			if ( strncmp(szFilename + c, "\\", 1) == 0) return false;
			if ( strncmp(szFilename + c, ":",  1) == 0) return false;
		}

		return false;
	}

	//============================================================
	GB_FF_API  bool gb::system::filefunc::changeFileExtentionW(WCHAR* lpbuff, const WCHAR* szFilename, const WCHAR* szNewExt)
	{
		int sLen = (int)wcslen(szFilename);
		if (sLen == 1) return false; 
		WCHAR tempChr;
		for(int c = sLen-1; c >= 0; c--)
		{
			tempChr = *(szFilename + c);
			if ( wcsncmp(szFilename + c, L".", 1) == 0)
			{
				memcpy(lpbuff, szFilename, sizeof(WCHAR) * c );
				*(lpbuff + c  ) = 0;
				wcscat(lpbuff, L".");
				wcscat(lpbuff, szNewExt);
				*(lpbuff + c + wcslen(szNewExt) + 1) = 0;
				return true;
			}

			if ( wcsncmp(szFilename + c, L"\\", 1) == 0) return false;
			if ( wcsncmp(szFilename + c, L":",  1) == 0) return false;
		}
		return false;
	}

	//===================================================
	GB_FF_API  bool gb::system::filefunc::compareFileExtentionsA(const CHAR* lpFileName, const CHAR* szExt)
	{
		bool result;
		CHAR ext[32];  
		result = gb::system::filefunc::extractFileExtentionA(&ext[0], lpFileName);
		if (!result) return result;

		int isrcExtLen = (int)strlen(szExt);
		if(isrcExtLen != strlen(&ext[0])) return false;
		if (strncmp(szExt, &ext[0], isrcExtLen) == 0) return true;

		return false;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::compareFileExtentionsW(const WCHAR* lpFileName, const WCHAR* szExt)
	{
		bool result;
		WCHAR ext[32];
		result = gb::system::filefunc::extractFileExtentionW(&ext[0], lpFileName);
		if (!result) return result;

		int isrcExtLen = (int)wcslen(szExt);
		if(isrcExtLen != wcslen(&ext[0])) return false;
		if (wcsncmp(szExt, &ext[0], isrcExtLen) == 0) return true;

		return false;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::pathLevelUpA(CHAR* path)
	{
		int srcLen = (int)strlen(path);
		if (srcLen < 4) return false;

		if (*(path + srcLen - 1) == '\\') *(path + srcLen - 1) = 0;

		for (int c = srcLen; c >=0; c--)
		{
			if ( *(path + c) != '\\')  
			{
				*(path + c) = 0;
			}
			else
			{
				return true;
			}

			if (*(path + c) == ':') {return false; };

		};
		return true;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::pathLevelUpW(WCHAR* path)
	{
		int srcLen = (int)wcslen(path); 
		if (srcLen < 4) return false;

		if (*(path + srcLen - 1) == L'\\') *(path + srcLen - 1) = 0;

		for (int c = srcLen; c >=0; c--)
		{
			if ( *(path + c) != L'\\')  
			{
				*(path + c) = 0;
			}
			else
			{
				return true;
			}

			if (*(path + c) == L':') {return false; };

		};
		return true;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::FileNameMakeA(CHAR* lpszBuff, const CHAR* lpszDir, const CHAR* lpszFname)
	{
		strcpy(lpszBuff, lpszDir);
		strcat(lpszBuff, lpszFname);
		return true;
	}

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::FileNameMakeW(WCHAR* lpszBuff, const WCHAR* lpszDir, const WCHAR* lpszFname)
	{
		wcscpy(lpszBuff, lpszDir);
		wcscat(lpszBuff, lpszFname);
		return true;
	}

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::fileNameMakeExA(CHAR* lpszBuff, const CHAR* lpszDir, const CHAR* lpszFile, const CHAR* lpszExt)
	{
		strcpy(lpszBuff, lpszDir);
		strcat(lpszBuff, lpszFile);
		strcat(lpszBuff, ".");
		strcat(lpszBuff, lpszExt );
		return true;
	}

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::fileNameMakeExW(WCHAR* lpszBuff, const WCHAR* lpszDir, const WCHAR* lpszFile, const WCHAR* lpszExt)
	{
		wcscpy(lpszBuff, lpszDir);
		wcscat(lpszBuff, lpszFile);
		wcscat(lpszBuff, L".");
		wcscat(lpszBuff, lpszExt );
		return true;
	}

	//=========================================================================
	GB_FF_API bool gb::system::filefunc::convertFilenameToFilePathA(CHAR* szFilename)
	{
		int slen = (int)strlen(szFilename);
		if(slen <= 3) return false;
		for(int c = slen; c >=0; c--)
		{
			if ( strncmp(szFilename + c, ":",  1) == 0) return false;
			if ( *(szFilename + c) == '\\' ) return true;
			*(szFilename + c) = 0; 
		}

		return false;
	};

	//=========================================================================
	GB_FF_API bool gb::system::filefunc::convertFilenameToFilePathW(WCHAR* szwFilename)
	{
		int slen = (int)wcslen(szwFilename);
		if(slen <= 3) return false;
		for(int c = slen; c >=0; c--)
		{
			if ( wcsncmp(szwFilename + c, L":",  1) == 0) return false;
			if ( *(szwFilename + c) == L'\\' ) return true;
			*(szwFilename + c) = 0; 
		}

		return false;
	};


	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::changeFileExtentionA(CHAR* szFilename, const CHAR* szNewExt)
	{
		int sLen = (int)strlen(szFilename); if (sLen <= 2) return false; 
		//CHAR tempChr;
		for(int c = sLen-1; c >= 0; c--) {

			if ( strncmp(szFilename + c, "\\", 1) == 0) return false;
			if ( strncmp(szFilename + c, ":",  1) == 0) return false;
			if ( strncmp(szFilename + c, ".", 1) == 0) { // найдено разделитель расширения
				strcat(szFilename, szNewExt);
				return true;
			}
			else { *(szFilename + c)=0;  };
		};

		return false;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::changeFileExtentionW(WCHAR* szwFilename, const WCHAR* szwNewExt)
	{
		int sLen = (int)wcslen(szwFilename); if (sLen <= 2) return false; 
		//	WCHAR tempChr;
		for(int c = sLen-1; c >= 0; c--) {

			if ( wcsncmp(szwFilename + c, L"\\", 1) == 0) return false;
			if ( wcsncmp(szwFilename + c, L":",  1) == 0) return false;
			if ( wcsncmp(szwFilename + c, L".", 1) == 0) { // найдено разделитель расширения
				wcscat(szwFilename, szwNewExt);
				return true;
			}
			else { *(szwFilename + c)=0;  };
		};

		return false;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getApplFilenameA(char* lpBuff)
	{
		memset(lpBuff, 0, sizeof(char) * MAX_PATH);
		DWORD ret = GetModuleFileNameA(0, lpBuff, MAX_PATH );
		if(0 == ret) return false;
		return true;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getApplFilenameW(WCHAR* lpwBuff)
	{
		memset(lpwBuff, 0, sizeof(WCHAR) * MAX_PATH);
		DWORD ret = GetModuleFileNameW(0, lpwBuff, MAX_PATH );
		if(0 == ret) return false;
		return true;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getApplPathA(CHAR* lpBuff)
	{
		if (!gb::system::filefunc::getApplFilenameA(lpBuff)) return false;

		int slen = (int)strlen(lpBuff);
		for(int c = slen; c >=0; c--)
		{
			if ( *(lpBuff + c) == '\\' ) return true;
			*(lpBuff + c) = 0; 
		}

		return false;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getApplPathW(WCHAR* lpwBuff)
	{
		if (!gb::system::filefunc::getApplFilenameW(lpwBuff)) return false;

		int slen = (int)wcslen(lpwBuff);
		for(int c = slen; c >=0; c--)
		{
			if ( *(lpwBuff + c) == L'\\' ) return true;
			*(lpwBuff + c) = 0; 
		}

		return false;
	};

	//=========================================================================
	GB_FF_API  void gb::system::filefunc::DirectoryConcatToA(CHAR* szDir, const CHAR* szSubDir)
	{
		strcat(szDir, szSubDir);
	};

	//=========================================================================
	GB_FF_API  void gb::system::filefunc::DirectoryConcatToW(WCHAR* szwDir, const WCHAR* szwSubDir)
	{
		wcscat(szwDir, szwSubDir);
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getModuleDirA(CHAR* szModuleDir, const HMODULE hm) {
		if(!GetModuleFileNameA(hm, szModuleDir, MAX_PATH) ) return false;
		return gb::system::filefunc::convertFilenameToFilePathA(szModuleDir);

	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::getModuleDirW(WCHAR* szwModuleDir, const HMODULE hm) {
		if(!GetModuleFileNameW(hm, szwModuleDir, MAX_PATH) ) return false;
		return gb::system::filefunc::convertFilenameToFilePathW(szwModuleDir);

	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::makeSubDirWhereModuleA(CHAR* szDirBuff , const HMODULE hm, const CHAR* szSubDir){
		if(!gb::system::filefunc::getModuleDirA(szDirBuff, hm)) return false;
		gb::system::filefunc::DirectoryConcatToA(szDirBuff, szSubDir);
		return true;
	};

	GB_FF_API bool gb::system::filefunc::makeSubDirWhereModuleW(WCHAR* szDirBuff , const HMODULE hm, const WCHAR* szSubDir) 
	{
		if(!gb::system::filefunc::getModuleDirW(szDirBuff, hm)) return false;
		gb::system::filefunc::DirectoryConcatToW(szDirBuff, szSubDir);
		return true;
	}



	//=========================================================================
	// TODO :   MakeSubDirWhereModuleW


	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::CreateDirectoryA(const CHAR* szDirName )
	{
		BOOL res = ::CreateDirectoryA(szDirName, NULL);
		if(!res) {
			DWORD dwErr =	GetLastError();
			return false; } else return true;
	};

	//=========================================================================
	GB_FF_API  bool gb::system::filefunc::CreateDirectoryW(const WCHAR* szDirName )
	{
		BOOL res = ::CreateDirectoryW(szDirName, NULL);
		if(!res) {
			DWORD dwErr =	GetLastError();
			return false; } else return true;
	};

	GB_FF_API bool gb::system::filefunc::saveCstrToFileA(const char* fname, const char* srcData, int numBytes)
	{
		FILE* f = fopen(fname, "w+b");
		if (!f) return false;
		if ( fwrite(srcData, 1, numBytes, f) != numBytes ) {

			fclose(f);
			return false;
		}; 



		fflush(f);
		fclose(f);
		return true;
	}


	GB_FF_API bool gb::system::filefunc::saveBinDataToFileA(const char* fname, const void* pdata, unsigned int numBytes)
	{
		FILE* f = fopen(fname, "w+b");
		if (!f) return false;
		if ( fwrite(pdata, 1, numBytes, f) != numBytes ) {

			fclose(f);
			return false;
		}; 

		fflush(f);
		fclose(f);
		return true;
	}


    //=================================================
	//======================  2  ======================
	//=================================================


 //======================================================
GB_FF_API  bool gb::system::filefunc::directoryExistCstrA(const char* szDir)
{
	int rv = GetFileAttributesA( (LPCSTR)szDir);
	if(rv == -1) return false;
	if(rv & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
}

 //======================================================
GB_FF_API  bool gb::system::filefunc::directoryExistCstrW(const wchar_t* wszDir)
{
	int rv = GetFileAttributesW( (LPCWSTR)wszDir);
	if(rv == -1) return false;
	if(rv & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
}

 //======================================================
GB_FF_API bool gb::system::filefunc::isFullPathA(const char* fname) {
	const size_t slen = strlen(fname);
	if(  slen < 3 )
		return false;

	if( *(fname + 1) == ':' )
		return true;

	return false;
};

 //======================================================
GB_FF_API bool gb::system::filefunc::isFullPathW(const wchar_t* fname) {
	const size_t slen = wcslen(fname);
	if(slen < 3)
		return false;

	if( *(fname + 1) == L':' )
		return true;

	return false;
};



//====================================================
//=======================  3  ========================
//====================================================



//======================================================
GB_FF_API  bool gb::system::filefunc::compareFileExtentions2A( const char*  filename, const char* ext, bool bCaseSence )
{
	const size_t FNLEN = strlen(filename);
	const size_t EXTLEN = strlen(ext);

	if(FNLEN == 0)
		return false;

	if(EXTLEN == 0)
		return false;

	// extract extent
	std::string sext;
	sext = "";
	{

		for(size_t c = FNLEN-1; c>=0; c--)
		{
			char smb =	 *(filename + c);
			if( smb =='.' )
		 {
			 break;
		 }

			sext = smb + sext;
		}


	} // for

	static std::string sSrcExt;
	sSrcExt = ext;

	if(!bCaseSence) {
		// set lowercase
		{
			boost::to_lower(sSrcExt);
			boost::to_lower(sext);
		}

	} // if

	if( sSrcExt == sext    )
	{
		return true;
	}


	return false;
}

//===========================================================
GB_FF_API bool gb::system::filefunc::compareFileExtentions2W( const wchar_t*  filename, const wchar_t* ext, bool bCaseSence )
{
	const size_t FNLEN =  wcslen(filename);
	const size_t EXTLEN = wcslen(ext);

	if(FNLEN == 0)
		return false;

	if(EXTLEN == 0)
		return false;

	// extract extent
	std::wstring sext;
	sext = L"";
	{

		for(size_t c = FNLEN-1; c>=0; c--)
		{
			wchar_t smb =	 *(filename + c);
			if( smb == L'.' )
		 {
			 break;
		 }

			sext = smb + sext;
		}


	} // for

	static std::wstring sSrcExt;
	sSrcExt = ext;

	if(!bCaseSence) {
		// set lowercase
		{
			boost::to_lower(sSrcExt);
			boost::to_lower(sext);
		}

	} // if

	if( sSrcExt == sext    )
	{
		return true;
	}


	return false;
}


//----------------------------------------------------------------
class ___FUNCFOUNDFILEA_PARAM {
public:
	___FUNCFOUNDFILEA_PARAM(     const std::vector<std::string>& _vExt , gb::system::filefunc::VEC_PathDataA& _vdest ) 
		:  _v(_vdest) ,   _vExtentions(_vExt)  
	{  

	};

	gb::system::filefunc::VEC_PathDataA& _v;
	const std::vector<std::string>& _vExtentions;
};

//===================================================================
static void ___FUNCFOUNDFILEA(const CHAR *lpszFileName, void *pUserData) {
	___FUNCFOUNDFILEA_PARAM* param = (___FUNCFOUNDFILEA_PARAM*)pUserData;

	gb::system::filefunc::PathDataA pd;
	if(param->_vExtentions.empty() )
	{
		pd =	lpszFileName;
		param->_v.push_back(pd);
		return;
	}
	else
	{

		for(size_t c=0; c<param->_vExtentions.size(); c++)
		{
			// CHAR ext[32];
			const bool bCompFExt =  gb::system::filefunc::compareFileExtentions2A( lpszFileName, param->_vExtentions[c].c_str()  )  ;
			if( bCompFExt )
		 {
			 pd =	lpszFileName;
			 param->_v.push_back(pd);

			};

		}

	}


};



//----------------------------------------------------------------
class ___FUNCFOUNDFILEW_PARAM {
public:
	___FUNCFOUNDFILEW_PARAM(     const std::vector<std::wstring>& _vExt , gb::system::filefunc::VEC_PathDataW& _vdest ) 
		:  _v(_vdest) ,   _vExtentions(_vExt)  
	{  

	};

	gb::system::filefunc::VEC_PathDataW& _v;
	const std::vector<std::wstring>& _vExtentions;
};

//===================================================================
static void ___FUNCFOUNDFILEW(const WCHAR *lpszFileName, void *pUserData) {
	___FUNCFOUNDFILEW_PARAM* param = (___FUNCFOUNDFILEW_PARAM*)pUserData;

	gb::system::filefunc::PathDataW pd;
	if(param->_vExtentions.empty() )
	{
		pd =	lpszFileName;
		param->_v.push_back(pd);
		return;
	}
	else
	{

		for(size_t c=0; c<param->_vExtentions.size(); c++)
		{
			// CHAR ext[32];
			const bool bCompFExt =  gb::system::filefunc::compareFileExtentions2W( lpszFileName, param->_vExtentions[c].c_str()  )  ;
			if( bCompFExt )
		 {
			 pd =	lpszFileName;
			 param->_v.push_back(pd);

			};

		}

	}


};



//===================================================================
static HRESULT __FindFiles_UnsafeA(const char* szDir,  const bool bIncludeSubDirs, const std::vector<std::string>& _vExtentions, _out gb::system::filefunc::VEC_PathDataA& _v) {
	HRESULT hr =0;

	_v.clear();

	if( !gb::system::filefunc::directoryExistCstrA( szDir ) )
	{
		return E_FAIL;
	}

	static std::string sSearch;
	sSearch = szDir;

	sSearch +=  "*.*";


	BOOL bInerFld = FALSE;
	if(bIncludeSubDirs)
	{
		bInerFld = TRUE;
	}
	else
	{
		bInerFld = FALSE;
	}

	___FUNCFOUNDFILEA_PARAM _param ( _vExtentions ,  _v  );
	_param._v = _v;

	if(sSearch.length() > (size_t)MAX_PATH )
	{
		return E_FAIL;
	}

	static char ss_search[MAX_PATH+1];
	strncpy(ss_search, sSearch.c_str(), MAX_PATH );

	const BOOL bsearchres =


		gb::system::filefunc::searchFilesA (
		ss_search , ___FUNCFOUNDFILEA, (void*)&_param, bInerFld );



	if( _v.empty() )
	{
		return S_FALSE;
	}

	return 0;
};



//===================================================================
static HRESULT __FindFiles_UnsafeW(const wchar_t* wszDir,  const bool bIncludeSubDirs, const std::vector<std::wstring>& _vExtentions, _out gb::system::filefunc::VEC_PathDataW& _v) {
	HRESULT hr =0;

	_v.clear();

	if( !gb::system::filefunc::directoryExistCstrW( wszDir ) )
	{
		return E_FAIL;
	}

	static std::wstring sSearch;
	sSearch = wszDir;

	sSearch +=  L"*.*";


	BOOL bInerFld = FALSE;
	if(bIncludeSubDirs)
	{
		bInerFld = TRUE;
	}
	else
	{
		bInerFld = FALSE;
	}

	___FUNCFOUNDFILEW_PARAM _param ( _vExtentions ,  _v  );
	_param._v = _v;

	if(sSearch.length() > (size_t)MAX_PATH )
	{
		return E_FAIL;
	}

	static wchar_t ss_search[MAX_PATH+1];
	wcsncpy (ss_search, sSearch.c_str(), MAX_PATH );

	const BOOL bsearchres =  
		gb::system::filefunc::searchFilesW (
		ss_search , 
		___FUNCFOUNDFILEW, 
		(void*)&_param, 
		bInerFld 
		);


	if( _v.empty() )
	{
		return S_FALSE;
	}

	return 0;
};

//=======================================================================
GB_FF_API HRESULT gb::system::filefunc::findFilesA(const char* szDir,  const bool bIncludeSubDirs, const std::string& sExtentionsLine, _out gb::system::filefunc::VEC_PathDataA& _v) 
{
	HRESULT hr =0;

	std::vector<std::string> v_ext;

	typedef boost::tokenizer<boost::char_separator<char> >	tokenizer;
	boost::char_separator<char> sep(",");
	tokenizer tokens(sExtentionsLine, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();	tok_iter != tokens.end(); ++tok_iter)
	{
		// std::cout << "<" << *tok_iter << "> ";
		v_ext.push_back( *tok_iter  );
	}

	hr =  findFilesA( szDir,  bIncludeSubDirs, v_ext,  _v) ;


	return hr  ;
};

//========================================

 std::wstring StringToWString(const std::string& s);

static std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp; 
}

//=======================================================================
GB_FF_API HRESULT gb::system::filefunc::findFilesW(const wchar_t* wszDir,  const bool bIncludeSubDirs, const std::wstring& sExtentionsLine, _out gb::system::filefunc::VEC_PathDataW& _v) 
{
	HRESULT hr =0;

	std::vector<std::wstring> v_ext;
   /*
	typedef boost::tokenizer<boost::char_separator<wchar_t> >	tokenizer;
	boost::char_separator<wchar_t> sep(  L","  );
	tokenizer tokens(sExtentionsLine, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();	tok_iter != tokens.end(); ++tok_iter)
	{
		// std::cout << "<" << *tok_iter << "> ";
		std::string stemp = *tok_iter;
		 std::wstring wstemp ; // = StringToWString ( stemp ); 
		v_ext.push_back( wstemp  );
	}
	*/
	std::wstring wstemp ;
	  wstemp = L"";
   for(size_t c = 0; c<sExtentionsLine.length(); c++)
   {
	  if( sExtentionsLine[c] == L','  )
	  {
		 v_ext.push_back( wstemp  );
		 wstemp = L"";
	  }
	  else
	  {
		  wstemp += sExtentionsLine[c];
	  }
   }

   // last
   if(wstemp.length() )
   {
	 v_ext.push_back( wstemp  );
   }


	hr =  findFilesW( wszDir,  bIncludeSubDirs, v_ext,  _v) ;


	return hr  ;
};




//======================================================================
GB_FF_API HRESULT  gb::system::filefunc::findFilesA(const char* szDir,  const bool bIncludeSubDirs, const std::vector<std::string>& _vExtentions, _out gb::system::filefunc::VEC_PathDataA& _v) 
{	
	HRESULT hr =0;
	__try 
	{
		hr = __FindFiles_UnsafeA( szDir,  bIncludeSubDirs,   _vExtentions,   _v);
	}	 __except(1) {
		hr |= E_FAIL;
	 
	}

	return hr;
}

//================================================================
GB_FF_API HRESULT  gb::system::filefunc::findFilesW(const wchar_t* wszDir,  const bool bIncludeSubDirs, const std::vector<std::wstring>& _vExtentions, _out gb::system::filefunc::VEC_PathDataW& _v) {

	HRESULT hr =0;
	__try 
	{
		hr = __FindFiles_UnsafeW( wszDir,  bIncludeSubDirs,   _vExtentions,   _v);
	}	 __except(1) {
		hr |= E_FAIL;
		 
	}
	return hr;
};



//====================================================
//========================  4  =======================
//====================================================


//===============================================================
GB_FF_API std::string gb::system::filefunc::getModuleFullPath_s_A(const HMODULE hm) {
	
	CHAR path[MAX_PATH];
	  path[0]  = 0;
	DWORD dwres = ::GetModuleFileNameA( hm, path, MAX_PATH );

	std::string res;
	if(dwres)
	{
	  res = path;
	}
	else
	{

	}
	
	 return res;	
};

//===============================================================
GB_FF_API std::wstring gb::system::filefunc::getModuleFullPath_s_W(const HMODULE hm) {

	WCHAR path[MAX_PATH];
	path[0]  = 0;
	DWORD dwres = ::GetModuleFileNameW( hm, path, MAX_PATH );

	std::wstring res;
	if(dwres)
	{
		res = path;
	}
	else
	{

	}
 
	return res;	
};



//===============================================================
GB_FF_API std::string gb::system::filefunc::getExeFullPaths_A() {
	  std::string res;
	 CHAR path[MAX_PATH];
	  path[0]  = 0;

	DWORD dwres = ::GetModuleFileNameA(  0, path, MAX_PATH );
	if(!dwres) return res; // error

   int nSpashPos = -1;
   const int NPATH_LEN = (int)strlen(path);
   for(int c=NPATH_LEN-1; c>=0; c--) {
	   if( path[c] == '\\' ) {
		   nSpashPos = c;
		   break;
		   };	   
   };

	path[nSpashPos+1] = 0;


    res = path;
	 return res;
	
};

//=================================================
GB_FF_API std::wstring gb::system::filefunc::getExeFullPaths_W() {
	std::wstring res;
	WCHAR path[MAX_PATH];
	path[0]  = 0;

	DWORD dwres = ::GetModuleFileNameW(  0, path, MAX_PATH );
	if(!dwres) return res; // error

	int nSpashPos = -1;
	const int NPATH_LEN = (int)wcslen(path);
	for(int c=NPATH_LEN-1; c>=0; c--) {
		if( path[c] == L'\\' ) {
			nSpashPos = c;
			break;
		};	   
	};

	path[nSpashPos+1] = 0;


	  res = path;
	return res;

};




 
//=================================================
GB_FF_API    const char* gb::system::filefunc::getApplPathc_A() {

	return gb::system::filefunc::getModulePathc_A(NULL);
};

//=================================================
GB_FF_API    const wchar_t* gb::system::filefunc::getApplPathc_W() {

	return gb::system::filefunc::getModulePathc_W(NULL);
};


//==============================================
GB_FF_API    const char* gb::system::filefunc::getModulePathc_A(const HMODULE hm) {
	static char path[MAX_PATH];
	path[0]	 = 0;
	::GetModuleFileNameA(hm, path, MAX_PATH);
  return path;
};

//============================================
GB_FF_API    const wchar_t* gb::system::filefunc::getModulePathc_W(const HMODULE hm) {
	static wchar_t path[MAX_PATH];
	path[0]	 = 0;
	::GetModuleFileNameW(hm, path, MAX_PATH);
	return path;
}; 

//============================================
GB_FF_API    const char*     gb::system::filefunc::getApplDirectoryCstr_A() {
   static char buf[MAX_PATH];
   buf[0] = 0;
	DWORD dwres =  ::GetModuleFileNameA( NULL, buf, MAX_PATH);
	if(!dwres)
		   return buf;

	const int BUFLEN = (int)strlen(buf);
	  if(BUFLEN == 0)
		   return buf;

	  for(int c=BUFLEN-1; c>=0; c--) {
	     if( buf[c] == '\\' )	
			 {
			 // buf[c] = 0 ;
			  return buf;
			 }

		 buf[c] = 0 ;
		  
	  };
 


   return buf;
};

//============================================
GB_FF_API    const wchar_t*  gb::system::filefunc::getApplDirectoryCstr_W() {
   static wchar_t buf[MAX_PATH];
   buf[0] = 0;
	 DWORD dwres = ::GetModuleFileNameW( NULL, buf, MAX_PATH);
   if(!dwres)
	    return buf;


	const int BUFLEN = (int)wcslen(buf);
	  if(BUFLEN == 0)
		   return buf;

	  for(int c=BUFLEN-1; c>=0; c--) {
	     if( buf[c] == L'\\' )	
			 {
			 // buf[c] = 0 ;
			  return buf;
			 }

		 buf[c] = 0 ;
		  
	  };
 


  
   return buf;
};


//============================================
GB_FF_API bool gb::system::filefunc::setCurrDirA( _in_opt CHAR* dir) {
	BOOL  res;
	if(dir)
	{
		res = SetCurrentDirectoryA(  dir );
	}
	else
	{
		res = SetCurrentDirectoryA( gb::system::filefunc::getApplDirectoryCstr_A() );
	};



	if(!res )
		return false;

	return true;
};

//============================================
GB_FF_API bool gb::system::filefunc::setCurrDirW( _in_opt WCHAR* dir) {
	BOOL  res;
	if(dir)
	{
		res = SetCurrentDirectoryW( dir );
	}
	else
	{
		res = SetCurrentDirectoryW(  gb::system::filefunc::getApplDirectoryCstr_W()  );
	};





	if(!res )
		return false;

	return true;
};


//=======================================================================
GB_FF_API bool gb::system::filefunc::getFullPathA(char* buf, const int nbuflen,  const char* src, bool bCheckFileExists) {
		//char buffer[MAX_PATH];
	  memset(buf,  0, sizeof(char) * nbuflen);
 
	DWORD  dwres =  GetFullPathNameA(
		src,  //__in   LPCTSTR lpFileName,
		nbuflen, //__in   DWORD nBufferLength,
		buf, //__out  LPTSTR lpBuffer,
		NULL  //__out  LPTSTR *lpFilePart
		);

	if(dwres == 0)
		  return false;

	if(bCheckFileExists) {
		if( !gb::system::filefunc::fileExistsA(buf) ) {
			return false;
		};

	};

  return true;
};


//=======================================================================
GB_FF_API bool gb::system::filefunc::getFullPathW(wchar_t* buf, const int nbuflen,  const wchar_t* src, bool bCheckFileExists) {
	//char buffer[MAX_PATH];
	memset(buf,  0, sizeof(wchar_t) * nbuflen);
 
	DWORD  dwres =  GetFullPathNameW(
		src,  //__in   LPCTSTR lpFileName,
		nbuflen, //__in   DWORD nBufferLength,
		buf, //__out  LPTSTR lpBuffer,
		NULL  //__out  LPTSTR *lpFilePart
		);

	if(dwres == 0)
		return false;

	if(bCheckFileExists) {
		if( !gb::system::filefunc::fileExistsW(buf) ) {
			return false;
		};

	};

	return true;
};


//===============================================================
GB_FF_API  bool gb::system::filefunc::getCurrDirA(char* buf, const int nbuflen) {
	DWORD dwres =  GetCurrentDirectoryA (
  (DWORD) nbuflen,
    buf // LPTSTR lpBuffer
);
	
  if(dwres == 0)
	    return false;

  // check last slash
  const int SRCLEN = (int)strlen(buf);
  if(  buf[SRCLEN-1] != '\\' )
	  {
	   buf[SRCLEN] = '\\';
	   buf[SRCLEN + 1] = 0;
	  };



  return true;
};

//===============================================================
GB_FF_API  bool gb::system::filefunc::getCurrDirW(wchar_t* buf, const int nbuflen) {
	DWORD dwres =  GetCurrentDirectoryW (
  (DWORD) nbuflen,
    buf // LPTSTR lpBuffer
);
	
  if(dwres == 0)
	    return false;

    // check last slash
  const int SRCLEN = (int)wcslen(buf);
  if(  buf[SRCLEN-1] != L'\\' )
	  {
	   buf[SRCLEN] = L'\\';
	   buf[SRCLEN + 1] = 0;
	  };

  return true;
};

//===============================================================
GB_FF_API  const char* gb::system::filefunc::getCurrDirCstr_A() {
    static char buf[MAX_PATH];
	buf[0] = 0;
	if(!getCurrDirA(buf, MAX_PATH) ) {
	 // error	
	};

	return buf;
};

//===============================================================
GB_FF_API  const wchar_t* gb::system::filefunc::getCurrDirCstr_W() {
    static wchar_t buf[MAX_PATH];
	buf[0] = 0;
	if(!getCurrDirW(buf, MAX_PATH) ) {
	 // error	
	};

	return buf;
};

//===========================================================
GB_FF_API const char* gb::system::filefunc::getShortPathCstr_A(const char* src) {
	static char buf[MAX_PATH];
	 buf[0] = 0;

    DWORD dwres =  GetShortPathNameA(
  src, //  LPCTSTR lpszLongPath,
 buf,  // LPTSTR lpszShortPath,
   MAX_PATH // DWORD cchBuffer
);

	if(!dwres )
		 return  buf; // error

	 return buf;
};
  
//===========================================================
GB_FF_API const wchar_t* gb::system::filefunc::getShortPathCstr_W(const wchar_t* src) {
	static wchar_t buf[MAX_PATH];
	 buf[0] = 0;

    DWORD dwres =  GetShortPathNameW(
  src , //  LPCTSTR lpszLongPath,
 buf,  // LPTSTR lpszShortPath,
   MAX_PATH // DWORD cchBuffer
);

	if(!dwres )
		 return  buf; // error

	 return buf;
};





//=====================================================
//====================== 5  ===========================
//=====================================================


//============================================================
class _GetCurExeStartDir {
public:
   CHAR  bufcurder_a[MAX_PATH];
   WCHAR bufcurder_w[MAX_PATH];

	_GetCurExeStartDir() {
		strcpy(bufcurder_a,  gb::system::filefunc::getCurrDirCstr_A()  );
		wcscpy( bufcurder_w,  gb::system::filefunc::getCurrDirCstr_W()  );
	};
 
};
// end class

static _GetCurExeStartDir  g_exestartdir;


//=====================================================
GB_FF_API CHAR*  gb::system::filefunc::getExeStartCurrDir_A() {

	return g_exestartdir.bufcurder_a;

};

//=====================================================
GB_FF_API WCHAR* gb::system::filefunc::getExeStartCurrDir_W() {

  return g_exestartdir.bufcurder_w;

};

//=====================================================
 
GB_FF_API 
gb::system::filefunc::SearchparhApendA::SearchparhApendA(
						   const char* path0, 
						   const char* path1 ,
						   const char* path2 ,	   
						   const char* path3 ,	   
						   const char* path4 ,	   
						   const char* path5 ,
						   const char* path6 ,	
						   const char* path7 

						   ) {
							   PathDataA path = path0; FileUtApendGlobalSearchPathA(&path);

							   if(path1) { path = path1; FileUtApendGlobalSearchPathA(&path); };
							   if(path2) { path = path2; FileUtApendGlobalSearchPathA(&path); };	
							   if(path3) { path = path3; FileUtApendGlobalSearchPathA(&path); };	
							   if(path4) { path = path4; FileUtApendGlobalSearchPathA(&path); };	
							   if(path5) { path = path5; FileUtApendGlobalSearchPathA(&path); };	
							   if(path6) { path = path6; FileUtApendGlobalSearchPathA(&path); };	
							   if(path7) { path = path7; FileUtApendGlobalSearchPathA(&path); };	

};




//=========================================================================
 

#pragma warning(pop)

#endif 
// end file