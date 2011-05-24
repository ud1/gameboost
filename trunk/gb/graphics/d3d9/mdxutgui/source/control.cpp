#include "d3d9pch.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h>
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>
#include <gb/macro.h>



//--------------------------------------------------------------------------------------
// Control class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
Control::Control( Dialog *pDialog )
{
	m_Type = MYUT_CONTROL_TYPE::BUTTON;
	m_pDialog = pDialog;
	m_ID = 0;
	m_Index = 0;
	m_pUserData = NULL;

	m_bEnabled = true;
	m_bVisible = true;
	m_bMouseOver = false;
	m_bHasFocus = false;
	m_bIsDefault = false;

	m_pDialog = NULL;

	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;

	ZeroMemory( &m_rcBoundingBox, sizeof( m_rcBoundingBox ) );
}


Control::~Control()
{
	for( int i = 0; i < m_Elements.GetSize(); ++i )
	{
		delete m_Elements[i];
	}
	m_Elements.RemoveAll();
}


//--------------------------------------------------------------------------------------
void Control::SetTextColor( D3DCOLOR Color )
{
	Element* pElement = m_Elements.GetAt( 0 );

	if( pElement )
		pElement->FontColor.States[MYUT_CONTROL_STATE::NORMAL] = Color;
}


//--------------------------------------------------------------------------------------
HRESULT Control::SetElement( UINT iElement, Element* pElement )
{
	HRESULT hr = S_OK;

	if( pElement == NULL )
		return E_INVALIDARG;

	// Make certain the array is this large
	for( UINT i=m_Elements.GetSize(); i <= iElement; i++ )
	{
		Element* pNewElement = new Element();
		if( pNewElement == NULL )
			return E_OUTOFMEMORY;

		hr = m_Elements.Add( pNewElement );
		if( FAILED(hr) )
		{
			GB_SAFE_DEL_OBJ( pNewElement );
			return hr;
		}
	}

	// Update the data
	Element* pCurElement = m_Elements.GetAt( iElement );
	*pCurElement = *pElement;

	return S_OK;
}


//--------------------------------------------------------------------------------------
void Control::Refresh()
{
	m_bMouseOver = false;
	m_bHasFocus = false;

	for( int i=0; i < m_Elements.GetSize(); i++ )
	{
		Element* pElement = m_Elements.GetAt( i );
		pElement->Refresh();
	}
}


//--------------------------------------------------------------------------------------
void Control::UpdateRects()
{
	SetRect( &m_rcBoundingBox, m_x, m_y, m_x + m_width, m_y + m_height );
}





// end file