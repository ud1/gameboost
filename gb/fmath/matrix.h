

#pragma once

#include <boost/array.hpp>

namespace gb
{

namespace fmath
{

template <typename T, size_t NumColumns, size_t NumRows>
struct matrix : public boost:array< T , NumColumns * NumRows > {
  /// ....
};

template <typename T, size_t N>
struct matrix_quad : public  matrix<T,N*N>{
  /// ....
}; 


template <typename T>
matrix2x2 : public matrix_quad<T,2>{
  /// ....
};

template <typename T>
matrix3x3 : public matrix_quad<T,3>{
  /// ....
};

template <typename T>
matrix4x4 : public matrix_quad<T,4>{
 /// ....
};








}

}

