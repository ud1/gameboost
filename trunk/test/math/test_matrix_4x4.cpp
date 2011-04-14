

#include "stdafx.h"

#include <gb/math/math.h>
#include <d3dx9math.h>

#include <stdio.h>

void print_m(const D3DXMATRIX& m)
{
 printf("\n%f  %f  %f  %f  \n  %f  %f  %f  %f  \n%f  %f  %f  %f  \n%f  %f  %f  %f  \n  ", 
	 m._11, m._12, m._13, m._14, 
	 m._21, m._22, m._23, m._24,
	 m._31, m._32, m._33, m._34,	 
	 m._41, m._42, m._43, m._44	 
	 );
};

void print_div()
{
printf("\n-----------------------------------\n");
}

#define MDX  D3DXMATRIX
#define MGB  gb::math::base::mat44_s


int _tmain(int argc, _TCHAR* argv[])
{
  MDX mdx;
  MGB mgb;
  D3DXMatrixIdentity(&mdx);

  print_div();
  print_m(mdx);

    print_div();
	mgb.reset();
	mgb.print();



system("pause");
	return 0;
}

