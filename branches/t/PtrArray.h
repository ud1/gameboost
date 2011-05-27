
#pragma once
#include <stdexcept>


namespace t
{


	template<typename T>
	/** \brief Шаблон просто указатель на массив */
	class PtrArray {
	public:
		inline const unsigned int num() const 
		{ 
			return m_len;
		}
		
		inline T* ptr() const 
		{ 
			return m_ptr; 
		}
		
		inline operator T* () const { return m_ptr; }

		explicit  PtrArray(T* _ptr, const unsigned int _len) 
		{
  		    m_ptr = _ptr; 
			m_len = _len; 
		}
		
		 PtrArray(const PtrArray& _arr) 
		 { 
		    m_ptr = _arr.m_ptr; 
			m_len = _arr.m_len; 
		 }
 
		//!  \brief Сколько памяти в байтах занимает массив 
		inline unsigned int mem_size() const { return m_len * sizeof(T); };

	private:
		T* m_ptr;
	   unsigned int m_len;
	};

	
}	
	
// end file