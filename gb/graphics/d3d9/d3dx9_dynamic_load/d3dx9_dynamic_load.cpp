#include "stdafx.h"

#if ( defined(WIN32) && defined(GB_D3D9) )


#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>

#include <stdlib.h>
#include <assert.h>

namespace  gb
{
namespace  graphics
{
namespace  d3d9
{
namespace d3dx9_dynamic_load
{

 

//====================================================================
GB_D3D9_API void  makeD3DX9dllFilename_by_version(std::string& strOut, unsigned int vers, bool bDebugV)
{
  strOut = "";
  strOut += "d3dx9";
  
  if(bDebugV)
  {
    strOut += "d";
  }

  strOut += "_";
  
  char buf [32];
  sprintf( buf , "%02i" , vers );
  strOut += buf;
  strOut += ".dll";

  // temp mon
  if(vers<10)
  {
   int _stop =0;
  }
 
}

//====================================================================
GB_D3D9_API bool checkDllExistsA (const char* fname, bool bIncludeExeDir)   
{    
    return ::GetFileAttributesA(fname) != DWORD(-1);
}
 

//====================================================================
GB_D3D9_API bool checkExistsDll(const char* sDllFilename)
{
   std::string sfullpath ;
   char bufsysdir[MAX_PATH];
 
  if(! ::GetSystemDirectoryA(bufsysdir, MAX_PATH ))
  {
   throw (std::runtime_error("system error"));
  }
  
  sfullpath = bufsysdir;
  sfullpath += '\\';
  sfullpath += sDllFilename;
  
  if( checkDllExistsA(sfullpath.c_str(), true ) )
  {
    return true;
  
  }  
 
   return false;
}

//====================================================================
GB_D3D9_API bool getInstaledD3DXlastVersion(unsigned int* piOutVers)
 {
   *piOutVers  =0;
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	   *piOutVers = cvers;
	   return true;
	  }

  } 
 
    return false;
}

//====================================================================
GB_D3D9_API void print_d3dx9_dll_info()
{
	std::string str;
  for( int c=50; c>=0; c-- )
  {
	makeD3DX9dllFilename_by_version( str, ( unsigned int )c  );
	if(  checkExistsDll (str.c_str() ) )
	{
	
	  printf( str.c_str() );
	  printf("\n");
	}

  
  }

 
   printf("\n   END. \n");
}

//====================================================================
GB_D3D9_API bool getInstaledD3DXallVersion(std::vector<unsigned int>& versions)
 {
   bool result = false;
	versions.clear();
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	    versions.push_back(cvers);
	   result =  true;
	  }

  } 
 
    return  result;
 }

//====================================================================
GB_D3D9_API HMODULE loadDllLastVersion(unsigned int* piOutVers )
{
 
	if(piOutVers) *piOutVers = 0;
   if( !getInstaledD3DXlastVersion( piOutVers ) )
   {
   
     return 0;
   }
   
   std::string dllfname;
   makeD3DX9dllFilename_by_version(dllfname, *piOutVers );
   
   HMODULE hm = 0 ;
   hm = ::LoadLibraryA(dllfname.c_str() );
   if(hm)
   {
    /// error load.  none
   }

   return hm;
}  




//==================================================================== 
 
 
//==================================================================== 
 

//====================================================================

}
}
}
}

//===============

#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file