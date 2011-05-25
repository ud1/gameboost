//#include "stdafx.h"

#include <gb/base/ini.h>
//#include "ksut_ini.h"
#include <gb/str/String.h>

//#include "ksut.h"

#pragma warning( disable : 4290 )
#pragma warning( disable : 4996 )

namespace gb 
{
namespace base
{
namespace ini
{

	//==================================================================


//===========================================
//	IniSection
//===========================================

//===========================================
bool  IniSection::addKeyValue(const  IniKeyValue& kv) 
{
	if(isKeyExests(kv.m_skey)) 
	{
		// error. key exists
		return false;
		};


	m_vector_keyval.push_back(kv); 
	return true;
};

//===========================================================
bool  IniSection::searchKey(  int& index , const std::string& sKey) const 
{
	index = -1;
	if(m_vector_keyval.size() == 0) return false;

	for(int c=0; c<(int)m_vector_keyval.size(); c++)
		{
		const IniKeyValue& kv = m_vector_keyval.at(c);
		if(kv.m_skey == sKey)   {
			// found !
			index = c;
			return true;
			};

		};

  return false;	
};

//================================================================
bool  IniSection::isKeyExests(const std::string& sKey) 
{
	int indx = -1;
	
	if( !searchKey(indx, sKey) ) {
		return false;
		};

  return true;	
};

//===================================================
 IniKeyValue&  IniSection::getKeyValueByIndex(const int index) throw(std::runtime_error&) 
{
    if( (index >= (int)m_vector_keyval.size() )  || (index<0) ) {
	 // error
		throw::std::runtime_error("Invalid index");
		static int INVALID =0;
		return (IniKeyValue&)INVALID;
	};

   IniKeyValue& res = m_vector_keyval.at(index);
	
   return res;	
};

//================================================================
const  IniKeyValue&  IniSection::getKeyValueByIndex (const int index) const throw(std::runtime_error&)
{

    if( (index >= (int)m_vector_keyval.size()) || (index<0) ) {
	 // error
		throw::std::runtime_error("Invalid index");
		static int INVALID =0;
		return (const  IniKeyValue&)INVALID;
	};

   const  IniKeyValue& res = m_vector_keyval.at(index);
	
   return res;	
};



//
//   Ini
//

//===================================================
bool  Ini::searchSection(  int& index, const std::string& sSection) const
{
   index = -1;
	if(m_vector_sections.size() == 0) return false;
	
	for(int c=0; c<(int)m_vector_sections.size() ; c++)
		{
		const  IniSection& sect = m_vector_sections.at(c);
		   if(sect.getSectionName() == sSection) {
			 // found !
			   index = c;
			   return true;
			};
		
		};
 return false;	
};

//===================================================
bool  Ini::isSectionExists(const std::string& sSection) const 
{
	 int index = -1;
	 if( !searchSection(index, sSection ) )
		 {
		  // not found !
		 return false;
		 };
	
	return true;
};

//=================================================
 IniSection*  Ini::addSection(const std::string& sSection) {
	IniSection sect(sSection);
	m_vector_sections.push_back(sect);

	 IniSection* psect =
		&m_vector_sections.at( m_vector_sections.size() - 1 );


  return 	psect;
};

//=======================================================
 IniSection&    Ini::getSectionByIndex(const int index) throw(std::runtime_error&)
{
	if(index >=(int)m_vector_sections.size() )
		{
		// error
		throw std::runtime_error("invalid index");

		};
	
	 IniSection& res = m_vector_sections.at(index);

	return res;
};

//===========================================================
const  IniSection&   Ini::getSectionByIndex( const int index   ) const throw(std::runtime_error&)
{
	if(index >=(int)m_vector_sections.size() )
		{
		throw std::runtime_error("invalid index");
		}
	
	const  IniSection& res = m_vector_sections.at(index);

	return res;	
};

//================================================================
bool  Ini::preprocessString(std::string& str) const {
		std::string sres = "";

		bool bSymbolFound = false;
		for(int c=0; c<(int)str.length(); c++) {

			if(str[c] == ';') {
				// comment found !!
				break;
				};
			

			if(!bSymbolFound) {

			      if(  (str[c] == ' ') || (str[c] == '\t') || (str[c] == '\r') )
				  {
				     continue;
				  };

			 };

		  // current valid symbols
		  bSymbolFound = true;

		   if(bSymbolFound) {
				sres += str[c];
				
				};


			
		};   // for

		str = sres;

   return true;
};

//=================================================================
bool  Ini::parseKeyValueString(  std::string& s_OutKey, 
						   std::string& s_OutValue,
						 const std::string& src ) const 
{
		s_OutKey = ""; s_OutValue = "";

	const size_t SLEN = src.length();
	if(SLEN == 0) return false;

	int nDivPos =  -1; // position '='

	// read key
	//
	for(size_t c=0; c<SLEN; c++)
		{
		if(  (src[c] == '\t') || (src[c] == ' ') || (src[c] == '\r') )
			continue;

		if( src[c] == '=' )
			{
			// found 
			nDivPos = (int)c;
			break;
			}


		s_OutKey += src[c];
		}

	// read value
	//
	for(size_t c=nDivPos+1; c<SLEN; c++)
		{
		s_OutValue += src[c];


		};
 
   // добавить код поправки значения.... 





	return true;
};

//=================================================================
bool  Ini::readFromStrData(const std::string& src) {
	clearAllData();

	std::vector<std::string> vs;

	char tkns[2];
	tkns[0] = '\n';
	tkns[1] = '\0';

	gb::str::split (vs, src, tkns );

	if(vs.size() == 0) 
	{
		return false;
	}

	//* current line from file
	std::string scurr;
	   scurr.resize(128);
	   scurr = "";

	//* current section name
	std::string sCurrentSectionName;
	 sCurrentSectionName.resize(128);
	 sCurrentSectionName = "";


	 std::string sCurr_key;
		 sCurr_key.resize(128);

	 std::string sCurr_value;
		 sCurr_value.resize(128);


 
	 IniSection* pCurrSect = NULL;

	 bool bresult = true;

	for(int c=0; c<(int)vs.size(); c++)
		{
		   scurr = "";
		   scurr = vs[c];

		  sCurr_key = "";
		  sCurr_value = "";



		   // preprocess string
		   if(!preprocessString(scurr))	{
			   // error preprocess
			   return false;
		    };


		   // check empty
		   if(scurr.length() ==0) {
			   continue;
			   };

		   // parse string   as section
		   //
		   {

		       if( (scurr[0] == '[') && (scurr[scurr.length()-1] == ']') )
			   {
			    // section   found !
				// parse section name
			         for(int j=1; j<(int)scurr.length()-1; j++)
					 {
					  sCurrentSectionName += scurr[j];
					 
					 };

				// check parse section name
				 if(sCurrentSectionName == "") {
					 // parse error
					 return false;
					 
					 }

				// add section
			    pCurrSect = addSection	(sCurrentSectionName);
				  sCurrentSectionName = "";

			  continue;

			   
			   }; // if	section

		   }
		   //
		   // end (parse section)
		

	   if(!parseKeyValueString(sCurr_key, sCurr_value,  scurr) )
		   {
		   // error 
		   return false;		   
		   };

	   // add key value
	   if(pCurrSect)
		   {
		   if( !pCurrSect->addKeyValue(sCurr_key, sCurr_value) ) {
			   // error add key value
			   return false;
			   
			   };


		   }
	   else
		   {
		   // section none
		   return false;
		   
		   };





		}; // for each vector



   return true;
};

//=================================================================
bool  Ini::writeToStr(  std::string& dest) const {
	dest = "";

	for(int c=0; c<(int)m_vector_sections.size(); c++) 
		{
		const IniSection& sect =  m_vector_sections.at(c);
		  dest += "[";
		  dest += sect.getSectionName();
		  dest += "]\n";

		  for(int j=0; j<sect.getNumKeys(); j++)
			  {
			  const IniKeyValue& kval = sect.getKeyValueByIndex(j);
				 dest += kval.m_skey;
				 dest += "=";
				 dest += kval.m_svalue;
				 dest += "\n";
			  
			  }; // for j
		
		  dest += "\n";
		
		}; // for c
 
	return  true;
};

//===========================================================
bool  Ini::readFromFileA(const char* fname) {
	
	std::string str ;

	if(!gb::str::loadStrFromFileA(str, fname)) {
		return false;
		};
 
 return  readFromStrData(str);	
};

//===========================================================
bool  Ini::writeToFileA(const char* fname) const {
	std::string str = "";

	if( !writeToStr(str) )
		{
		 return false;
		}

	if(!gb::str::saveStrToFileA(str, fname)  )
		{
		 return false;
		}

 return true;	
};

//===========================================================
bool  Ini::setValue(const std::string& sSection, 
			  const std::string& sKey, 
			  const std::string& sValue )
{
    IniKeyValue kval (sKey, sValue);	

   int indexSect = -1;
   if( !searchSection(indexSect, sSection) ) {
	  // section not found

	   // create section
	    IniSection* pSect =    addSection(sSection);
		 if( !pSect->addKeyValue(sKey, sValue) )
			 {
			  return false;
			 };
	 
	   }
   else
	   {
	   // section FOUND !!
	    IniSection& sect_ref =  getSectionByIndex(indexSect);
	   if( !sect_ref.addKeyValue(sKey, sValue) ) {
		   return false;
		   }; 
	   
	   
	   }

  
  return true;	
};

//===========================================================
bool  Ini::setValueBool(const std::string& sSection, 
			  const std::string& sKey, const bool val )
{
  std::string svalue;
  svalue = "";
  svalue = gb::str::intToStr( (int32_t)val, false );   
 // svalue = ks::util::Formater::IntToStr( (int)val );

  return setValue( sSection, sKey, svalue  ); 	
};

//===========================================================
bool  Ini::setValueInt(const std::string& sSection, 
			  const std::string& sKey, const int val )
{
  std::string svalue;
  svalue = "";
  svalue =  gb::str::intToStr( val, false );
  //svalue = ks::util::Formater::IntToStr(  val );

  return setValue( sSection, sKey, svalue  );  	
};

//===========================================================
bool  Ini::setValueFloat(const std::string& sSection, 
			  const std::string& sKey, const float val )
{
  std::string svalue;
  svalue = "";

  svalue = gb::str::floatToStr(val);
  //svalue = ks::util::Formater::FloatToStr( val );


  return setValue( sSection, sKey, svalue  ); 
};

//===================================================
bool  Ini::getValue(const std::string& sSection, 
			  const std::string& sKey, 
			     std::string& sValue) const 
{
	int index = -1;
	if( !searchSection(index, sSection ) )
		{
		return false;
		};

	const IniSection& sect = getSectionByIndex(index);

	index = -1;
	if(!sect.searchKey(index, sKey)  )
		{
		  // not found
		return false;
		
		};

	const IniKeyValue& kval = sect.getKeyValueByIndex(index);

	sValue = kval.m_svalue;
	return true;
	
};

//===================================================
bool  Ini::getValueBool(const std::string& sSection, 
			   const std::string& sKey, 
			      bool& val) const 
{
  std::string sval;
 if(!getValue(sSection, sKey, sval) )
	 {
	  return false;
	 };

 int value = -1;

 bool bres = gb::str::intFromCstr(value, sval.c_str() );
 //bool bres =  ks::util::Formater::IntFromStr(value, sval.c_str() );

 if(!bres)
 {
	 return false;
 }


	 if(value)
		   val = true; 
	    else val = false;

	 return true;
};

//===================================================
bool  Ini::getValueInt(const std::string& sSection, 
			   const std::string& sKey, 
			      int& val) const 
{
 std::string sval;
 if(!getValue(sSection, sKey, sval) )
	 {
	  return false;
	 };

  bool bres = gb::str::intFromCstr(val, sval.c_str() );
 //bool bres =  ks::util::Formater::IntFromStr(val, sval.c_str() );

   if(!bres) return false;

	 return true;
};



//===================================================
bool  Ini::getValueFloat(const std::string& sSection, 
			   const std::string& sKey, 
			      float& val) const 
{
 std::string sval;
 if(!getValue(sSection, sKey, sval) )
	 {
	  return false;
	 };	
 
 bool bres = gb::str::floatFromCstr(val, sval.c_str() );
// bool bres =  ks::util::Formater::FloatFromStr(val, sval.c_str() );

   if(!bres) return false;

   return true;
};

  	//==================================================================
}
}
}


// end file