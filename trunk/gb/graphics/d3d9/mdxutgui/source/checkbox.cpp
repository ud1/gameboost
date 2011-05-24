#include "d3d9pch.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h>
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>


#pragma warning(disable : 4996)

//--------------------------------------------------------------------------------------
// CheckBox class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
CheckBox::CheckBox( Dialog *pDialog )
{
	m_Type = MYUT_CONTROL_TYPE::CHECKBOX;
	m_pDialog = pDialog;

	m_bChecked = false;
}


//--------------------------------------------------------------------------------------
bool CheckBox::HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( !m_bEnabled || !m_bVisible )
		return false;

	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_SPACE:
				m_bPressed = true;
				return true;
			}
		}

	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_SPACE:
				if( m_bPressed == true )
				{
					m_bPressed = false;
					SetCheckedInternal( !m_bChecked, true );
				}
				return true;
			}
		}
	}
	return false;
}


//--------------------------------------------------------------------------------------
bool CheckBox::HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
	if( !m_bEnabled || !m_bVisible )
		return false;

	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			if( ContainsPoint( pt ) )
			{
				// Pressed while inside the control
				m_bPressed = true;
				SetCapture( this->m_pDialog->getHwnd() ); // MYUTGetHWND() );

				if( !m_bHasFocus )
					m_pDialog->RequestFocus( this );

				return true;
			}

			break;
		}

	case WM_LBUTTONUP:
		{
			if( m_bPressed )
			{
				m_bPressed = false;
				ReleaseCapture();

				// Button click
				if( ContainsPoint( pt ) )
					SetCheckedInternal( !m_bChecked, true );

				return true;
			}

			break;
		}
	};

	return false;
}


//--------------------------------------------------------------------------------------
void CheckBox::SetCheckedInternal( bool bChecked, bool bFromInput ) 
{ 
	m_bChecked = bChecked; 

	m_pDialog->SendEvent( EVENT_CHECKBOX_CHANGED, bFromInput, this ); 
}


//--------------------------------------------------------------------------------------
BOOL CheckBox::ContainsPoint( POINT pt ) 
{ 
	return ( PtInRect( &m_rcBoundingBox, pt ) || 
		PtInRect( &m_rcButton, pt ) ); 
}



//--------------------------------------------------------------------------------------
void CheckBox::UpdateRects()
{
	Button::UpdateRects();

	m_rcButton = m_rcBoundingBox;
	m_rcButton.right = m_rcButton.left + RectHeight( m_rcButton );

	m_rcText = m_rcBoundingBox;
	m_rcText.left += (int) ( 1.25f * RectWidth( m_rcButton ) );
}



//--------------------------------------------------------------------------------------
void CheckBox::Render( IDirect3DDevice9* pd3dDevice, float fElapsedTime )
{
	MYUT_CONTROL_STATE::e iState = MYUT_CONTROL_STATE::NORMAL;

	if( m_bVisible == false )
		iState = MYUT_CONTROL_STATE::HIDDEN;
	else if( m_bEnabled == false )
		iState = MYUT_CONTROL_STATE::DISABLED;
	else if( m_bPressed )
		iState = MYUT_CONTROL_STATE::PRESSED;
	else if( m_bMouseOver )
		iState = MYUT_CONTROL_STATE::MOUSEOVER;
	else if( m_bHasFocus )
		iState = MYUT_CONTROL_STATE::FOCUS;

	Element* pElement = m_Elements.GetAt( 0 );

	float fBlendRate = ( iState == MYUT_CONTROL_STATE::PRESSED ) ? 0.0f : 0.8f;

	pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
	pElement->FontColor.Blend( iState, fElapsedTime, fBlendRate );

	m_pDialog->DrawSprite( pElement, &m_rcButton );
	m_pDialog->DrawText( m_strText, pElement, &m_rcText, true );

	if( !m_bChecked )
		iState = MYUT_CONTROL_STATE::HIDDEN;

	pElement = m_Elements.GetAt( 1 );

	pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
	m_pDialog->DrawSprite( pElement, &m_rcButton );
}








// end file