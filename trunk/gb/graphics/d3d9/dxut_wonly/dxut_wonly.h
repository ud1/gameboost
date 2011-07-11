//--------------------------------------------------------------------------------------
// File: DXUT.h
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#define DXUT_H


#ifndef STRICT
#define STRICT
#endif

// If app hasn't choosen, set to work with Windows 98, Windows Me, Windows 2000, Windows XP and beyond
#ifndef WINVER
#define WINVER         0x0410
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410 
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0500 
#endif


 

#if 0
#ifdef _DEBUG
#pragma comment ( lib , "j:\\!!MYCODE\\ce\\dxut_wonly\\project_lib\\Debug\\dxut_wonly.lib" )
#else
#pragma comment ( lib , "j:\\!!MYCODE\\ce\\dxut_wonly\\project_lib\\Release\\dxut_wonly.lib" )
#endif
#endif
 


// library
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )

#ifdef DXUT_D3DX9
#if defined(DEBUG) || defined(_DEBUG)
  #pragma comment( lib, "d3dx9d.lib" )
#else
  #pragma comment( lib, "d3dx9.lib" )
#endif
#endif

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

#pragma  warning(disable : 4995)

#include <windows.h>
#include <assert.h>
#include <wchar.h>
#include <mmsystem.h>
#include <commctrl.h> // for InitCommonControls() 
#include <shellapi.h> // for ExtractIcon()
#include <new.h>      // for placement new
#include <math.h>      
#include <limits.h>      
#include <stdio.h>
#include <XInput.h> // Header for XInput APIs



// CRT's memory leak detection
#if defined(DEBUG) || defined(_DEBUG)
      #include <crtdbg.h>
#endif


// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

// Direct3D includes
#include <d3d9.h>

#ifdef DXUT_D3DX9
#include <d3dx9.h>
#endif

#include <dxerr.h>


// DirectSound includes
#include <mmsystem.h>
#include <mmreg.h>
//#include <dsound.h>

// strsafe.h deprecates old unsecure string functions.  If you 
// really do not want to it to (not recommended), then uncomment the next line 
//#define STRSAFE_NO_DEPRECATE

#ifndef STRSAFE_NO_DEPRECATE
#pragma deprecated("strncpy")
#pragma deprecated("wcsncpy")
#pragma deprecated("_tcsncpy")
#pragma deprecated("wcsncat")
#pragma deprecated("strncat")
#pragma deprecated("_tcsncat")
#endif

#pragma warning( disable : 4996 ) // disable deprecated warning
#include <tchar.h>
#include <strsafe.h>
#pragma warning( default : 4996 ) 




#if defined(DEBUG) || defined(_DEBUG)

#ifndef V
#define V(x)           { hr = x; if( FAILED(hr) ) { DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
#endif

#ifndef V_RETURN
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
#endif
#else
#ifndef V
#define V(x)           { hr = x; }
#endif

#ifndef V_RETURN
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif

#endif // #if defined(DEBUG) || defined(_DEBUG)


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif  


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

 

#ifndef UNICODE
  #error "DXUT requires a Unicode build. See the nearby comments for details"
#endif 


//--------------------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------------------
class CD3DEnumeration;

struct DXUTDeviceSettings
{
    UINT AdapterOrdinal;
    D3DDEVTYPE DeviceType;
    D3DFORMAT AdapterFormat;
    DWORD BehaviorFlags;
    D3DPRESENT_PARAMETERS pp;
};


//--------------------------------------------------------------------------------------
// Error codes
//--------------------------------------------------------------------------------------
#define DXUTERR_NODIRECT3D              MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0901)
#define DXUTERR_NOCOMPATIBLEDEVICES     MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0902)
#define DXUTERR_MEDIANOTFOUND           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0903)
#define DXUTERR_NONZEROREFCOUNT         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0904)
#define DXUTERR_CREATINGDEVICE          MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0905)
#define DXUTERR_RESETTINGDEVICE         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0906)
#define DXUTERR_CREATINGDEVICEOBJECTS   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0907)
#define DXUTERR_RESETTINGDEVICEOBJECTS  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0908)
#define DXUTERR_INCORRECTVERSION        MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0909)


//--------------------------------------------------------------------------------------
// Callback registration 
//--------------------------------------------------------------------------------------
typedef bool    (CALLBACK *LPDXUTCALLBACKISDEVICEACCEPTABLE)( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
typedef bool    (CALLBACK *LPDXUTCALLBACKMODIFYDEVICESETTINGS)( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
typedef HRESULT (CALLBACK *LPDXUTCALLBACKDEVICECREATED)( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
typedef HRESULT (CALLBACK *LPDXUTCALLBACKDEVICERESET)( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKDEVICEDESTROYED)( void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKDEVICELOST)( void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKFRAMEMOVE)( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKFRAMERENDER)( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKKEYBOARD)( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKMOUSE)( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext );
typedef LRESULT (CALLBACK *LPDXUTCALLBACKMSGPROC)( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
typedef void    (CALLBACK *LPDXUTCALLBACKTIMER)( UINT idEvent, void* pUserContext );

// Device callbacks
void DXUTSetCallbackDeviceCreated( LPDXUTCALLBACKDEVICECREATED pCallbackDeviceCreated, void* pUserContext = NULL );
void DXUTSetCallbackDeviceReset( LPDXUTCALLBACKDEVICERESET pCallbackDeviceReset, void* pUserContext = NULL );
void DXUTSetCallbackDeviceLost( LPDXUTCALLBACKDEVICELOST pCallbackDeviceLost, void* pUserContext = NULL );
void DXUTSetCallbackDeviceDestroyed( LPDXUTCALLBACKDEVICEDESTROYED pCallbackDeviceDestroyed, void* pUserContext = NULL );
void DXUTSetCallbackDeviceChanging( LPDXUTCALLBACKMODIFYDEVICESETTINGS pCallbackModifyDeviceSettings, void* pUserContext = NULL );
 

//-----------------------------------------------------------------
// A growable array
//-----------------------------------------------------------------
template< typename TYPE >
class CGrowableArray
{
public:
	CGrowableArray()  
	{ 
		m_pData = NULL; 
		m_nSize = 0; 
		m_nMaxSize = 0; 
	}
	CGrowableArray( const CGrowableArray<TYPE>& a ) 
	{ 
		for( int i=0; i < a.m_nSize; i++ ) 
			Add( a.m_pData[i] ); 
	}

	~CGrowableArray() 
	{ 
		RemoveAll(); 
	}

	const TYPE& operator[]( int nIndex ) const 
	{ 
		return GetAt( nIndex ); 
	}

	TYPE& operator[]( int nIndex ) 
	{ 
		return GetAt( nIndex ); 
	}

	CGrowableArray& operator=( const CGrowableArray<TYPE>& a ) 
	{ 
		if( this == &a ) return *this; RemoveAll(); 
		for( int i=0; i < a.m_nSize; i++ ) Add( a.m_pData[i] ); 
		return *this; 
	}

	HRESULT SetSize( int nNewMaxSize );
	HRESULT Add( const TYPE& value );
	HRESULT Insert( int nIndex, const TYPE& value );
	HRESULT SetAt( int nIndex, const TYPE& value );
	TYPE&   GetAt( int nIndex ) { assert( nIndex >= 0 && nIndex < m_nSize ); return m_pData[nIndex]; }
	int     GetSize() const { return m_nSize; }
	TYPE*   GetData() { return m_pData; }
	bool    Contains( const TYPE& value ){ return ( -1 != IndexOf( value ) ); }

	int     IndexOf( const TYPE& value ) { return ( m_nSize > 0 ) ? IndexOf( value, 0, m_nSize ) : -1; }
	int     IndexOf( const TYPE& value, int iStart ) { return IndexOf( value, iStart, m_nSize - iStart ); }
	int     IndexOf( const TYPE& value, int nIndex, int nNumElements );

	int     LastIndexOf( const TYPE& value ) { return ( m_nSize > 0 ) ? LastIndexOf( value, m_nSize-1, m_nSize ) : -1; }
	int     LastIndexOf( const TYPE& value, int nIndex ) { return LastIndexOf( value, nIndex, nIndex+1 ); }
	int     LastIndexOf( const TYPE& value, int nIndex, int nNumElements );

	HRESULT Remove( int nIndex );
	void    RemoveAll() { SetSize(0); }

protected:
	TYPE* m_pData;      // the actual array of data
	int m_nSize;        // # of elements (upperBound - 1)
	int m_nMaxSize;     // max allocated

	HRESULT SetSizeInternal( int nNewMaxSize );  // This version doesn't call ctor or dtor.
};




//-------------------------------------------------------
// Implementation of CGrowableArray
//-------------------------------------------------------

// This version doesn't call ctor or dtor.
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::SetSizeInternal( int nNewMaxSize )
{
	if( nNewMaxSize < 0 )
	{
		assert( false );
		return E_INVALIDARG;
	}

	if( nNewMaxSize == 0 )
	{
		// Shrink to 0 size & cleanup
		if( m_pData )
		{
			free( m_pData );
			m_pData = NULL;
		}

		m_nMaxSize = 0;
		m_nSize = 0;
	}
	else if( m_pData == NULL || nNewMaxSize > m_nMaxSize )
	{
		// Grow array
		int nGrowBy = ( m_nMaxSize == 0 ) ? 16 : m_nMaxSize;

		// Limit nGrowBy to keep m_nMaxSize less than INT_MAX
		if( (UINT)m_nMaxSize + (UINT)nGrowBy > (UINT)INT_MAX )
			nGrowBy = INT_MAX - m_nMaxSize;

		nNewMaxSize = __max( nNewMaxSize, m_nMaxSize + nGrowBy );

		// Verify that (nNewMaxSize * sizeof(TYPE)) is not greater than UINT_MAX or the realloc will overrun
		if( sizeof(TYPE) > UINT_MAX / (UINT)nNewMaxSize )
			return E_INVALIDARG;

		TYPE* pDataNew = (TYPE*) realloc( m_pData, nNewMaxSize * sizeof(TYPE) );
		if( pDataNew == NULL )
			return E_OUTOFMEMORY;

		m_pData = pDataNew;
		m_nMaxSize = nNewMaxSize;
	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::SetSize( int nNewMaxSize )
{
	int nOldSize = m_nSize;

	if( nOldSize > nNewMaxSize )
	{
		// Removing elements. Call dtor.

		for( int i = nNewMaxSize; i < nOldSize; ++i )
			m_pData[i].~TYPE();
	}

	// Adjust buffer.  Note that there's no need to check for error
	// since if it happens, nOldSize == nNewMaxSize will be true.)
	HRESULT hr = SetSizeInternal( nNewMaxSize );

	if( nOldSize < nNewMaxSize )
	{
		// Adding elements. Call ctor.

		for( int i = nOldSize; i < nNewMaxSize; ++i )
			::new (&m_pData[i]) TYPE;
	}

	return hr;
}


//--------------------------------------------------------------------------------------
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::Add( const TYPE& value )
{
	HRESULT hr;
	if( FAILED( hr = SetSizeInternal( m_nSize + 1 ) ) )
		return hr;

	// Construct the new element
	::new (&m_pData[m_nSize]) TYPE;

	// Assign
	m_pData[m_nSize] = value;
	++m_nSize;

	return S_OK;
}


//--------------------------------------------------------------------------------------
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::Insert( int nIndex, const TYPE& value )
{
	HRESULT hr;

	// Validate index
	if( nIndex < 0 || 
		nIndex > m_nSize )
	{
		assert( false );
		return E_INVALIDARG;
	}

	// Prepare the buffer
	if( FAILED( hr = SetSizeInternal( m_nSize + 1 ) ) )
		return hr;

	// Shift the array
	MoveMemory( &m_pData[nIndex+1], &m_pData[nIndex], sizeof(TYPE) * (m_nSize - nIndex) );

	// Construct the new element
	::new (&m_pData[nIndex]) TYPE;

	// Set the value and increase the size
	m_pData[nIndex] = value;
	++m_nSize;

	return S_OK;
}


//--------------------------------------------------------------------------------------
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::SetAt( int nIndex, const TYPE& value )
{
	// Validate arguments
	if( nIndex < 0 ||
		nIndex >= m_nSize )
	{
		assert( false );
		return E_INVALIDARG;
	}

	m_pData[nIndex] = value;
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Searches for the specified value and returns the index of the first occurrence
// within the section of the data array that extends from iStart and contains the 
// specified number of elements. Returns -1 if value is not found within the given 
// section.
//--------------------------------------------------------------------------------------
template< typename TYPE >
int CGrowableArray<TYPE>::IndexOf( const TYPE& value, int iStart, int nNumElements )
{
	// Validate arguments
	if( iStart < 0 || 
		iStart >= m_nSize ||
		nNumElements < 0 ||
		iStart + nNumElements > m_nSize )
	{
		assert( false );
		return -1;
	}

	// Search
	for( int i = iStart; i < (iStart + nNumElements); i++ )
	{
		if( value == m_pData[i] )
			return i;
	}

	// Not found
	return -1;
}


//--------------------------------------------------------------------------------------
// Searches for the specified value and returns the index of the last occurrence
// within the section of the data array that contains the specified number of elements
// and ends at iEnd. Returns -1 if value is not found within the given section.
//--------------------------------------------------------------------------------------
template< typename TYPE >
int CGrowableArray<TYPE>::LastIndexOf( const TYPE& value, int iEnd, int nNumElements )
{
	// Validate arguments
	if( iEnd < 0 || 
		iEnd >= m_nSize ||
		nNumElements < 0 ||
		iEnd - nNumElements < 0 )
	{
		assert( false );
		return -1;
	}

	// Search
	for( int i = iEnd; i > (iEnd - nNumElements); i-- )
	{
		if( value == m_pData[i] )
			return i;
	}

	// Not found
	return -1;
}



//--------------------------------------------------------------------------------------
template< typename TYPE >
HRESULT CGrowableArray<TYPE>::Remove( int nIndex )
{
	if( nIndex < 0 || 
		nIndex >= m_nSize )
	{
		assert( false );
		return E_INVALIDARG;
	}

	// Destruct the element to be removed
	m_pData[nIndex].~TYPE();

	// Compact the array and decrease the size
	MoveMemory( &m_pData[nIndex], &m_pData[nIndex+1], sizeof(TYPE) * (m_nSize - (nIndex+1)) );
	--m_nSize;

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
class CD3DEnumAdapterInfo;
class CD3DEnumDeviceInfo;
struct CD3DEnumDeviceSettingsCombo;
struct CD3DEnumDSMSConflict;





//--------------------------------------------------------------------------------------
// Enumerates available Direct3D adapters, devices, modes, etc.
// Use DXUTGetEnumeration() to access global instance
//--------------------------------------------------------------------------------------
class CD3DEnumeration
{
public:
    // These should be called before Enumerate(). 
    //
    // Use these calls and the IsDeviceAcceptable to control the contents of 
    // the enumeration object, which affects the device selection and the device settings dialog.
    void SetRequirePostPixelShaderBlending( bool bRequire ) { m_bRequirePostPixelShaderBlending = bRequire; }
    void SetResolutionMinMax( UINT nMinWidth, UINT nMinHeight, UINT nMaxWidth, UINT nMaxHeight );  
    void SetRefreshMinMax( UINT nMin, UINT nMax );
    void SetMultisampleQualityMax( UINT nMax );    
    void GetPossibleVertexProcessingList( bool* pbSoftwareVP, bool* pbHardwareVP, bool* pbPureHarewareVP, bool* pbMixedVP );
    void SetPossibleVertexProcessingList( bool bSoftwareVP, bool bHardwareVP, bool bPureHarewareVP, bool bMixedVP );
    CGrowableArray<D3DFORMAT>* GetPossibleDepthStencilFormatList();   
    CGrowableArray<D3DMULTISAMPLE_TYPE>* GetPossibleMultisampleTypeList();   
    CGrowableArray<UINT>* GetPossiblePresentIntervalList();
    void ResetPossibleDepthStencilFormats();
    void ResetPossibleMultisampleTypeList();
    void ResetPossiblePresentIntervalList();

    // Call Enumerate() to enumerate available D3D adapters, devices, modes, etc.
    HRESULT Enumerate( IDirect3D9* pD3D = NULL,
                       LPDXUTCALLBACKISDEVICEACCEPTABLE IsDeviceAcceptableFunc = NULL,
                       void* pIsDeviceAcceptableFuncUserContext = NULL );

    // These should be called after Enumerate() is called
    CGrowableArray<CD3DEnumAdapterInfo*>*   GetAdapterInfoList();  
    CD3DEnumAdapterInfo*                    GetAdapterInfo( UINT AdapterOrdinal );  
    CD3DEnumDeviceInfo*                     GetDeviceInfo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType );    
    CD3DEnumDeviceSettingsCombo*            GetDeviceSettingsCombo( DXUTDeviceSettings* pDeviceSettings ) { return GetDeviceSettingsCombo( pDeviceSettings->AdapterOrdinal, pDeviceSettings->DeviceType, pDeviceSettings->AdapterFormat, pDeviceSettings->pp.BackBufferFormat, pDeviceSettings->pp.Windowed ); }
    CD3DEnumDeviceSettingsCombo*            GetDeviceSettingsCombo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL Windowed );  

    ~CD3DEnumeration();

private:
    friend CD3DEnumeration* DXUTGetEnumeration(); 

    // Use DXUTGetEnumeration() to access global instance
    CD3DEnumeration();

    IDirect3D9* m_pD3D;                                    
    LPDXUTCALLBACKISDEVICEACCEPTABLE m_IsDeviceAcceptableFunc;
    void* m_pIsDeviceAcceptableFuncUserContext;
    bool m_bRequirePostPixelShaderBlending;
    CGrowableArray<D3DFORMAT> m_DepthStecilPossibleList;
    CGrowableArray<D3DMULTISAMPLE_TYPE> m_MultiSampleTypeList;
    CGrowableArray<UINT> m_PresentIntervalList;

    bool m_bSoftwareVP;
    bool m_bHardwareVP;
    bool m_bPureHarewareVP;
    bool m_bMixedVP;

    UINT m_nMinWidth;
    UINT m_nMaxWidth;
    UINT m_nMinHeight;
    UINT m_nMaxHeight;
    UINT m_nRefreshMin;
    UINT m_nRefreshMax;
    UINT m_nMultisampleQualityMax;

    // Array of CD3DEnumAdapterInfo* with unique AdapterOrdinals
    CGrowableArray<CD3DEnumAdapterInfo*> m_AdapterInfoList;  

    HRESULT EnumerateDevices( CD3DEnumAdapterInfo* pAdapterInfo, CGrowableArray<D3DFORMAT>* pAdapterFormatList );
    HRESULT EnumerateDeviceCombos( CD3DEnumAdapterInfo* pAdapterInfo, CD3DEnumDeviceInfo* pDeviceInfo, CGrowableArray<D3DFORMAT>* pAdapterFormatList );
    void BuildDepthStencilFormatList( CD3DEnumDeviceSettingsCombo* pDeviceCombo );
    void BuildMultiSampleTypeList( CD3DEnumDeviceSettingsCombo* pDeviceCombo );
    void BuildDSMSConflictList( CD3DEnumDeviceSettingsCombo* pDeviceCombo );
    void BuildPresentIntervalList( CD3DEnumDeviceInfo* pDeviceInfo, CD3DEnumDeviceSettingsCombo* pDeviceCombo );
    void ClearAdapterInfoList();
};

CD3DEnumeration* DXUTGetEnumeration(); 


//--------------------------------------------------------------------------------------
// A class describing an adapter which contains a unique adapter ordinal 
// that is installed on the system
//--------------------------------------------------------------------------------------
class CD3DEnumAdapterInfo
{
public:
    ~CD3DEnumAdapterInfo();

    UINT AdapterOrdinal;
    D3DADAPTER_IDENTIFIER9 AdapterIdentifier;
    WCHAR szUniqueDescription[256];

    CGrowableArray<D3DDISPLAYMODE> displayModeList; // Array of supported D3DDISPLAYMODEs
    CGrowableArray<CD3DEnumDeviceInfo*> deviceInfoList; // Array of CD3DEnumDeviceInfo* with unique supported DeviceTypes
};


//--------------------------------------------------------------------------------------
// A class describing a Direct3D device that contains a 
//       unique supported device type 
//--------------------------------------------------------------------------------------
class CD3DEnumDeviceInfo
{
public:
    ~CD3DEnumDeviceInfo();

    UINT AdapterOrdinal;
    D3DDEVTYPE DeviceType;
    D3DCAPS9 Caps;

    // List of CD3DEnumDeviceSettingsCombo* with a unique set 
    // of AdapterFormat, BackBufferFormat, and Windowed
    CGrowableArray<CD3DEnumDeviceSettingsCombo*> deviceSettingsComboList; 
};


//--------------------------------------------------------------------------------------
// A struct describing device settings that contains a unique combination of 
// adapter format, back buffer format, and windowed that is compatible with a 
// particular Direct3D device and the app.
//--------------------------------------------------------------------------------------
struct CD3DEnumDeviceSettingsCombo
{
    UINT AdapterOrdinal;
    D3DDEVTYPE DeviceType;
    D3DFORMAT AdapterFormat;
    D3DFORMAT BackBufferFormat;
    BOOL Windowed;

    CGrowableArray<D3DFORMAT> depthStencilFormatList; // List of D3DFORMATs
    CGrowableArray<D3DMULTISAMPLE_TYPE> multiSampleTypeList; // List of D3DMULTISAMPLE_TYPEs
    CGrowableArray<DWORD> multiSampleQualityList; // List of number of quality levels for each multisample type
    CGrowableArray<UINT> presentIntervalList; // List of D3DPRESENT flags
    CGrowableArray<CD3DEnumDSMSConflict> DSMSConflictList; // List of CD3DEnumDSMSConflict

    CD3DEnumAdapterInfo* pAdapterInfo;
    CD3DEnumDeviceInfo* pDeviceInfo;
};


//--------------------------------------------------------------------------------------
// A depth/stencil buffer format that is incompatible with a
// multisample type.
//--------------------------------------------------------------------------------------
struct CD3DEnumDSMSConflict
{
    D3DFORMAT DSFormat;
    D3DMULTISAMPLE_TYPE MSType;
};

#ifndef INT_MAX
   #define INT_MAX       2147483647    /* maximum (signed) int value */
#endif

#ifndef UINT_MAX      
   #define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#endif
 

//--------------------------------------------------------------------------------------
// Performs timer operations
// Use DXUTGetGlobalTimer() to get the global instance
//--------------------------------------------------------------------------------------
class CDXUTTimer
{
public:
    CDXUTTimer();

    void Reset(); // resets the timer
    void Start(); // starts the timer
    void Stop();  // stop (or pause) the timer
    void Advance(); // advance the timer by 0.1 seconds
    double GetAbsoluteTime(); // get the absolute system time
    double GetTime(); // get the current time
    double GetElapsedTime(); // get the time that elapsed between Get*ElapsedTime() calls
    void GetTimeValues( double* pfTime, double* pfAbsoluteTime, float* pfElapsedTime ); // get all time values at once
    bool IsStopped(); // returns true if timer stopped

    // Limit the current thread to one processor (the current one). This ensures that timing code runs
    // on only one processor, and will not suffer any ill effects from power management.
    void LimitThreadAffinityToCurrentProc();

protected:
    LARGE_INTEGER GetAdjustedCurrentTime();

    bool m_bTimerStopped;
    LONGLONG m_llQPFTicksPerSec;
    
    LONGLONG m_llStopTime;
    LONGLONG m_llLastElapsedTime;
    LONGLONG m_llBaseTime;
};

CDXUTTimer* DXUTGetGlobalTimer();


//-----------------------------------------------------------------------------
// Resource cache for textures, fonts, meshs, and effects.  
// Use DXUTGetGlobalResourceCache() to access the global cache
//-----------------------------------------------------------------------------

enum DXUTCACHE_SOURCELOCATION { DXUTCACHE_LOCATION_FILE, DXUTCACHE_LOCATION_RESOURCE };

struct DXUTCache_Texture
{
    DXUTCACHE_SOURCELOCATION Location;
    WCHAR wszSource[MAX_PATH];
    HMODULE hSrcModule;
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    D3DRESOURCETYPE Type;
    IDirect3DBaseTexture9 *pTexture;
};

 
#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK  0x01

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08

 

//--------------------------------------------------------------------------------------
// Shared code for samples to ask user if they want to use a REF device or quit
//--------------------------------------------------------------------------------------
void DXUTDisplaySwitchingToREFWarning();

//--------------------------------------------------------------------------------------
// Tries to finds a media file by searching in common locations
//--------------------------------------------------------------------------------------
HRESULT DXUTFindDXSDKMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename );
HRESULT DXUTSetMediaSearchPath( LPCWSTR strPath );
LPCWSTR DXUTGetMediaSearchPath();


//--------------------------------------------------------------------------------------
// Returns the string for the given D3DFORMAT.
//       bWithPrefix determines whether the string should include the "D3DFMT_"
//--------------------------------------------------------------------------------------
LPCWSTR DXUTD3DFormatToString( D3DFORMAT format, bool bWithPrefix );

//--------------------------------------------------------------------------------------
// Helper function to launch the Media Center UI after the program terminates
//--------------------------------------------------------------------------------------
bool DXUTReLaunchMediaCenter();

//--------------------------------------------------------------------------------------
// Debug printing support
// See dxerr.h for more debug printing support
//--------------------------------------------------------------------------------------
void DXUTOutputDebugStringW( LPCWSTR strMsg, ... );
void DXUTOutputDebugStringA( LPCSTR strMsg, ... );
HRESULT WINAPI DXUTTrace( const CHAR* strFile, DWORD dwLine, HRESULT hr, const WCHAR* strMsg, bool bPopMsgBox );
void DXUTTraceDecl( D3DVERTEXELEMENT9 decl[65] );
WCHAR* DXUTTraceD3DDECLUSAGEtoString( BYTE u );
WCHAR* DXUTTraceD3DDECLMETHODtoString( BYTE m );
WCHAR* DXUTTraceD3DDECLTYPEtoString( BYTE t );

#ifdef UNICODE
#define DXUTOutputDebugString DXUTOutputDebugStringW
#else
#define DXUTOutputDebugString DXUTOutputDebugStringA
#endif

// These macros are very similar to dxerr's but it special cases the HRESULT defined
// by DXUT to pop better message boxes. 
#if defined(DEBUG) || defined(_DEBUG)
#define DXUT_ERR(str,hr)           DXUTTrace( __FILE__, (DWORD)__LINE__, hr, str, false )
#define DXUT_ERR_MSGBOX(str,hr)    DXUTTrace( __FILE__, (DWORD)__LINE__, hr, str, true )
#define DXUTTRACE                  DXUTOutputDebugString
#else
#define DXUT_ERR(str,hr)           (hr)
#define DXUT_ERR_MSGBOX(str,hr)    (hr)
#define DXUTTRACE                  (__noop)
#endif


//--------------------------------------------------------------------------------------
// Direct3D9 dynamic linking support -- calls top-level D3D9 APIs with graceful
// failure if APIs are not present.
//--------------------------------------------------------------------------------------

IDirect3D9 * WINAPI DXUT_Dynamic_Direct3DCreate9(UINT SDKVersion);
int WINAPI DXUT_Dynamic_D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName );
int WINAPI DXUT_Dynamic_D3DPERF_EndEvent( void );
void WINAPI DXUT_Dynamic_D3DPERF_SetMarker( D3DCOLOR col, LPCWSTR wszName );
void WINAPI DXUT_Dynamic_D3DPERF_SetRegion( D3DCOLOR col, LPCWSTR wszName );
BOOL WINAPI DXUT_Dynamic_D3DPERF_QueryRepeatFrame( void );
void WINAPI DXUT_Dynamic_D3DPERF_SetOptions( DWORD dwOptions );
DWORD WINAPI DXUT_Dynamic_D3DPERF_GetStatus( void );


//--------------------------------------------------------------------------------------
// Profiling/instrumentation support
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Some D3DPERF APIs take a color that can be used when displaying user events in 
// performance analysis tools.  The following constants are provided for your 
// convenience, but you can use any colors you like.
//--------------------------------------------------------------------------------------
const D3DCOLOR DXUT_PERFEVENTCOLOR  = D3DCOLOR_XRGB(200,100,100);
const D3DCOLOR DXUT_PERFEVENTCOLOR2 = D3DCOLOR_XRGB(100,200,100);
const D3DCOLOR DXUT_PERFEVENTCOLOR3 = D3DCOLOR_XRGB(100,100,200);

//--------------------------------------------------------------------------------------
// The following macros provide a convenient way for your code to call the D3DPERF 
// functions only when PROFILE is defined.  If PROFILE is not defined (as for the final 
// release version of a program), these macros evaluate to nothing, so no detailed event
// information is embedded in your shipping program.  It is recommended that you create
// and use three build configurations for your projects:
//     Debug (nonoptimized code, asserts active, PROFILE defined to assist debugging)
//     Profile (optimized code, asserts disabled, PROFILE defined to assist optimization)
//     Release (optimized code, asserts disabled, PROFILE not defined)
//--------------------------------------------------------------------------------------
#ifdef PROFILE
// PROFILE is defined, so these macros call the D3DPERF functions
#define DXUT_BeginPerfEvent( color, pstrMessage )   DXUT_Dynamic_D3DPERF_BeginEvent( color, pstrMessage )
#define DXUT_EndPerfEvent()                         DXUT_Dynamic_D3DPERF_EndEvent()
#define DXUT_SetPerfMarker( color, pstrMessage )    DXUT_Dynamic_D3DPERF_SetMarker( color, pstrMessage )
#else
// PROFILE is not defined, so these macros do nothing
#define DXUT_BeginPerfEvent( color, pstrMessage )   (__noop)
#define DXUT_EndPerfEvent()                         (__noop)
#define DXUT_SetPerfMarker( color, pstrMessage )    (__noop)
#endif // #ifdef PROFILE

//--------------------------------------------------------------------------------------
// CDXUTPerfEventGenerator is a helper class that makes it easy to attach begin and end
// events to a block of code.  Simply define a CDXUTPerfEventGenerator variable anywhere 
// in a block of code, and the class's constructor will call DXUT_BeginPerfEvent when 
// the block of code begins, and the class's destructor will call DXUT_EndPerfEvent when 
// the block ends.
//--------------------------------------------------------------------------------------
class CDXUTPerfEventGenerator
{
public:
    CDXUTPerfEventGenerator( D3DCOLOR color, LPCWSTR pstrMessage ) { DXUT_BeginPerfEvent( color, pstrMessage ); }
    ~CDXUTPerfEventGenerator( void ) { DXUT_EndPerfEvent(); }
};


//--------------------------------------------------------------------------------------
// Multimon handling to support OSes with or without multimon API support.  
// Purposely avoiding the use of multimon.h so DXUT.lib doesn't require 
// COMPILE_MULTIMON_STUBS and cause complication with MFC or other users of multimon.h
//--------------------------------------------------------------------------------------
#ifndef MONITOR_DEFAULTTOPRIMARY
    #define MONITORINFOF_PRIMARY        0x00000001
    #define MONITOR_DEFAULTTONULL       0x00000000
    #define MONITOR_DEFAULTTOPRIMARY    0x00000001
    #define MONITOR_DEFAULTTONEAREST    0x00000002
    typedef struct tagMONITORINFO
    {
        DWORD   cbSize;
        RECT    rcMonitor;
        RECT    rcWork;
        DWORD   dwFlags;
    } MONITORINFO, *LPMONITORINFO;
    typedef struct tagMONITORINFOEXW : public tagMONITORINFO
    {
        WCHAR       szDevice[CCHDEVICENAME];
    } MONITORINFOEXW, *LPMONITORINFOEXW;
    typedef MONITORINFOEXW MONITORINFOEX;
    typedef LPMONITORINFOEXW LPMONITORINFOEX;
#endif

HMONITOR DXUTMonitorFromWindow( HWND hWnd, DWORD dwFlags );
BOOL     DXUTGetMonitorInfo( HMONITOR hMonitor, LPMONITORINFO lpMonitorInfo );
void     DXUTGetDesktopResolution( UINT AdapterOrdinal, UINT* pWidth, UINT* pHeight );


//--------------------------------------------------------------------------------------
// Creates a REF or NULLREF device and returns that device.  The caller should call
// Release() when done with the device.
//--------------------------------------------------------------------------------------
IDirect3DDevice9* DXUTCreateRefDevice( HWND hWnd, bool bNullRef = true );

 

// Frame callbacks
void DXUTSetCallbackFrameMove( LPDXUTCALLBACKFRAMEMOVE pCallbackFrameMove, void* pUserContext = NULL );
void DXUTSetCallbackFrameRender( LPDXUTCALLBACKFRAMERENDER pCallbackFrameRender, void* pUserContext = NULL );

// Message callbacks
void DXUTSetCallbackKeyboard( LPDXUTCALLBACKKEYBOARD pCallbackKeyboard, void* pUserContext = NULL );
void DXUTSetCallbackMouse( LPDXUTCALLBACKMOUSE pCallbackMouse, bool bIncludeMouseMove = false, void* pUserContext = NULL );
void DXUTSetCallbackMsgProc( LPDXUTCALLBACKMSGPROC pCallbackMsgProc, void* pUserContext = NULL );


//--------------------------------------------------------------------------------------
// Initialization
//--------------------------------------------------------------------------------------
HRESULT DXUTInit( bool bParseCommandLine = true, bool bHandleDefaultHotkeys = true, bool bShowMsgBoxOnError = true, bool bHandleAltEnter = true );

// Choose either DXUTCreateWindow or DXUTSetWindow.  If using DXUTSetWindow, consider using DXUTStaticWndProc
HRESULT DXUTCreateWindow( const WCHAR* strWindowTitle = L"Direct3D Window", 
                          HINSTANCE hInstance = NULL, HICON hIcon = NULL, HMENU hMenu = NULL,
                          int x = CW_USEDEFAULT, int y = CW_USEDEFAULT );
HRESULT DXUTSetWindow( HWND hWndFocus, HWND hWndDeviceFullScreen, HWND hWndDeviceWindowed, bool bHandleMessages = true );
LRESULT CALLBACK DXUTStaticWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

// Choose either DXUTCreateDevice or DXUTSetDevice or DXUTCreateDeviceFromSettings
HRESULT DXUTCreateDevice( UINT AdapterOrdinal = D3DADAPTER_DEFAULT, bool bWindowed = true, 
                          int nSuggestedWidth = 0, int nSuggestedHeight = 0,
                          LPDXUTCALLBACKISDEVICEACCEPTABLE pCallbackIsDeviceAcceptable = NULL,
                          LPDXUTCALLBACKMODIFYDEVICESETTINGS pCallbackModifyDeviceSettings = NULL, 
                          void* pUserContext = NULL );
HRESULT DXUTCreateDeviceFromSettings( DXUTDeviceSettings* pDeviceSettings, bool bPreserveInput = false, bool bClipWindowToSingleAdapter = true );
HRESULT DXUTSetDevice( IDirect3DDevice9* pd3dDevice );

// Choose either DXUTMainLoop or implement your own main loop 
HRESULT DXUTMainLoop( HACCEL hAccel = NULL );

// If not using DXUTMainLoop consider using DXUTRender3DEnvironment
void DXUTRender3DEnvironment(); 


//--------------------------------------------------------------------------------------
// Finding valid device settings
//--------------------------------------------------------------------------------------
enum DXUT_MATCH_TYPE
{
    DXUTMT_IGNORE_INPUT = 0,  // Use the closest valid value to a default 
    DXUTMT_PRESERVE_INPUT,    // Use input without change, but may cause no valid device to be found
    DXUTMT_CLOSEST_TO_INPUT   // Use the closest valid value to the input 
};

struct DXUTMatchOptions
{
    DXUT_MATCH_TYPE eAdapterOrdinal;
    DXUT_MATCH_TYPE eDeviceType;
    DXUT_MATCH_TYPE eWindowed;
    DXUT_MATCH_TYPE eAdapterFormat;
    DXUT_MATCH_TYPE eVertexProcessing;
    DXUT_MATCH_TYPE eResolution;
    DXUT_MATCH_TYPE eBackBufferFormat;
    DXUT_MATCH_TYPE eBackBufferCount;
    DXUT_MATCH_TYPE eMultiSample;
    DXUT_MATCH_TYPE eSwapEffect;
    DXUT_MATCH_TYPE eDepthFormat;
    DXUT_MATCH_TYPE eStencilFormat;
    DXUT_MATCH_TYPE ePresentFlags;
    DXUT_MATCH_TYPE eRefreshRate;
    DXUT_MATCH_TYPE ePresentInterval;
};

HRESULT DXUTFindValidDeviceSettings( DXUTDeviceSettings* pOut, DXUTDeviceSettings* pIn = NULL, DXUTMatchOptions* pMatchOptions = NULL );


//--------------------------------------------------------------------------------------
// Common Tasks 
//--------------------------------------------------------------------------------------
void    DXUTSetCursorSettings( bool bShowCursorWhenFullScreen, bool bClipCursorWhenFullScreen );
void    DXUTSetMultimonSettings( bool bAutoChangeAdapter );

 // Controls the Windows key, and accessibility shortcut keys
void    DXUTSetShortcutKeySettings( bool bAllowWhenFullscreen = false, bool bAllowWhenWindowed = true );
void    DXUTSetWindowSettings( bool bCallDefWindowProc = true );
void    DXUTSetConstantFrameTime( bool bConstantFrameTime, float fTimePerFrame = 0.0333f );
HRESULT DXUTSetTimer( LPDXUTCALLBACKTIMER pCallbackTimer, float fTimeoutInSecs = 1.0f, UINT* pnIDEvent = NULL, void* pCallbackUserContext = NULL );
HRESULT DXUTKillTimer( UINT nIDEvent );
HRESULT DXUTToggleFullScreen();
HRESULT DXUTToggleREF();
void    DXUTPause( bool bPauseTime, bool bPauseRendering );
void    DXUTResetFrameworkState();
void    DXUTShutdown( int nExitCode = 0 );


HRESULT WINAPI DXUTTrace( const CHAR* strFile, DWORD dwLine, HRESULT hr,
						 const WCHAR* strMsg, bool bPopMsgBox );

//--------------------------------------------------------------------------------------
// State Retrieval  
//--------------------------------------------------------------------------------------
IDirect3D9*             DXUTGetD3DObject(); // Does not addref unlike typical Get* APIs
IDirect3DDevice9*       DXUTGetD3DDevice(); // Does not addref unlike typical Get* APIs
DXUTDeviceSettings      DXUTGetDeviceSettings(); 
D3DPRESENT_PARAMETERS   DXUTGetPresentParameters();
const D3DSURFACE_DESC*  DXUTGetBackBufferSurfaceDesc();
const D3DCAPS9*         DXUTGetDeviceCaps();
HINSTANCE               DXUTGetHINSTANCE();
HWND                    DXUTGetHWND();
HWND                    DXUTGetHWNDFocus();
HWND                    DXUTGetHWNDDeviceFullScreen();
HWND                    DXUTGetHWNDDeviceWindowed();
RECT                    DXUTGetWindowClientRect();
// Useful for returning to windowed mode with 
// the same resolution as before toggle to full screen mode
RECT                    DXUTGetWindowClientRectAtModeChange(); 

 // Useful for returning to full screen mode with 
 // the same resolution as before toggle to windowed mode
RECT                    DXUTGetFullsceenClientRectAtModeChange();
double                  DXUTGetTime();
float                   DXUTGetElapsedTime();
bool                    DXUTIsWindowed();
float                   DXUTGetFPS();
LPCWSTR                 DXUTGetWindowTitle();
LPCWSTR                 DXUTGetFrameStats( bool bIncludeFPS = false );
LPCWSTR                 DXUTGetDeviceStats();
bool                    DXUTIsRenderingPaused();
bool                    DXUTIsTimePaused();
bool                    DXUTIsActive();
int                     DXUTGetExitCode();
bool                    DXUTGetShowMsgBoxOnError();
bool                    DXUTGetHandleDefaultHotkeys();

// Pass a virtual-key code, ex. VK_F1, 'A', VK_RETURN, VK_LSHIFT, etc
bool                    DXUTIsKeyDown( BYTE vKey ); 

// Pass a virtual-key code: VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2
bool                    DXUTIsMouseButtonDown( BYTE vButton );
// Returns true if -automation parameter is used to launch the app
bool                    DXUTGetAutomation();  


// ks777
void DXUTCleanup3DEnvironment( bool bReleaseSettings = true);



//#endif // #ifndef DXUT_H
