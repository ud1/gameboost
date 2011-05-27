

#pragma once
#include <stdexcept>

namespace t
{
		
	template <typename T> 
	//! \brief ������ ��� �������� ������������ ��������� �� ������ (const T* ptr).
	class PtrConstArray {
	public:

		const T* ptr;  ///< ��������� �� ������ �������
		const unsigned int num;	///< ������ �������

		explicit PtrConstArray(const T* _ptr, unsigned int _num) : ptr(_ptr), num(_num) {};
		explicit PtrConstArray(const PtrConstArray<T>& pac) : ptr(pac.ptr), num(pac.num) {};

		//! \brief  get array   
		inline operator const T*() const { return ptr; }
		//! \brief  get array memory size in bytes	 
		inline unsigned int  mem_size() const { return sizeof(T) * num; }
		//!** \brief 	���������� ������ 
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