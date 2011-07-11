﻿/** \file 
* \brief  template functions
*
*
*/

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <deque>
#include <stdexcept>

#include <assert.h>

 

namespace gb 
{
 namespace t 
 {


 //     //! \brief  
 // namespace func
  //{

//-------------------------------------------------------------------------

  
 	// template<typename T>
	// /** \brief Обмен указателей по адресам */
	// inline void swap_ptrs(T** pp1, T** pp2) 
	// {
		// T* temp = *pp1;
		// *pp1 = *pp2;
		// *pp2 = temp;
	// };

	// template<typename T>
	// /** \brief Обмен элементов по ссылке */
	// inline void swap_refs(T& a1, T& a2) 
	// {
		// T temp = a1;
		// a1 = a2;
		// a2 = temp;  
	// }; 
  
 /***************************************************** 
  
 template <typename T>
//! \brief  Печать буфера на консоль. Для T требуется:  std::string tostr() const .
void print_buffer(const T* p, const int len) 
{
	for(int c=0; c<len; c++) 
	{
		const T* _p = (p + c);
		printf("%s\n", _p->tostr().c_str() );
	};
};

template<typename T>
/** \brief Печать содержимого вектора на консоль. Для T должен быть 
       опреденён  std::string tostr() const  * /
void print_vector(const std::vector<T>& v) 
{
	for(size_t c=0; c<v.size(); c++) 
	{
		printf("%s\n", v[c].tostr().c_str()  );
	};
};

//! \brief  Вывести буфер на консоль
 template<typename T>
 void print_list(const std::list<T>& l)
 {
 	for(std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
 	{
 		T val = *it;
 		printf( "%s\n", val.tostr().c_str()  );
 	}
 }

 *****************************************/



 template<typename T>
 /** \brief вычисление кол-ва пустых элементов в массиве p размером num. 
      Требует bool empty() const  */
 int compute_empty(const T* parray, const int num)   
 {
 	int res =0;
 	for(int c=0; c<num; c++) 
 	{
 		if( parray[c].empty() ) 
 		{
 			++res;
 		};
 	};
 
 	return res;
 }
 
 
 template<typename T>
 /** \brief вычисление кол-ва пустых элементов в  векторе. 
      Требует bool empty() const  */
 int compute_empty(const std::vector<T>& v)
 {
  if (v.empty() ) return 0;
  int res = 0;
  //const size_t NSIZE = v.size();
  for(size_t c=0; c<v.size(); c++)
  {
    if( v.at(c).empty() )
    {
    res++;
    }
  }
  return res;
 }


 // замнить мягкой сортировкой.

 template <typename T>
 /** \brief Паковать буфер. Все Непустые элементы перемещаются в начало. Конечные обнуляются.
 Требуются методы: setzero() - для обнуления элемента  и   bool empty() для проверки на "свободный" элемент.  */
 int packBufferByEmpty(T* pBuf, const int len) 
 {
	 int nCountEmpty = 0;
	 int npos = 0;
	 for(int c=0; c<len; c++) 
	 {
		 T* pcurr = (pBuf + c);

		 if( pcurr->empty() ) 
		 {
			 //empty

		 }
		 else
		 {   // not empty !
			 *(pBuf + npos   ) = *pcurr;
			 npos++;
		 }

	 }; // for

	 for(int c= len-1; c>=npos; c--) 
	 {
		 T* pcurr = (pBuf + c);
		 pcurr->setzero();
	 };

	 return len - npos;
 };


#pragma message ( "ks777 gb::t::  УДАЛИТЬ одну из findFirstEmptyFromBuffer"   __FILE__ )


 template <typename T>
 /** \brief Поиск индекса первого свободного элемента в массиве. Для T требуется: bool empty() const .
 Если не найдено то возвращает минус один.   */
 int findFirstEmptyFromBuffer(const T* pbuf, const int len) 
 {
	 for(int c=0; c<len; c++)
	 {
		 if( pbuf[c].empty() ) 
		 {
			 return c;
		 }
	 }
	 return -1;
 };					 



 //template <typename T>
 // /** \brief Аналог  FindFirstEmptyFromBuffer , но по указателю  */
 //int findFirstEmptyFromBuffer_ptr(const T* pbuf, const int len) {
	// for(int c=0; c<len; c++)
	// {
	//	 const T* pcurr = pbuf + c;
	//	 if( pcurr->empty() ) {
	//		 return c;
	//	 };
	// }
	// return -1;
 //}


 template<typename T>
 /** \brief  Перебор всех элементов массива и зануление элемента если он равен переданому val.
 для T требуются операции  == и метод зануления setzero() */
 int setZeroBufferIfAny(T buf[], const int len, const T& val) {
	 int res = 0;
	 for(int c=0; c<len; c++)
	 {
		 if( buf[c] == val) 
		 {
			 buf[c].setzero();
			 res++;
		 }
	 }

	 return res;
 }


 template<typename T>
 /** \brief  Нахождение в векторе всех элементов равных val и их обнуление  без удаления из вектора.
 Для T должен быть определён оператор:  bool == const . */
 int setzero_any_vector(  std::vector<T>& v, const T& val) 
 {
	 int res = 0;
	 for(size_t c=0; c<v.size(); c++) {
		 T& curr = v[c];
		 if( curr == val ) {
			 v[c].setzero();
			 res++;
		 };
	 };

	 return res;
 }


 template<typename T>
 /** \brief Полный сброс (зануление) массива.  Должен быть определён для T:  void setzero()    */
 void setzero_buffer( T* pbuf, const int len ) 
 {
	 for(int c=0; c<len; c++)
	 {
		 T* pcurr = (pbuf + c);
		 pcurr->setzero();
	 }
 }


 template<typename T>
 /** \brief Удаление из вектора всех элементов равных val.  
 Нееффективный способ. Рекурсия + многократное повторение. */
 bool removeFromVectorAny(  std::vector<T>& v, const T& val ) 
 {
	 int res  = 0;
	 for(std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) 
	 {
		 if( val == *it ) 
		 {
			 v.erase(it);
			 if(RemoveFromVectorAny(v, val ))
			 {
				 return true;
			 }
		 }
	 }

	 return true;
 }


 /** \brief Удаление мз вектора v всех значений равных valTobeRomoved */
 template<typename T>
 bool removeAnyFromVectorLooped(  std::vector<T>& v, const T& valTobeRomoved ) 
 {
	 bool res = false;

	 while(1)
	 {
		 bool bFound = false;

		 for(std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) 
		 {
			 if( valTobeRomoved == *it ) 
			 {
				 v.erase(it);
				 bFound = true;
				 res = true;
				 break;
			 }
		 }

		 if(!bFound) break;

	 }

	 return res;
 }



template <typename T>
/** \brief  удаление  буфера.  Для дружбы с блоком try ... catch  */
void deleteBuffer( T** ppBuf ) 
{
 if(ppBuf)
 {
   if(*ppBuf)
   {
	   T* p = *ppBuf;
	   delete[] p;
	   *ppBuf = NULL; 
   }
 }
}

 template <typename T>
 /** \brief  удаление  объекта. Для дружбы с блоком try ... catch   */
 void deleteObject( T** ppObj ) 
 {
  if(ppObj)
  {
    if(*ppObj)
    {
 	   T* p = *ppObj;
 	   delete  p;
 	   *ppObj = NULL; 
    }
   }
 }


#ifdef WIN32
template <typename T>
/** \brief Функция незащищённого по исключению освобождения  windows COM-интерфейса */
void unsafeRelease(T** pp) 
{
  if(pp)
  {
	if(*pp)
	{
		T* p = *pp;
		p->Release();
		*pp = NULL;
	}
  }
}
#endif

//-----------------------
template <typename T>
/** \brief Безопасное  освобождение объекта. Если ошибка  вернёт false  */
bool safeExceptionDelete(T** pp) 
{
	try
	{
	  deleteObject(pp);
	}
	catch(...)
	{
		return false;
	}

 return true;
}


#ifdef WIN32
template <typename T>
/** \brief Безопасное  освобождение интерфейса. Если ошибка  вернёт (-1)  */
long safeExceptionRelease(T** pp) 
{
	//__try 
	try
	{
	  unsafeRelease(pp);
	}
	//__except(1)
	catch(...)
	{
		return -1;
	}

 return 0;
}
#endif

//* \brief Выделить объект. Для дружбы с блоком try ... catch
template<typename T>
T* newObject()
{
   return new T();
}


template<typename T>
//* \brief Выделить массив. Для дружбы с блоком try ... catch
T* newArray(const size_t num)
{
   return new T [num];
}









 
// namespace sort {   }

 


//  } // end ns

//-------------------------------------------------------------------------

 } // end ns
} // end ns
// end file