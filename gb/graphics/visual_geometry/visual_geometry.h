/** \file  visual_geometry.h
 \brief  Отрисовка математических примитивов. Математика/Геометрия на мониторе .
* Полезно при отладке.
*
*
  Вывод для OpenGL пока не готов. но ОБЯЗАТЕЛЬНО будет.
*
 \todo Дорефракторить IDraw2DGeometry 
 \todo Переделать функции создания интерфейсов на бросающие исключения
 \todo Переделать все функции интерфейсов на void и бросающие исключения
 \todo Убрать с отрисовщиков в 3d параметр матрицы трансформации.


* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>

#include <gb/math/math.h>
#include <gb/color/color.h>



#if ( !defined(GB_OPENGL) && !defined(GB_D3D9) )
#error graph api not defined
#endif

// temp !
#ifdef WIN32
#include <windows.h>
#endif

#ifdef GB_D3D9
#include <d3d9.h>
#endif






// \todo убрать !!
#define _in_opt 


namespace gb
{

 namespace  graphics
 {
 
  /** \brief Отрисовка математических примитивов. Математика/Геометрия на мониторе.  */
  namespace visual_geometry
  {
 
//--------------------------------------------------------------------------------------


  //! \brief Перечисление тип графического API вывода виз. геомтрии.
  namespace vg_graph_api_e 
  {
	    enum  grarh_api_e 
		{

		  VG_GAPY_UNDEF   = 0, ///< API не определено

          #if ( defined(GB_D3D9) && defined(WIN32) )
		  VG_GAPY_D3D9, ///< Вывод через D3D9
          #endif 

          #ifdef GB_OPENGL
		  VG_GAPY_OPENGL, ///< Вывод через OpenGL
          #endif

	    };
  };



  // !  temp 
#if (1)

#define VGCOLOR  gb::color::Color4f   
#define VGVEC2  gb::math::base::vec2_s 
#define VGVEC3  gb::math::base::vec3_s 
#define VGVEC4  gb::math::base::vec4_s 
#define VGMATRIX  gb::math::base::mat44_s 

//typedef gb::color::Color4f        VGCOLOR;     
//typedef gb::math::base::vec2_s    VGVEC2;   
//typedef gb::math::base::vec3_s    VGVEC3;   
//typedef gb::math::base::vec4_s    VGVEC4;   
//typedef gb::math::base::mat44_s   VGMATRIX;  


#else

#define  VGCOLOR D3DXCOLOR
#define  VGVEC2 D3DXVECTOR2
#define  VGVEC3 D3DXVECTOR3
#define  VGVEC4 D3DXVECTOR4
#define  VGMATRIX D3DXMATRIX

#endif





  //! \brief  Интерфейс вывода значений
  class IDrawValues {
  public:
	virtual ~IDrawValues() {};

	//! \brief Установить позицию вывода 
	virtual HRESULT setPos( int x, int y ) const =0;

	// virtual HRESULT setFontSmall() const =0;
	//virtual HRESULT setFontNormal() const =0;
	//virtual HRESULT setFontBig() const =0;

	//! \brief Установить цвет вывода  
	virtual HRESULT setColor( const VGCOLOR& color ) const =0;
	//! \brief Установить цвет вывода  красным 
	virtual HRESULT setColorRed() const =0;
	//! \brief Установить цвет вывода  зелёным
	virtual HRESULT setColorGreen() const =0;
	//! \brief Установить цвет вывода синим	
	virtual HRESULT setColorBlue() const =0;
	//! \brief Установить цвет вывода желтым
	virtual HRESULT setColorYellow() const =0;
	//! \brief Установить цвет вывода белым
	virtual HRESULT setColorWhite() const =0;
	//! \brief Установить цвет вывода серым
	virtual HRESULT setColorGray() const =0;
 
 	//! \brief Вывести строчку
	virtual HRESULT drawS(const char* s) const =0;
    //! \brief Вывод с форматированием
	virtual HRESULT drawF(const char* _Format, ... ) const =0;
	
    //! \brief Вывод bool значения в подсказкой promt
	virtual HRESULT drawBool  (bool  val, const char* promt=NULL) const =0;
    //! \brief Вывод int значения в подсказкой promt	
	virtual HRESULT drawInt   (int   val, const char* promt=NULL) const =0;
    //! \brief Вывод float значения в подсказкой promt	
	virtual HRESULT drawFloat (float val, const char* promt=NULL) const =0;
	
	
    //! \brief Вывод массива int в подсказкой promt	
	virtual HRESULT drawIntArray   (const int*   p, int num, const char* promt=NULL) const =0;
	//! \brief Вывод массива float с подсказкой promt
	virtual HRESULT drawFloatArray (const float* p, int num, const char* promt=NULL) const =0;

	//---------------------------------------------------------------------------

	virtual HRESULT drawVec2(const VGVEC2* v, const char* promt=NULL) const =0;
	virtual HRESULT drawVec3(const VGVEC3* v, const char* promt=NULL) const =0;
	virtual HRESULT drawVec4(const VGVEC4* v, const char* promt=NULL) const =0;

	virtual HRESULT drawMatrix(const VGMATRIX* m, const char* promt=NULL) const =0;

	virtual HRESULT drawPoint(const POINT pnt, const char* promt=NULL) const =0;
	virtual HRESULT drawPoint(int x, int y,    const char* promt=NULL) const =0;
	virtual HRESULT drawPoint(const VGVEC2* pos, const char* promt=NULL) const =0;

	 /************************
	//  virtual ID3DXFont*  GetInterfaceFontSmall()  const =0;
	//  virtual ID3DXFont*  GetInterfaceFontNormal() const =0;
	//  virtual ID3DXFont*  GetInterfaceFontBig()    const =0;

	 ********************************/

  };
  // end class 
  
  
//! \brief Вывод двухмерных объектов 
class   IDraw2DGeometry   {
public:
  //! \brief Установить цвет отрисовки 
  virtual HRESULT setColor(const VGCOLOR& color) const =0;

#ifdef GB_D3D9
  //! \brief Установить цвет отрисовки 
  virtual HRESULT setColor(const D3DCOLORVALUE& color) const =0;
#endif

//  virtual HRESULT SetColor(const D3DXCOLOR* color) const =0;

  //! \brief Установить цвет отрисовки 
  virtual HRESULT setColor(float r, float g, float b, float a) const=0;

  //! \brief Установить цвет отрисовки красным 
  virtual HRESULT setColorRed    ()  const =0;
  //! \brief Установить цвет отрисовки зелёным
  virtual HRESULT setColorGreen  ()  const =0;
  //! \brief Установить цвет отрисовки синим
  virtual HRESULT setColorBlue   ()  const =0;
  //! \brief Установить цвет отрисовки жёлтым
  virtual HRESULT setColorYellow ()  const =0;
  //! \brief Установить цвет отрисовки белым
  virtual HRESULT setColorWhite  ()  const =0;
  //! \brief Установить цвет отрисовки серым
  virtual HRESULT setColorGray   ()  const =0;
  //! \brief Установить цвет отрисовки розовым
  virtual HRESULT setColorPink   ()  const =0;

  //-----------------------------------------------------------------------
			 
  /*******************************************

 virtual HRESULT draw2dPoint(int x, int y,                float pointSize) const =0;
 virtual HRESULT draw2dPoint(float x, float y,            float pointSize) const =0;
 virtual HRESULT draw2dPoint(const VGVEC2 pos,      float pointSize) const =0;
// virtual HRESULT Draw2dPoint(const VGVEC2* pos,  float pointSize) const =0;
 virtual HRESULT draw2dPoint(const POINT p,               float pointSize) const =0;
 virtual HRESULT draw2dPoints(const VGVEC2* pv, int num, float pointSize) const =0;

 virtual HRESULT draw2dLine(const VGVEC2* p1,        const VGVEC2* p2) const =0;
 //virtual HRESULT Draw2dLine(const VGVEC2* p1,    const VGVEC2* p2) const =0;
 virtual HRESULT draw2dLine(const POINT p1,               const POINT p2) const =0;

 virtual HRESULT draw2dLine(const math::geom2d::Line* line) const =0;
 virtual HRESULT draw2dLine(int x1,   int y1,      int x2,   int y2   ) const =0;
 virtual HRESULT draw2dLine(float x1, float y1,    float x2, float y2 ) const =0;

 virtual HRESULT draw2dLines(const VGVEC2* pv, int num) const =0;

#ifdef GB_D3D9
 virtual HRESULT draw2dRect(const D3DRECT* rect) const =0;
#endif

 virtual HRESULT draw2dRect(int x1,   int y1,     int x2,   int y2) const =0;
 virtual HRESULT draw2dRect(float x1, float y1,   float x2, float y2) const =0;
 virtual HRESULT draw2dRect(const POINT p1, POINT p2) const =0;
 virtual HRESULT draw2dRect(const RECT rect) const =0;
// virtual HRESULT Draw2dRect(gb::math::geom2d::Rect* rect) const =0;
 
#ifdef GB_D3D9
 virtual HRESULT draw2dSolidRect(const D3DRECT* rect) const =0;
#endif

 virtual HRESULT draw2dSolidRect(const POINT p1, const POINT p2) const =0;
 virtual HRESULT draw2dSolidRect(int x1, int y1,   int x2, int y2) const =0;
 virtual HRESULT draw2dSolidRect(const RECT rect) const =0;

#pragma message("ks777: insert code rect")
 //virtual HRESULT Draw2dSolidRect(const gb::math::geom2d::Rect* rect) const =0;

 virtual HRESULT draw2dCircle(const VGVEC2* pos, float radius) const =0;
 virtual HRESULT draw2dCircle(float x, float y,       float radius) const =0;
 virtual HRESULT draw2dCircle(int x, int y,           float radius) const =0;
 virtual HRESULT draw2dCircle(const POINT pos,        float radius) const =0;
 virtual HRESULT draw2dCircle(const math::geom2d::Circle*   c) const =0;

//---------------------------------------------------------------

 virtual HRESULT draw2dAxies(const VGVEC2 coord) const =0;
 //virtual HRESULT Draw2dAxies(const VGVEC2 coord) const =0;

 virtual HRESULT draw2dAxies(float x, float y) const =0;
 virtual HRESULT draw2dAxies(int x, int y) const =0;
 virtual HRESULT draw2dAxies(const POINT p) const =0;


 //--------------------------------------------------------------

 virtual HRESULT draw2dTriangle(const VGVEC2* p1, const VGVEC2* p2,const VGVEC2* p3) const =0;
 virtual HRESULT draw2dTriangle(const POINT p1, const POINT p2, const POINT p3) const =0;

 //--------------------------------------------------------------

 virtual HRESULT draw2dSolidTriangle(const VGVEC2* p1, const VGVEC2* p2,const VGVEC2* p3) const =0;

 virtual HRESULT draw2dPromtString(const VGVEC2 coord, const char* s) const =0;
 virtual HRESULT draw2dPromtString(const   POINT p,         const char* s) const =0;
 virtual HRESULT draw2dPromtString(int x,   int y,          const char* s) const =0;
 virtual HRESULT draw2dPromtString(float x, float y,        const char* s) const =0;

 //----------------------------------------------------------------------


 virtual HRESULT draw2dRay(const VGVEC2* orig, const VGVEC2* nrml) const =0;

 *************************************/

};
// end class
 
 
//! \brief Вывод трёхмерных объектов.
class   IDraw3DGeometry   {
public:

  virtual HRESULT setColor(const VGCOLOR* color) const =0;


#ifdef GB_D3D9 
  virtual HRESULT setColor(const D3DCOLORVALUE* color) const =0;
#endif


  // TODO : remove
//  virtual HRESULT SetColor(const D3DXCOLOR* color) const =0;


  virtual HRESULT setColor(float r, float g, float b, float a) const=0;

  virtual HRESULT setColorRed    ()  const =0;
  virtual HRESULT setColorGreen  ()  const =0;
  virtual HRESULT setColorBlue   ()  const =0;
  virtual HRESULT setColorYellow ()  const =0;
  virtual HRESULT setColorWhite  ()  const =0;
  virtual HRESULT setColorGray   ()  const =0;
  virtual HRESULT setColorPink   ()  const =0;

//-------------------------------------------------------------------

  virtual HRESULT draw3dPoint  (const VGVEC3* pos,          float pointSize,  _in_opt  VGMATRIX* pTransf) const =0;
//virtual HRESULT draw3dPoint  (const VGVEC3* pos,      float pointSize,  _in_opt  VGMATRIX* pTransf) const =0;
  virtual HRESULT draw3dPoint  (float _x, float _y, float _z,    float pointSize,  _in_opt  VGMATRIX* pTransf) const =0;


  virtual HRESULT draw3dPoints (const VGVEC3* pv, int num, float pointSize,  _in_opt  VGMATRIX* pTransf) const =0;

  //-------------------------------------

  virtual HRESULT draw3dLine(const VGVEC3* p1, const VGVEC3* p2,_in_opt VGMATRIX* mTransf) const =0;
  virtual HRESULT draw3dLine(float x1, float y1, float z1,   float x2, float y2, float z2,_in_opt VGMATRIX* mTransf) const =0;
  virtual HRESULT draw3dLines( const VGVEC3* pv, int num ) const =0;

  virtual HRESULT drawAABB(const VGVEC3* min, const VGVEC3* max,_in_opt VGMATRIX* mTransf) const =0;

  virtual HRESULT draw3dRay(const VGVEC3* orig, const VGVEC3* normal,
							_in_opt VGMATRIX* mTransf) const =0;

  virtual HRESULT draw3dRay(float orgX, float orgY, float orgZ, float nrmlX, 
							float nrmlY, float nrmlZ, 
							_in_opt VGMATRIX* mTransf) const =0;

  virtual HRESULT draw3dRay(const math::geom3d::Ray * ray, _in_opt VGMATRIX* mTransf ) const =0;

  virtual HRESULT draw3dTraingle(const VGVEC3* v1, const VGVEC3* v2, const VGVEC3* v3, 
									_in_opt VGMATRIX* mTransf ) const =0;

  virtual HRESULT draw3dTraingle(const math::geom3d::Triangle*  tri, 
									_in_opt VGMATRIX* mTransf ) const =0;



  virtual HRESULT draw3dArrow(const VGVEC3* src, const VGVEC3* dest, _in_opt VGMATRIX* mTransf ) const =0;  


  virtual HRESULT draw3dAxies(const VGVEC3* coord, float axiesLen) const =0;

  virtual HRESULT draw3dSolidSphere(const VGVEC3* center, float radius) const =0;


};
// end class
 
  
  

//! \brief Опции создания интерфейсов
class CreteDrawValuesOptions {
public:
	//! \brief    граф. API
	vg_graph_api_e::grarh_api_e   api;  

#if ( defined(GB_D3D9) && defined(WIN32) )
    //! \brief    указатель на устройство
    IDirect3DDevice9* pdevice;
#endif 

  CreteDrawValuesOptions()
  {
	  api =  vg_graph_api_e::VG_GAPY_UNDEF;//   vg_graph_api_t::grarh_api_e::VG_GAPY_UNDEF;

      #if ( defined(GB_D3D9) && defined(WIN32) )
	    pdevice = NULL;
      #endif 

  }

};

//-------------------------------------------------------------------------

//! \brief Создать интерфейс вывода значений  
int32_t CreateInterfaceDrawValues(IDrawValues** ppOut, 
				const CreteDrawValuesOptions* opt);


//! \brief Создать интерфейс вывода 2-х мерных объектов  
int32_t CreateInterfaceDraw2DGeometry(IDraw2DGeometry** ppOut, 
				const CreteDrawValuesOptions* opt);

				

//! \brief Создать интерфейс вывода 3-х мерных объектов  
int32_t CreateInterfaceDraw3DGeometry(IDraw3DGeometry** ppOut,
				const CreteDrawValuesOptions* opt);

				




//-------------------------------------------------------------------------
 
  } // end ns
 } // end ns
} // end ns

// end file