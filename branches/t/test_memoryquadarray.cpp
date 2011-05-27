#include "stdafx.h"

#include <ce/exp/t/memoryquadarray.h>
#include <ostream>
#include <istream>
#include <iostream>

 void print_info(const MemoryQuadArray<int>& q)
 {

 }

 void print_quad(const MemoryQuadArray<int>& q)
 {
	 unsigned int ncol = 0;
  for( unsigned int c=0; c< q.num_columns()*q.num_rows(); c++  )
  {
	  int val = 0;
	  val = *(q.pointer() + c)  ;
	  printf( "%i " , val );

	  ncol ++;
	  if(ncol>=q.num_columns() )
	  {
		  printf("\n");
		  ncol = 0;
	  }

  }

    printf("\n------------------\n");

 }


int main()
{
   MemoryQuadArray<int> quad(3,12);
  std::cout << quad <<  std::endl;


   quad.fill(0);
   std::cout << quad << std::endl ;

   for(unsigned int c=0; c<( quad.num_columns() * quad.num_rows() ); c++)
   {
	   *( quad.pointer() + c  ) = c;
   }
  std::cout << quad <<  std::endl;

  quad.fill_col(1, 9);
  std::cout << quad <<  std::endl;


  quad.fill_row(3, 0);
   std::cout << quad << std::endl;


  //   set
 quad(2,2) = 66;
   print_quad(quad); 
   
   // get
 int res = quad(2,2);



 std::cout << quad << std::endl;

  system("pause");

	return 0;
}