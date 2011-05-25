/** \file  makecppcode.h
 \brief Очень простое решение для построения cpp-кода. 
    Немного удобнее, чем набивание просто текстом.


 \author ksacvet777

  \todo поменять константы на указательные
  \todo Прокомментировать
  \todo Добавить методы доступа в объектам в векторах.
  \todo  Добавить примеров.
  \todo  расширить функционал.  



*/


#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>

#pragma warning(push)
#pragma warning(disable : 4290)

namespace gb
{


/**  \brief  Очень простое решение для построения cpp-кода. 
           Немного удобнее, чем набивание просто текстом.       */
namespace makecppcode
{

//-------------------------------------------------------------------------


 using    std::string;

#pragma  warning( push )
#pragma  warning(disable : 4996)
#pragma  warning(disable : 4297) // trow warning

static const char*  SC_BOOLEAN     =  "bool";
static const char*  SC_VOID        =  "void";
static const char*  SC_INT         =  "int";
static const char*  SC_UINT        =  "unsigned int";
static const char*  SC_LONG        =  "long";
static const char*  SC_ULONG       =  "unsigned long";
static const char*  SC_FLOAT       =  "float";

static const char  SC_HRESULT[]    =  "HRESULT";

 
 

template <class T, bool owned>
//! \brief Простой вектор для указателей с самоудалением. вместо бустовского.
class vector_pointers :  public std::vector<T*> 
{
public:

	 vector_pointers() {}
	~vector_pointers()
	 {
		if(!owned) return ;

	  for(size_t c=0; c<size(); c++)
	  {
		  T* p = at(c);
		  if(p) delete p;
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

   string MakeVarDeclStr() const;

};
// end class

typedef   vector_pointers<CppVariable,true>    Vec_Variables;


//! \brief  Определение в коде. например #define name  value  .
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

   //! \brief Получить текст декларации .
   string MakeDeclarationString() const;

};

 
typedef  vector_pointers<CppDefine,true> Vec_Defines;



//! \brief Декларация перечисления в коде.
class CppEnum {
public:
   const  string m_sName;  ///< имя
   const  string m_sBrief; ///<	бриф-комментарий в стиле doxygen

   class EnumItem {
   public:
	    string m_sItemValue;
	    string m_sBriefLine;

		EnumItem() {}
   };

	CppEnum(const  string sName, const  string sBrief) 
		: m_sName(sName), m_sBrief(sBrief) 
	{}

	//! добавить пункт перечисления. Параметры(имя и комментарий)
	void AddEnumItem(const string sItemValue, 
					 const  string sBriefLine) 
	{
		 EnumItem ei;
		 ei.m_sItemValue = sItemValue;
		 ei.m_sBriefLine = sBriefLine;
		   m_vecItems.push_back(ei);
	}

 //! \brief  Получить текст декларации .
 string MakeDeclaration() const ;


 std::vector<EnumItem> m_vecItems;

};

 
typedef  vector_pointers<CppEnum,true> Vec_Enums;



//! \brief Параметр функции/метода.
class CppFuncParameter {
public:
   const string m_sType; ///<  тип параметра (например float)
   const string m_sName; ///<   имя параметра (например  value)
   const string m_sComment;	///< комментарий 

	CppFuncParameter( const string sType, 
					  const string sName, 
					  const string sComment="" ) 
		: m_sType(sType), 
		  m_sName(sName), 
		  m_sComment(sComment)  
	{}

	//! \brief  Получить текст декларации .
	string MakeDeclString( ) const 
	{
			string s;

			s +=  m_sType;
			s += " ";
			s += m_sName;
	 
			return s;
	}


};


typedef  vector_pointers<CppFuncParameter,true>  Vec_FuncParams;



//! \brief  Функиция в коде.
class CppFunction {
public:
  const string m_sName; ///< имя . Например MyFunction. 
  const string m_sRetVal; ///< Тип возвр. значения. Например void. 
  const string m_sBrief; ///<	комментарий в стиле dozygen.
 

      /**  \brief Конструктор
	    \param sName - имя . Например MyFunction.
	    \param sRetVal - Тип возвр. значения. Например void.
	    \param sBrief - комментарий в стиле dozygen.
	    \param sCode - код функции. В код можно добавить с помощью AppendStrToCode.	  
	  */
	  CppFunction(const string sName, 
				  const string sRetVal, 
				  const string sBrief, 
				  const string& sCode )
		  : m_sName(sName), 
		    m_sRetVal(sRetVal), 
			m_sBrief(sBrief)   
		{  
		    m_sCode += sCode;  
		}


	//! \brief Добавить параметр.
	CppFuncParameter* AddParameter(const string sType, 
					  const string sName, 
					  const string sComment="") 
	{
	   CppFuncParameter* par = new CppFuncParameter(sType,  sName, sComment); 
			m_vec_FuncParams.push_back(par);
			return par;
	}

	//! Получить текст декларации .
	virtual  string  MakeDeclarationString(
						bool bIncBriefComment, 
						const char* szLineBeforeName=NULL) const;

	//! Получить текст  реализации .
	virtual  string  MakeImplementationString(const char* szLineBeforeName=NULL) const 
	{
		 string  s;
		s += MakeDeclarationString(false, szLineBeforeName);
		s += "\n{\n";
		s += GetCodeText();
		s += "\n};\n\n";
		return s ;
	}

	//! \brief получить  код функции.  
	 string  GetCodeText() const {  return m_sCode; }

	//!	\brief Добавить текст к коду функции.
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
	const string m_sType;  ///< тип.
    const string m_sName;  ///< имя.
	const string m_sBrief;   ///< бриф-комментарий.
	const string m_sBeforeDecl;	///< строка перед декларацией.

	CppMember(const string sType, 
			  const string sName, 
			  const string sBrief, 
			  const  string  sBeforeDecl=""  
			  ) 
		: m_sType(sType), 
		  m_sName(sName), 
		  m_sBrief(sBrief), 
		  m_sBeforeDecl(sBeforeDecl) 
	{}

	//! Получить текст декларации .
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
					const  string  sName, 
					const  string  sRetVal, 
					const  string  sBrief, 
					const  string & sCode,
					const bool bForceImplemIntoDecl )

		: CppFunction(sName,  sRetVal,  sBrief,   sCode), 
		     m_pClassOwner(pClassOwner),
		     m_bForceImplemIntoDecl(bForceImplemIntoDecl)  
	{}


	 string  MakeDeclarationString(bool bIncBriefComment ) const;
	 string  MakeImplementationString() const;


	const bool IsForceImplemIntoDecl() const 
	{ 
		return m_bForceImplemIntoDecl; 
	}

	void SetLineAfterDecl(const  string  s) 
	{ 
	  m_sLineAfterDecl = s;
	}

private:
   const CppClass* m_pClassOwner;
   bool m_bForceImplemIntoDecl;
    string  m_sLineAfterDecl;


};
// end class

typedef  vector_pointers<CppClassMethod,true>   Vec_ClassMethods;


/** \brief Структура в коде. 
 В отличие от класса нет спецификаторов доступа и методов.  */
class CppStruct{
public:

	const string m_sName;  ///< 
	const string m_sBrief; ///< 

	CppStruct(const string sName, const string sBrief) 
		: m_sName(sName), m_sBrief(sBrief)  
	{}

	virtual ~CppStruct() {}

	CppMember* addMember(const string& sType, const string& sName, const string& sBrief)
	{
	   CppMember* res = new CppMember(sType, sName, sBrief);
	   m_vec_members.push_back(res);
	   return res;
	}

 	 string    MakeDeclarationString() const 
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


//! \brief   Класс
class CppClass {
public:
  const string m_sName;	///< 
  const string m_sBrief; ///< 
  const CppClass* m_pClassBase;	///< 
  const bool m_bHasDestructor;   ///< 

	  class Declaration 
	  {
	  public:
		  Vec_ClassMembers    m_vec_ClassMembers;
		  Vec_ClassMethods    m_vec_ClassMethods;
		  Vec_ClassMethods    m_vec_ClassConstructors;
	  
	  };

	//! \brief  
    CppClass(const string sName, 
			 const string sBrief, 
			 const CppClass* pClassBase, 
			 bool bHasDestructor=true) 
           : m_sName(sName),  
		     m_sBrief(sBrief), 
			 m_pClassBase(pClassBase), 
			 m_bHasDestructor(bHasDestructor)  
	{}

	//! 
	CppMember* AddMember(const DECL_VISIBLE::e dv, 
						 const string sType, 
						 const string sName, 
						 const string sBrief, 
						 const  string  sBeforeDecl="") 
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

	//! 
	CppClassMethod* AddMethod(const DECL_VISIBLE::e dv, 
							  const  string  sName, 
							  const  string  sRetVal, 
							  const  string  sBrief, 
							  const  string & sCode, 
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

	//! 
	CppClassMethod* AddPublicConstructor(const  string  sBrief, 
										 const  string  sInitLine,  
										 const  string & sCode, 
										 bool bForceImplemIntoDecl ) 
	{

		CppClassMethod* pm = new CppClassMethod( this, m_sName,  "", sBrief,  
			     sCode,  bForceImplemIntoDecl );
		pm->SetLineAfterDecl(sInitLine);
		m_decl_public.m_vec_ClassConstructors.push_back(pm); 
		return pm;
	}

	///< 
	void AddCodeToDestructor(const  string & sCode) throw(std::runtime_error&)
	{
		if(!m_bHasDestructor) 
		{
			throw	( std::runtime_error("Class no have destructor")   );
			return;
		}
		m_sDestrCode += sCode;
	}
 
	 string    MakeDeclarationString() const ;
	 string    MakeImplementationString() const ;
	   
private:

	Declaration m_decl_public;
	Declaration m_decl_protected;
	Declaration m_decl_private;

	 string  m_sDestrCode;
 
};
// end class
 
typedef  vector_pointers<CppClass,true> Vec_CppClasses;


//!  \brief  c++ заголовок
class CppHeaderFile {
public:
  const string m_sHeaderFilename; ///<  имя файла заголовка . В этот же файл и будет сохранение
  const string m_sHeaderBrief;   ///< бриф-комментарий в стиле doxygen .

  
   CppHeaderFile(const string sHeaderFilename, 
			     const string sHeaderBrief) 
         : m_sHeaderFilename(sHeaderFilename), 
	       m_sHeaderBrief(sHeaderBrief)  
   {}

/** \brief Добавить директиву включения файла sInclude.  
  Например AddInclude("source.h") вставит в код #include "source.h" */
string&  AddInclude(const string sInclude)	   
{
  string s = sInclude;
  m_vecInclude.push_back(s);
  return m_vecInclude[m_vecInclude.size()-1];
}

/**  \brief Добавить  сырое определение  .	 
   например AddHeaderDefineStr("MYDEF", "define line", "")  
   вставит в код #define MYDEF   define line  */
CppDefine* AddHeaderDefine(const string sDefName, const string sValue, const string sBrief);
 

/**  \brief Добавить строковое определение  .	 
   например AddHeaderDefineStr("MYDEF", "my_string", "")  
   вставит в код #define MYDEF  "my_string"   */
CppDefine* AddHeaderDefineStr(const string sDefName, const string sValue, const string sBrief) ;

/**  \brief Добавить определение  .	 
   например AddHeaderDefineInt("MYDEF", 777, "")  
   вставит в код #define MYDEF  777   */
CppDefine* AddHeaderDefineInt(const string sDefName, const int val, const string sBrief) ;

/**  \brief Добавить float-определение  .	 
   например AddHeaderDefineFloat("MYDEF", 1.44f, "")  
   вставит в код #define MYDEF  1.44f   */
CppDefine* AddHeaderDefineFloat(const string sDefName, const float val, const string sBrief) ;

/**  \brief Добавить целочисленое   определение  в hex-виде .	  
  например AddHeaderDefineHex("MYDEF", 255, "")  
  вставит в код #define MYDEF 0xFF   */
CppDefine* AddHeaderDefineHex(const string sDefName, const unsigned int val, const string sBrief) ;


 /**  \brief Добавить перечисление  . */
CppEnum* AddEnum(const  string  sName, const  string  sBrief) 
{
	CppEnum* penm = new CppEnum( sName,  sBrief );
	m_vec_Enums.push_back(penm);
	return penm;
}

 /**  \brief Добавить функцию  . */
CppFunction* AddFunction(const  string  sName, 
						 const  string  sRetVal, 
						 const  string  sBrief, 
						 const  string & sCode ) 
{
	CppFunction* pfunc = new CppFunction(sName,   sRetVal,   sBrief, sCode);
	m_vec_Functions.push_back(pfunc);
	return pfunc;
}

 /**  \brief  внутренюю статическую функцию  . */
CppFunction* AddInternalFunction(const  string  sName, 
								 const  string  sRetVal, 
								 const  string  sBrief, 
								 const  string & sCode ) 
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
 string  MakeFullText();	


//! \brief   Запись кода заголовка  в файл.
long Save();


 

private:
  std::vector< string > m_vecInclude;
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

//! \brief  Записать строку в файл.
bool saveString( string & s,  const char* fname);


//! строчка визуального разделения  декларации
inline string    MakeDivDeclString(const string& caption)   
{
   string  s;
   s += "\n//-----------------------------------------------\n";
   s += "//         "; s += caption;
   s += "\n//-----------------------------------------------\n\n";
  return s;
};

//! строчка визуального разделения методов в коде
inline  string  MakeImplemDivLine() 
{  
  string  s =  "//============================================================"; 
  return s; 
}


//-------------------------------------------------------------------------

}
// end namespace
}
// end namespace

#pragma warning(pop)

// end file