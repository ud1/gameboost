/** \file macro.h
 \brief Макросы ,  макроопределения. Здесь ТОЛЬКО макросы.
*
*
*/

#pragma once

 // Отпостил тему.. добавляем ...


//! \brief Печать на консоль функции. Для мониторинга
#define GB_PRINT_FUNC  printf(" %s\n", __FUNCTION__); 

//! Безопасное удаление объекта
#define GB_SAFE_DEL_OBJ(p) { if(NULL != p) { delete   (p);  (p)=NULL; } }
//! Безопасное удаление буфера
#define GB_SAFE_DEL_BUF(p) { if(NULL != p) { delete [](p);  (p)=NULL; } }

#ifdef WIN32
   //! Безопасное удаление COM-интерфейса
   #define GB_SAFE_REL(p) { if(NULL != p) { (p)->Release(); (p)=NULL; } }
#endif

//! \brief проверка на вхождение в диапазон  включительно 
#define CHECK_RANGE(i,min,max) ((i) >= (min)) && ((i) <= (max)) ? 1 : 0


//! \brief Возврат максимального значения 
#define GB_MAX_VAL(i,j) (i)>(j) ? i : j


//! \brief Соединение лексем 
#define GB_JOIN(a, b) a ## b


//! \brief Преобразование символов  в строку 
#define GB_MAKE_STR(s)  # s
#define GB_MAKE_STR2(x) GB_MAKE_STR(x)


#ifdef WIN32
  //! \brief Для windows: Выбросить окошко с сообщением msg
  #define GB_MBOX(msg)  MessageBoxA(0,  (msg), "GB_MBOX", MB_OK|MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST);
  //! \brief Для windows: Выбросить окошко с сообщением и надписью об ошибке.
  #define GB_MBOX_ERR(msg,caption)  MessageBoxA(0, (msg), (caption), MB_OK|MB_ICONERROR|MB_TASKMODAL|MB_TOPMOST);

#endif

#ifdef WIN32
  //! \brief Выход из функции если результат неудачный
  #define GB_RETFAIL  if FAILED(hr) { return hr;  }
#endif


  
#ifdef WIN32	
  //! \brief  Безопасное по исключению удаление COM-интерфейса	56	 
  #define GB_SAFE_EXC_RELEASE(p) { if(NULL != (p) ) { try { (p)->Release(); } catch(...) { (p)=NULL; }; (p)=NULL; } }		
#endif		
			
		
#define GB_MONPRINT(msg)  printf("%s\n" , (msg) );	


//----------------------------------------------------------------------


//
//   маркеры параметров
// 


//!  \brief  Обязательный параметр  только  для чтения (нельзя NULL если указатель).  
#define   gb_in  const

//!  \brief   Обязательный параметр для записи (без чтения) (нельзя NULL если указатель).  
#define   gb_out

//!  \brief   Обязательный параметр для чтения и записи (данные могут быть прочитаны и после операции записаны) (нельзя NULL если указатель) .  
#define   gb_inout

//!  \brief  Опциональный параметр (по умолчанию)  для чтения (можно передать NULL ).  
#define   gb_in_opt  const

//!  \brief   Опциональный параметр (по умолчанию) для записи (без чтения) (можно передать NULL ) .  
#define   gb_out_opt

//!  \brief   Опциональный параметр (по умолчанию) для чтения и записи (данные могут быть прочитаны , а после записаны) (можно передать NULL если указатель).  
#define   gb_inout_opt

//!  \brief   Опциональный параметр указатель (можно передать NULL ).   
#define   gb_opt 

//----------------------------------------------------

		
// end file