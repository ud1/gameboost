/** \file  visual_geometry.h
 \brief  Отрисовка математических примитивов. Математика/Геометрия на мониторе .
* Полезно при отладке.
*
*
  Вывод для OpenGL пока не готов. но ОБЯЗАТЕЛЬНО будет.
*
 \todo Дорефракторить IDraw2DGeometry 
 \todo draw2dRect(const RECT rect) - переделать по ссылке параметр
 \todo Переделать все функции интерфейсов на void и бросающие исключения
 \todo Переделать парметры (вектора и матрицы)  на float* 
 \todo поменять GB_OPENGL на GB_VG_OPENGL   и  GB_D3D9 на GB_VG_D3D9
 \todo Отрисовку матриц сделать для разных 2x2  3x3  4x4
 \todo добавить установку ещё цветов.
 \tofo зависимость от gb::math только по макроопределению или вообще нет.



* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586

<br><br>

\code
 СДЕЛАНО:
   - Переделать функции создания интерфейсов на бросающие исключения
   - Убрать с отрисовщиков в 3d параметр матрицы трансформации.


\endcode


*/

#ifdef GB_VG // макрозащита

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>



#ifdef GB_MATH
   #include <gb/math/math.h>
#endif

#ifdef GB_COLOR
   #include <gb/color/color.h>
#endif



#if ( !defined(GB_OPENGL) && !defined(GB_D3D9) )
  #error graph api not defined. ДОЛЖЕН БЫТЬ ОПРЕДЕЛЁН ОДИН ИЗ МАКРОСОВ GB_OPENGL или GB_D3D9.
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

//! \brief Декларатор экспорта функций. Пока пустышка.
#define GB_VG_API 


namespace gb
{

 namespace  graphics
 {
 
  /** \brief Отрисовка математических примитивов. Математика/Геометрия на мониторе.  */
  namespace visual_geometry
  {


    
 
//--------------------------------------------------------------------------------------


  /**  \brief Дочернее от gb::graphics::vesual_geometry . 
         Перечисление тип графического API вывода визуальной геометрии. */
  namespace vg_graph_api_e 
  {
	    enum  grarh_api_e 
		{

		  VG_GAPY_UNDEF   = 0, ///< API не определено


           #ifdef GB_OPENGL
		  VG_GAPY_OPENGL, ///< Вывод через OpenGL
          #endif


          #if ( defined(GB_D3D9) && defined(WIN32) )
		  VG_GAPY_D3D9, ///< Вывод через D3D9
          #endif 




	    };
  };

 



  //! \brief  Интерфейс вывода значений
  class IDrawValues {
  public:
	virtual ~IDrawValues() {};

	//! \brief Установить позицию вывода 
	virtual void setPos( int x, int y ) const =0;

	// virtual HRESULT setFontSmall() const =0;
	//virtual HRESULT setFontNormal() const =0;
	//virtual HRESULT setFontBig() const =0;

	//! \brief Установить цвет вывода 
	virtual void setColor( float r, float g, float b, float a ) const =0;
	//virtual HRESULT setColor( const VGCOLOR& color ) const =0;
	//! \brief Установить цвет вывода  красным 
	virtual void setColorRed() const =0;
	//! \brief Установить цвет вывода  зелёным
	virtual void setColorGreen() const =0;
	//! \brief Установить цвет вывода синим	
	virtual void setColorBlue() const =0;
	//! \brief Установить цвет вывода желтым
	virtual void setColorYellow() const =0;
	//! \brief Установить цвет вывода белым
	virtual void setColorWhite() const =0;
	//! \brief Установить цвет вывода серым
	virtual void setColorGray() const =0;


 
 	//! \brief Вывести строчку
	virtual void drawS(const char* s) const =0;
    //! \brief Вывод с форматированием
	virtual void drawF(const char* _Format, ... ) const =0;
	
    //! \brief Вывод bool значения в подсказкой promt
	virtual void drawBool  (bool  val, const char* promt=NULL) const =0;
    //! \brief Вывод int значения в подсказкой promt	
	virtual void drawInt   (int   val, const char* promt=NULL) const =0;
    //! \brief Вывод float значения в подсказкой promt	
	virtual void drawFloat (float val, const char* promt=NULL) const =0;
	
    //---------------------------------------------------------------------

    //! \brief Вывод массива int в подсказкой promt	
	virtual void drawIntArray   (const int*   p, int num, const char* promt=NULL) const =0;
	//! \brief Вывод массива float с подсказкой promt
	virtual void drawFloatArray (const float* p, int num, const char* promt=NULL) const =0;

	//---------------------------------------------------------------------

	virtual void drawVec2(const float* vect2, const char* promt=NULL) const =0;
	virtual void drawVec3(const float* vect3, const char* promt=NULL) const =0;
	virtual void drawVec4(const float* vect4, const char* promt=NULL) const =0;

	virtual void drawMatrix4x4(const float* matrix4x4, const char* promt=NULL) const =0;

	//---------------------------------------------------------------------
 
	virtual void drawPoint(const POINT pnt,  const char* promt=NULL) const =0;
	virtual void drawPoint(int x, int y,     const char* promt=NULL) const =0;
	virtual void drawPoint(const float* vec2_pos, const char* promt=NULL) const =0;

 

 
	//  virtual ID3DXFont*  GetInterfaceFontSmall()  const =0;
	//  virtual ID3DXFont*  GetInterfaceFontNormal() const =0;
	//  virtual ID3DXFont*  GetInterfaceFontBig()    const =0;
 

  };
  // end class 
  
  
//! \brief Вывод двухмерных объектов 
class   IDraw2DGeometry   {
public:

#ifdef GB_COLOR
  //! \brief Установить цвет отрисовки 
	virtual void setColor(const gb::color::Color4f& color) const =0;
#endif

#ifdef GB_D3D9
  //! \brief Установить цвет отрисовки 
  virtual void setColor(const D3DCOLORVALUE& color) const =0;
#endif

//  virtual void SetColor(const D3DXCOLOR* color) const =0;

  //! \brief Установить цвет отрисовки 
  virtual void setColor(float r, float g, float b, float a) const=0;

  //! \brief Установить цвет отрисовки красным 
  virtual void setColorRed    ()  const =0;
  //! \brief Установить цвет отрисовки зелёным
  virtual void setColorGreen  ()  const =0;
  //! \brief Установить цвет отрисовки синим
  virtual void setColorBlue   ()  const =0;
  //! \brief Установить цвет отрисовки жёлтым
  virtual void setColorYellow ()  const =0;
  //! \brief Установить цвет отрисовки белым
  virtual void setColorWhite  ()  const =0;
  //! \brief Установить цвет отрисовки серым
  virtual void setColorGray   ()  const =0;
  //! \brief Установить цвет отрисовки розовым
  virtual void setColorPink   ()  const =0;

  //-----------------------------------------------------------------------
			 
		
 virtual HRESULT draw2dPoint(float x, float y,            float pointSize) const =0;
 virtual HRESULT draw2dPoint(const float* vec2_coord,     float pointSize) const =0;
// virtual HRESULT Draw2dPoint(const float* pos,  float pointSize) const =0;
 virtual HRESULT draw2dPoint(const POINT p,               float pointSize) const =0;

 //------------------------------------------------------------------------
	
 virtual HRESULT draw2dPoints(const float* vec2Array_points, int num, float pointSize) const =0;


 virtual HRESULT draw2dLine(const float* vec2_p1, const float* vec2_p2) const =0;
 //virtual HRESULT Draw2dLine(const float* p1,    const float* p2) const =0;
 virtual HRESULT draw2dLine(const POINT p1, const POINT p2) const =0;

#ifdef GB_MATH
 virtual HRESULT draw2dLine(const math::geom2d::Line* line) const =0;
#endif 

 //virtual HRESULT draw2dLine(int x1,   int y1,      int x2,   int y2   ) const =0;
 virtual HRESULT draw2dLine(float x1, float y1,    float x2, float y2 ) const =0;


     

 virtual HRESULT draw2dLines(const float* vec2Array_points, int num) const =0;

#ifdef GB_D3D9
 virtual HRESULT draw2dRect(const D3DRECT& rect) const =0;
#endif

 virtual HRESULT draw2dRect(int x1,   int y1,     int x2,   int y2) const =0;
 virtual HRESULT draw2dRect(float x1, float y1,   float x2, float y2) const =0;
 virtual HRESULT draw2dRect(const POINT p1, POINT p2) const =0;
 virtual HRESULT draw2dRect(const RECT rect) const =0;

#ifdef GB_MATH
   virtual HRESULT Draw2dRect(gb::math::geom2d::Rect* rect) const =0;
#endif

   
 
#ifdef GB_D3D9
   virtual HRESULT draw2dSolidRect(const D3DRECT& rect) const =0;
#endif

 virtual HRESULT draw2dSolidRect(const POINT& p1, const POINT& p2) const =0;
 virtual HRESULT draw2dSolidRect(int x1, int y1,   int x2, int y2) const =0;
 virtual HRESULT draw2dSolidRect(const RECT& rect) const =0;

 //------------------------------------------------------------------------

#pragma message("ks777: insert code rect")

#ifdef GB_MATH
 virtual HRESULT draw2dSolidRect(const gb::math::geom2d::Rect* rect) const =0;
#endif

 //------------------------------------------------------------------------

 virtual HRESULT draw2dCircle(const float* vec2_pos, float radius) const =0;
 virtual HRESULT draw2dCircle(float x, float y,       float radius) const =0;
 virtual HRESULT draw2dCircle(const POINT pos,        float radius) const =0;

    
#ifdef GB_MATH
  virtual HRESULT draw2dCircle(const math::geom2d::Circle*   c) const =0;
#endif

  

//---------------------------------------------------------------

 virtual HRESULT draw2dAxies(const float* vec2_coord) const =0;
 //virtual HRESULT Draw2dAxies(const float* coord) const =0;

 virtual HRESULT draw2dAxies(float x, float y) const =0;
 //virtual HRESULT draw2dAxies(int x, int y) const =0;
 virtual HRESULT draw2dAxies(const POINT p) const =0;

	
 //--------------------------------------------------------------

 virtual HRESULT draw2dTriangle(const float* vec2_p1, const float* vec2_p2, const float* vec2_p3) const =0;
 virtual HRESULT draw2dTriangle(const POINT& p1, const POINT& p2, const POINT& p3) const =0;

 //--------------------------------------------------------------
		
 virtual HRESULT draw2dSolidTriangle(const float* vec2_p1, const float* vec2_p2, const float* vec2_p3) const =0;
	 
 virtual HRESULT draw2dPromtString(const float* vec2_coord, const char* s) const =0;
 virtual HRESULT draw2dPromtString(const   POINT p,         const char* s) const =0;
 virtual HRESULT draw2dPromtString(int x,   int y,          const char* s) const =0;
 virtual HRESULT draw2dPromtString(float x, float y,        const char* s) const =0;
	    
 //----------------------------------------------------------------------


 virtual HRESULT draw2dRay(const float* vec2_orig, const float* vec2_normal) const =0;



		  /********************************************* 
		  ********************************************/

};
// end class
 
 
//! \brief Вывод трёхмерных объектов.
class   IDraw3DGeometry   {
public:

#ifdef GB_COLOR
  //! \brief Установить цвет отрисовки 
	virtual HRESULT setColor(const gb::color::Color4f& color) const =0;
#endif


#ifdef GB_D3D9 
  virtual void setColor(const D3DCOLORVALUE* color) const =0;
#endif



  virtual void setColor(float r, float g, float b, float a) const=0;

  virtual void setColorRed    ()  const =0;
  virtual void setColorGreen  ()  const =0;
  virtual void setColorBlue   ()  const =0;
  virtual void setColorYellow ()  const =0;
  virtual void setColorWhite  ()  const =0;
  virtual void setColorGray   ()  const =0;
  virtual void setColorPink   ()  const =0;

//-------------------------------------------------------------------

  virtual HRESULT draw3dPoint  (const float* vec3_coord,        float pointSize ) const =0;
  virtual HRESULT draw3dPoint  (float _x, float _y, float _z,   float pointSize ) const =0;

  virtual HRESULT draw3dPoints (const float* vec3_ArrayCoord, int num, float pointSize ) const =0;

  //-----------------------------------------------------------------

  virtual HRESULT draw3dLine(const float* vec3_p1, const float* vec3_p2 ) const =0;
  virtual HRESULT draw3dLine(float x1, float y1, float z1,   float x2, float y2, float z2 ) const =0;
  virtual HRESULT draw3dLines( const float* vec3_ArrayPoints, int num ) const =0;

  virtual HRESULT draw3dAABB(const float* vec3_min, const float* vec3_max ) const =0;

#ifdef GB_MATH
  virtual HRESULT draw3dAABB(const math::geom3d::AABB* aabb) const =0;
#endif

  virtual HRESULT draw3dRay(const float* vec3_orig, const float* vec3_normal ) const =0;

  virtual HRESULT draw3dRay(float orgX, float orgY, float orgZ, float nrmlX, float nrmlY, float nrmlZ ) const =0;

#ifdef GB_MATH
  virtual HRESULT draw3dRay(const math::geom3d::Ray * ray ) const =0;
#endif

  virtual HRESULT draw3dTraingle(const float* vec3_p1, const float* vec3_p2, const float* vec3_p3 ) const =0;

#ifdef GB_MATH
  virtual HRESULT draw3dTraingle(const math::geom3d::Triangle* tri) const =0;
#endif


  virtual HRESULT draw3dArrow(const float* vec3_srcCoord, const float* vec3_destCoord ) const =0;  


  virtual HRESULT draw3dAxies(const float* vec3_coord, float axiesLen) const =0;

  virtual HRESULT draw3dSolidSphere(const float* vec3_center, float radius) const =0;


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
GB_VG_API void CreateInterfaceDrawValues(IDrawValues** ppOut, 
				const CreteDrawValuesOptions* opt) throw();


//! \brief Создать интерфейс вывода 2-х мерных объектов  
GB_VG_API void CreateInterfaceDraw2DGeometry(IDraw2DGeometry** ppOut, 
				const CreteDrawValuesOptions* opt) throw();

				

//! \brief Создать интерфейс вывода 3-х мерных объектов  
GB_VG_API void CreateInterfaceDraw3DGeometry(IDraw3DGeometry** ppOut,
				const CreteDrawValuesOptions* opt) throw();

				




//-------------------------------------------------------------------------
 
  } // end namespace
 } // end namespace
} // end namespace


#endif // #ifdef GB_VG
// end file