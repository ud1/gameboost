
#pragma once


namespace t
{

	template<class T , unsigned int TSIZE>
	/** \brief Шаблон фиксированый массив . <br>
	Для сортировки требуется перегрузка оператора < : bool operator < (const T& t) const {if(*this < t) return true; return false;  };  */
	class FixedArray {
	public:

		typedef bool (* FuncForEach) (T& t, void* param  );
		typedef const char* (* FuncToStr) (const T& t, void* param  );

		FixedArray() 
		{
			int _end =0;
		}
 
		size_t size() const { return (size_t)TSIZE;  };

		/** \brief Очистка подразумевает вызов setzero() для каждого пункта */
		void clear() 
		{
			for(unsigned int c=0; c<TSIZE; c++) 
			{
				T& curr = m_arr[c];
				curr.setzero();
			}
		}

		T* ptr() { return m_arr; }

		void fill_all_looped(const T& _val) 
		{
			for(unsigned int c=0; c<TSIZE; c++) m_arr[c] = _val;
		}

		bool getFill(unsigned int index, T* ptOut) { if(index >= TSIZE) return false; *ptOut = m_arr[index]; return true; };

		bool set(unsigned int index, const T* t) {if(index >= TSIZE) return false; m_arr[index] = *t; return true; };
		bool set(unsigned int index, const T& t) {if(index >= TSIZE) return false; m_arr[index] =  t; return true; };
		void setThrow(unsigned int index, const T& t) throw (char*) {if(index >= TSIZE){ throw("illegal index"); return;} m_arr[index]=t;  };

		void set_first(const T& _t) 
		{   
		   m_arr[0] = _t;  
		}
		
		void set_last(const T& _t) 
		{   
		   m_arr[TSIZE-1] = _t;  
		}

		T& at(const unsigned int indx) throw() 
		{
		    if(indx >= TSIZE)
			{ 
			   throw("illegal index"); 
			}

		    return m_arr[indx]; 
		}
		
		const T& at(const unsigned int indx) const throw()   
		{
		    if(indx >= TSIZE)
			{ 
			   throw("illegal index"); 
			}

		    return m_arr[indx]; 
		}		
		
	 
		const unsigned int arrSize() const { return TSIZE; };

		T& operator [] (unsigned int index) throw()
		{
			if(index >= TSIZE) 
			{  
				throw("Bad index");  
			}
			
			return m_arr[index];
		}  

		const T& operator [] (unsigned int index) const throw()
		{
			if(index >= TSIZE) 
			{  
				throw  std::runtime_error("Bad index"); 
			}
			
			return m_arr[index];
		} 

		
/*
		bool forEach(FuncForEach func, void* param=NULL) 
		{
		   for(int c=0; c<TSIZE; c++) 
		   { 
		       if(!func(m_arr[c],param)) return false;	
		   } 
		   
		   return true;	
		}
		*/

		void swap(const unsigned ind1, const unsigned ind2)  throw()
		{
			if( (ind1>=TSIZE) || (ind2>=TSIZE) ) 
			{
			      throw std::runtime_error("Bad index"); 
			}
				 
			T temp;
			temp = m_arr[ind1];
			m_arr[ind1] = m_arr[ind2];
			m_arr[ind2] = temp;
		}

		void swapThrow(const unsigned ind1, const unsigned ind2) throw () 
		{
			if( (ind1>=TSIZE) || (ind2>=TSIZE) ) 
			{ 
			     throw std::runtime_error("Bad index"); 
			}
			
			T temp;
			temp = m_arr[ind1];
			m_arr[ind1] = m_arr[ind2];
			m_arr[ind2] = temp;
		};

		void shift_all_left() 
		{
		     for(unsigned int c=1; c<TSIZE; c++)
			 {
			     m_arr[c-1]  = m_arr[c];
			 }
		}

		void shift_all_right() 
		{
			 for(unsigned int c=TSIZE-1; c > 0; c--)
			 {
			    m_arr[c-1]  = m_arr[c];
			 }
		}


		void insert_shift(const unsigned int _index, const T& _val, bool bShiftBefore ) throw() 
		{
			if(_index >= TSIZE) { throw(_index); return; };
			// ?????
			
			if(bShiftBefore)  
			{
				for(int unsigned c=0; c<_num; c++) 
				{

				}

			}
			else
			{


			}

		}

 
/******************
		////    /** \brief Паковка данных. Непустые поднимаются наверх. 
		          Требует bool empty() const и void zero() 
				возвращект кол-во пустых занулёных элементов.   
		int pack() {
 
			}; // for

			for(int c= TSIZE-1; c>=npos; c--) {
				T* pcurr = (m_arr + c);
				pcurr->zero();
			};

			return TSIZE - npos;
		};
***************************/



		
		/***************************
		//! \brief Печать на консоль с функцией перевода в строку  
		void print(FuncToStr _func_, void* param ) 
		{
			for(int unsigned c=0; c<_num; c++) 
			{
			   printf("%s\n", _func_( m_arr[c], param)  );
			};
		};
		******************************/
		
		

	  operator <<  .......  /** \brief Печать на консоль с определёной функцией tostr() const */
		void print() const 
		{
			for(int unsigned c=0; c<TSIZE; c++) 
			{
				printf("%s\n",   m_arr[c].tostr()  );
			}
		}




	private:
		T m_arr[TSIZE];
	};
	// end class

	
	
}	

// end file