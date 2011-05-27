 
#include "stdafx.h"

//#include <gb/base/Types.h>
#include <iostream>
#include <istream>
#include <stdlib.h>

namespace t 
{


template <typename T, size_t TSIZE>

struct Quad {

	//! \brief  ���� � ���������.
	inline operator T*() 
	{
		return &m_array[0][0];
	}

	//! \brief ���� � ������������ ��������.
	inline operator const T*()  const
	{
		return &m_array[0][0];
	}

    Quad<T,TSIZE> operator + (const T& value)
	{
	  Quad<T,TSIZE> res = *this;
	  for(size_t i=0; i<size(); i++)
	  {
		  for(size_t j=0; j<size(); j++)
		  {
			  res.m_array [i][j] += value;
		  }
	  }
	  return res;
	}

	Quad<T,TSIZE> operator - (const T& value)
	{
		Quad<T,TSIZE> res = *this;
		for(size_t i=0; i<size(); i++)
		{
			for(size_t j=0; j<size(); j++)
			{
				res.m_array [i][j] -= value;
			}
		}
		return res;
	}

	Quad<T,TSIZE> operator * (const T& value)
	{
		Quad<T,TSIZE> res = *this;
		for(size_t i=0; i<size(); i++)
		{
			for(size_t j=0; j<size(); j++)
			{
				res.m_array [i][j] *= value;
			}
		}
		return res;
	}

	Quad<T,TSIZE> operator / (const T& value)
	{
		Quad<T,TSIZE> res = *this;
		for(size_t i=0; i<size(); i++)
		{
			for(size_t j=0; j<size(); j++)
			{
				res.m_array [i][j] /= value;
			}
		}
		return res;
	}



	//! \brief �������� ������ ������� �������� (�� ����� ���-�� ���������). ����� ���-�� ��������������: 2*size()
   size_t size() const
   {
	   return TSIZE;
   }

   //! \brief �����������  ������ � ��������
   const T& at(size_t col, size_t row) const throw()
   {
	   if( (col>=TSIZE) || (col<0) || (row>=TSIZE) || (row<0) )
	   {
		   throw std::runtime_error("bad index");
	   }
	   return m_array[row][col];
   }

   //! \brief �������������  ������ � ��������
   T& at(size_t col, size_t row) throw()
   {
	   if( (col>=TSIZE) || (col<0) || (row>=TSIZE) || (row<0) )
	   {
		   throw std::runtime_error("bad index");
	   }
	   return m_array[row][col];
   }

   //! \brief ��������� ������ ��������� value
   void fill(const T& value)
   {
	   for(size_t i=0; i<size(); i++)
	   {
		   for(size_t j=0; j<size(); j++)
		   {
			   m_array [i][j] = value;
		   }
	   }
   }

   //! \brief �������� ������� � �������� ���������  � ��������� �������.
   Quad<T,TSIZE>  rotate_right() const
   {
	   Quad<T,TSIZE> res;
	   for(int c=0; c<TSIZE; c++)
	   {
		   for(int j=0; j<TSIZE; j++)
		   {
			   res.m_array[c][TSIZE-1-j] =  m_array[j][c];
		   }
	   }
	   return res;
   }

   //! \brief �������� ������� � �������� ���������  � ��������� ������.
   Quad<T,TSIZE>  rotate_left() const
   {
	   Quad<T,TSIZE> res;
	   for(int c=0; c<TSIZE; c++)
	   {
		   for(int j=0; j<TSIZE; j++)
		   {
			   res.m_array[TSIZE-1-j][c] =  m_array[c][j];
		   }
	   }
	   return res;
   }

   // \brief   ����������� (��������) �� �����������
   Quad<T,TSIZE>  flip_horizontal() const
   {
	   Quad<T,TSIZE> res;
	   for(int c=0; c<TSIZE; c++)
	   {
		   for(int j=0; j<TSIZE; j++)
		   {
			   res.m_array[c][TSIZE-1-j] =  m_array[c][j];
		   }
	   }
	   return res;
   }

   //! \brief   ����������� (��������) �� ���������
   Quad<T,TSIZE>  flip_vertical() const
   {
	   Quad<T,TSIZE> res;
	   for(int c=0; c<TSIZE; c++)
	   {
		   for(int j=0; j<TSIZE; j++)
		   {
			   res.m_array[TSIZE-1-j][c] =  m_array[j][c];
		   }
	   }
	   return res;
   }





	//! \brief  ���������� ����� � ������� .
	friend std::ostream& operator << (std::ostream&os, const Quad<T,TSIZE>& qd) 
	{  
		unsigned int ncol = 0;
		for( size_t c=0; c< qd.size() * qd.size(); c++  )
		{
			T val  = *( qd + c)  ;
			os <<  val;
			os << "  ";

			ncol ++;
			if(ncol>=qd.size() )
			{
				os << '\n';
				ncol = 0;
			}

		}

		os << '\n';
		return os;
	}



protected:
   T m_array [TSIZE][TSIZE] ;

};

}

// end file