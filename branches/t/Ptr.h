

#pragma once

#include <stdexcept.h>

namespace t
{

	template <class T>
	
	//! \brief  ПРостой шаблон указателя на объект (НЕ ДЛЯ МАССИВОВ).
	class Ptr {
	public:

	    Ptr() 
		{
		  m_ptr = NULL;
		}
		
		Ptr(T* _ptr)
		{ 
		   m_ptr = _ptr;
		}
		
		explicit Ptr(const Ptr<T>& p)
		{
		   m_ptr = p.m_ptr;
		}
		
		inline T* operator -> () const 
		{
		   if(!m_ptr) throw std::runtime_error("null pointer");
		   return m_ptr;
		}
		
		inline T operator * () const 
		{
		   if(!m_ptr) throw std::runtime_error("null pointer");
		   return *m_ptr;		
		}
		
		inline operator bool () const 
		{
			return m_ptr != NULL;
		}
		
		inline operator = (T* p)
		{
		  m_ptr = p;
		}
		
		inline void operator = (Ptr<T>& p)
		{
		  m_ptr = p.m_ptr;
		}
		
		inline bool operator == (Ptr<T>& p) const 
		{
			return m_ptr == p.m_ptr;
		}
		
		inline bool operator == (const T* p) const 
		{
			return m_ptr == p;
		}		
		
		inline bool operator != (Ptr<T>& p) const 
		{
			return m_ptr != p.m_ptr;
		}
		
		inline bool operator != (const T* p) const 
		{
			return m_ptr != p;
		}		
		
		
		
		

		
	protected:
	 T* m_ptr;

	private:

	// закрытые действия
	
	T* operator + (const int i) const 
	{
	 return m_ptr + i;
	}
	 
	T* operator - (const int i) const 
	{
	 return m_ptr - i;
	}	 
	 
	 
	 
	};


}


// end file