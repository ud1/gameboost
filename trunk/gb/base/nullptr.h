#pragma once

// nullptr for gcc < 4.6 version
#if defined(__GNUC__)
#if __GNUC__ == 4 && __GNUC_MINOR__ < 6
#define DEFINE_NULLPTR 1
#endif
#endif

// nullptr for msvc < 2010
#if defined(_MFC_VER)
#if _MFC_VER < 0x0A00
#define DEFINE_NULLPTR 1
#endif
#endif

#ifdef DEFINE_NULLPTR
const // this is a const object...
class
{
public:
	template<class T> // convertible to any type
	operator T*() const // of null non-member pointer...
	{
		return 0;
	}
	
	template<class C, class T> // or any type of null
	operator T C::*() const // member pointer...
	{
		return 0;
	}
	
private:
  void operator&() const; // whose address can't be taken
} nullptr = {}; // and whose name is nullptr
#endif

#undef DEFINE_NULLPTR
