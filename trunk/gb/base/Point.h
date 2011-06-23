/** \file
 \brief Точка

*/

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>
#include <stdlib.h>
#include <string>

namespace gb
{

namespace base 
{

//! \brief Точка
class Point {
public:

  int x;
  int y;
 
 inline Point() { x=y=0; }
 inline Point(const Point& p) { x=p.x; y=p.y; }

#ifdef _WINDOWS_
 inline Point(const POINT& p) { *this = p; }
#endif

 inline Point(int _x, int _y) { init(_x,_y);  }
  
 inline void init(int _x, int _y) { x=_x; y=_y; }
 
#ifdef _WINDOWS_

 inline void operator = (const POINT& p) 
 {
	 x = p.x;
	 y = p.y;
 }
 
 inline operator POINT() const 
 {
   POINT res = {x,y};
   return res;
 }

#endif
 
 inline Point operator + (const Point& p) const 
 {
   return Point( x+p.x , y+p.y );
 }
 
 inline Point& operator += (const Point& p)  
 {
   x += p.x;
   y += p.y;
   return *this;
 } 

 inline Point operator - (const Point& p) const 
 {
	 return Point( x-p.x , y-p.y );
 }

 inline Point& operator -= (const Point& p)  
 {
	 x -= p.x;
	 y -= p.y;
	 return *this;
 } 

#pragma warning(push)
#pragma warning(disable : 4996)

 std::string tostr() const
 {
   char buffer [32];
   sprintf(buffer, "%i %i", x, y);
   std::string res = buffer;
   return res; 
 }

 bool fromstr(const std::string& str)
 {
	 const int NSCANRES = sscanf(str.c_str(), "%i %i", &x, &y);
	 if(NSCANRES != 2) return false;
	 return true;
 }
 
#pragma warning(pop)

};

}
//end namespace base
}
//end namespace gb

// end file