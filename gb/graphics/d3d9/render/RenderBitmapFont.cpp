#include "d3d9pch.h"

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
#pragma warning ( disable : 4297 )

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
  
  
  //=======================================================================
  bool __load_table(const char* fname,  
					IRenderBitmapFont::CharDescrTableAnsi& tb, 
					FondBuilderHeader& hdr )
  {
	  xml_document doc ; 
	  pugi::xml_parse_result res =  doc.load_file( fname);

	  xml_node   node_font_root =  doc.first_child();  
	  if(node_font_root.empty() )
	  {
		  // not found
		  return false;
	  }

	  bool bresult  = __read_from_xml_root( hdr, tb, node_font_root);

	  return bresult;
  }

  
  
  
  
 

	#define SCREENQUADVERT_FVF (D3DFVF_XYZRHW | D3DFVF_TEX1  )


    //! \brief  сеть:  двухполигональный экранный квадрат .
	class Quad {
	public:
   	   	struct NEWSCREENQUADVERT  {
		         float x, y, z, rhw, u, v;
		     inline void set_xy(float _x, float _y) { x=_x; y=_y; z=rhw=1.0f;  }
		     inline void set_uv(float _u, float _v) { u=_u; v=_v; }
			 inline void add_uv(float _u, float _v) { u+=_u; v+=_v; }
			 inline void mul_uv(float _u, float _v) { u*=_u; v*=_v; }
	     };

		NEWSCREENQUADVERT  vertex [6];

		Quad()
		{
		    memset(vertex, 0, sizeof(vertex) );
		   vertex[0].z = vertex[0].rhw = 1.0f;
		   vertex[1].z = vertex[1].rhw = 1.0f;
		   vertex[2].z = vertex[2].rhw = 1.0f;
		   vertex[3].z = vertex[3].rhw = 1.0f;
		   vertex[4].z = vertex[4].rhw = 1.0f;
		   vertex[5].z = vertex[5].rhw = 1.0f;


			setTxCoord_default();
		}
 
		inline void setTxCoord_default()
		{
			vertex[0].set_uv(  0.0f , 0.0f );
			vertex[1].set_uv(  1.0f , 0.0f ); 
			vertex[2].set_uv(  1.0f , 1.0f );
			vertex[3].set_uv(  0.0f , 0.0f ); 
			vertex[4].set_uv(  1.0f , 1.0f );
			vertex[5].set_uv(  0.0f , 1.0f );

		}

		inline void set_TxCoordRectTx(const RECT& rec, int nTextureW, int nTextureH)
		{
			float mulx, muly;
			mulx = ( (float) (rec.right -  rec.left))  /  nTextureW  ;
			muly = ( (float) (rec.bottom - rec.top))   /  nTextureH  ;

	    	 vertex[0].mul_uv( mulx , muly  );   //  0.0f,  0.0f, 
			 vertex[1].mul_uv( mulx , muly  );   //  1.0f,  0.0f, 
			 vertex[2].mul_uv( mulx , muly  );	//  1.0f,  1.0f, 
			 vertex[3].mul_uv( mulx , muly  );	//  0.0f,  0.0f, 
			 vertex[4].mul_uv( mulx , muly  );	//  1.0f,  1.0f, 
			 vertex[5].mul_uv( mulx , muly  );	//  0.0f,  1.0f,

			 float addx, addy;
			 addx =    (float)rec.left /nTextureW   ;
			 addy =    (float)rec.top / nTextureH   ;
 
  			 vertex[0].add_uv( addx , addy  );  //  0.0f ,  0.0f, 
			 vertex[1].add_uv( addx , addy  ); 	//  1.0f ,  0.0f, 
			 vertex[2].add_uv( addx , addy  );	//  1.0f ,  1.0f, 
			 vertex[3].add_uv( addx , addy  );	//  0.0f ,  0.0f, 
			 vertex[4].add_uv( addx , addy  );	//  1.0f ,  1.0f, 
			 vertex[5].add_uv( addx , addy  );	//  0.0f ,  1.0f,
				 
 

		}

		inline void setPosRect(float x1, float y1,    float x2, float y2)
		{
 
			vertex[0].set_xy(x1 , y1);        
			vertex[1].set_xy(x2 , y1);   
			vertex[2].set_xy(x2 , y2);    
			vertex[3].set_xy(x1 , y1);    
			vertex[4].set_xy(x2 , y2);    
			vertex[5].set_xy(x1 , y2);    


		}


	
	};

	

	class QuadsBuffer {
	public:
 
		QuadsBuffer(int num) : m_num(num)
		{
		   m_pQuads = new Quad[m_num];
		}

		~QuadsBuffer()
		{
			delete[] m_pQuads;
		}

		inline void setzero() { memset(m_pQuads, 0, m_num * sizeof(Quad) ); }


		Quad* m_pQuads;
		const int m_num;
	
	};
	
	
	

	class RenderBitmapFont : public IRenderBitmapFont {
	public:
		IDirect3DDevice9* m_pdevice;
		IDirect3DTexture9* m_ptexture;
		FondBuilderHeader  m_FondBuilderHeader;
	  mutable  QuadsBuffer m_QuadsBuffer;

	   IRenderBitmapFont::CharDescrTableAnsi   m_charsDescrTable ;
	   IRenderBitmapFont::DrawOptions          m_DrawOptions;

	virtual const DrawOptions& getDrawOptions() const  
	{
		return m_DrawOptions;
	};

	virtual void  setDrawOptions(const DrawOptions& opt)   
	{
	   m_DrawOptions = opt;
	};


	   //    ПЕРВЫЙ КОНСТРУКТОР
	   RenderBitmapFont(IDirect3DDevice9* device, 
		   IDirect3DTexture9* txtr, 
		   const IRenderBitmapFont::CharDescrTableAnsi& table) throw()
		   : m_QuadsBuffer(1024)  
		{
			m_pdevice = device;
			m_ptexture = txtr;

			assert(m_pdevice);
			assert(m_ptexture);

			if( (!m_pdevice)  || (!m_ptexture) )
			{
				throw std::runtime_error("invalid args");
			}
  
			memset(&m_charsDescrTable, 0, sizeof(m_charsDescrTable) );
			m_charsDescrTable = table;
 
		}


	   //    ВТОРОЙ КОНСТРУКТОР
	   RenderBitmapFont(IDirect3DDevice9* device,  IDirect3DTexture9* txtr,
		      const char* xmlFile) throw()
		   : m_QuadsBuffer(1024)  
	   {
		   m_pdevice = device;
		   m_ptexture = txtr;

		   assert(m_pdevice);
		   assert(m_ptexture);

		   if( (!m_pdevice)  || (!m_ptexture) )
		   {
			   throw std::runtime_error("invalid args");
		   }

		   memset(&m_charsDescrTable, 0, sizeof(m_charsDescrTable) );
		 
		  if(!xmlFile)
		  {
			  throw ( std::runtime_error("invalid file")  );
		  }

		  // load 
		  if(!__load_table(xmlFile,  m_charsDescrTable,  m_FondBuilderHeader ) )
		  {
			  throw std::runtime_error("Error read file");
		  };


	   }



		virtual  ~RenderBitmapFont()
		{

		}
 

	  virtual HRESULT  DrawStr(int x, int y, const char* str ) const 
		{
			HRESULT hr =0;

			const int NSTRLEN = (int)strlen(str);
			if(NSTRLEN == 0)
			{
				return hr;
			}

			D3DMATERIAL9 mat;
			hr |= m_pdevice->GetMaterial(&mat);
			mat.Emissive.r = mat.Emissive.g = mat.Emissive.b = mat.Emissive.a;
			hr |= m_pdevice->SetMaterial(&mat);

			D3DSURFACE_DESC  des;
			hr |= m_ptexture->GetLevelDesc(0, &des);

			DWORD dwOldStateCullMode = 0;
			hr |= m_pdevice->GetRenderState(D3DRS_CULLMODE, &dwOldStateCullMode );
			hr |= m_pdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );


			hr |= m_pdevice->SetTexture(0, m_ptexture); // g_pTexture );
			

  
				 // m_DrawOptions.nSymbolsWidth
				//	m_DrawOptions.nSymbolHeight
				//  m_DrawOptions.nBetweenSymbols
 

			RECT recVertex, recTxCoord;
			SetRect(&recVertex, x, y,  x + m_DrawOptions.nSymbolsWidth, y + m_DrawOptions.nSymbolHeight );
			for(int c=0; c<NSTRLEN; c++)
			{
			  const char curr = *(str+c);

 // make rect	 old
  recVertex.left  = recVertex.left  + m_DrawOptions.nSymbolsWidth + m_DrawOptions.nBetweenSymbols;
  recVertex.right = recVertex.right + m_DrawOptions.nSymbolsWidth + m_DrawOptions.nBetweenSymbols;


  // make rect vertex
// int ofsx =  m_charsDescrTable.table[ (int)curr ].offset.x + m_charsDescrTable.table[(int)curr].advance - m_charsDescrTable.table[ (int)curr ].offset.x;
// recVertex.left = recVertex.left +	ofsx;
 //recVertex.right = recVertex.right +	ofsx;
 // int ofsy = m_charsDescrTable.table[ (int)curr ].offset.y;
 // recVertex.bottom = recVertex.top +  m_DrawOptions.nSymbolHeight;  // ofsy;


 recTxCoord = m_charsDescrTable.table[ (int)curr ].recTexture ;





 // set to quad
 m_QuadsBuffer.m_pQuads[c].setTxCoord_default();
 m_QuadsBuffer.m_pQuads[c].setPosRect( (float)recVertex.left , (float)recVertex.top , (float)recVertex.right , (float)recVertex.bottom );
 m_QuadsBuffer.m_pQuads[c].set_TxCoordRectTx(  recTxCoord ,  des.Width,  des.Height );



			}
 
   

		   //только для 0

			   // 134 3 10 17
			//SetRect(&rec,  134, 3,  134+10  , 3+17    );
			//m_pQuads[0].set_TxCoordRectTx(rec, des.Width, des.Height );
 

			// set data
			hr |= m_pdevice->SetFVF( SCREENQUADVERT_FVF );  
			hr |= m_pdevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, NSTRLEN*2, (void*)m_QuadsBuffer.m_pQuads, sizeof( Quad::NEWSCREENQUADVERT ) );

			 // restore
			hr |= m_pdevice->SetRenderState(D3DRS_CULLMODE,  dwOldStateCullMode );	


			return hr;
		}



	};
	
	



//=================================================================
GB_D3D9_API HRESULT  gb::graphics::d3d9::render::CreateRenderBitmapFontInterface(
		IRenderBitmapFont** ppOut,  
		IDirect3DDevice9* pdevice,	
		IDirect3DTexture9* pBitmapTexture, 
		const IRenderBitmapFont::CharDescrTableAnsi& table  )
 
{
	HRESULT hr =S_OK;

	assert(ppOut);
	if(!ppOut)
	{
		return E_FAIL;
	}

 
   *ppOut = NULL;

   try {
   *ppOut = (IRenderBitmapFont*) new RenderBitmapFont(pdevice, pBitmapTexture, table);
   }
   catch(...)
   {
	 delete	 *ppOut;

	   hr |= E_FAIL; // | ERROR_EX
   }

   

	return hr;
};

#undef SCREENQUADVERT_FVF




//========================================================================
GB_D3D9_API HRESULT  gb::graphics::d3d9::render::CreateRenderBitmapFontInterfaceFromXmlFileA(   
			IRenderBitmapFont** ppOut, IDirect3DDevice9* pdevice,	
			IDirect3DTexture9* pBitmapTexture,  const char* sXmlFileFontDescr  )
{
 HRESULT hr =0;

 assert(ppOut);
 if(!ppOut)
 {
	 return E_FAIL;
 }


 *ppOut = NULL;

  RenderBitmapFont* pfont = NULL;

 try {
	 pfont =  new RenderBitmapFont(pdevice, pBitmapTexture, sXmlFileFontDescr );

 }
 catch(...)
 {
	  GB_SAFE_DEL_OBJ(pfont);

	 hr |= E_FAIL; 
 }





   *ppOut = (IRenderBitmapFont*)pfont;

 return hr;
};



//========================================================================

#pragma warning (pop)


#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file
	
	