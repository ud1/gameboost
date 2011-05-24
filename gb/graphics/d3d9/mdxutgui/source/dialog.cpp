
#include "d3d9pch.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h> 
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>
#include <gb/macro.h>



struct MYUT_SCREEN_VERTEX
{
	float x, y, z, h;
	D3DCOLOR color;
	float tu, tv;

	static DWORD FVF;
};
DWORD MYUT_SCREEN_VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;


struct MYUT_SCREEN_VERTEX_UNTEX
{
	float x, y, z, h;
	D3DCOLOR color;

	static DWORD FVF;
};
DWORD MYUT_SCREEN_VERTEX_UNTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;




//--------------------------------------------------------------------------------------
// Dialog class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
Dialog::Dialog()
{
	m_hwnd = 0;

	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;

	m_pManager = NULL;
	m_bVisible = true;
	m_bCaption = false;
	m_bMinimized = false;
	m_bDrag = false;
	m_wszCaption[0] = L'\0';
	m_nCaptionHeight = 18;

	m_colorTopLeft = 0;
	m_colorTopRight = 0;
	m_colorBottomLeft = 0;
	m_colorBottomRight = 0;

	m_pCallbackEvent = NULL;
	m_pCallbackEventUserContext = NULL;

	m_fTimeLastRefresh = 0;

	m_pControlMouseOver = NULL;

	m_pNextDialog = this;
	m_pPrevDialog = this;

	m_nDefaultControlID = 0xffff;
	m_bNonUserEvents = false;
	m_bKeyboardInput = false;
	m_bMouseInput = true;
}


//--------------------------------------------------------------------------------------
Dialog::~Dialog()
{
	int i=0;

	RemoveAllControls();

	m_Fonts.RemoveAll();
	m_Textures.RemoveAll();

	for( i=0; i < m_DefaultElements.GetSize(); i++ )
	{
		ElementHolder* pElementHolder = m_DefaultElements.GetAt( i );
		GB_SAFE_DEL_OBJ( pElementHolder );
	}

	m_DefaultElements.RemoveAll();
}

//--------------------------------------------------------------------------------------
void Dialog::SetCaptionText( const WCHAR *pwszText )
{
	StringCchCopy( m_wszCaption, sizeof( m_wszCaption ) / sizeof( m_wszCaption[ 0 ] ), pwszText );
}


//--------------------------------------------------------------------------------------
void Dialog::Init( DialogResourceManager* pManager, bool bRegisterDialog )
{
	m_pManager = pManager;
	if( bRegisterDialog )
		pManager->RegisterDialog( this );

	SetTexture( 0, MAKEINTRESOURCE(0xFFFF), (HMODULE)0xFFFF );
	InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void Dialog::Init( DialogResourceManager* pManager, bool bRegisterDialog, LPCWSTR pszControlTextureFilename )
{
	m_pManager = pManager;
	if( bRegisterDialog )
		pManager->RegisterDialog( this );
	SetTexture( 0, pszControlTextureFilename );
	InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void Dialog::Init( DialogResourceManager* pManager, bool bRegisterDialog, LPCWSTR szControlTextureResourceName, HMODULE hControlTextureResourceModule )
{
	m_pManager = pManager;
	if( bRegisterDialog )
		pManager->RegisterDialog( this );

	SetTexture( 0, szControlTextureResourceName, hControlTextureResourceModule );
	InitDefaultElements();
}


//--------------------------------------------------------------------------------------
void Dialog::SetCallback( PCALLBACKMYUTGUIEVENT pCallback, void* pUserContext )
{
	// If this assert triggers, you need to call Dialog::Init() first.  This change
	// was made so that the MYUT's GUI could become seperate and optional from MYUT's core.  The 
	// creation and interfacing with DialogResourceManager is now the responsibility 
	// of the application if it wishes to use MYUT's GUI.
	assert( m_pManager != NULL && L"To fix call Dialog::Init() first.  See comments for details." ); 

	m_pCallbackEvent = pCallback; 
	m_pCallbackEventUserContext = pUserContext; 
}


//--------------------------------------------------------------------------------------
void Dialog::RemoveControl( int ID )
{
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );
		if( pControl->GetID() == ID )
		{
			// Clean focus first
			ClearFocus();

			// Clear references to this control
			if( s_pControlFocus == pControl )
				s_pControlFocus = NULL;
			if( s_pControlPressed == pControl )
				s_pControlPressed = NULL;
			if( m_pControlMouseOver == pControl )
				m_pControlMouseOver = NULL;

			GB_SAFE_DEL_OBJ( pControl );
			m_Controls.Remove( i );

			return;
		}
	}
}


//--------------------------------------------------------------------------------------
void Dialog::RemoveAllControls()
{
	if( s_pControlFocus && s_pControlFocus->m_pDialog == this )
		s_pControlFocus = NULL;
	if( s_pControlPressed && s_pControlPressed->m_pDialog == this )
		s_pControlPressed = NULL;
	m_pControlMouseOver = NULL;

	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );
		GB_SAFE_DEL_OBJ( pControl );
	}

	m_Controls.RemoveAll();
}






//--------------------------------------------------------------------------------------
HRESULT Dialog::AddButton( int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, Button** ppCreated )
{
	HRESULT hr = S_OK;

	Button* pButton = new Button( this );

	if( ppCreated != NULL )
		*ppCreated = pButton;

	if( pButton == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pButton );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pButton->SetID( ID ); 
	pButton->SetText( strText );
	pButton->SetLocation( x, y );
	pButton->SetSize( width, height );
	pButton->SetHotkey( nHotkey );
	pButton->m_bIsDefault = bIsDefault;

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::AddCheckBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bChecked, UINT nHotkey, bool bIsDefault, CheckBox** ppCreated )
{
	HRESULT hr = S_OK;

	CheckBox* pCheckBox = new CheckBox( this );

	if( ppCreated != NULL )
		*ppCreated = pCheckBox;

	if( pCheckBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pCheckBox );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pCheckBox->SetID( ID ); 
	pCheckBox->SetText( strText );
	pCheckBox->SetLocation( x, y );
	pCheckBox->SetSize( width, height );
	pCheckBox->SetHotkey( nHotkey );
	pCheckBox->m_bIsDefault = bIsDefault;
	pCheckBox->SetChecked( bChecked );

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddRadioButton( int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height, bool bChecked, UINT nHotkey, bool bIsDefault, RadioButton** ppCreated )
{
	HRESULT hr = S_OK;

	RadioButton* pRadioButton = new RadioButton( this );

	if( ppCreated != NULL )
		*ppCreated = pRadioButton;

	if( pRadioButton == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pRadioButton );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pRadioButton->SetID( ID ); 
	pRadioButton->SetText( strText );
	pRadioButton->SetButtonGroup( nButtonGroup );
	pRadioButton->SetLocation( x, y );
	pRadioButton->SetSize( width, height );
	pRadioButton->SetHotkey( nHotkey );
	pRadioButton->SetChecked( bChecked );
	pRadioButton->m_bIsDefault = bIsDefault;
	pRadioButton->SetChecked( bChecked );

	return S_OK;
}




//--------------------------------------------------------------------------------------
HRESULT Dialog::AddComboBox( int ID, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, ComboBox** ppCreated )
{
	HRESULT hr = S_OK;

	ComboBox* pComboBox = new ComboBox( this );

	if( ppCreated != NULL )
		*ppCreated = pComboBox;

	if( pComboBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pComboBox );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pComboBox->SetID( ID ); 
	pComboBox->SetLocation( x, y );
	pComboBox->SetSize( width, height );
	pComboBox->SetHotkey( nHotkey );
	pComboBox->m_bIsDefault = bIsDefault;

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddSlider( int ID, int x, int y, int width, int height, int min, int max, int value, bool bIsDefault, Slider** ppCreated )
{
	HRESULT hr = S_OK;

	Slider* pSlider = new Slider( this );

	if( ppCreated != NULL )
		*ppCreated = pSlider;

	if( pSlider == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pSlider );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pSlider->SetID( ID ); 
	pSlider->SetLocation( x, y );
	pSlider->SetSize( width, height );
	pSlider->m_bIsDefault = bIsDefault;
	pSlider->SetRange( min, max );
	pSlider->SetValue( value );
	pSlider->UpdateRects();

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault, EditBox** ppCreated )
{
	HRESULT hr = S_OK;

	EditBox *pEditBox = new EditBox( this );

	if( ppCreated != NULL )
		*ppCreated = pEditBox;

	if( pEditBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pEditBox );
	if( FAILED(hr) )
		return hr;

	// Set the ID and position
	pEditBox->SetID( ID ); 
	pEditBox->SetLocation( x, y );
	pEditBox->SetSize( width, height );
	pEditBox->m_bIsDefault = bIsDefault;

	if( strText )
		pEditBox->SetText( strText );

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddIMEEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault, IMEEditBox** ppCreated )
{
	HRESULT hr = S_OK;
	IMEEditBox *pEditBox = new IMEEditBox( this );

	if( ppCreated != NULL )
		*ppCreated = pEditBox;

	if( pEditBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pEditBox );
	if( FAILED(hr) )
		return hr;

	// Set the ID and position
	pEditBox->SetID( ID ); 
	pEditBox->SetLocation( x, y );
	pEditBox->SetSize( width, height );
	pEditBox->m_bIsDefault = bIsDefault;

	if( strText )
		pEditBox->SetText( strText );

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddListBox( int ID, int x, int y, int width, int height, DWORD dwStyle, ListBox** ppCreated )
{
	HRESULT hr = S_OK;
	ListBox *pListBox = new ListBox( this );

	if( ppCreated != NULL )
		*ppCreated = pListBox;

	if( pListBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pListBox );
	if( FAILED(hr) )
		return hr;

	// Set the ID and position
	pListBox->SetID( ID );
	pListBox->SetLocation( x, y );
	pListBox->SetSize( width, height );
	pListBox->SetStyle( dwStyle );

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::InitControl( Control* pControl )
{
	HRESULT hr;

	if( pControl == NULL )
		return E_INVALIDARG;

	pControl->m_Index = m_Controls.GetSize();

	// Look for a default Element entries
	for( int i=0; i < m_DefaultElements.GetSize(); i++ )
	{
		ElementHolder* pElementHolder = m_DefaultElements.GetAt( i );
		if( pElementHolder->nControlType == pControl->GetType() )
			pControl->SetElement( pElementHolder->iElement, &pElementHolder->Element );
	}

	V_RETURN( pControl->OnInit() );

	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddControl( Control* pControl )
{
	HRESULT hr = S_OK;

	hr = InitControl( pControl );
	if( FAILED(hr) )
		return DXTRACE_ERR( L"Dialog::InitControl", hr );

	// Add to the list
	hr = m_Controls.Add( pControl );
	if( FAILED(hr) )
	{
		return DXTRACE_ERR( L"TemplatedArray::Add", hr );
	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
Control* Dialog::GetControl( int ID )
{
	// Try to find the control with the given ID
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );

		if( pControl->GetID() == ID )
		{
			return pControl;
		}
	}

	// Not found
	return NULL;
}



//--------------------------------------------------------------------------------------
Control* Dialog::GetControl( int ID, UINT nControlType )
{
	// Try to find the control with the given ID
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );

		if( pControl->GetID() == ID && pControl->GetType() == nControlType )
		{
			return pControl;
		}
	}

	// Not found
	return NULL;
}



//--------------------------------------------------------------------------------------
Control* Dialog::GetNextControl( Control* pControl )
{
	int index = pControl->m_Index + 1;

	Dialog* pDialog = pControl->m_pDialog;

	// Cycle through dialogs in the loop to find the next control. Note
	// that if only one control exists in all looped dialogs it will
	// be the returned 'next' control.
	while( index >= (int) pDialog->m_Controls.GetSize() )
	{
		pDialog = pDialog->m_pNextDialog;
		index = 0;
	}

	return pDialog->m_Controls.GetAt( index );
}

//--------------------------------------------------------------------------------------
Control* Dialog::GetPrevControl( Control* pControl )
{
	int index = pControl->m_Index - 1;

	Dialog* pDialog = pControl->m_pDialog;

	// Cycle through dialogs in the loop to find the next control. Note
	// that if only one control exists in all looped dialogs it will
	// be the returned 'previous' control.
	while( index < 0 )
	{
		pDialog = pDialog->m_pPrevDialog;
		if( pDialog == NULL )
			pDialog = pControl->m_pDialog;

		index = pDialog->m_Controls.GetSize() - 1;
	}

	return pDialog->m_Controls.GetAt( index );    
}


//--------------------------------------------------------------------------------------
void Dialog::ClearRadioButtonGroup( UINT nButtonGroup )
{
	// Find all radio buttons with the given group number
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );

		if( pControl->GetType() == MYUT_CONTROL_TYPE::RADIOBUTTON )
		{
			RadioButton* pRadioButton = (RadioButton*) pControl;

			if( pRadioButton->GetButtonGroup() == nButtonGroup )
				pRadioButton->SetChecked( false, false );
		}
	}
}



//--------------------------------------------------------------------------------------
void Dialog::ClearComboBox( int ID )
{
	ComboBox* pComboBox = GetComboBox( ID );
	if( pComboBox == NULL )
		return;

	pComboBox->RemoveAllItems();
}




//--------------------------------------------------------------------------------------
void Dialog::RequestFocus( Control* pControl )
{
	if( s_pControlFocus == pControl )
		return;

	if( !pControl->CanHaveFocus() )
		return;

	if( s_pControlFocus )
		s_pControlFocus->OnFocusOut();

	pControl->OnFocusIn();
	s_pControlFocus = pControl;
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::DrawRect( RECT* pRect, D3DCOLOR color )
{
	RECT rcScreen = *pRect;
	OffsetRect( &rcScreen, m_x, m_y );

	// If caption is enabled, offset the Y position by its height.
	if( m_bCaption )
		OffsetRect( &rcScreen, 0, m_nCaptionHeight );

	MYUT_SCREEN_VERTEX vertices[4] =
	{
		(float) rcScreen.left -0.5f,  (float) rcScreen.top -0.5f,    0.5f, 1.0f, color, 0, 0,
		(float) rcScreen.right -0.5f, (float) rcScreen.top -0.5f,    0.5f, 1.0f, color, 0, 0, 
		(float) rcScreen.right -0.5f, (float) rcScreen.bottom -0.5f, 0.5f, 1.0f, color, 0, 0, 
		(float) rcScreen.left -0.5f,  (float) rcScreen.bottom -0.5f, 0.5f, 1.0f, color, 0, 0,
	};

	IDirect3DDevice9* pd3dDevice = m_pManager->GetD3DDevice();

	// Since we're doing our own drawing here we need to flush the sprites
	m_pManager->m_pSprite->Flush();
	IDirect3DVertexDeclaration9 *pDecl = NULL;
	pd3dDevice->GetVertexDeclaration( &pDecl );  // Preserve the sprite's current vertex decl
	pd3dDevice->SetFVF( MYUT_SCREEN_VERTEX::FVF );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof(MYUT_SCREEN_VERTEX) );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	// Restore the vertex decl
	pd3dDevice->SetVertexDeclaration( pDecl );
	pDecl->Release();

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::DrawPolyLine( POINT* apPoints, UINT nNumPoints, D3DCOLOR color )
{
	MYUT_SCREEN_VERTEX* vertices = new MYUT_SCREEN_VERTEX[ nNumPoints ];
	if( vertices == NULL )
		return E_OUTOFMEMORY;

	MYUT_SCREEN_VERTEX* pVertex = vertices;
	POINT* pt = apPoints;
	for( UINT i=0; i < nNumPoints; i++ )
	{
		pVertex->x = m_x + (float) pt->x;
		pVertex->y = m_y + (float) pt->y;
		pVertex->z = 0.5f;
		pVertex->h = 1.0f;
		pVertex->color = color;
		pVertex->tu = 0.0f;
		pVertex->tv = 0.0f;

		pVertex++;
		pt++;
	}

	IDirect3DDevice9* pd3dDevice = m_pManager->GetD3DDevice();

	// Since we're doing our own drawing here we need to flush the sprites
	m_pManager->m_pSprite->Flush();
	IDirect3DVertexDeclaration9 *pDecl = NULL;
	pd3dDevice->GetVertexDeclaration( &pDecl );  // Preserve the sprite's current vertex decl
	pd3dDevice->SetFVF( MYUT_SCREEN_VERTEX::FVF );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, nNumPoints - 1, vertices, sizeof(MYUT_SCREEN_VERTEX) );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	// Restore the vertex decl
	pd3dDevice->SetVertexDeclaration( pDecl );
	pDecl->Release();

	GB_SAFE_DEL_BUF( vertices );
	return S_OK;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::DrawSprite( Element* pElement, RECT* prcDest )
{
	// No need to draw fully transparent layers
	if( pElement->TextureColor.Current.a == 0 )
		return S_OK;

	RECT rcTexture = pElement->rcTexture;

	RECT rcScreen = *prcDest;
	OffsetRect( &rcScreen, m_x, m_y );

	// If caption is enabled, offset the Y position by its height.
	if( m_bCaption )
		OffsetRect( &rcScreen, 0, m_nCaptionHeight );

	TextureNode* pTextureNode = GetTexture( pElement->iTexture );
	if( pTextureNode == NULL )
		return E_FAIL;

	float fScaleX = (float) RectWidth( rcScreen ) / RectWidth( rcTexture );
	float fScaleY = (float) RectHeight( rcScreen ) / RectHeight( rcTexture );

	D3DXMATRIXA16 matTransform;
	D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

	m_pManager->m_pSprite->SetTransform( &matTransform );

	D3DXVECTOR3 vPos( (float)rcScreen.left, (float)rcScreen.top, 0.0f );

	vPos.x /= fScaleX;
	vPos.y /= fScaleY;

	return m_pManager->m_pSprite->Draw( pTextureNode->pTexture, &rcTexture, NULL, &vPos, pElement->TextureColor.Current );
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::CalcTextRect( LPCWSTR strText, Element* pElement, RECT* prcDest, int nCount )
{
	HRESULT hr = S_OK;

	FontNode* pFontNode = GetFont( pElement->iFont );
	if( pFontNode == NULL )
		return E_FAIL;

	DWORD dwTextFormat = pElement->dwTextFormat | DT_CALCRECT;
	// Since we are only computing the rectangle, we don't need a sprite.
	hr = pFontNode->pFont->DrawText( NULL, strText, nCount, prcDest, dwTextFormat, pElement->FontColor.Current );
	if( FAILED(hr) )
		return hr;

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::DrawText( LPCWSTR strText, Element* pElement, RECT* prcDest, bool bShadow, int nCount )
{
	HRESULT hr = S_OK;

	// No need to draw fully transparent layers
	if( pElement->FontColor.Current.a == 0 )
		return S_OK;

	RECT rcScreen = *prcDest;
	OffsetRect( &rcScreen, m_x, m_y );

	// If caption is enabled, offset the Y position by its height.
	if( m_bCaption )
		OffsetRect( &rcScreen, 0, m_nCaptionHeight );

	//debug
	//DrawRect( &rcScreen, D3DCOLOR_ARGB(100, 255, 0, 0) );

	D3DXMATRIXA16 matTransform;
	D3DXMatrixIdentity( &matTransform );
	m_pManager->m_pSprite->SetTransform( &matTransform );

	FontNode* pFontNode = GetFont( pElement->iFont );

	if( bShadow )
	{
		RECT rcShadow = rcScreen;
		OffsetRect( &rcShadow, 1, 1 );
		hr = pFontNode->pFont->DrawText( m_pManager->m_pSprite, strText, nCount, &rcShadow, pElement->dwTextFormat, D3DCOLOR_ARGB(DWORD(pElement->FontColor.Current.a * 255), 0, 0, 0) );
		if( FAILED(hr) )
			return hr;
	}

	hr = pFontNode->pFont->DrawText( m_pManager->m_pSprite, strText, nCount, &rcScreen, pElement->dwTextFormat, pElement->FontColor.Current );
	if( FAILED(hr) )
		return hr;

	return S_OK;
}


//--------------------------------------------------------------------------------------
void Dialog::SetBackgroundColors( D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight )
{
	m_colorTopLeft = colorTopLeft;
	m_colorTopRight = colorTopRight;
	m_colorBottomLeft = colorBottomLeft;
	m_colorBottomRight = colorBottomRight;
}


//--------------------------------------------------------------------------------------
void Dialog::SetNextDialog( Dialog* pNextDialog )
{ 
	if( pNextDialog == NULL )
		pNextDialog = this;

	m_pNextDialog = pNextDialog;
	if( pNextDialog )
		m_pNextDialog->m_pPrevDialog = this;
}


//--------------------------------------------------------------------------------------
void Dialog::ClearFocus()
{
	if( s_pControlFocus )
	{
		s_pControlFocus->OnFocusOut();
		s_pControlFocus = NULL;
	}

	ReleaseCapture();
}


//--------------------------------------------------------------------------------------
void Dialog::FocusDefaultControl()
{
	// Check for default control in this dialog
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt( i );
		if( pControl->m_bIsDefault )
		{
			// Remove focus from the current control
			ClearFocus();

			// Give focus to the default control
			s_pControlFocus = pControl;
			s_pControlFocus->OnFocusIn();
			return;
		}
	}
}


//--------------------------------------------------------------------------------------
bool Dialog::OnCycleFocus( bool bForward )
{
	Control *pControl = NULL;
	Dialog *pDialog = NULL; // pDialog and pLastDialog are used to track wrapping of
	Dialog *pLastDialog;    // focus from first control to last or vice versa.

	if( s_pControlFocus == NULL )
	{
		// If s_pControlFocus is NULL, we focus the first control of first dialog in
		// the case that bForward is true, and focus the last control of last dialog when
		// bForward is false.
		//
		if( bForward )
		{
			// Search for the first control from the start of the dialog
			// array.
			for( int d = 0; d < m_pManager->m_Dialogs.GetSize(); ++d )
			{
				pDialog = pLastDialog = m_pManager->m_Dialogs.GetAt(d);
				if( pDialog && pDialog->m_Controls.GetSize() > 0 )
				{
					pControl = pDialog->m_Controls.GetAt(0);
					break;
				}
			}

			if( !pDialog || !pControl )
			{
				// No dialog has been registered yet or no controls have been
				// added to the dialogs. Cannot proceed.
				return true;
			}
		}
		else
		{
			// Search for the first control from the end of the dialog
			// array.
			for( int d = m_pManager->m_Dialogs.GetSize() - 1; d >= 0; --d )
			{
				pDialog = pLastDialog = m_pManager->m_Dialogs.GetAt(d);
				if( pDialog && pDialog->m_Controls.GetSize() > 0 )
				{
					pControl = pDialog->m_Controls.GetAt( pDialog->m_Controls.GetSize() - 1 );
					break;
				}
			}

			if( !pDialog || !pControl )
			{
				// No dialog has been registered yet or no controls have been
				// added to the dialogs. Cannot proceed.
				return true;
			}
		}
	}
	else
		if( s_pControlFocus->m_pDialog != this )
		{
			// If a control belonging to another dialog has focus, let that other
			// dialog handle this event by returning false.
			//
			return false;
		}
		else
		{
			// Focused control belongs to this dialog. Cycle to the
			// next/previous control.
			pLastDialog = s_pControlFocus->m_pDialog;
			pControl = (bForward) ? GetNextControl( s_pControlFocus ) : GetPrevControl( s_pControlFocus );
			pDialog = pControl->m_pDialog;
		}

		for( int i=0; i < 0xffff; i++ )
		{
			// If we just wrapped from last control to first or vice versa,
			// set the focused control to NULL. This state, where no control
			// has focus, allows the camera to work.
			int nLastDialogIndex = m_pManager->m_Dialogs.IndexOf( pLastDialog );
			int nDialogIndex = m_pManager->m_Dialogs.IndexOf( pDialog );
			if( ( !bForward && nLastDialogIndex < nDialogIndex ) ||
				( bForward && nDialogIndex < nLastDialogIndex ) )
			{
				if( s_pControlFocus )
					s_pControlFocus->OnFocusOut();
				s_pControlFocus = NULL;
				return true;
			}

			// If we've gone in a full circle then focus doesn't change
			if( pControl == s_pControlFocus )
				return true;

			// If the dialog accepts keybord input and the control can have focus then
			// move focus
			if( pControl->m_pDialog->m_bKeyboardInput && pControl->CanHaveFocus() )
			{
				if( s_pControlFocus )
					s_pControlFocus->OnFocusOut();
				s_pControlFocus = pControl;
				s_pControlFocus->OnFocusIn();
				return true;
			}

			pLastDialog = pDialog;
			pControl = (bForward) ? GetNextControl( pControl ) : GetPrevControl( pControl );
			pDialog = pControl->m_pDialog;
		}

		// If we reached this point, the chain of dialogs didn't form a complete loop
		DXTRACE_ERR( L"Dialog: Multiple dialogs are improperly chained together", E_FAIL );
		return false;
}



//--------------------------------------------------------------------------------------
void Dialog::Refresh()
{
	if( s_pControlFocus )
		s_pControlFocus->OnFocusOut();

	if( m_pControlMouseOver )
		m_pControlMouseOver->OnMouseLeave();

	s_pControlFocus = NULL;
	s_pControlPressed = NULL;
	m_pControlMouseOver = NULL;

	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt(i);
		pControl->Refresh();
	}

	if( m_bKeyboardInput )
		FocusDefaultControl();
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::OnRender( float fElapsedTime )
{   
	// If this assert triggers, you need to call DialogResourceManager::On*Device() from inside
	// the application's device callbacks.  See the SDK samples for an example of how to do this.
	assert( m_pManager->GetD3DDevice() && m_pManager->m_pStateBlock && L"To fix hook up DialogResourceManager to device callbacks.  See comments for details" );

	// See if the dialog needs to be refreshed
	if( m_fTimeLastRefresh < s_fTimeRefresh )
	{
		m_fTimeLastRefresh = getGlobalTime();
		Refresh();
	}

	// For invisible dialog, out now.
	if( !m_bVisible ||
		( m_bMinimized && !m_bCaption ) )
		return S_OK;

	IDirect3DDevice9* pd3dDevice = m_pManager->GetD3DDevice();

	// Set up a state block here and restore it when finished drawing all the controls
	m_pManager->m_pStateBlock->Capture();

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	pd3dDevice->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED );
	pd3dDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
	pd3dDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_RESULTARG, D3DTA_CURRENT );
	pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	BOOL bBackgroundIsVisible = ( m_colorTopLeft | m_colorTopRight | m_colorBottomRight | m_colorBottomLeft ) & 0xff000000;
	if( !m_bMinimized && bBackgroundIsVisible )
	{
		MYUT_SCREEN_VERTEX_UNTEX vertices[4] =
		{
			(float)m_x,           (float)m_y,            0.5f, 1.0f, m_colorTopLeft,
			(float)m_x + m_width, (float)m_y,            0.5f, 1.0f, m_colorTopRight,
			(float)m_x + m_width, (float)m_y + m_height, 0.5f, 1.0f, m_colorBottomRight,
			(float)m_x,           (float)m_y + m_height, 0.5f, 1.0f, m_colorBottomLeft,
		};

		pd3dDevice->SetVertexShader( NULL );
		pd3dDevice->SetPixelShader( NULL );

		pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

		pd3dDevice->SetFVF( MYUT_SCREEN_VERTEX_UNTEX::FVF );
		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof(MYUT_SCREEN_VERTEX_UNTEX) );
	}

	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	TextureNode* pTextureNode = GetTexture( 0 );
	pd3dDevice->SetTexture( 0, pTextureNode->pTexture );

	m_pManager->m_pSprite->Begin( D3DXSPRITE_DONOTSAVESTATE );

	// Render the caption if it's enabled.
	if( m_bCaption )
	{
		// DrawSprite will offset the rect down by
		// m_nCaptionHeight, so adjust the rect higher
		// here to negate the effect.
		RECT rc = { 0, -m_nCaptionHeight, m_width, 0 };
		DrawSprite( &m_CapElement, &rc );
		rc.left += 5; // Make a left margin
		WCHAR wszOutput[256];
		StringCchCopy( wszOutput, 256, m_wszCaption );
		if( m_bMinimized )
			StringCchCat( wszOutput, 256, L" (Minimized)" );
		DrawText( wszOutput, &m_CapElement, &rc, true );
	}

	// If the dialog is minimized, skip rendering
	// its controls.
	if( !m_bMinimized )
	{
		for( int i=0; i < m_Controls.GetSize(); i++ )
		{
			Control* pControl = m_Controls.GetAt(i);   

			// Focused control is drawn last
			if( pControl == s_pControlFocus )
				continue;

			pControl->Render( pd3dDevice, fElapsedTime );
		}

		if( s_pControlFocus != NULL && s_pControlFocus->m_pDialog == this )
			s_pControlFocus->Render( pd3dDevice, fElapsedTime );
	}

	m_pManager->m_pSprite->End();

	m_pManager->m_pStateBlock->Apply();

	return S_OK;
}


//--------------------------------------------------------------------------------------
VOID Dialog::SendEvent( UINT nEvent, bool bTriggeredByUser, Control* pControl )
{
	// If no callback has been registered there's nowhere to send the event to
	if( m_pCallbackEvent == NULL )
		return;

	// Discard events triggered programatically if these types of events haven't been
	// enabled
	if( !bTriggeredByUser && !m_bNonUserEvents )
		return;

	m_pCallbackEvent( nEvent, pControl->GetID(), pControl, m_pCallbackEventUserContext );
}





//--------------------------------------------------------------------------------------
bool Dialog::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	bool bHandled = false;
	m_hwnd =  hWnd;
	  setGlobalHwnd(hWnd);//  g_hwnd =hWnd;

	// For invisible dialog, do not handle anything.
	if( !m_bVisible )
		return false;

	// If automation command-line switch is on, enable this dialog's keyboard input
	// upon any key press or mouse click.
	if( getGlobalAutomation() &&
		( WM_LBUTTONDOWN == uMsg || WM_LBUTTONDBLCLK == uMsg || WM_KEYDOWN == uMsg ) )
	{
		m_pManager->EnableKeyboardInputForAllDialogs();
	}

	// If caption is enable, check for clicks in the caption area.
	if( m_bCaption )
	{
		if( uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK )
		{
			POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };

			if( mousePoint.x >= m_x && mousePoint.x < m_x + m_width &&
				mousePoint.y >= m_y && mousePoint.y < m_y + m_nCaptionHeight )
			{
				m_bDrag = true;
				SetCapture( m_hwnd) ;//  MYUTGetHWND() );
				return true;
			}
		} else
			if( uMsg == WM_LBUTTONUP && m_bDrag )
			{
				POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };

				if( mousePoint.x >= m_x && mousePoint.x < m_x + m_width &&
					mousePoint.y >= m_y && mousePoint.y < m_y + m_nCaptionHeight )
				{
					ReleaseCapture();
					m_bDrag = false;
					m_bMinimized = !m_bMinimized;
					return true;
				}
			}
	}

	// If the dialog is minimized, don't send any messages to controls.
	if( m_bMinimized )
		return false;

	// If a control is in focus, it belongs to this dialog, and it's enabled, then give
	// it the first chance at handling the message.
	if( s_pControlFocus && 
		s_pControlFocus->m_pDialog == this && 
		s_pControlFocus->GetEnabled() )
	{
		// If the control MsgProc handles it, then we don't.
		if( s_pControlFocus->MsgProc( uMsg, wParam, lParam ) )
			return true;
	}

	switch( uMsg )
	{
	case WM_SIZE:
	case WM_MOVE:
		{
			// Handle sizing and moving messages so that in case the mouse cursor is moved out
			// of an UI control because of the window adjustment, we can properly
			// unhighlight the highlighted control.
			POINT pt = { -1, -1 };
			OnMouseMove( pt );
			break;
		}

	case WM_ACTIVATEAPP:
		// Call OnFocusIn()/OnFocusOut() of the control that currently has the focus
		// as the application is activated/deactivated.  This matches the Windows
		// behavior.
		if( s_pControlFocus && 
			s_pControlFocus->m_pDialog == this && 
			s_pControlFocus->GetEnabled() )
		{
			if( wParam )
				s_pControlFocus->OnFocusIn();
			else
				s_pControlFocus->OnFocusOut();
		}
		break;

		// Keyboard messages
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		{
			// If a control is in focus, it belongs to this dialog, and it's enabled, then give
			// it the first chance at handling the message.
			if( s_pControlFocus && 
				s_pControlFocus->m_pDialog == this && 
				s_pControlFocus->GetEnabled() )
			{
				if( s_pControlFocus->HandleKeyboard( uMsg, wParam, lParam ) )
					return true;
			}

			// Not yet handled, see if this matches a control's hotkey
			// Activate the hotkey if the focus doesn't belong to an
			// edit box.
			if( uMsg == WM_KEYDOWN && ( !s_pControlFocus ||
				( s_pControlFocus->GetType() != MYUT_CONTROL_TYPE::EDITBOX
				&& s_pControlFocus->GetType() != MYUT_CONTROL_TYPE::IMEEDITBOX ) ) )
			{
				for( int i=0; i < m_Controls.GetSize(); i++ )
				{
					Control* pControl = m_Controls.GetAt( i );
					if( pControl->GetHotkey() == wParam )
					{
						pControl->OnHotkey();
						return true;
					}
				}
			}

			// Not yet handled, check for focus messages
			if( uMsg == WM_KEYDOWN )
			{
				// If keyboard input is not enabled, this message should be ignored
				if( !m_bKeyboardInput )
					return false;

				switch( wParam )
				{
				case VK_RIGHT:
				case VK_DOWN:
					if( s_pControlFocus != NULL )
					{
						return OnCycleFocus( true );
					}
					break;

				case VK_LEFT:
				case VK_UP:
					if( s_pControlFocus != NULL )
					{
						return OnCycleFocus( false );
					}
					break;

				case VK_TAB: 
					{
						bool bShiftDown = ((GetKeyState( VK_SHIFT ) & 0x8000) != 0);
						return OnCycleFocus( !bShiftDown );
					}
				}
			}

			break;
		}


		// Mouse messages
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
		{
			// If not accepting mouse input, return false to indicate the message should still 
			// be handled by the application (usually to move the camera).
			if( !m_bMouseInput )
				return false;

			POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };
			mousePoint.x -= m_x;
			mousePoint.y -= m_y;

			// If caption is enabled, offset the Y coordinate by the negative of its height.
			if( m_bCaption )
				mousePoint.y -= m_nCaptionHeight;

			// If a control is in focus, it belongs to this dialog, and it's enabled, then give
			// it the first chance at handling the message.
			if( s_pControlFocus && 
				s_pControlFocus->m_pDialog == this && 
				s_pControlFocus->GetEnabled() )
			{
				if( s_pControlFocus->HandleMouse( uMsg, mousePoint, wParam, lParam ) )
					return true;
			}

			// Not yet handled, see if the mouse is over any controls
			Control* pControl = GetControlAtPoint( mousePoint );
			if( pControl != NULL && pControl->GetEnabled() )
			{
				bHandled = pControl->HandleMouse( uMsg, mousePoint, wParam, lParam );
				if( bHandled )
					return true;
			}
			else
			{
				// Mouse not over any controls in this dialog, if there was a control
				// which had focus it just lost it
				if( uMsg == WM_LBUTTONDOWN && 
					s_pControlFocus && 
					s_pControlFocus->m_pDialog == this )
				{
					s_pControlFocus->OnFocusOut();
					s_pControlFocus = NULL;
				}
			}

			// Still not handled, hand this off to the dialog. Return false to indicate the
			// message should still be handled by the application (usually to move the camera).
			switch( uMsg )
			{
			case WM_MOUSEMOVE:
				OnMouseMove( mousePoint );
				return false;
			}

			break;
		}

	case WM_CAPTURECHANGED:
		{
			// The application has lost mouse capture.
			// The dialog object may not have received
			// a WM_MOUSEUP when capture changed. Reset
			// m_bDrag so that the dialog does not mistakenly
			// think the mouse button is still held down.
			if( (HWND)lParam != hWnd )
				m_bDrag = false;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------------
Control* Dialog::GetControlAtPoint( POINT pt )
{
	// Search through all child controls for the first one which
	// contains the mouse point
	for( int i=0; i < m_Controls.GetSize(); i++ )
	{
		Control* pControl = m_Controls.GetAt(i);

		if( pControl == NULL )
		{
			continue;
		}

		// We only return the current control if it is visible
		// and enabled.  Because GetControlAtPoint() is used to do mouse
		// hittest, it makes sense to perform this filtering.
		if( pControl->ContainsPoint( pt ) && pControl->GetEnabled() && pControl->GetVisible() )
		{
			return pControl;
		}
	}

	return NULL;
}


//--------------------------------------------------------------------------------------
bool Dialog::GetControlEnabled( int ID )
{
	Control* pControl = GetControl( ID );
	if( pControl == NULL )
		return false;

	return pControl->GetEnabled();
}



//--------------------------------------------------------------------------------------
void Dialog::SetControlEnabled( int ID, bool bEnabled )
{
	Control* pControl = GetControl( ID );
	if( pControl == NULL )
		return;

	pControl->SetEnabled( bEnabled );
}


//--------------------------------------------------------------------------------------
void Dialog::OnMouseUp( POINT pt )
{
	s_pControlPressed = NULL;
	m_pControlMouseOver = NULL;
}


//--------------------------------------------------------------------------------------
void Dialog::OnMouseMove( POINT pt )
{
	// Figure out which control the mouse is over now
	Control* pControl = GetControlAtPoint( pt );

	// If the mouse is still over the same control, nothing needs to be done
	if( pControl == m_pControlMouseOver )
		return;

	// Handle mouse leaving the old control
	if( m_pControlMouseOver )
		m_pControlMouseOver->OnMouseLeave();

	// Handle mouse entering the new control
	m_pControlMouseOver = pControl;
	if( pControl != NULL )
		m_pControlMouseOver->OnMouseEnter();
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::SetDefaultElement( UINT nControlType, UINT iElement, Element* pElement )
{
	// If this Element type already exist in the list, simply update the stored Element
	for( int i=0; i < m_DefaultElements.GetSize(); i++ )
	{
		ElementHolder* pElementHolder = m_DefaultElements.GetAt( i );

		if( pElementHolder->nControlType == nControlType &&
			pElementHolder->iElement == iElement )
		{
			pElementHolder->Element = *pElement;
			return S_OK;
		}
	}

	// Otherwise, add a new entry
	ElementHolder* pNewHolder;
	pNewHolder = new ElementHolder;
	if( pNewHolder == NULL )
		return E_OUTOFMEMORY;

	pNewHolder->nControlType = nControlType;
	pNewHolder->iElement = iElement;
	pNewHolder->Element = *pElement;

	m_DefaultElements.Add( pNewHolder );
	return S_OK;
}


//--------------------------------------------------------------------------------------
Element* Dialog::GetDefaultElement( UINT nControlType, UINT iElement )
{
	for( int i=0; i < m_DefaultElements.GetSize(); i++ )
	{
		ElementHolder* pElementHolder = m_DefaultElements.GetAt( i );

		if( pElementHolder->nControlType == nControlType &&
			pElementHolder->iElement == iElement )
		{
			return &pElementHolder->Element;
		}
	}

	return NULL;
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::AddStatic( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault, Static** ppCreated )
{
	HRESULT hr = S_OK;

	Static* pStatic = new Static( this );

	if( ppCreated != NULL )
		*ppCreated = pStatic;

	if( pStatic == NULL )
		return E_OUTOFMEMORY;

	hr = AddControl( pStatic );
	if( FAILED(hr) )
		return hr;

	// Set the ID and list index
	pStatic->SetID( ID ); 
	pStatic->SetText( strText );
	pStatic->SetLocation( x, y );
	pStatic->SetSize( width, height );
	pStatic->m_bIsDefault = bIsDefault;

	return S_OK;
}


//--------------------------------------------------------------------------------------
FontNode* Dialog::GetFont( UINT index )
{
	if( NULL == m_pManager )
		return NULL;
	return m_pManager->GetFontNode( m_Fonts.GetAt( index ) );
}



//--------------------------------------------------------------------------------------
HRESULT Dialog::SetTexture( UINT index, LPCWSTR strFilename )
{
	// If this assert triggers, you need to call Dialog::Init() first.  This change
	// was made so that the MYUT's GUI could become seperate and optional from MYUT's core.  The 
	// creation and interfacing with DialogResourceManager is now the responsibility 
	// of the application if it wishes to use MYUT's GUI.
	assert( m_pManager != NULL && L"To fix this, call Dialog::Init() first.  See comments for details." ); 

	// Make sure the list is at least as large as the index being set
	for( UINT i=m_Textures.GetSize(); i <= index; i++ )
	{
		m_Textures.Add( -1 );
	}

	int iTexture = m_pManager->AddTexture( strFilename );

	m_Textures.SetAt( index, iTexture );
	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::SetTexture( UINT index, LPCWSTR strResourceName, HMODULE hResourceModule )
{
	// If this assert triggers, you need to call Dialog::Init() first.  This change
	// was made so that the MYUT's GUI could become seperate and optional from MYUT's core.  The 
	// creation and interfacing with DialogResourceManager is now the responsibility 
	// of the application if it wishes to use MYUT's GUI.
	assert( m_pManager != NULL && L"To fix this, call Dialog::Init() first.  See comments for details." ); 

	// Make sure the list is at least as large as the index being set
	for( UINT i=m_Textures.GetSize(); i <= index; i++ )
	{
		m_Textures.Add( -1 );
	}

	int iTexture = m_pManager->AddTexture( strResourceName, hResourceModule );

	m_Textures.SetAt( index, iTexture );
	return S_OK;
}


//--------------------------------------------------------------------------------------
TextureNode* Dialog::GetTexture( UINT index )
{
	if( NULL == m_pManager )
		return NULL;
	return m_pManager->GetTextureNode( m_Textures.GetAt( index ) );
}



//--------------------------------------------------------------------------------------
void Dialog::InitDefaultElements()
{
	SetFont( 0, L"Arial", 14, FW_NORMAL );

	Element Element;
	RECT rcTexture;

	//-------------------------------------
	// Element for the caption
	//-------------------------------------
	m_CapElement.SetFont( 0 );
	SetRect( &rcTexture, 17, 269, 241, 287 );
	m_CapElement.SetTexture( 0, &rcTexture );
	m_CapElement.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_CapElement.FontColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_CapElement.SetFont( 0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER );
	// Pre-blend as we don't need to transition the state
	m_CapElement.TextureColor.Blend( MYUT_CONTROL_STATE::NORMAL, 10.0f );
	m_CapElement.FontColor.Blend( MYUT_CONTROL_STATE::NORMAL, 10.0f );

	//-------------------------------------
	// Static
	//-------------------------------------
	Element.SetFont( 0 );
	Element.FontColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::STATIC, 0, &Element );


	//-------------------------------------
	// Button - Button
	//-------------------------------------
	SetRect( &rcTexture, 0, 0, 136, 54 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0 );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.FontColor.States[ MYUT_CONTROL_STATE::MOUSEOVER ] = D3DCOLOR_ARGB(255, 0, 0, 0);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::BUTTON, 0, &Element );


	//-------------------------------------
	// Button - Fill layer
	//-------------------------------------
	SetRect( &rcTexture, 136, 0, 252, 54 );
	Element.SetTexture( 0, &rcTexture, D3DCOLOR_ARGB(0, 255, 255, 255) );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::MOUSEOVER ] = D3DCOLOR_ARGB(160, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(60, 0, 0, 0);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(30, 255, 255, 255);


	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::BUTTON, 1, &Element );


	//-------------------------------------
	// CheckBox - Box
	//-------------------------------------
	SetRect( &rcTexture, 0, 54, 27, 81 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER );
	Element.FontColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(255, 255, 255, 255);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::CHECKBOX, 0, &Element );


	//-------------------------------------
	// CheckBox - Check
	//-------------------------------------
	SetRect( &rcTexture, 27, 54, 54, 81 );
	Element.SetTexture( 0, &rcTexture );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::CHECKBOX, 1, &Element );


	//-------------------------------------
	// RadioButton - Box
	//-------------------------------------
	SetRect( &rcTexture, 54, 54, 81, 81 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER );
	Element.FontColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB( 200, 200, 200, 200 );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(255, 255, 255, 255);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::RADIOBUTTON, 0, &Element );


	//-------------------------------------
	// RadioButton - Check
	//-------------------------------------
	SetRect( &rcTexture, 81, 54, 108, 81 );
	Element.SetTexture( 0, &rcTexture );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::RADIOBUTTON, 1, &Element );


	//-------------------------------------
	// ComboBox - Main
	//-------------------------------------
	SetRect( &rcTexture, 7, 81, 247, 123 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0 );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 200, 200, 200);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(170, 230, 230, 230);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(70, 200, 200, 200);
	Element.FontColor.States[ MYUT_CONTROL_STATE::MOUSEOVER ] = D3DCOLOR_ARGB(255, 0, 0, 0);
	Element.FontColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(255, 0, 0, 0);
	Element.FontColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(200, 200, 200, 200);


	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::COMBOBOX, 0, &Element );


	//-------------------------------------
	// ComboBox - Button
	//-------------------------------------
	SetRect( &rcTexture, 98, 189, 151, 238 );
	Element.SetTexture( 0, &rcTexture );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::PRESSED ] = D3DCOLOR_ARGB(255, 150, 150, 150);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(70, 255, 255, 255);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::COMBOBOX, 1, &Element );


	//-------------------------------------
	// ComboBox - Dropdown
	//-------------------------------------
	SetRect( &rcTexture, 13, 123, 241, 160 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 0, 0, 0), DT_LEFT | DT_TOP );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::COMBOBOX, 2, &Element );


	//-------------------------------------
	// ComboBox - Selection
	//-------------------------------------
	SetRect( &rcTexture, 12, 163, 239, 183 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_TOP );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::COMBOBOX, 3, &Element );


	//-------------------------------------
	// Slider - Track
	//-------------------------------------
	SetRect( &rcTexture, 1, 187, 93, 228 );
	Element.SetTexture( 0, &rcTexture );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::NORMAL ] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::FOCUS ] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(70, 255, 255, 255);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SLIDER, 0, &Element );

	//-------------------------------------
	// Slider - Button
	//-------------------------------------
	SetRect( &rcTexture, 151, 193, 192, 234 );
	Element.SetTexture( 0, &rcTexture );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SLIDER, 1, &Element );

	//-------------------------------------
	// ScrollBar - Track
	//-------------------------------------
	int nScrollBarStartX = 196;
	int nScrollBarStartY = 191;
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 21, nScrollBarStartX + 22, nScrollBarStartY + 32 );
	Element.SetTexture( 0, &rcTexture );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(255, 200, 200, 200);

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SCROLLBAR, 0, &Element );

	//-------------------------------------
	// ScrollBar - Up Arrow
	//-------------------------------------
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 1, nScrollBarStartX + 22, nScrollBarStartY + 21 );
	Element.SetTexture( 0, &rcTexture );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(255, 200, 200, 200);


	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SCROLLBAR, 1, &Element );

	//-------------------------------------
	// ScrollBar - Down Arrow
	//-------------------------------------
	SetRect( &rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 32, nScrollBarStartX + 22, nScrollBarStartY + 53 );
	Element.SetTexture( 0, &rcTexture );
	Element.TextureColor.States[ MYUT_CONTROL_STATE::DISABLED ] = D3DCOLOR_ARGB(255, 200, 200, 200);


	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SCROLLBAR, 2, &Element );

	//-------------------------------------
	// ScrollBar - Button
	//-------------------------------------
	SetRect( &rcTexture, 220, 192, 238, 234 );
	Element.SetTexture( 0, &rcTexture );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::SCROLLBAR, 3, &Element );


	//-------------------------------------
	// EditBox
	//-------------------------------------
	// Element assignment:
	//   0 - text area
	//   1 - top left border
	//   2 - top border
	//   3 - top right border
	//   4 - left border
	//   5 - right border
	//   6 - lower left border
	//   7 - lower border
	//   8 - lower right border

	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

	// Assign the style
	SetRect( &rcTexture, 14, 90, 241, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 0, &Element );
	SetRect( &rcTexture, 8, 82, 14, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 1, &Element );
	SetRect( &rcTexture, 14, 82, 241, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 2, &Element );
	SetRect( &rcTexture, 241, 82, 246, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 3, &Element );
	SetRect( &rcTexture, 8, 90, 14, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 4, &Element );
	SetRect( &rcTexture, 241, 90, 246, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 5, &Element );
	SetRect( &rcTexture, 8, 113, 14, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 6, &Element );
	SetRect( &rcTexture, 14, 113, 241, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 7, &Element );
	SetRect( &rcTexture, 241, 113, 246, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::EDITBOX, 8, &Element );


	//-------------------------------------
	// IMEEditBox
	//-------------------------------------

	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_LEFT | DT_TOP );

	// Assign the style
	SetRect( &rcTexture, 14, 90, 241, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 0, &Element );
	SetRect( &rcTexture, 8, 82, 14, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 1, &Element );
	SetRect( &rcTexture, 14, 82, 241, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 2, &Element );
	SetRect( &rcTexture, 241, 82, 246, 90 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 3, &Element );
	SetRect( &rcTexture, 8, 90, 14, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 4, &Element );
	SetRect( &rcTexture, 241, 90, 246, 113 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 5, &Element );
	SetRect( &rcTexture, 8, 113, 14, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 6, &Element );
	SetRect( &rcTexture, 14, 113, 241, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 7, &Element );
	SetRect( &rcTexture, 241, 113, 246, 121 );
	Element.SetTexture( 0, &rcTexture );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 8, &Element );
	// Element 9 for IME text, and indicator button
	SetRect( &rcTexture, 0, 0, 136, 54 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0, 0 ), DT_CENTER | DT_VCENTER );
	SetDefaultElement( MYUT_CONTROL_TYPE::IMEEDITBOX, 9, &Element );

	//-------------------------------------
	// ListBox - Main
	//-------------------------------------
	SetRect( &rcTexture, 13, 123, 241, 160 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 0, 0, 0), DT_LEFT | DT_TOP );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::LISTBOX, 0, &Element );

	//-------------------------------------
	// ListBox - Selection
	//-------------------------------------

	SetRect( &rcTexture, 16, 166, 240, 183 );
	Element.SetTexture( 0, &rcTexture );
	Element.SetFont( 0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_TOP );

	// Assign the Element
	SetDefaultElement( MYUT_CONTROL_TYPE::LISTBOX, 1, &Element );
}


//--------------------------------------------------------------------------------------
HRESULT Dialog::SetFont( UINT index, LPCWSTR strFaceName, LONG height, LONG weight )
{
	// If this assert triggers, you need to call Dialog::Init() first.  This change
	// was made so that the MYUT's GUI could become seperate and optional from MYUT's core.  The 
	// creation and interfacing with DialogResourceManager is now the responsibility 
	// of the application if it wishes to use MYUT's GUI.
	assert( m_pManager != NULL && L"To fix call Dialog::Init() first.  See comments for details." ); 

	// Make sure the list is at least as large as the index being set
	UINT i;
	for( i=m_Fonts.GetSize(); i <= index; i++ )
	{
		m_Fonts.Add( -1 );
	}

	int iFont = m_pManager->AddFont( strFaceName, height, weight );
	m_Fonts.SetAt( index, iFont );

	return S_OK;
}





// end file