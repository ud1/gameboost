/** \file


   Copyright (c) Microsoft Corporation. All rights reserved.
*/


#if ( defined(WIN32) && defined(GB_D3D9) )
 
#pragma once
#define __GB_D3D9_MDXUTGUI_H__

#ifndef STRICT
#define STRICT
#endif

// If app hasn't choosen, set to work with Windows 98, Windows Me, Windows 2000,
// Windows XP and beyond
#ifndef WINVER
#define WINVER         0x0410
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410 
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0500 
#endif


#include <gb/graphics/d3d9/auto_include_libr.h>
#include <d3d9.h>

#ifndef __D3DX9_H__
    #error NEED INCLUDE D3DX9
#endif
 
//#ifdef __D3DX9_H__	 // only with d3dx9


	#include <usp10.h>
	#include <dimm.h>


//	#include <windows.h>
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

	#if defined(DEBUG) || defined(_DEBUG)
		#include <crtdbg.h>
	#endif 


	//Header strsafe.h 
	//Import library strsafe.lib 
	// #include <strsafe.h>


#include <gb/graphics/d3d9/mdxutgui/source/templatedarray.h>



	//--------------------------------------------------------------------------------------
	// Defines and macros 
	//--------------------------------------------------------------------------------------
	#define EVENT_BUTTON_CLICKED                0x0101
	#define EVENT_COMBOBOX_SELECTION_CHANGED    0x0201
	#define EVENT_RADIOBUTTON_CHANGED           0x0301
	#define EVENT_CHECKBOX_CHANGED              0x0401
	#define EVENT_SLIDER_VALUE_CHANGED          0x0501
	#define EVENT_EDITBOX_STRING                0x0601
	// EVENT_EDITBOX_CHANGE is sent when the listbox content changes
	// due to user input.
	#define EVENT_EDITBOX_CHANGE                0x0602
	#define EVENT_LISTBOX_ITEM_DBLCLK           0x0701
	// EVENT_LISTBOX_SELECTION is fired off when the selection changes in
	// a single selection list box.
	#define EVENT_LISTBOX_SELECTION             0x0702
	#define EVENT_LISTBOX_SELECTION_END         0x0703


	//---------------------------------------------------------------
	// Forward declarations
	//---------------------------------------------------------------
	class DialogResourceManager;
	class Control;
	class Button;
	class Static;
	class CheckBox;
	class RadioButton;
	class ComboBox;
	class Slider;
	class EditBox;
	class IMEEditBox;
	class ListBox;
	class ScrollBar;
	class Element;
	struct ElementHolder;
	struct TextureNode;
	struct FontNode;
	
	typedef VOID( CALLBACK *PCALLBACKMYUTGUIEVENT ) ( UINT nEvent, int nControlID, Control *pControl, void *pUserContext );


 //! \brief Enum  for pre-defined control types
 struct MYUT_CONTROL_TYPE
 {
	enum  e
	{
			BUTTON, 
			STATIC, 
			CHECKBOX, 
			RADIOBUTTON, 
			COMBOBOX, 
			SLIDER, 
			EDITBOX, 
			IMEEDITBOX, 
			LISTBOX, 
			SCROLLBAR, 
	};
 };


 struct MYUT_CONTROL_STATE
 {
	enum e
	{
		NORMAL = 0, 
		DISABLED, 
		HIDDEN, 
		FOCUS, 
		MOUSEOVER, 
		PRESSED, 
	};
 };

	//#define MAX_CONTROL_STATES 6
  static const int MAX_CONTROL_STATES = 6;

	struct BlendColor
	{
		void Init( D3DCOLOR defaultColor, 
				   D3DCOLOR disabledColor = D3DCOLOR_ARGB( 200, 128, 128, 128 ), 
				   D3DCOLOR hiddenColor = 0 );
				   
		void Blend( UINT iState, float fElapsedTime, float fRate = 0.7f );

		D3DCOLOR States[ MAX_CONTROL_STATES ]; // Modulate colors for all possible control states
		D3DXCOLOR Current;
	};


	void setGlobalTime(double time);


	//! \brief Contains all the display tweakables for a sub-control
	class Element
	{
		public:
			void SetTexture( UINT iTexture, RECT *prcTexture, 
						D3DCOLOR defaultTextureColor = D3DCOLOR_ARGB( 255, 255, 255, 255 ) );

			void SetFont( UINT iFont, 
						D3DCOLOR defaultFontColor = D3DCOLOR_ARGB( 255, 255, 255, 255 ), 
						DWORD dwTextFormat = DT_CENTER | DT_VCENTER );

			void Refresh();

			UINT iTexture; ////< Index of the texture for this Element 
			UINT iFont; ////< Index of the font for this Element
			DWORD dwTextFormat; ////< The format argument to DrawText 

			RECT rcTexture; ///< Bounding rect of this element on the composite texture

			BlendColor TextureColor;
			BlendColor FontColor;
	};

 
	/** \brief     All controls must be assigned to a dialog, which handles
	         input and rendering for the controls.   */
	class Dialog
	{
			friend class DialogResourceManager;

		public:
			Dialog();
			// ks777: был невиртуальный!
			virtual ~Dialog();

			// Need to call this now
			void Init( DialogResourceManager *pManager, bool bRegisterDialog = true );
			void Init( DialogResourceManager *pManager, bool bRegisterDialog, LPCWSTR pszControlTextureFilename );
			void Init( DialogResourceManager *pManager, bool bRegisterDialog, LPCWSTR szControlTextureResourceName, HMODULE hControlTextureResourceModule );

			//! \brief  Windows message handler
			bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

			// Control creation
			
			HRESULT AddStatic(  int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, Static **ppCreated = NULL );
			HRESULT AddButton(  int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, Button **ppCreated = NULL );
			HRESULT AddCheckBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, CheckBox **ppCreated = NULL );
			HRESULT AddRadioButton( int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, RadioButton **ppCreated = NULL );
			HRESULT AddComboBox( int ID, int x, int y, int width, int height, UINT nHotKey = 0, bool bIsDefault = false, ComboBox **ppCreated = NULL );
			HRESULT AddSlider( int ID, int x, int y, int width, int height, int min = 0, int max = 100, int value = 50, bool bIsDefault = false, Slider **ppCreated = NULL );
			HRESULT AddEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, EditBox **ppCreated = NULL );
			HRESULT AddIMEEditBox( int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, IMEEditBox **ppCreated = NULL );
			HRESULT AddListBox( int ID, int x, int y, int width, int height, DWORD dwStyle = 0, ListBox **ppCreated = NULL );
			
			HRESULT AddControl( Control *pControl );
			HRESULT InitControl( Control *pControl );

			HWND getHwnd() const 
			{
				  return m_hwnd;
			}

			// Control retrieval
			Static *GetStatic( int ID )
			{
				return ( Static* )GetControl( ID, MYUT_CONTROL_TYPE::STATIC );
			}

			Button *GetButton( int ID )
			{
					return ( Button* )GetControl( ID, MYUT_CONTROL_TYPE::BUTTON );
			}

			CheckBox *GetCheckBox( int ID )
			{
					return ( CheckBox* )GetControl( ID, MYUT_CONTROL_TYPE::CHECKBOX );
			}

			RadioButton *GetRadioButton( int ID )
			{
					return ( RadioButton* )GetControl( ID, MYUT_CONTROL_TYPE::RADIOBUTTON );
			}

			ComboBox *GetComboBox( int ID )
			{
					return ( ComboBox* )GetControl( ID, MYUT_CONTROL_TYPE::COMBOBOX );
			}

			Slider *GetSlider( int ID )
			{
					return ( Slider* )GetControl( ID, MYUT_CONTROL_TYPE::SLIDER );
			}

			EditBox *GetEditBox( int ID )
			{
					return ( EditBox* )GetControl( ID, MYUT_CONTROL_TYPE::EDITBOX );
			}

			IMEEditBox *GetIMEEditBox( int ID )
			{
					return ( IMEEditBox* )GetControl( ID, MYUT_CONTROL_TYPE::IMEEDITBOX );
			}
			ListBox *GetListBox( int ID )
			{
					return ( ListBox* )GetControl( ID, MYUT_CONTROL_TYPE::LISTBOX );
			}

			Control *GetControl( int ID );
			Control *GetControl( int ID, UINT nControlType );
			Control *GetControlAtPoint( POINT pt );

			bool GetControlEnabled( int ID );
			void SetControlEnabled( int ID, bool bEnabled );

			void ClearRadioButtonGroup( UINT nGroup );
			void ClearComboBox( int ID );

			// Access the default display Elements used when adding new controls
			HRESULT SetDefaultElement( UINT nControlType, UINT iElement, Element *pElement );
			Element *GetDefaultElement( UINT nControlType, UINT iElement );

			// Methods called by controls
			void SendEvent( UINT nEvent, bool bTriggeredByUser, Control *pControl );
			void RequestFocus( Control *pControl );

			// Render helpers
			HRESULT DrawRect( RECT *pRect, D3DCOLOR color );
			HRESULT DrawPolyLine( POINT *apPoints, UINT nNumPoints, D3DCOLOR color );
			HRESULT DrawSprite( Element *pElement, RECT *prcDest );
			HRESULT CalcTextRect( LPCWSTR strText, Element *pElement, RECT *prcDest, int nCount =  - 1 );
			HRESULT DrawText( LPCWSTR strText, Element *pElement, RECT *prcDest, bool bShadow = false, int nCount =  - 1 );

			// Attributes
			bool GetVisible()
			{
					return m_bVisible;
			}
			void SetVisible( bool bVisible )
			{
					m_bVisible = bVisible;
			}
			bool GetMinimized()
			{
					return m_bMinimized;
			}
			void SetMinimized( bool bMinimized )
			{
					m_bMinimized = bMinimized;
			}
			void SetBackgroundColors( D3DCOLOR colorAllCorners )
			{
					SetBackgroundColors( colorAllCorners, colorAllCorners, colorAllCorners, colorAllCorners );
			}
			void SetBackgroundColors( D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight );
			void EnableCaption( bool bEnable )
			{
					m_bCaption = bEnable;
			}
			int GetCaptionHeight()const
			{
					return m_nCaptionHeight;
			}
			void SetCaptionHeight( int nHeight )
			{
					m_nCaptionHeight = nHeight;
			}
			void SetCaptionText( const WCHAR *pwszText ) ;

			void GetLocation( POINT &Pt )const
			{
					Pt.x = m_x;
					Pt.y = m_y;
			}
			void SetLocation( int x, int y )
			{
					m_x = x;
					m_y = y;
			}
			void SetSize( int width, int height )
			{
					m_width = width;
					m_height = height;
			}
			int GetWidth()
			{
					return m_width;
			}
			int GetHeight()
			{
					return m_height;
			}

			static void SetRefreshTime( float fTime )
			{
					s_fTimeRefresh = fTime;
			}

			static Control *GetNextControl( Control *pControl );
			static Control *GetPrevControl( Control *pControl );

			void RemoveControl( int ID );
			void RemoveAllControls();

			// Sets the callback used to notify the app of control events
			void SetCallback( PCALLBACKMYUTGUIEVENT pCallback, void *pUserContext = NULL );
			void EnableNonUserEvents( bool bEnable )
			{
					m_bNonUserEvents = bEnable;
			}
			void EnableKeyboardInput( bool bEnable )
			{
					m_bKeyboardInput = bEnable;
			}
			void EnableMouseInput( bool bEnable )
			{
					m_bMouseInput = bEnable;
			}
			bool IsKeyboardInputEnabled()const
			{
					return m_bKeyboardInput;
			}

			//! \brief  Device state notification
			void Refresh();

			HRESULT OnRender( float fElapsedTime );

			/** \brief Shared resource access. Indexed fonts and textures are shared among  all the controls.  */
			HRESULT SetFont( UINT index, LPCWSTR strFaceName, LONG height, LONG weight );
			FontNode *GetFont( UINT index );

			HRESULT SetTexture( UINT index, LPCWSTR strFilename );
			HRESULT SetTexture( UINT index, LPCWSTR strResourceName, HMODULE hResourceModule );
			TextureNode *GetTexture( UINT index );

			DialogResourceManager *GetManager()
			{
					return m_pManager;
			}

			static void ClearFocus();
			void FocusDefaultControl();

			bool m_bNonUserEvents;
			bool m_bKeyboardInput;
			bool m_bMouseInput;



		private:
			int m_nDefaultControlID;

			static double s_fTimeRefresh;
			double m_fTimeLastRefresh;

			//! \brief Initialize default Elements
			void InitDefaultElements();

			//! \brief Windows message handlers
			void OnMouseMove( POINT pt );
			void OnMouseUp( POINT pt );

			void SetNextDialog( Dialog *pNextDialog );

			//! \brief Control events
			bool OnCycleFocus( bool bForward );

			static Control *s_pControlFocus; //<   The control which has focus
			static Control *s_pControlPressed; //<   The control currently pressed

			Control *m_pControlMouseOver; //< The control which is hovered over

			bool m_bVisible;
			bool m_bCaption;
			bool m_bMinimized;
			bool m_bDrag;
			WCHAR m_wszCaption[ 256 ];

			int m_x;
			int m_y;
			int m_width;
			int m_height;
			int m_nCaptionHeight;

			D3DCOLOR m_colorTopLeft;
			D3DCOLOR m_colorTopRight;
			D3DCOLOR m_colorBottomLeft;
			D3DCOLOR m_colorBottomRight;

			DialogResourceManager *m_pManager;
			PCALLBACKMYUTGUIEVENT m_pCallbackEvent;
			void *m_pCallbackEventUserContext;

			TemplatedArray < int > m_Textures; // Index into m_TextureCache;
			TemplatedArray < int > m_Fonts; // Index into m_FontCache;

			TemplatedArray < Control * > m_Controls;
			TemplatedArray < ElementHolder * > m_DefaultElements;

			Element m_CapElement; // Element for the caption

			Dialog *m_pNextDialog;
			Dialog *m_pPrevDialog;

			HWND m_hwnd;
	};

 
	//! \brief Structs for shared resources
	struct TextureNode
	{
		bool bFileSource; // True if this texture is loaded from a file. False if from resource.
		HMODULE hResourceModule;
		int nResourceID; // Resource ID. If 0, string-based ID is used and stored in strFilename.
		WCHAR strFilename[ MAX_PATH ];
		IDirect3DTexture9 *pTexture;
		DWORD dwWidth;
		DWORD dwHeight;
	};

	struct FontNode
	{
		WCHAR strFace[ MAX_PATH ];
		ID3DXFont *pFont;
		LONG nHeight;
		LONG nWeight;
	};


	//! \brief Manages shared resources of dialogs
	class DialogResourceManager
	{
		public:
			DialogResourceManager();
			~DialogResourceManager();

			HRESULT OnCreateDevice( LPDIRECT3DDEVICE9 pd3dDevice );
			HRESULT OnResetDevice();
			void OnLostDevice();
			void OnDestroyDevice();
			bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

			int AddFont( LPCWSTR strFaceName, LONG height, LONG weight );
			int AddTexture( LPCWSTR strFilename );
			int AddTexture( LPCWSTR strResourceName, HMODULE hResourceModule );

			FontNode *GetFontNode( int iIndex )
			{
					return m_FontCache.GetAt( iIndex );
			};
			TextureNode *GetTextureNode( int iIndex )
			{
					return m_TextureCache.GetAt( iIndex );
			};
			IDirect3DDevice9 *GetD3DDevice()
			{
					return m_pd3dDevice;
			}

			bool RegisterDialog( Dialog *pDialog );
			void UnregisterDialog( Dialog *pDialog );
			void EnableKeyboardInputForAllDialogs();

			//! \brief Shared between all dialogs

			IDirect3DStateBlock9 *m_pStateBlock;
			ID3DXSprite *m_pSprite; // Sprite used for drawing

			TemplatedArray < Dialog * > m_Dialogs; // Dialogs registered

		protected:

			TemplatedArray < TextureNode * > m_TextureCache; // Shared textures
			TemplatedArray < FontNode * > m_FontCache; // Shared fonts

			IDirect3DDevice9 *m_pd3dDevice;

			// Resource creation helpers
			HRESULT CreateFont( UINT index );
			HRESULT CreateTexture( UINT index );
	};

	//! \brief Base class for controls
	class Control
	{
		public:
			Control( Dialog *pDialog = NULL );
			virtual ~Control();

			virtual HRESULT OnInit()
			{
					return S_OK;
			}
			virtual void Refresh();
			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime ){}
			;

			//! \brief   Windows message handler
			virtual bool MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
			{
					return false;
			}

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam )
			{
					return false;
			}
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
			{
					return false;
			}

			virtual bool CanHaveFocus()
			{
					return false;
			}
			virtual void OnFocusIn()
			{
					m_bHasFocus = true;
			}
			virtual void OnFocusOut()
			{
					m_bHasFocus = false;
			}
			virtual void OnMouseEnter()
			{
					m_bMouseOver = true;
			}
			virtual void OnMouseLeave()
			{
					m_bMouseOver = false;
			}
			virtual void OnHotkey(){}

			virtual BOOL ContainsPoint( POINT pt )
			{
					return PtInRect( &m_rcBoundingBox, pt );
			}

			virtual void SetEnabled( bool bEnabled )
			{
					m_bEnabled = bEnabled;
			}
			virtual bool GetEnabled()
			{
					return m_bEnabled;
			}
			virtual void SetVisible( bool bVisible )
			{
					m_bVisible = bVisible;
			}
			virtual bool GetVisible()
			{
					return m_bVisible;
			}

			UINT GetType()const
			{
					return m_Type;
			}

			int GetID()const
			{
					return m_ID;
			}
			void SetID( int ID )
			{
					m_ID = ID;
			}

			void SetLocation( int x, int y )
			{
					m_x = x;
					m_y = y;
					UpdateRects();
			}
			void SetSize( int width, int height )
			{
					m_width = width;
					m_height = height;
					UpdateRects();
			}

			void SetHotkey( UINT nHotkey )
			{
					m_nHotkey = nHotkey;
			}
			UINT GetHotkey()
			{
					return m_nHotkey;
			}

			void SetUserData( void *pUserData )
			{
					m_pUserData = pUserData;
			}
			void *GetUserData()const
			{
					return m_pUserData;
			}

			virtual void SetTextColor( D3DCOLOR Color );
			Element *GetElement( UINT iElement )
			{
					return m_Elements.GetAt( iElement );
			}
			HRESULT SetElement( UINT iElement, Element *pElement );

			bool m_bVisible; // Shown/hidden flag
			bool m_bMouseOver; // Mouse pointer is above control
			bool m_bHasFocus; // Control has input focus
			bool m_bIsDefault; // Is the default control

			//!   Size, scale, and positioning members
			int m_x, m_y;
			int m_width, m_height;

			//! These members are set by the container
			Dialog *m_pDialog; // Parent container
			UINT m_Index; // Index within the control list

			TemplatedArray < Element * > m_Elements; // All display elements

		protected:
			virtual void UpdateRects();

			int m_ID; // ID number
			MYUT_CONTROL_TYPE::e m_Type; // Control type, set once in constructor  
			UINT m_nHotkey; // Virtual key code for this control's hotkey
			void *m_pUserData; // Data associated with this control that is set by user.

			bool m_bEnabled; // Enabled/disabled flag

			RECT m_rcBoundingBox; // Rectangle defining the active region of the control
	};


	//! \brief    Contains all the display information for a given control type
	struct ElementHolder
	{
		UINT nControlType;
		UINT iElement;

		Element Element;
	};


 
	//! \brief    Static control
	class Static: public Control
	{
		public:
			Static( Dialog *pDialog = NULL );

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual BOOL ContainsPoint( POINT pt )
			{
					return false;
			}

			HRESULT GetTextCopy( LPWSTR strDest, UINT bufferCount );
			LPCWSTR GetText()
			{
					return m_strText;
			}
			HRESULT SetText( LPCWSTR strText );


		protected:
			WCHAR m_strText[ MAX_PATH ]; // Window text  
	};


 
	//! \brief    Button control
	class Button: public Static
	{
		public:
			Button( Dialog *pDialog = NULL );

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual void OnHotkey()
			{
					if ( m_pDialog->IsKeyboardInputEnabled() )
					{
						m_pDialog->RequestFocus( this );
					}
					m_pDialog->SendEvent( EVENT_BUTTON_CLICKED, true, this );
			}

			virtual BOOL ContainsPoint( POINT pt )
			{
					return PtInRect( &m_rcBoundingBox, pt );
			}
			virtual bool CanHaveFocus()
			{
					return ( m_bVisible && m_bEnabled );
			}

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );

		protected:
			bool m_bPressed;
	};


 
	//! \brief   CheckBox control
	class CheckBox: public Button
	{
		public:
			CheckBox( Dialog *pDialog = NULL );

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual void OnHotkey()
			{
					if ( m_pDialog->IsKeyboardInputEnabled() )
					{
						m_pDialog->RequestFocus( this );
					}
					SetCheckedInternal( !m_bChecked, true );
			}

			virtual BOOL ContainsPoint( POINT pt );
			virtual void UpdateRects();

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );

			bool GetChecked()
			{
					return m_bChecked;
			}
			void SetChecked( bool bChecked )
			{
					SetCheckedInternal( bChecked, false );
			}

		protected:
			virtual void SetCheckedInternal( bool bChecked, bool bFromInput );

			bool m_bChecked;
			RECT m_rcButton;
			RECT m_rcText;
	};


 
	//! \brief    RadioButton control
	class RadioButton: public CheckBox
	{
		public:
			RadioButton( Dialog *pDialog = NULL );

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual void OnHotkey()
			{
					if ( m_pDialog->IsKeyboardInputEnabled() )
					{
						m_pDialog->RequestFocus( this );
					}
					SetCheckedInternal( true, true, true );
			}

			void SetChecked( bool bChecked, bool bClearGroup = true )
			{
					SetCheckedInternal( bChecked, bClearGroup, false );
			}
			void SetButtonGroup( UINT nButtonGroup )
			{
					m_nButtonGroup = nButtonGroup;
			}
			UINT GetButtonGroup()
			{
					return m_nButtonGroup;
			}

		protected:
			virtual void SetCheckedInternal( bool bChecked, bool bClearGroup, bool bFromInput );
			UINT m_nButtonGroup;
	};


 
	//! \brief    Scrollbar control
	class ScrollBar: public Control
	{
		public:
			ScrollBar( Dialog *pDialog = NULL );
			virtual ~ScrollBar();

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual bool MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual void UpdateRects();

			void SetTrackRange( int nStart, int nEnd );
			int GetTrackPos()
			{
					return m_nPosition;
			}
			void SetTrackPos( int nPosition )
			{
					m_nPosition = nPosition;
					Cap();
					UpdateThumbRect();
			}
			int GetPageSize()
			{
					return m_nPageSize;
			}
			void SetPageSize( int nPageSize )
			{
					m_nPageSize = nPageSize;
					Cap();
					UpdateThumbRect();
			}

			void Scroll( int nDelta ); // Scroll by nDelta items (plus or minus)
			void ShowItem( int nIndex ); // Ensure that item nIndex is displayed, scroll if necessary

		protected:
			// ARROWSTATE indicates the state of the arrow buttons.
			// CLEAR            No arrow is down.
			// CLICKED_UP       Up arrow is clicked.
			// CLICKED_DOWN     Down arrow is clicked.
			// HELD_UP          Up arrow is held down for sustained period.
			// HELD_DOWN        Down arrow is held down for sustained period.
			enum ARROWSTATE
			{
					CLEAR, CLICKED_UP, CLICKED_DOWN, HELD_UP, HELD_DOWN
			};

			void UpdateThumbRect();
			void Cap(); // Clips position at boundaries. Ensures it stays within legal range.

			bool m_bShowThumb;
			bool m_bDrag;
			RECT m_rcUpButton;
			RECT m_rcDownButton;
			RECT m_rcTrack;
			RECT m_rcThumb;
			int m_nPosition; // Position of the first displayed item
			int m_nPageSize; // How many items are displayable in one page
			int m_nStart; // First item
			int m_nEnd; // The index after the last item
			POINT m_LastMouse; // Last mouse position
			ARROWSTATE m_Arrow; // State of the arrows
			double m_dArrowTS; // Timestamp of last arrow event.
	};


	//! \brief    ListBox control
	struct ListBoxItem
	{
		WCHAR strText[ 256 ];
		void *pData;

		RECT rcActive;
		bool bSelected;
	};

	class ListBox: public Control
	{
		public:
			ListBox( Dialog *pDialog = NULL );
			virtual ~ListBox();

			virtual HRESULT OnInit()
			{
					return m_pDialog->InitControl( &m_ScrollBar );
			}
			virtual bool CanHaveFocus()
			{
					return ( m_bVisible && m_bEnabled );
			}
			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual bool MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual void UpdateRects();

			DWORD GetStyle()const
			{
					return m_dwStyle;
			}
			int GetSize()const
			{
					return m_Items.GetSize();
			}
			void SetStyle( DWORD dwStyle )
			{
					m_dwStyle = dwStyle;
			}
			int GetScrollBarWidth()const
			{
					return m_nSBWidth;
			}
			void SetScrollBarWidth( int nWidth )
			{
					m_nSBWidth = nWidth;
					UpdateRects();
			}
			void SetBorder( int nBorder, int nMargin )
			{
					m_nBorder = nBorder;
					m_nMargin = nMargin;
			}
			HRESULT AddItem( const WCHAR *wszText, void *pData );
			HRESULT InsertItem( int nIndex, const WCHAR *wszText, void *pData );
			void RemoveItem( int nIndex );
			void RemoveItemByText( WCHAR *wszText );
			void RemoveItemByData( void *pData );
			void RemoveAllItems();

			ListBoxItem *GetItem( int nIndex );
			int GetSelectedIndex( int nPreviousSelected =  - 1 );
			ListBoxItem *GetSelectedItem( int nPreviousSelected =  - 1 )
			{
					return GetItem( GetSelectedIndex( nPreviousSelected ) );
			}
			void SelectItem( int nNewIndex );

			enum STYLE
			{
					MULTISELECTION = 1
			};

		protected:
			RECT m_rcText; // Text rendering bound
			RECT m_rcSelection; // Selection box bound
			ScrollBar m_ScrollBar;
			int m_nSBWidth;
			int m_nBorder;
			int m_nMargin;
			int m_nTextHeight; // Height of a single line of text
			DWORD m_dwStyle; // List box style
			int m_nSelected; // Index of the selected item for single selection list box
			int m_nSelStart; // Index of the item where selection starts (for handling multi-selection)
			bool m_bDrag; // Whether the user is dragging the mouse to select

			TemplatedArray < ListBoxItem * > m_Items;
	};


 
	//! \brief    ComboBox control
	struct ComboBoxItem
	{
		WCHAR strText[ 256 ];
		void *pData;

		RECT rcActive;
		bool bVisible;
	};


	class ComboBox: public Button
	{
		public:
			ComboBox( Dialog *pDialog = NULL );
			virtual ~ComboBox();

			virtual void SetTextColor( D3DCOLOR Color );
			virtual HRESULT OnInit()
			{
					return m_pDialog->InitControl( &m_ScrollBar );
			}

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual void OnHotkey();

			virtual bool CanHaveFocus()
			{
					return ( m_bVisible && m_bEnabled );
			}
			virtual void OnFocusOut();
			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );

			virtual void UpdateRects();

			HRESULT AddItem( const WCHAR *strText, void *pData );
			void RemoveAllItems();
			void RemoveItem( UINT index );
			bool ContainsItem( const WCHAR *strText, UINT iStart = 0 );
			int FindItem( const WCHAR *strText, UINT iStart = 0 );
			void *GetItemData( const WCHAR *strText );
			void *GetItemData( int nIndex );
			void SetDropHeight( UINT nHeight )
			{
					m_nDropHeight = nHeight;
					UpdateRects();
			}
			int GetScrollBarWidth()const
			{
					return m_nSBWidth;
			}
			void SetScrollBarWidth( int nWidth )
			{
					m_nSBWidth = nWidth;
					UpdateRects();
			}

			void *GetSelectedData();
			ComboBoxItem *GetSelectedItem();

			UINT GetNumItems()
			{
					return m_Items.GetSize();
			}
			ComboBoxItem *GetItem( UINT index )
			{
					return m_Items.GetAt( index );
			}

			HRESULT SetSelectedByIndex( UINT index );
			HRESULT SetSelectedByText( const WCHAR *strText );
			HRESULT SetSelectedByData( void *pData );

		protected:
			int m_iSelected;
			int m_iFocused;
			int m_nDropHeight;
			ScrollBar m_ScrollBar;
			int m_nSBWidth;

			bool m_bOpened;

			RECT m_rcText;
			RECT m_rcButton;
			RECT m_rcDropdown;
			RECT m_rcDropdownText;


			TemplatedArray < ComboBoxItem * > m_Items;
	};

 
	//! \brief    Slider control
	class Slider: public Control
	{
		public:
			Slider( Dialog *pDialog = NULL );

			virtual BOOL ContainsPoint( POINT pt );
			virtual bool CanHaveFocus()
			{
					return ( m_bVisible && m_bEnabled );
			}
			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );

			virtual void UpdateRects();

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );

			void SetValue( int nValue )
			{
					SetValueInternal( nValue, false );
			}
			int GetValue()const
			{
					return m_nValue;
			};

			void GetRange( int &nMin, int &nMax )const
			{
					nMin = m_nMin;
					nMax = m_nMax;
			}
			void SetRange( int nMin, int nMax );

		protected:
			void SetValueInternal( int nValue, bool bFromInput );
			int ValueFromPos( int x );

			int m_nValue;

			int m_nMin;
			int m_nMax;

			int m_nDragX; // Mouse position at start of drag
			int m_nDragOffset; // Drag offset from the center of the button
			int m_nButtonX;

			bool m_bPressed;
			RECT m_rcButton;
	};


 
	//! \brief    UniBuffer class for the edit control
	class UniBuffer
	{
		public:
			UniBuffer( int nInitialSize = 1 );
			~UniBuffer();

			static void Initialize();
			static void Uninitialize();

			int GetBufferSize()
			{
					return m_nBufferSize;
			}
			bool SetBufferSize( int nSize );
			int GetTextSize()
			{
					return lstrlenW( m_pwszBuffer );
			}
			const WCHAR *GetBuffer()
			{
					return m_pwszBuffer;
			}
			const WCHAR &operator[ ]( int n )const
			{
					return m_pwszBuffer[ n ];
			}
			WCHAR &operator[ ]( int n );
			FontNode *GetFontNode()
			{
					return m_pFontNode;
			}
			void SetFontNode( FontNode *pFontNode )
			{
					m_pFontNode = pFontNode;
			}
			void Clear();

			bool InsertChar( int nIndex, WCHAR wChar ); // Inserts the char at specified index. If nIndex == -1, insert to the end.
			bool RemoveChar( int nIndex ); // Removes the char at specified index. If nIndex == -1, remove the last char.
			bool InsertString( int nIndex, const WCHAR *pStr, int nCount =  - 1 ); // Inserts the first nCount characters of the string pStr at specified index.  If nCount == -1, the entire string is inserted. If nIndex == -1, insert to the end.
			bool SetText( LPCWSTR wszText );

			// Uniscribe
			HRESULT CPtoX( int nCP, BOOL bTrail, int *pX );
			HRESULT XtoCP( int nX, int *pCP, int *pnTrail );
			void GetPriorItemPos( int nCP, int *pPrior );
			void GetNextItemPos( int nCP, int *pPrior );

		private:
			HRESULT Analyse(); // Uniscribe -- Analyse() analyses the string in the buffer

			WCHAR *m_pwszBuffer; // Buffer to hold text
			int m_nBufferSize; // Size of the buffer allocated, in characters

			// Uniscribe-specific
			FontNode *m_pFontNode; // Font node for the font that this buffer uses
			bool m_bAnalyseRequired; // True if the string has changed since last analysis.
			SCRIPT_STRING_ANALYSIS m_Analysis; // Analysis for the current string

		private:
			// Empty implementation of the Uniscribe API
			static HRESULT WINAPI Dummy_ScriptApplyDigitSubstitution( const SCRIPT_DIGITSUBSTITUTE *, SCRIPT_CONTROL *, SCRIPT_STATE* )
			{
					return E_NOTIMPL;
			}
			static HRESULT WINAPI Dummy_ScriptStringAnalyse( HDC, const void *, int, int, int, DWORD, int, SCRIPT_CONTROL *, SCRIPT_STATE *, const int *, SCRIPT_TABDEF *, const BYTE *, SCRIPT_STRING_ANALYSIS* )
			{
					return E_NOTIMPL;
			}
			static HRESULT WINAPI Dummy_ScriptStringCPtoX( SCRIPT_STRING_ANALYSIS, int, BOOL, int* )
			{
					return E_NOTIMPL;
			}
			static HRESULT WINAPI Dummy_ScriptStringXtoCP( SCRIPT_STRING_ANALYSIS, int, int *, int* )
			{
					return E_NOTIMPL;
			}
			static HRESULT WINAPI Dummy_ScriptStringFree( SCRIPT_STRING_ANALYSIS* )
			{
					return E_NOTIMPL;
			}
			static const SCRIPT_LOGATTR *WINAPI Dummy_ScriptString_pLogAttr( SCRIPT_STRING_ANALYSIS )
			{
					return NULL;
			}
			static const int *WINAPI Dummy_ScriptString_pcOutChars( SCRIPT_STRING_ANALYSIS )
			{
					return NULL;
			}

			// Function pointers
			static HRESULT( WINAPI *_ScriptApplyDigitSubstitution ) ( const SCRIPT_DIGITSUBSTITUTE *, SCRIPT_CONTROL *, SCRIPT_STATE* );
			static HRESULT( WINAPI *_ScriptStringAnalyse ) ( HDC, const void *, int, int, int, DWORD, int, SCRIPT_CONTROL *, SCRIPT_STATE *, const int *, SCRIPT_TABDEF *, const BYTE *, SCRIPT_STRING_ANALYSIS* );
			static HRESULT( WINAPI *_ScriptStringCPtoX ) ( SCRIPT_STRING_ANALYSIS, int, BOOL, int* );
			static HRESULT( WINAPI *_ScriptStringXtoCP ) ( SCRIPT_STRING_ANALYSIS, int, int *, int* );
			static HRESULT( WINAPI *_ScriptStringFree ) ( SCRIPT_STRING_ANALYSIS* );
			static const SCRIPT_LOGATTR *( WINAPI *_ScriptString_pLogAttr ) ( SCRIPT_STRING_ANALYSIS );
			static const int *( WINAPI *_ScriptString_pcOutChars ) ( SCRIPT_STRING_ANALYSIS );

			static HINSTANCE s_hDll; // Uniscribe DLL handle

	};

 
	//! \brief    EditBox control
	class EditBox: public Control
	{
		public:
			EditBox( Dialog *pDialog = NULL );
			virtual ~EditBox();

			virtual bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual bool MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual void UpdateRects();
			virtual bool CanHaveFocus()
			{
					return ( m_bVisible && m_bEnabled );
			}
			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual void OnFocusIn();

			void SetText( LPCWSTR wszText, bool bSelected = false );
			LPCWSTR GetText()
			{
					return m_Buffer.GetBuffer();
			}

			// Returns text length in chars excluding NULL.
			int GetTextLength()
			{
					return m_Buffer.GetTextSize();
			} 
			

			HRESULT GetTextCopy( LPWSTR strDest, UINT bufferCount );
			void ClearText();

			 // Text color
			virtual void SetTextColor( D3DCOLOR Color )
			{
					m_TextColor = Color;
			}

			// Selected text color
			void SetSelectedTextColor( D3DCOLOR Color )
			{
					m_SelTextColor = Color;
			} 
			
			// Selected background color
			void SetSelectedBackColor( D3DCOLOR Color )
			{
					m_SelBkColor = Color;
			}
			
			// Caret color
			void SetCaretColor( D3DCOLOR Color )
			{
					m_CaretColor = Color;
			}

			// Border of the window
			void SetBorderWidth( int nBorder )
			{
					m_nBorder = nBorder;
					UpdateRects();
			}
			
			void SetSpacing( int nSpacing )
			{
					m_nSpacing = nSpacing;
					UpdateRects();
			}
			void ParseFloatArray( float *pNumbers, int nCount );
			void SetTextFloatArray( const float *pNumbers, int nCount );

		protected:
			void PlaceCaret( int nCP );
			void DeleteSelectionText();
			void ResetCaretBlink();
			void CopyToClipboard();
			void PasteFromClipboard();

			UniBuffer m_Buffer; // Buffer to hold text
			int m_nBorder; // Border of the window
			int m_nSpacing; // Spacing between the text and the edge of border
			RECT m_rcText; // Bounding rectangle for the text
			RECT m_rcRender[ 9 ]; // Convenient rectangles for rendering elements
			double m_dfBlink; // Caret blink time in milliseconds
			double m_dfLastBlink; // Last timestamp of caret blink
			bool m_bCaretOn; // Flag to indicate whether caret is currently visible
			int m_nCaret; // Caret position, in characters
			bool m_bInsertMode; // If true, control is in insert mode. Else, overwrite mode.
			int m_nSelStart; // Starting position of the selection. The caret marks the end.
			int m_nFirstVisible; // First visible character in the edit control
			D3DCOLOR m_TextColor; // Text color
			D3DCOLOR m_SelTextColor; // Selected text color
			D3DCOLOR m_SelBkColor; // Selected background color
			D3DCOLOR m_CaretColor; // Caret color

			// Mouse-specific
			bool m_bMouseDrag; // True to indicate drag in progress

			// Static
			static bool s_bHideCaret; // If true, we don't render the caret.
	};


	//-----------------------------------------------------------------------------
	// IME-enabled EditBox control
	//-----------------------------------------------------------------------------


    //#define MAX_CANDLIST 10
	//#define MAX_COMPSTRING_SIZE 256
   static const int MAX_CANDLIST  = 10;
   static const int MAX_COMPSTRING_SIZE = 256;



	class IMEEditBox: public EditBox
	{
		protected:
			// Empty implementation of the IMM32 API
			static INPUTCONTEXT *WINAPI Dummy_ImmLockIMC( HIMC )
			{
					return NULL;
			}
			static BOOL WINAPI Dummy_ImmUnlockIMC( HIMC )
			{
					return FALSE;
			}
			static LPVOID WINAPI Dummy_ImmLockIMCC( HIMCC )
			{
					return NULL;
			}
			static BOOL WINAPI Dummy_ImmUnlockIMCC( HIMCC )
			{
					return FALSE;
			}
			static BOOL WINAPI Dummy_ImmDisableTextFrameService( DWORD )
			{
					return TRUE;
			}
			static LONG WINAPI Dummy_ImmGetCompositionStringW( HIMC, DWORD, LPVOID, DWORD )
			{
					return IMM_ERROR_GENERAL;
			}
			static DWORD WINAPI Dummy_ImmGetCandidateListW( HIMC, DWORD, LPCANDIDATELIST, DWORD )
			{
					return 0;
			}
			static HIMC WINAPI Dummy_ImmGetContext( HWND )
			{
					return NULL;
			}
			static BOOL WINAPI Dummy_ImmReleaseContext( HWND, HIMC )
			{
					return FALSE;
			}
			static HIMC WINAPI Dummy_ImmAssociateContext( HWND, HIMC )
			{
					return NULL;
			}
			static BOOL WINAPI Dummy_ImmGetOpenStatus( HIMC )
			{
					return 0;
			}
			static BOOL WINAPI Dummy_ImmSetOpenStatus( HIMC, BOOL )
			{
					return 0;
			}
			static BOOL WINAPI Dummy_ImmGetConversionStatus( HIMC, LPDWORD, LPDWORD )
			{
					return 0;
			}
			static HWND WINAPI Dummy_ImmGetDefaultIMEWnd( HWND )
			{
					return NULL;
			}
			static UINT WINAPI Dummy_ImmGetIMEFileNameA( HKL, LPSTR, UINT )
			{
					return 0;
			}
			static UINT WINAPI Dummy_ImmGetVirtualKey( HWND )
			{
					return 0;
			}
			static BOOL WINAPI Dummy_ImmNotifyIME( HIMC, DWORD, DWORD, DWORD )
			{
					return FALSE;
			}
			static BOOL WINAPI Dummy_ImmSetConversionStatus( HIMC, DWORD, DWORD )
			{
					return FALSE;
			}
			static BOOL WINAPI Dummy_ImmSimulateHotKey( HWND, DWORD )
			{
					return FALSE;
			}
			static BOOL WINAPI Dummy_ImmIsIME( HKL )
			{
					return FALSE;
			}

			// Traditional Chinese IME
			static UINT WINAPI Dummy_GetReadingString( HIMC, UINT, LPWSTR, PINT, BOOL *, PUINT )
			{
					return 0;
			}
			static BOOL WINAPI Dummy_ShowReadingWindow( HIMC, BOOL )
			{
					return FALSE;
			}

			// Verion library imports
			static BOOL APIENTRY Dummy_VerQueryValueA( const LPVOID, LPSTR, LPVOID *, PUINT )
			{
					return 0;
			}
			static BOOL APIENTRY Dummy_GetFileVersionInfoA( LPSTR, DWORD, DWORD, LPVOID )
			{
					return 0;
			}
			static DWORD APIENTRY Dummy_GetFileVersionInfoSizeA( LPSTR, LPDWORD )
			{
					return 0;
			}

			// Function pointers: IMM32
			static INPUTCONTEXT *( WINAPI *_ImmLockIMC ) ( HIMC );
			static BOOL( WINAPI *_ImmUnlockIMC ) ( HIMC );
			static LPVOID( WINAPI *_ImmLockIMCC ) ( HIMCC );
			static BOOL( WINAPI *_ImmUnlockIMCC ) ( HIMCC );
			static BOOL( WINAPI *_ImmDisableTextFrameService ) ( DWORD );
			static LONG( WINAPI *_ImmGetCompositionStringW ) ( HIMC, DWORD, LPVOID, DWORD );
			static DWORD( WINAPI *_ImmGetCandidateListW ) ( HIMC, DWORD, LPCANDIDATELIST, DWORD );
			static HIMC( WINAPI *_ImmGetContext ) ( HWND );
			static BOOL( WINAPI *_ImmReleaseContext ) ( HWND, HIMC );
			static HIMC( WINAPI *_ImmAssociateContext ) ( HWND, HIMC );
			static BOOL( WINAPI *_ImmGetOpenStatus ) ( HIMC );
			static BOOL( WINAPI *_ImmSetOpenStatus ) ( HIMC, BOOL );
			static BOOL( WINAPI *_ImmGetConversionStatus ) ( HIMC, LPDWORD, LPDWORD );
			static HWND( WINAPI *_ImmGetDefaultIMEWnd ) ( HWND );
			static UINT( WINAPI *_ImmGetIMEFileNameA ) ( HKL, LPSTR, UINT );
			static UINT( WINAPI *_ImmGetVirtualKey ) ( HWND );
			static BOOL( WINAPI *_ImmNotifyIME ) ( HIMC, DWORD, DWORD, DWORD );
			static BOOL( WINAPI *_ImmSetConversionStatus ) ( HIMC, DWORD, DWORD );
			static BOOL( WINAPI *_ImmSimulateHotKey ) ( HWND, DWORD );
			static BOOL( WINAPI *_ImmIsIME ) ( HKL );

			// Function pointers: Traditional Chinese IME
			static UINT( WINAPI *_GetReadingString ) ( HIMC, UINT, LPWSTR, PINT, BOOL *, PUINT );
			static BOOL( WINAPI *_ShowReadingWindow ) ( HIMC, BOOL );

			// Function pointers: Verion library imports
			static BOOL( APIENTRY *_VerQueryValueA ) ( const LPVOID, LPSTR, LPVOID *, PUINT );
			static BOOL( APIENTRY *_GetFileVersionInfoA ) ( LPSTR, DWORD, DWORD, LPVOID );
			static DWORD( APIENTRY *_GetFileVersionInfoSizeA ) ( LPSTR, LPDWORD );

		public:
			IMEEditBox( Dialog *pDialog = NULL );
			virtual ~IMEEditBox();

			static void Initialize();
			static void Uninitialize();

			static HRESULT StaticOnCreateDevice();
			static bool StaticMsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );

			static void EnableImeSystem( bool bEnable );

			virtual void Render( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual bool MsgProc( UINT uMsg, WPARAM wParam, LPARAM lParam );
			virtual bool HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam );
			virtual void UpdateRects();
			virtual void OnFocusIn();
			virtual void OnFocusOut();

			void PumpMessage();

			virtual void RenderCandidateReadingWindow( IDirect3DDevice9 *pd3dDevice, float fElapsedTime, bool bReading );
			virtual void RenderComposition( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );
			virtual void RenderIndicator( IDirect3DDevice9 *pd3dDevice, float fElapsedTime );

		protected:
			static WORD GetLanguage()
			{
					return LOWORD( s_hklCurrent );
			}
			static WORD GetPrimaryLanguage()
			{
					return PRIMARYLANGID( LOWORD( s_hklCurrent ) );
			}
			static WORD GetSubLanguage()
			{
					return SUBLANGID( LOWORD( s_hklCurrent ) );
			}
			static void SendKey( BYTE nVirtKey );
			static DWORD GetImeId( UINT uIndex = 0 );
			static void CheckInputLocale();
			static void CheckToggleState();
			static void SetupImeApi();
			static void ResetCompositionString();
			void TruncateCompString( bool bUseBackSpace = true, int iNewStrLen = 0 );
			void FinalizeString( bool bSend );
			static void GetReadingWindowOrientation( DWORD dwId );
			static void GetPrivateReadingString();

			void SendCompString();

		protected:
			enum
			{
					INDICATOR_NON_IME, INDICATOR_CHS, INDICATOR_CHT, INDICATOR_KOREAN, INDICATOR_JAPANESE
			};
			enum IMESTATE
			{
					IMEUI_STATE_OFF, IMEUI_STATE_ON, IMEUI_STATE_ENGLISH
			};

			struct CCandList
			{
					WCHAR awszCandidate[ MAX_CANDLIST][ 256 ];
					UniBuffer HoriCand; // Candidate list string (for horizontal candidate window)
					int nFirstSelected; // First character position of the selected string in HoriCand
					int nHoriSelectedLen; // Length of the selected string in HoriCand
					DWORD dwCount; // Number of valid entries in the candidate list
					DWORD dwSelection; // Currently selected candidate entry relative to page top
					DWORD dwPageSize;
					int nReadingError; // Index of the error character
					bool bShowWindow; // Whether the candidate list window is visible
					RECT rcCandidate; // Candidate rectangle computed and filled each time before rendered
			};

			struct CInputLocale
			{
					HKL m_hKL; // Keyboard layout
					WCHAR m_wszLangAbb[ 3 ]; // Language abbreviation
					WCHAR m_wszLang[ 64 ]; // Localized language name
			};

			// Application-wide data
			static HINSTANCE s_hDllImm32; // IMM32 DLL handle
			static HINSTANCE s_hDllVer; // Version DLL handle
			static HIMC s_hImcDef; // Default input context

			static HKL s_hklCurrent; // Current keyboard layout of the process
			static bool s_bVerticalCand; // Indicates that the candidates are listed vertically
			static LPWSTR s_wszCurrIndicator; // Points to an indicator string that corresponds to current input locale
			static WCHAR s_aszIndicator[ 5][ 3 ]; // String to draw to indicate current input locale
			static bool s_bInsertOnType; // Insert the character as soon as a key is pressed (Korean behavior)
			static HINSTANCE s_hDllIme; // Instance handle of the current IME module
			static IMESTATE s_ImeState; // IME global state
			static bool s_bEnableImeSystem; // Whether the IME system is active
			static POINT s_ptCompString; // Composition string position. Updated every frame.
			static int s_nCompCaret; // Caret position of the composition string
			static int s_nFirstTargetConv; // Index of the first target converted char in comp string.  If none, -1.
			static UniBuffer s_CompString; // Buffer to hold the composition string (we fix its length)
			static BYTE s_abCompStringAttr[ MAX_COMPSTRING_SIZE ];
			static DWORD s_adwCompStringClause[ MAX_COMPSTRING_SIZE ];
			static WCHAR s_wszReadingString[ 32 ]; // Used only with horizontal reading window (why?)
			static CCandList s_CandList; // Data relevant to the candidate list
			static bool s_bShowReadingWindow; // Indicates whether reading window is visible
			static bool s_bHorizontalReading; // Indicates whether the reading window is vertical or horizontal
			static bool s_bChineseIME;
			static TemplatedArray < CInputLocale > s_Locale; // Array of loaded keyboard layout on system

			// Color of various IME elements
			D3DCOLOR m_ReadingColor; ///< Reading string color
			D3DCOLOR m_ReadingWinColor; ///< Reading window color
			D3DCOLOR m_ReadingSelColor; ///< Selected character in reading string
			D3DCOLOR m_ReadingSelBkColor; ///< Background color for selected char in reading str
			D3DCOLOR m_CandidateColor; ///< Candidate string color
			D3DCOLOR m_CandidateWinColor; ///< Candidate window color
			D3DCOLOR m_CandidateSelColor; ///< Selected candidate string color
			D3DCOLOR m_CandidateSelBkColor; ///< Selected candidate background color
			D3DCOLOR m_CompColor; ///< Composition string color
			D3DCOLOR m_CompWinColor; ///< Composition string window color
			D3DCOLOR m_CompCaretColor; ///< Composition string caret color
			D3DCOLOR m_CompTargetColor; ///< Composition string target converted color
			D3DCOLOR m_CompTargetBkColor; ///< Composition string target converted background
			D3DCOLOR m_CompTargetNonColor; ///< Composition string target non-converted color
			D3DCOLOR m_CompTargetNonBkColor; ///< Composition string target non-converted background
			D3DCOLOR m_IndicatorImeColor; ///< Indicator text color for IME
			D3DCOLOR m_IndicatorEngColor; ///< Indicator text color for English
			D3DCOLOR m_IndicatorBkColor; ///< Indicator text background color

			// Edit-control-specific data
			int m_nIndicatorWidth; ///< Width of the indicator symbol
			RECT m_rcIndicator; ///< Rectangle for drawing the indicator button

			#if defined(DEBUG) || defined(_DEBUG)
				static bool m_bIMEStaticMsgProcCalled;
			#endif 
	};


 


//#endif // #ifdef __D3DX9_H__
#endif // #if ( defined(WIN32) && defined(GB_D3D9) )


// end file