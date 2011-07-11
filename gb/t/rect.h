

#pragma once

#include <gb/base/Point.h>
#include <boost/array.hpp>
#include <assert.h>


namespace gb
{

 namespace t
 {



	 template <typename T, size_t TNumColumns, size_t TNumRows >
	 class  rect	{
	 public:

		 typedef boost::array<T,TNumColumns>  row_type;
		 typedef boost::array<row_type,TNumRows> _rows;
		 //row_type _rows[TNumRows];

		 T& at(size_t nColumn, size_t nRow) throw (std::runtime_error)
		 {
			 if( (nColumn>=TNumColumns) || (nRow>=TNumRows) )
			 {
				 throw std::runtime_error("bad index");
			 }

			 return _rows[nRow][nColumn];
		 }

		 row_type& get_row(size_t nrow)
		 {
			 return _rows[nrow];
		 }


	 };



 }

}
