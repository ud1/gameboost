
//#include "stdafx.h"
#include <gb/Config.h>
#include <gb/makecppcode/makecppcode.h>
#include <gb/system/filefunc.h>
namespace ff = gb::system::filefunc;

using    std::string; ;

#pragma warning(disable : 4996)


namespace gb
{

namespace makecppcode
{
//======================================================


	//======================================================
	bool saveString( string & s,  const char* fname)  
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
 string     CppDefine::MakeDeclarationString() const {
	    string  s;
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
 string       CppVariable::MakeVarDeclStr() const {
		 string  s = "";
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
 string        CppEnum::MakeDeclaration() const {
		 string  s;
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
 string   CppClassMethod::MakeDeclarationString(bool bIncBriefComment ) const {
	     string  s;

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
 string   CppClassMethod::MakeImplementationString() const {
	 string  s = "";

	if(m_bForceImplemIntoDecl) {
	   return s;
	};


	 string  sLineBeforeName = m_pClassOwner->m_sName;
	sLineBeforeName += "::";
	s =  CppFunction::MakeImplementationString(  sLineBeforeName.c_str()    );

	    

  return  s;
};







//=============================================================
//=======          CppFunction
//=============================================================

//=============================================================
 string          CppFunction::MakeDeclarationString(bool bIncBriefComment, const char* szLineBeforeName ) const {
		   string  s;

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
   saveString(s,  m_sHeaderFilename.c_str()   );

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
 CppDefine*    CppHeaderFile::AddHeaderDefineFloat(const string sDefName, 
		const float val, const string sBrief) 
{
   char temp[32];
   temp[0] = 0;
      int nsppos = sprintf(temp, "%f", val  );
      temp[nsppos] = 0;
   return AddHeaderDefine(  sDefName,  temp,   sBrief);
};

//================================================================
 CppDefine*   CppHeaderFile::AddHeaderDefineInt(const string sDefName, 
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
	



 


//========================================================
 string     CppClass::MakeImplementationString() const {
	  string  s = "";

	 // проверка на существование методов
  if( ( m_decl_public.m_vec_ClassMethods.size()==0 ) && 
	  ( m_decl_protected.m_vec_ClassMethods.size()==0 ) &&
	  ( m_decl_private.m_vec_ClassMethods.size()==0 )
	)

  {
  
	return s ;
  };


  // make constructors
  for(size_t c=0; c<m_decl_public.m_vec_ClassConstructors.size(); c++) {
	    if(  m_decl_public.m_vec_ClassConstructors[c]->IsForceImplemIntoDecl()  ) 
		{
		 continue;
        } 
  
	  s += m_decl_public.m_vec_ClassConstructors[c]->MakeImplementationString();
	  s += "\n";
  
  
  };


   		


 

	// make public methods implementation
	for(size_t c=0; c<m_decl_public.m_vec_ClassMethods.size(); c++ )
	{
		if(  m_decl_public.m_vec_ClassMethods[c]->IsForceImplemIntoDecl()  ) {
		 continue;
		} 

	  s +=  MakeImplemDivLine();
	  s += "\n";
	  s +=	m_decl_public.m_vec_ClassMethods[c]->MakeImplementationString();
	  s += "\n\n";
	
	
	}



	// make protected methods implementation
	for(size_t c=0; c<m_decl_protected.m_vec_ClassMethods.size(); c++  )
	{
	   	 if(  m_decl_protected.m_vec_ClassMethods[c]->IsForceImplemIntoDecl()  ) 
		 {
		    continue;
		 }
	
	
	  s +=   MakeImplemDivLine();
	  s += "\n";
	  s +=	m_decl_protected.m_vec_ClassMethods[c]->MakeImplementationString();
	  s += "\n\n";
 
	}
	 
 

	// make private methods implementation
		for(size_t c=0; c<m_decl_private.m_vec_ClassMethods.size(); c++  )
	{
	   	 if(  m_decl_private.m_vec_ClassMethods[c]->IsForceImplemIntoDecl()  ) 
		 {
		    continue;
		 }
	
	
	  s +=   MakeImplemDivLine();
	  s += "\n";
	  s +=	m_decl_private.m_vec_ClassMethods[c]->MakeImplementationString();
	  s += "\n\n";
 
	}

 
	 s += "\n\n";
    return s;
};

//========================================================
 string    CppClass::MakeDeclarationString() const {
	 string  s;

		  if( m_sBrief.length() )
		  {
			s += "/** \\brief ";
			s += m_sBrief;
			s += " */\n";
		  
		  }


		  s += "class ";
		  s += m_sName;

		  if(m_pClassBase)
		  {
			  s += " : public ";
				  s += m_pClassBase->m_sName;

		  
		  }

		  s += "\n";
		  s += "{\n";

		  // make public
		  //
		  {

		  if( m_decl_public.m_vec_ClassMembers.size() || m_decl_public.m_vec_ClassMethods.size() ||
			   m_decl_public.m_vec_ClassConstructors.size()
			  )
		  {
			  s += "   public:\n\n";
		  }


		  // make members
		  if(m_decl_public.m_vec_ClassMembers.size() )
		  {
		    for(size_t c=0; c<m_decl_public.m_vec_ClassMembers.size(); c++)
			{
			  s += "   ";
			  s += m_decl_public.m_vec_ClassMembers[c]->MakeDeclarationString();
			  s += "\n";
			
			}
		  
		  }

		  // make constructors
		  for(size_t c=0; c<m_decl_public.m_vec_ClassConstructors.size(); c++)
		  {
		    s += m_decl_public.m_vec_ClassConstructors[c]->MakeDeclarationString(true);
			s += "\n";
		  
		  }

		  // make destructor
		  if(m_bHasDestructor)
		  {
		   s += "   ~";
		   s += m_sName;
		   s += "() { ";

		   if(m_sDestrCode.length() )
		   {
		    s += m_sDestrCode;
		   }
		  
		   s +=  "  };\n\n";
		  }



		  // make methods
		  if(m_decl_public.m_vec_ClassMethods.size() )
		  {
		    for(size_t c=0; c<m_decl_public.m_vec_ClassMethods.size(); c++)
			{
			 s += "   ";
			 s += m_decl_public.m_vec_ClassMethods[c]->MakeDeclarationString(true);
			 s += ";\n";
			
			}
		  
		  
		  };

		  }
		  //
		  //  end 






		  // make protected
		  //
		  {
			  if( m_decl_protected.m_vec_ClassMembers.size() || m_decl_protected.m_vec_ClassMethods.size() )
		      {
			     s += "\n   protected:\n\n";
		      }


		   
		  // make members
		  if(m_decl_protected.m_vec_ClassMembers.size() )
		  {
		    for(size_t c=0; c<m_decl_protected.m_vec_ClassMembers.size(); c++)
			{
			  s += "   ";
			  s += m_decl_protected.m_vec_ClassMembers[c]->MakeDeclarationString();
			  s += "\n";
			
			}
		  
		  }

		  // make methods
		  if(m_decl_protected.m_vec_ClassMethods.size() )
		  {
		    for(size_t c=0; c<m_decl_protected.m_vec_ClassMethods.size(); c++)
			{
			 s += "   ";
			 s += m_decl_protected.m_vec_ClassMethods[c]->MakeDeclarationString(true);
			 s += ";\n";
			
			}
		  
		  
		  };



		  }
		  //
		  //  end



		  // make private
		  //
		  {

		  	  if( m_decl_private.m_vec_ClassMembers.size() || m_decl_private.m_vec_ClassMethods.size() )
		      {
			     s += "\n   private:\n\n";
		      }


			  // make members
			  if(m_decl_private.m_vec_ClassMembers.size() )
			  {
				for(size_t c=0; c<m_decl_private.m_vec_ClassMembers.size(); c++)
				{
				  s += "   ";
				  s += m_decl_private.m_vec_ClassMembers[c]->MakeDeclarationString();
				  s += "\n";
				
				}
			  
			  }

			  // make methods
			  if(m_decl_private.m_vec_ClassMethods.size() )
			  {
				for(size_t c=0; c<m_decl_private.m_vec_ClassMethods.size(); c++)
				{
				 s += "   ";
				 s += m_decl_private.m_vec_ClassMethods[c]->MakeDeclarationString(true);
				 s += ";\n";
				
				}
			  
			  
			  };






		  }
		  //
		  //  end




		  s += "\n};\n";

	   return s;
};




//========================================================
 string   CppHeaderFile::MakeFullText() {
   string  s;
  
  

  

  // make header comment section
  //
  {
	  if(m_sHeaderBrief.length() > 0)
	  {
		  s += "/** \\file ";
 

#ifndef WIN32
#pragma warning("WARNING!  PLATFORM SPEC CONST:   MAX_PATH  "  __FILE__)
#endif

#ifndef WIN32
	 const int MAX_PATH = 512;
#endif


char sfile[MAX_PATH];

 
   
		  if( ff::extractFileNameA(sfile,  m_sHeaderFilename.c_str() ) ) 
		  {


		  }
		  else 
		  {
			  strncpy(sfile,   m_sHeaderFilename.c_str(), MAX_PATH );

		  };

		  s += sfile;
		  s += " \n";

		  s += " \\brief ";
		  s += m_sHeaderBrief;
		  s += " \n";
		  s += "*/\n\n";
	  }
	  else
	  {
		  s += "\n";
	  };


  }
  //
  //   end ( header comment section  )

  
  
  //  make header preprocessor
  //
  {
  s += " #pragma once\n";
      string  sInc;
    for(size_t c=0; c<m_vecInclude.size(); c++) {
	 sInc = "#include \"";
	 sInc += m_vecInclude[c];
	 sInc += "\"\n";
	 s += sInc;
      
  
    }
	
	s += "\n";
  
  
  }
  //
  //   end ( make header preprocessor  )  
  
  
  
  // make header defines
  //
  {
	  
   
    if( m_vecDefines.size() > 0)
	{
	  s += MakeDivDeclString( "DEFINE" );

		for(size_t c=0; c<m_vecDefines.size(); c++) {
		 s += m_vecDefines[c]->MakeDeclarationString();
		 s += "\n";

		}
	  
	
	}
	else
	{
	 s += "\n";
	
	};
  
  
	s += "\n\n";
  
  
  }
  //
  //   end ( make header defines  )
  
  
  
  // make header enum
  //
  {
	if(m_vec_Enums.size() )
	{
	   s += MakeDivDeclString( "ENUM" );

	    for(size_t c=0; c<m_vec_Enums.size(); c++)
		{
			CppEnum* penm = m_vec_Enums[c];
			 s +=  penm->MakeDeclaration();
		}


	}

 
  }
  //
  //   end ( make header enum  )


  

  // make header function declare
  //
  {
    if(m_vec_Functions.size() >0)
	{
	   s += MakeDivDeclString( "FUNCTIONS" );

	   for(size_t c=0; c<m_vec_Functions.size(); c++)
	   {
		    CppFunction* pfunc = m_vec_Functions[c];
		   s += pfunc->MakeDeclarationString(true);
		   s += ";\n\n";
		    


	   }

	   

	}
	else
	{
		s += "\n";
	}
 
   s += "\n";

  }
  //
  //   end (  make header function declare )


  
  
  //  make classes declare
  //
  {
	if(m_vec_Classes.size() > 0)
	{
	  s += MakeDivDeclString( "CLASSES" );

	  for(size_t c=0; c< m_vec_Classes.size(); c++)
	  {
	   s +=	 m_vec_Classes[c]->MakeDeclarationString();
	  
	  };


	
	}
	else
	{
	 s += "\n";
	};

    
  }
  //
  //   end (  classes declare )


#ifdef _DEBUG
  saveString(s, "log_header.log");
#endif

 //------------------------------------------------------------------------
 //              MAKE CPP FILE   CODE
 //------------------------------------------------------------------------
  
  s += "\n//\n";
  s += "//==================  implementation  =========================\n";
  s += "//\n";

  s += "#include \"stdafx.h\"\n";

  s += "\n\n";


  s += "\n";
  s +=  " #pragma warning( push )\n";

  //  make pragma warn disable
  //
  {
	 for(size_t c=0; c<m_vecPragmaWarnDisable.size(); c++)
	 {
		 s += "#pragma warning( disable : ";

		unsigned short val = m_vecPragmaWarnDisable[c];
		   char buf[32];
		        buf[0] = 0;
		  const int NSPRNTRES = sprintf(buf, "%u", val );
		   buf[NSPRNTRES] = 0;
		 s += buf;

		 s += " )\n";
	 }

  
  }
  //
  //   end ( make pragma warn disable )
  
  s += "\n\n";


  //	make cpp internal vars
  //
  {
	  if(m_vec_InternalVariables.size() ) {
	     s +=  MakeDivDeclString("INTERNAL VARIABLES//CONSTANTS");
	  }

	 for(size_t c=0; c<m_vec_InternalVariables.size(); c++)
	 {
	   s += m_vec_InternalVariables[c]->MakeVarDeclStr();
	   s += "\n";
	 
	 };


  }
  //
  //   end





  //  make internal functions
  //
  {

	  if(m_vec_InternalFunctions.size() ) {
	  s +=  MakeDivDeclString("INTERNAL FUNCTIONS");	   
	  };

	  for(size_t c=0; c < m_vec_InternalFunctions.size(); c++) {
	    s += MakeImplemDivLine();
		s += "\n";

		s += m_vec_InternalFunctions[c]->MakeImplementationString();
		s += "\n";
	  
	  }
 
	 s += "\n//------------------------------------------------------\n\n";
  }
  //
  // end



  
  //  make func implementation
  //
  {
  
   	for(size_t c =0; c< m_vec_Functions.size(); c++)
	{
	s += MakeImplemDivLine();
	s += "\n";
	s += m_vec_Functions[c]->MakeImplementationString();  
	s += "\n";
 
	 
	};
 
  }
  //
  //   end ( make func implementation )
  



  
  //  make implementation classes
  //
  {
	 if(m_vec_Classes.size() )
	 {
		for(size_t c=0; c<m_vec_Classes.size(); c++)
		{
		  s += "//=====================================================\n";
		  s += "//         ";  s += m_vec_Classes[c]->m_sName; s += "    \n";
		  s += "//=====================================================\n";
		  s += "\n";
		
		  s += m_vec_Classes[c]->MakeImplementationString();

		  s += "\n";
		}
	 
	 
	 
	 }
  
	s += "\n\n";
  }
  //
  //   end ( make implementation classes )  
  




  //  xxxxxxxxxxxx
  //
  {
  
  
  
  }
  //
  //   end ( xxxxxxxx)  

  
  
  //  xxxxxxxxxxxx
  //
  {
  
  
  
  }
  //
  //   end ( xxxxxxxx)  
  
  
  
   s +=  " #pragma warning( pop )\n";
   s += "// end file";
  


  return s;
};


 

//======================================================

}
}

// end file