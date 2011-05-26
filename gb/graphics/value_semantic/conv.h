

#pragma once

#include <string>

#include <gb/graphics/value_semantic/enums.h>

namespace gb
{
namespace graphics
{
namespace value_semantic
{ 

//----------------------------------------------------------------------


/*
 std::string  float_type_tostr(const float_type_e::e val);
 bool float_type_fromstr(const float_type_e::e& valOut, const std::string& s);
 */

 std::string  matrix4x4_type_e_tostr(const matrix4x4_type_e::e val);
 bool         matrix4x4_type_e_fromstr(matrix4x4_type_e::e& valOut, const std::string& str);






//----------------------------------------------------------------------
}
}
}

// end file