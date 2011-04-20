
#if ( defined(GB_D3D9) && defined(WIN32)  )
#if defined(GB_D3DX9)

#include <gb/graphics/visual_geometry/internal/vg_impl_d3d9.h>
#include <gb/str/formater.h>

//принудительно  подключаем gb::math
#include <gb/math/math.h>


namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {


//=========================================================================




//=========================================================================
HRESULT VGSaveRestoreDataD3D9::SaveDeviceData(IDirect3DDevice9 *pdevice, 
				const VGCOLOR* newColor, float pointSize, IDirect3DTexture9 *newTxtr)
{
  HRESULT hr = S_OK;
  D3DMATERIAL9 newMat;

  assert(pdevice);

  hr |= pdevice->GetFVF(&fvf);
  hr |= pdevice->GetMaterial(&material);
  if (newColor)
  {
    newMat.Diffuse.r = newColor->r;
    newMat.Diffuse.g = newColor->g;
    newMat.Diffuse.b = newColor->b;
    newMat.Diffuse.a = newColor->a;

    newMat.Emissive.r = newColor->r;
    newMat.Emissive.g = newColor->g;
    newMat.Emissive.b = newColor->b;
    newMat.Emissive.a = newColor->a;

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


//==================================================================
HRESULT VGDrawValuesImpl_D3D9::checkFontInterfaces()const
{
	HRESULT hr =0;
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



//=========================================================
void VGDrawValuesImpl_D3D9::drawS(const char *s)const
{
  HRESULT hr = 0;

  hr |= this->drawStrEx(  s);

  #pragma message("NEED CHECK  CODE"  __FILE__)

   if FAILED(hr)
   {

	   throw std::runtime_error("Operation failed !");
   }
};

//=========================================================================
void VGDrawValuesImpl_D3D9::drawPoint(const float* vec2_pointcoord, const char* promt) const 
{
	VGVEC2 pos(vec2_pointcoord);
	drawPoint(gb::math::scalar::round(pos.x) , gb::math::scalar::round(pos.y) , promt);
}

//============================================================
void VGDrawValuesImpl_D3D9::drawF(const char *_Format, ...)const
{

  static char ss[8192];
  ss[0] = 0;

  va_list ap;
  va_start(ap, _Format);
  vsprintf(ss, _Format, ap);
  va_end(ap);
  drawS(ss);


  #pragma message("NEED CHECK  CODE"  __FILE__)
 
};

void VGDrawValuesImpl_D3D9::drawBool(bool val, const char *promt)const
{
 
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

 drawS(buf);
  
};

//=====================================
void VGDrawValuesImpl_D3D9::drawInt(int val, const char *promt) const
{
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
  drawS(buf);
}

//=====================================
void VGDrawValuesImpl_D3D9::drawFloat(float val, const char *promt)const
{
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
 drawS(buf);
}

//==================================================================
void VGDrawValuesImpl_D3D9::drawIntArray(const int *p, int num, const char* promt) const
{
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

  drawS(ss);
}

//==================================================================
void VGDrawValuesImpl_D3D9::drawFloatArray(const float *p, int num, const char *promt)const
{
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

  drawS(ss);
}

#pragma message("ks777:  Перенести в общую"  __FILE__ )

//==========================================================
static void __StrFromFloatForDrawVec(char *buf, const FLOAT f)
{
  _gcvt((double)f, 10, buf);
};

//==================================================================
void VGDrawValuesImpl_D3D9::drawVec2(const float* vect2, const char *promt)const
{
  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

  VGVEC2 v(vect2);

  //str += "x= ";
  __StrFromFloatForDrawVec(sdigit, v.x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;

drawS(str.c_str());

}

//==================================================================
void VGDrawValuesImpl_D3D9::drawVec3(const float* vect3, const char *promt)const
{
  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

    VGVEC3 v(vect3);


  __StrFromFloatForDrawVec(sdigit, v.x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;

  drawS(str.c_str());
 
}

//=====================================================================
void VGDrawValuesImpl_D3D9::drawVec4(const float* vect4, const char *promt)const
{
	static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

  VGVEC4 v(vect4);

  __StrFromFloatForDrawVec(sdigit, v.x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v.z);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v.w);
  str += sdigit;


    drawS(str.c_str());

}


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
void VGDrawValuesImpl_D3D9::drawMatrix4x4(const float* matrix4x4, const char *promt)  const
{
 
  static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
    str += "\n";
  };

  const VGMAT4 mat (matrix4x4);
  const VGMAT4* m = &mat;

 
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

  drawS(str.c_str());
 
}


//=====================================================================
/*
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoint (const float* pos, float pointSize) const 
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




//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dPoints(const float* vec3Array_coord, int num,  float pointSize )const
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
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, num, (void*)vec3Array_coord, sizeof(D3DVECTOR) );

  // restore
  //
  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=============================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLine(const float* vec3_p1, const float* vec3_p2 )const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  VGVEC3 varr[2];


  // prepare
  //
  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, 1);

  //*( ( D3DVECTOR* ) ( &varr[0] ) ) = *( ( D3DVECTOR* ) ( &p1 ) );
  //*( ( D3DVECTOR* ) ( &varr[1] ) ) = *( ( D3DVECTOR* ) ( &p2 ) );

  varr[0] =  vec3_p1;
  varr[1] =  vec3_p2;


 

  // draw
  //
  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(D3DVECTOR) );

  // restore
  //
  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLine(
					float x1, float y1, float z1,
					float x2, float y2, float z2 ) const
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

  hr |= draw3dLine(varr[0], varr[1] );

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dLines(const float* vec3_coord, int num)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);


  // D3DPT_LINELIST
  // D3DPT_LINESTRIP << было 

#pragma message("ПРОВЕРИТЬ КОД " __FILE__)
 
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, num - 1, (void*)vec3_coord, sizeof(float)*3 );


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dAABB(const float* vec3_min, 
											   const float* vec3_max ) const
{
  HRESULT hr = S_OK;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  const int NSIZEOF = sizeof(float*);

  static VGVEC3 vArrLine[8];
  ZeroMemory(vArrLine, sizeof(VGVEC3) *8);

  static const int nCount_quad_vert = 4;


  // vectors
  VGVEC3 min (vec3_min);
  VGVEC3 max (vec3_max);

  ///  first quad ///
  /// 0
  vArrLine[0].x = min.x;
  vArrLine[0].y = min.y;
  vArrLine[0].z = min.z;


  /// 1
  vArrLine[1].x = max.x;
  vArrLine[1].y = min.y;
  vArrLine[1].z = min.z;


  /// 2
  vArrLine[2].x = max.x;
  vArrLine[2].y = max.y;
  vArrLine[2].z = min.z;


  /// 3
  vArrLine[3].x = min.x;
  vArrLine[3].y = max.y;
  vArrLine[3].z = min.z;


  /// 4
  vArrLine[4].x = min.x;
  vArrLine[4].y = min.y;
  vArrLine[4].z = min.z;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*)
                                   vArrLine, NSIZEOF);



  ///  second quad ///
  /// 0
  vArrLine[0].x = max.x;
  vArrLine[0].y = max.y;
  vArrLine[0].z = max.z;

  /// 1
  vArrLine[1].x = max.x;
  vArrLine[1].y = min.y;
  vArrLine[1].z = max.z;


  // 2
  vArrLine[2].x = min.x;
  vArrLine[2].y = min.y;
  vArrLine[2].z = max.z;


  // 3
  vArrLine[3].x = min.x;
  vArrLine[3].y = max.y;
  vArrLine[3].z = max.z;


  // 4
  vArrLine[4].x = max.x;
  vArrLine[4].y = max.y;
  vArrLine[4].z = max.z;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_quad_vert, (void*)
                                   vArrLine, NSIZEOF);



  //////////    draw other borders ///////////////////
  if (1)
  {

    static const int nCount_border = 1;


    /// border 0    ///
    vArrLine[0].x = max.x;
    vArrLine[0].y = max.y;
    vArrLine[0].z = max.z;

    vArrLine[1].x = max.x;
    vArrLine[1].y = max.y;
    vArrLine[1].z = min.z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);



    /// border 1    ///
    vArrLine[0].x = min.x;
    vArrLine[0].y = max.y;
    vArrLine[0].z = max.z;

    vArrLine[1].x = min.x;
    vArrLine[1].y = max.y;
    vArrLine[1].z = min.z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);


    /// border 2   ///
    vArrLine[0].x = max.x;
    vArrLine[0].y = min.y;
    vArrLine[0].z = max.z;

    vArrLine[1].x = max.x;
    vArrLine[1].y = min.y;
    vArrLine[1].z = min.z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);


    /// border 3    ///
    vArrLine[0].x = min.x;
    vArrLine[0].y = min.y;
    vArrLine[0].z = min.z;

    vArrLine[1].x = min.x;
    vArrLine[1].y = min.y;
    vArrLine[1].z = max.z;

    hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nCount_border, (void*)
                                     vArrLine, NSIZEOF);

  };


  /// end ///


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};


//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(const float* vec3_orig, 
											  const float* vec3_normal )const
{
  HRESULT hr = S_OK;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  gb::math::base::vec3_s varr[4];

  gb::math::base::vec3_s  orig (vec3_orig);
  //VGVEC3 orig (vec3_orig);


  varr[0].x = orig.x;
  varr[0].y = orig.y;
  varr[0].z = orig.z;

  static const float VG_MAX_INFINITY_VALUE = 3.4E30f;
  gb::math::base::vec3_s vt = orig; orig *= VG_MAX_INFINITY_VALUE; //  D3DXVec3Scale(vt,  *orig, VG_MAX_INFINITY_VALUE);
    varr[1] = orig + vt; //  D3DXVec3Add(varr[1],  *orig, vt);


  const UINT nNumValue = 1; // num-1;

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumValue, (void*)varr, sizeof(gb::math::base::vec3_s) );

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(
					float orgX, float orgY, float  orgZ, 
					float nrmlX, float nrmlY, float nrmlZ )const
{
  HRESULT hr = 0;
  assert(m_pdevice);
  VGVEC3 orig (orgX, orgY, orgZ);
  VGVEC3 nrml (nrmlX, nrmlY, nrmlZ);

  hr |= draw3dRay(orig, nrml);
  return hr;
};

//=====================================================================
#ifdef GB_MATH
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dRay(const gb::math::geom3d::Ray *ray )const
{
  HRESULT hr = 0;
  assert(m_pdevice);
  float* orig = float*(ray->orig.x, ray->orig.y, ray->orig.z);
  float* nrml = float*(ray->dir.x, ray->dir.y, ray->dir.z);

  hr |= draw3dRay(&orig, &nrml );

  return hr;
};
#endif


//=====================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dTraingle(
				const float* vec3_v1, const float* vec3_v2, const float* vec3_v3 )const
{
  HRESULT hr = 0;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);

  static gb::math::base::vec3_s varr[4];
  varr[0] =  vec3_v1;
  varr[1] =  vec3_v2;
  varr[2] =  vec3_v3;
  varr[3] =  vec3_v1;

  static const UINT nNumValue = 3;

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumValue, (void*)varr,
                                   sizeof(float*));


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=====================================================================
#ifdef GB_MATH
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dTraingle(
			const gb::math::geom3d::Triangle *tri )const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  float* varr[3];

  varr[0].x = tri->p1.x;
  varr[0].y = tri->p1.y;
  varr[0].z = tri->p1.z;

  varr[1].x = tri->p2.x;
  varr[1].y = tri->p2.y;
  varr[1].z = tri->p2.z;

  varr[2].x = tri->p3.x;
  varr[2].y = tri->p3.y;
  varr[2].z = tri->p3.z;

  hr |= draw3dTraingle(&varr[0], &varr[1], &varr[2] );


  return hr;
};
#endif

//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dArrow(
					const float* vec3_src, 
					const float* vec3_dest )const
{
  HRESULT hr = 0;

  #pragma message ("ks777: НЕ РАБОТАЕТ КОРРЕКТНО Draw3dArrow "  __FILE__ )
  return E_FAIL;


  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);

  //////// make matrix   ////////////




  // make scaling
  D3DXMATRIX  msc;
  {
    D3DXMatrixIdentity(&msc);

	gb::math::base::vec3_s vsub = gb::math::base::vec3_s(vec3_dest) - gb::math::base::vec3_s(vec3_src);
    float fdistance = vsub.length(); // D3DXVec3Length(vsub);

    static bool stb_inverse = false;
    if (stb_inverse)
    {
      fdistance =  - fdistance;
    }

    D3DXMatrixScaling(&msc, fdistance, fdistance, fdistance);

  };



  // make rotation
  D3DXMATRIX  mrot;
  {
    D3DXMatrixIdentity(&mrot);
    //mrot.setIdentity();

    gb::math::base::vec3_s vNormal  = gb::math::base::vec3_s(vec3_dest) - gb::math::base::vec3_s(vec3_src);
     vNormal.normalize(); // D3DXVec3Normalize(vNormal, vNormal);
    //vNormal = vNormal;
    const gb::math::base::vec3_s IDENTITY_NORMAL( -0.0f,  -0.0f, 1.0f  );

    gb::math::base::vec3_s vCross = vNormal.cross(IDENTITY_NORMAL); // D3DXVec3Cross(vCross, vNormal, IDENTITY_NORMAL);
    vCross.normalize();// D3DXVec3Normalize(vCross, vCross);
    float angle =  - acos(  vCross.dot(vNormal) /* D3DXVec3Dot(vCross, vNormal) */    );


    D3DXMatrixRotationAxis(&mrot, vCross, angle);

  };


  // make translation 
  D3DXMATRIX  mtr;
  {
    D3DXMatrixIdentity(&mtr);
	gb::math::base::vec3_s vTransl(vec3_src);
    D3DXMatrixTranslation( &mtr, vTransl.x, vTransl.y, vTransl.z );
  }


  D3DXMATRIX  matrix; // final matrix
  matrix = msc * mrot * mtr;



  //if (mTransf)
  //{
  //  matrix = matrix **mTransf;

  //}
  //else
  //{


  //} ;

  hr |= m_pdevice->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&matrix._11 );

  assert(false && "need check code");
  // надо поменять !!!
  return E_FAIL;
  //hr |= m_pcontext->DrawPrimitiveArrow();


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);

  return hr;
};

//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dAxies(const float* vec3_coord, float  axiesLen) const
{
  HRESULT hr = 0;
  VGCOLOR oldcolor = m_color;

  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);


  gb::math::base::vec3_s varr[2];
  D3DMATERIAL9 material;

  hr |= m_pdevice->SetFVF(VG_FVF_3DLINES);
  hr |= m_pdevice->GetMaterial(&material);


  // x
  varr[0] =  vec3_coord;
  varr[1] =  vec3_coord;
  varr[1].x += axiesLen;
  material.Emissive.r = 1.0f;
  material.Emissive.g = 0.0f;
  material.Emissive.b = 0.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(float*) );



  // y
  varr[0] =  vec3_coord;
  varr[1] =  vec3_coord;
  varr[1].y += axiesLen;
  material.Emissive.r = 0.0f;
  material.Emissive.g = 1.0f;
  material.Emissive.b = 0.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (float*));



  // z
  varr[0] =  vec3_coord;
  varr[1] =  vec3_coord;
  varr[1].z += axiesLen;
  material.Emissive.r = 0.0f;
  material.Emissive.g = 0.0f;
  material.Emissive.b = 1.0f;
  material.Emissive.a = 1.0f;
  hr |= m_pdevice->SetMaterial(&material);
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof
                                   (float*));



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
   setColor( oldcolor.r, oldcolor.g, oldcolor.b, oldcolor.a );
  return hr;
};


//=========================================================================
HRESULT VGDraw3DGeometry_Impl_D3D9::draw3dSolidSphere(const float* vec3_center,  float radius)const
{
  HRESULT hr = 0;
  assert(false && "ПРОВЕРИТЬ КОД !!!! ");
  assert(m_pdevice);

  D3DXMATRIX  m;
  D3DXMatrixIdentity(&m);

  D3DXMATRIX  msc;
  D3DXMatrixScaling(&msc, radius, radius, radius);

  D3DXMATRIX  mtr;
  VGVEC3 vtr(vec3_center);
  D3DXMatrixTranslation( &mtr, vtr.x, vtr.y, vtr.z );


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
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPoint(float x, float y, float pointSize)const
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

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, (void*) &vert,  sizeof (TVgVert2D) );



  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPoints(
	const float* vec2_arrayCoord, int num, float pointSize) const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  static const int NARRLEN = 256;
  static TVgVert2D varr[NARRLEN];
  for (int c = 0; (c < num) && (c < NARRLEN); c++)
  {
	  const gb::math::base::vec3_s* pv = (gb::math::base::vec3_s*)vec2_arrayCoord;
    varr[c].x = (pv + c)->x;
    varr[c].y = (pv + c)->y;
    varr[c].z = 0.0f;
    varr[c].rhw = 2.0;
    varr[c].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a);

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

  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, numpoints, (void*)varr, sizeof(TVgVert2D));

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dLine( const float* vec2_p1, const float* vec2_p2 )const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  static TVgVert2D varr[2];

  gb::math::base::vec2_s v1(vec2_p1);
  gb::math::base::vec2_s v2(vec2_p2);

  varr[0].x = v1.x;
  varr[0].y = v1.y;
  varr[0].z = 0.0f;
  varr[0].rhw = 2.0f;
  varr[0].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a);

  varr[1].x = v2.x;
  varr[1].y = v2.y;
  varr[1].z = 0.0f;
  varr[1].rhw = 2.0f;
  varr[1].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a);


  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  // D3DPT_LINELIST              = 2,
  // D3DPT_LINESTRIP
  hr |= m_pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(TVgVert2D)  );

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dLines(const float* vec2_arrayCoord, int num)const
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
	  const VGVEC2* pv = (VGVEC2*)vec2_arrayCoord;
    varr[c].x = (pv + c)->x;
    varr[c].y = (pv + c)->y;
    varr[c].z = 0.0f;
    varr[c].rhw = 2.0f;
    varr[c].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a);

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
  hr |= m_pdevice->DrawPrimitiveUP(
	  D3DPT_LINESTRIP, numpoints, 
	  (void*)varr, sizeof(TVgVert2D)   
	  );

  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//=====================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dRect(const D3DRECT& rect)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  VGVEC2 varr[5];

  varr[0].x = (float)rect.x1;
  varr[0].y = (float)rect.y1;

  varr[1].x = (float)rect.x2;
  varr[1].y = (float)rect.y1;

  varr[2].x = (float)rect.x2; // + rect.x2;
  varr[2].y = (float)rect.y2; // + rect.y2;

  varr[3].x = (float)rect.x1;
  varr[3].y = (float)rect.y2;

  varr[4] = varr[0];

  hr |= draw2dLines(varr[0], 5);


  return hr;
};

//=========================================================
#ifdef GB_MATH
 virtual HRESULT draw2dSolidRect(const gb::math::geom2d::Rect& rect) const 
 {
	 return draw2dSolidRect( 
		 gb::math::scalar::round(rect.x1), 
		 gb::math::scalar::round(rect.y1), 
		 gb::math::scalar::round(rect.x2),  
		 gb::math::scalar::round(rect.y2) );
 };
#endif

//============================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dSolidRect(int x1, int y1, int x2, int y2)const 
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

//=========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dCircle(const float* vec2_pos, float radius) const
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
	const VGVEC2 pos(vec2_pos);
    valfact = (FLOAT)c / SEGM;
    varr[c].x = sin((D3DX_PI *2.0f) *valfact) *radius;
    varr[c].y = cos((D3DX_PI *2.0f) *valfact) *radius;

    varr[c].x += pos.x;
    varr[c].y += pos.y;

  };

  varr[SEGM] = varr[0];
  varr[SEGM + 1] = varr[0];


  //D3DCOLOR clr = D3DCOLOR_COLORVALUE( color->r, color->g, color->b, color->a );

  //hr |= g_pILine->SetWidth( fLineWidth );
  //hr |= g_pILine->Begin();

  DWORD num = (DWORD)SEGM + 1;
  //hr |= g_pILine->Draw( &varr[0], num, clr );
  hr |= draw2dLines(varr[0], num);

  //hr |= g_pILine->End();


  return hr;
};

//===================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dAxies(const float* vec2_coord) const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  //gb::color::Color4f 
	  VGCOLOR oldcolor = m_color;


	  gb::math::base::vec2_s varr[2];
  const float _MAX_VALUE_ = 2500.0f;

  const gb::math::base::vec2_s coord(vec2_coord);

  // x
  setColorRed();
  varr[0] = gb::math::base::vec2_s(0.0f, coord.y);
  varr[1] = gb::math::base::vec2_s(_MAX_VALUE_, coord.y);
  hr |=   draw2dLine(varr[0], varr[1]);


  // y
  setColorGreen();
  varr[0] = gb::math::base::vec2_s(coord.x, 0.0f);
  varr[1] = gb::math::base::vec2_s(coord.x, _MAX_VALUE_);
 hr |= draw2dLine(varr[0], varr[1]);


 setColor(oldcolor.r, oldcolor.g, oldcolor.b, oldcolor.a);
  return hr;
};

//========================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dTriangle(
			const float* vec2_p1, const float* vec2_p2,  const float* vec2_p3)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  gb::math::base::vec3_s varr[4];
  varr[0] =  vec2_p1;
  varr[1] =  vec2_p2;
  varr[2] =  vec2_p3;
  varr[3] =  vec2_p1;

  return draw2dLines(varr[0], 4);
};

//====================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dSolidTriangle(
		const float* vec2_p1, const float* vec2_p2, const float* vec2_p3)const
{
  HRESULT hr = 0;
  assert(m_pdevice);


  static TVgVert2D varr[3];


  {
	const gb::math::base::vec2_s p1(vec2_p1);
    varr[0].x = p1.x;
    varr[0].y = p1.y;
    varr[0].z = 0.0f;
    varr[0].rhw = 2.0f;
    varr[0].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

	const gb::math::base::vec2_s p2(vec2_p2);
    varr[1].x = p2.x;
    varr[1].y = p2.y;
    varr[1].z = 0.0f;
    varr[1].rhw = 2.0f;
    varr[1].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);

	const gb::math::base::vec2_s p3(vec2_p3);
    varr[2].x = p3.x;
    varr[2].y = p3.y;
    varr[2].z = 0.0f;
    varr[2].rhw = 2.0f;
    varr[2].color = D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b,
                                        m_color.a);


  };



  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color);
  hr |= m_pdevice->SetFVF(VG_FVF_2DLINES);
  hr |= m_pdevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
  hr |= m_pdevice->SetRenderState(D3DRS_ZENABLE, 0);

  hr |= m_pdevice->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST, 1, (void*)varr, sizeof (TVgVert2D) );


  hr |= m_DeviceData.RestoreDeviceData(m_pdevice);
  return hr;
};

//===================================================================
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dPromtString(const float* vec2_coord, const char *s)const
{
  HRESULT hr = S_OK;
  assert(m_pdevice);

  hr |= m_DeviceData.SaveDeviceData(m_pdevice, &m_color, 1.0f, NULL);

  // draw rectangles
  //
  static gb::math::base::vec2_s varr[7];

  int isLen = (int)strlen(s);
  float k = (float)isLen *7.0f + 22.0f;

	const gb::math::base::vec2_s coord( vec2_coord );
  varr[0] = coord;

  varr[1].x = coord.x + 15;
  varr[1].y = coord.y - 15;

  varr[2].x = coord.x + 15;
  varr[2].y = coord.y - 33;

  varr[3].x = coord.x + 0 + k; // 154
  varr[3].y = coord.y - 33;

  varr[4].x = coord.x + 0 + k; // 154
  varr[4].y = coord.y - 15;

  varr[5].x = coord.x + 19;
  varr[5].y = coord.y - 15;

  varr[6] = varr[0];

  #pragma message("ks777: Заменить код...")
  assert(false && "ks777: Заменить код...");


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
HRESULT VGDraw2DGeometry_Impl_D3D9::draw2dRay(const float* vec2_orig, const float* vec2_normal)const
{
  HRESULT hr = 0;
  assert(m_pdevice);

  gb::math::base::vec2_s normalzd =  vec2_normal;
  normalzd.normalize(); // D3DXVec2Normalize(normalzd, normalzd);

  gb::math::base::vec2_s varr[2];
  varr[0] =  vec2_orig;
  varr[1] = normalzd;

  static const float FSCALEVAL = 3000.0f;
  varr[1].x *= FSCALEVAL;
  varr[1].y *= FSCALEVAL;


  varr[1] = varr[1] + varr[0];

  hr |= draw2dLine(varr[0], varr[1]);


  return hr;
};




//=========================================================================


} // end namespace
} // end namespace
} // end namespace
} // end namespace


#endif
#endif
// end file
