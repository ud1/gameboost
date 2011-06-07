#include "pch.h"

#include "dialog.h"

 


#ifndef WIN32
  #error   only win32  (((
#endif

#ifdef WIN32
  #ifndef _WINDOWS_
     #error windows.h not included
  #endif
#endif

#pragma warning(push)
#pragma warning(disable:4996)

namespace gb 
{
namespace dialog 
{

//=========================================================================
 
#if ( defined(WIN32) && defined(_WINDOWS_) )

//#include <windows.h>
#include <commdlg.h>

//=========================================================================
bool openFileDialog(
					std::string& sOutFileName, 
					const char* szFilter
					) 
{
	OPENFILENAMEA ofn;
	static char fileName[MAX_PATH+1] = "";
	fileName[0]=0;
	strcpy( fileName , sOutFileName.c_str()  );

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner =  0;

	// ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.lpstrFilter = szFilter;


	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "*.*";

	if ( GetOpenFileNameA(&ofn) )
		{
		sOutFileName = fileName;
		return true;
		}
	else
		{
		return false;
		}

	return true;
}


//=========================================================================
bool saveFileDialog(
					std::string& sOutFileName, 
					const char* szFilter
					) 
{
	 /*
	typedef struct tagOFNA {
		DWORD        lStructSize;
		HWND         hwndOwner;
		HINSTANCE    hInstance;
		LPCSTR       lpstrFilter;
		LPSTR        lpstrCustomFilter;
		DWORD        nMaxCustFilter;
		DWORD        nFilterIndex;
		LPSTR        lpstrFile;
		DWORD        nMaxFile;
		LPSTR        lpstrFileTitle;
		DWORD        nMaxFileTitle;
		LPCSTR       lpstrInitialDir;
		LPCSTR       lpstrTitle;
		DWORD        Flags;
		WORD         nFileOffset;
		WORD         nFileExtension;
		LPCSTR       lpstrDefExt;
		LPARAM       lCustData;
		LPOFNHOOKPROC lpfnHook;
		LPCSTR       lpTemplateName;
#ifdef _MAC
		LPEDITMENU   lpEditInfo;
		LPCSTR       lpstrPrompt;
#endif
#if (_WIN32_WINNT >= 0x0500)
		void *        pvReserved;
		DWORD        dwReserved;
		DWORD        FlagsEx;
#endif // (_WIN32_WINNT >= 0x0500)
		} OPENFILENAMEA, *LPOPENFILENAMEA;
	*/
	
	
	OPENFILENAMEA ofn;
	static char fileName[MAX_PATH+1] = "";
	fileName[0]=0;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner =  0;

	if(szFilter)
		ofn.lpstrFilter = szFilter;
	else ofn.lpstrFilter = "*.*";

	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";


	if ( GetSaveFileNameA(&ofn) )
		{
		sOutFileName = fileName;
		return true;

		}
	else
		{
		return false;
		}

	return false;
}

//=========================================================================
static bool __DialogSelectColor(  DWORD* pdwOutColor  ) 
	{

	CHOOSECOLORA cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 

	//HBRUSH hbrush;                  // brush handle
	static DWORD rgbCurrent;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner =  0;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.rgbResult = *pdwOutColor;

	if (ChooseColorA(&cc)==TRUE) 
		{
		//hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult; 
		*pdwOutColor = cc.rgbResult;
		return true;
		}
	else
		{
		return false;
		}

	return false;
	};


//=========================================================================
bool DialogSelectColor(  float& r,   float& g,   float& b  ) 	
{

	DWORD dwRes =0;
	
	
	dwRes |=  (DWORD) ( ( (DWORD)r * 255)  );
	dwRes |=  (DWORD) ( ( (DWORD)b * 255) << 8 );
	dwRes |=  (DWORD) ( ( (DWORD)g * 255) << 16 );


	if(__DialogSelectColor(&dwRes) )
		{
		r = (float)(  ((  (dwRes       ) | 0xffffff00 ) ^ 0xffffff00 )/255.0f  );
		g = (float)(  ((  (dwRes >> 8  ) | 0xffffff00 ) ^ 0xffffff00 )/255.0f  );
		b = (float)(  ((  (dwRes >> 16 ) | 0xffffff00 ) ^ 0xffffff00 )/255.0f  );

		return true;
		}
	else
		{
         return false;
		}

	return true;
};


#endif // WIN32







//=========================================================================

}
// end namespace
}
// end namespace

#pragma warning( pop )
// end file