/** \file  filefunc.h
* \brief  функции связанные с файлами. Пока только для WINDOWS 
*
*
*
*
*  \author  ksacvet777

 

 \todo  для всех возможных убрать засисимость от windows. Что можно сделать под другие платформы.
 \todo  убрать лишние, кот. можно аменить на сишные.
 \tofo  возможно убрать PathDataA/W

 \todo удалить FileNameMakeA/W
 \todo удалить DirectoryConcatToA/W
*
*
*/

#ifdef  WIN32   // пока только для windows

#pragma once
#define __GB_SYS_FILEFUNC_H__

#include <gb/Config.h>

#include <windows.h>
#include <string.h>
#include <string>
#include <vector>

namespace gb
{

 namespace system
 {
  
  //! \brief  Функции для выполнения операций с файлами, директориями, строками именами файлов 
  namespace filefunc
  {

  //-----------------------------------------------------------------------
  

	  //! \brief  Спецификатор экспорта для файловых функций.  Пока пустышка
#define GB_FF_API 

  // убрать !!  маркер параметра
#define _in_opt

// убрать !!  маркер параметра
#define _out




	  /**  \brief тип для обратного вызова для функции  SearchFilesA, который будет вызываться если найден
	  новый файл  */
	  typedef void  (__cdecl  *TFUNCFOUNDFILEA)(
		  const CHAR* lpszFileName, 
		  void* pUserData );

	  /**  \brief Выполняет поиск файлов по пути и маске. В  lpszFileName должен быть полный путь и маска.
	  например "C:\dir\*.txt" .
	  lpSearchFunc - функция которая будет вызвана если найден файл. 
	  pUserData - параметр функции выше.
	  bInnerFolders - присвойть  true если необходим поиск в подпапках  */
	  GB_FF_API BOOL   searchFilesA(char* lpszFileName, TFUNCFOUNDFILEA  lpSearchFunc, void* pUserData,   BOOL bInnerFolders = TRUE);

	  /**  \brief тип для задания обратного вызова для в функции SearchFilesW */
	  typedef void  (__cdecl  *TFUNCFOUNDFILEW)(const WCHAR* lpszFileName,  void* pUserData );

	  /**  \brief Аналог функции SearchFilesA  . Версия для UNICODE  */
	  GB_FF_API BOOL   searchFilesW(WCHAR* lpszFileName, TFUNCFOUNDFILEW lpSearchFunc,  void* pUserData,  BOOL bInnerFolders = TRUE);

	  /**   \brief Выполняет поиск файлов по указаным: директории (lpszDir) и маске (lpszMask).
	  lpSearchFunc - функция, которая будет вызываться при нахождении файла,
	  pUserData - пользовательский указатель. Можно передать NULL */
	  GB_FF_API  BOOL searchDirFilesA(const char* lpszDir, const char* lpszMask, TFUNCFOUNDFILEA  lpSearchFunc, void* pUserData,   BOOL bInnerFolders = TRUE);


	  /**  \brief То же , что и SearchDirFilesA, но для UNICODE   */
	  GB_FF_API  BOOL searchDirFilesW(const WCHAR* lpszwDir, const WCHAR* lpszwMask, TFUNCFOUNDFILEW  lpSearchFunc, void* pUserData, BOOL bInnerFolders = TRUE);


	  /**  \brief Простое копирование CHAR-строки из  szSrc в szDest */
	  GB_FF_API  void stringCopyA(CHAR* szDest, const CHAR* szSrc);

	  /**  \brief Простое копирование WCHAR-строки из  szwSrc в szwDest */
	  GB_FF_API  void stringCopyW(WCHAR* szwDest, const WCHAR* szwSrc);

	  /**  \brief Присоединить строку  szSrc к szStr*/
	  GB_FF_API  void stringConcatA(CHAR* szStr, const CHAR* szSrc) ;

	  /**  \brief Присоединить строку  szwSrc к szwStr*/
	  GB_FF_API  void stringConcatW(WCHAR* szwStr, const WCHAR* szwSrc) ;



	  /**   \brief Извлечение пути к файлу  в lpBuffer   по указаному полному файлу lpFilePath.
	  Версия для ANSI  */
	  GB_FF_API  bool extractFilePathA(char* lpBuffer, const char* lpFilePath);

	  /**   \brief Извлечение пути к файлу  в lpBuffer   по указаному полному файлу lpFilePath.
	  Версия для UNICODE  */
	  GB_FF_API  bool extractFilePathW(WCHAR* lpBuffer, const WCHAR* lpFilePath);

	  /**  \brief Декомпозиция (извлечения) частей файлового имени из полного пути. <BR>
	  Например: передано "с:\sdsd\vcvcvcv\text.h"  <BR>	 Результат будет: <BR>
	  szDir = "с:\sdsd\vcvcvcv\"   <BR>
	  szFile = "text"	<BR>
	  szExt  = "h"	<BR> 	  */
	  GB_FF_API  bool filePathDecomposeA(CHAR* szDir, CHAR* szFile, CHAR* szExt, const CHAR* szSrcFilePath);

	  /** \brief Весия FilePathDesomposA для WCHAR   */
	  GB_FF_API  bool filePathDecomposeW(WCHAR* szDir, WCHAR* szFile, WCHAR* szExt, const WCHAR* szSrcFilePath);

	  /**  \brief  Извлечение короткого имени файла  в lpBuffer   по указаному полному пути к файлу lpFilePath.
	  Версия для ANSI */
	  GB_FF_API  bool extractFileNameA(char* lpBuffer, const char* lpFilePath);

	  /**  \brief  Извлечение короткого имени файла  в lpBuffer   по указаному полному пути к файлу lpFilePath.
	  Версия для UNICODE */
	  GB_FF_API  bool extractFileNameW (WCHAR* lpBuffer, const WCHAR* lpFilePath);



	  /**  \brief  Извлечение из имени файла его расширения в lpBuffer  
	  по указаному полному пути к файлу lpFilePath 	  Версия для ANSI */
	  GB_FF_API  bool extractFileExtentionA (char* lpBuffer, const char* lpFilePath) ;

	  /**  \brief  Извлечение из имени файла его расширения в lpBuffer  
	  по указаному полному пути к файлу lpFilePath 	  Версия для UNICODE */
	  GB_FF_API  bool extractFileExtentionW (WCHAR* lpBuffer, const WCHAR* lpFilePath);

	  /**  \brief  Проверка на существование файла по ANSI */
	  GB_FF_API bool fileExistsA (const LPCSTR fname);

	  /**   \brief Проверка на существование файла по UNICODE */
	  GB_FF_API bool fileExistsW (const LPCTSTR fname);

	  /**   \brief зануляет расширение файла оставляя точку  */
	  GB_FF_API bool zeroFileExtentionA(CHAR* buf);
	  /**   \brief зануляет расширение файла оставляя точку  (для widechar) */
	  GB_FF_API bool zeroFileExtentionW(WCHAR* buf);

	  /**  \brief Проверка существования папки. Версия для ANSI  */
	  GB_FF_API  bool directoryExistA(const LPSTR dir);

	  GB_FF_API  bool directoryExistCstrA(const char* szDir) ;

	  /**  \brief Проверка существования папки. Версия для UNICODE  */
	  GB_FF_API  bool directoryExistW(const LPWSTR dir)   ;

	  GB_FF_API  bool directoryExistCstrW(const wchar_t* wszDir) ;


	  /**  \brief Изменяет расширение файла. В szFilename передать имя файла, в szNewExt новое расширение.
	  в lpbuff буфер результата операции (имя файла с новым расширением). Буфер lpbuff должен
	  быть достаточной длины . Возвращает true если расширение успешно изменено   и false 
	  если передано некорректное имя файла или в имени файла нет расширения   */
	  GB_FF_API bool changeFileExtentionA(CHAR* lpbuff, const CHAR* szFilename, const CHAR* szNewExt);

	  /**  \brief  Аналог функции ChangeFileExtA , но для UNICODE */
	  GB_FF_API bool changeFileExtentionW(WCHAR* lpbuff, const WCHAR* szFilename, const WCHAR* szNewExt) ;

	  /**  \brief  Сравнивает расширение файла с указаным расширением. Если совпадает то возвращает true, иначе false. ANSI  */ 
	  GB_FF_API bool compareFileExtentionsA(const CHAR* lpFileName, const CHAR* szExt);
	  /**   \brief Сравнивает расширение файла с указаным расширением. Если совпадает то возвращает true, иначе false . UNICODE  */ 
	  GB_FF_API bool compareFileExtentionsW(const WCHAR* lpFileName, const WCHAR* szExt);

	  /**  \brief Преобразует данный путь на уровень выше.   ДОБАВИТЬ КОММЕНТАРИЙ */
	  GB_FF_API bool pathLevelUpA(CHAR* path) ;

	  /**  \brief Преобразует данный путь на уровень выше. */
	  GB_FF_API bool pathLevelUpW(WCHAR* path)  ;

	  /**  \brief Сделать имя файла в буфер lpszBuff  из директории lpszDir и короткого имени файла plszFname */
	  GB_FF_API bool FileNameMakeA(CHAR* lpszBuff, const CHAR* lpszDir, const CHAR* lpszFname);

	  /**  \brief Сделать имя файла в буфер lpszBuff  из директории lpszDir и короткого имени файла plszFname */
	  GB_FF_API bool FileNameMakeW(WCHAR* lpszBuff, const WCHAR* lpszDir, const WCHAR* lpszFname) ;

	  /**  \brief Сделать имя файла в буфер lpszBuff  из директории lpszDir и   имени файла 
	  без расширения lpszFile  и  расширения lpszExt (без точки)  */
	  GB_FF_API bool fileNameMakeExA(CHAR* lpszBuff, const CHAR* lpszDir, const CHAR* lpszFile, const CHAR* lpszExt);

	  /**  \brief Сделать имя файла в буфер lpszBuff  из директории lpszDir и   имени файла 
	  без расширения lpszFile  и  расширения lpszExt (без точки)  */
	  GB_FF_API bool fileNameMakeExW(WCHAR* lpszBuff, const WCHAR* lpszDir, const WCHAR* lpszFile, const WCHAR* lpszExt);


	  /**  \brief Конвертирует полное имя файла в директорию.  Зануляет символы имени файла . Например 
	  если передать "c:\dir\file.txt" , то результат будет "c:\dir\" .  В szFilename должен быть 
	  передан полный путь к файлу .. */
	  GB_FF_API bool convertFilenameToFilePathA(CHAR* szFilename);

	  /**  \brief Вариант функции ConvertFilenameToFilePathA для WCHAR */
	  GB_FF_API bool convertFilenameToFilePathW(WCHAR* szwFilename);



	  /**  \brief Изменяет расширение файла в буфере  szFilename по новому расширению из szNewExt */
	  GB_FF_API bool changeFileExtentionA(CHAR* szFilename, const CHAR* szNewExt);

	  /**  \brief Аналог функции ChangeFileExtToA для WCHAR . Проверено */
	  GB_FF_API bool changeFileExtentionW(WCHAR* szwFilename, const WCHAR* szwNewExt) ;



	  /**  \brief  Получить полное имя файла приложения в lpBuff (char). Буфер должен быть длиной НЕ МЕНЕЕ MAX_PACH  */
	  GB_FF_API bool getApplFilenameA(char* lpBuff);

	  /**  \brief  Получить полное имя файла приложения в lpBuff (wchar). Буфер должен быть длиной НЕ МЕНЕЕ MAX_PACH  */
	  GB_FF_API bool getApplFilenameW(WCHAR* lpwBuff);

	  /**  \brief  Получить директорию приложения в lpBuff (char). Буфер должен быть длиной НЕ МЕНЕЕ MAX_PATH  */
	  GB_FF_API bool getApplPathA(CHAR* lpBuff);

	  /**  \brief  Получить директорию приложения в lpwBuff (wchar). Буфер должен быть длиной НЕ МЕНЕЕ MAX_PATH  */
	  GB_FF_API bool getApplPathW(WCHAR* lpwBuff);

	  /**  \brief Присоединяет директорию szSubDir в конец директории szDir и помещает результат в buff */
	  GB_FF_API void DirectoryConcatToA(CHAR* szDir, const CHAR* szSubDir);

	  /**  \brief Аналог DirectoryConcatA для WCHAR */
	  GB_FF_API void DirectoryConcatToW(WCHAR* szwDir, const WCHAR* szwSubDir);

	  /**  \brief Получить директорию модуля. Буфер должен быть длиной не менее MAX_PATH */
	  GB_FF_API bool getModuleDirA(CHAR* szModuleDir, const HMODULE hm) ;

	  /**  \brief Версия GetModuleDirA для WCHAR  */
	  GB_FF_API bool getModuleDirW(WCHAR* szwModuleDir, const HMODULE hm) ;

	  /**  \brief Сделать строку директории в папке где расположен модуль. 
	  szDirBuff - буфер приёмник (результат),
	  hm - хэндл модуля, 
	  szSubDir - поддиректория, например "subdir\\" */
	  GB_FF_API bool makeSubDirWhereModuleA(CHAR* szDirBuff , const HMODULE hm, const CHAR* szSubDir) ;

	  /** \brief Весия MakeSubDirWhereModule для widechar */
	  GB_FF_API bool makeSubDirWhereModuleW(WCHAR* szDirBuff , const HMODULE hm, const WCHAR* szSubDir) ;

	  /**  \brief Создаёт директорию. При успешном результате вернёт true */
	  GB_FF_API bool CreateDirectoryA(const CHAR* szDirName );

	  /**  \brief Создаёт директорию. При успешном результате вернёт true */
	  GB_FF_API bool CreateDirectoryW(const WCHAR* szDirName );

	  /** \brief Сохраняет строку(srcData)  размером numBytes   в файл(fname)        .  */
	  GB_FF_API bool saveCstrToFileA(const char* fname, const char* srcData, int numBytes);

	  /**  \brief  Сохраняет двоичные данные в файл  */
	  GB_FF_API bool saveBinDataToFileA(const char* fname, const void* pdata, unsigned int numBytes);

	  /** \brief Является ли путь полным */
	  GB_FF_API bool isFullPathA(const char* fname) ;

	  /** \brief Является ли путь полным */
	  GB_FF_API bool isFullPathW(const wchar_t* fname) ;


	  /** \brief Сравнение расширения файла . bCaseSence - учитывать или нет регистр  */
	  GB_FF_API bool compareFileExtentions2A( const char*  filename, const char* ext, bool bCaseSence = false);
	  GB_FF_API bool compareFileExtentions2W( const wchar_t*  filename, const wchar_t* ext, bool bCaseSence = false);

	  /** \brief Получить полный путь к модулю hm(NULL если к EXE)  в виде std::string/wstring.  
	  Вернёт пустую строку  если ошибка.  */
	  GB_FF_API std::string   getModuleFullPath_s_A(const HMODULE hm);
	  GB_FF_API std::wstring  getModuleFullPath_s_W(const HMODULE hm);

	  /** \brief Получить полный путь к EXE в виде std::string. Пустая строка если ошибка.  */
	  GB_FF_API std::string  getExeFullPaths_A();
	  /** \brief Получить полный путь к EXE в виде std::wstring. Пустая строка если ошибка.  */
	  GB_FF_API std::wstring getExeFullPaths_W();

	  /** \brief Получить полный путь  в модулю (DLL)  */
	  GB_FF_API    const char*     getModulePathc_A(const HMODULE hm);
	  GB_FF_API    const wchar_t*  getModulePathc_W(const HMODULE hm);

	  /** \brief Получить   полный путь к EXE */
	  GB_FF_API    const char*     getApplPathc_A();
	  GB_FF_API    const wchar_t*  getApplPathc_W();

	  /** \brief Получить директорию EXE */
	  GB_FF_API    const char*     getApplDirectoryCstr_A();
	  GB_FF_API    const wchar_t*  getApplDirectoryCstr_W();



	  /** \brief Установить текущий каталог. Если передать NULL, то будет установлена директория приложения */
	  GB_FF_API bool setCurrDirA( _in_opt CHAR* dir);
	  /** \brief См. SetCurrDirA . Версия для UNICODE */
	  GB_FF_API bool setCurrDirW( _in_opt WCHAR* dir);

	  /** \brief Получить полный путь к файлу. в буфер buf размером nbuflen. bCheckFileExists-проверять или нет на существование */
	  GB_FF_API bool getFullPathA(char*    buf, const int nbuflen,  const char* src,     bool bCheckFileExists);
	  /** \brief См. GetFullPathA . Версия для UNICODE */
	  GB_FF_API bool getFullPathW(wchar_t* buf, const int nbuflen,  const wchar_t* src,  bool bCheckFileExists);


	  /** \brief  Получить  текущую директорию  в буфер  buf  размеhом nbuflen.    */
	  GB_FF_API  bool getCurrDirA(_out char* buf,    const int nbuflen);
	  GB_FF_API  bool getCurrDirW(_out wchar_t* buf, const int nbuflen);

	  /** \brief Получить  текущую директорию.  */
	  GB_FF_API  const char*     getCurrDirCstr_A();
	  GB_FF_API  const wchar_t*  getCurrDirCstr_W();

	  /** \brief Получить короткое имя файла */
	  GB_FF_API const char*      getShortPathCstr_A(const char* src);
	  GB_FF_API const wchar_t*   getShortPathCstr_W(const wchar_t* src);

	  /** \brief Получить директорию  на момент старта приложения */
	  GB_FF_API CHAR*  getExeStartCurrDir_A();
	  /** \brief Получить директорию  на момент старта приложения */
	  GB_FF_API WCHAR* getExeStartCurrDir_W();




//----------------------------

	  class PathDataA;
	  class PathDataW;



//-------------------------------------------------------------------------




	  /** \brief Выполнить поиск файлов в указаной директории  
	  \param szDir - [in]   Директория поиска.
	  \param bIncludeSubDirs - [in]   Вкоючать в поиск подпапки или нет.
	  \param _vExtentions - [in]   Вектор содержащий расширения файлов (без точек  например txt ).
	  \param _v - [out]   Вектор , который будет содержать список найденых файлов.
	  \return  - S_OK - если файлы найдены и операция без ошибок. E_FAIL -если исключение. S_FALSE - если файлы не найдены.
	  */
	  GB_FF_API HRESULT  findFilesA(const char* szDir,  const bool bIncludeSubDirs, const std::vector<std::string>& _vExtentions, _out std::vector<PathDataA>& _v);
	  /** \brief  Версия  FindFiles для UNICODE */
	  GB_FF_API HRESULT  findFilesW(const wchar_t* wszDir,  const bool bIncludeSubDirs, const std::vector<std::wstring>& _vExtentions, _out std::vector<PathDataW>& _v);

	  /** \brief   Аналог FindFilesA , но в параметре передаётся не вектор расширений файлов,
	  а строка. расширения должны быть разделены запятой */
	  GB_FF_API HRESULT findFilesA(const char* szDir,  const bool bIncludeSubDirs, const std::string& sExtentionsLine, _out std::vector<PathDataA>& _v);
	  /** \brief  Версия  FindFiles для UNICODE */
	  GB_FF_API HRESULT findFilesW(const wchar_t* wszDir,  const bool bIncludeSubDirs, const std::wstring& sExtentionsLine, _out std::vector<PathDataW>& _v);



	  /** \brief Установить путь поиска  */
	  GB_FF_API HRESULT FileUtSetMediaSearchPathA( LPSTR strPath );

	  /** \brief найти файл и возвратить полный путь к нему  . 
	  \param strDestPath - [out] Буфер приёмник .
	  \param cchDest - [in] Размер буфера приёмника .
	  \param strFilename - [in] Файл для поиска .    	*/
	  GB_FF_API HRESULT FileUtFindFileCchA( CHAR* strDestPath, int cchDest, LPSTR strFilename );

	  GB_FF_API bool FileUtFindMediaSearchTypicalDirsA( CHAR* strSearchPath, int cchSearch, LPSTR strLeaf,  CHAR* strExePath, CHAR* strExeName );
	  GB_FF_API bool FileUtFindMediaSearchParentDirsA( CHAR* strSearchPath, int cchSearch, CHAR* strStartAt, CHAR* strLeafName );


	  /** \brief Установить путь поиска  */
	  GB_FF_API HRESULT FileUtSetMediaSearchPathW( LPCWSTR strPath );

	  /** \brief найти файл и возвратить полный путь к нему  . 
	  \param strDestPath - [out] Буфер приёмник .
	  \param cchDest - [in] Размер буфера приёмника .
	  \param strFilename - [in] Файл для поиска .    	*/
	  GB_FF_API HRESULT FileUtFindFileCchW( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename );

	  GB_FF_API bool FileUtFindMediaSearchTypicalDirsW( WCHAR* strSearchPath, int cchSearch, LPCWSTR strLeaf,  WCHAR* strExePath, WCHAR* strExeName );
	  GB_FF_API bool FileUtFindMediaSearchParentDirsW( WCHAR* strSearchPath, int cchSearch, WCHAR* strStartAt, WCHAR* strLeafName );


	  /** \brief Поиск полного пути по данному  короткому имени файла в path <br>
	  Если файл найден, то path будет заполнен полным путём к файлу. <br>
	  ВНИМАНИЕ: Глобальные пути НЕ УЧИТЫВАЮТСЯ.  */
	  GB_FF_API  HRESULT FileUtExecuteFindA(PathDataA* path) ;  
	  GB_FF_API  HRESULT FileUtExecuteFindW(PathDataW* path) ;

	  /** \brief Получить текущий путь поиска по умолчанию */
	  GB_FF_API  HRESULT FileUtGetSearchPathA(PathDataA* pOut);
	  GB_FF_API  HRESULT FileUtGetSearchPathW(PathDataW* pOut);

	  /** \brief Добавить путь поиска файлов. */
	  GB_FF_API  HRESULT FileUtApendGlobalSearchPathA(const PathDataA* path);
	  GB_FF_API  HRESULT FileUtApendGlobalSearchPathW(const PathDataW* path);

	  /** \brief Выполнить поиск файла по короткому имени файла в path. <br>
	  С учётом всех путей поиска добавленых функцией FileUtApendGlobalSearchPath. <br>
	  После выполнения операции в случае успеха в path будет полный путь к файлу <br>
	  Если файл не найден вернёт E_FAIL  . */
	  GB_FF_API  HRESULT FileUtExecFindWithGLobalSearchPathA(PathDataA* path) ;  
	  GB_FF_API  HRESULT FileUtExecFindWithGLobalSearchPathW(PathDataW* path) ; 

	  /** \brief Максимальное кол-во путей
	  поиска для функций FileUtApendGlobalSearchPath...  ПЕРЕИМЕНОВАТЬ !!!!  */
	  static const unsigned int MAX_GLOBALSEARCHPATH = 	 32;


	  /** \brief Класс для простой установки путей поиска файлов. 
	  В конструкторе просто передать требуемые пути поиска. */
	  class SearchparhApendA {
	  public:
		  GB_FF_API SearchparhApendA(const char* path0, 
			  const char* path1 = NULL,
			  const char* path2 = NULL,	   
			  const char* path3 = NULL,	   
			  const char* path4 = NULL,	   
			  const char* path5 = NULL,
			  const char* path6 = NULL,	
			  const char* path7 = NULL 	

			  );

		  //~SearchparhApendA() {};
	  };
	  // end class



 
  
//-------------------------------------------------------------------------




	  /** \brief Класс путь к  файлу или директория  для CHAR */
	  class PathDataA  {
	  public:
		  CHAR path[MAX_PATH+1];

		  PathDataA() { path[0]=0; }
		  PathDataA(const CHAR* fpath) { if(fpath) {strncpy(path, fpath,  MAX_PATH );} else { path[0]=0; }; }
		  PathDataA(const PathDataA& pd) { *this = pd; }

		  void operator = (const CHAR* s) {   strncpy(path, s ,  MAX_PATH );  }
		  void operator = (const PathDataA& pd) {   strncpy(path, pd.path ,  MAX_PATH );  }


		  bool empty() const { return ( path[0] == 0 ); }
		  void setzero() { memset(path, 0, sizeof(path) ); }
		  int lenght() const { return (int)strlen(path); }

		  bool isFullPath() const 
		  {
			  if(path[0] == 0) return false;
			  return ( path[1] == ':' );
		  }

		  bool IsDirectory() const 
		  {
			  if(empty() )
				  return false;

			  if( path[lenght()-1] == '\\' )
				  return true;

			  return false;	
		  }

		  bool operator == (const char* _data) const 
		  {
			  if( strncmp(path, _data, MAX_PATH) == 0 )   
				  return true;

			  return false;
		  }

		  bool operator == (const PathDataA& pd) const  
		  {
			  if( strncmp(path, pd.path, MAX_PATH) == 0 )   
				  return true;

			  return false;
		  }


	  };



	  /** \brief Класс путь к  файлу или директория  для WCHAR */
	  class PathDataW  {
	  public:
		  WCHAR path[MAX_PATH+1];

		  PathDataW() { path[0]=0; }
		  PathDataW(const WCHAR* fpath) { if(fpath) {wcsncpy(path, fpath,  MAX_PATH );} else { path[0]=0; }; }
		  PathDataW(const PathDataW& pd) { *this = pd; }

		  void operator = (const WCHAR* s)  {  wcsncpy(path, s ,  MAX_PATH );  }
		  void operator = (const PathDataW& pd) {   wcsncpy(path, pd.path ,  MAX_PATH );  }

		  bool empty() const { return ( path[0] == 0 ); }
		  void setzero() { memset(path, 0, sizeof(path) ); }
		  int lenght() const { return (int)wcslen(path); }

		  bool isFullPath() const 
		  {
			  if(path[0] == 0) return false;
			  return ( path[1] == L':' );
		  }

	  };






//-------------------------------------------------------------------------


  
  
  
  

  //-----------------------------------------------------------------------
  
  } // end ns

 } // end ns

} // end ns


#endif // #ifdef  WIN32 

// end file