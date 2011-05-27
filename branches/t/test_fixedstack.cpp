#include "stdafx.h"

#include <ce/exp/t/fixedstack.h>

#include <stdio.h>
#include <stdlib.h>

typedef   gb::t::FixedStack<int,8> TIntFixStack;

 TIntFixStack     g_fstack;


void print_info( const TIntFixStack& stk )
{
 printf("\n--------------------\n");
 printf("\n  size: %i \n" , g_fstack.size() );

  if( stk.empty() )
  {
   printf(" stack empty \n" );
  }
  else
  {
     printf(" stack NOT empty \n" );
  }


  if( stk.full() )
  {
     printf(" stack FULL \n" );
  }
  else
  {
    printf(" stack  not full \n" );
  }




}


int main()
{
  print_info(g_fstack);


 g_fstack.push(0);

   print_info(g_fstack);


 g_fstack.push(1);
  g_fstack.push(2);
 g_fstack.push(3);
 g_fstack.push(4);
 g_fstack.push(5);
 g_fstack.push(6);
 g_fstack.push(7);
     print_info(g_fstack);

   g_fstack.push(6);






 
     print_info(g_fstack);

  system("pause");
	return 0;
}