
#include "d3d9pch.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h> 
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>



//--------------------------------------------------------------------------------------
// Button class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
Button::Button( Dialog *pDialog )
{
	m_Type = MYUT_CONTROL_TYPE::BUTTON;
	m_pDialog = pDialog;

	m_bPressed = false;
	m_nHotkey = 0;
}

//--------------------------------------------------------------------------------------
bool Button::HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
					m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, true, this );
				}
				return true;
			}
		}
	}
	return false;
}


//--------------------------------------------------------------------------------------
bool Button::HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
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
				SetCapture(  this->m_pDialog->getHwnd() ); //  MYUTGetHWND() );

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

				if( !m_pDialog->m_bKeyboardInput )
					m_pDialog->ClearFocus();

				// Button click
				if( ContainsPoint( pt ) )
					m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, true, this );

				return true;
			}

			break;
		}
	};

	return false;
}

//--------------------------------------------------------------------------------------
void Button::Render( IDirect3DDevice9* pd3dDevice, float fElapsedTime )
{
	int nOffsetX = 0;
	int nOffsetY = 0;

	MYUT_CONTROL_STATE::e iState = MYUT_CONTROL_STATE::NORMAL;

	if( m_bVisible == false )
	{
		iState = MYUT_CONTROL_STATE::HIDDEN;
	}
	else if( m_bEnabled == false )
	{
		iState = MYUT_CONTROL_STATE::DISABLED;
	}
	else if( m_bPressed )
	{
		iState = MYUT_CONTROL_STATE::PRESSED;

		nOffsetX = 1;
		nOffsetY = 2;
	}
	else if( m_bMouseOver )
	{
		iState = MYUT_CONTROL_STATE::MOUSEOVER;

		nOffsetX = -1;
		nOffsetY = -2;
	}
	else if( m_bHasFocus )
	{
		iState = MYUT_CONTROL_STATE::FOCUS;
	}

	// Background fill layer
	//TODO: remove magic numbers
	Element* pElement = m_Elements.GetAt( 0 );

	float fBlendRate = ( iState == MYUT_CONTROL_STATE::PRESSED ) ? 0.0f : 0.8f;

	RECT rcWindow = m_rcBoundingBox;
	OffsetRect( &rcWindow, nOffsetX, nOffsetY );


	// Blend current color
	pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
	pElement->FontColor.Blend( iState, fElapsedTime, fBlendRate );

	m_pDialog->DrawSprite( pElement, &rcWindow );
	m_pDialog->DrawText( m_strText, pElement, &rcWindow );

	// Main button
	pElement = m_Elements.GetAt( 1 );


	// Blend current color
	pElement->TextureColor.Blend( iState, fElapsedTime, fBlendRate );
	pElement->FontColor.Blend( iState, fElapsedTime, fBlendRate );

	m_pDialog->DrawSprite( pElement, &rcWindow );
	m_pDialog->DrawText( m_strText, pElement, &rcWindow );
}









// end file