d3dx9_undef   = 0 ,
d3dx9_24,
d3dx9_25,
d3dx9_26,
d3dx9_27,
d3dx9_28,
d3dx9_29,
d3dx9_30,
d3dx9_31,
d3dx9_32,
d3dx9_33,
d3dx9_34,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,
d3dx9_xxxxxx,

int getVersion()

/** \brief   Получить файл d3dx dll по номеру версии   */
void  makeD3DXdllFilename_by_version(std::string& strOut, int vers)
{
  strOut = "";
  strOut += "d3dx9_";
  
  char buf [32];
  sprintf( buf , "%i" , vers );
  strOut += buf;
  strOut += ".dll";
 
}
 
bool checkExistsDll(const char* sDllFilename)
{
   std::string sfullpath ;
   char bufsysdir[MAX_PATH];
  if(! ::GetSystemDir(bufsysdir))
  {
   throw (tsd::runtime_error("system error"));
  }
  
  sfullpath = bufsysdir;
  sfullpath += sDllFilename;
  
  if( FileExests(sDllFilename.c_str() ) )
  {
    return true;
  
  }  
 
   return false;
}
 
 
 bool getInstaledD3DXlastVersion(int* piOutVers)
 {
   *piOutVers  =0;
 
  std::string fname;
  for(cvers=45; cvers>0; cvers--)
  {
    makeD3DXdllFilename_by_version(fname , cvers);
	  if( !checkExistsDll( cvers ) )
	  {
	   *piOutVers = cvers;
	   return true;
	  }

  } 
 
    return false;
 }
 
 
HMODULE loadDllLastVersion(int* piOutVers=NULL)
{
    int vers = 0;
	if(piOutVers) *piOutVers = 0;
   if( !getInstaledD3DXlastVersion(&vers) )
   {
   
     return 0;
   }
   
   std::string dllfname;
   makeD3DXdllFilename_by_version(dllfname, vers );
   
   HMODULE hm = ::LoadLibraryA(dllfname.c_str() );
   if(hm)
   {
    /// error load.  none
   }

   return hm;
}  
 
 
//////////////////////////////////////////////

typedef HRESULT (__stdcall *TFunc_xxx)(int arg);
 

 
 typedef BOOL (__stdcall *TFunc_D3DXCheckVersion)(UINT D3DSDKVersion, UINT D3DXSDKVersion);
 
 
 
 //////////////////// general purpose function ////////////////////
 
 
 typedef HRESULT (__stdcall *TFunc_D3DXCreateBuffer)( DWORD NumBytes, LPD3DXBUFFER * ppBuffer);
 
 
 
 
 
 
 
 typedef HRESULT  (__stdcall *TFunc_D3DXCreateFont)(
  LPDIRECT3DDEVICE9 pDevice,
  INT Height,
  UINT Width,
  UINT Weight,
  UINT MipLevels,
  BOOL Italic,
  DWORD CharSet,
  DWORD OutputPrecision,
  DWORD Quality,
  DWORD PitchAndFamily,
  LPCTSTR pFacename,
  LPD3DXFONT * ppFont
);


 typedef HRESULT (__stdcall *TFunc_D3DXCreateFontIndirect)(
  LPDIRECT3DDEVICE9 pDevice,
  CONST D3DXFONT_DESC * pDesc,
  LPD3DXFONT * ppFont
);

 
 typedef HRESULT (__stdcall *TFunc_D3DXCreateLine)(
  LPDIRECT3DDEVICE9 pDevice,
  LPD3DXLINE* ppLine
);

 typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToEnvMap)(
  LPDIRECT3DDEVICE9 pDevice,
  UINT Size,
  UINT MipLevels,
  D3DFORMAT Format,
  BOOL DepthStencil,
  D3DFORMAT DepthStencilFormat,
  LPD3DXRENDERTOENVMAP * ppRenderToEnvMap
);

 typedef HRESULT (__stdcall *TFunc_D3DXCreateRenderToSurface)(
  LPDIRECT3DDEVICE9 pDevice,
  UINT Width,
  UINT Height,
  D3DFORMAT Format,
  BOOL DepthStencil,
  D3DFORMAT DepthStencilFormat,
  LPD3DXRENDERTOSURFACE * ppRenderToSurface
);


 typedef HRESULT (__stdcall *TFunc_D3DXCreateSprite)(
  LPDIRECT3DDEVICE9 pDevice,
  LPD3DXSPRITE * ppSprite
);


 typedef HRESULT (__stdcall *TFunc_D3DXDebugMute)(
  BOOL Mute
);


 typedef HRESULT (__stdcall *TFunc_D3DXGetDriverLevel)(
  LPDIRECT3DDEVICE9 pDevice
);




///////////////// d3dxmesh /////////////////////





