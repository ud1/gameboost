//#include "stdafx.h" 


#if ( defined(GB_D3D9) && defined(WIN32) )


#define STRICT



#include <stdexcept>

#include <tchar.h>
//#include <D3DX9.h>
#include <gb/graphics/d3d9/d3dFont.h>
 
#include <gb/macro.h>

#include <math.h>
#include <assert.h>


#pragma warning (push)
#pragma warning (disable : 4996)

#include <stdio.h>


namespace gb {
namespace graphics 	{
namespace d3d9 	{

//=========================================================================

//-------------------------------------------------------------------------
// Custom vertex types for rendering text
//-------------------------------------------------------------------------
#define MAX_NUM_VERTICES 50*6

	struct VECTOR3
	{
		float x, y, z;

		VECTOR3() {}
		VECTOR3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}

	};

 struct VECTOR4
 {
	 float x, y, z, w;

	 VECTOR4() {}
	 VECTOR4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {}

 };


	struct FONT2DVERTEX { VECTOR4 p;   DWORD color;     float tu, tv; };
	struct FONT3DVERTEX { VECTOR3 p;   VECTOR3 n;   float tu, tv; };

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FONT3DVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

inline FONT2DVERTEX InitFont2DVertex( const VECTOR4& p, D3DCOLOR color,
                                      float tu, float tv )
{
	FONT2DVERTEX v;   
	v.p = p;   
	v.color = color;   
	v.tu = tu;   
	v.tv = tv;
	return v;
}

inline FONT3DVERTEX InitFont3DVertex( const VECTOR3& p, const VECTOR3& n,
                                      float tu, float tv )
{
    FONT3DVERTEX v;  
	v.p = p;  
	v.n = n;  
	v.tu = tu;  
	v.tv = tv;
    return v;
}




//-----------------------------------------------------------------------------
// Name: D3dFont()
// Desc: Font class constructor
//-----------------------------------------------------------------------------
  GB_D3D9_API  D3dFont::D3dFont(IDirect3DDevice9* pd3dDevice,  const WCHAR* strFontName, DWORD dwHeight, DWORD dwFlags )
{
    _tcsncpy( m_strFontName, strFontName, sizeof(m_strFontName) / sizeof(WCHAR) );
    m_strFontName[ sizeof(m_strFontName) / sizeof(WCHAR) - 1] = _T('\0' );
    m_dwFontHeight         = dwHeight;
    m_dwFontFlags          = dwFlags;
    m_dwSpacing            = 0;

    m_pd3dDevice           = NULL;
    m_pTexture             = NULL;
    m_pVB                  = NULL;

    m_pStateBlockSaved     = NULL;
    m_pStateBlockDrawText  = NULL;

  // new code
	HRESULT hr = S_OK;
	hr |=  InitDeviceObjects(pd3dDevice);

	hr |=  RestoreDeviceObjects();

	if FAILED(hr)
	{
		throw (std::runtime_error("Failed operation") );
	}


}




//-----------------------------------------------------------------------------
// Name: ~D3dFont()
// Desc: Font class destructor
//-----------------------------------------------------------------------------
  GB_D3D9_API  D3dFont::~D3dFont()
{
    InvalidateDeviceObjects();
    DeleteDeviceObjects();
}




//-----------------------------------------------------------------------------
// Name: CreateGDIFont
// Desc: Create a font based on the current state of related member variables
//       and return the handle (or null on error)
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::CreateGDIFont( HDC hDC, HFONT* pFont )
{
    // Create a font.  By specifying ANTIALIASED_QUALITY, we might get an
    // antialiased font, but this is not guaranteed.
    INT nHeight    = -MulDiv( m_dwFontHeight, 
                              (INT)(GetDeviceCaps(hDC, LOGPIXELSY) * m_fTextScale), 
                              72 );
    DWORD dwBold   = (m_dwFontFlags & GB_D3D9_FONT_D3DFONT_BOLD)   ? FW_BOLD : FW_NORMAL;
    DWORD dwItalic = (m_dwFontFlags & GB_D3D9_FONT_D3DFONT_ITALIC) ? TRUE    : FALSE;
    *pFont         = CreateFontW // A
		( nHeight, 0, 0, 0, dwBold, dwItalic,
                                 FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                 CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                 VARIABLE_PITCH, m_strFontName );

    if( *pFont == NULL )
        return E_FAIL;

    return S_OK;
}




//-------------------------------------------------------------------------
// Name: PaintAlphabet
// Desc: Paint the printable characters for the given GDI font onto the
//       provided device context. If the bMeasureOnly flag is set, no drawing 
//       will occur.
//-------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::PaintAlphabet( HDC hDC, BOOL bMeasureOnly )
{
    SIZE size;
    TCHAR str[2] = _T("x"); // One-character, null-terminated string
    
    // Calculate the spacing between characters based on line height
    if( 0 == GetTextExtentPoint32( hDC, str, 1, &size ) )
        return E_FAIL;
    m_dwSpacing = (DWORD) ceil(size.cy * 0.3f);

    // Set the starting point for the drawing
    DWORD x = m_dwSpacing;
    DWORD y = 0;
    
    // For each character, draw text on the DC and advance the current position
    for( char c = 32; c < 127; c++ )
    {
        str[0] = c;
        if( 0 == GetTextExtentPoint32( hDC, str, 1, &size ) )
            return E_FAIL;

        if( (DWORD)(x + size.cx + m_dwSpacing) > m_dwTexWidth )
        {
            x  = m_dwSpacing;
            y += size.cy + 1;
        }

        // Check to see if there's room to write the character here
        if( y + size.cy > m_dwTexHeight )
            return D3DERR_MOREDATA;
           
        if( !bMeasureOnly )
        {
            // Perform the actual drawing
            if( 0 == ExtTextOut( hDC, x+0, y+0, ETO_OPAQUE, NULL, str, 1, NULL ) )
			{
                return E_FAIL;
			}

            m_fTexCoords[c-32][0] = ((float)(x + 0       - m_dwSpacing))/m_dwTexWidth;
            m_fTexCoords[c-32][1] = ((float)(y + 0       + 0          ))/m_dwTexHeight;
            m_fTexCoords[c-32][2] = ((float)(x + size.cx + m_dwSpacing))/m_dwTexWidth;
            m_fTexCoords[c-32][3] = ((float)(y + size.cy + 0          ))/m_dwTexHeight;
        }

        x += size.cx + (2 * m_dwSpacing);
    }

    return S_OK;
}





//-------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initializes device-dependent objects, including the vertex buffer used
//       for rendering text and the texture map which stores the font image.
//-------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice )
{
    HRESULT hr = S_OK;
    HFONT hFont = NULL;
    HFONT hFontOld = NULL;
    HDC hDC = NULL;
    HBITMAP hbmBitmap = NULL;
    HGDIOBJ hbmOld = NULL;

    // Keep a local copy of the device
    m_pd3dDevice = pd3dDevice;

    // Assume we will draw fonts into texture without scaling unless the
    // required texture size is found to be larger than the device max
    m_fTextScale  = 1.0f; 

    hDC = CreateCompatibleDC( NULL );
    SetMapMode( hDC, MM_TEXT );

    hr = CreateGDIFont( hDC, &hFont );
    if( FAILED(hr) )
        goto LCleanReturn;

    hFontOld = (HFONT) SelectObject( hDC, hFont );

    // Calculate the dimensions for the smallest power-of-two texture which
    // can hold all the printable characters
    m_dwTexWidth = m_dwTexHeight = 128;
    while( D3DERR_MOREDATA == ( hr = PaintAlphabet( hDC, true ) ) )
    {
        m_dwTexWidth *= 2;
        m_dwTexHeight *= 2;
    }

    if( FAILED(hr) )
        goto LCleanReturn;
    
    // If requested texture is too big, use a smaller texture and smaller font,
    // and scale up when rendering.
    D3DCAPS9 d3dCaps;
    m_pd3dDevice->GetDeviceCaps( &d3dCaps );

    if( m_dwTexWidth > d3dCaps.MaxTextureWidth )
    {
        m_fTextScale = (float)d3dCaps.MaxTextureWidth / (float)m_dwTexWidth;
        m_dwTexWidth = m_dwTexHeight = d3dCaps.MaxTextureWidth;
   
        bool bFirstRun = true; // Flag clear after first run

        do
        {
            // If we've already tried fitting the new text, the scale is still 
            // too large. Reduce and try again.
            if( !bFirstRun)
                m_fTextScale *= 0.9f;

            // The font has to be scaled to fit on the maximum texture size; our
            // current font is too big and needs to be recreated to scale.
            DeleteObject( SelectObject( hDC, hFontOld ) );

            hr = CreateGDIFont( hDC, &hFont );
            if( FAILED(hr) )
                goto LCleanReturn;

            hFontOld = (HFONT) SelectObject( hDC, hFont );

            bFirstRun = false;
        } 
        while( D3DERR_MOREDATA == ( hr = PaintAlphabet( hDC, true ) ) );
    }

    
    // Create a new texture for the font
    hr = m_pd3dDevice->CreateTexture( m_dwTexWidth, m_dwTexHeight, 1,
                                      0, D3DFMT_A4R4G4B4,
                                      D3DPOOL_MANAGED, &m_pTexture, NULL );
    if( FAILED(hr) )
        goto LCleanReturn;

    // Prepare to create a bitmap
    DWORD*      pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory( &bmi.bmiHeader, sizeof(BITMAPINFOHEADER) );
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       =  (int)m_dwTexWidth;
    bmi.bmiHeader.biHeight      = -(int)m_dwTexHeight;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // Create a bitmap for the font
    hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS,
                                  (void**)&pBitmapBits, NULL, 0 );

    hbmOld = SelectObject( hDC, hbmBitmap );
    
    // Set text properties
    SetTextColor( hDC, RGB(255,255,255) );
    SetBkColor(   hDC, 0x00000000 );
    SetTextAlign( hDC, TA_TOP );

    // Paint the alphabet onto the selected bitmap
    hr = PaintAlphabet( hDC, false );
    if( FAILED(hr) )
        goto LCleanReturn;

    // Lock the surface and write the alpha values for the set pixels
    D3DLOCKED_RECT d3dlr;
    m_pTexture->LockRect( 0, &d3dlr, 0, 0 );
    BYTE* pDstRow;
    pDstRow = (BYTE*)d3dlr.pBits;
    WORD* pDst16;
    BYTE bAlpha; // 4-bit measure of pixel intensity
    DWORD x, y;

    for( y=0; y < m_dwTexHeight; y++ )
    {
        pDst16 = (WORD*)pDstRow;
        for( x=0; x < m_dwTexWidth; x++ )
        {
            bAlpha = (BYTE)((pBitmapBits[m_dwTexWidth*y + x] & 0xff) >> 4);
            if (bAlpha > 0)
            {
                *pDst16++ = (WORD) ((bAlpha << 12) | 0x0fff);
            }
            else
            {
                *pDst16++ = 0x0000;
            }
        }
        pDstRow += d3dlr.Pitch;
    }

    hr = S_OK;

    // Done updating texture, so clean up used objects
LCleanReturn:
    if( m_pTexture )
        m_pTexture->UnlockRect(0);

    SelectObject( hDC, hbmOld );
    SelectObject( hDC, hFontOld );
    DeleteObject( hbmBitmap );
    DeleteObject( hFont );
    DeleteDC( hDC );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::RestoreDeviceObjects()
{
    HRESULT hr;

    // Create vertex buffer for the letters
    int vertexSize = max( sizeof(FONT2DVERTEX), sizeof(FONT3DVERTEX ) );
    if( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( MAX_NUM_VERTICES * vertexSize,
                                                       D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0,
                                                       D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
    {
        return hr;
    }

    bool bSupportsAlphaBlend = true;
    LPDIRECT3D9 pd3d9 = NULL;
    if( SUCCEEDED( m_pd3dDevice->GetDirect3D( &pd3d9 ) ) )
    {
        D3DCAPS9 Caps;
        D3DDISPLAYMODE Mode;
        LPDIRECT3DSURFACE9 pSurf = NULL;
        D3DSURFACE_DESC Desc;
        m_pd3dDevice->GetDeviceCaps( &Caps );
        m_pd3dDevice->GetDisplayMode( 0, &Mode );
        if( SUCCEEDED( m_pd3dDevice->GetRenderTarget( 0, &pSurf ) ) )
        {
            pSurf->GetDesc( &Desc );
            if( FAILED( pd3d9->CheckDeviceFormat( Caps.AdapterOrdinal, Caps.DeviceType, Mode.Format,
                D3DUSAGE_RENDERTARGET | D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, D3DRTYPE_SURFACE, 
                Desc.Format ) ) )
            {
                bSupportsAlphaBlend = false;
            }
            GB_SAFE_REL( pSurf );
        }
        GB_SAFE_REL( pd3d9 );
    }

    // Create the state blocks for rendering text
    for( UINT which=0; which<2; which++ )
    {
        m_pd3dDevice->BeginStateBlock();
        m_pd3dDevice->SetTexture( 0, m_pTexture );

        if ( D3DFONT_ZENABLE & m_dwFontFlags )
            m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
        else
            m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

        if( bSupportsAlphaBlend )
        {
            m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
            m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA );
            m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );
        }
        else
        {
            m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
        }
        m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,         0x08 );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC,  D3DCMP_GREATEREQUAL );
        m_pd3dDevice->SetRenderState( D3DRS_FILLMODE,   D3DFILL_SOLID );
        m_pd3dDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CCW );
        m_pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_CLIPPING,         TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,  FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND,      D3DVBF_DISABLE );
        m_pd3dDevice->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_COLORWRITEENABLE,
            D3DCOLORWRITEENABLE_RED  | D3DCOLORWRITEENABLE_GREEN |
            D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
        m_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
        m_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
        m_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

        if( which==0 )
            m_pd3dDevice->EndStateBlock( &m_pStateBlockSaved );
        else
            m_pd3dDevice->EndStateBlock( &m_pStateBlockDrawText );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Destroys all device-dependent objects
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::InvalidateDeviceObjects()
{
    GB_SAFE_REL( m_pVB );
    GB_SAFE_REL( m_pStateBlockSaved );
    GB_SAFE_REL( m_pStateBlockDrawText );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Destroys all device-dependent objects
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::DeleteDeviceObjects()
{
    GB_SAFE_REL( m_pTexture );
    m_pd3dDevice = NULL;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: GetTextExtent()
// Desc: Get the dimensions of a text string
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::GetTextExtent( const TCHAR* strText, SIZE* pSize )
{
    if( NULL==strText || NULL==pSize )
        return E_FAIL;

    float fRowWidth  = 0.0f;
    float fRowHeight = (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight;
    float fWidth     = 0.0f;
    float fHeight    = fRowHeight;

    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            fRowWidth = 0.0f;
            fHeight  += fRowHeight;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        float tx1 = m_fTexCoords[c-32][0];
        float tx2 = m_fTexCoords[c-32][2];

        fRowWidth += (tx2-tx1)*m_dwTexWidth - 2*m_dwSpacing;

        if( fRowWidth > fWidth )
            fWidth = fRowWidth;
    }

    pSize->cx = (int)fWidth;
    pSize->cy = (int)fHeight;

    return S_OK;
}

//
//-------------------------------------------------------------------------
  GB_D3D9_API  GB_D3D9_API	HRESULT D3dFont::DrawTextBackgrA(int x, int y, int backOffset,
								 DWORD dwFrontColor, DWORD dwBackColor, 
								 const CHAR* str, DWORD dwFlag  )
{
	HRESULT hr = 0;
 
 hr |= DrawTextA(x+backOffset, y+backOffset, dwBackColor, str,  0   );
 hr |= DrawTextA(x, y, dwFrontColor, str,  0 );

	return hr;
};



//-----------------------------------------------------------------------------
// Name: DrawTextScaled()
// Desc: Draws scaled 2D text.  Note that x and y are in viewport coordinates
//       (ranging from -1 to +1).  fXScale and fYScale are the size fraction 
//       relative to the entire viewport.  For example, a fXScale of 0.25 is
//       1/8th of the screen width.  This allows you to output text at a fixed
//       fraction of the viewport, even if the screen or window size changes.
//-----------------------------------------------------------------------------
  GB_D3D9_API  HRESULT D3dFont::DrawTextScaled( float x, float y, float z,
                                  float fXScale, float fYScale, DWORD dwColor,
                                  const WCHAR* strText, DWORD dwFlags )
{
    if( m_pd3dDevice == NULL )
        return E_FAIL;

    // Set up renderstate
    m_pStateBlockSaved->Capture();
    m_pStateBlockDrawText->Apply();
    m_pd3dDevice->SetFVF( D3DFVF_FONT2DVERTEX );
    m_pd3dDevice->SetPixelShader( NULL );
    m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT2DVERTEX) );

    // Set filter states
    if( dwFlags & GB_D3D9_D3DFONT_FILTERED )
    {
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    D3DVIEWPORT9 vp;
    m_pd3dDevice->GetViewport( &vp );
    float fLineHeight = ( m_fTexCoords[0][3] - m_fTexCoords[0][1] ) * m_dwTexHeight;

    // Center the text block in the viewport
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_X )
    {
        const TCHAR* strTextTmp = strText;
        float xFinal = 0.0f;

        while( *strTextTmp )
        {
            TCHAR c = *strTextTmp++;
    
            if( c == _T('\n') )
                break;  // Isn't supported.  
            if( (c-32) < 0 || (c-32) >= 128-32 )
                continue;

            float tx1 = m_fTexCoords[c-32][0];
            float tx2 = m_fTexCoords[c-32][2];

            float w = (tx2-tx1)*m_dwTexWidth;

            w *= (fXScale*vp.Height)/fLineHeight;

            xFinal += w - (2 * m_dwSpacing) * (fXScale*vp.Height)/fLineHeight;
        }

        x = -xFinal/vp.Width;
    }
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_Y )
    {
        y = -fLineHeight/vp.Height;
    }

    float sx  = (x+1.0f)*vp.Width/2;
    float sy  = (y+1.0f)*vp.Height/2;
    float sz  = z;
    float rhw = 1.0f;

    // Adjust for character spacing
    sx -= m_dwSpacing * (fXScale*vp.Height)/fLineHeight;
    float fStartX = sx;

    // Fill vertex buffer
    FONT2DVERTEX* pVertices;
    DWORD         dwNumTriangles = 0L;
    m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            sx  = fStartX;
            sy += fYScale*vp.Height;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        float tx1 = m_fTexCoords[c-32][0];
        float ty1 = m_fTexCoords[c-32][1];
        float tx2 = m_fTexCoords[c-32][2];
        float ty2 = m_fTexCoords[c-32][3];

        float w = (tx2-tx1)*m_dwTexWidth;
        float h = (ty2-ty1)*m_dwTexHeight;

        w *= (fXScale*vp.Height)/fLineHeight;
        h *= (fYScale*vp.Height)/fLineHeight;

        if( c != _T(' ') )
        {
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+0-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx1, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+0-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx1, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+w-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+w-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx2, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+w-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(sx+0-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx1, ty1 );
            dwNumTriangles += 2;

            if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
            {
                // Unlock, render, and relock the vertex buffer
                m_pVB->Unlock();
                m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
                m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
                dwNumTriangles = 0L;
            }
        }

        sx += w - (2 * m_dwSpacing) * (fXScale*vp.Height)/fLineHeight;
    }

    // Unlock and render the vertex buffer
    m_pVB->Unlock();
    if( dwNumTriangles > 0 )
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );

    // Restore the modified renderstates
    m_pStateBlockSaved->Apply();

    return S_OK;
}



//-------------------------------------------------------------------------
//
GB_D3D9_API	HRESULT D3dFont::DrawTextA( int n_sx, int n_sy,  DWORD dwColor, const char* strText,  DWORD dwFlags )
{
 
		HRESULT hr = S_OK;

	  float fsx = (float)n_sx;
	  float fsy = (float)n_sy;

    if( m_pd3dDevice == NULL )
	{
        return E_FAIL;
	}

	if(!m_pStateBlockSaved)
	{
		return E_FAIL;
	}


    // Setup renderstate

    try
    {
	  hr  |=  m_pStateBlockSaved->Capture();
    }
    catch ( ... )
    {
		// except
		throw (std::runtime_error("failed operation") );
   	
    }

	if FAILED(hr)
	{
		return  hr;
	}
 

  hr |=  m_pStateBlockDrawText->Apply();
  hr |=   m_pd3dDevice->SetFVF( D3DFVF_FONT2DVERTEX );
  hr |=   m_pd3dDevice->SetPixelShader( NULL );
  hr |=   m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT2DVERTEX) );

  if FAILED(hr)
  {
	  return  hr;
  }

    // Set filter states
    if( dwFlags & GB_D3D9_D3DFONT_FILTERED )
    {
     hr |=   m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
     hr |=   m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    // Center the text block in the viewport
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_X )
    {
        D3DVIEWPORT9 vp;
        m_pd3dDevice->GetViewport( &vp );
        const  char* strTextTmp = strText;
        float xFinal = 0.0f;

        while( *strTextTmp )
        {
            unsigned  char chr = *strTextTmp++;


    
            if( chr == '\n'  ) //  _T('\n') )
			{
                break;  // Isn't supported.  
			}

		   bool bFoundRussion = false;
		 // russian
		 if( (chr>=128) && (chr<=255) )
		 {
			 bFoundRussion = true; // break
			// printf(strText);

		 }

		 /*	  TEMPORARY CODE !
            if( (chr-32) < 0 || (chr-32) >= 128-32 )
			{
                continue;
			}
			*/

            float tx1 = m_fTexCoords[chr-32][0];
            float tx2 = m_fTexCoords[chr-32][2];
    
            float w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
    
            xFinal += w - (2 * m_dwSpacing);
        }

        fsx = ( (float)vp.Width- (float)xFinal)/2.0f;
    }

	if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_Y )
	{
		D3DVIEWPORT9 vp;
		hr |=     m_pd3dDevice->GetViewport( &vp );
		float fLineHeight = ((m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight);
		fsy = (vp.Height-fLineHeight)/2;
	}

    // Adjust for character spacing
    fsx -= m_dwSpacing;
    float fStartX =  fsx;

    // Fill vertex buffer
    FONT2DVERTEX* pVertices = NULL;
    DWORD         dwNumTriangles = 0;
    hr |= m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( *strText )
    {
         unsigned char _chr_ = *strText++;


		 bool bFoundRussion = false;
		 // russian
		 if( (_chr_>=128) && (_chr_<=255) )
		 {
			 bFoundRussion = true; // break
			 //printf(strText);

		 }

        if( _chr_ ==  '\n') 
        {
            fsx = fStartX;
            fsy += (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight;
        }

		if(bFoundRussion)
		{
			int _stop = 0; // break !
		}

	 
        if( (_chr_-32) < 0 &&  (_chr_-32) >= 128-32 )
		{
            continue;
		}
		 

        float tx1 = m_fTexCoords[_chr_-32][0];
        float ty1 = m_fTexCoords[_chr_-32][1];
        float tx2 = m_fTexCoords[_chr_-32][2];
        float ty2 = m_fTexCoords[_chr_-32][3];

        float w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
        float h = (ty2-ty1) * m_dwTexHeight / m_fTextScale;

        if( _chr_ != ' ' )
        {
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx1, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx1, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx2, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx1, ty1 );
            dwNumTriangles += 2;

			if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
			{
				// Unlock, render, and relock the vertex buffer
				hr |=   m_pVB->Unlock();
				hr |=    m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
				pVertices = NULL;
				hr |=   m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
				dwNumTriangles = 0L;
			}
		}

        fsx += w - (2.0f * m_dwSpacing);
    }

	// Unlock and render the vertex buffer
	m_pVB->Unlock();
	if( dwNumTriangles > 0 )
	{
		hr |=  m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
	}

    // Restore the modified renderstates
     hr |=    m_pStateBlockSaved->Apply();

	 if FAILED(hr)
	 {
		 return  hr;
	 }



    return  hr;

};



//-----------------------------------------------------------------------------
// Name: DrawText()
// Desc: Draws 2D text. Note that sx and sy are in pixels
//-----------------------------------------------------------------------------
GB_D3D9_API	GB_D3D9_API	HRESULT D3dFont::DrawTextW( int n_sx, int n_sy, DWORD dwColor,
                            const WCHAR* strText, DWORD dwFlags )
{
	HRESULT hr = S_OK;

	  float fsx = (float)n_sx;
	  float fsy = (float)n_sy;

    if( m_pd3dDevice == NULL )
	{
        return E_FAIL;
	}

	if(!m_pStateBlockSaved)
	{
		return E_FAIL;
	}


    // Setup renderstate

    try
    {
	  hr  |=  m_pStateBlockSaved->Capture();
    }
    catch ( ... )
    {
		// except
		throw (std::runtime_error("failed operation") );
   	
    }

	if FAILED(hr)
	{
		return  hr;
	}
 

  hr |=  m_pStateBlockDrawText->Apply();
  hr |=   m_pd3dDevice->SetFVF( D3DFVF_FONT2DVERTEX );
  hr |=   m_pd3dDevice->SetPixelShader( NULL );
  hr |=   m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT2DVERTEX) );

  if FAILED(hr)
  {
	  return  hr;
  }

    // Set filter states
    if( dwFlags & GB_D3D9_D3DFONT_FILTERED )
    {
     hr |=   m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
     hr |=   m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    // Center the text block in the viewport
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_X )
    {
        D3DVIEWPORT9 vp;
        m_pd3dDevice->GetViewport( &vp );
        const TCHAR* strTextTmp = strText;
        float xFinal = 0.0f;

        while( *strTextTmp )
        {
            WCHAR chr = *strTextTmp++;
    
            if( chr == _T('\n') )
                break;  // Isn't supported.  
            if( (chr-32) < 0 || (chr-32) >= 128-32 )
                continue;

            float tx1 = m_fTexCoords[chr-32][0];
            float tx2 = m_fTexCoords[chr-32][2];
    
            float w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
    
            xFinal += w - (2 * m_dwSpacing);
        }

        fsx = ( (float)vp.Width- (float)xFinal)/2.0f;
    }

	if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_Y )
	{
		D3DVIEWPORT9 vp;
		hr |=     m_pd3dDevice->GetViewport( &vp );
		float fLineHeight = ( (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight );
		fsy = (vp.Height-fLineHeight)/2;
	}

    // Adjust for character spacing
    fsx -= m_dwSpacing;
    float fStartX =  fsx;

    // Fill vertex buffer
    FONT2DVERTEX* pVertices = NULL;
    DWORD         dwNumTriangles = 0;
    hr |= m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            fsx = fStartX;
            fsy += (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
		{
            continue;
		}

        float tx1 = m_fTexCoords[c-32][0];
        float ty1 = m_fTexCoords[c-32][1];
        float tx2 = m_fTexCoords[c-32][2];
        float ty2 = m_fTexCoords[c-32][3];

        float w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
        float h = (ty2-ty1) * m_dwTexHeight / m_fTextScale;

        if( c != _T(' ') )
        {
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx1, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx1, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx2, ty1 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+w-0.5f,fsy+h-0.5f,0.9f,1.0f), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( VECTOR4(fsx+0-0.5f,fsy+0-0.5f,0.9f,1.0f), dwColor, tx1, ty1 );
            dwNumTriangles += 2;

			if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
			{
				// Unlock, render, and relock the vertex buffer
				hr |=   m_pVB->Unlock();
				hr |=    m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
				pVertices = NULL;
				hr |=   m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
				dwNumTriangles = 0L;
			}
		}

        fsx += w - (2.0f * m_dwSpacing);
    }

	// Unlock and render the vertex buffer
	m_pVB->Unlock();
	if( dwNumTriangles > 0 )
	{
		hr |=  m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
	}

    // Restore the modified renderstates
     hr |=    m_pStateBlockSaved->Apply();

	 if FAILED(hr)
	 {
		 return  hr;
	 }



    return  hr;
}




//-----------------------------------------------------------------------------
// Name: Render3DText()
// Desc: Renders 3D text
//-----------------------------------------------------------------------------
GB_D3D9_API	HRESULT D3dFont::Render3DText( const TCHAR* strText, DWORD dwFlags )
{
    if( m_pd3dDevice == NULL )
        return E_FAIL;

    // Setup renderstate
    m_pStateBlockSaved->Capture();
    m_pStateBlockDrawText->Apply();
    m_pd3dDevice->SetFVF( D3DFVF_FONT3DVERTEX );
    m_pd3dDevice->SetPixelShader( NULL );
    m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT3DVERTEX) );

    // Set filter states
    if( dwFlags & GB_D3D9_D3DFONT_FILTERED )
    {
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    // Position for each text element
    float x = 0.0f;
    float y = 0.0f;

    // Center the text block at the origin (not the viewport)
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_X )
    {
        SIZE sz;
        GetTextExtent( strText, &sz );
        x = -(((float)sz.cx)/10.0f)/2.0f;
    }
    if( dwFlags & GB_D3D9_FONT_D3DFONT_CENTERED_Y )
    {
        SIZE sz;
        GetTextExtent( strText, &sz );
        y = -(((float)sz.cy)/10.0f)/2.0f;
    }

    // Turn off culling for two-sided text
    if( dwFlags & GB_D3D9_FONT_GB_D3D9_FONT_D3DFONT_TWOSIDED )
        m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Adjust for character spacing
    x -= m_dwSpacing / 10.0f;
    float fStartX = x;
    TCHAR c;

    // Fill vertex buffer
    FONT3DVERTEX* pVertices;
    DWORD         dwNumTriangles = 0L;
    m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( (c = *strText++) != 0 )
    {
        if( c == '\n' )
        {
            x = fStartX;
            y -= (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight/10.0f;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        float tx1 = m_fTexCoords[c-32][0];
        float ty1 = m_fTexCoords[c-32][1];
        float tx2 = m_fTexCoords[c-32][2];
        float ty2 = m_fTexCoords[c-32][3];

        float w = (tx2-tx1) * m_dwTexWidth  / ( 10.0f * m_fTextScale );
        float h = (ty2-ty1) * m_dwTexHeight / ( 10.0f * m_fTextScale );

        if( c != _T(' ') )
        {
            *pVertices++ = InitFont3DVertex( VECTOR3(x+0,y+0,0), VECTOR3(0,0,-1), tx1, ty2 );
            *pVertices++ = InitFont3DVertex( VECTOR3(x+0,y+h,0), VECTOR3(0,0,-1), tx1, ty1 );
            *pVertices++ = InitFont3DVertex( VECTOR3(x+w,y+0,0), VECTOR3(0,0,-1), tx2, ty2 );
            *pVertices++ = InitFont3DVertex( VECTOR3(x+w,y+h,0), VECTOR3(0,0,-1), tx2, ty1 );
            *pVertices++ = InitFont3DVertex( VECTOR3(x+w,y+0,0), VECTOR3(0,0,-1), tx2, ty2 );
            *pVertices++ = InitFont3DVertex( VECTOR3(x+0,y+h,0), VECTOR3(0,0,-1), tx1, ty1 );
            dwNumTriangles += 2;

            if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
            {
                // Unlock, render, and relock the vertex buffer
                m_pVB->Unlock();
                m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
                m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
                dwNumTriangles = 0L;
            }
        }

        x += w - (2 * m_dwSpacing) / 10.0f;
    }

    // Unlock and render the vertex buffer
    m_pVB->Unlock();
    if( dwNumTriangles > 0 )
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );

    // Restore the modified renderstates
    m_pStateBlockSaved->Apply();

    return S_OK;
}

//=========================================================================

} // end namespace d3d9
} // end namespace graphics
} // end namespace gb



#pragma warning (pop)

#endif

// end file