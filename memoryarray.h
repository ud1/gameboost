
#pragma once
xzxcczczxczxc


	template <class T>
	/** \brief шаблон массив в памяти   */
	class MemoryArray {
	public:

		MemoryArray(unsigned int _num) : m_num(_num) 
		{ 
		    m_ptr = new T[m_num]; 
		}
		
		virtual ~MemoryArray() 
		{  
			if(m_ptr) 
			{  
				delete [] m_ptr; 
			}	 
		}

		//! \brief безопастный доступ к элементу
		T& operator [] (const unsigned int index) throw() 
		{
			if(index > m_num-1) 
			{ 
			  throw std::runtime_error("Bad index");
			}
			
			t = *(m_ptr + index);
			return t;
		};

		//! \brief безопастный доступ к элементу констунте
		const T& operator [] (const unsigned int index) const throw() 
		{
			if(index > m_num-1) 
			{ 
			  throw std::runtime_error("Bad index");
			}
			
			t = *(m_ptr + index);
			return t;
		}	

		//! \brief получить размер буфера.
		inline const size_t size() const 
		{ 
		    return (size_t)m_num; 
		}
		
		//! \brief размер буфера в байтах .
		inline const unsigned int numBytes() const 
		{ 
		    return ( m_num * sizeof(T) ; 
		}		
 
		
		// inline  operator const T*() const 
		// { 
		    // return m_ptr; 
		// }
		
		// inline  operator  T*()  
		// { 
		    // return m_ptr; 
		// }		
		
		//! \brief  присвоить первому.
		inline void set_first(const T& t) 
		{ 
		    *m_ptr = t; 
		}
		
		//! \brief присвоить последнему.
		inline void set_last (const T& t)
		{ 
		    *(m_ptr + m_num-1) = t; 
		}
 
		//! \brief залить буфер значением t . 
		void fill(const T& t) 
		{
			for(unsigned int c=0; c<m_num; c++) 
			{ 
				*(m_ptr + c) = t;
			}
		}

		//! \brief Безопастный обмен знаячений по индексам n1  n2 .
		void swap(const unsigned int n1, const unsigned int n2) throw() 
		{
			if( (n1 > m_num-1) || (n2 > m_num-1) ) 
			{ 
			    throw("Bad index"); 
			}

			register T temp;
			temp = *(m_ptr + n1);
			*(m_ptr + n1) = *(m_ptr + n2);
			*(m_ptr + n2) = temp;
		}



		/** \brief Проверка на размер с пересозданием. 
		  Если размер меньше чем n то буфер будет пересоздан с новым размером n */
		void check_realloc(const unsigned int n ) 
		{
		    if(m_num < n)
			{
			    if(m_ptr)
				{
				   delete[] m_ptr;
				   m_ptr = NULL;
				}

			    m_num = n;

			   m_ptr = new T[m_num];
			}
		}
 				   
		//! \brief Сдвиг содержимого вниз (к последнему элементу) Последний элемент теряется
		void shift_down() 
		{
			for(unsigned int c=m_num-1; c>0; c--) 
			{
				 *( m_ptr + c ) = *( m_ptr + c - 1 );
			}
		}

		//! \brief Сдвиг содержимого вверх (к первому элементу) Первый элемент теряется
		void shift_up() 
		{
			for(unsigned int c=0; c<m_num-1; c++) 
			{
				 *( m_ptr + c   )  =  *( m_ptr + c + 1 ) ;
			}
		}
 

    protected:

		inline const T&     getUnsafe(const unsigned int index)              
		{ 
  		    return *(m_ptr + index);      
		}
		
		inline void         setUnsafe(const unsigned int index, const T& t)   
		{         
		    *(m_ptr + index) = t;  
		}

		void swap_unsafe(const unsigned int n1, const unsigned int n2) 
		{
			register T temp;
			temp = *(m_ptr + n1);
			*(m_ptr + n1) = *(m_ptr + n2);
			*(m_ptr + n2) = temp;

		}		
		
	private:
		const unsigned int m_num;
		T* m_ptr;
	}; 


