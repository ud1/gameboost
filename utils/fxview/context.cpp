 
#include <Windows.h>

#include "context.h"

using namespace gb::fmath;
using namespace gb::fmath::geom3d;
using namespace gb::fmath::proj;


//============================================================= 
int  Context::setMatrices(const mat44 *mWorld, const mat44 *mView, const mat44 *mProj) 
{
  int  hr = 0;

  if (mWorld)
  {
    m_mWorld =  *mWorld;
    m_BoolChangedMatr.bWorldChange = true;
    m_bMouseCoordCameraUnproject_change = true;


    m_matr.mWorldViewProjection.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverseTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mWorldTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldInverseTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldView.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewInverseTranspone.bChangeFlag = TRUE_VAL;


  } // if(mWorld)

  if (mView)
  {
    m_mView =  *mView;
    m_BoolChangedMatr.bViewChange = true;
    m_bMouseCoordCameraUnproject_change = true;

    m_matr.mViewProjection.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionInverseTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mViewTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mViewInverse.bChangeFlag = TRUE_VAL;
    m_matr.mViewInverseTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mWorldViewProjection.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverseTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mWorldView.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewInverseTranspone.bChangeFlag = TRUE_VAL;

  } // if(mView)


  if (mProj)
  {
    m_bChangeProjectionData = true;
    m_mProj =  *mProj;
    m_BoolChangedMatr.bProjChange = true;
    m_bMouseCoordCameraUnproject_change = true;

    m_matr.mViewProjection.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionInverseTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mViewProjectionTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mProjectionTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mProjectionInverseTranspone.bChangeFlag = TRUE_VAL;

    m_matr.mWorldViewProjection.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionTranspone.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverse.bChangeFlag = TRUE_VAL;
    m_matr.mWorldViewProjectionInverseTranspone.bChangeFlag = TRUE_VAL;


  } // if(mProj)


  // set to device


  //if (pdvc)
  //{

  //  if (mWorld)
  //  {
  //    hr |= pdvc->SetTransform(D3DTS_WORLD, &m_mWorld);
  //  };

  //  if (mView)
  //  {
  //    hr |= pdvc->SetTransform(D3DTS_VIEW, &m_mView);
  //  };

  //  if (mProj)
  //  {
  //    hr |= pdvc->SetTransform(D3DTS_PROJECTION, &m_mProj);
  //  };
 
  //}
  //else
  //{
  //  MONPRINT("device is NULL");
  //  hr |= S_FALSE;

  //};



  return hr;
};

//====================================================================  
const mat44 *Context::GetMatrixViewProjection()const
{
  if (m_matr.mViewProjection .bChangeFlag)
  {
    //MMUL(&m_matr.mViewProjection.matrix, &m_mView, &m_mProj);
	m_matr.mViewProjection.matrix = m_mView * m_mProj;

    m_matr.mViewProjection .bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewProjection.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewProjectionInverse()const
{
  if (m_matr.mViewProjectionInverse.bChangeFlag)
  {
    //MMUL(&m_temp, &m_mView, &m_mProj);
	m_temp = m_mView * m_mProj;

    //D3DXMatrixInverse(&m_matr.mViewProjectionInverse.matrix, NULL, &m_temp);
	m_matr.mViewProjectionInverse.matrix = m_temp.inverted();

    m_matr.mViewProjectionInverse.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewProjectionInverse.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewProjectionInverseTranspone()const
{
  if (m_matr.mViewProjectionInverseTranspone.bChangeFlag)
  {
   // MMUL(&m_temp, &m_mView, &m_mProj);
	 m_temp  = m_mView * m_mProj;

   // D3DXMatrixInverse(&m_temp2, NULL, &m_temp);
	m_temp2.invert();

    //D3DXMatrixTranspose(&m_matr.mViewProjectionInverseTranspone.matrix, &m_temp2);
	 m_matr.mViewProjectionInverseTranspone.matrix=m_temp2.transponed();


    m_matr.mViewProjectionInverseTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewProjectionInverseTranspone.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewProjectionTranspone()const
{
  if (m_matr.mViewProjectionTranspone.bChangeFlag)
  {
   // MMUL(&m_temp, &m_mView, &m_mProj);
	m_temp = m_mView * m_mProj;
    //D3DXMatrixTranspose(&m_matr.mViewProjectionTranspone.matrix, &m_temp);


    m_matr.mViewProjectionTranspone.bChangeFlag = TRUE_VAL;
  }

  return  &m_matr.mViewProjectionTranspone.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewTranspone()const
{
  if (m_matr.mViewTranspone.bChangeFlag)
  {
   // D3DXMatrixTranspose(&m_matr.mViewTranspone.matrix, &m_mView);
   m_matr.mViewTranspone.matrix = m_mView.transponed();

    m_matr.mViewTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewTranspone.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewInverse()const
{
  if (m_matr.mViewInverse.bChangeFlag)
  {
   // D3DXMatrixInverse(&m_matr.mViewInverse.matrix, NULL, &m_mView);
	m_matr.mViewInverse.matrix = m_mView.inverted();

    m_matr.mViewInverse.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewInverse.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixViewInverseTranspone()const
{
  if (m_matr.mViewInverseTranspone.bChangeFlag)
  {
    //D3DXMatrixInverse(&m_temp, NULL, &m_mView);
	 m_temp = m_mView.inverted();
   // D3DXMatrixTranspose(&m_matr.mViewInverseTranspone.matrix, &m_temp);
   m_matr.mViewInverseTranspone.matrix = m_temp.transponed();

    m_matr.mViewInverseTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mViewInverseTranspone.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixProjectionInverse()const
{
  if (m_matr.mProjectionInverse.bChangeFlag)
  {
    //D3DXMatrixInverse(&m_matr.mProjectionInverse.matrix, NULL, &m_mProj);
	m_matr.mProjectionInverse.matrix = m_mProj.inverted();

    m_matr.mProjectionInverse.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mProjectionInverse.matrix;
};

//==================================================================== 
const mat44 *Context::GetMatrixProjectionTranspone()const
{
  if (m_matr.mProjectionTranspone.bChangeFlag)
  {
   // D3DXMatrixTranspose(&m_matr.mProjectionTranspone.matrix, &m_mProj);
	 m_matr.mProjectionTranspone.matrix = m_mProj.transponed();

    m_matr.mProjectionTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mProjectionTranspone.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixProjectionInverseTranspone()const
{
  if (m_matr.mProjectionInverseTranspone.bChangeFlag)
  {
   // D3DXMatrixInverse(&m_temp, NULL, &m_mProj);
	  m_temp = m_mProj.inverted();
   // D3DXMatrixTranspose(&m_matr.mProjectionInverseTranspone.matrix, &m_temp);
	 m_matr.mProjectionInverseTranspone = m_temp.transponed();

    m_matr.mProjectionInverseTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mProjectionInverseTranspone.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixWorldViewProjection()const
{
  if (m_matr.mWorldViewProjection.bChangeFlag)
  {
   // MMUL(&m_temp, &m_mView, &m_mProj);
   m_temp = m_mView * m_mProj;

   // MMUL(&m_matr.mWorldViewProjection.matrix, &m_mWorld, &m_temp);
   m_matr.mWorldViewProjection.matrix = m_mWorld * m_temp;

    m_matr.mWorldViewProjection.bChangeFlag = TRUE_VAL;
  }

  return  &m_matr.mWorldViewProjection.matrix;
};

//====================================================================  
const mat44 *Context::GetMatrixWorldViewProjectionTranspone()const
{
  if (m_matr.mWorldViewProjectionTranspone.bChangeFlag)
  {
    //MMUL(&m_temp, &m_mView, &m_mProj);
		  m_temp = m_mView * m_mProj;
    //MMUL(&m_temp2, &m_mWorld, &m_temp);
		  m_temp2 = m_mWorld * m_temp;

    D3DXMatrixTranspose(&m_matr.mWorldViewProjectionTranspone.matrix, &m_temp2);
	 m_matr.mWorldViewProjectionTranspone.matrix = m_temp2.transponed();

    m_matr.mWorldViewProjectionTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldViewProjectionTranspone.matrix;
};

//====================================================================  
const mat44 *Context::GetMatrixWorldViewProjectionInverse()const
{
  if (m_matr.mWorldViewProjectionInverse.bChangeFlag)
  {
    //MMUL(&m_temp, &m_mView, &m_mProj);
		  m_temp =m_mView * m_mProj;

    //MMUL(&m_temp2, &m_mWorld, &m_temp);
		  m_temp2 =m_mWorld * m_temp;

    D3DXMatrixInverse(&m_matr.mWorldViewProjectionInverse.matrix, NULL, &m_temp2);
	 m_matr.mWorldViewProjectionInverse.matrix = m_temp2.inverted();

    m_matr.mWorldViewProjectionInverse.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldViewProjectionInverse.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixWorldViewProjectionInverseTranspone()const
{
  mat44 temp;
  if (m_matr.mWorldViewProjectionInverseTranspone.bChangeFlag)
  {
    //MMUL(&m_temp, &m_mView, &m_mProj);
		  m_temp =m_mView * m_mProj;
    //MMUL(&m_temp2, &m_mWorld, &m_temp);
		 m_temp2 =m_mWorld * m_temp;


   // D3DXMatrixInverse(&temp, NULL, &m_temp2);
	   temp = m_temp2.inverted();

    D3DXMatrixTranspose(&m_matr.mWorldViewProjectionInverseTranspone.matrix, &temp);
	  m_matr.mWorldViewProjectionInverseTranspone.matrix=temp.transponed();

    m_matr.mWorldViewProjectionInverseTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldViewProjectionInverseTranspone.matrix;
};

//====================================================================  
const mat44 *Context::GetMatrixWorldTranspone()const
{
  if (m_matr.mWorldTranspone.bChangeFlag)
  {
    //D3DXMatrixTranspose(&m_matr.mWorldTranspone.matrix, &m_mWorld);
	m_matr.mWorldTranspone.matrix=m_mWorld.transponed();

    m_matr.mWorldTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldTranspone.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixWorldInverse()const
{
  if (m_matr.mWorldInverse.bChangeFlag)
  {
   // D3DXMatrixInverse(&m_matr.mWorldInverse.matrix, NULL, &m_mWorld);
		m_matr.mWorldInverse.matrix = m_mWorld.inverted();

    m_matr.mWorldInverse.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldInverse.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixWorldInverseTranspone()const
{
  if (m_matr.mWorldInverseTranspone.bChangeFlag)
  {
   // D3DXMatrixInverse(&m_temp, NULL, &m_mWorld);
	 m_temp = m_mWorld.inverted();

    //D3DXMatrixTranspose(&m_matr.mWorldInverseTranspone.matrix, &m_temp);
	m_matr.mWorldInverseTranspone.matrix=m_temp.transponed();

    m_matr.mWorldInverseTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldInverseTranspone.matrix;
};

//====================================================================   
const mat44 *Context::GetMatrixWorldView()const
{
  if (m_matr.mWorldView .bChangeFlag)
  {
    //MMUL(&m_matr.mWorldView.matrix, &m_mWorld, &m_mView);
    m_matr.mWorldView.matrix * m_mWorld * m_mView;

    m_matr.mWorldView.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldView.matrix;
};

//====================================================================  
const mat44 *Context::GetMatrixWorldViewTranspone()const
{
  if (m_matr.mWorldViewTranspone.bChangeFlag)
  {
    //MMUL(&m_temp, &m_mWorld, &m_mView);
	   m_temp = m_mWorld * m_mView;

    //D3DXMatrixTranspose(&m_matr.mWorldViewTranspone.matrix, &m_temp);
	m_matr.mWorldViewTranspone.matrix=m_temp.transponed();

    m_matr.mWorldViewTranspone.bChangeFlag = FALSE_VAL;
  }

  return  &m_matr.mWorldViewTranspone.matrix;
};

#error ДОДЕЛАТЬ ДАЛЬШЕ !!!!


//====================================================================  
const mat44 *Context::GetMatrixWorldViewInverse()const
{
  if (m_matr.mWorldViewInverse.bChangeFlag)
  {
    MMUL(&m_temp, &m_mWorld, &m_mView);
    D3DXMatrixInverse(&m_matr.mWorldViewInverse.matrix, NULL, &m_temp);
    m_matr.mWorldViewInverse.bChangeFlag = FALSE_VAL;
  };
  return  &m_matr.mWorldViewInverse.matrix;
};

//====================================================================  
const mat44 *Context::GetMatrixWorldViewInverseTranspone()const
{
  if (m_matr.mWorldViewInverseTranspone.bChangeFlag)
  {
    MMUL(&m_temp, &m_mWorld, &m_mView);
    D3DXMatrixInverse(&m_temp2, NULL, &m_temp);
    D3DXMatrixTranspose(&m_matr.mWorldViewInverseTranspone.matrix, &m_temp2);
    m_matr.mWorldViewInverseTranspone.bChangeFlag = FALSE_VAL;
  };
  return  &m_matr.mWorldViewInverseTranspone.matrix;
};

//==================================================================== 
void Context::__checkViewVectors()const
{
  if (m_matr.mViewInverse.bChangeFlag)
  {
    GetMatrixViewInverse();
    #pragma message ("ПРОВЕРИТЬ ПОЛУЧЕНИЕ ВЕКТОРОВ  ВИДА ИЗ ИНВЕРСНОЙ ВИДОВОЙ МАТРИЦЫ ")
    m_VewPos = *((vec3*) &m_matr.mViewInverse.matrix._41);
    m_ViewDir = *((vec3*) &m_matr.mViewInverse.matrix._31);
    m_ViewUp = *((vec3*) &m_matr.mViewInverse.matrix._21);
  };
};

//==================================================================== 
const vec4 *Context::GetVector4ViewPos()const
{
  __checkViewVectors();
  m_vec4Temp.x = m_VewPos.x;
  m_vec4Temp.y = m_VewPos.y;
  m_vec4Temp.z = m_VewPos.z;
  m_vec4Temp.w = 1.0f;
  return  &m_vec4Temp;
};

//====================================================================  
const vec4 *Context::GetVector4ViewDir()const
{
  __checkViewVectors();
  m_vec4Temp.x = m_ViewDir.x;
  m_vec4Temp.y = m_ViewDir.y;
  m_vec4Temp.z = m_ViewDir.z;
  m_vec4Temp.w = 1.0f;
  return  &m_vec4Temp;
};

//==================================================================== 
const vec4 *Context::GetVector4ViewUp()const
{
  __checkViewVectors();
  m_vec4Temp.x = m_ViewUp.x;
  m_vec4Temp.y = m_ViewUp.y;
  m_vec4Temp.z = m_ViewUp.z;
  m_vec4Temp.w = 1.0f;
  return  &m_vec4Temp;
};

//====================================================================  
const vec3 *Context::GetVector3ViewSideUp()const
{
  #pragma message ("ПРОВЕРИТЬ ПОЛУЧЕНИЕ БОКОВОГО ВЕКТОРА ВИДА")
  D3DXVec3Cross(&m_vec3Temp, &m_ViewDir, &m_ViewUp);
  return  &m_vec3Temp;
};

//====================================================================  
const vec4 *Context::GetVector4ViewSideUp()const
{
  vec3 res =  *GetVector3ViewUp();
  m_vec4Temp.x = res.x;
  m_vec4Temp.y = res.y;
  m_vec4Temp.z = res.z;
  m_vec4Temp.w = 1.0f;
  return  &m_vec4Temp;
};


//==================================================================
const vec3 *Context::GetMouseCoordCameraUnproject()const
{
  //ViewportZ  vp ; 
  //  POINT  pntMouseCoord ;

  // get viewport and mouse coord
  const DAPLIB_RenderContext *prcontext = DAPL_GetRenderContext();

  POINT msCoord = RWnd_GetWindowCursorPosition();

  return GetMouseCoordCameraUnproject(GetViewPortPtr(), &GetPointCursorWindowPosition() // &prcontext->GetPointCursorWindowPosition();

  );
};

//==================================================================
const vec3 *Context::GetVector3Unproject(_in_opt ViewportZ *vp, _in POINT *pntCoord)const
{
  vec3 vsrc;
  vsrc.x = (FLOAT)pntCoord->x;
  vsrc.y = (FLOAT)pntCoord->y;
  vsrc.z = 0.0f;



  ViewportZ __viewport;

  if (vp)
  {
    __viewport =  *vp;
  }
  else
  {
    //const DAPLIB_RenderContext* prcontext =  DAPL_GetRenderContext();
    // viewport = prcontext->viewport;
    __viewport =  *GetViewPortPtr();
  }


  static vec3 res[4];


  static int nCurrResult = 0;
  nCurrResult++;
  if (nCurrResult >= 4)
  {
    nCurrResult = 0;
  }

  vec3 *pResult = &res[nCurrResult];





  D3DXVec3Unproject(pResult,  // vec3 * pOut,
   &vsrc,  //CONST vec3 * pV,
   &__viewport,  //CONST ViewportZ * pViewport,
  GetMatrixProj(),  //CONST mat44 * pProjection,
  GetMatrixView(),  //CONST mat44 * pView,
  GetMatrixWorld() // CONST mat44 * pWorld
  );



  return pResult;
};

//==================================================================== 
const vec3 *Context::GetMouseCoordCameraUnproject(const ViewportZ *vp, const POINT *pntMouseCoord)const
{

  if (m_bMouseCoordCameraUnproject_change)
  {
    // compute
    vec3 vsrc;
    vsrc.x = (FLOAT)pntMouseCoord->x;
    vsrc.y = (FLOAT)pntMouseCoord->y;
    vsrc.z = 0.0f;

    D3DXVec3Unproject( &m_vec3_MouseCoordCameraUnproject,  // vec3 * pOut,
     &vsrc,  //CONST vec3 * pV,
    vp,  //CONST ViewportZ * pViewport,
    GetMatrixProj(),  //CONST mat44 * pProjection,
    GetMatrixView(),  //CONST mat44 * pView,
    GetMatrixWorld() // CONST mat44 * pWorld
    );


    m_bMouseCoordCameraUnproject_change = false;
  };

  return  &m_vec3_MouseCoordCameraUnproject;
};


const vec3 *Context::GetVector3VewPos()const
{
  __checkViewVectors();
  return  &m_VewPos;
};
const vec3 *Context::GetVector3ViewDir()const
{
  __checkViewVectors();
  return  &m_ViewDir;
};
const vec3 *Context::GetVector3ViewUp()const
{
  __checkViewVectors();
  return  &m_ViewUp;
};


//===============================================
const PerspectiveProjData *Context::GetProjectionData()const
{
  if (m_BoolChangedMatr.bProjChange)
  {

    if (m_bChangeProjectionData)
    {
      D3DXEX_ExtractProjPerspectLH(m_PerspectiveProjData.fFovy, m_PerspectiveProjData.fAspect, m_PerspectiveProjData.fZnear, m_PerspectiveProjData.fZfar, GetMatrixProj());


      m_bChangeProjectionData = FALSE_VAL;

    } // if


  }; // if


  return  &m_PerspectiveProjData;
};


//============================================================
int  Context::PushMatrixWorld()const
{
  int  hr = 0;

  if (m_MatrixStackWorld.full())
    return E_FAIL;

  __try
  {
    m_MatrixStackWorld.top() =  *GetMatrixWorld();
    m_MatrixStackWorld.push();

  }
  __except(1)
  {
    hr |= E_FAIL;
  };


  return hr;
};

//============================================================
int  Context::PushMatrixView()const
{
  int  hr = 0;
  if (m_MatrixStackView.full())
    return E_FAIL;

  __try
  {
    m_MatrixStackView.top() =  *GetMatrixView();
    m_MatrixStackView.push();

  }
  __except(1)
  {
    hr |= E_FAIL;
  };


  return hr;
};

//============================================================
int  Context::PushMatrixProj()const
{
  int  hr = 0;

  if (m_MatrixStackProj.full())
    return E_FAIL;

  __try
  {
    m_MatrixStackProj.top() =  *GetMatrixProj();
    m_MatrixStackProj.push();

  }
  __except(1)
  {
    hr |= E_FAIL;
  };


  return hr;
};

//============================================================
int  Context::PushMatrices(BOOLFLAG bWorld, BOOLFLAG bView, BOOLFLAG bProj)const
{
  int  hr = 0;



  //const mat44* pmw = NULL;
  if (bWorld)
  {
    if (m_MatrixStackWorld.full())
    {
      MONPRINT(" MatrixStackWorld is full");
      hr |= E_FAIL;
    }
    else
    {
      *m_MatrixStackWorld.top_ptr() =  *GetMatrixWorld();
      m_MatrixStackWorld.push();
    }

  };

  //const mat44* pmv = NULL;
  if (bView)
  {
    if (m_MatrixStackView.full())
    {
      MONPRINT(" MatrixStackView is full");
      hr |= E_FAIL;
    }
    else
    {
      *m_MatrixStackView.top_ptr() =  *GetMatrixView();
      m_MatrixStackView.push();
    }
  };

  //const mat44* pmp = NULL;
  if (bProj)
  {
    if (m_MatrixStackProj.full())
    {
      MONPRINT(" MatrixStackProj is full");
      hr |= E_FAIL;
    }
    else
    {
      *m_MatrixStackProj.top_ptr() =  *GetMatrixProj();
      m_MatrixStackProj.push();
    }

  };


  return hr;
};

 

//============================================================
int  Context::PopMatrixWorld()const
{
  int  hr = 0;


  if (m_MatrixStackWorld.empty())
    return S_FALSE;

  hr |= setMatrices(m_MatrixStackWorld.top_ptr(), 0, 0);
  m_MatrixStackWorld.pop();

  return hr;
};

//============================================================
int  Context::PopMatrixView()const
{
  int  hr = 0;

  if (m_MatrixStackView.empty())
    return S_FALSE;

  hr |= setMatrices(0, m_MatrixStackView.top_ptr(), 0);
  m_MatrixStackView.pop();

  return hr;
};

//============================================================
int  Context::PopMatrixProj()const
{
  int  hr = 0;

  if (m_MatrixStackProj.empty())
    return S_FALSE;

  hr |= setMatrices(0, 0, m_MatrixStackProj.top_ptr());
  m_MatrixStackProj.pop();

  return hr;
};

//============================================================
int  Context::PopMatrices(BOOLFLAG bWorld, BOOLFLAG bView, BOOLFLAG bProj)const
{
  int  hr = 0;



  const mat44 *pmw = NULL;
  if (bWorld)
  {
    pmw = m_MatrixStackWorld.top_ptr();
  };

  const mat44 *pmv = NULL;
  if (bView)
  {
    pmv = m_MatrixStackView.top_ptr();
  };


  const mat44 *pmp = NULL;
  if (bProj)
  {
    pmp = m_MatrixStackProj.top_ptr();
  };


  hr |= setMatrices(pmw, pmv, pmp);


  return hr;
};


//=======================================================
int  Context::PopAllMatrices()const
{
  int  hr = 0;

  return PopMatrices(1, 1, 1);

};

//=======================================================
EyeData Context::GetViewParams()const
{
  EyeData res =  *GetViewParamsPtr();
  return res;
};

//=======================================================
const EyeData *Context::GetViewParamsPtr()const
{
  #pragma message ("ПОГОНЯТЬ В ОТЛАДКЕ ЭТОТ МЕТОД")

  /*struct EyeData {

  vec3 vEye;
  vec3 vAt;
  vec3 vUp;
  };*/


  const mat44 *pmViewInv = GetMatrixViewInverse();

  if (m_bIsParameter_EyeData_changed)
  {

    #pragma message ("ПРОВЕРИТЬ ПОЛУЧЕНИЕ ВЕКТОРОВ  ВИДА ИЗ ИНВЕРСНОЙ ВИДОВОЙ МАТРИЦЫ ")
    m_EyeData.vEye = *((vec3*) &m_matr.mViewInverse.matrix._41);
    vec3 vViewDir = *((vec3*) &m_matr.mViewInverse.matrix._31);
    m_EyeData.vUp = *((vec3*) &m_matr.mViewInverse.matrix._21);

    #pragma message("ПРОВЕРИТЬ ПОЛУЧЕНИЕ m_EyeData.vAt  ")
    float fDistToCenter = D3DXVec3Length(&vViewDir);
    m_EyeData.vAt = m_EyeData.vEye;
    m_EyeData.vAt.x += fDistToCenter;
    m_EyeData.vAt.y += fDistToCenter;
    m_EyeData.vAt.z += fDistToCenter;


    m_bIsParameter_EyeData_changed = FALSE_VAL;
  }; // if



  return  &m_EyeData;
};



//===========================================================
int  Context::SetViewParams(_in_opt vec3 *eye, _in_opt vec3 *at, _in_opt vec3 *up)const
{
  int  hr = 0;

  EyeData vp = GetViewParams();

  if (eye)
    vp.vEye =  *eye;
  if (at)
    vp.vAt =  *at;
  if (up)
    vp.vUp =  *up;

  hr |= SetViewParams(&vp);

  return hr;
};

//===========================================================
int  Context::SetViewParams(const EyeData *pvp)const
{
  int  hr = 0;

  mat44 mv;
  m_EyeData =  *pvp;

  D3DXMatrixLookAtLH(&mv, &m_EyeData.vEye, &m_EyeData.vAt, &m_EyeData.vUp);

  hr |= SetMatrixView(&mv);
  m_bIsParameter_EyeData_changed = FALSE_VAL;
  return hr;
};

//===========================================================
int  Context::SetViewEye(const vec3 *eye)const
{
  int  hr = 0;

  EyeData vp = GetViewParams();
  vp.vEye =  *eye;
  hr |= SetViewParams(&vp);

  return hr;
};

//===========================================================
int  Context::SetViewAt(const vec3 *at)const
{
  int  hr = 0;

  EyeData vp = GetViewParams();
  vp.vAt =  *at;
  hr |= SetViewParams(&vp);

  return hr;
};

//===========================================================
int  Context::SetViewUp(const vec3 *up)const
{
  int  hr = 0;

  EyeData vp = GetViewParams();
  vp.vUp =  *up;
  hr |= SetViewParams(&vp);

  return hr;
};

//===========================================================




//==============================================
int  Context::SetProjectionParams(float fFov, float fAsp, float fZNear, float fZFar)const
{
  int  hr = 0;

  PerspectiveProjData pd;

  pd.fFovy = fFov;
  pd.fAspect = fAsp;
  pd.fZnear = fZNear;
  pd.fZfar = fZFar;

  hr |= SetProjectionParams(&pd);

  return hr;
};

//===================================
int  Context::SetProjectionParams(const PerspectiveProjData *proj)const
{
  int  hr = 0;
  __try
  {

    mat44 mproj;
    D3DXMatrixPerspectiveFovLH(&mproj, proj->fFovy, proj->fAspect, proj->fZnear, proj->fZfar);
    hr |= SetMatrixProj(&mproj);

  }
  __exc_mon
  {
    hr |= E_FAIL;
  };

  return hr;
};

//==============================================
int  Context::SetProjectionFov(float fFov)const
{
  int  hr = 0;

  __try
  {
    PerspectiveProjData proj =  *GetProjectionData();
    proj.fFovy = fFov;
    SetProjectionParams(&proj);
  }
  __except(1)
  {
    MONPRINT("Exception ");
    hr |= E_FAIL;
  };

  return hr;
};

//===================================================
int  Context::SetProjectionAsp(float fAsp)const
{
  int  hr = 0;


  __try
  {
    PerspectiveProjData proj =  *GetProjectionData();
    proj.fAspect = fAsp;
    SetProjectionParams(&proj);
  }
  __except(1)
  {
    MONPRINT("Exception ");
    hr |= E_FAIL;
  };


  return hr;

};

//===================================================
int  Context::SetProjectionZNear(float fZNear)const
{
  int  hr = 0;

  __try
  {
    PerspectiveProjData proj =  *GetProjectionData();
    proj.fZnear = fZNear;
    SetProjectionParams(&proj);
  }
  __except(1)
  {
    MONPRINT("Exception ");
    hr |= E_FAIL;
  };


  return hr;
};

//===================================================
int  Context::SetProjectionZFar(float fZFar)const
{
  int  hr = 0;

  __try
  {
    PerspectiveProjData proj =  *GetProjectionData();
    proj.fZfar = fZFar;
    SetProjectionParams(&proj);
  }
  __except(1)
  {
    MONPRINT("Exception ");
    hr |= E_FAIL;
  };

  return hr;
};

//=====================================================
int  Context::SetProjectionZNearZFar(float fZNear, float fZFar)const
{
  int  hr = 0;

  __try
  {
    PerspectiveProjData proj =  *GetProjectionData();
    proj.fZnear = fZNear;
    proj.fZfar = fZFar;
    SetProjectionParams(&proj);
  }
  __except(1)
  {
    MONPRINT("Exception ");
    hr |= E_FAIL;
  };

  return hr;
};

//=============================================



//==========================================
TransformData  Context::GetWorldTransformData()const
{
  TransformData  res =  *GetWorldTransformDataPtr();
  return res;
};


//==========================================
const TransformData  *Context::GetWorldTransformDataPtr()const
{

  if (m_bTransfDataChange)
  {

    #pragma message("NEED CHECK IMPLEMENTATION" __FILE__ )

    const mat44 *mw = GetMatrixWorld();

    int  hrDecomp = D3DXMatrixDecompose( &m_D3DXTRANSFORMDATA.vSc,  //vec3 * pOutScale, 
     &m_qRotation,  //Quaternion * pOutRotation,
     &m_D3DXTRANSFORMDATA.vTrnsl,  //  vec3 * pOutTranslation, 
    mw  // CONST mat44 * pM
    );

    if FAILED(hrDecomp)
    {
      throw std::runtime_error("Error decompose matrix");
    };

    D3DXQuaternionToAxisAngle( &m_qRotation,  // CONST Quaternion * pQ, 
     &m_D3DXTRANSFORMDATA.rot.vRotAx,  //vec3 * pAxis,
     &m_D3DXTRANSFORMDATA.rot.fAngle  //  FLOAT * pAngle
    );

    m_bTransfDataChange = FALSE_VAL;
  }; // if


  return  &m_D3DXTRANSFORMDATA;
};

//==========================================
vec3 Context::GetWorldScaling()const
{

  vec3 res = GetWorldTransformDataPtr()->vSc;

  return res;

};

//==========================================
D3DXROTATION Context::GetWorldRotationData()const
{

  const TransformData  *ptd = GetWorldTransformDataPtr();

  return ptd->rot;

};

//==========================================
Quaternion Context::GetWorldRotationQnt()const
{
  // get const to check calculate
  const TransformData  *ptr = GetWorldTransformDataPtr();

  #pragma message("NEED CHECK CODE IMPLEMENTATION" __FILE__ )

  return m_qRotation;
};

//==========================================
vec3 Context::GetWorldPosition()const
{

  const TransformData  *ptd = GetWorldTransformDataPtr();

  return ptd->vTrnsl;

};


//==========================================
int  Context::SetWorldTransformData(const TransformData  *pTr)const
{
  int  hr = 0;

  m_bTransfDataChange = true;
  m_D3DXTRANSFORMDATA =  *pTr;

  mat44 mscale, mrotate, mtransl;

  D3DXMatrixTranslation(&mtransl, m_D3DXTRANSFORMDATA.vTrnsl.x, m_D3DXTRANSFORMDATA.vTrnsl.y, m_D3DXTRANSFORMDATA.vTrnsl.z);
  D3DXMatrixRotationAxis(&mrotate, &m_D3DXTRANSFORMDATA.rot.vRotAx, m_D3DXTRANSFORMDATA.rot.fAngle);
  D3DXMatrixScaling(&mscale, m_D3DXTRANSFORMDATA.vSc.x, m_D3DXTRANSFORMDATA.vSc.y, m_D3DXTRANSFORMDATA.vSc.z);

  mat44 mworld = mtransl * mscale * mrotate;
  hr |= setMatrices(&mworld, NULL, NULL);

  #pragma message("NEED CHECK IMPLEMENTATION" __FILE__ )

  return hr;
};

//==========================================
int  Context::SetWorldPositionVal(float x, float y, float z)const
{
  int  hr = 0;
  TransformData  trd = GetWorldTransformData();

  trd.vTrnsl.x = x;
  trd.vTrnsl.y = y;
  trd.vTrnsl.z = z;

  hr |= SetWorldTransformData(&trd);

  return hr;
};

//==========================================
int  Context::SetWorldPositionVec(const vec3 *pos)const
{
  int  hr = 0;
  vec3 vpos =  *pos;
  hr |= SetWorldPositionVal(vpos.x, vpos.y, vpos.z);

  return hr;
};


//==========================================
int  Context::SetWorldRotationEulers(float yaw, float pitch, float roll)const
{
  int  hr = 0;
  Quaternion q;
  D3DXQuaternionRotationYawPitchRoll(&q, yaw, pitch, roll);
  hr |= SetWorldRotationQnt(&q);

  return hr;
};

//==========================================
int  Context::SetWorldRotationVal(float axX, float axY, float axZ, float angle)const
{
  int  hr = 0;
  TransformData  trd = GetWorldTransformData();
  trd.rot.vRotAx.x = axX;
  trd.rot.vRotAx.y = axY;
  trd.rot.vRotAx.z = axZ;
  D3DXVec3Normalize(&trd.rot.vRotAx, &trd.rot.vRotAx);

  hr |= SetWorldTransformData(&trd);

  return hr;
};

//========================================== 
int  Context::SetWorldRotationQnt(const Quaternion *q)const
{
  int  hr = 0;
  TransformData  trd = GetWorldTransformData();
  m_qRotation =  *q;


  D3DXQuaternionToAxisAngle( &m_qRotation,  // CONST Quaternion * pQ,
   &trd.rot.vRotAx,  // vec3 * pAxis,
   &trd.rot.fAngle  //  FLOAT * pAngle
  );


  mat44 world;

  D3DXMatrixTransformation( &world,  //mat44 * pOut,
  NULL,  //CONST vec3 * pScalingCenter,
  NULL,  //CONST Quaternion * pScalingRotation,
   &trd.vSc,  // CONST vec3 * pScaling,
  NULL,  //CONST vec3 * pRotationCenter,
   &m_qRotation,  // CONST Quaternion * pRotation,
   &trd.vTrnsl  //  CONST vec3 * pTranslation
  );

  m_bTransfDataChange = true;


  #pragma message(">> NEED CHECK IMPLEMENTATION" __FILE__ )

  return hr;
};

//========================================
int  Context::SetWorldRotationAx(const vec3 *vAx, float angle, bool bNeedAxNormalize)const
{
  int  hr = 0;

  TransformData  trd = GetWorldTransformData();

  trd.rot.vRotAx =  *vAx;
  trd.rot.fAngle = angle;
  if (bNeedAxNormalize)
  {
    D3DXVec3Normalize(&trd.rot.vRotAx, &trd.rot.vRotAx);
  };

  hr |= SetWorldTransformData(&trd);

  return hr;
};


//==========================================
int  Context::SetWorldScaling(float val)const
{
  int  hr = 0;
  hr |= SetWorldScalingVal(val, val, val);

  return hr;
};

//==========================================
int  Context::SetWorldScalingVal(float x, float y, float z)const
{
  int  hr = 0;

  TransformData  tr = GetWorldTransformData();

  tr.vSc.x = x;
  tr.vSc.y = y;
  tr.vSc.z = z;

  hr |= SetWorldTransformData(&tr);
  return hr;
};

//=======================================================================
int  Context::SetWorldScalingVec(const vec3 *vSc)const
{
  int  hr = 0;
  vec3 scale =  *vSc;
  hr |= SetWorldScalingVal(scale.x, scale.y, scale.z);

  return hr;
};

//========================================================================
int  Context::SetWorldScalingTranslation(float fScale, const vec3 *vTrnsl)const
{
  int  hr = 0;
  TransformData  tr = GetWorldTransformData();
  tr.vSc.x = tr.vSc.y = tr.vSc.z = fScale;
  tr.vTrnsl =  *vTrnsl;
  hr |= SetWorldTransformData(&tr);

  return hr;
};

//==========================================
int  Context::SetWorldScalingTranslation(float fScale, float x, float y, float z)const
{
  int  hr = 0;
  vec3 vtr;

  vtr.x = x;
  vtr.y = y;
  vtr.z = z;

  hr |= SetWorldScalingTranslation(fScale, &vtr);

  return hr;
};


//============================================================
int  Context::SetWorldIdentity()const
{
  return setMatrices(&D3DXMATRIX_IDENTITY, NULL, NULL);


};
