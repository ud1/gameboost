/**
 *
 *
 * \todo УБрать FAILED SUCC и все виндовские макросы.  
 * \todo Подружить с не windows ....
 *
 *
 */ 



#pragma  once
 

#include <gb/base/Types.h>
#include <gb/fmath/fmath.h>

using namespace gb::fmath;
using namespace gb::fmath::geom3d;
using namespace gb::fmath::proj;
 
 

 

class Context  {
public:
   Context() {}
 

  long  setMatrices(const  mat44 *mWorld,
				    const  mat44 *mView, 
				    const  mat44 *mProj );

	inline long  SetMatrixWorld(const mat44 *m) 
	{
	  return setMatrices(m, NULL, NULL);
	}	 

	inline long SetMatrixView(const mat44 *m) 
	{
	  return setMatrices(NULL, m, NULL);
	}

	inline long SetMatrixProj(const mat44 *m) 
	{
	  return setMatrices(NULL, NULL, m);
	}


  const mat44 *getMatrixWorld()const
  {
    return  &m_mWorld;
  }

  const mat44 *getMatrixView()const
  {
    return  &m_mView;
  }

  const mat44 *getMatrixProj()const
  {
    return  &m_mProj;
  }


  const mat44 *getMatrixViewProjection()const;
  const mat44 *getMatrixViewProjectionInverse()const;
  const mat44 *getMatrixViewProjectionInverseTranspone()const;
  const mat44 *getMatrixViewProjectionTranspone()const;
  const mat44 *getMatrixViewTranspone()const;
  const mat44 *getMatrixViewInverse()const;
  const mat44 *getMatrixViewInverseTranspone()const;

  const mat44 *getMatrixProjectionInverse()const;
  const mat44 *getMatrixProjectionTranspone()const;
  const mat44 *getMatrixProjectionInverseTranspone()const;

  const mat44 *getMatrixWorldViewProjection()const;
  const mat44 *getMatrixWorldViewProjectionTranspone()const;
  const mat44 *getMatrixWorldViewProjectionInverse()const;
  const mat44 *getMatrixWorldViewProjectionInverseTranspone()const;
  const mat44 *getMatrixWorldTranspone()const;
  const mat44 *getMatrixWorldInverse()const;
  const mat44 *getMatrixWorldInverseTranspone()const;
  const mat44 *getMatrixWorldView()const;
  const mat44 *getMatrixWorldViewTranspone()const;
  const mat44 *getMatrixWorldViewInverse()const;
  const mat44 *getMatrixWorldViewInverseTranspone()const;

  const vec3 *get_vector3_VewPos()const;
  const vec3 *get_vector3_ViewDir()const;
  const vec3 *get_vector3_ViewUp()const;
  const vec3 *get_vector3_ViewSideUp()const;

  const vec4 *get_vector4_ViewPos()const;
  const vec4 *get_vector4_ViewDir()const;
  const vec4 *get_vector4_ViewUp()const;
  const vec4 *get_vector4_ViewSideUp()const;


//  const vec3 *get_vector3_Unproject(const  ViewportZ *vp, const  POINT *pntCoord)const;
 
 // const vec3 *GetMouseCoordCameraUnproject(const ViewportZ *vp, const POINT *pntMouseCoord)const;
 // const vec3 *GetMouseCoordCameraUnproject()const;

  const PerspectiveProjData *get_projection_Data()const;

  float get_projection_Fov()const
  {
    const PerspectiveProjData *prj = get_projection_Data();
    return prj->fovy; 
  }

  float get_projection_Aspect()const
  {
    const PerspectiveProjData *prj = get_projection_Data();
    return prj->aspect; 
  }

  float get_projection_ZNear()const
  {
    const PerspectiveProjData *prj = get_projection_Data();
    return prj->zn; 
  }

  float get_projection_ZFar()const
  {
    const PerspectiveProjData *prj = get_projection_Data();
    return prj->zf; 
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



    EyeData getViewParams()const;
    const EyeData *getViewParamsPtr()const;


    int  setViewParams(const  vec3 *eye, const  vec3 *at, const  vec3 *up) ;
    int  setViewParams(const EyeData *pvp) ;

    int  setViewEye(const vec3 *eye) ;
    int  setViewAt(const vec3 *at) ;
    int  setViewUp(const vec3 *up) ;

    int  setProjectionParams(float fFov, float fAsp, float fZNear, float fZFar) ;
    int  setProjectionParams(const PerspectiveProjData *proj) ;
    int  setProjectionFov(float fFov) ;
    int  setProjectionAsp(float fAsp) ;
    int  setProjectionZNear(float fZNear) ;
    int  setProjectionZFar(float fZFar) ;
    int  setProjectionZNearZFar(float fZNear, float fZFar) ;

  //-----------------------------------------------------------------------
 

    TransformData  getWorldTransformData()const;
    const TransformData  *getWorldTransformDataPtr()const;

    vec3 getWorldScaling()const;

 
    AxiesAngle getWorldRotationAxiesAngle()const;

    Quaternion getWorldRotationQuaternion()const;
 

    vec3 getWorldPosition()const;

    int  setWorldTransformData(const TransformData  *pTr) ;

    int  setWorldPositionVal(float x, float y, float z) ;
    int  setWorldPositionVec(const vec3 *pos) ;

    int  setWorldRotationYawPitchRoll(float yaw, float pitch, float roll) ;
//    int  setWorldRotationVal(float axX, float axY, float axZ, float angle) ;
    int  setWorldRotationQuaternion(const Quaternion *q) ;
    int  setWorldRotationAxiesAngle(const vec3 *vAx, float angle) ;

    int  setWorldScaling(float val) ;
    int  setWorldScaling(float x, float y, float z) ;
    int  setWorldScalingVec(const vec3 *vSc) ;

    int  setWorldScalingTranslation(float fScale, const vec3 *vTrnsl) ;
    int  setWorldScalingTranslation(float fScale, float x, float y, float z) ;

	int  setWorldIdentity()  
	{
	   mat44 mident(1.0f);
		return setMatrices(&mident, NULL, NULL);
	}

  
	/*
    UINT getMatrixWorldStackSize()const
  {
    return (UINT)m_MatrixStackWorld.size();
  };
    UINT getMatrixViewStackSize()const
  {
    return (UINT)m_MatrixStackView.size();
  };
    UINT getMatrixProjStackSize()const
  {
    return (UINT)m_MatrixStackProj.size();
  };
     */


	//gb::fmath::proj::PerspectiveProjData

protected:
   void __checkViewVectors() const;


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

	mViewProjection, 
	mViewProjectionInverse, 
	mViewProjectionInverseTranspone, 
	mViewProjectionTranspone, 
    mViewTranspone, 
	mViewInverse, 
	mViewInverseTranspone, 
    mProjectionInverse, 
	mProjectionTranspone, 
	mProjectionInverseTranspone, 
    mWorldViewProjection, 
	mWorldViewProjectionTranspone,
	mWorldViewProjectionInverse, 
	mWorldViewProjectionInverseTranspone, 
    mWorldTranspone, 
	mWorldInverse, 
	mWorldInverseTranspone, 
	mWorldView, 
	mWorldViewTranspone, 
	mWorldViewInverse, 
	mWorldViewInverseTranspone;

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
 

	/*
  mutable CFixedMatrixStack m_MatrixStackWorld;
  mutable CFixedMatrixStack m_MatrixStackView;
  mutable CFixedMatrixStack m_MatrixStackProj;
    */

  mutable bool m_bTransfDataChange;
  mutable TransformData  m_TransformData;

  // временно исключено !
 // mutable Quaternion m_qRotation;
 

};
// end class
