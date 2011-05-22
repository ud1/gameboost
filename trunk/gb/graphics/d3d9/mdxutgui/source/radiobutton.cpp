#include "stdafx.h"
#include <gb/graphics/d3d9/mdxutgui/mdxutgui.h>
#include <gb/graphics/d3d9/mdxutgui/source/internal.h>


// radiobutton

//--------------------------------------------------------------------------------------
// RadioButton class
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
RadioButton::RadioButton( Dialog *pDialog )
{
	m_Type = MYUT_CONTROL_TYPE::RADIOBUTTON;
	m_pDialog = pDialog;
}



//--------------------------------------------------------------------------------------
bool RadioButton::HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam )
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

					m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );
					m_bChecked = !m_bChecked;

					m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, true, this );
				}
				return true;
			}
		}
	}
	return false;
}


//--------------------------------------------------------------------------------------
bool RadioButton::HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
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
				SetCapture(  this->m_pDialog->getHwnd() );

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
				{
					m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );
					m_bChecked = !m_bChecked;

					m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, true, this );
				}

				return true;
			}

			break;
		}
	};

	return false;
}

//--------------------------------------------------------------------------------------
void RadioButton::SetCheckedInternal( bool bChecked, bool bClearGroup, bool bFromInput )
{
	if( bChecked && bClearGroup )
		m_pDialog->ClearRadioButtonGroup( m_nButtonGroup );

	m_bChecked = bChecked;
	m_pDialog->SendEvent( EVENT_RADIOBUTTON_CHANGED, bFromInput, this );
}







// end file