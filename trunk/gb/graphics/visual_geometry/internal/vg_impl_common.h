/** \file 
 \brief Общие типы для реализаторов классав визуальной геометрии

*/

#ifdef GB_VG

#pragma once
#define __GB_VG_INTERNAL_COMMON_H__

namespace gb
{
namespace graphics
{
namespace visual_geometry
{
//-------------------------------------------------------------------


	//! \brief цвет для реализаторов визуальной геометрии
	class VGCOLOR  {
	public:
		float r, g, b, a;

		VGCOLOR () { r=g=b=a=1.0f; }
		inline void set(float _r, float _g, float _b, float _a)	{ r=_r; g=_g; b=_b; a=_a; }
		inline void set_rgb(float _r, float _g, float _b)	{ r=_r; g=_g; b=_b;   a=1.0f;  }

#ifdef GB_COLOR 
		inline void set(const gb::color::Color4f& c) {r=c.r; g=c.g; b=c.b; a=c.a; }
#endif

#ifdef GB_D3D9
		inline void operator = (const D3DCOLORVALUE& c) { r=c.r; g=c.g; b=c.b; a=c.a; }
#endif

		inline void setWhite() {r=g=b=a=1.0f; }
		inline void setBlack() {r=g=b=0.0f; a=1.0f; }


		inline void setRed()        {  set_rgb( 1.0f, 0.0f , 0.0f );    }
		inline void setGreen()      {  set_rgb( 0.0f, 1.0f , 0.0f );  }
		inline void setBlue()       {  set_rgb( 0.0f, 0.0f , 1.0f );    }
		inline void setYellow()     {  set_rgb( 1.0f, 1.0f , 0.0f );   }

		inline void setPink()    { set_rgb(0.737255f,  0.560784f,  0.560784f); }

		inline void setGray() { set_rgb(0.0f, 0.5f, 0.0f ); }



	};
	// end class VGCOLOR


	class VGVEC2 {
	public:
		float x, y;

		VGVEC2() {x=y=0.0f; }
		VGVEC2(const VGVEC2& v) {x=v.x; y=v.y;}
		VGVEC2(float _x, float _y) {x=_x; y=_y;}
		VGVEC2(const float* pf) {*this = pf; }
		VGVEC2(const POINT& p) { *this = p; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; }

		inline void operator = (const POINT& p) { x=(float)p.x; y=(float)p.y; }

		inline operator const float*() const {return &x;}
	};


	class VGVEC3 {
	public:
		float x, y, z;

		VGVEC3() {x=y=z=0.0f; }
		VGVEC3(const VGVEC3& v) {x=v.x; y=v.y; z=v.z;}
		VGVEC3(float _x, float _y, float _z) {x=_x; y=_y;z=_z;}
		VGVEC3(const float* pf) {*this = pf; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; z=pf[2]; }

		inline operator const float*() const {return &x;}
	};

	class VGVEC4 {
	public:
		float x, y, z, w ;

		VGVEC4() {x=y=z=w=0.0f; }
		VGVEC4(const VGVEC4& v) {x=v.x; y=v.y; z=v.z; w=v.w; }
		VGVEC4(float _x, float _y, float _z, float _w) {x=_x; y=_y;z=_z; w=_w;}
		VGVEC4(const float* pf) {*this = pf; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; z=pf[2]; w=pf[3]; }

		inline operator const float*() const {return &x;}
	};


	class VGMAT4 {
	public:
		union {
			float  _11,_12,_13,_14,   _21,_22,_23,_24,   _31,_32,_33,_34,   _41,_42,_43,_44;
			float array[16];
			float m[4][4];
		};

		VGMAT4() {}
		VGMAT4(const float* pf) { *this = pf; }



		inline void operator  = (const float* pf)
		{
			for(int c=0; c<16; c++)
			{
				array[c] = pf[c];
			}
		}

		inline operator const float* () const { return array; }
	};



//-------------------------------------------------------------------
}
}
}

#endif // #ifdef GB_VG
//end file