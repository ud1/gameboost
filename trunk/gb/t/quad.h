

#pragma once

#include <gb/base/Point.h>
#include <boost/array.hpp>
#include <assert.h>

namespace gb
{

 namespace t
 {


	 template <typename T, size_t TSize>
	 class  quad	{
	 public:

		 typedef boost::array<T,TSize>  line_type;
		 typedef boost::array<line_type, TSize> _rows;
		// line_type _rows[TSize];

		 T& at(size_t ncolumn, size_t nrow) throw (std::runtime_error)
		 {
			 if( (ncolumn>=TSize) || (nrow>=TSize) )
			 {
				 throw std::runtime_error("bad index");
			 }

			 return _rows[nrow][ncolumn];
		 }

		 line_type& get_row(size_t nrow)
		 {
			 return _rows[nrow];
		 }


	 };


 }

}
