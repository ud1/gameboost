

#if ( defined(WIN32) && defined(GB_D3D9) )

#include <gb/graphics/d3d9/render/render.h>
#include <gb/macro.h>

//! pugi xml library
#include "pugixml.hpp"

#include <string.h> 
#include <string>
#include <stdexcept>

#include <ostream>
#include <istream>
#include <iostream>
 

#include <stdlib.h>
#include <stdio.h>


#include <assert.h> 


using namespace gb::graphics::d3d9::render;
using namespace pugi;

#pragma warning (push)
#pragma warning ( disable : 4996 )

//===================================================================================
 
 
 
 

//! заголовок описания шрифта  софтины Font Builder
class FondBuilderHeader {
public:
	std::string type;

	struct description 
	{
		int size;
		std::string  family;
		std::string  style;
	};


	struct	metrics {
		int ascender;
		int height;
		int descender;
	};

	struct texture {
		int width;
		int height;
		std::string file;
	};


	//    xml header descr
	//<description size="32" family="Courier New" style="Bold"/>
	//<metrics ascender="21" height="33" descender="-8"/>
	//<texture width="256" height="128" file="courier_new_bold_32.PNG"/>



	description  m_description;
	metrics  m_metrics;
	texture   m_texture;



	FondBuilderHeader ()
	{

	}					


};




 //===============================================================
 static  bool __point_from_str(POINT& pnt,  const std::string& str)
  {
	 pnt.x = pnt.y =0;

	 int n1, n2;
	 const int nsres = sscanf(str.c_str(), "%i %i", &n1, &n2 );
	 if(nsres != 2)
	 {
		 return false;
	 }

	 pnt.x = n1;
	 pnt.y = n2;

   

	  return true;
  }


 //===============================================================
  static  bool __rect_from_str(RECT& rec,  const std::string& str)
  {
	 rec.left=rec.right=rec.top=rec.bottom=0;


	 int a1, a2, a3, a4;
	 const int NSRES = sscanf(str.c_str(), "%i %i %i %i", &a1, &a2, &a3, &a4 );
	 if(NSRES != 4)
	 {
		 return false;
	 }

	 rec.left = a1;
	 rec.right = rec.left + a3;

	 rec.top = a2;
	 rec.bottom = rec.top + a4;

	  return true;
  }

