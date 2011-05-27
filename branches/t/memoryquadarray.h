/** \file
 \brief Шаблон двухмерный буфер

*/

#pragma once

#include <ostream>
#include <stdexcept>


#pragma warning(push)
#pragma warning(disable : 4297)
 
	template<class T>
	//! \brief  Шаблон двухмерный буфер
	class MemoryQuadArray {
	public:
	
		//! \brief  координата на массиве
		struct  Coord 
		{
			  int colNumber; 
			  int rowNumber;
		}; 

		MemoryQuadArray(const unsigned int numColumns, const unsigned int numRows) 
							//: m_numcols(numColumns), m_nunrows(numRows)  
		{
		    m_ptr = NULL;
			realloc(numColumns, numRows);
		}

		// нужен ли виртуал ...... ?????
		virtual ~MemoryQuadArray() 
		{ 
		   if(m_ptr) 
		   { 
		      delete[] m_ptr; 
			  m_ptr = NULL;
		   } 
		}

		//! \brief ПОлучить размер буфера в байтах
		inline unsigned int getMemBufNumBytes() const 
		{
           return ( (m_nunrows + m_numcols) * sizeof(T) ); 
		}

		inline void fillmem( char value )
		{
			memset(m_ptr, value, sizeof(T) * m_numcols * m_nunrows );
		}
		
		void realloc(const unsigned int numColumns, const unsigned int numRows)
		{
			 if(m_ptr)
			 {
			   delete [] m_ptr;
			   m_ptr = NULL;
			 }
			 
			 m_nunrows = nunRows;
			 m_numcols = numColumns;
			 
			 m_ptr = new T [ m_nunrows * m_numcols ];
		}

		/*************
		inline   T& operator () (unsigned int colNumber, unsigned int rowNumber) 
		{
			if(  rowNumber > m_nunrows-1 ) 
			{ 
				throw std::runtime_error("Bad index"); 
			}
			if(  colNumber > m_numcols-1 ) 
			{ 
				throw std::runtime_error("Bad index"); 
			}

			return   *( m_ptr  + colNumber + (  rowNumber * m_numcols ) ); 
		}
		**********************/
		
		inline T operator [] (const Coord coord) const
		{
		
		   return   *( m_ptr  + coord.col + (  coord.row * m_numcols ) ); 
		}

		//! \brief xxxxxxxxxxxxxxxxxx
		inline const T& operator () (const unsigned int col, const unsigned int row) const throw()  
		{
			if(row>m_nunrows-1) 
			{ 
				throw std::runtime_error("Bad index"); 
			}
			if(col>m_numcols-1) 
			{ 
				throw std::runtime_error("Bad index"); 
			}
			
			return   *( m_ptr  + col + (  row * m_numcols ) ); 
		}

		//! \brief xxxxxxxxxxxxxxxx
		inline T& operator ()(const unsigned int col, const unsigned int row) throw() 
		{
			if(row>m_nunrows-1) 
			{ 
			   throw(row);
			}
			
			if(col>m_numcols-1) 
			{ 
			   throw(col);
			}
			
			return *( m_ptr  + col + ( row * m_numcols ) ) ;
		}

		inline void fill(const T& t) 
		{
			for(unsigned int c=0; c<(m_nunrows * m_numcols); c++) 
			{
				*(m_ptr + c) = t; 
			}
		}



		inline void fill_row(const unsigned numRow, const T& t) throw() 
		{
			if(numRow>m_nunrows-1) 
			{ 
			    throw( std::runtime_error("Bad index") );   
			}
			
			for(unsigned int c=0; c<m_numcols; c++) 
			{
				*( m_ptr + c + (numRow * m_numcols) ) = t;
			}
		}

		inline void fill_col(const unsigned numCol, const T& t) throw() 
		{
			if(numCol>m_numcols-1) 
			{ 
			   throw( std::runtime_error("Bad index") ); 
			}
			
			for(unsigned int c=0; c<m_nunrows; c++) 
			{
				*( m_ptr + numCol + (c * m_numcols) ) = t;
			}
		};

		//! \brief  Обмен значений строк
		void swap_rows(const unsigned int r1, const unsigned int r2) throw() 
		{
			if( (r1>m_nunrows-1) || (r2>m_nunrows-1) ) 
			{ 
			  throw( std::runtime_error("Bad index") );
			}
 
			register T temp;
			for(unsigned int c=0; c<m_numcols; c++) 
			{
				temp = *( m_ptr + c + (r1 * m_numcols) ) ;
				*( m_ptr + c + (r1 * m_numcols) )   =   *( m_ptr + c + (r2 * m_numcols) ) ;
				*( m_ptr + c + (r2 * m_numcols) ) = temp;
			}

		}

		//! \brief  Обмен занчений колонн.
		void swap_cols(const unsigned int c1, const unsigned int c2) throw() 
		{
			if( (c1>m_numcols-1) || (c2>m_numcols-1) ) 
			{ 
				throw(c1); return; 
			}
 
			register T temp;
			for(unsigned int c=0; c<m_nunrows; c++) 
			{
				temp = *( m_ptr + c1 + (c * m_numcols));
				*( m_ptr + c1 + (c * m_numcols) )   =   *( m_ptr + c2 + (c * m_numcols) ) ;
				*( m_ptr + c2 + (c * m_numcols) ) = temp;
			}
 
		}
		
 

		inline unsigned int num_columns() const 
		{
			return m_numcols;
		}

		inline unsigned int num_rows() const 
		{
			return m_nunrows;
		}

		inline operator const T* () const 
		{
			return m_ptr;
		}

		inline operator T* ()  
		{
			return m_ptr;
		}
		
		inline operator void*()
		{
		  return (void*)m_ptr;
		}

 		//! \brief  Отладочный вывод в консоль .
		friend std::ostream& operator << (std::ostream&os, const MemoryQuadArray<T>& mqa) 
		{  
			unsigned int ncol = 0;
			for( unsigned int c=0; c< mqa.num_columns() * mqa.num_rows(); c++  )
			{
				T val  = *( mqa.pointer() + c)  ;
				os <<  val;
				os << " ";

				ncol ++;
				if(ncol>=mqa.num_columns() )
				{
					os << '\n';
					ncol = 0;
				}

			}

			os << '\n';
			return os;
		}



protected:


		inline T getUnsafe(const unsigned int col, const unsigned int row) const 
		{
			return *( m_ptr + col + (row * m_numcols) );
		}

		inline void setUnsafe(const unsigned int col, const unsigned int row, const T& t) 
		{
			*( m_ptr + col + (row * m_numcols) ) = t;
		}		
	
		

	private:
		  unsigned int m_nunrows;
		  unsigned int m_numcols;
		T* m_ptr;


	};
	// end class



#pragma warning(pop)

// end file