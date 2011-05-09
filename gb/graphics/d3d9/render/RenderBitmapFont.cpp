

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


