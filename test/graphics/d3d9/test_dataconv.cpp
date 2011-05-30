
#include <d3d9.h>
#include <gb/graphics/d3d9/auto_include_libr.h>
#include <gb/graphics/d3d9/dataconv/dataconv.h>
using namespace gb::graphics::d3d9::dataconv;


 
 
 void test()
 {
 
 #error ƒŒƒ≈À¿“‹ “≈—“!!
 
 
 std::string str;
 
   str =   D3DFORMAT_tostr( const D3DFORMAT format,bool bShortWord=false);

 
  if(D3DFORMAT_fromstr(D3DFORMAT& fOut,  const std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }

	//====================
 
   str =    D3DRESOURCETYPE_tostr(const D3DRESOURCETYPE val,bool bShortWord=false);

 
  if(! D3DRESOURCETYPE_fromstr( D3DRESOURCETYPE&  rOut, const std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str =   D3DRENDERSTATETYPE_tostr(const D3DRENDERSTATETYPE val,bool bShortWord=false);

 
  if(!  D3DRENDERSTATETYPE_fromstr(  D3DRENDERSTATETYPE& val, std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str =   D3DRENDERSTATEVALUE_tostr(const D3DRENDERSTATETYPE state, const DWORD val,bool bShortWord=false  );

 
   if(!  D3DRENDERSTATEVALUE_fromstr(DWORD &val, const D3DRENDERSTATETYPE state, const std::string &s ) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str =   D3DPOOL_tostr(const D3DPOOL val,bool bShortWord=false);

 
  if(!  D3DPOOL_fromstr( D3DPOOL& val, const  std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
  	//====================
 
   str =    D3DFILLMODE_tostr(const D3DFILLMODE val,bool bShortWord=false); 

 
  if(!   D3DFILLMODE_fromstr( D3DFILLMODE& valOut, const std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }	 
	//====================
 
   str = D3DSHADEMODE_tostr(const D3DSHADEMODE val,bool bShortWord=false); 

 
  if(!   D3DSHADEMODE_fromstr( D3DSHADEMODE& valOut, const  std::string& str,bool bShortWord=false) ) 
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str = D3DBLEND_tostr(const D3DBLEND   val,bool bShortWord=false) ;

 
  if(!  D3DBLEND_fromstr(D3DBLEND& valOut,  const std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str = D3DCULL_tostr(const D3DCULL val,bool bShortWord=false);



  if(!   D3DCULL_fromstr(D3DCULL& valOut, const std::string& str,bool bShortWord=false) )
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
 	//====================
   str =  D3DCMPFUNC_tostr( const D3DCMPFUNC val,bool bShortWord=false);

 
    if(!  D3DCMPFUNC_fromstr ( D3DCMPFUNC& valOut, const std::string& str,bool bShortWord=false);
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str = D3DFOGMODE_tostr(const D3DFOGMODE val,bool bShortWord=false);


 
  bool D3DFOGMODE_fromstr(  D3DFOGMODE& valOut, const std::string& str,bool bShortWord=false);
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 
   str =  D3DSTENCILOP_tostr(const D3DSTENCILOP val,bool bShortWord=false); 

 
  bool D3DSTENCILOP_fromstr( D3DSTENCILOP& valOut, const std::string& str,bool bShortWord=false);
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
  
	//====================
   str = D3DMATERIALCOLORSOURCE_tostr(const D3DMATERIALCOLORSOURCE val,bool bShortWord=false);
   
   
   bool        D3DMATERIALCOLORSOURCE_fromstr(D3DMATERIALCOLORSOURCE &val, const std::string &s,bool bShortWord=false);
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
	//====================
 

   std::string  D3DTEXTUREADDRESS_tostr(const D3DTEXTUREADDRESS val,bool bShortWord=false);
  bool D3DTEXTUREADDRESS_fromstr( D3DTEXTUREADDRESS& valOut, const std::string& str,bool bShortWord=false);
  {
    printf("ERROR ! \n");
  }
  else
  {
      printf("OK \n");
  }
  	//====================
	
   std::string  D3DTEXTUREFILTERTYPE_tostr(const D3DTEXTUREFILTERTYPE val,bool bShortWord=false); 
  bool D3DTEXTUREFILTERTYPE_fromstr( D3DTEXTUREFILTERTYPE& valOut, const std::string& str,bool bShortWord=false);

	//====================  
  
   std::string  D3DTEXTUREOP_tostr(const D3DTEXTUREOP val,bool bShortWord=false); 
  bool D3DTEXTUREOP_fromstr( D3DTEXTUREOP& valOut, const std::string& str,bool bShortWord=false);

  	//====================
  
   std::string  D3DTEXTURESTAGESTATETYPE_tostr(const D3DTEXTURESTAGESTATETYPE val,bool bShortWord=false); 
  bool D3DTEXTURESTAGESTATETYPE_fromstr( D3DTEXTURESTAGESTATETYPE& valOut, const std::string& str,bool bShortWord=false);

	//====================  
  
   std::string  D3DTEXTURETRANSFORMFLAGS_tostr(const D3DTEXTURETRANSFORMFLAGS val,bool bShortWord=false); 
  bool D3DTEXTURETRANSFORMFLAGS_fromstr( D3DTEXTURETRANSFORMFLAGS& valOut, const std::string& str,bool bShortWord=false);

	//====================  
  
   std::string  D3DTRANSFORMSTATETYPE_tostr(const D3DTRANSFORMSTATETYPE val,bool bShortWord=false); 
  bool D3DTRANSFORMSTATETYPE_fromstr( D3DTRANSFORMSTATETYPE& valOut, const std::string& str,bool bShortWord=false);

	//====================  
  
   std::string  D3DVERTEXBLENDFLAGS_tostr(const D3DVERTEXBLENDFLAGS val,bool bShortWord=false); 
  bool D3DVERTEXBLENDFLAGS_fromstr( D3DVERTEXBLENDFLAGS& valOut, const std::string& str,bool bShortWord=false);

	//====================  
  
   std::string  D3DZBUFFERTYPE_tostr(const D3DZBUFFERTYPE val,bool bShortWord=false); 
  bool D3DZBUFFERTYPE_fromstr( D3DZBUFFERTYPE& valOut, const std::string& str,bool bShortWord=false);

	//====================

   std::string  D3DPRIMITIVETYPE_tostr(const D3DPRIMITIVETYPE val,bool bShortWord=false); 
  bool D3DPRIMITIVETYPE_fromstr( D3DPRIMITIVETYPE& valOut, const std::string& str,bool bShortWord=false);



   std::string D3DSAMPLER_TEXTURE_TYPE_tostr(const D3DSAMPLER_TEXTURE_TYPE val,bool bShortWord=false); 
  bool D3DSAMPLER_TEXTURE_TYPE_fromstr( D3DSAMPLER_TEXTURE_TYPE& valOut, const std::string& str,bool bShortWord=false);


   std::string  D3DSAMPLERSTATETYPE_tostr(const D3DSAMPLERSTATETYPE val,bool bShortWord=false); 
   bool D3DSAMPLERSTATETYPE_fromstr( D3DSAMPLERSTATETYPE& valOut, const std::string& str,bool bShortWord=false);


   std::string  D3DSTATEBLOCKTYPE_tostr(const D3DSTATEBLOCKTYPE val,bool bShortWord=false); 
   bool D3DSTATEBLOCKTYPE_fromstr( D3DSTATEBLOCKTYPE& valOut, const std::string& str,bool bShortWord=false);

   std::string  D3DSWAPEFFECT_tostr(const D3DSWAPEFFECT val,bool bShortWord=false); 
   bool D3DSWAPEFFECT_fromstr( D3DSWAPEFFECT& valOut, const std::string& str,bool bShortWord=false);



   std::string  D3DDECLTYPEtostr(const D3DDECLTYPE val,bool bShortWord=false); 
  bool D3DDECLTYPE_fromstr( D3DDECLTYPE& valOut, const std::string& str,bool bShortWord=false);

   std::string  D3DDECLMETHOD_tostr(const D3DDECLMETHOD val,bool bShortWord=false); 
  bool D3DDECLMETHOD_fromstr( D3DDECLMETHOD& valOut, const std::string& str,bool bShortWord=false);

 

 }
 
 


int main()
{
	//dc::D3DBLEND_fromstr()


	return 0;
}