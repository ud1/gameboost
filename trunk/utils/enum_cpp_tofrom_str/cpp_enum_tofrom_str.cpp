/**    Перечисление c++ в строку
 **    Скопировать перечисление в буфер . 
 **    Затем запустить программу. 
 **    Программа создаст временный файл с функциями 
 **    преобразование перечисления в строку/ из строки.
 **    
 **    
 **    
 **    */



#include <gb/str/String.h>
#include <gb/makecppcode/makecppcode.h>
using namespace gb::makecppcode;

#include <windows.h>
#include <gb/clipboard/clipboard.h>

namespace ss = gb::str;
using namespace std;

// открывает файл с заданной программой .
 int OpenFileWithApplA(const char* fname) {
	HINSTANCE hi =  ShellExecuteA(
		NULL, //__in_opt  HWND hwnd,
		"open", //, __in_opt  LPCTSTR lpOperation,
		fname, //__in      LPCTSTR lpFile,
		NULL, //__in_opt  LPCTSTR lpParameters,
		NULL, //__in_opt  LPCTSTR lpDirectory,
		SW_SHOW //, //__in      INT nShowCmd
		);

	if(hi > (HINSTANCE)32) 
		return 0;

	return 0-1;
};
 

std::string make_code_tostr(  const std::vector<std::string>& vitems)
{
	std::string res = "";

  res += "   std::string result;\n\n";

    // begin switch
	  res += "   switch(val) \n";
	  res += "  {\n\n";

	  for(size_t c=0; c<vitems.size(); c++)
	  {
		  // case item
		  res += " case "; 
		  res += vitems[c]; 
		  res += ": \n";

		  res += "   {\n";    
		  res += "    result = \"";  res +=  vitems[c];  res += "\";\n";
		  res += "   }\n    break;\n\n";
	  }

	  // switch default:
  res += "  default:  {  \n\n\n     }\n";

	  // end switch
  res += "  }\n\n";

   // end func
  res += "    return result;\n";

  return res;
}

std::string make_code_fromstr( const std::vector<std::string>& vitems)
{
	std::string res;
	res += "\n";

   for(size_t c=0; c<vitems.size(); c++)
   {

   // begin if compare
   res += "    if( str == \"";  res += vitems[c]; res += "\" )\n";
   res += "    {\n";

   res += "    valOut = ";  res+= vitems[c]; res += ";\n";
   res += "    return true;\n";

   // end if
   res += "    }\n\n";

   }

   res += "    return false;\n";

  return res;
}


bool __extractEnum(vector<string>& vEnumItems, string& enumName, const string& strArg)
{
  vEnumItems.clear();
  enumName = "";

  string str = strArg;
  ss::preprocessCppComments(str);

  std::string sEnumLine ;
  int32_t posit = 0;
  if(!ss::findSubstringBetween(sEnumLine,	  str, '{', '}',   posit ))
  {
	  printf("not found ! ");
	  return  false;
  }

  ss::ksSplit(vEnumItems,  sEnumLine, ',', true );


  if(vEnumItems.size() == 0)
  {
	  printf("Enum not found \n");
	  return false;
  }

 
  // trim vector
  std::string temp, t2;

  for(size_t c=0 ;c<vEnumItems.size(); c++)
  {
	  t2 = "";
	  temp = vEnumItems[c];
	  for(size_t j=0; j<temp.length(); j++)
	  {
		  char curr = temp[j];
		  if(curr == '=')
		  {
			 break;
		  }

		   t2 += curr;
	  }
	 // temp = vEnumItems[c];
	  ss::trim(t2);
	  vEnumItems[c] = t2;
  }


  // хз пока как  извлекать имя
  enumName = "myenum";


   return true;
}


//=================================================
int   main(int argc,   char* argv[])
{

	std::string  str ;
	std::vector<std::string> vec_items;

	if(0)
	{	// test 
		str = "  enum myenum { one, two, three, four  }; " ;
	}

	if(! gb::clipboard::readTextFromClipBoardA(str))
	{
		printf("\n Error read text from clipboard \n\n");
		Sleep(1000);
		return -1;
	}

	if(str.length()==0)
	{
		printf("\n Clipboard empty ! \n");
		Sleep(1000);
		return -1;
	}
	
  string enumName;
 if(!__extractEnum(vec_items, enumName, str))
 {
	 printf(" Error extract enum! ");
	 Sleep(1000);
	 return -1;
 }

 if(vec_items.size() == 0)
 {
    printf("\n   Enum not found ! \n");
	 Sleep(1000);
	 return  -1;
 }

	
 printf("  \n\n  Found items:  \n");
 for(size_t c=0; c<vec_items. size(); c++)
 {
	 printf("%s\n",  vec_items.at(c).c_str() );
 }	
 
   const string sFuncName_tostr = enumName + "_tostr";
   const string sFuncName_formstr = enumName + "_formstr";

   CppHeaderFile* ph = new CppHeaderFile("temp.h", "");


   CppFunction* pfunc_tostr = ph->AddFunction(sFuncName_tostr, "std::string",
	   "enum to string",  make_code_tostr( vec_items) );

  pfunc_tostr->AddParameter("const " + enumName, "val");


   CppFunction* pfunc_fromstr = ph->AddFunction(sFuncName_formstr,
	 "bool", "enum from string", make_code_fromstr( vec_items)  
	   );
   pfunc_fromstr->AddParameter(enumName+"&", "valOut"  );
   pfunc_fromstr->AddParameter("const std::string&", "str");

	//ph->MakeFullText();	


   ph->Save();

   delete ph;
   ph = NULL;

  OpenFileWithApplA( "temp.h"  );

	return 0;
}

