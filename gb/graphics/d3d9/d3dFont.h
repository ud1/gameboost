/** \file
 \brief Очень простой класс чуть подправленый из старого SDK Microsoft для вывода текста. <br>
  Немного переделан. В будущем возможны улучшения.


  \a  ksacvet777

*/


#if ( defined(GB_D3D9) && defined(WIN32) ) 

#pragma once

#include <tchar.h>

#include <D3D9.h>


#define GB_D3D9_API

namespace gb 
{

namespace graphics 
{

namespace d3d9 
{

//-------------------------------------------------------------------------


// Font creation flags
#define GB_D3D9_FONT_D3DFONT_BOLD        0x0001
#define GB_D3D9_FONT_D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define GB_D3D9_FONT_D3DFONT_CENTERED_X  0x0001
#define GB_D3D9_FONT_D3DFONT_CENTERED_Y  0x0002
#define GB_D3D9_FONT_GB_D3D9_FONT_D3DFONT_TWOSIDED    0x0004
#define GB_D3D9_D3DFONT_FILTERED    0x0008




/** \brief  Простой шрифт для вывода текста на экран  без использования d3dx. 
	Не отображает русский шрифт. */
class D3dFont {
public:
 

GB_D3D9_API	 D3dFont(IDirect3DDevice9* pd3dDevice,  const WCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
GB_D3D9_API	~D3dFont();


//! \brief Вывести текст на экран
GB_D3D9_API HRESULT DrawTextA( int x, int y, 
							  DWORD dwColor, 
							  const char* strText, 
							  DWORD dwFlags=0L );

//! \brief Вывести двойную строку (с фоном)
GB_D3D9_API HRESULT DrawTextBackgrA(int x, int y, 
									int backOffset, 
									DWORD dwFrontColor, 
									DWORD dwBackColor, 
									const CHAR* str,
									DWORD dwFlag = 0);

// \brief draw unicode
GB_D3D9_API	HRESULT DrawTextW( int x, int y,
							  DWORD dwColor,
							  const WCHAR* strText, 
							  DWORD dwFlags=0L );

private:

  GB_D3D9_API   HRESULT DrawTextScaled(
			float x, float y, float z, 
			float fXScale, float fYScale,
			DWORD dwColor, 
			const WCHAR* strText,
			DWORD dwFlags=0L );

  GB_D3D9_API HRESULT Render3DText( const TCHAR* strText, DWORD dwFlags=0L );

	// Function to get extent of text
  GB_D3D9_API HRESULT GetTextExtent( const TCHAR* strText, SIZE* pSize );


	//--------------------------------------------------------------

  GB_D3D9_API HRESULT   CreateGDIFont( HDC hDC, HFONT* pFont );
  GB_D3D9_API HRESULT   PaintAlphabet( HDC hDC, BOOL bMeasureOnly=FALSE );

  GB_D3D9_API HRESULT InvalidateDeviceObjects();
  GB_D3D9_API HRESULT DeleteDeviceObjects();

  GB_D3D9_API HRESULT InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice );
  GB_D3D9_API HRESULT RestoreDeviceObjects();


	TCHAR   m_strFontName[80];            ///< Font properties
	DWORD   m_dwFontHeight;
	DWORD   m_dwFontFlags;

	LPDIRECT3DDEVICE9       m_pd3dDevice; ///< A D3DDevice used for rendering
	LPDIRECT3DTEXTURE9      m_pTexture;   ///< The d3d texture for this font
	LPDIRECT3DVERTEXBUFFER9 m_pVB;        ///< VertexBuffer for rendering text
	DWORD   m_dwTexWidth;                 ///< Texture dimensions
	DWORD   m_dwTexHeight;
	float   m_fTextScale;
	float   m_fTexCoords[256][4];//    [128-32][4];
	DWORD   m_dwSpacing;                  ///< Character pixel spacing per side

 
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockSaved;   ///<  State blocks for setting and restoring render states
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText; ///<   State block draw Text
 

};

//-------------------------------------------------------------------------

} // end namespace d3d9
} // end namespace graphics
} // end namespace gb


#endif // #if ( defined(GB_D3D9) && defined(WIN32) ) 
// end file