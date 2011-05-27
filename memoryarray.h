
#pragma once
xzxcczczxczxc


	template <class T>
	/** \brief ������ ������ � ������   */
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

		//! \brief ����������� ������ � ��������
		T& operator [] (const unsigned int index) throw() 
		{
			if(index > m_num-1) 
			{ 
			  throw std::runtime_error("Bad index");
			}
			
			t = *(m_ptr + index);
			return t;
		};

		//! \brief ����������� ������ � �������� ���������
		const T& operator [] (const unsigned int index) const throw() 
		{
			if(index > m_num-1) 
			{ 
			  throw std::runtime_error("Bad index");
			}
			
			t = *(m_ptr + index);
			return t;
		}	

		//! \brief �������� ������ ������.
		inline const size_t size() const 
		{ 
		    return (size_t)m_num; 
		}
		
		//! \brief ������ ������ � ������ .
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
		
		//! \brief  ��������� �������.
		inline void set_first(const T& t) 
		{ 
		    *m_ptr = t; 
		}
		
		//! \brief ��������� ����������.
		inline void set_last (const T& t)
		{ 
		    *(m_ptr + m_num-1) = t; 
		}
 
		//! \brief ������ ����� ��������� t . 
		void fill(const T& t) 
		{
			for(unsigned int c=0; c<m_num; c++) 
			{ 
				*(m_ptr + c) = t;
			}
		}

		//! \brief ����������� ����� ��������� �� �������� n1  n2 .
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



		/** \brief �������� �� ������ � �������������. 
		  ���� ������ ������ ��� n �� ����� ����� ���������� � ����� �������� n */
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
 				   
		//! \brief ����� ����������� ���� (� ���������� ��������) ��������� ������� ��������
		void shift_down() 
		{
			for(unsigned int c=m_num-1; c>0; c--) 
			{
				 *( m_ptr + c ) = *( m_ptr + c - 1 );
			}
		}

		//! \brief ����� ����������� ����� (� ������� ��������) ������ ������� ��������
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


