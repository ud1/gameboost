
#if ( defined(GB_D3D9) && defined(WIN32)  )
#if defined(GB_D3DX9)

#include <gb/graphics/visual_geometry/internal/vg_impl_d3d9.h>
#include <gb/str/formater.h>


namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {


//=========================================================================




//=========================================================================
HRESULT VGSaveRestoreDataD3D9::SaveDeviceData(IDirect3DDevice9 *pdevice, const
  VGCOLOR &newColor, float pointSize, IDirect3DTexture9 *newTxtr)
{
  HRESULT hr = S_OK;
  D3DMATERIAL9 newMat;

  assert(pdevice);

  hr |= pdevice->GetFVF(&fvf);
  hr |= pdevice->GetMaterial(&material);
  if (newColor)
  {
    newMat.Diffuse.r = newColor.r;
    newMat.Diffuse.g = newColor.g;
    newMat.Diffuse.b = newColor.b;
    newMat.Diffuse.a = newColor.a;

    newMat.Emissive.r = newColor.r;
    newMat.Emissive.g = newColor.g;
    newMat.Emissive.b = newColor.b;
    newMat.Emissive.a = newColor.a;

  };

  hr |= pdevice->SetMaterial(&newMat);
  hr |= pdevice->GetTransform(D3DTS_WORLD, &wMatrix);
  hr |= pdevice->GetTexture(0, &texture0);
  hr |= pdevice->SetTexture(0, newTxtr);


  // OLD >>	hr |= m_pdevice->GetRenderState( D3DRS_POINTSIZE, &rsPointSize );
  hr |= pdevice->GetRenderState(D3DRS_POINTSIZE, &rsPointSize);

  hr |= pdevice->GetRenderState(D3DRS_ZENABLE, &rsZENABLE);
  hr |= pdevice->GetRenderState(D3DRS_ZWRITEENABLE, &rsZWRITEENABLE);


  hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*) &pointSize));

  hr |= pdevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &rsALPHABLENDENABLE);
  hr |= pdevice->GetRenderState(D3DRS_FILLMODE, &rsFillMode);

  hr |= pdevice->GetVertexShader(&pIVSH);
  hr |= pdevice->GetPixelShader(&pIPSH);

  return hr;
};

//======================================================================
HRESULT VGSaveRestoreDataD3D9::RestoreDeviceData(IDirect3DDevice9 *pdevice)
{
  HRESULT hr = S_OK;
  hr |= pdevice->SetFVF(fvf);
  hr |= pdevice->SetMaterial(&material);
  hr |= pdevice->SetTransform(D3DTS_WORLD, &wMatrix);
  hr |= pdevice->SetTexture(0, texture0);

  if (texture0)
  {
    texture0->Release();
    texture0 = NULL;
  };

  hr |= pdevice->SetRenderState(D3DRS_ZENABLE, rsZENABLE);
  hr |= pdevice->SetRenderState(D3DRS_ZWRITEENABLE, rsZWRITEENABLE);
  hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, rsPointSize);
  hr |= pdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, rsALPHABLENDENABLE);
  hr |= pdevice->SetRenderState(D3DRS_FILLMODE, rsFillMode);

  hr |= pdevice->SetVertexShader(pIVSH);

  if (pIVSH)
  {
    pIVSH->Release();
    pIVSH = NULL;
  };

  hr |= pdevice->SetPixelShader(pIPSH);
  if (pIVSH)
  {
    pIPSH->Release();
    pIPSH = NULL;
  };


  return hr;
};



//=========================================================
void VGDrawValuesImpl_D3D9::ComputeNextPos()const
{
  if (m_bChangePos)
  {
    // ???????
  };

  switch (m_lastFontSize)
  {

    case FS_NORMAL:
      {
        m_Rec.top += CONST_DRWVAL_FONTS_COMM_BETWLINES_OFFSET;
        switch (m_lastFontSize)
        {
        case FS_NORMAL:
          m_Rec.top += CONST_DRWVAL_NORMALFONT_NEWSTR_OFFSET;
          break;
        case FS_SMALL:
          m_Rec.top += CONST_DRWVAL_SMALLFONT_NEWSTR_OFFSET;
          break;
        case FS_BIG:
          m_Rec.top += CONST_DRWVAL_BIGFONT_NEWSTR_OFFSET;
          break;
        }
        ;

      }
      break; 

    case FS_SMALL:
      {
        m_Rec.top += CONST_DRWVAL_FONTS_COMM_BETWLINES_OFFSET;
        switch (m_lastFontSize)
        {
        case FS_NORMAL:
          m_Rec.top += CONST_DRWVAL_NORMALFONT_NEWSTR_OFFSET;
          break;
        case FS_SMALL:
          m_Rec.top += CONST_DRWVAL_SMALLFONT_NEWSTR_OFFSET;
          break;
        case FS_BIG:
          m_Rec.top += CONST_DRWVAL_BIGFONT_NEWSTR_OFFSET;
          break;
        }

      }
      break; 

    case FS_BIG:
      {
        m_Rec.top += CONST_DRWVAL_FONTS_COMM_BETWLINES_OFFSET;
        switch (m_lastFontSize)
        {
        case FS_NORMAL:
          m_Rec.top += CONST_DRWVAL_NORMALFONT_NEWSTR_OFFSET;
          break;
        case FS_SMALL:
          m_Rec.top += CONST_DRWVAL_SMALLFONT_NEWSTR_OFFSET;
          break;
        case FS_BIG:
          m_Rec.top += CONST_DRWVAL_BIGFONT_NEWSTR_OFFSET;
          break;
        }
      }
      break;

  }; // switch

 
};

//=============================================
HRESULT VGDrawValuesImpl_D3D9::drawStrEx(const char *str) const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  hr |= checkFontInterfaces();
  if FAILED(hr)
  {
    return hr;
  }

  //* вычислить позицию
  ComputeNextPos();

  D3DCOLOR _d3dcolor = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
    m_color.a);

  switch (m_lastFontSize)
  {
 

    case FS_NORMAL:
      {
        //* draw small font
        hr |= pIFontNormal->DrawTextA(NULL, str,  - 1,  &m_Rec, DT_LEFT,
                                      _d3dcolor);

      }
      ;
      break;

    case FS_SMALL:
      {
        //* draw small font
        hr |= pIFontSmall->DrawTextA(NULL, str,  - 1,  &m_Rec, DT_LEFT,
                                     _d3dcolor);

      }
      break;

    case FS_BIG:
      {
        //* draw big font
        hr |= pIFontBig->DrawTextA(NULL, str,  - 1,  &m_Rec, DT_LEFT, _d3dcolor)
                                   ;

      }
      break;


    default:
      return S_FALSE; //* not found font size
  };

  return hr;
};

//=========================================================
HRESULT VGDrawValuesImpl_D3D9::drawS(const char *s)const
{
  HRESULT hr = 0;

  hr |= this->drawStrEx(  s);

  #pragma message("NEED CHECK  CODE"  __FILE__)

  return hr;
};

//============================================================
HRESULT VGDrawValuesImpl_D3D9::drawF(const char *_Format, ...)const
{
  HRESULT hr = 0;

  static char ss[8192];
  ss[0] = 0;

  va_list ap;
  va_start(ap, _Format);
  vsprintf(ss, _Format, ap);
  va_end(ap);

  hr |= drawS(ss);


  #pragma message("NEED CHECK  CODE"  __FILE__)

  return hr;
};

HRESULT VGDrawValuesImpl_D3D9::drawBool(bool val, const char *promt)const
{
  HRESULT hr = 0;

  char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  if (val)
  {
    strcat(buf, "true");
  }
  else
  {
    strcat(buf, "fasle");
  };

  hr |= drawS(buf);

  return hr;
};

//=====================================
HRESULT VGDrawValuesImpl_D3D9::drawInt(int val, const char *promt)const
{
  HRESULT hr = 0;

  char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  char bufdigit[32];
  bufdigit[0] = 0;

  sprintf(bufdigit, "%i", val);
  strcat(buf, bufdigit);

  hr |= drawS(buf);

  return hr;
};

//=====================================
HRESULT VGDrawValuesImpl_D3D9::drawFloat(float val, const char *promt)const
{
  HRESULT hr = 0;

  char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  char bufdigit[32];
  bufdigit[0] = 0;

  sprintf(bufdigit, "%f", val);
  strcat(buf, bufdigit);

  hr |= drawS(buf);

  return hr;
};

//==================================================================
HRESULT VGDrawValuesImpl_D3D9::checkFontInterfaces()const
{
  HRESULT hr = 0;
  assert(m_pdevice);



  //*  create font small
  if (!pIFontSmall)
  {
    hr |= D3DXCreateFontA(m_pdevice, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                          OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
                          FF_DONTCARE, "Courier New", &pIFontSmall);
  };
  if FAILED(hr)
  {
    return hr;
  }

  //* create font  big
  if (!pIFontBig)
  {
    hr |= D3DXCreateFontA(m_pdevice, 19, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                          OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
                          FF_DONTCARE, "Courier New", &pIFontBig);
  };
  if FAILED(hr)
  {
    return hr;
  }

  // * crate font noraml  
  if (!pIFontNormal)
  {
    hr |= D3DXCreateFontA(m_pdevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                          OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
                          FF_DONTCARE, "Courier New", &pIFontNormal);
  };
  if FAILED(hr)
  {
    return hr;
  }


  #pragma message("ks777:  NEED CHECK NORMAL FONT"  __FILE__ )

  return hr;
};

//==================================================================
HRESULT VGDrawValuesImpl_D3D9::drawIntArray(const int *p, int num, const char
  *promt)const
{
  HRESULT hr = 0;
  static char ss[2048];
  ss[0] = 0;

  if (promt)
  {
    strcat(ss, promt);
    strcat(ss, " ");
  };

  char buf[32];

  for (int c = 0; c < num; c++)
  {
    buf[0] = 0;
    int curr = *(p + c);
    sprintf(buf, "%i", curr);
    strcat(ss, buf);
    strcat(ss, " ");

  };

  hr |= drawS(ss);


  return hr;
};

//==================================================================
HRESULT VGDrawValuesImpl_D3D9::drawFloatArray(const float *p, int num, const
  char *promt)const
{
  HRESULT hr = 0;
  static char ss[2048];
  ss[0] = 0;

  if (promt)
  {
    strcat(ss, promt);
    strcat(ss, " ");
  };

  char buf[32];

  for (int c = 0; c < num; c++)
  {
    buf[0] = 0;
    float curr = *(p + c);
    sprintf(buf, "%f", curr);
    strcat(ss, buf);
    strcat(ss, " ");

  };

  hr |= drawS(ss);



  return hr;
};

#pragma message("ks777:  Перенести в общую"  __FILE__ )
//==========================================================
static void __StrFromFloatForDrawVec(char *buf, const FLOAT f)
{
  _gcvt((double)f, 10, buf);
};

//==================================================================
HRESULT VGDrawValuesImpl_D3D9::drawVec2(const VGVEC2 *v, const char *promt)const
{
  HRESULT hr = S_OK;

  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

  //str += "x= ";
  __StrFromFloatForDrawVec(sdigit, v->x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v->y);
  str += sdigit;


  hr |= drawS(str.c_str());

  return hr;
};

//==================================================================
HRESULT VGDrawValuesImpl_D3D9::drawVec3(const VGVEC3 *v, const char *promt)const
{
  HRESULT hr = S_OK;

  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };


  __StrFromFloatForDrawVec(sdigit, v->x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v->y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v->y);
  str += sdigit;


  hr |= drawS(str.c_str());

  return hr;
};

//=====================================================================
HRESULT VGDrawValuesImpl_D3D9::drawVec4(const VGVEC4 *v, const char *promt)const
{
  HRESULT hr = S_OK;

  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };


  __StrFromFloatForDrawVec(sdigit, v->x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v->y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v->y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v->z);
  str += sdigit;


  hr |= drawS(str.c_str());

  return hr;
};


#pragma message("ks777:  Перенести в общее  " __FILE__)
//=========================================================================
static void __FormatFloatMatrix(char *buf, float f)
{
  *buf = 0;

  char *pCurrBuffer = buf;

  if (f >= 0.0f)
  {
    strcat(buf, " ");
    pCurrBuffer++;

  };

  static char ssformat[8];
  ssformat[0] = 0;
  strcat(ssformat, "%");

  char tbuf[32];

  static int d0 = 0;
  gb::str::Formater::intToCstr(tbuf, 32, d0, false);
  strcat(ssformat, tbuf);

  static int d1 = 1;
  gb::str::Formater::intToCstr(tbuf, 32, d1, false);
  strcat(ssformat, tbuf);
  strcat(ssformat, ".");

  static int d2 = 6;
  gb::str::Formater::intToCstr(tbuf, 32, d2, false);
  strcat(ssformat, tbuf);



  // format
  sprintf(pCurrBuffer, "%01.6f", f); //  ssformat , f );


  const int STRLEN = (int)strlen(buf);

  static const int ALIGN = 10;
  for (int c = 0; c < ALIGN - STRLEN; c++)
  {
    strcat(buf, " ");
  };

  int _end = 0;
  // debug
  printf("len: %d\n", strlen(buf));
};

//==========================================================
HRESULT VGDrawValuesImpl_D3D9::drawMatrix(const VGMATRIX *m, const char *promt)
  const
{
  HRESULT hr = S_OK;

  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
    str += "\n";
  };



  // row 1
  __FormatFloatMatrix(sdigit, m->_11);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_12);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_13);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_14);
  str += sdigit;
  str += "\n";


  // row 2
  __FormatFloatMatrix(sdigit, m->_21);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_22);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_23);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_24);
  str += sdigit;
  str += "\n";


  // row 3
  __FormatFloatMatrix(sdigit, m->_31);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_32);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_33);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_34);
  str += sdigit;
  str += "\n";


  // row 4
  __FormatFloatMatrix(sdigit, m->_41);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_42);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_43);
  str += sdigit;
  str += "  ";

  __FormatFloatMatrix(sdigit, m->_44);
  str += sdigit;
  str += "\n";


  hr |= drawS(str.c_str());

  return hr;
};




//=====================================================================
/*
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoint  (const VGVEC3* pos,   float pointSize,  
_in_opt  VGMATRIX* pTransf) const 
{
HRESULT hr =0;

assert(m_pdevice);

// prepare
//
hr = m_DeviceData.SaveDeviceData (pdevice,  &m_color,  pointSize  , NULL );
hr = hr | m_pdevice->SetFVF(  VG_FVF_3DLINES );

if ( pTransf != NULL )
{
hr |= m_pcontext->SetMatrixWorld  (  pTransf );
}
else
{
hr |= m_pcontext->SetMatrixWorld(  &D3DXMATRIX_IDENTITY );
};

// draw
//
hr |= m_pdevice->DrawPrimitiveUP( D3DPT_POINTLIST, 1, ( void* )pos, sizeof( D3DVECTOR ) );

// restore
//
hr |= m_DeviceData.RestoreDeviceData(pdevice);


return hr;
};
 */

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoint(float _x, float _y, float _z,
  float pointSize, _in_opt VGMATRIX *pTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  hr |= draw3dPoint(&VGVEC3(_x, _y, _z), pointSize, pTransf);

  return hr;
};

//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoint(const VGVEC3 *pos, float
  pointSize, _in_opt VGMATRIX *pTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  hr |= draw3dPoint(&VGVEC3(pos->x, pos->y, pos->z), pointSize, pTransf);

  return hr;
};

//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoints(const VGVEC3 *pv, int num,
  float pointSize, _in_opt VGMATRIX *pTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  hr = m_DeviceData.SaveDeviceData(m_pdevice, &m_color, pointSize, NULL);
  hr = hr | m_pdevice->SetFVF(VG_FVF_3DLINES);

  //if ( pTransf  )
  //{
  //	hr |= m_pdevice->SetTransform( D3DTS_WORLD, pTransf );
  //}
  //else
  //{
  //	
  //	hr |= m_pdevice->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&gb::math::base::MATRIX44_IDENTITY );
  //};

  // draw
  //
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, num, (void*)pv, sizeof
                                   (D3DVECTOR));

  // restore
  //
  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=============================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLine(const VGVEC3 *p1, const VGVEC3
  *p2, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  D3DVECTOR varr[2];


  // prepare
  //
  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, 1);

  //*( ( D3DVECTOR* ) ( &varr[0] ) ) = *( ( D3DVECTOR* ) ( &p1 ) );
  //*( ( D3DVECTOR* ) ( &varr[1] ) ) = *( ( D3DVECTOR* ) ( &p2 ) );

  varr[0] =  *p1;
  varr[1] =  *p2;



  //if ( mTransf )
  //{
  //	hr |=  m_pcontext->SetMatrixWorld(mTransf);
  //}
  //else
  //{
  //	hr |=  m_pcontext->SetMatrixWorld(&D3DXMATRIX_IDENTITY);
  //}

  // draw
  //
  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*) &varr[0], sizeof
                                   (D3DVECTOR));

  // restore
  //
  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLine(float x1, float y1, float z1,
  float x2, float y2, float z2, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  VGVEC3 varr[2];

  varr[0].x = x1;
  varr[0].y = y1;
  varr[0].z = z1;

  varr[1].x = x2;
  varr[1].y = y2;
  varr[1].z = z2;

  hr |= draw3dLine(&varr[0], &varr[1], mTransf);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLines(const VGVEC3 *pv, int num)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);


  // D3DPT_LINELIST
  // D3DPT_LINESTRIP << было 

  const UINT nNumValue = num - 1;
  const int NSIZEOF = sizeof(VGVEC3);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumValue, (void*)pv,
                                   NSIZEOF);


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::drawAABB(const VGVEC3 *min, const VGVEC3
  *max, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = S_OK;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  const int NSIZEOF = sizeof(VGVEC3);

  static VGVEC3 vArrLine[8];
  ZeroMemory(vArrLine, sizeof(VGVEC3) *8);

  static const int nCount_quad_vert = 4;


  ///  first quad ///
  /// 0
  vArrLine[0].x = min->x;
  vArrLine[0].y = min->y;
  vArrLine[0].z = min->z;


  /// 1
  vArrLine[1].x = max->x;
  vArrLine[1].y = min->y;
  vArrLine[1].z = min->z;


  /// 2
  vArrLine[2].x = max->x;
  vArrLine[2].y = max->y;
  vArrLine[2].z = min->z;


  /// 3
  vArrLine[3].x = min->x;
  vArrLine[3].y = max->y;
  vArrLine[3].z = min->z;


  /// 4
  vArrLine[4].x = min->x;
  vArrLine[4].y = min->y;
  vArrLine[4].z = min->z;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*)
                                   vArrLine, NSIZEOF);



  ///  second quad ///
  /// 0
  vArrLine[0].x = max->x;
  vArrLine[0].y = max->y;
  vArrLine[0].z = max->z;

  /// 1
  vArrLine[1].x = max->x;
  vArrLine[1].y = min->y;
  vArrLine[1].z = max->z;


  // 2
  vArrLine[2].x = min->x;
  vArrLine[2].y = min->y;
  vArrLine[2].z = max->z;


  // 3
  vArrLine[3].x = min->x;
  vArrLine[3].y = max->y;
  vArrLine[3].z = max->z;


  // 4
  vArrLine[4].x = max->x;
  vArrLine[4].y = max->y;
  vArrLine[4].z = max->z;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*)
                                   vArrLine, NSIZEOF);



  //////////    draw other borders ///////////////////
  if (1)
  {

    static const int nCount_border = 1;


    /// border 0    ///
    vArrLine[0].x = max->x;
    vArrLine[0].y = max->y;
    vArrLine[0].z = max->z;

    vArrLine[1].x = max->x;
    vArrLine[1].y = max->y;
    vArrLine[1].z = min->z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);



    /// border 1    ///
    vArrLine[0].x = min->x;
    vArrLine[0].y = max->y;
    vArrLine[0].z = max->z;

    vArrLine[1].x = min->x;
    vArrLine[1].y = max->y;
    vArrLine[1].z = min->z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);


    /// border 2   ///
    vArrLine[0].x = max->x;
    vArrLine[0].y = min->y;
    vArrLine[0].z = max->z;

    vArrLine[1].x = max->x;
    vArrLine[1].y = min->y;
    vArrLine[1].z = min->z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);


    /// border 3    ///
    vArrLine[0].x = min->x;
    vArrLine[0].y = min->y;
    vArrLine[0].z = min->z;

    vArrLine[1].x = min->x;
    vArrLine[1].y = min->y;
    vArrLine[1].z = max->z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);

  };


  /// end ///


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};


//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(const VGVEC3 *orig, const VGVEC3
  *normal, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = S_OK;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  VGVEC3 varr[4]; //! было 1

  varr[0].x = orig->x;
  varr[0].y = orig->y;
  varr[0].z = orig->z;

  static const float VG_MAX_INFINITY_VALUE = 3.4E30f;
  VGVEC3 vt;
  D3DXVec3Scale(vt,  *orig, VG_MAX_INFINITY_VALUE);
  D3DXVec3Add(varr[1],  *orig, vt);


  const UINT nNumValue = 1; // num-1;

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumValue, (void*)varr,
                                   sizeof(VGVEC3));

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(
					float orgX, float orgY, float  orgZ, 
					float nrmlX, float nrmlY, float nrmlZ, 
					_in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);
  VGVEC3 orig = VGVEC3(orgX, orgY, orgZ);
  VGVEC3 nrml = VGVEC3(nrmlX, nrmlY, nrmlZ);

  hr |= draw3dRay(&orig, &nrml, mTransf);
  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(const gb::math::geom3d::Ray *ray,
  _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);
  VGVEC3 orig = VGVEC3(ray->orig.x, ray->orig.y, ray->orig.z);
  VGVEC3 nrml = VGVEC3(ray->dir.x, ray->dir.y, ray->dir.z);

  hr |= draw3dRay(&orig, &nrml, mTransf);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dTraingle(
				const VGVEC3 *v1, const VGVEC3 *v2, const VGVEC3 *v3,
				_in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);

  static VGVEC3 varr[4];
  varr[0] =  *v1;
  varr[1] =  *v2;
  varr[2] =  *v3;
  varr[3] =  *v1;

  static const UINT nNumValue = 3;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumValue, (void*)varr,
                                   sizeof(VGVEC3));


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dTraingle(const gb::math::geom3d
  ::Triangle *tri, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  VGVEC3 varr[3];

  varr[0].x = tri->p1.x;
  varr[0].y = tri->p1.y;
  varr[0].z = tri->p1.z;

  varr[1].x = tri->p2.x;
  varr[1].y = tri->p2.y;
  varr[1].z = tri->p2.z;

  varr[2].x = tri->p3.x;
  varr[2].y = tri->p3.y;
  varr[2].z = tri->p3.z;

  hr |= draw3dTraingle(&varr[0], &varr[1], &varr[2], mTransf);


  return hr;
};

//===========================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dArrow(const VGVEC3 *src, const VGVEC3
  *dest, _in_opt VGMATRIX *mTransf)const
{
  HRESULT hr = 0;

  #pragma message ("ks777: НЕ РАБОТАЕТ КОРРЕКТНО Draw3dArrow "  __FILE__ )
  return E_FAIL;


  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);

  //////// make matrix   ////////////




  // make scaling
  VGMATRIX msc;
  {
    D3DXMatrixIdentity(msc);

    VGVEC3 vsub;
    vsub = (*dest) - (*src);
    float fdistance = D3DXVec3Length(vsub);
    static bool stb_inverse = false;
    if (stb_inverse)
    {
      fdistance =  - fdistance;
    };
    D3DXMatrixScaling(msc, fdistance, fdistance, fdistance);

  };



  // make rotation
  VGMATRIX mrot;
  {
    D3DXMatrixIdentity(mrot);
    //mrot.setIdentity();

    VGVEC3 vNormal;
    vNormal = (*dest) - (*src);
    D3DXVec3Normalize(vNormal, vNormal);
    vNormal = vNormal;
    const VGVEC3 IDENTITY_NORMAL = VGVEC3( - 0.0f,  - 0.0f, 1.0f);

    VGVEC3 vCross;
    D3DXVec3Cross(vCross, vNormal, IDENTITY_NORMAL);
    D3DXVec3Normalize(vCross, vCross);
    float angle =  - acos(D3DXVec3Dot(vCross, vNormal));


    D3DXMatrixRotationAxis(mrot, vCross, angle);

  };


  // make translation 
  VGMATRIX mtr;
  {
    D3DXMatrixIdentity(mtr);

    D3DXMatrixTranslation(mtr, src->x, src->y, src->z);
  }



  VGMATRIX matrix; // final matrix
  matrix = msc * mrot * mtr;

  if (mTransf)
  {
    matrix = matrix **mTransf;

  }
  else
  {


  }
    ;

  hr |= m_pdevice->SetTransform(D3DTS_WORLD, matrix);

  assert(false);
  // надо поменять !!!
  return E_FAIL;
  //hr |= m_pcontext->DrawPrimitiveArrow();



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=======================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dAxies(const VGVEC3 *coord, float
  axiesLen)const
{
  HRESULT hr = 0;
  VGCOLOR oldcolor = m_color;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  VGVEC3 varr[2];
  D3DMATERIAL9 material;

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->GetMaterial(&material);


  // x
  varr[0] =  *coord;
  varr[1] =  *coord;
  varr[1].x += axiesLen;
  material.Emissive.r = 1.0f;
  material.Emissive.g = 0.0f;
  material.Emissive.b = 0.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (VGVEC3));



  // y
  varr[0] =  *coord;
  varr[1] =  *coord;
  varr[1].y += axiesLen;
  material.Emissive.r = 0.0f;
  material.Emissive.g = 1.0f;
  material.Emissive.b = 0.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (VGVEC3));



  // z
  varr[0] =  *coord;
  varr[1] =  *coord;
  varr[1].z += axiesLen;
  material.Emissive.r = 0.0f;
  material.Emissive.g = 0.0f;
  material.Emissive.b = 1.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (VGVEC3));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  hr |= setColor(&oldcolor);
  return hr;
};


//==============================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dSolidSphere(const VGVEC3 *center,
  float radius)const
{
  HRESULT hr = 0;
  assert(false);
  assert(m_pdevice);

  VGMATRIX m;
  D3DXMatrixIdentity(m);

  VGMATRIX msc;
  D3DXMatrixScaling(msc, radius, radius, radius);

  VGMATRIX mtr;
  D3DXMatrixTranslation(mtr, center->x, center->y, center->z);


  /*
  m =  mtr * msc;
  if(mTransf)
  {
  m =  m  * *mTransf;
  }
  else
  {

  };
   */




  return hr;
};






//=========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPoint(float x, float y, float
  pointSize)const
{
  HRESULT hr = 0;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, pointSize);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  TVgVert2D vert;
  vert.x = x;
  vert.y = y;
  vert.z = 0.0f;
  vert.rhw = 2.0f;
  //vert.color

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, (void*) &vert, sizeof
                                   (TVgVert2D));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//======================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPoints(const VGVEC2 *pv, int num,
  float pointSize)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  static const int NARRLEN = 256;
  static TVgVert2D varr[NARRLEN];
  for (int c = 0; (c < num) && (c < NARRLEN); c++)
  {
    varr[c].x = (pv + c)->x;
    varr[c].y = (pv + c)->y;
    varr[c].z = 0.0f;
    varr[c].rhw = 2.0;
    varr[c].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

  };


  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, pointSize);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  int numpoints = num;
  if (numpoints < num)
  {
    numpoints = NARRLEN;
    hr |= S_FALSE; // check max
  };

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, numpoints, (void*)varr,
                                   sizeof(TVgVert2D));

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=========================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dLine(const VGVEC2 *p1, const VGVEC2
  *p2)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  static TVgVert2D varr[2];

  varr[0].x = p1->x;
  varr[0].y = p1->y;
  varr[0].z = 0.0f;
  varr[0].rhw = 2.0f;
  varr[0].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                      m_color.a);

  varr[1].x = p2->x;
  varr[1].y = p2->y;
  varr[1].z = 0.0f;
  varr[1].rhw = 2.0f;
  varr[1].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                      m_color.a);


  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  // D3DPT_LINELIST              = 2,
  // D3DPT_LINESTRIP
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (TVgVert2D));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=======================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dLines(const VGVEC2 *pv, int num)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  if (num < 2)
  {
    return S_FALSE;
  }

  static const int NARRLEN = 256;
  static TVgVert2D varr[NARRLEN];

  for (int c = 0; (c < NARRLEN) && (c < num); c++)
  {
    varr[c].x = (pv + c)->x;
    varr[c].y = (pv + c)->y;
    varr[c].z = 0.0f;
    varr[c].rhw = 2.0f;
    varr[c].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

  };



  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);


  int numpoints = num - 1;
  if (numpoints > NARRLEN)
  {
    numpoints = NARRLEN;
    hr |= S_FALSE; // check max
  };

  // D3DPT_LINELIST              = 2,
  // D3DPT_LINESTRIP
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, numpoints, (void*)varr,
                                   sizeof(TVgVert2D));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=====================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dRect(const D3DRECT *rect)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  VGVEC2 varr[5];

  varr[0].x = (FLOAT)rect->x1;
  varr[0].y = (FLOAT)rect->y1;

  varr[1].x = (FLOAT)rect->x2;
  varr[1].y = (FLOAT)rect->y1;

  varr[2].x = (FLOAT)rect->x2; // + rect.x2;
  varr[2].y = (FLOAT)rect->y2; // + rect.y2;

  varr[3].x = (FLOAT)rect->x1;
  varr[3].y = (FLOAT)rect->y2;

  varr[4] = varr[0];

  hr |= draw2dLines(varr, 5);


  return hr;
};

//============================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dSolidRect(int x1, int y1, int x2, int
  y2)const 
//const D3DRECT* rect) const 
{
  HRESULT hr = 0;
  assert(m_pdevice);
  #pragma message("НЕ РАБОТАЕТ ПРОЗРАЧНОСТЬ КАК ХОТЕЛОСЬ БЫ" __FILE__ )


  static TVgVert2D screenQuadVertices[] = 
  {
    {
      10.0f, 0.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 
    {
      300.0f, 0.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 
    {
      300.0f, 400.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 
    {
      10.0f, 0.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 
    {
      300.0f, 400.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 
    {
      10.0f, 400.0f, 1.0f, 1.0f, 0xffffffff, 
    }
    , 

  };



  {
    float fleft = (float)x1;
    float ftop = (float)y1;
    float fright = (float)x2;
    float fbottom = (float)y2;

    screenQuadVertices[0].x = fleft;
    screenQuadVertices[0].y = ftop;
    screenQuadVertices[1].x = fright;
    screenQuadVertices[1].y = ftop;
    screenQuadVertices[2].x = fright;
    screenQuadVertices[2].y = fbottom;

    screenQuadVertices[3].x = fleft;
    screenQuadVertices[3].y = ftop;
    screenQuadVertices[4].x = fright;
    screenQuadVertices[4].y = fbottom;
    screenQuadVertices[5].x = fleft;
    screenQuadVertices[5].y = fbottom;
  }


  for (int c = 0; c < 6; c++)
  {
    screenQuadVertices[c].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g,
      m_color.b, m_color.a);
  }


  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, (void*)
                                   screenQuadVertices, sizeof(TVgVert2D));

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=======================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dCircle(const VGVEC2 *pos, float
  radius)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  static const int SEGM = 32;
  VGVEC2 varr[SEGM + 1];

  static const FLOAT FACT = 0.0f;
  FLOAT valfact = FACT;

  int valSEGM = SEGM;
  for (int c = 0; c < SEGM; c++)
  {

    valfact = (FLOAT)c / SEGM;
    varr[c].x = sin((D3DX_PI *2.0f) *valfact) *radius;
    varr[c].y = cos((D3DX_PI *2.0f) *valfact) *radius;

    varr[c].x += pos->x;
    varr[c].y += pos->y;

  };

  varr[SEGM] = varr[0];
  varr[SEGM + 1] = varr[0];


  //D3DCOLOR clr = D3DCOLOR_COLORVALUE( color->r, color->g, color->b, color->a );

  //hr |= g_pILine->SetWidth( fLineWidth );
  //hr |= g_pILine->Begin();

  DWORD num = (DWORD)SEGM + 1;
  //hr |= g_pILine->Draw( &varr[0], num, clr );
  hr |= draw2dLines(varr, num);

  //hr |= g_pILine->End();


  return hr;
};

//===================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dAxies(const VGVEC2 coord)const
{
  HRESULT hr = 0;
  assert(m_pdevice);
  gb::color::Color4f oldcolor = m_color;


  VGVEC2 varr[2];
  const float _MAX_VALUE_ = 2500.0f;

  // x
  hr |= setColorRed();
  varr[0] = VGVEC2(0.0f, coord.y);
  varr[1] = VGVEC2(_MAX_VALUE_, coord.y);
  hr |= draw2dLine(&varr[0], &varr[1]);


  // y
  hr |= setColorGreen();
  varr[0] = VGVEC2(coord.x, 0.0f);
  varr[1] = VGVEC2(coord.x, _MAX_VALUE_);
  hr |= draw2dLine(&varr[0], &varr[1]);


  hr |= setColor(&oldcolor);
  return hr;
};

//========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dTriangle(const VGVEC2 *p1, const
  VGVEC2 *p2, const VGVEC2 *p3)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  VGVEC2 varr[4];
  varr[0] =  *p1;
  varr[1] =  *p2;
  varr[2] =  *p3;
  varr[3] =  *p1;

  return draw2dLines(varr, 4);
};

//====================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dSolidTriangle(const VGVEC2 *p1, const
  VGVEC2 *p2, const VGVEC2 *p3)const
{
  HRESULT hr = 0;
  assert(m_pdevice);


  static TVgVert2D varr[3];


  {
    varr[0].x = p1->x;
    varr[0].y = p1->y;
    varr[0].z = 0.0f;
    varr[0].rhw = 2.0f;
    varr[0].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

    varr[1].x = p2->x;
    varr[1].y = p2->y;
    varr[1].z = 0.0f;
    varr[1].rhw = 2.0f;
    varr[1].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

    varr[2].x = p3->x;
    varr[2].y = p3->y;
    varr[2].z = 0.0f;
    varr[2].rhw = 2.0f;
    varr[2].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);


  };



  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, (void*)varr, sizeof
                                   (TVgVert2D));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//===================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPromtString(const VGVEC2 coord, const
  char *s)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, 1.0f, NULL);

  // draw rectangles
  //
  static VGVEC2 varr[7];

  int isLen = (int)strlen(s);
  float k = (float)isLen *7.0f + 22.0f;


  varr[0] = coord;

  varr[1].x = coord.x + 15;
  varr[1].y = coord.y - 15;

  varr[2].x = coord.x + 15;
  varr[2].y = coord.y - 33;

  varr[3].x = coord.x + 0+k; // 154
  varr[3].y = coord.y - 33;

  varr[4].x = coord.x + 0+k; // 154
  varr[4].y = coord.y - 15;

  varr[5].x = coord.x + 19;
  varr[5].y = coord.y - 15;

  varr[6] = varr[0];

  #pragma message("ks777: Заменить код...")
  assert(false);


  /*****************
  ID3DXLine* pline =   m_pcontext->GetInterfaceLine();
  if(!pline) return E_FAIL;


  hr |= pline->SetWidth( 1.0f );
  hr |= pline->Begin();

  hr |= pline->Draw( &varr[0], 7, D3DCOLOR_COLORVALUE( m_color.r, m_color.g, m_color.b, m_color.a ) );
  hr |= pline->End();


  // Draw promt string
  //

  const IDAPLIB_DrawValues* pdrawval = m_pcontext->GetInterfaceDrawValues();
  ID3DXFont* pfont =   pdrawval->GetInterfaceFontNormal();
  if(!pfont) return E_FAIL;

  RECT rect;
  SetRect( &rect, ksmtc::Round( coord.x + 20.0f ), ksmtc::Round( coord.y - 30.0f ), 1000, 1000 );

  hr |= pfont->DrawTextA( NULL, s, isLen, &rect, DT_LEFT,
  D3DCOLOR_COLORVALUE( m_color.r, m_color.g, m_color.b, m_color.a )  );


   **************************************/


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dRay(const VGVEC2 *orig, const VGVEC2
  *nrml)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  VGVEC2 normalzd =  *nrml;
  D3DXVec2Normalize(normalzd, normalzd);

  VGVEC2 varr[2];
  varr[0] =  *orig;
  varr[1] = normalzd;

  static const float FSCALEVAL = 3000.0f;
  varr[1].x *= FSCALEVAL;
  varr[1].y *= FSCALEVAL;


  varr[1] = varr[1] + varr[0];

  hr |= draw2dLine(&varr[0], &varr[1]);


  return hr;
};




//=========================================================================


} // end ns
} // end ns
} // end ns
} // end ns


#endif
#endif
// end file
