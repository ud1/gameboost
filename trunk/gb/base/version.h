/** \file
 \brief  Версия

*/

#pragma once
#include <gb/base/Types.h>
#include <stdexcept>
#include <assert.h>

#pragma warning(push)
#pragma warning(disable : 4290)
#pragma warning(disable : 4996)

namespace gb
{

namespace base 
{
//---------------------------------------------------------------

static const char CSTR_MONTH_NAMES[] = "JanFebMarAprMayJunJulAugSepOctNovDec"; 
 

   struct DATE 
   { 
	  uint32_t      year;
	  uint32_t      month;	  
      uint32_t      day;

	  DATE(uint32_t nYear, uint32_t nMonth, uint32_t nDay)
		  :	year(nYear), month(nMonth), day(nDay)   {}

	  DATE(const DATE& d) 
		  :	year(d.year), month(d.month), day(d.day) {}

	  DATE(const char* str) throw(std::runtime_error&)
	  {
	   from_cstr(str);
	  }

	  
	  bool operator == (const DATE& d) const
	  {
	    if(year  != d.year)  return false;
		if(month != d.month) return false;
		if(day   != d.day)   return false;
		  return true;
	  }
	  
	  bool operator < (const DATE& d) const 
	  {
	   if(year < d.year) return true;
	   if(month < d.month) return true;
	   if(day < d.day) return true;
	      return false;	  
	  }

	  uint32_t days() const 
	  {
	      return year*360 + month*60 + day; 
	  }


	  void from_cstr(char const *pStrDate) throw(std::runtime_error&)
	  { 
		  char s_month[5];


		  sscanf(pStrDate, "%s %d %d", s_month, &day, &year);

		  for(uint32_t c=0; c<12; c++)
			  {
			  const char* pscmp = CSTR_MONTH_NAMES + c*3 ;
			      if( strncmp(s_month , pscmp, 3 ) == 0 )
				  {
				  month = c+1;
				  break;
				  }

			  }

		  if( (month<1) || (month>12) )
		  {
			  assert(false && "bad month");
			  throw std::runtime_error("bad month");
		  }
 
 
	  }
 
   };

   struct VERSION_INFO
   {
    uint32_t      version_major;
    uint32_t      version_minor;
    uint32_t      version_build;

	VERSION_INFO(uint32_t vmajor, uint32_t vminor, uint32_t build)
		   : version_major(vmajor), version_minor(vminor), version_build(build)
	{}
   

    bool operator < (const VERSION_INFO& v) const
	{
	  if(version_major < v.version_major) return true;
	  if(version_minor < v.version_minor) return true;
	  if(version_build < v.version_build) return true;
	      return false;
	}

	bool operator == (const VERSION_INFO& v) const
	{
		if(version_major != v.version_major) return false;
		if(version_minor != v.version_minor) return false;
		if(version_build != v.version_build) return false;
		return  true;
	}

	std::string tostr() const 
	{
	 std::string res;
	 char buf[32];
	 buf[0] = '\0';
	 sprintf(buf, "%i", version_major);
	 res += buf;
	 res += ".";
	 sprintf(buf, "%02i", version_minor);
	 res += buf;
	 res += ".";
	 sprintf(buf, "%i", version_build);
	 res += buf;

	 return res;
	}
	
   };
   
   struct VERSION
   {
   
    VERSION_INFO versinf; ///< полная информация о версии
   
    DATE  date_daclare; ///< дата рождения класса
	DATE  date_modifyed; ///< дата последней модификации/добавления

	VERSION(const DATE& ddecl, 
		    const DATE& dmodif, 
			uint32_t vMajor, 
			uint32_t vMinor, 
			uint32_t vBuild 
			) 
		 : date_daclare(ddecl), date_modifyed(dmodif), versinf(vMajor, vMinor, vBuild)  {}

	VERSION(const VERSION& v)
		: date_daclare(v.date_daclare), 
		  date_modifyed(v.date_modifyed), 
		  versinf(v.versinf)  {}

   };

//-------------------------------------------------------------------



//---------------------------------------------------------------
}
}

// end file