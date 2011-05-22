#include "stdafx.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h>
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>
#include <gb/macro.h>




//--------------------------------------------------------------------------------------
// Static class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
Static::Static( Dialog *pDialog )
{
	m_Type = MYUT_CONTROL_TYPE::STATIC;
	m_pDialog = pDialog;

	ZeroMemory( &m_strText, sizeof(m_strText) );  

	for( int i=0; i < m_Elements.GetSize(); i++ )
	{
		Element* pElement = m_Elements.GetAt( i );
		GB_SAFE_DEL_OBJ( pElement );
	}

	m_Elements.RemoveAll();
}


//--------------------------------------------------------------------------------------
void Static::Render( IDirect3DDevice9* pd3dDevice, float fElapsedTime )
{    
	if( m_bVisible == false )
		return;

	MYUT_CONTROL_STATE::e iState = MYUT_CONTROL_STATE::NORMAL;

	if( m_bEnabled == false )
		iState = MYUT_CONTROL_STATE::DISABLED;

	Element* pElement = m_Elements.GetAt( 0 );

	pElement->FontColor.Blend( iState, fElapsedTime );

	m_pDialog->DrawText( m_strText, pElement, &m_rcBoundingBox, true );
}

//--------------------------------------------------------------------------------------
HRESULT Static::GetTextCopy( LPWSTR strDest, UINT bufferCount )
{
	// Validate incoming parameters
	if( strDest == NULL || bufferCount == 0 )
	{
		return E_INVALIDARG;
	}

	// Copy the window text
	StringCchCopy( strDest, bufferCount, m_strText );

	return S_OK;
}


//--------------------------------------------------------------------------------------
HRESULT Static::SetText( LPCWSTR strText )
{
	if( strText == NULL )
	{
		m_strText[0] = 0;
		return S_OK;
	}

	StringCchCopy( m_strText, MAX_PATH, strText); 
	return S_OK;
}





// end file