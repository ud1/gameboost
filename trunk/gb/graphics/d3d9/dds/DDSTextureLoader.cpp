/**  \file
  \brief реализатор загрузчика dds
 
 Functions for loading a DDS texture without using D3DX
 Copyright (c) Microsoft Corporation. All rights reserved.
  \todo убрать макросы  поменять на gb macro
 
*/

#include "stdafx.h"
 
#include <DDraw.h>
#include <gb/graphics/d3d9/dds/DDSTextureLoader.h>
#include <gb/graphics/d3d9/dds/ddsurfacedesc2_32bit.h>

#include <stdlib.h>

#include <assert.h>



#ifndef SAFE_DELETE
  #define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif  
  
#ifndef SAFE_DELETE_ARRAY
  #define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif  
  
#ifndef SAFE_RELEASE
  #define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif


#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))


//--------------------------------------------------------------------------------------
BOOL LoadTextureDataFromFileA( CHAR* szFileName, BYTE** ppHeapData, DDSURFACEDESC2_32BIT** ppSurfDesc, BYTE** ppBitData, UINT* pBitSize )
{
	*ppHeapData = NULL;
	*ppSurfDesc = NULL;
	*ppBitData  = NULL;
	*pBitSize   = 0;

	// open the file
	HANDLE hFile = CreateFileA( szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL );
	if( INVALID_HANDLE_VALUE == hFile )
		return FALSE;

	// Get the file size
	LARGE_INTEGER FileSize;
	GetFileSizeEx( hFile, &FileSize );

	// create enough space for the file data
	*ppHeapData = new BYTE[ FileSize.LowPart ];
	if( !(*ppHeapData) )
		return FALSE;

	// read the data in
	DWORD BytesRead;
	if( !ReadFile( hFile, *ppHeapData, FileSize.LowPart, &BytesRead, NULL ) )
		return FALSE;

	// DDS files always start with the same magic number
	DWORD dwMagicNumber = *(DWORD*)(*ppHeapData);
	if( dwMagicNumber != 0x20534444 )
		return FALSE;

	// setup the pointers in the process request
	*ppSurfDesc = (DDSURFACEDESC2_32BIT*)( *ppHeapData + sizeof(DWORD) );
	*ppBitData  = *ppHeapData + sizeof(DWORD) + sizeof(DDSURFACEDESC2_32BIT);
	*pBitSize   = FileSize.LowPart - sizeof(DWORD) - sizeof(DDSURFACEDESC2_32BIT);

	CloseHandle( hFile );

	return TRUE;
}


//--------------------------------------------------------------------------------------
BOOL LoadTextureDataFromFileW( WCHAR* szFileName, BYTE** ppHeapData, DDSURFACEDESC2_32BIT** ppSurfDesc, BYTE** ppBitData, UINT* pBitSize )
{
    *ppHeapData = NULL;
    *ppSurfDesc = NULL;
    *ppBitData  = NULL;
    *pBitSize   = 0;

    // open the file
    HANDLE hFile = CreateFileW( szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL );
    if( INVALID_HANDLE_VALUE == hFile )
        return FALSE;

    // Get the file size
    LARGE_INTEGER FileSize;
    GetFileSizeEx( hFile, &FileSize );

    // create enough space for the file data
    *ppHeapData = new BYTE[ FileSize.LowPart ];
    if( !(*ppHeapData) )
        return FALSE;

    // read the data in
    DWORD BytesRead;
    if( !ReadFile( hFile, *ppHeapData, FileSize.LowPart, &BytesRead, NULL ) )
        return FALSE;

    // DDS files always start with the same magic number
    DWORD dwMagicNumber = *(DWORD*)(*ppHeapData);
    if( dwMagicNumber != 0x20534444 )
        return FALSE;

    // setup the pointers in the process request
    *ppSurfDesc = (DDSURFACEDESC2_32BIT*)( *ppHeapData + sizeof(DWORD) );
    *ppBitData  = *ppHeapData + sizeof(DWORD) + sizeof(DDSURFACEDESC2_32BIT);
    *pBitSize   = FileSize.LowPart - sizeof(DWORD) - sizeof(DDSURFACEDESC2_32BIT);

    CloseHandle( hFile );

    return TRUE;
}

//--------------------------------------------------------------------------------------
// Return the BPP for a particular format
//--------------------------------------------------------------------------------------
UINT BitsPerPixel( D3DFORMAT fmt )
{
    UINT fmtU = (UINT)fmt;
    switch( fmtU )
    {
    case D3DFMT_A32B32G32R32F:
        return 128;

    case D3DFMT_A16B16G16R16:
    case D3DFMT_Q16W16V16U16:
    case D3DFMT_A16B16G16R16F:
    case D3DFMT_G32R32F:
        return 64;

    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
    case D3DFMT_A2B10G10R10:
    case D3DFMT_A8B8G8R8:
    case D3DFMT_X8B8G8R8:
    case D3DFMT_G16R16:
    case D3DFMT_A2R10G10B10:
    case D3DFMT_Q8W8V8U8:
    case D3DFMT_V16U16:
    case D3DFMT_X8L8V8U8:
    case D3DFMT_A2W10V10U10:
    case D3DFMT_D32:
    case D3DFMT_D24S8:
    case D3DFMT_D24X8:
    case D3DFMT_D24X4S4:
    case D3DFMT_D32F_LOCKABLE:
    case D3DFMT_D24FS8:
    case D3DFMT_INDEX32:
    case D3DFMT_G16R16F:
    case D3DFMT_R32F:
        return 32;

    case D3DFMT_R8G8B8:
        return 24;

    case D3DFMT_A4R4G4B4:
    case D3DFMT_X4R4G4B4:
    case D3DFMT_R5G6B5:
    case D3DFMT_L16:
    case D3DFMT_A8L8:
    case D3DFMT_X1R5G5B5:
    case D3DFMT_A1R5G5B5:
    case D3DFMT_A8R3G3B2:
    case D3DFMT_V8U8:
    case D3DFMT_CxV8U8:
    case D3DFMT_L6V5U5:
    case D3DFMT_G8R8_G8B8:
    case D3DFMT_R8G8_B8G8:
    case D3DFMT_D16_LOCKABLE:
    case D3DFMT_D15S1:
    case D3DFMT_D16:
    case D3DFMT_INDEX16:
    case D3DFMT_R16F:
    case D3DFMT_YUY2:
        return 16;

    case D3DFMT_R3G3B2:
    case D3DFMT_A8:
    case D3DFMT_A8P8:
    case D3DFMT_P8:
    case D3DFMT_L8:
    case D3DFMT_A4L4:
        return 8;

    case D3DFMT_DXT1:
        return 4;
    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
        return  8;

    // From DX docs, reference/d3d/enums/d3dformat.asp
    // (note how it says that D3DFMT_R8G8_B8G8 is "A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, and so on)")
    case D3DFMT_UYVY:
        return 16;

    // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/directshow/htm/directxvideoaccelerationdxvavideosubtypes.asp
    case MAKEFOURCC( 'A', 'I', '4', '4' ):
    case MAKEFOURCC( 'I', 'A', '4', '4' ):
        return 8;

    case MAKEFOURCC( 'Y', 'V', '1', '2' ):
        return 12;

    default:
        assert(FALSE); // unhandled format
        return 0;
    }
}

//--------------------------------------------------------------------------------------
DXGI_FORMAT ConvertToDXGI_FORMAT( D3DFORMAT d3dformat )
{
    switch( d3dformat )
    {
    case D3DFMT_A32B32G32R32F:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    case D3DFMT_A16B16G16R16:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    case D3DFMT_A16B16G16R16F:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case D3DFMT_G32R32F:
        return DXGI_FORMAT_R32G32_FLOAT;

    case D3DFMT_R8G8B8:
    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
        return DXGI_FORMAT_R8G8B8A8_UNORM;

    case D3DFMT_G16R16:
    case D3DFMT_V16U16:
        return DXGI_FORMAT_R16G16_UNORM;

    case D3DFMT_G16R16F:
        return DXGI_FORMAT_R16G16_FLOAT;
    case D3DFMT_R32F:
        return DXGI_FORMAT_R32_FLOAT;

    case D3DFMT_R16F:
        return DXGI_FORMAT_R16_FLOAT;

    case D3DFMT_A8:
        return DXGI_FORMAT_A8_UNORM;
    case D3DFMT_P8:
    case D3DFMT_L8:
        return DXGI_FORMAT_R8_UNORM;

    case D3DFMT_DXT1:
        return DXGI_FORMAT_BC1_UNORM;
    case D3DFMT_DXT2:
        return DXGI_FORMAT_BC1_UNORM;
    case D3DFMT_DXT3:
        return DXGI_FORMAT_BC2_UNORM;
    case D3DFMT_DXT4:
        return DXGI_FORMAT_BC2_UNORM;
    case D3DFMT_DXT5:
        return DXGI_FORMAT_BC3_UNORM_SRGB;

    default:
        assert(FALSE); // unhandled format
        return DXGI_FORMAT_UNKNOWN;
    }
}

//--------------------------------------------------------------------------------------
// Get surface information for a particular format
//--------------------------------------------------------------------------------------
void GetSurfaceInfo( UINT width, UINT height, D3DFORMAT fmt, UINT* pNumBytes, UINT* pRowBytes, UINT* pNumRows )
{
    UINT numBytes = 0;
    UINT rowBytes = 0;
    UINT numRows  = 0;

    // From the DXSDK docs:
    //
    //     When computing DXTn compressed sizes for non-square textures, the 
    //     following formula should be used at each mipmap level:
    //
    //         max(1, width ч 4) x max(1, height ч 4) x 8(DXT1) or 16(DXT2-5)
    //
    //     The pitch for DXTn formats is different from what was returned in 
    //     Microsoft DirectX 7.0. It now refers the pitch of a row of blocks. 
    //     For example, if you have a width of 16, then you will have a pitch 
    //     of four blocks (4*8 for DXT1, 4*16 for DXT2-5.)"

    if( fmt == D3DFMT_DXT1 || fmt == D3DFMT_DXT2 || fmt == D3DFMT_DXT3 || fmt == D3DFMT_DXT4 || fmt == D3DFMT_DXT5 )
    {
        // Note: we support width and/or height being 0 in order to compute
        // offsets in functions like CBufferLockEntry::CopyBLEToPerfectSizedBuffer().
        int numBlocksWide = 0;
        if( width > 0 )
            numBlocksWide = max( 1, width / 4 );
        int numBlocksHigh = 0;
        if( height > 0 )
            numBlocksHigh = max( 1, height / 4 );
        //int numBlocks = numBlocksWide * numBlocksHigh;
        int numBytesPerBlock = ( fmt == D3DFMT_DXT1 ? 8 : 16 );
        rowBytes = numBlocksWide * numBytesPerBlock;
        numRows = numBlocksHigh;
    }
    else
    {
        UINT bpp = BitsPerPixel( fmt );
        rowBytes = ( width * bpp + 7) / 8; // round up to nearest byte
        numRows = height;
    }
    numBytes = rowBytes * numRows;
    if( pNumBytes != NULL )
        *pNumBytes = numBytes;
    if( pRowBytes != NULL )
        *pRowBytes = rowBytes;
    if( pNumRows != NULL )
        *pNumRows = numRows;
}

//--------------------------------------------------------------------------------------
#define ISBITMASK( r,g,b,a ) ( ddpf.dwRBitMask == r && ddpf.dwGBitMask == g && ddpf.dwBBitMask == b && ddpf.dwRGBAlphaBitMask == a )

//--------------------------------------------------------------------------------------
D3DFORMAT GetD3D9Format( DDPIXELFORMAT ddpf )
{
    if( ddpf.dwFlags & DDPF_RGB )	//rgb codes
                                    // Only do the more common formats
    {
        if( 32 == ddpf.dwRGBBitCount )
        {
            if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0xff000000) )
                return D3DFMT_A8R8G8B8;
            if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0x00000000) )
                return D3DFMT_X8R8G8B8;
            if( ISBITMASK(0x000000ff,0x00ff0000,0x0000ff00,0xff000000) )
                return D3DFMT_A8B8G8R8;
            if( ISBITMASK(0x000000ff,0x00ff0000,0x0000ff00,0x00000000) )
                return D3DFMT_X8B8G8R8;
            if( ISBITMASK(0xffffffff,0x00000000,0x00000000,0x00000000) )
                return D3DFMT_R32F;
        }

        if( 24 == ddpf.dwRGBBitCount )
        {
            if( ISBITMASK(0x00ff0000,0x0000ff00,0x000000ff,0x00000000) )
                return D3DFMT_R8G8B8;
        }

        if( 16 == ddpf.dwRGBBitCount )
        {
            if( ISBITMASK(0x0000F800,0x000007E0,0x0000001F,0x00000000) )
                return D3DFMT_R5G6B5;
        }
    }
    else if( ddpf.dwFlags & DDPF_LUMINANCE )
    {
        if( 8 == ddpf.dwRGBBitCount )
        {
            return D3DFMT_L8;
        }
    }
    else if( ddpf.dwFlags & DDPF_ALPHA )
    {
        if( 8 == ddpf.dwRGBBitCount )
        {
            return D3DFMT_A8;
        }
    }
    else if( ddpf.dwFlags & DDPF_FOURCC )  //fourcc codes (dxtn)
    {
        if( MAKEFOURCC('D','X','T','1') == ddpf.dwFourCC )
            return D3DFMT_DXT1;
        if( MAKEFOURCC('D','X','T','2') == ddpf.dwFourCC )
            return D3DFMT_DXT2;
        if( MAKEFOURCC('D','X','T','3') == ddpf.dwFourCC )
            return D3DFMT_DXT3;
        if( MAKEFOURCC('D','X','T','4') == ddpf.dwFourCC )
            return D3DFMT_DXT4;
        if( MAKEFOURCC('D','X','T','5') == ddpf.dwFourCC )
            return D3DFMT_DXT5;
    }
    
    return D3DFMT_UNKNOWN;
}

//--------------------------------------------------------------------------------------
HRESULT CreateTextureFromDDS( LPDIRECT3DDEVICE9 pDev, 
							 DDSURFACEDESC2_32BIT* pSurfDesc, 
							 BYTE* pBitData, 
							 UINT BitSize, 
							 LPDIRECT3DTEXTURE9* ppTex,
							 CreateDDSOptions* opt)
{
    HRESULT hr = S_OK;
    D3DLOCKED_RECT LockedRect;

    UINT iWidth    = pSurfDesc->dwWidth;
    UINT iHeight   = pSurfDesc->dwHeight;
    UINT iMipCount = pSurfDesc->dwMipMapCount;

	// kacvet777  correct by options
	iMipCount = opt->mipLevels;

    if( 0 == iMipCount )
	{
        iMipCount = 1;
	}



   // old code
    // D3DFORMAT fmt = GetD3D9Format( pSurfDesc->ddpfPixelFormat );

	// ksacvet777 new code
  D3DFORMAT fmt = D3DFMT_UNKNOWN;
  fmt = opt->format;
  if(fmt == D3DFMT_UNKNOWN)
  {
	  fmt = GetD3D9Format( pSurfDesc->ddpfPixelFormat );
  }



    // Create the texture
    LPDIRECT3DTEXTURE9 pTexture;
    LPDIRECT3DTEXTURE9 pStagingTexture;
    hr = pDev->CreateTexture( iWidth,
                              iHeight,
                              iMipCount,
                               opt->usage,     // old usage is: 0, // usage
                              fmt,
                              opt->pool,      // old pool is:  D3DPOOL_DEFAULT,
                              &pTexture,
                              NULL );
    if(FAILED(hr))
        return hr;
    hr = pDev->CreateTexture( iWidth,
                              iHeight,
                              iMipCount,
                              0, // usage
                              fmt,
                              D3DPOOL_SYSTEMMEM,
                              &pStagingTexture,
                              NULL );
    if(FAILED(hr))
        return hr;

    // Lock, fill, unlock
    UINT RowBytes, NumRows;
    BYTE* pSrcBits = pBitData;

    for( UINT i=0; i<iMipCount; i++ )
    {
        GetSurfaceInfo( iWidth, iHeight, fmt, NULL, &RowBytes, &NumRows );

        if( SUCCEEDED( pStagingTexture->LockRect( i, &LockedRect, NULL, 0 ) ) )
        {
            BYTE* pDestBits = (BYTE*)LockedRect.pBits;

            // Copy stride line by line
            for( UINT h=0; h<NumRows; h++ )
            {
                CopyMemory( pDestBits, pSrcBits, RowBytes ); 
                pDestBits += LockedRect.Pitch;
                pSrcBits += RowBytes;
            }

            pStagingTexture->UnlockRect( i );
        }

        iWidth = iWidth >> 1;
        iHeight = iHeight >> 1;
        if( iWidth == 0 )
            iWidth = 1;
        if( iHeight == 0 )
            iHeight = 1;
    }

    hr = pDev->UpdateTexture( pStagingTexture, pTexture );
    SAFE_RELEASE( pStagingTexture );
    if(FAILED(hr))
        return hr;

    // Set the result
    *ppTex = pTexture;
    return hr;
}


//--------------------------------------------------------------------------------------
GB_D3D9_API HRESULT CreateDDSTextureFromFileA( LPDIRECT3DDEVICE9 pDev,  
										   CHAR* szFileName, 
										   IDirect3DTexture9** ppTex,
										   const CreateDDSOptions* pOpt)
{
	HRESULT hr = S_OK;

	BYTE*                 pHeapData = NULL;
	DDSURFACEDESC2_32BIT* pSurfDesc = NULL;
	BYTE*                 pBitData = NULL;
	UINT                  BitSize = 0;

	CreateDDSOptions options;
	if(pOpt)
	{
		options = *pOpt;
	}

	 
	if( !LoadTextureDataFromFileA( szFileName, &pHeapData, &pSurfDesc, &pBitData, &BitSize ) )
	{

		return E_FAIL;
	}

	  hr |= CreateTextureFromDDS( pDev, pSurfDesc, pBitData, BitSize, ppTex, &options );

	SAFE_DELETE_ARRAY( pHeapData );
	return hr;
}


//--------------------------------------------------------------------------------------
GB_D3D9_API HRESULT CreateDDSTextureFromFileW( LPDIRECT3DDEVICE9 pDev, 
										   WCHAR* szFileName,
										   IDirect3DTexture9** ppTex,
										   const CreateDDSOptions* pOpt)
{
	HRESULT hr = S_OK;

    BYTE*                 pHeapData = NULL;
    DDSURFACEDESC2_32BIT* pSurfDesc = NULL;
    BYTE*                 pBitData = NULL;
    UINT                  BitSize = 0;

	CreateDDSOptions options;
	if(pOpt)
	{
		options = *pOpt;
	}

    if( !LoadTextureDataFromFileW( szFileName, &pHeapData, &pSurfDesc, &pBitData, &BitSize ) )
        return E_FAIL;
    
	  hr |= CreateTextureFromDDS( pDev, pSurfDesc, pBitData, BitSize, ppTex, &options );

    SAFE_DELETE_ARRAY( pHeapData );
    return hr;
}
  