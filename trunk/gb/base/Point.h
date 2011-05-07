/** \file
 \brief Точка

*/

#pragma once

#include <gb/Config.h>
#include <gb/base/Types.h>

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
 inline Point(const POINT& p) { *this = p; }
 inline Point(int _x, int _y) { x=_x; y=_y; }
  
 inline void init(int _x, int _y) { x=_x; y=_y; }
 
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

 inline void offset(int _x, int _y)
 {
	 x += _x;
	 y += _y;
 }

 
 


};

}
//end namespace base
}
//end namespace gb

// end file