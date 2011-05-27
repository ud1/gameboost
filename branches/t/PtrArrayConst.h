

#pragma once
#include <stdexcept>

namespace t
{

	template <typename T> 
	/** \brief Шаблон для хранения константного указателя на массив (T* const ptr). */
	class PtrArrayConst {
	public:

		T* const ptr;  ///< pointer constant to array
		const unsigned int num;	///< array num elements

		explicit PtrArrayConst(T* const _ptr, unsigned int _num) : ptr(_ptr), num(_num) {};
		explicit PtrArrayConst(const PtrArrayConst<T>& pac) : ptr(pac.ptr), num(pac.num) {};

		//! \brief  get array pointer  
		inline operator T* const () const 
		{ 
		   return ptr; 
		}
		
		//! \brief  get array memory size in bytes
		inline unsigned int mem_size() const 
		{ 
		    return sizeof(T) * num; 
		}
		
		//! \brief 	get element operator 
		T& operator [] (const size_t index) 
		{
			if(index>=num) 
			{ 
				std::runtime_error( C_STRERR_INVALID_INDEX ); 
			}
			
			return *(ptr + index);
		}
		
		//! \brief 	get element const operator		
		const T& operator [] (const size_t index) const
		{
			if(index>=num) 
			{ 
				std::runtime_error( C_STRERR_INVALID_INDEX ); 
			}
			
			return *(ptr + index);
		}		
		
		
		
	};
	
}	

// edn file