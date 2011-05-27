

#pragma once
#include <vector>
#include <stdexcept>

namespace t
{
	
	
	template<typename T, bool bOwned>
	/** \brief Шаблон вектор для хранения указателей. <br>
	 Второй булев параметр шаблона - удалять ли объекты в деструкторе */
	class VectorPointers : public std::vector<T*> {
	public:
		typedef const char* (*FuncVectorPointers_PtrToStr)(const T* p);

		          VectorPointers() {}	
		virtual  ~VectorPointers() 
		{
			if(bOwned) {
				remove_delete_all();
			};	
		}

		
		bool remove_delete(T* p) 
		{
			std::vector<T*>::iterator it  = find( begin(),  end(), p  );
			if(*it == p) {
				if(*it) 
				{
					delete *it;
					*it = NULL;
					erase(it);
					return true;
				}
			}

			return false;
		}

		void remove_delete_all() 
		{
			T* ptr = NULL;
			for(std::vector<T*>::iterator it = begin(); it != end(); it++ ) {
				ptr = *it;
				if(ptr)
				{
					//delete ptr;
					kst::SafeExcDelete(&ptr, true);

					*it = NULL;
				}
			}

			clear();
		}

		bool remove_setnull(T* p) 
		{
			for(std::vector<T*>::iterator it = begin(); it != end(); it++ ) 
			{
				if(*it == p) 
				{
					*it = NULL;
					erase(it);
					return true;
				}

			}
			
			return false;
		}

		void print(FuncVectorPointers_PtrToStr func, bool bInline=false) 
		{
			T* p =NULL;
			for(std::vector<T*>::iterator it = begin(); it != end(); it++ ) 
			{
				p = *it;
				printf("%s,", func(p));
				if(!bInline) { printf("\n"); };
			}
		}
 

	};
	// end class

	
} 	
	
// end file