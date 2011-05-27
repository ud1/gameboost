
#pragma once
#include <stdexcept>

 //!  \todo добавить перегруз cout<<

 namespace t
 {
	
	
	template <typename T , size_t TSIZE>

	//! \brief  Стек с фиксированым размером.
	class FixedStack {
	public:

	     FixedStack() :m_stackpos( -1 ) {} 
		 
	    //! \brief Стек пуст? Если пуст, тогда попытка извлечь (top, pop) вызовет исключение.
		inline bool empty() const 
		{
           return (m_stackpos<0); 
		}

	    //! \brief Стек полон ?  Если полон, тогда попытка помещения в стек вызовет исключение.
		inline bool full() const 
		{  
		   return ( m_stackpos+1>=(int)(TSIZE) ); 
		}
		
	    //! \brief ПОлучить текущий размер стека (число элементов в стеке.)
		inline size_t  size() const 
		{ 
		   return  m_stackpos+1;
		}
		
		//! \brief Получить максимальный размер стека.
		inline size_t max_size() const { return TSIZE; }
 
		//! \brief ПОложить значение val в стек. Бросает исключение если стек полон.
		void push(const T& val) throw() 
		{    
			if( full() ) 
			{ 
			   throw  std::runtime_error("Stack is full");  
			}

			m_stackpos++;
	     
		  top() = val;

		}

		//! \brief удалить последнее. Бросает исключение если стек пуст.
		void pop() throw() 
		{ 
			if( empty() ) 
			{ 
			   throw  std::runtime_error("Stack is empty");  
			}

			m_stackpos--;
		}
		
		//! \brief Получить ссылку на вершину. Бросает исключение если стек пуст.
		T& top() 
		{ 
		   if( empty() )
		   {
			   throw std::runtime_error("Stack is empty");
		   }

		    return m_arr [m_stackpos+1] ;
		}
		
		//! \brief Получить константную ссылку на вершину. Бросает исключение если стек пуст.
		const T& top() const
		{ 
			if( empty() )
			{
				throw std::runtime_error("Stack is empty");
			}

			return m_arr [m_stackpos+1] ;
		}

		//! \brief  Очистить стек.
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