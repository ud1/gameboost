/** \file
\brief Класс вычислитель среднего цвета рендертаргет поверхности .  

В рассчёт должна передаваться поверхность созданая только как Render Target. 
и только созданую по формату заднего буфера .  <br>

Создан: 27.06.2010 


 */

#pragma once

#include <gb/base/Rectangle.h>
#include <gb/base/Point.h>
#include <gb/t/func.h>
#include <gb/macro.h>

#include <gb/color/color.h>



#pragma warning (push)
#pragma warning (disable : 4244)
#pragma warning (disable : 4996)




/** \brief Класс интерфейсы вычислителя цвета SurfAvearColorComputer  */
class SurfAvearcolInterfaces
{
  public:
    IDirect3DTexture9 *texture;
    IDirect3DSurface9 *surface;

    SurfAvearcolInterfaces()
    {
        void Release();
    };

    void Release()
    {
        gb::t::func::safeExceptionRelease(&surface); 
          //  if(surface) { surface->Release(); surface = NULL; };
        gb::t::func::safeExceptionRelease(&texture); 
          //if(texture) { texture->Release(); texture = NULL; };
    };

    //* \brief   Создание  как рендер-таргет текстуры
    HRESULT CreateStretched(IDirect3DDevice9 *device, UINT w, UINT h, const
      D3DSURFACE_DESC *des);
    //* \brief   Создание как  конечной 1x1 поверхности для конечного результата
    HRESULT CreateEnd(IDirect3DDevice9 *device, const D3DSURFACE_DESC *des);


};
// end class SurfAvearcolInterfaces 


/** \brief Класс вычислитель среднего зачения поверхности */
class SurfAvearColorComputer
{
  private:
    SurfAvearcolInterfaces m_end;
    SurfAvearcolInterfaces m_stretch256x256, m_stretch32x32, m_stretch8x8,
      m_stretch4x4, m_stretch2x2, m_stretch1x1;

    char m_strError[64];

    //* Проверка переданого описания поверхности (srcDes-переданый для вычисления , 
    // backBuffDes-текущее   стреч поверхности.  )
    bool CheckSourceDescription(const D3DSURFACE_DESC *srcDes, const
      D3DSURFACE_DESC *strechDes)
    {
        if ((srcDes->Format != strechDes->Format) || (srcDes->Pool != strechDes
          ->Pool))
        {
          return false;
        }

        //* TODO .... Возможн оследует подкорректировать проверку
        return true;
    };


    /** \brief Создание необходимых интерфейсов */
    HRESULT CreateInterfaces(IDirect3DDevice9 *device);

    /** \brief Проверка на инициализацию */
    static HRESULT CheckInit();

  public:
    /** \brief Удаление интерфейсов . Обязательно вызвать при потере девайса или удалении.  */
    void ReleaseInterfaces()
    {
        m_end.Release();
        m_stretch256x256.Release();
        m_stretch32x32.Release();
        m_stretch8x8.Release();
        m_stretch4x4.Release();
        m_stretch2x2.Release();
        m_stretch1x1.Release();
    };

  public:

    ////** \brief ПОлучить глобальный объект */
    //	static SurfAvearColorComputer* GetGlobalInstance();

    SurfAvearColorComputer();
    ~SurfAvearColorComputer()
    {
        ReleaseInterfaces();
    };

    /** \brief  Получение описания ошибки в виде строки . */
    const char *GetLastErrorDescr()
    {
        if (m_strError[0] == 0)
        {
          return NULL;
        }
        return m_strError;
    };


    /** \brief  Вычисление среднего цвета поверхности. <br>
    Для получения строки ошибки использовать метод GetLastErrorDescr  <br> .
    \param pOut  - [out] Результат  .
    \param device  - [in] девайс  .
    \param surf  - [in] Поверхность , с которой требуется вычислить цвет  .
    \param rect  - [in] Прямоугольник высисляемой области или NULL если требуется вычислить всю поверхность  .
    \return  -   Возвращает E_FAIL если произошла ошибка   .
     */
    HRESULT Compute(D3DCOLOR *pOut, 
		IDirect3DDevice9 *device, 
		IDirect3DSurface9
      *surf, 
	  const RECT *rect);


    //-------------------------------------------------------------------
    HRESULT ComputeColor2(gb_out gb::color::Color4f *pOut, 
		IDirect3DDevice9  *device, 
		IDirect3DSurface9 *surf, 
		const gb::base::Rectangle *rect)
    {
        HRESULT hr = 0;

        if (rect)
        {
            RECT _rect = (RECT) *rect; // rect->AsRect();
            hr |= ComputeColor(pOut, device, surf, &_rect);
        }
        else
        {

            hr |= ComputeColor(pOut, device, surf, NULL);
        }


        return hr;
    }


    //--------------------------------------------------------------------
    HRESULT ComputeColor(
		gb_out gb::color::Color4f *pOut, 
		IDirect3DDevice9  *device, 
		IDirect3DSurface9 *surf, 
		const RECT *rect);

    /** \brief Вычислить цвет всей текущей рендертаргет поверхности . */
    HRESULT ComputeCurrentRenderSurfColor(
		D3DCOLOR *pOut, 
		IDirect3DDevice9   *device, 
		const RECT *rect = NULL)
    {
        return Compute(pOut, device, NULL, rect);
    };


};
//  end class SurfAvearColorComputer



#pragma warning (pop)
// end file
