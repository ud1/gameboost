 
#include "stdafx.h"

//#include <gb/base/Types.h>
#include <iostream>
#include <istream>
#include <stdlib.h>
 
#include <ce/exp/t/quad.h>

//#include <boost/array.hpp>


 
int  main()
{

	//boost::array<int,2> tarray;
	//tarray.

	t::Quad<int,4> quad;
	quad.fill(5);
	std::cout << "\n---------------------------------\n" ;
   std::cout << quad;

   // fill loops
   for(int c=0; c<4*4; c++)
   {
	   *(quad+c) = c;
   }

   std::cout << "\n-----------  source quad ---------\n" ;
   std::cout << quad;

   // rotate   right
   {
	   std::cout << "\n----------- rotate_right -------------\n" ;
	   t::Quad<int,4> qrot = quad.rotate_right();
	   std::cout << qrot;
   }

   // rotate   left
   {
	   std::cout << "\n----------- rotate_left -------------\n" ;
	   t::Quad<int,4> qrot = quad.rotate_left();
	   std::cout << qrot;
   }



	// flip horizontal
	{
		std::cout << "\n--------  flip_horizontal  -----------\n" ;
		t::Quad<int,4> qrot = quad.flip_horizontal();
		std::cout << qrot;
	}


	// flip  vertical
	{
		std::cout << "\n------  flip_vertical  -----------\n" ;
		t::Quad<int,4> qrot = quad.flip_vertical();
		std::cout << qrot;
	}




		std::cout << "\n---------------------------------\n" ;
		system("pause");
		return 0;
};
 

 