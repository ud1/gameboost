#ifdef WIN32 // only windows

#include <gb/system/filefunc.h>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>


#pragma warning(push)

//=========================================================================


namespace gb {
	namespace system {
		namespace filefunc {

// \brief  std вектор для PathDataA  
typedef std::vector<PathDataA> VEC_PathDataA;

// \brief  std вектор для PathDataW  
typedef std::vector<PathDataW> VEC_PathDataW; 	

		}
	}
}

//===========  времянки.. дял совместимости (убрать) =================

#define MONPRINT(msg)



 

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
	return (bool)(rv & FILE_ATTRIBUTE_DIRECTORY);
}

 //======================================================
GB_FF_API  bool gb::system::filefunc::directoryExistCstrW(const wchar_t* wszDir)
{
	int rv = GetFileAttributesW( (LPCWSTR)wszDir);
	if(rv == -1) return false;
	return (bool)(rv & FILE_ATTRIBUTE_DIRECTORY);
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
		MONPRINT("Exception \n");
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
		MONPRINT("Exception \n");
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