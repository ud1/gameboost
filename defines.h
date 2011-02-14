#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

#ifndef PMATH_ASSERT
#define PMATH_ASSERT(expression) assert(!!(expression))
#endif

#ifndef PMATH_STATIC_ASSERT
#define PMATH_STATIC_ASSERT(expression, message) static_assert( !!(expression), message )
#endif

#endif // MATH_DEFINES_H