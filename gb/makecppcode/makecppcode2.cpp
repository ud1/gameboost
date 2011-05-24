
//#include "stdafx.h"
#include <gb/Config.h>
#include <gb/makecppcode/makecppcode.h>
#include <gb/system/filefunc.h>
namespace ff = gb::system::filefunc;


#pragma warning (disable : 4996)


namespace gb
{
namespace makecppcode
{


//========================================================
std::string    CppClass::MakeImplementationString() const {
	 std::string s = "";

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

	  s +=  CppHeaderFile::MakeImplemDivLine();
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
	
	
	  s +=  CppHeaderFile::MakeImplemDivLine();
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
	
	
	  s +=  CppHeaderFile::MakeImplemDivLine();
	  s += "\n";
	  s +=	m_decl_private.m_vec_ClassMethods[c]->MakeImplementationString();
	  s += "\n\n";
 
	}

 
	 s += "\n\n";
    return s;
};

//========================================================
std::string   CppClass::MakeDeclarationString() const {
	std::string s;

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
std::string  CppHeaderFile::MakeFullText() {
  std::string s;
  
  

  

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
     std::string sInc;
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



//=============================================================

}
}




// end file