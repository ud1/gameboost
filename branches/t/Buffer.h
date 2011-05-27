

#pragma once
#include <stdexcept>

namespace t
{



	template <typename T>
	//! \brief ѕростой шаблон дл€ динамического массива.
	class Buffer {
	public:
	
	   Buffer(unsigned long _size)
	   {
		     m_ptr = NULL;
		     m_size = _size;
			 if(m_size)
			 {
			  m_ptr = new t [m_size];
			 }
	   }
	   
	   
	   //virtual 
	   ~Buffer()
	   {
		     if(m_ptr)
			 {
			  delete [] m_ptr;
			  m_ptr = NULL;
			 }
	   }
	   
	   inline unsigned long size() const 
	   {
			return m_size;
	   }
	   
	   void realloc(unsigned long _size)
	   {
		     if(m_ptr)
			 {
			  delete [] m_ptr;
			  m_ptr = NULL;
			  m_size = 0;
			 }
			 
			 m_size = _size;
			 if(m_size)
			 {
			  m_ptr = new T [m_size];
			 }
	   }
	   
	   void check_realloc(unsigned long _size)
	   {
		    if(m_size<_size)
			{
			 realloc(_size);
			}
	   
	   }
	   
	   inline void zero()  throw()
	   {
	     if(!m_ptr)
		 {
		   throw std::runtime_error("null pointer");	
		 }
		 
	     memset(m_ptr, 0, sizeof(T) * m_num );
	   }
	   
	   inline const T&  operator [] (const size_t index) const 
	   {
		      if( (index<0) || (index>=(size_t)m_size) )
			  {
			    throw std::runtime_error("bad index");
			  }
			  
			  if(!m_ptr)
			  {
			    throw std::runtime_error("null pointer");		  
			  }
			  
			  return *(m_ptr + index);
	   }
	   
	   inline operator bool() const 
	   {
			return (m_ptr != NULL);
	   }


	protected:
		unsigned long m_size;
		T* m_ptr;


	private:
	
	// операторы присваивани€ дл€ буфера запрещены.
	
	void operator = (const Buffer<t> a) {}
	void operator = (T* p) {}


	};



} 

// end file