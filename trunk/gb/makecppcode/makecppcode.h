/** \file  makecppcode.h
 \brief Очень простое решение для построения cpp-кода. 
    Немного удобнее, чем набивание просто текстом.


 \author ksacvet777

  \todo поменять константы на указательные
  \todo Прокомментировать
  \todo Добавить методы доступа в объектам в векторах.
  \todo  Добавить примеров.

*/


#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>

namespace gb
{


/**  \brief  Очень простое решение для построения cpp-кода. 
           Немного удобнее, чем набивание просто текстом.       */
namespace makecppcode
{

//-------------------------------------------------------------------------


using   std::string;

#pragma  warning( push )
#pragma  warning(disable : 4996)

static const char  SC_BOOLEAN[]   = "bool";
static const char  SC_VOID[]      = "void";
static const char  SC_INT[]       = "int";
static const char  SC_UINT[]      = "unsigned int";
static const char  SC_LONG[]      = "long";
static const char  SC_ULONG[]     = "unsigned long";
static const char  SC_FLOAT[]     = "float";

static const char  SC_HRESULT[]    = "HRESULT";

 
// temp

template <class T, bool owned>
//! \brief Простой вектор для указателей с самоудалением. вместо бустовского.
class vector_pointers :  public std::vector<T*> 
{
public:

	 vector_pointers() {}
	~vector_pointers()
	{
		if(!owned) 
			return ;
	  for(size_t c=0; c<size(); c++)
	  {
		  T* p = at(c);
		  delete p;
	  }

	  clear();
	}



};
 

class CppVariable {
public:
    const  string  m_sName;
    const  string  m_sType;
	const  string  m_sDefaultVal; 
    const  string  m_sBrief;


	CppVariable(const  string sName, 
				const  string  sType,  
				const  string sDefaultVal,  
				const  string  sBrief 
				)				
		:  m_sName(sName),  
		   m_sType(sType), 
		   m_sDefaultVal(sDefaultVal),  
		   m_sBrief(sBrief)  {}

std::string MakeVarDeclStr() const;

};
// end class

typedef   vector_pointers<CppVariable,true>    Vec_Variables;


//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
class CppDefine {
public:
   const  string m_sName;
   const  string m_sValue;
   const  string m_sBrief;
   
   CppDefine(const  string sName, 
			 const  string sValue, 
			 const  string sBrief
			 )			 
	   : m_sName(sName),  m_sValue(sValue), m_sBrief(sBrief)    {} 

   std::string MakeDeclarationString() const;

};
// end class

//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
typedef  vector_pointers<CppDefine,true> Vec_Defines;



//! \brief xxxxxxxxxxxxxxxxxx
class CppEnum {
public:
   const  string m_sName;
   const  string m_sBrief;

   class EnumItem {
   public:
	    string m_sItemValue;
	    string m_sBriefLine;

		EnumItem() {};
   };

	CppEnum(const  string sName, const  string sBrief) 
		: m_sName(sName), m_sBrief(sBrief) 
	{}

	void AddEnumItem(const string sItemValue, 
					 const  string sBriefLine) 
	{
		 EnumItem ei;
		 ei.m_sItemValue = sItemValue;
		 ei.m_sBriefLine = sBriefLine;
		   m_vecItems.push_back(ei);
	}

//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
std::string MakeDeclaration() const ;


 std::vector<EnumItem> m_vecItems;

};
// end class

//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
typedef  vector_pointers<CppEnum,true> Vec_Enums;



//! \brief xxxxxxxxxxxxxxxxxx
class CppFuncParameter {
public:
   const string m_sType; 
   const string m_sName;
   const string m_sComment;

	CppFuncParameter( const string sType, 
					  const string sName, 
					  const string sComment="" ) 
		: m_sType(sType), 
		  m_sName(sName), 
		  m_sComment(sComment)  
	{}

//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
std::string MakeDeclString( ) const 
{
		std::string s;

		s +=  m_sType;
		s += " ";
		s += m_sName;
 
		return s;
}; 


};
// end class

//! \brief  xxxxxxxxxxxxxxxxxxxxxxxxx
typedef  vector_pointers<CppFuncParameter,true>  Vec_FuncParams;



//! \brief xxxxxxxxxxxxxxxxxx
class CppFunction {
public:
  const std::string m_sName; 
  const std::string m_sRetVal; 
  const std::string m_sBrief;
 
	  CppFunction(const std::string sName, 
				  const std::string sRetVal, 
				  const std::string sBrief, 
				  const std::string& sCode )
		  : m_sName(sName), 
		    m_sRetVal(sRetVal), 
			m_sBrief(sBrief)   
		{  
		    m_sCode += sCode;  
		}


	void AddParameter(const std::string sType, 
					  const std::string sName, 
					  const std::string sComment="") 
	{
	   CppFuncParameter* par = new CppFuncParameter(sType,  sName, sComment); 
			m_vec_FuncParams.push_back(par);
	}

 
	virtual std::string MakeDeclarationString(bool bIncBriefComment, const char* szLineBeforeName=NULL) const;

	virtual std::string MakeImplementationString(const char* szLineBeforeName=NULL) const 
	{
	  std::string s;
		 s += MakeDeclarationString(false, szLineBeforeName);
		 s += "{\n";
		 s += GetCodeText();
		 s += "\n};\n\n";
		    return s ;
	}

	  
	std::string GetCodeText() const {  return m_sCode; }


	void AppendStrToCode(const string& s) 
	{
	   m_sCode += s;
	}

protected:
   Vec_FuncParams m_vec_FuncParams;
   string m_sCode;   ///<  код функции. Само тело исполняемая часть

};
// end class

typedef  vector_pointers<CppFunction,true> Vec_Functions;
 
//! \brief  Член класса
class CppMember {
public:
	const string m_sType;
    const string m_sName;
	const string m_sBrief;
	const string m_sBeforeDecl;

	CppMember(const string sType, 
			  const string sName, 
			  const string sBrief, 
			  const std::string sBeforeDecl=""  
			  ) 
		: m_sType(sType), 
		  m_sName(sName), 
		  m_sBrief(sBrief), 
		  m_sBeforeDecl(sBeforeDecl) 
	{}

	string MakeDeclarationString() const 
	{
			  string s;
			  s += m_sBeforeDecl;
			  s += m_sType;
			  s += " ";
			  s += m_sName;
			  s += ";";

			  if(m_sBrief.length() )
			  {
			   s += " ///< ";
			   s += m_sBrief;
			  }
 
	  return s;
	}

};
// end class

typedef  vector_pointers<CppMember,true> Vec_ClassMembers;


class   CppClass;

//!   Метод класса
class CppClassMethod : public  CppFunction {
public:

	CppClassMethod( const CppClass* pClassOwner, 
					const std::string sName, 
					const std::string sRetVal, 
					const std::string sBrief, 
					const std::string& sCode,
					const bool bForceImplemIntoDecl )

		: CppFunction(sName,  sRetVal,  sBrief,   sCode), 
		     m_pClassOwner(pClassOwner),
		     m_bForceImplemIntoDecl(bForceImplemIntoDecl)  
	{}


	std::string MakeDeclarationString(bool bIncBriefComment ) const;
	std::string MakeImplementationString() const;


	const bool IsForceImplemIntoDecl() const 
	{ 
		return m_bForceImplemIntoDecl; 
	}

	void SetLineAfterDecl(const std::string s) 
	{ 
	  m_sLineAfterDecl = s;
	}

private:
   const CppClass* m_pClassOwner;
   bool m_bForceImplemIntoDecl;
   std::string m_sLineAfterDecl;


};
// end class

typedef  vector_pointers<CppClassMethod,true>   Vec_ClassMethods;


class CppStruct{
public:

	const string m_sName;
	const string m_sBrief;

	CppStruct(const string sName, const string sBrief) 
		: m_sName(sName), m_sBrief(sBrief)  {}

	virtual ~CppStruct() {}

	CppMember* addMember(const string& sType, const string& sName, const string& sBrief)
	{
	   CppMember* res = new CppMember(sType, sName, sBrief);
	   m_vec_members.push_back(res);
	   return res;
	}

 	std::string   MakeDeclarationString() const 
	{
		// none code
		assert(false&&"NEED INSERT CODE !"); 
	}

protected:

  Vec_ClassMembers m_vec_members;

};

typedef  vector_pointers<CppStruct,true>   Vec_Struct;


//! \brief Видимость.. как обычно публик , протектед, приват.
struct DECL_VISIBLE
{
	enum e 
	{
	  PUBLIC,
	  PROTECTED,
	  PRIVATE
	};
};

//! Класс
class CppClass {
public:
  const string m_sName;
  const string m_sBrief;
  const CppClass* m_pClassBase;
  const bool m_bHasDestructor;

	  class Declaration 
	  {
	  public:
		  Vec_ClassMembers    m_vec_ClassMembers;
		  Vec_ClassMethods    m_vec_ClassMethods;
		  Vec_ClassMethods    m_vec_ClassConstructors;
	  
	  };


    CppClass(const string sName, 
			 const string sBrief, 
			 const CppClass* pClassBase, 
			 bool bHasDestructor=true) 
           : m_sName(sName),  
		     m_sBrief(sBrief), 
			 m_pClassBase(pClassBase), 
			 m_bHasDestructor(bHasDestructor)  
	{}


	CppMember* AddMember(const DECL_VISIBLE::e dv, 
						 const string sType, 
						 const string sName, 
						 const string sBrief, 
						 const std::string sBeforeDecl="") 
	{
		CppMember* pm = new CppMember(  sType,   sName,   sBrief, sBeforeDecl);

		  switch(dv)
		  {
		  case DECL_VISIBLE::PUBLIC: {     
			m_decl_public.m_vec_ClassMembers.push_back(pm);
		  } break;

		  case DECL_VISIBLE::PROTECTED: {     
			m_decl_protected.m_vec_ClassMembers.push_back(pm);						 
		  } break;

		  case DECL_VISIBLE::PRIVATE: {     
			m_decl_private.m_vec_ClassMembers.push_back(pm);				   
		  } break;

		  default: {
				   delete pm;
			       assert(false &&  L"default not allow" );
			       return NULL;
			 }
		  
		  } // switch

		return pm;
	};


	CppClassMethod* AddMethod(const DECL_VISIBLE::e dv, 
							  const std::string sName, 
							  const std::string sRetVal, 
							  const std::string sBrief, 
							  const std::string& sCode, 
							  bool bForceImplemIntoDecl=false   ) 
	{
		CppClassMethod* pcm = new CppClassMethod(this, sName, sRetVal, 
			     sBrief, sCode, bForceImplemIntoDecl);

		switch(dv)
		{

		case DECL_VISIBLE::PUBLIC : 
			{  
				m_decl_public.m_vec_ClassMethods.push_back(pcm);

			} break;

		case DECL_VISIBLE::PROTECTED: 
			{ 
				m_decl_protected.m_vec_ClassMethods.push_back(pcm);

			} break;

		case DECL_VISIBLE::PRIVATE: 
			{ 
				m_decl_private.m_vec_ClassMethods.push_back(pcm);

			} break;

		default: 
			{
				delete pcm;
				assert(false && L"default not allowed" );		
				return NULL;	
			};

		}; // switch

	 return pcm;
	}


	CppClassMethod* AddPublicConstructor(const std::string sBrief, 
										 const std::string sInitLine,  
										 const std::string& sCode, 
										 bool bForceImplemIntoDecl ) 
	{

		CppClassMethod* pm = new CppClassMethod( this, m_sName,  "", sBrief,  
			     sCode,  bForceImplemIntoDecl );
		pm->SetLineAfterDecl(sInitLine);
		m_decl_public.m_vec_ClassConstructors.push_back(pm); 
		return pm;
	}

	void AddCodeToDestructor(const std::string& sCode) throw()
	{
		if(!m_bHasDestructor) 
		{
			throw	( std::runtime_error("Class no have destructor")   );
			return;
		}
		m_sDestrCode += sCode;
	}
 
	std::string   MakeDeclarationString() const ;
	std::string   MakeImplementationString() const ;
	   
private:

	Declaration m_decl_public;
	Declaration m_decl_protected;
	Declaration m_decl_private;

	std::string m_sDestrCode;
 
};
// end class
 
typedef  vector_pointers<CppClass,true> Vec_CppClasses;


//!  \brief  c++ заголовок
class CppHeaderFile {
public:
const string m_sHeaderFilename;
const string m_sHeaderBrief;
  
   CppHeaderFile(const string sHeaderFilename, 
			     const string sHeaderBrief) 
         : m_sHeaderFilename(sHeaderFilename), 
	       m_sHeaderBrief(sHeaderBrief)  
   {}


string&  AddInclude(const string sInclude)	   
{
  string s = sInclude;
  m_vecInclude.push_back(s);
  return m_vecInclude[m_vecInclude.size()-1];
}

CppDefine* AddHeaderDefine(const string sDefName, const string sValue, const string sBrief);
	
CppDefine* AddHeaderDefineStr(const string sDefName, const string sValue, const string sBrief) ;

CppDefine* AddHeaderDefine(const string sDefName, const int val, const string sBrief) ;

CppDefine* AddHeaderDefine(const string sDefName, const float val, const string sBrief) ;

CppDefine* AddHeaderDefineHex(const string sDefName, const unsigned int val, const string sBrief) ;

CppEnum* AddEnum(const std::string sName, const std::string sBrief) 
{
	CppEnum* penm = new CppEnum( sName,  sBrief );
	m_vec_Enums.push_back(penm);
	return penm;
}

CppFunction* AddFunction(const std::string sName, 
						 const std::string sRetVal, 
						 const std::string sBrief, 
						 const std::string& sCode ) 
{
	CppFunction* pfunc = new CppFunction(sName,   sRetVal,   sBrief, sCode);
	m_vec_Functions.push_back(pfunc);
	return pfunc;
}

CppFunction* AddInternalFunction(const std::string sName, 
								 const std::string sRetVal, 
								 const std::string sBrief, 
								 const std::string& sCode ) 
{
	CppFunction* pfunc  = new CppFunction(sName,   sRetVal,   sBrief, sCode);
	m_vec_InternalFunctions.push_back(pfunc);
	return pfunc;
}

CppStruct* AddStruct(const string sName, const string sBrief)
{
	CppStruct* res = new CppStruct(sName, sBrief);
	m_vec_Struct.push_back(res);
	return res;
}

CppClass* AddClass(const string sName, 
				   const string sBrief, 
				   const CppClass* pClassBase, 
				   bool bHasDestructor=true) 
{
	CppClass* pcls = new CppClass(sName,   sBrief,   pClassBase, bHasDestructor);
	m_vec_Classes.push_back(pcls);
	return pcls;
}

void AddPragmaWarnDisable(unsigned short val) 
{  
	m_vecPragmaWarnDisable.push_back(val); 
}

CppVariable* AddInternalVariable(const  string sName, const  string  sType, const  string sDefaultVal,  const  string  sBrief ) 
{
	CppVariable* pvar = new CppVariable(sName,   sType, sDefaultVal,  sBrief);
   m_vec_InternalVariables.push_back(pvar);
   return pvar; 
}

//! \brief  Построение полного текста  кода.
std::string MakeFullText();	


//! \brief   Запись кода заголовка  в файл.
long Save();


static std::string MakeDivDeclString(const std::string caption) ;

static std::string MakeImplemDivLine() 
{  
  std::string s =  "//============================================================"; 
  return s; 
}
 

private:
  std::vector<std::string> m_vecInclude;
  Vec_Defines     m_vecDefines; 
  std::vector<unsigned short> m_vecPragmaWarnDisable;

  Vec_Enums  m_vec_Enums;
  Vec_Functions   m_vec_Functions;
  Vec_Functions   m_vec_InternalFunctions;

  Vec_CppClasses  m_vec_Classes;
	  
  Vec_Variables  m_vec_InternalVariables;
  Vec_Struct     m_vec_Struct;

	  
};
// end class



//-------------------------------------------------------------------------

}
// end namespace
}
// end namespace


// end file