 

#pragma  once

#include <gb/base/Types.h>
#include <gb/fmath/fmath.h>

using namespace gb::fmath;
using namespace gb::fmath::geom3d;
using namespace gb::fmath::proj;
 

#define TRUE_VAL   1
#define FALSE_VAL  1

#define _in_opt  const
#define  _in    const 

class Context 
{
	//gb::fmath::proj::PerspectiveProjData

private:
	typedef unsigned long BOOLFLAG;

  /** \brief Сборка для класса MatricesContext */
  struct matrixStore_s
  {
    mat44 matrix;
    BOOLFLAG bChangeFlag;
  };

  /** \brief Структура Вспомогательная сборка матриц для класса MatricesContext */
  struct MatricesStore
  {
    matrixStore_s 

	mViewProjection, mViewProjectionInverse, 
	mViewProjectionInverseTranspone, mViewProjectionTranspone, 
    mViewTranspone, mViewInverse, mViewInverseTranspone, 
    mProjectionInverse, mProjectionTranspone, mProjectionInverseTranspone, 
    mWorldViewProjection, mWorldViewProjectionTranspone,
	mWorldViewProjectionInverse, mWorldViewProjectionInverseTranspone, 
    mWorldTranspone, mWorldInverse, mWorldInverseTranspone, mWorldView, 
	mWorldViewTranspone, mWorldViewInverse, mWorldViewInverseTranspone;

  };



  /** \brief Вспомогательная структура для класса MatricesContext  */
  struct BoolChangedMainMatrisec
  {
    BOOLFLAG bViewChange, bWorldChange, bProjChange;
  };


    mat44 m_mWorld, m_mView, m_mProj; //*< основные матрицы


  mutable mat44 m_temp;
  mutable mat44 m_temp2; //*< для временных вычислений

  mutable MatricesStore m_matr;
  mutable BoolChangedMainMatrisec m_BoolChangedMatr;

  mutable vec3 m_VewPos;
  mutable vec3 m_ViewDir;
  mutable vec3 m_ViewUp;
  mutable vec3 m_vec3Temp;

  mutable vec4 m_vec4Temp;

  //*  показывает изменился ли вектор MouseCoordCameraUnproject
  mutable bool m_bMouseCoordCameraUnproject_change;
  //* последний пересчитаный вектор MouseCoordCameraUnproject
  mutable vec3 m_vec3_MouseCoordCameraUnproject;

  //* изменилимь ли данные проекции 
  mutable BOOLFLAG m_bChangeProjectionData;
  //* данные проекции 
  mutable PerspectiveProjData m_PerspectiveProjData;

  //* изменились ли вью параметры
  mutable BOOLFLAG m_bIsParameter_EyeData_changed;
  //* вью параметры
  mutable EyeData m_EyeData;


 
 // gb::fmath::geom3d::EyeData


protected:
  void __checkViewVectors()const;


public:
   Context() {}
  // ~Context() {}


  int  setMatrices(_in_opt mat44 *mWorld,
				   _in_opt mat44 *mView, 
				   _in_opt mat44 *mProj );

  const mat44 *GetMatrixWorld()const
  {
    return  &m_mWorld;
  }

  const mat44 *GetMatrixView()const
  {
    return  &m_mView;
  }

  const mat44 *GetMatrixProj()const
  {
    return  &m_mProj;
  }


  const mat44 *GetMatrixViewProjection()const;
  const mat44 *GetMatrixViewProjectionInverse()const;
  const mat44 *GetMatrixViewProjectionInverseTranspone()const;
  const mat44 *GetMatrixViewProjectionTranspone()const;
  const mat44 *GetMatrixViewTranspone()const;
  const mat44 *GetMatrixViewInverse()const;
  const mat44 *GetMatrixViewInverseTranspone()const;

  const mat44 *GetMatrixProjectionInverse()const;
  const mat44 *GetMatrixProjectionTranspone()const;
  const mat44 *GetMatrixProjectionInverseTranspone()const;

  const mat44 *GetMatrixWorldViewProjection()const;
  const mat44 *GetMatrixWorldViewProjectionTranspone()const;
  const mat44 *GetMatrixWorldViewProjectionInverse()const;
  const mat44 *GetMatrixWorldViewProjectionInverseTranspone()const;
  const mat44 *GetMatrixWorldTranspone()const;
  const mat44 *GetMatrixWorldInverse()const;
  const mat44 *GetMatrixWorldInverseTranspone()const;
  const mat44 *GetMatrixWorldView()const;
  const mat44 *GetMatrixWorldViewTranspone()const;
  const mat44 *GetMatrixWorldViewInverse()const;
  const mat44 *GetMatrixWorldViewInverseTranspone()const;

  const vec3 *GetVector3VewPos()const;
  const vec3 *GetVector3ViewDir()const;
  const vec3 *GetVector3ViewUp()const;
  const vec3 *GetVector3ViewSideUp()const;

  const vec4 *GetVector4ViewPos()const;
  const vec4 *GetVector4ViewDir()const;
  const vec4 *GetVector4ViewUp()const;
  const vec4 *GetVector4ViewSideUp()const;


  const vec3 *GetVector3Unproject(_in_opt ViewportZ *vp, _in POINT *pntCoord)const;
 
  const vec3 *GetMouseCoordCameraUnproject(const ViewportZ *vp, const POINT *pntMouseCoord)const;
  const vec3 *GetMouseCoordCameraUnproject()const;

  const PerspectiveProjData *GetProjectionData()const;

  float GetProjectionFov()const
  {
    const PerspectiveProjData *prj = GetProjectionData();
    return prj->fovy;   //->fFovy;
  }

  float GetProjectionAspect()const
  {
    const PerspectiveProjData *prj = GetProjectionData();
    return prj->aspect; //fAspect;
  }

  float GetProjectionZNear()const
  {
    const PerspectiveProjData *prj = GetProjectionData();
    return prj->zn;   //fZnear;
  }

  float GetProjectionZFar()const
  {
    const PerspectiveProjData *prj = GetProjectionData();
    return prj->zf;   //fZfar;
  }

   /*
  int  PushMatrixWorld()const;
  int  PushMatrixView()const;
  int  PushMatrixProj()const;

  int  PushMatrices(BOOLFLAG bWorld, BOOLFLAG bView, BOOLFLAG bProj)const;
  inline int  PushAllMatrices()const 
  {
    PushMatrices(1, 1, 1);
  }

  int  PopMatrixWorld()const;
  int  PopMatrixView()const;
  int  PopMatrixProj()const;


  int  PopMatrices(BOOLFLAG bWorld, BOOLFLAG bView, BOOLFLAG bProj)const;
  int  PopAllMatrices()const;

    int  SetMatrixWorld(const mat44 *m)const;
    int  SetMatrixView(const mat44 *m)const;
    int  SetMatrixProj(const mat44 *m)const;
	*/

	 
	inline int  SetMatrixWorld(const mat44 *m) 
	{
	  return setMatrices(m, NULL, NULL);
	}
 
	inline int SetMatrixView(const mat44 *m) 
	{
	  return setMatrices(NULL, m, NULL);
	}
 
	inline int SetMatrixProj(const mat44 *m) 
	{
	  return setMatrices(NULL, NULL, m);
	}



    EyeData GetViewParams()const;
    const EyeData *GetViewParamsPtr()const;

    int  SetViewParams(_in_opt vec3 *eye, _in_opt vec3 *at, _in_opt vec3 *up)const;
    int  SetViewParams(const EyeData *pvp)const;

    int  SetViewEye(const vec3 *eye)const;
    int  SetViewAt(const vec3 *at)const;
    int  SetViewUp(const vec3 *up)const;

    int  SetProjectionParams(float fFov, float fAsp, float fZNear, float fZFar)const;
    int  SetProjectionParams(const PerspectiveProjData *proj)const;
    int  SetProjectionFov(float fFov)const;
    int  SetProjectionAsp(float fAsp)const;
    int  SetProjectionZNear(float fZNear)const;
    int  SetProjectionZFar(float fZFar)const;
    int  SetProjectionZNearZFar(float fZNear, float fZFar)const;

  //-----------------------------------------------------------------------
 

    TransformData  GetWorldTransformData()const;
    const TransformData  *GetWorldTransformDataPtr()const;

    vec3 GetWorldScaling()const;

   /*
    D3DXROTATION GetWorldRotationData()const;
    Quaternion GetWorldRotationQnt()const;
   */

    vec3 GetWorldPosition()const;

    int  SetWorldTransformData(const TransformData  *pTr)const;

    int  SetWorldPositionVal(float x, float y, float z)const;
    int  SetWorldPositionVec(const vec3 *pos)const;

    int  SetWorldRotationEulers(float yaw, float pitch, float roll)const;
    int  SetWorldRotationVal(float axX, float axY, float axZ, float angle)const;
    int  SetWorldRotationQnt(const Quaternion *q)const;
    int  SetWorldRotationAx(const vec3 *vAx, float angle, bool bNeedAxNormalize)const;

    int  SetWorldScaling(float val)const;
    int  SetWorldScalingVal(float x, float y, float z)const;
    int  SetWorldScalingVec(const vec3 *vSc)const;

    int  SetWorldScalingTranslation(float fScale, const vec3 *vTrnsl)const;
    int  SetWorldScalingTranslation(float fScale, float x, float y, float z)const;

    int  SetWorldIdentity()const;

  
	/*
    UINT GetMatrixWorldStackSize()const
  {
    return (UINT)m_MatrixStackWorld.size();
  };
    UINT GetMatrixViewStackSize()const
  {
    return (UINT)m_MatrixStackView.size();
  };
    UINT GetMatrixProjStackSize()const
  {
    return (UINT)m_MatrixStackProj.size();
  };
     */


private:

	/*
  mutable CFixedMatrixStack m_MatrixStackWorld;
  mutable CFixedMatrixStack m_MatrixStackView;
  mutable CFixedMatrixStack m_MatrixStackProj;
    */

  mutable bool m_bTransfDataChange;
  mutable TransformData  m_D3DXTRANSFORMDATA;
  mutable Quaternion m_qRotation;



public:


};
// end class
