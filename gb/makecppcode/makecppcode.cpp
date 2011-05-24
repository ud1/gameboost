
//#include "stdafx.h"
#include <gb/makecppcode/makecppcode.h>

using std::string;
#pragma warning(disable : 4996)

namespace gb
{

namespace makecppcode
{
//======================================================


	//======================================================
	static bool __saveStr(std::string& s,  const char* fname)  
	{
		FILE* file = fopen(fname, "w+b");
		if(!file) return false;

		size_t swrtd = fwrite(s.c_str(), s.length(), 1, file); //fputs( s.c_str(), file );

		fflush(file);
		fclose(file);
		return true;
	}


//=============================================================
//=======          CppDefine
//=============================================================

//=============================================================
std::string    CppDefine::MakeDeclarationString() const {
	   std::string s;
	   if(m_sBrief.length() > 0)
	   {
		   s += "/** \\brief ";
		   s += m_sBrief;
		   s += " */\n";
	   }
	   else
	   {
		   s += " \n";
	   }

	   s += "#define ";
	   s += m_sName;
	   s += " ";
	   s += m_sValue;
	   
	   return s;
};


//=============================================================
//=======          CppVariable
//=============================================================

//=============================================================
std::string      CppVariable::MakeVarDeclStr() const {
		std::string s = "";
		s += m_sType;
		s += " ";
		s += m_sName;

		if(m_sDefaultVal.length() )
		{
		 s += " = ";
		 s += m_sDefaultVal;
		};

		s += " ; ";

		if(m_sBrief.length() > 0)
		{
		 s += "///< ";
		 s += m_sBrief;
		
		};
	
	 return s;
};





//=============================================================
//=======          CppEnum
//=============================================================

//=============================================================
std::string       CppEnum::MakeDeclaration() const {
		std::string s;
		if(m_sBrief.length() > 0)
		{
			s += "/** \\brief ";
			s += m_sBrief;
			s += " */\n";
		}
		else
		{
			s += "\n";
		}


		s += "enum ";
		s += m_sName;
		s += " {\n";

		for(size_t c=0; c<m_vecItems.size(); c++) {
		  const  CppEnum::EnumItem& ei = m_vecItems[c];
		  s += ei.m_sItemValue;

		       if(c != m_vecItems.size()-1 ) { s += ","; }

		    if( ei.m_sBriefLine.length()>0  ) {
			  s += "  ///< ";
			  s += ei.m_sBriefLine;
			  s += "\n";
		    }
		    else
		    {
			s += "\n";
		    }
		  }	// for

		s += "\n};\n";

		return s;
};





//=======================================================
//     CppClassMethod
//=======================================================

//=========================================================================
std::string  CppClassMethod::MakeDeclarationString(bool bIncBriefComment ) const {
	    std::string s;

		s =  CppFunction::MakeDeclarationString(bIncBriefComment);

		if(  m_sLineAfterDecl.length() > 0 ) {
		  s += m_sLineAfterDecl;
		};



		if(m_bForceImplemIntoDecl) {
		 s += " {\n";

		 s += m_sCode;
		
		 s += "\n}";
		};
	
	 return s  ;
};

//=========================================================================
std::string  CppClassMethod::MakeImplementationString() const {
	std::string s = "";

	if(m_bForceImplemIntoDecl) {
	   return s;
	};


	std::string sLineBeforeName = m_pClassOwner->m_sName;
	sLineBeforeName += "::";
	s =  CppFunction::MakeImplementationString(  sLineBeforeName.c_str()    );

	    

  return  s;
};







//=============================================================
//=======          CppFunction
//=============================================================

//=============================================================
std::string         CppFunction::MakeDeclarationString(bool bIncBriefComment, const char* szLineBeforeName ) const {
		  std::string s;

		  if(bIncBriefComment) 
		  {

			  if(m_sBrief.length() >0)
			  {
				  s += "/** \\brief ";
				  s += m_sBrief;

				   for(size_t c=0; c<m_vec_FuncParams.size(); c++)
				   {
					 if(m_vec_FuncParams[c]->m_sComment.length()  )
					 {
					   s += "\n  \\param  ";
					   s += m_vec_FuncParams[c]->m_sName;
					   s += "  - ";
					   s += m_vec_FuncParams[c]->m_sComment;
					 }
 
				   }
 
				  s += " */\n";
			  }; // if

	      }	// if

 
		  s += m_sRetVal;
		  s += " ";

		  if(szLineBeforeName)  {
			s += szLineBeforeName;
		  }

		  s += m_sName;
		  s += "(";

		  for(size_t c=0; c<m_vec_FuncParams.size(); c++)
		  {
			  const CppFuncParameter* par = m_vec_FuncParams[c];
			  s += par->MakeDeclString();

			  if(c != m_vec_FuncParams.size()-1)
			  {
				  s += ",";
			  }

			  s += " ";

		  }
 
		  s += ")";
	  return s;
};






//=============================================================
//=======        CppHeaderFile
//=============================================================


//===================================================
long  CppHeaderFile::Save() {
   long res = 0;

   string s = MakeFullText();
   __saveStr(s,  m_sHeaderFilename.c_str()   );

	 return res;
 };

//================================================================
 CppDefine*  CppHeaderFile::AddHeaderDefineHex(
						const string sDefName, 
						const unsigned int val, 
						const string sBrief) 
{
  char temp[32];
  temp[0] = 0;
    int nsppos = sprintf(temp, "0x%X", val  );
    temp[nsppos] = 0;

   return AddHeaderDefine(  sDefName,  temp,   sBrief);
};

//=================================================================
 CppDefine*    CppHeaderFile::AddHeaderDefine(const string sDefName, 
		const float val, const string sBrief) 
{
   char temp[32];
   temp[0] = 0;
      int nsppos = sprintf(temp, "%f", val  );
      temp[nsppos] = 0;
   return AddHeaderDefine(  sDefName,  temp,   sBrief);
};

//================================================================
 CppDefine*   CppHeaderFile::AddHeaderDefine(const string sDefName, 
						const int val, const string sBrief) 
{
   char temp[32];
   temp[0] = 0;
      int nsppos = sprintf(temp, "%i", val  );
      temp[nsppos] = 0;
   return AddHeaderDefine(  sDefName,  temp,   sBrief);
};

//========================================================
 CppDefine*  CppHeaderFile::AddHeaderDefineStr(
						const string sDefName, 
						const string sValue, 
						const string sBrief) 
{
 string s = "\""; 
  s += sValue;
  s += "\"";
   return AddHeaderDefine(  sDefName,  sValue,   sBrief);
};


//==========================================================
 CppDefine*  CppHeaderFile::AddHeaderDefine(
					const string sDefName, 
					const string sValue, 
					const string sBrief) 
{
   CppDefine* pdef = new CppDefine(sDefName,  sValue,  sBrief);
      m_vecDefines.push_back(pdef);
          return  m_vecDefines[m_vecDefines.size()-1];
};
	



//================================================================
std::string   CppHeaderFile::MakeDivDeclString(const std::string caption)   {
  std::string s;

   s += "\n";
   s += "//-----------------------------------------------\n";
   s += "//         ";
   s += caption;
   s += "\n";
   s += "//-----------------------------------------------\n";
   s += "\n";

  return s;
};

 

//======================================================

}
}

// end file