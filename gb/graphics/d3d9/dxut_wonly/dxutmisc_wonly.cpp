//--------------------------------------------------------------------------------------
// File: DXUTMisc.cpp
//
// Shortcut macros and functions for using DX objects
//
// Copyright (c) Microsoft Corporation. All rights reserved
//--------------------------------------------------------------------------------------
 
#include  "dxut_wonly.h"


#define DXUT_GAMEPAD_TRIGGER_THRESHOLD      30
#undef min // use __min instead
#undef max // use __max instead

//
////--------------------------------------------------------------------------------------
//// Global/Static Members
////--------------------------------------------------------------------------------------
//CDXUTResourceCache& DXUTGetGlobalResourceCache()
//{
//    // Using an accessor function gives control of the construction order
//    static CDXUTResourceCache cache;
//    return cache;
//}


CDXUTTimer* DXUTGetGlobalTimer()
{
    // Using an accessor function gives control of the construction order
    static CDXUTTimer timer;
    return &timer;
}


//--------------------------------------------------------------------------------------
// Internal functions forward declarations
//--------------------------------------------------------------------------------------
bool DXUTFindMediaSearchTypicalDirs( WCHAR* strSearchPath, int cchSearch, LPCWSTR strLeaf, WCHAR* strExePath, WCHAR* strExeName );
bool DXUTFindMediaSearchParentDirs( WCHAR* strSearchPath, int cchSearch, WCHAR* strStartAt, WCHAR* strLeafName );
INT_PTR CALLBACK DisplaySwitchToREFWarningProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


//--------------------------------------------------------------------------------------
// Shared code for samples to ask user if they want to use a REF device or quit
//--------------------------------------------------------------------------------------
void DXUTDisplaySwitchingToREFWarning()
{
    if( DXUTGetShowMsgBoxOnError() )
    {
        // Open the appropriate registry key
        DWORD dwSkipWarning = 0;
        HKEY hKey;
        LONG lResult = RegOpenKeyEx( HKEY_CURRENT_USER, L"Software\\Microsoft\\DirectX 9.0 SDK", 0, KEY_READ, &hKey );
        if( ERROR_SUCCESS == lResult ) 
        {
            DWORD dwType;
            DWORD dwSize = sizeof(DWORD);
            lResult = RegQueryValueEx( hKey, L"Skip Warning On REF", NULL, &dwType, (BYTE*)&dwSkipWarning, &dwSize );
            RegCloseKey( hKey );
        }

        if( dwSkipWarning == 0 )
        {
            // Compact code to create a custom dialog box without using a template in a resource file.
            // If this dialog were in a .rc file, this would be a lot simpler but every sample calling this function would
            // need a copy of the dialog in its own .rc file. Also MessageBox API could be used here instead, but 
            // the MessageBox API is simpler to call but it can't provide a "Don't show again" checkbox
            typedef struct { DLGITEMTEMPLATE a; WORD b; WORD c; WORD d; WORD e; WORD f; } DXUT_DLG_ITEM; 
            typedef struct { DLGTEMPLATE a; WORD b; WORD c; WCHAR d[2]; WORD e; WCHAR f[14]; DXUT_DLG_ITEM i1; DXUT_DLG_ITEM i2; DXUT_DLG_ITEM i3; DXUT_DLG_ITEM i4; DXUT_DLG_ITEM i5; } DXUT_DLG_DATA; 

            DXUT_DLG_DATA dtp = 
            {                                                                                                                                                  
                {WS_CAPTION|WS_POPUP|WS_VISIBLE|WS_SYSMENU|DS_ABSALIGN|DS_3DLOOK|DS_SETFONT|DS_MODALFRAME|DS_CENTER,0,5,0,0,269,82},0,0,L" ",8,L"MS Sans Serif", 
                {{WS_CHILD|WS_VISIBLE|SS_ICON|SS_CENTERIMAGE,0,7,7,24,24,0x100},0xFFFF,0x0082,0,0,0}, // icon
                {{WS_CHILD|WS_VISIBLE,0,40,7,230,25,0x101},0xFFFF,0x0082,0,0,0}, // static text
                {{WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,0,80,39,50,14,IDYES},0xFFFF,0x0080,0,0,0}, // Yes button
                {{WS_CHILD|WS_VISIBLE,0,133,39,50,14,IDNO},0xFFFF,0x0080,0,0,0}, // No button
                {{WS_CHILD|WS_VISIBLE|BS_CHECKBOX,0,7,59,70,16,IDIGNORE},0xFFFF,0x0080,0,0,0}, // checkbox
            }; 

            int nResult = (int) DialogBoxIndirect( DXUTGetHINSTANCE(), (DLGTEMPLATE*)&dtp, DXUTGetHWND(), DisplaySwitchToREFWarningProc ); 

            if( (nResult & 0x80) == 0x80 ) // "Don't show again" checkbox was checked
            {
                lResult = RegOpenKeyEx( HKEY_CURRENT_USER, L"Software\\Microsoft\\DirectX 9.0 SDK", 0, KEY_WRITE, &hKey );
                if( ERROR_SUCCESS == lResult ) 
                {
                    dwSkipWarning = 1;
                    RegSetValueEx( hKey, L"Skip Warning On REF", 0, REG_DWORD, (BYTE*)&dwSkipWarning, sizeof(DWORD) );
                    RegCloseKey( hKey );
                }
            }

            // User choose not to continue
            if( (nResult & 0x0F) == IDNO )
                DXUTShutdown(1);
        }
    }
}


//--------------------------------------------------------------------------------------
// MsgProc for DXUTDisplaySwitchingToREFWarning() dialog box
//--------------------------------------------------------------------------------------
INT_PTR CALLBACK DisplaySwitchToREFWarningProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    switch (message) 
    { 
        case WM_INITDIALOG:
            // Easier to set text here than in the DLGITEMTEMPLATE
            SetWindowText( hDlg, DXUTGetWindowTitle() );
            SendMessage( GetDlgItem(hDlg, 0x100), STM_SETIMAGE, IMAGE_ICON, (LPARAM)LoadIcon(0, IDI_QUESTION));
            SetDlgItemText( hDlg, 0x101, L"Switching to the Direct3D reference rasterizer, a software device\nthat implements the entire Direct3D feature set, but runs very slowly.\nDo you wish to continue?" ); 
            SetDlgItemText( hDlg, IDYES, L"&Yes" );
            SetDlgItemText( hDlg, IDNO, L"&No" );
            SetDlgItemText( hDlg, IDIGNORE, L"&Don't show again" );
            break;

        case WM_COMMAND: 
            switch (LOWORD(wParam)) 
            { 
                case IDIGNORE: CheckDlgButton( hDlg, IDIGNORE, (IsDlgButtonChecked( hDlg, IDIGNORE ) == BST_CHECKED) ? BST_UNCHECKED : BST_CHECKED ); EnableWindow( GetDlgItem( hDlg, IDNO ), (IsDlgButtonChecked( hDlg, IDIGNORE ) != BST_CHECKED) ); break;
                case IDNO: EndDialog(hDlg, (IsDlgButtonChecked( hDlg, IDIGNORE ) == BST_CHECKED) ? IDNO|0x80 : IDNO|0x00 ); return TRUE; 
                case IDCANCEL:
                case IDYES: EndDialog(hDlg, (IsDlgButtonChecked( hDlg, IDIGNORE ) == BST_CHECKED) ? IDYES|0x80 : IDYES|0x00 ); return TRUE; 
            } 
            break;
    } 
    return FALSE; 
} 


//--------------------------------------------------------------------------------------
CDXUTTimer::CDXUTTimer()
{
    m_bTimerStopped     = true;
    m_llQPFTicksPerSec  = 0;

    m_llStopTime        = 0;
    m_llLastElapsedTime = 0;
    m_llBaseTime        = 0;

    // Use QueryPerformanceFrequency to get the frequency of the counter
    LARGE_INTEGER qwTicksPerSec;
    QueryPerformanceFrequency( &qwTicksPerSec );
    m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;
}


//--------------------------------------------------------------------------------------
void CDXUTTimer::Reset()
{
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();
    
    m_llBaseTime        = qwTime.QuadPart;
    m_llLastElapsedTime = qwTime.QuadPart;
    m_llStopTime        = 0;
    m_bTimerStopped     = FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTTimer::Start()
{
    // Get the current time
    LARGE_INTEGER qwTime;
    QueryPerformanceCounter( &qwTime );

    if( m_bTimerStopped )
        m_llBaseTime += qwTime.QuadPart - m_llStopTime;
    m_llStopTime = 0;
    m_llLastElapsedTime = qwTime.QuadPart;
    m_bTimerStopped = FALSE;
}


//--------------------------------------------------------------------------------------
void CDXUTTimer::Stop()
{
    if( !m_bTimerStopped )
    {
        LARGE_INTEGER qwTime;
        QueryPerformanceCounter( &qwTime );
        m_llStopTime = qwTime.QuadPart;
        m_llLastElapsedTime = qwTime.QuadPart;
        m_bTimerStopped = TRUE;
    }
}


//--------------------------------------------------------------------------------------
void CDXUTTimer::Advance()
{
    m_llStopTime += m_llQPFTicksPerSec/10;
}


//--------------------------------------------------------------------------------------
double CDXUTTimer::GetAbsoluteTime()
{
    LARGE_INTEGER qwTime;
    QueryPerformanceCounter( &qwTime );

    double fTime = qwTime.QuadPart / (double) m_llQPFTicksPerSec;

    return fTime;
}


//--------------------------------------------------------------------------------------
double CDXUTTimer::GetTime()
{
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    double fAppTime = (double) ( qwTime.QuadPart - m_llBaseTime ) / (double) m_llQPFTicksPerSec;

    return fAppTime;
}


//--------------------------------------------------------------------------------------
void CDXUTTimer::GetTimeValues( double* pfTime, double* pfAbsoluteTime, float* pfElapsedTime )
{
    assert( pfTime && pfAbsoluteTime && pfElapsedTime );    

    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    float fElapsedTime = (float) ((double) ( qwTime.QuadPart - m_llLastElapsedTime ) / (double) m_llQPFTicksPerSec);
    m_llLastElapsedTime = qwTime.QuadPart;

    // Clamp the timer to non-negative values to ensure the timer is accurate.
    // fElapsedTime can be outside this range if processor goes into a 
    // power save mode or we somehow get shuffled to another processor.  
    // However, the main thread should call SetThreadAffinityMask to ensure that 
    // we don't get shuffled to another processor.  Other worker threads should NOT call 
    // SetThreadAffinityMask, but use a shared copy of the timer data gathered from 
    // the main thread.
    if( fElapsedTime < 0.0f )
        fElapsedTime = 0.0f;
    
    *pfAbsoluteTime = qwTime.QuadPart / (double) m_llQPFTicksPerSec;
    *pfTime = ( qwTime.QuadPart - m_llBaseTime ) / (double) m_llQPFTicksPerSec;   
    *pfElapsedTime = fElapsedTime;
}


//--------------------------------------------------------------------------------------
double CDXUTTimer::GetElapsedTime()
{
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    double fElapsedTime = (double) ( qwTime.QuadPart - m_llLastElapsedTime ) / (double) m_llQPFTicksPerSec;
    m_llLastElapsedTime = qwTime.QuadPart;

    // See the explanation about clamping in CDXUTTimer::GetTimeValues()
    if( fElapsedTime < 0.0f )
        fElapsedTime = 0.0f;

    return fElapsedTime;
}


//--------------------------------------------------------------------------------------
// If stopped, returns time when stopped otherwise returns current time
//--------------------------------------------------------------------------------------
LARGE_INTEGER CDXUTTimer::GetAdjustedCurrentTime()
{
    LARGE_INTEGER qwTime;
    if( m_llStopTime != 0 )
        qwTime.QuadPart = m_llStopTime;
    else
        QueryPerformanceCounter( &qwTime );
    return qwTime;
}


//--------------------------------------------------------------------------------------
bool CDXUTTimer::IsStopped()
{
    return m_bTimerStopped;
}


//--------------------------------------------------------------------------------------
// Limit the current thread to one processor (the current one). This ensures that timing code 
// runs on only one processor, and will not suffer any ill effects from power management.
// See "Game Timing and Multicore Processors" for more details
//--------------------------------------------------------------------------------------
void CDXUTTimer::LimitThreadAffinityToCurrentProc()
{
    HANDLE hCurrentProcess = GetCurrentProcess();
    
    // Get the processor affinity mask for this process
    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;
    
    if( GetProcessAffinityMask( hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask ) != 0 && dwProcessAffinityMask )
    {
        // Find the lowest processor that our process is allows to run against
        DWORD_PTR dwAffinityMask = ( dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1 ) );

        // Set this as the processor that our thread must always run against
        // This must be a subset of the process affinity mask
        HANDLE hCurrentThread = GetCurrentThread();
        if( INVALID_HANDLE_VALUE != hCurrentThread )
        {
            SetThreadAffinityMask( hCurrentThread, dwAffinityMask );
            CloseHandle( hCurrentThread );
        }
    }

    CloseHandle( hCurrentProcess );
}


//--------------------------------------------------------------------------------------
// Returns pointer to static media search buffer
//--------------------------------------------------------------------------------------
WCHAR* DXUTMediaSearchPath()
{
    static WCHAR s_strMediaSearchPath[MAX_PATH] = {0};
    return s_strMediaSearchPath;

}   

//--------------------------------------------------------------------------------------
LPCWSTR DXUTGetMediaSearchPath()
{
    return DXUTMediaSearchPath();
}


//--------------------------------------------------------------------------------------
HRESULT DXUTSetMediaSearchPath( LPCWSTR strPath )
{
    HRESULT hr;

    WCHAR* s_strSearchPath = DXUTMediaSearchPath();

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
HRESULT DXUTFindDXSDKMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename )
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
    bFound = DXUTFindMediaSearchTypicalDirs( strDestPath, cchDest, strFilename, strExePath, strExeName );
    if( bFound )
        return S_OK;

    // Typical directory search again, but also look in a subdir called "\media\" 
    StringCchPrintf( strSearchFor, MAX_PATH, L"media\\%s", strFilename ); 
    bFound = DXUTFindMediaSearchTypicalDirs( strDestPath, cchDest, strSearchFor, strExePath, strExeName );
    if( bFound )
        return S_OK;

    WCHAR strLeafName[MAX_PATH] = {0};

    // Search all parent directories starting at .\ and using strFilename as the leaf name
    StringCchCopy( strLeafName, MAX_PATH, strFilename ); 
    bFound = DXUTFindMediaSearchParentDirs( strDestPath, cchDest, L".", strLeafName );
    if( bFound )
        return S_OK;

    // Search all parent directories starting at the exe's dir and using strFilename as the leaf name
    bFound = DXUTFindMediaSearchParentDirs( strDestPath, cchDest, strExePath, strLeafName );
    if( bFound )
        return S_OK;

    // Search all parent directories starting at .\ and using "media\strFilename" as the leaf name
    StringCchPrintf( strLeafName, MAX_PATH, L"media\\%s", strFilename ); 
    bFound = DXUTFindMediaSearchParentDirs( strDestPath, cchDest, L".", strLeafName );
    if( bFound )
        return S_OK;

    // Search all parent directories starting at the exe's dir and using "media\strFilename" as the leaf name
    bFound = DXUTFindMediaSearchParentDirs( strDestPath, cchDest, strExePath, strLeafName );
    if( bFound )
        return S_OK;

    // On failure, return the file as the path but also return an error code
    StringCchCopy( strDestPath, cchDest, strFilename );

    return DXUTERR_MEDIANOTFOUND;
}


//--------------------------------------------------------------------------------------
// Search a set of typical directories
//--------------------------------------------------------------------------------------
bool DXUTFindMediaSearchTypicalDirs( WCHAR* strSearchPath, int cchSearch, LPCWSTR strLeaf, 
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
    WCHAR* s_strSearchPath = DXUTMediaSearchPath();
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
bool DXUTFindMediaSearchParentDirs( WCHAR* strSearchPath, int cchSearch, WCHAR* strStartAt, WCHAR* strLeafName )
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

  
 

//--------------------------------------------------------------------------------------
// Returns the string for the given D3DFORMAT.
//--------------------------------------------------------------------------------------
LPCWSTR DXUTD3DFormatToString( D3DFORMAT format, bool bWithPrefix )
{
    WCHAR* pstr = NULL;
    switch( format )
    {
    case D3DFMT_UNKNOWN:         pstr = L"D3DFMT_UNKNOWN"; break;
    case D3DFMT_R8G8B8:          pstr = L"D3DFMT_R8G8B8"; break;
    case D3DFMT_A8R8G8B8:        pstr = L"D3DFMT_A8R8G8B8"; break;
    case D3DFMT_X8R8G8B8:        pstr = L"D3DFMT_X8R8G8B8"; break;
    case D3DFMT_R5G6B5:          pstr = L"D3DFMT_R5G6B5"; break;
    case D3DFMT_X1R5G5B5:        pstr = L"D3DFMT_X1R5G5B5"; break;
    case D3DFMT_A1R5G5B5:        pstr = L"D3DFMT_A1R5G5B5"; break;
    case D3DFMT_A4R4G4B4:        pstr = L"D3DFMT_A4R4G4B4"; break;
    case D3DFMT_R3G3B2:          pstr = L"D3DFMT_R3G3B2"; break;
    case D3DFMT_A8:              pstr = L"D3DFMT_A8"; break;
    case D3DFMT_A8R3G3B2:        pstr = L"D3DFMT_A8R3G3B2"; break;
    case D3DFMT_X4R4G4B4:        pstr = L"D3DFMT_X4R4G4B4"; break;
    case D3DFMT_A2B10G10R10:     pstr = L"D3DFMT_A2B10G10R10"; break;
    case D3DFMT_A8B8G8R8:        pstr = L"D3DFMT_A8B8G8R8"; break;
    case D3DFMT_X8B8G8R8:        pstr = L"D3DFMT_X8B8G8R8"; break;
    case D3DFMT_G16R16:          pstr = L"D3DFMT_G16R16"; break;
    case D3DFMT_A2R10G10B10:     pstr = L"D3DFMT_A2R10G10B10"; break;
    case D3DFMT_A16B16G16R16:    pstr = L"D3DFMT_A16B16G16R16"; break;
    case D3DFMT_A8P8:            pstr = L"D3DFMT_A8P8"; break;
    case D3DFMT_P8:              pstr = L"D3DFMT_P8"; break;
    case D3DFMT_L8:              pstr = L"D3DFMT_L8"; break;
    case D3DFMT_A8L8:            pstr = L"D3DFMT_A8L8"; break;
    case D3DFMT_A4L4:            pstr = L"D3DFMT_A4L4"; break;
    case D3DFMT_V8U8:            pstr = L"D3DFMT_V8U8"; break;
    case D3DFMT_L6V5U5:          pstr = L"D3DFMT_L6V5U5"; break;
    case D3DFMT_X8L8V8U8:        pstr = L"D3DFMT_X8L8V8U8"; break;
    case D3DFMT_Q8W8V8U8:        pstr = L"D3DFMT_Q8W8V8U8"; break;
    case D3DFMT_V16U16:          pstr = L"D3DFMT_V16U16"; break;
    case D3DFMT_A2W10V10U10:     pstr = L"D3DFMT_A2W10V10U10"; break;
    case D3DFMT_UYVY:            pstr = L"D3DFMT_UYVY"; break;
    case D3DFMT_YUY2:            pstr = L"D3DFMT_YUY2"; break;
    case D3DFMT_DXT1:            pstr = L"D3DFMT_DXT1"; break;
    case D3DFMT_DXT2:            pstr = L"D3DFMT_DXT2"; break;
    case D3DFMT_DXT3:            pstr = L"D3DFMT_DXT3"; break;
    case D3DFMT_DXT4:            pstr = L"D3DFMT_DXT4"; break;
    case D3DFMT_DXT5:            pstr = L"D3DFMT_DXT5"; break;
    case D3DFMT_D16_LOCKABLE:    pstr = L"D3DFMT_D16_LOCKABLE"; break;
    case D3DFMT_D32:             pstr = L"D3DFMT_D32"; break;
    case D3DFMT_D15S1:           pstr = L"D3DFMT_D15S1"; break;
    case D3DFMT_D24S8:           pstr = L"D3DFMT_D24S8"; break;
    case D3DFMT_D24X8:           pstr = L"D3DFMT_D24X8"; break;
    case D3DFMT_D24X4S4:         pstr = L"D3DFMT_D24X4S4"; break;
    case D3DFMT_D16:             pstr = L"D3DFMT_D16"; break;
    case D3DFMT_L16:             pstr = L"D3DFMT_L16"; break;
    case D3DFMT_VERTEXDATA:      pstr = L"D3DFMT_VERTEXDATA"; break;
    case D3DFMT_INDEX16:         pstr = L"D3DFMT_INDEX16"; break;
    case D3DFMT_INDEX32:         pstr = L"D3DFMT_INDEX32"; break;
    case D3DFMT_Q16W16V16U16:    pstr = L"D3DFMT_Q16W16V16U16"; break;
    case D3DFMT_MULTI2_ARGB8:    pstr = L"D3DFMT_MULTI2_ARGB8"; break;
    case D3DFMT_R16F:            pstr = L"D3DFMT_R16F"; break;
    case D3DFMT_G16R16F:         pstr = L"D3DFMT_G16R16F"; break;
    case D3DFMT_A16B16G16R16F:   pstr = L"D3DFMT_A16B16G16R16F"; break;
    case D3DFMT_R32F:            pstr = L"D3DFMT_R32F"; break;
    case D3DFMT_G32R32F:         pstr = L"D3DFMT_G32R32F"; break;
    case D3DFMT_A32B32G32R32F:   pstr = L"D3DFMT_A32B32G32R32F"; break;
    case D3DFMT_CxV8U8:          pstr = L"D3DFMT_CxV8U8"; break;
    default:                     pstr = L"Unknown format"; break;
    }
    if( bWithPrefix || wcsstr( pstr, L"D3DFMT_" )== NULL )
        return pstr;
    else
        return pstr + lstrlen( L"D3DFMT_" );
}



//--------------------------------------------------------------------------------------
// Outputs to the debug stream a formatted Unicode string with a variable-argument list.
//--------------------------------------------------------------------------------------
VOID DXUTOutputDebugStringW( LPCWSTR strMsg, ... )
{
#if defined(DEBUG) || defined(_DEBUG)
    WCHAR strBuffer[512];
    
    va_list args;
    va_start(args, strMsg);
    StringCchVPrintfW( strBuffer, 512, strMsg, args );
    strBuffer[511] = L'\0';
    va_end(args);

    OutputDebugString( strBuffer );
#else
    UNREFERENCED_PARAMETER(strMsg);
#endif
}


//--------------------------------------------------------------------------------------
// Outputs to the debug stream a formatted MBCS string with a variable-argument list.
//--------------------------------------------------------------------------------------
VOID DXUTOutputDebugStringA( LPCSTR strMsg, ... )
{
#if defined(DEBUG) || defined(_DEBUG)
    CHAR strBuffer[512];
    
    va_list args;
    va_start(args, strMsg);
    StringCchVPrintfA( strBuffer, 512, strMsg, args );
    strBuffer[511] = '\0';
    va_end(args);

    OutputDebugStringA( strBuffer );
#else
    UNREFERENCED_PARAMETER(strMsg);
#endif
}
 
  


//--------------------------------------------------------------------------------------
// Direct3D9 dynamic linking support -- calls top-level D3D9 APIs with graceful
// failure if APIs are not present.
//--------------------------------------------------------------------------------------

// Function prototypes
typedef IDirect3D9* (WINAPI * LPDIRECT3DCREATE9) (UINT);
typedef INT         (WINAPI * LPD3DPERF_BEGINEVENT)(D3DCOLOR, LPCWSTR);
typedef INT         (WINAPI * LPD3DPERF_ENDEVENT)(void);
typedef VOID        (WINAPI * LPD3DPERF_SETMARKER)(D3DCOLOR, LPCWSTR);
typedef VOID        (WINAPI * LPD3DPERF_SETREGION)(D3DCOLOR, LPCWSTR);
typedef BOOL        (WINAPI * LPD3DPERF_QUERYREPEATFRAME)(void);
typedef VOID        (WINAPI * LPD3DPERF_SETOPTIONS)( DWORD dwOptions );
typedef DWORD       (WINAPI * LPD3DPERF_GETSTATUS)( void );

// Module and function pointers
static HMODULE s_hModD3D9 = NULL;
static LPDIRECT3DCREATE9 s_DynamicDirect3DCreate9 = NULL;
static LPD3DPERF_BEGINEVENT s_DynamicD3DPERF_BeginEvent = NULL;
static LPD3DPERF_ENDEVENT s_DynamicD3DPERF_EndEvent = NULL;
static LPD3DPERF_SETMARKER s_DynamicD3DPERF_SetMarker = NULL;
static LPD3DPERF_SETREGION s_DynamicD3DPERF_SetRegion = NULL;
static LPD3DPERF_QUERYREPEATFRAME s_DynamicD3DPERF_QueryRepeatFrame = NULL;
static LPD3DPERF_SETOPTIONS s_DynamicD3DPERF_SetOptions = NULL;
static LPD3DPERF_GETSTATUS s_DynamicD3DPERF_GetStatus = NULL;

// Ensure function pointers are initialized
static bool DXUT_EnsureD3DAPIs( void )
{
    // If module is non-NULL, this function has already been called.  Note
    // that this doesn't guarantee that all D3D9 procaddresses were found.
    if( s_hModD3D9 != NULL )
        return true;

    // This may fail if DirectX 9 isn't installed
    s_hModD3D9 = LoadLibrary( L"d3d9.dll" );
    if( s_hModD3D9 == NULL ) 
        return false;
    s_DynamicDirect3DCreate9 = (LPDIRECT3DCREATE9)GetProcAddress( s_hModD3D9, "Direct3DCreate9" );
    s_DynamicD3DPERF_BeginEvent = (LPD3DPERF_BEGINEVENT)GetProcAddress( s_hModD3D9, "D3DPERF_BeginEvent" );
    s_DynamicD3DPERF_EndEvent = (LPD3DPERF_ENDEVENT)GetProcAddress( s_hModD3D9, "D3DPERF_EndEvent" );
    s_DynamicD3DPERF_SetMarker = (LPD3DPERF_SETMARKER)GetProcAddress( s_hModD3D9, "D3DPERF_SetMarker" );
    s_DynamicD3DPERF_SetRegion = (LPD3DPERF_SETREGION)GetProcAddress( s_hModD3D9, "D3DPERF_SetRegion" );
    s_DynamicD3DPERF_QueryRepeatFrame = (LPD3DPERF_QUERYREPEATFRAME)GetProcAddress( s_hModD3D9, "D3DPERF_QueryRepeatFrame" );
    s_DynamicD3DPERF_SetOptions = (LPD3DPERF_SETOPTIONS)GetProcAddress( s_hModD3D9, "D3DPERF_SetOptions" );
    s_DynamicD3DPERF_GetStatus = (LPD3DPERF_GETSTATUS)GetProcAddress( s_hModD3D9, "D3DPERF_GetStatus" );
    return true;
}

IDirect3D9 * WINAPI DXUT_Dynamic_Direct3DCreate9(UINT SDKVersion) 
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicDirect3DCreate9 != NULL )
        return s_DynamicDirect3DCreate9( SDKVersion );
    else
        return NULL;
}

int WINAPI DXUT_Dynamic_D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_BeginEvent != NULL )
        return s_DynamicD3DPERF_BeginEvent( col, wszName );
    else
        return -1;
}

int WINAPI DXUT_Dynamic_D3DPERF_EndEvent( void )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_EndEvent != NULL )
        return s_DynamicD3DPERF_EndEvent();
    else
        return -1;
}

void WINAPI DXUT_Dynamic_D3DPERF_SetMarker( D3DCOLOR col, LPCWSTR wszName )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_SetMarker != NULL )
        s_DynamicD3DPERF_SetMarker( col, wszName );
}

void WINAPI DXUT_Dynamic_D3DPERF_SetRegion( D3DCOLOR col, LPCWSTR wszName )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_SetRegion != NULL )
        s_DynamicD3DPERF_SetRegion( col, wszName );
}

BOOL WINAPI DXUT_Dynamic_D3DPERF_QueryRepeatFrame( void )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_QueryRepeatFrame != NULL )
        return s_DynamicD3DPERF_QueryRepeatFrame();
    else
        return FALSE;
}

void WINAPI DXUT_Dynamic_D3DPERF_SetOptions( DWORD dwOptions )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_SetOptions != NULL )
        s_DynamicD3DPERF_SetOptions( dwOptions );
}

DWORD WINAPI DXUT_Dynamic_D3DPERF_GetStatus( void )
{
    if( DXUT_EnsureD3DAPIs() && s_DynamicD3DPERF_GetStatus != NULL )
        return s_DynamicD3DPERF_GetStatus();
    else
        return 0;
}


//--------------------------------------------------------------------------------------
// Trace a string description of a decl 
//--------------------------------------------------------------------------------------
void DXUTTraceDecl( D3DVERTEXELEMENT9 decl[65] )
{
    int iDecl=0;
    for( iDecl=0; iDecl<65; iDecl++ )   //  MAX_FVF_DECL_SIZE
    {
        if( decl[iDecl].Stream == 0xFF )
            break;

        DXUTOutputDebugString( L"decl[%d]=Stream:%d, Offset:%d, %s, %s, %s, UsageIndex:%d\n", iDecl, 
                    decl[iDecl].Stream,
                    decl[iDecl].Offset,
                    DXUTTraceD3DDECLTYPEtoString( decl[iDecl].Type ),
                    DXUTTraceD3DDECLMETHODtoString( decl[iDecl].Method ),
                    DXUTTraceD3DDECLUSAGEtoString( decl[iDecl].Usage ),
                    decl[iDecl].UsageIndex );
    }

    DXUTOutputDebugString( L"decl[%d]=D3DDECL_END\n", iDecl );
}


//--------------------------------------------------------------------------------------
WCHAR* DXUTTraceD3DDECLTYPEtoString( BYTE t )
{
    switch( t )
    {
        case D3DDECLTYPE_FLOAT1: return L"D3DDECLTYPE_FLOAT1";
        case D3DDECLTYPE_FLOAT2: return L"D3DDECLTYPE_FLOAT2";
        case D3DDECLTYPE_FLOAT3: return L"D3DDECLTYPE_FLOAT3";
        case D3DDECLTYPE_FLOAT4: return L"D3DDECLTYPE_FLOAT4";
        case D3DDECLTYPE_D3DCOLOR: return L"D3DDECLTYPE_D3DCOLOR";
        case D3DDECLTYPE_UBYTE4: return L"D3DDECLTYPE_UBYTE4";
        case D3DDECLTYPE_SHORT2: return L"D3DDECLTYPE_SHORT2";
        case D3DDECLTYPE_SHORT4: return L"D3DDECLTYPE_SHORT4";
        case D3DDECLTYPE_UBYTE4N: return L"D3DDECLTYPE_UBYTE4N";
        case D3DDECLTYPE_SHORT2N: return L"D3DDECLTYPE_SHORT2N";
        case D3DDECLTYPE_SHORT4N: return L"D3DDECLTYPE_SHORT4N";
        case D3DDECLTYPE_USHORT2N: return L"D3DDECLTYPE_USHORT2N";
        case D3DDECLTYPE_USHORT4N: return L"D3DDECLTYPE_USHORT4N";
        case D3DDECLTYPE_UDEC3: return L"D3DDECLTYPE_UDEC3";
        case D3DDECLTYPE_DEC3N: return L"D3DDECLTYPE_DEC3N";
        case D3DDECLTYPE_FLOAT16_2: return L"D3DDECLTYPE_FLOAT16_2";
        case D3DDECLTYPE_FLOAT16_4: return L"D3DDECLTYPE_FLOAT16_4";
        case D3DDECLTYPE_UNUSED: return L"D3DDECLTYPE_UNUSED";
        default: return L"D3DDECLTYPE Unknown";
    }
}

WCHAR* DXUTTraceD3DDECLMETHODtoString( BYTE m )
{
    switch( m )
    {
        case D3DDECLMETHOD_DEFAULT: return L"D3DDECLMETHOD_DEFAULT";
        case D3DDECLMETHOD_PARTIALU: return L"D3DDECLMETHOD_PARTIALU";
        case D3DDECLMETHOD_PARTIALV: return L"D3DDECLMETHOD_PARTIALV";
        case D3DDECLMETHOD_CROSSUV: return L"D3DDECLMETHOD_CROSSUV";
        case D3DDECLMETHOD_UV: return L"D3DDECLMETHOD_UV";
        case D3DDECLMETHOD_LOOKUP: return L"D3DDECLMETHOD_LOOKUP";
        case D3DDECLMETHOD_LOOKUPPRESAMPLED: return L"D3DDECLMETHOD_LOOKUPPRESAMPLED";
        default: return L"D3DDECLMETHOD Unknown";
    }
}

WCHAR* DXUTTraceD3DDECLUSAGEtoString( BYTE u )
{
    switch( u )
    {
        case D3DDECLUSAGE_POSITION: return L"D3DDECLUSAGE_POSITION";
        case D3DDECLUSAGE_BLENDWEIGHT: return L"D3DDECLUSAGE_BLENDWEIGHT";
        case D3DDECLUSAGE_BLENDINDICES: return L"D3DDECLUSAGE_BLENDINDICES";
        case D3DDECLUSAGE_NORMAL: return L"D3DDECLUSAGE_NORMAL";
        case D3DDECLUSAGE_PSIZE: return L"D3DDECLUSAGE_PSIZE";
        case D3DDECLUSAGE_TEXCOORD: return L"D3DDECLUSAGE_TEXCOORD";
        case D3DDECLUSAGE_TANGENT: return L"D3DDECLUSAGE_TANGENT";
        case D3DDECLUSAGE_BINORMAL: return L"D3DDECLUSAGE_BINORMAL";
        case D3DDECLUSAGE_TESSFACTOR: return L"D3DDECLUSAGE_TESSFACTOR";
        case D3DDECLUSAGE_POSITIONT: return L"D3DDECLUSAGE_POSITIONT";
        case D3DDECLUSAGE_COLOR: return L"D3DDECLUSAGE_COLOR";
        case D3DDECLUSAGE_FOG: return L"D3DDECLUSAGE_FOG";
        case D3DDECLUSAGE_DEPTH: return L"D3DDECLUSAGE_DEPTH";
        case D3DDECLUSAGE_SAMPLE: return L"D3DDECLUSAGE_SAMPLE";
        default: return L"D3DDECLUSAGE Unknown";
    }
}


//--------------------------------------------------------------------------------------
// Multimon API handling for OSes with or without multimon API support
//--------------------------------------------------------------------------------------
#define DXUT_PRIMARY_MONITOR ((HMONITOR)0x12340042)
typedef HMONITOR (WINAPI* LPMONITORFROMWINDOW)(HWND, DWORD);
typedef BOOL     (WINAPI* LPGETMONITORINFO)(HMONITOR, LPMONITORINFO);

BOOL DXUTGetMonitorInfo(HMONITOR hMonitor, LPMONITORINFO lpMonitorInfo)
{
    static bool s_bInited = false;
    static LPGETMONITORINFO s_pFnGetMonitorInfo = NULL;
    if( !s_bInited )        
    {
        s_bInited = true;
        HMODULE hUser32 = GetModuleHandle( L"USER32" );
        if (hUser32 ) 
        {
            OSVERSIONINFOA osvi = {0}; osvi.dwOSVersionInfoSize = sizeof(osvi); GetVersionExA((OSVERSIONINFOA*)&osvi);
            bool bNT = (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId);    
            s_pFnGetMonitorInfo = (LPGETMONITORINFO) (bNT ? GetProcAddress(hUser32,"GetMonitorInfoW") : GetProcAddress(hUser32,"GetMonitorInfoA"));
        }
    }

    if( s_pFnGetMonitorInfo ) 
        return s_pFnGetMonitorInfo(hMonitor, lpMonitorInfo);

    RECT rcWork;
    if ((hMonitor == DXUT_PRIMARY_MONITOR) && lpMonitorInfo && (lpMonitorInfo->cbSize >= sizeof(MONITORINFO)) && SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWork, 0))
    {
        lpMonitorInfo->rcMonitor.left = 0;
        lpMonitorInfo->rcMonitor.top  = 0;
        lpMonitorInfo->rcMonitor.right  = GetSystemMetrics(SM_CXSCREEN);
        lpMonitorInfo->rcMonitor.bottom = GetSystemMetrics(SM_CYSCREEN);
        lpMonitorInfo->rcWork = rcWork;
        lpMonitorInfo->dwFlags = MONITORINFOF_PRIMARY;
        return TRUE;
    }
    return FALSE;
}


HMONITOR DXUTMonitorFromWindow(HWND hWnd, DWORD dwFlags)
{
    static bool s_bInited = false;
    static LPMONITORFROMWINDOW s_pFnGetMonitorFronWindow = NULL;
    if( !s_bInited )        
    {
        s_bInited = true;
        HMODULE hUser32 = GetModuleHandle( L"USER32" );
        if (hUser32 ) s_pFnGetMonitorFronWindow = (LPMONITORFROMWINDOW) GetProcAddress(hUser32,"MonitorFromWindow");
    }

    if( s_pFnGetMonitorFronWindow ) 
        return s_pFnGetMonitorFronWindow(hWnd, dwFlags);
    if (dwFlags & (MONITOR_DEFAULTTOPRIMARY | MONITOR_DEFAULTTONEAREST))
        return DXUT_PRIMARY_MONITOR;
    return NULL;
}


//--------------------------------------------------------------------------------------
// Get the desktop resolution of an adapter. This isn't the same as the current resolution 
// from GetAdapterDisplayMode since the device might be fullscreen 
//--------------------------------------------------------------------------------------
void DXUTGetDesktopResolution( UINT AdapterOrdinal, UINT* pWidth, UINT* pHeight )
{
    CD3DEnumeration* pd3dEnum = DXUTGetEnumeration();
    CD3DEnumAdapterInfo* pAdapterInfo = pd3dEnum->GetAdapterInfo( AdapterOrdinal );                       
    DEVMODE devMode;
    ZeroMemory( &devMode, sizeof(DEVMODE) );
    devMode.dmSize = sizeof(DEVMODE);
    WCHAR strDeviceName[256];
    MultiByteToWideChar( CP_ACP, 0, pAdapterInfo->AdapterIdentifier.DeviceName, -1, strDeviceName, 256 );
    strDeviceName[255] = 0;
    EnumDisplaySettings( strDeviceName, ENUM_REGISTRY_SETTINGS, &devMode );
    
    if( pWidth )
        *pWidth = devMode.dmPelsWidth;
    if( pHeight )
        *pHeight = devMode.dmPelsHeight;
}


//--------------------------------------------------------------------------------------
IDirect3DDevice9* DXUTCreateRefDevice( HWND hWnd, bool bNullRef )
{
    HRESULT hr;
    IDirect3D9* pD3D = DXUT_Dynamic_Direct3DCreate9( D3D_SDK_VERSION );
    if( NULL == pD3D )
        return NULL;

    D3DDISPLAYMODE Mode;
    pD3D->GetAdapterDisplayMode(0, &Mode);

    D3DPRESENT_PARAMETERS pp;
    ZeroMemory( &pp, sizeof(D3DPRESENT_PARAMETERS) );
    pp.BackBufferWidth  = 1;
    pp.BackBufferHeight = 1;
    pp.BackBufferFormat = Mode.Format;
    pp.BackBufferCount  = 1;
    pp.SwapEffect       = D3DSWAPEFFECT_COPY;
    pp.Windowed         = TRUE;
    pp.hDeviceWindow    = hWnd;

    IDirect3DDevice9* pd3dDevice = NULL;
    hr = pD3D->CreateDevice( D3DADAPTER_DEFAULT, bNullRef ? D3DDEVTYPE_NULLREF : D3DDEVTYPE_REF,
                             hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &pd3dDevice );

    SAFE_RELEASE( pD3D );
    return pd3dDevice;
}


typedef DWORD (WINAPI* LPXINPUTGETSTATE)(DWORD dwUserIndex, XINPUT_STATE* pState );
typedef DWORD (WINAPI* LPXINPUTSETSTATE)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration );
typedef DWORD (WINAPI* LPXINPUTGETCAPABILITIES)( DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities );
typedef void  (WINAPI* LPXINPUTENABLE)(BOOL bEnable);
 

//--------------------------------------------------------------------------------------
// Helper function to launch the Media Center UI after the program terminates
//--------------------------------------------------------------------------------------
bool DXUTReLaunchMediaCenter()
{
    // Skip if not running on a Media Center
    if( GetSystemMetrics( 87 ) == 0 ) //  SM_MEDIACENTER == 87, but is only defined if _WIN32_WINNT >= 0x0501
        return false;
 
    // Get the path to Media Center
    WCHAR szExpandedPath[MAX_PATH];
    if( !ExpandEnvironmentStrings( L"%SystemRoot%\\ehome\\ehshell.exe", szExpandedPath, MAX_PATH) )
        return false;

    // Skip if ehshell.exe doesn't exist
    if( GetFileAttributes( szExpandedPath ) == 0xFFFFFFFF )
        return false;
 
    // Launch ehshell.exe 
    INT_PTR result = (INT_PTR)ShellExecute( NULL, TEXT("open"), szExpandedPath, NULL, NULL, SW_SHOWNORMAL);
    return (result > 32);
}
