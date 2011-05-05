/** \file
 \brief Определения, типы функции и прочее для  D3D9 FVF
*
*
*
*
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once
#define __GB_D3D9_FVF_H__

#pragma warning(push)
#pragma warning (disable : 4995)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <string>

#include <gb/graphics/d3d9/common.h>




namespace gb 
{
 namespace graphics 
 {
  namespace d3d9 
  {

   //! \brief Определения, типы функции и прочее для  D3D9 FVF
   namespace fvf
   {
		 
//-------------------------------------------------------------------------
	

	   typedef DWORD   FVF;
	

	   
/** \brief Структура для фейса  */
struct face_vertex_s {

  WORD n1, n2, n3; 

  inline void toCstr(char* buf) const 
  {
	  sprintf(buf, "%u %u %u", (unsigned int)n1, (unsigned int)n2, (unsigned int)n3 );
  };

  inline bool fromCstr(const char* s) 
  {
	  unsigned int _n1, _n2, _n3;
	    const int SCANRES = sscanf(s, "%u %u %u", &_n1, &_n2, &_n3 );
	  if(3 != SCANRES)  return false;
	    n1 = (WORD)_n1;  n2 = (WORD)_n2; n3 = (WORD)_n3;
     return true;
  };


};
 


   //! \brief Вершина  только координата  xyz  (без прочих данных параметров)  
   struct vertex_xyz_s {

	   float x, y, z;

	   static inline DWORD get_fvf() { return  D3DFVF_XYZ; };
	   inline void make(float _x, float _y, float _z) {x=_x; y=_y; z=_z; };

	   std::string tostr() const 
	   {
		     char buf[64];
		    toCstr(buf);
		    std::string res = buf;
		    return res;
	   };

	   inline void toCstr(char* buf) const 
	   {
		   sprintf(buf, "%f %f %f", x, y, z);
	   };



	   inline bool fromCstr(const char* s) 
	   {
		   const int SCANRES = sscanf(s, "%f %f %f",   &x, &y, &z);
		   if(SCANRES != 3) return false;
		   return true;
	   };


   };
 



   /** \brief  Вершина для xyz + текстурная координата.   */
   struct vertex_xyz_txcoord1_s {

	   float x, y, z,
		   u, v;

	   static inline DWORD get_fvf() { return (D3DFVF_XYZ | D3DFVF_TEX1); };

	   inline void make(float _x, float _y, float _z, float _u, float _v) {x=_x; y=_y; z=_z; u=_u; v=_v; };
	   inline void make_xyz(float _x, float _y, float _z) {x=_x; y=_y; z=_z;};
	   inline void make_uv(float _u, float _v) { u=_u; v=_v; };

	   inline void toCstr(char* buf) const 
	   {
		   sprintf(buf, "%f %f %f     %f %f", x, y, z,  u, v);
	   };

	   bool fromCstr(const char* s) {
		   const int SCANRES = sscanf(s, "%f %f %f    %f %f", &x, &y, &z,  &u, &v );
		   if(SCANRES != 6) return false;
		   return true;
	   };

	   const char* toCstr_vertex_xyz(char* buf) const
	   {
		   sprintf(buf, "%f %f %f", x, y, z);
	   };

	   inline void toCstr_uv(char* buf) const 
	   {
		   sprintf(buf, "%f %f", u, v );
	   };

	   inline bool fromCstr_vertex_xyz(const char* s)  
	   {
		   int nres = sscanf(s, "%f %f %f", &x, &y, &z);
		   if(3 != nres) return false;
		   return true;
	   };

	   inline bool fromCstr_uv(const char* s) 
	   {
		   int nres = sscanf(s, "%f %f", &u, &v );
		   if(2 != nres) return false;
		   return true;
	   };


   };

 

//!  \brief Вершина для: вершина xyz + нормаль + текстурная координата    
struct vertex_xyz_normal_txcoord1_s {
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	static inline DWORD get_fvf() { return  (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1); };

	inline void toCstr(char* buf) const 
	{
	   sprintf(buf, "%f %f %f      %f %f %f      %f %f",  x, y, z, nx, ny, nz, u, v );
	};

	inline bool fromCstr(const char* s) 
	{
		const int SCANRES = sscanf(s,"%f %f %f  %f %f %f  %f %f",  &x, &y, &z, &nx, &ny, &nz, &u, &v  );
		if( SCANRES !=  8)  return false;
		return true;
	};

	inline void  toCstr_vertex_xyz(char* buf) const 
	{
		sprintf( buf, "%f %f %f", x, y, z);
	};

	inline void  toCstr_normal_xyz(char* buf) const 
	{
		sprintf(buf, "%f %f %f", nx, ny, nz);
	};

	inline void  toCstr_txcoord(char* buf) const 
	{
		sprintf(buf, "%f %f", u, v );
	};

	inline bool fromCstr_vertex_xyz(const char* s)  
	{
	   const int nres = sscanf(s, "%f %f %f", &x, &y, &z);
       if(3 != nres) return false;
	   return true;
	};

	inline bool fromCstr_normal_xyz(const char* s)  
	{
		const int nres = sscanf(s, "%f %f %f", &nx, &ny, &nz);
		if(3 != nres) return false;
		return true;
	};

	inline bool fromCstr_txcoord(const char* s) 
	{
		const int nres = sscanf(s, "%f %f", &u, &v );
		if(2 != nres) return false;
	    return true;
	};



};

      

//!  \brief Вершина для: xyz + диффузный цвет   
struct vertex_xyz_color_s	 {
	float x, y, z; 
	DWORD color;

   static inline DWORD get_fvf() { return (D3DFVF_XYZ | D3DFVF_DIFFUSE); };

   const char* toCstr_vertex_xyz(char* buf) const 
   {
	  sprintf(buf, "%f %f %f", x, y, z);
   };

   bool fromCstr_vertex_xyz(const char* s)  
   {
	   const int NSCAN = sscanf(s, "%f %f %f", &x, &y, &z);
	   if(3 != NSCAN) return false;
	   return true;
   };

   inline void toCstrHex_color(char* buf) const 
   {
	   sprintf(buf, "%8X", color);	   
   };

   bool fromCstr_color(const char* s) 
   {
	  const int SCANRES = sscanf(s, "%8X", &color);  
	  if(1 != SCANRES) return false; 
	  return true;   
   };


};



 

/**  \brief Трансформирования в экр. координаты     
     вершина  состоящая из: xy + текстурн. координата   */
struct  vertex_xyzrhw_txcoord1_s {
   float x, y, z, rhw;
   float u, v;

   static inline DWORD get_fvf() { return (D3DFVF_XYZRHW | D3DFVF_TEX0); };

   inline void make(float _x, float _y, float _u, float _v ) {x=_x; y=_y;  u=_u; v=_v; z = rhw = 0.0f;  };

   inline void toCstr_xy(char* buf) const 
   {
	   sprintf(buf, "%f %f", x, y);	   
   };

   inline bool fromCstr_xy(const char* s) 
   {
	  int SCRES = sscanf(s, "%f %f", &x, &y );
	  if(2 != SCRES) return false;
      return true;	   
   };

   inline void toCstr_txcoord(char* buf) const 
   {
	   sprintf(buf, "%f %f", u, v );
   };


   bool fromCstr_txcoord(const char* s) 
   {
	   int nres = sscanf(s, "%f %f", &u, &v );
	   if(2 != nres) return false;
	   return true;
   };


};

 

//!  \brief Вершина состоящая из :  xyz + диф. цвет + текстурные координаты   
struct vertex_xyz_color_txcoord1_s {
	float x, y, z; 
	DWORD color;
	float u, v;

  static inline DWORD get_fvf() { return (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0); };

  inline void make(float _x, float _y, float _z, DWORD _color, float _u, float _v ) 
  {
	  x=_x; y=_y; z=_z;   color = _color; u = _u; v = _v;
  };

  inline void  toCstr(char* buf) 
  {
	 sprintf(buf, "%f %f %f  %8X  %f %f", x, y, z, color, u, v );	  
  };

  inline bool fromCstr(const char* s) 
  {
	  const int SCANRES = sscanf(s, "%f %f %f    %8X     %f %f", x, y, z, color, u, v   );
	  if(6 != SCANRES ) return false;
      return true;	  
  };

  inline void  toCstr_txcoord(char* buf) const 
  {
	   sprintf(buf, "%f %f", u, v );
  };


  inline bool fromCstr_txcoord(const char* s) 
  {
	   const int NSCRES = sscanf(s, "%f %f", &u, &v );
	   if(2 != NSCRES) return false;
	   return true;
  };


};




		 
		 
		 
		 
		 
//-------------------------------------------------------------------------
		 
   } // end ns fvf
  } // end ns d3d9
 } // end ns graphics
} // end ns gb


#pragma warning(pop)

#endif
// end file