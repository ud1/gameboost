
#pragma once
#include <stdexcept>

 //!  \todo �������� �������� cout<<

 namespace t
 {
	
	
	template <typename T , size_t TSIZE>

	//! \brief  ���� � ������������ ��������.
	class FixedStack {
	public:

	     FixedStack() :m_stackpos( -1 ) {} 
		 
	    //! \brief ���� ����? ���� ����, ����� ������� ������� (top, pop) ������� ����������.
		inline bool empty() const 
		{
           return (m_stackpos<0); 
		}

	    //! \brief ���� ����� ?  ���� �����, ����� ������� ��������� � ���� ������� ����������.
		inline bool full() const 
		{  
		   return ( m_stackpos+1>=(int)(TSIZE) ); 
		}
		
	    //! \brief �������� ������� ������ ����� (����� ��������� � �����.)
		inline size_t  size() const 
		{ 
		   return  m_stackpos+1;
		}
		
		//! \brief �������� ������������ ������ �����.
		inline size_t max_size() const { return TSIZE; }
 
		//! \brief �������� �������� val � ����. ������� ���������� ���� ���� �����.
		void push(const T& val) throw() 
		{    
			if( full() ) 
			{ 
			   throw  std::runtime_error("Stack is full");  
			}

			m_stackpos++;
	     
		  top() = val;

		}

		//! \brief ������� ���������. ������� ���������� ���� ���� ����.
		void pop() throw() 
		{ 
			if( empty() ) 
			{ 
			   throw  std::runtime_error("Stack is empty");  
			}

			m_stackpos--;
		}
		
		//! \brief �������� ������ �� �������. ������� ���������� ���� ���� ����.
		T& top() 
		{ 
		   if( empty() )
		   {
			   throw std::runtime_error("Stack is empty");
		   }

		    return m_arr [m_stackpos+1] ;
		}
		
		//! \brief �������� ����������� ������ �� �������. ������� ���������� ���� ���� ����.
		const T& top() const
		{ 
			if( empty() )
			{
				throw std::runtime_error("Stack is empty");
			}

			return m_arr [m_stackpos+1] ;
		}

		//! \brief  �������� ����.
		void clear() 
		{
			m_stackpos = -1;
		}
 
	private:

	  int m_stackpos;
	  T m_arr[TSIZE];
	
	};
	// end class




}
// end namespace t
 
 
// end file