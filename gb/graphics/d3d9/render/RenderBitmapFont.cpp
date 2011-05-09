

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



  //===============================================================
static  bool __read_from_xml_root(FondBuilderHeader& hdr, 
					  IRenderBitmapFont::CharDescrTableAnsi& table, 
					  xml_node&  root)
  {
	  xml_attribute atr = root.attribute("type");
	  if(atr.empty() )
	  {
		  return false;
	  }

	  hdr.type = atr.value();


	  // read description
	  xml_node  des =	root.child("description");
	  if(des.empty())
	  {
		  return false;
	  }

	  xml_attribute  size = des.attribute("size");
	  if(size.empty() ) 
	  {
		  return false;
	  }

	  hdr.m_description.size = size.as_int();

	  xml_attribute  family = des.attribute("family");
	  if(family.empty() ) 
	  {
		  return false;
	  }

	  hdr.m_description.family = family.value();

	  xml_attribute   style = des.attribute("style");
	  if(style.empty() ) 
	  {
		  return false;
	  }

	  hdr.m_description.style =  style.value();




	  // read metrics

	  xml_node  n_metrics  =	root.child("metrics");
	  if(n_metrics.empty() )
	  {
		  return false;
	  }

	  atr = n_metrics.attribute("ascender");
	  if(atr.empty() )
	  {
		  return false;
	  }

	  hdr.m_metrics.ascender = atr.as_int();

	  atr = n_metrics.attribute("height");
	  if(atr.empty() )
	  {
		  return false;
	  }

	  hdr.m_metrics.height = atr.as_int();

	  atr = n_metrics.attribute("descender");
	  if(atr.empty() )
	  {
		  return false;
	  }

	  hdr. m_metrics.descender = atr.as_int();




	  // read texture

	  xml_node  node =	root.child("texture");


	  atr = node.attribute("width");
	  if(atr.empty() )
	  {
		  return false;
	  }
	  hdr.m_texture.width = atr.as_int();


	  atr = node.attribute("height");
	  if(atr.empty() )
	  {
		  return false;
	  }

	  hdr.m_texture.height = atr.as_int();



	  atr = node.attribute("file");
	  if(atr.empty() )
	  {
		  return false;
	  }
	  hdr.m_texture.file  = atr.value();



	  // read  table 
	  //

	  xml_node n_chars = root.child("chars");
	  if(n_chars.empty() )
	  {
		  return false;
	  }

	  // set zero
	  memset(&table, 0, sizeof(table) );


	  xml_node n_char;
	  for( xml_node::iterator it = n_chars.begin(); it != n_chars.end(); ++it  )
	  {
 
		  n_char = *it;

		  atr = n_char.attribute("offset");
		  if(atr.empty() )
		  {
			  return false;
		  }
		  POINT point;
		  if( !__point_from_str( point, atr.value() ) )
		  {
			  // err
			  return false;
		  }

		  RECT rect;
		  atr = n_char.attribute("rect");
		  if(atr.empty() )
		  {
			  return false;
		  }
		  if( !__rect_from_str( rect, atr.value() ) )
		  {
			  // err
			  return false;
		  }


		  int nAdvance =0;
		  atr = n_char.attribute("advance");
		  if(atr.empty() )
		  {
			  return false;
		  }
		  nAdvance = atr.as_int();


		  unsigned char id = '\0';
		  atr = n_char.attribute("id");
		  if(atr.empty() )
		  {
			  return false;
		  }

		  id = (unsigned char)atr.value()[0];//   as_int();


		  //  assign to table
		  //

		  table.table[ (unsigned int)id  ].advance = nAdvance;
		  table.table[ (unsigned int)id  ].offset =   point;
		  table.table[ (unsigned int)id  ].recTexture = rect;




		//  int _end =0;
	  }
 
	  //
	  // end 


	  return true;
  }