#include "stdafx.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h>
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>
#include <gb/macro.h>





//--------------------------------------------------------------------------------------
DialogResourceManager::DialogResourceManager()
{
	m_pd3dDevice = NULL;
	m_pStateBlock = NULL;
	m_pSprite = NULL;
}


//--------------------------------------------------------------------------------------
DialogResourceManager::~DialogResourceManager()
{
	int i;
	for( i=0; i < m_FontCache.GetSize(); i++ )
	{
		FontNode* pFontNode = m_FontCache.GetAt( i );
		GB_SAFE_DEL_OBJ( pFontNode );
	}
	m_FontCache.RemoveAll();   

	for( i=0; i < m_TextureCache.GetSize(); i++ )
	{
		TextureNode* pTextureNode = m_TextureCache.GetAt( i );
		GB_SAFE_DEL_OBJ( pTextureNode );
	}
	m_TextureCache.RemoveAll();   

	UniBuffer::Uninitialize();
	IMEEditBox::Uninitialize();
}


//--------------------------------------------------------------------------------------
HRESULT DialogResourceManager::OnCreateDevice( LPDIRECT3DDEVICE9 pd3dDevice )
{
	HRESULT hr = S_OK;
	int i=0;

	setGlobalDevice(pd3dDevice);

	m_pd3dDevice = pd3dDevice;

	for( i=0; i < m_FontCache.GetSize(); i++ )
	{
		hr = CreateFont( i );
		if( FAILED(hr) )
			return hr;
	}

	for( i=0; i < m_TextureCache.GetSize(); i++ )
	{
		hr = CreateTexture( i );
		if( FAILED(hr) )
			return hr;
	}

	hr = D3DXCreateSprite( pd3dDevice, &m_pSprite );
	if( FAILED(hr) )
		return MYUT_ERR( L"D3DXCreateSprite", hr );

	// Call IMEEditBox's StaticOnCreateDevice()
	// to initialize certain window-dependent data.
	IMEEditBox::StaticOnCreateDevice();

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT DialogResourceManager::OnResetDevice()
{
	HRESULT hr = S_OK;

	for( int i=0; i < m_FontCache.GetSize(); i++ )
	{
		FontNode* pFontNode = m_FontCache.GetAt( i );

		if( pFontNode->pFont )
			pFontNode->pFont->OnResetDevice();
	}

	if( m_pSprite )
		m_pSprite->OnResetDevice();

	assert( getGlobalDevice() );
	IDirect3DDevice9* pd3dDevice =  getGlobalDevice(); 

	V_RETURN( pd3dDevice->CreateStateBlock( D3DSBT_ALL, &m_pStateBlock ) );

	return S_OK;
}

//--------------------------------------------------------------------------------------
bool DialogResourceManager::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// Let the IMEEditBox's static message proc handle the msg.
	// This is because some IME messages must be handled to ensure
	// proper functionalities and the static msg proc ensures that
	// this happens even if no control has the input focus.
	if( IMEEditBox::StaticMsgProc( uMsg, wParam, lParam ) )
		return true;

	return false;
}


//--------------------------------------------------------------------------------------
void DialogResourceManager::OnLostDevice()
{
	for( int i=0; i < m_FontCache.GetSize(); i++ )
	{
		FontNode* pFontNode = m_FontCache.GetAt( i );

		if( pFontNode->pFont )
			pFontNode->pFont->OnLostDevice();
	}

	if( m_pSprite )
		m_pSprite->OnLostDevice();

	GB_SAFE_REL( m_pStateBlock  );
}


//--------------------------------------------------------------------------------------
void DialogResourceManager::OnDestroyDevice()
{
	int i=0; 

	m_pd3dDevice = NULL;

	// Release the resources but don't clear the cache, as these will need to be
	// recreated if the device is recreated
	for( i=0; i < m_FontCache.GetSize(); i++ )
	{
		FontNode* pFontNode = m_FontCache.GetAt( i );
		GB_SAFE_REL( pFontNode->pFont );
	}

	for( i=0; i < m_TextureCache.GetSize(); i++ )
	{
		TextureNode* pTextureNode = m_TextureCache.GetAt( i );
		GB_SAFE_REL( pTextureNode->pTexture );
	}

	GB_SAFE_REL( m_pSprite );
}


//--------------------------------------------------------------------------------------
bool DialogResourceManager::RegisterDialog( Dialog *pDialog )
{
	// Check that the dialog isn't already registered.
	for( int i = 0; i < m_Dialogs.GetSize(); ++i )
		if( m_Dialogs.GetAt( i ) == pDialog )
			return true;

	// Add to the list.
	if( FAILED( m_Dialogs.Add( pDialog ) ) )
		return false;

	// Set up next and prev pointers.
	if( m_Dialogs.GetSize() > 1 )
		m_Dialogs[m_Dialogs.GetSize() - 2]->SetNextDialog( pDialog );
	m_Dialogs[m_Dialogs.GetSize() - 1]->SetNextDialog( m_Dialogs[0] );

	return true;
}


//--------------------------------------------------------------------------------------
void DialogResourceManager::UnregisterDialog( Dialog *pDialog )
{
	// Search for the dialog in the list.
	for( int i = 0; i < m_Dialogs.GetSize(); ++i )
		if( m_Dialogs.GetAt( i ) == pDialog )
		{
			m_Dialogs.Remove( i );
			if( m_Dialogs.GetSize() > 0 )
			{
				int l, r;

				if( 0 == i )
					l = m_Dialogs.GetSize() - 1;
				else
					l = i - 1;

				if( m_Dialogs.GetSize() == i )
					r = 0;
				else
					r = i;

				m_Dialogs[l]->SetNextDialog( m_Dialogs[r] );
			}
			return;
		}
}


//--------------------------------------------------------------------------------------
void DialogResourceManager::EnableKeyboardInputForAllDialogs()
{
	// Enable keyboard input for all registered dialogs
	for( int i = 0; i < m_Dialogs.GetSize(); ++i )
		m_Dialogs[i]->EnableKeyboardInput( true );
}

// dialogresourcemanager

//--------------------------------------------------------------------------------------
int DialogResourceManager::AddFont( LPCWSTR strFaceName, LONG height, LONG weight )
{
	// See if this font already exists
	for( int i=0; i < m_FontCache.GetSize(); i++ )
	{
		FontNode* pFontNode = m_FontCache.GetAt(i);
		size_t nLen = 0;
		StringCchLength( strFaceName, MAX_PATH, &nLen );        
		if( 0 == _wcsnicmp( pFontNode->strFace, strFaceName, nLen ) &&
			pFontNode->nHeight == height &&
			pFontNode->nWeight == weight )
		{
			return i;
		}
	}

	// Add a new font and try to create it
	FontNode* pNewFontNode = new FontNode();
	if( pNewFontNode == NULL )
		return -1;

	ZeroMemory( pNewFontNode, sizeof(FontNode) );
	StringCchCopy( pNewFontNode->strFace, MAX_PATH, strFaceName );
	pNewFontNode->nHeight = height;
	pNewFontNode->nWeight = weight;
	m_FontCache.Add( pNewFontNode );

	int iFont = m_FontCache.GetSize()-1;

	// If a device is available, try to create immediately
	if( m_pd3dDevice )
		CreateFont( iFont );

	return iFont;
}



//--------------------------------------------------------------------------------------
int DialogResourceManager::AddTexture( LPCWSTR strFilename )
{
	// See if this texture already exists
	for( int i=0; i < m_TextureCache.GetSize(); i++ )
	{
		TextureNode* pTextureNode = m_TextureCache.GetAt(i);
		size_t nLen = 0;
		StringCchLength( strFilename, MAX_PATH, &nLen );        
		if( pTextureNode->bFileSource &&  // Sources must match
			0 == _wcsnicmp( pTextureNode->strFilename, strFilename, nLen ) )
			return i;
	}

	// Add a new texture and try to create it
	TextureNode* pNewTextureNode = new TextureNode();
	if( pNewTextureNode == NULL )
		return -1;

	ZeroMemory( pNewTextureNode, sizeof(TextureNode) );
	pNewTextureNode->bFileSource = true;
	StringCchCopy( pNewTextureNode->strFilename, MAX_PATH, strFilename );

	m_TextureCache.Add( pNewTextureNode );

	int iTexture = m_TextureCache.GetSize()-1;

	// If a device is available, try to create immediately
	if( m_pd3dDevice )
		CreateTexture( iTexture );

	return iTexture;
}


//--------------------------------------------------------------------------------------
int DialogResourceManager::AddTexture( LPCWSTR strResourceName, HMODULE hResourceModule )
{
	// See if this texture already exists
	for( int i=0; i < m_TextureCache.GetSize(); i++ )
	{
		TextureNode* pTextureNode = m_TextureCache.GetAt(i);
		if( !pTextureNode->bFileSource &&      // Sources must match
			pTextureNode->hResourceModule == hResourceModule ) // Module handles must match
		{
			if( IS_INTRESOURCE( strResourceName ) )
			{
				// Integer-based ID
				if( (INT_PTR)strResourceName == pTextureNode->nResourceID )
					return i;
			}
			else
			{
				// String-based ID
				size_t nLen = 0;
				StringCchLength( strResourceName, MAX_PATH, &nLen );        
				if( 0 == _wcsnicmp( pTextureNode->strFilename, strResourceName, nLen ) )
					return i;
			}
		}
	}

	// Add a new texture and try to create it
	TextureNode* pNewTextureNode = new TextureNode();
	if( pNewTextureNode == NULL )
		return -1;

	ZeroMemory( pNewTextureNode, sizeof(TextureNode) );
	pNewTextureNode->hResourceModule = hResourceModule;
	if( IS_INTRESOURCE( strResourceName ) )
	{
		pNewTextureNode->nResourceID = (int)(size_t)strResourceName;
	}
	else
	{
		pNewTextureNode->nResourceID = 0;
		StringCchCopy( pNewTextureNode->strFilename, MAX_PATH, strResourceName );
	}

	m_TextureCache.Add( pNewTextureNode );

	int iTexture = m_TextureCache.GetSize()-1;

	// If a device is available, try to create immediately
	if( m_pd3dDevice )
		CreateTexture( iTexture );

	return iTexture;
}




//--------------------------------------------------------------------------------------
HRESULT DialogResourceManager::CreateFont( UINT iFont )
{
	HRESULT hr = S_OK;

	FontNode* pFontNode = m_FontCache.GetAt( iFont );

	GB_SAFE_REL( pFontNode->pFont );

	V_RETURN( D3DXCreateFont( m_pd3dDevice, pFontNode->nHeight, 0, pFontNode->nWeight, 1, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		pFontNode->strFace, &pFontNode->pFont ) );

	return S_OK;
}

//--------------------------------------------------------------------------------------
HRESULT DialogResourceManager::CreateTexture( UINT iTexture )
{
	HRESULT hr = S_OK;

	TextureNode* pTextureNode = m_TextureCache.GetAt( iTexture );


	D3DXIMAGE_INFO info;   

	if( !pTextureNode->bFileSource )
	{
		if( pTextureNode->nResourceID == 0xFFFF && pTextureNode->hResourceModule == (HMODULE) 0xFFFF )
		{
			hr = CreateGUITextureFromInternalArray( m_pd3dDevice, &pTextureNode->pTexture, &info );
			if( FAILED(hr) )
				return DXTRACE_ERR( L"D3DXCreateTextureFromFileInMemoryEx", hr );
		}
		else
		{
			LPCWSTR pID = pTextureNode->nResourceID ? (LPCWSTR)(size_t)pTextureNode->nResourceID : pTextureNode->strFilename;

			// Create texture from resource
			hr =  D3DXCreateTextureFromResourceEx( m_pd3dDevice, pTextureNode->hResourceModule, pID, D3DX_DEFAULT, D3DX_DEFAULT, 
				1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
				D3DX_DEFAULT, D3DX_DEFAULT, 0, 
				&info, NULL, &pTextureNode->pTexture );
			if( FAILED(hr) )
				return DXTRACE_ERR( L"D3DXCreateTextureFromResourceEx", hr );
		}
	}
	else
	{
		// Make sure there's a texture to create
		if( pTextureNode->strFilename[0] == 0 )
			return S_OK;

		// Find the texture on the hard drive
		WCHAR strPath[MAX_PATH];

#pragma message("ks777: WARN; COMMENTED CODE  "  __FILE__)
		//hr = MYUTFindDXSDKMediaFileCch( strPath, MAX_PATH, 
		//pTextureNode->strFilename );

		assert(false);


		if( FAILED(hr) )
		{
			return DXTRACE_ERR( L"MYUTFindDXSDKMediaFileCch", hr );
		}

		// Create texture from file
		hr =  D3DXCreateTextureFromFileEx( m_pd3dDevice, strPath, D3DX_DEFAULT, D3DX_DEFAULT, 
			1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
			D3DX_DEFAULT, D3DX_DEFAULT, 0, 
			&info, NULL, &pTextureNode->pTexture );
		if( FAILED(hr) )
		{
			return DXTRACE_ERR( L"D3DXCreateTextureFromFileEx", hr );
		}
	}

	// Store dimensions
	pTextureNode->dwWidth = info.Width;
	pTextureNode->dwHeight = info.Height;

	return S_OK;
}






// end file