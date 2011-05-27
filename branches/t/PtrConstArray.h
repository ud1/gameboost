

#pragma once
#include <stdexcept>

namespace t
{
		
	template <typename T> 
	//! \brief Шаблон для хранения константного указателя на массив (const T* ptr).
	class PtrConstArray {
	public:

		const T* ptr;  ///< Указатель на первый элемент
		const unsigned int num;	///< размер массива

		explicit PtrConstArray(const T* _ptr, unsigned int _num) : ptr(_ptr), num(_num) {};
		explicit PtrConstArray(const PtrConstArray<T>& pac) : ptr(pac.ptr), num(pac.num) {};

		//! \brief  get array   
		inline operator const T*() const { return ptr; }
		//! \brief  get array memory size in bytes	 
		inline unsigned int  mem_size() const { return sizeof(T) * num; }
		//!** \brief 	безопасный доступ 
		T operator [] (const unsigned int indx) 
		{
			if(indx>=num) 
			{ 
				std::runtime_error( C_STRERR_INVALID_INDEX ); 
			}
			return *(ptr + indx);
		}
	};

}	

// end file