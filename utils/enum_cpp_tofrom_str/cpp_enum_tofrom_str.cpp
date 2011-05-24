// Перечисление c++ в строку


 

#include <gb/str/String.h>

namespace ss = gb::str;

std::string make_decl_h()
{
	std::string res ;
	 res += "\n";
	 res += "//----------------------------------------------------\n";
	 res += "//                        H\n";
	 res += "//----------------------------------------------------\n";
	 res += "\n";
	return res;
}

std::string make_decl_cpp()
{
	std::string res ;
 
	 res += "\n";
	 res += "//----------------------------------------------------\n";
	 res += "//                       CPP\n";
	 res += "//----------------------------------------------------\n";
	 res += "\n";


	return res;
}



std::string make_code_tostr(bool bDeclOnly,  const std::vector<std::string>& vitems)
{
	std::string res = "";
	
 //res += make_decl_h();

	if(bDeclOnly)
	{
     res += "std::string myenum_tostr(const myenum val);\n";
	 return res;
	}


 res += make_decl_cpp();


  // begin function 
  res += "std::string myenum_tostr(const myenum val)\n";
  res += "{\n";
  res += "   std::string result = \"\";\n\n";


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


     }// for

	  // switch default:
  res += "  default:  {  \n\n\n     }\n";



	  // end switch
  res += "  }\n\n";


   // end func
  res += "    return result;\n";
  res += "};\n";

  return res;
}

std::string make_code_fromstr(bool bDeclOnly,  const std::vector<std::string>& vitems)
{
	std::string res;
	res += "\n\n";


 //  res += make_decl_h();
	if(bDeclOnly)
	{
      res += "bool myenum_fromstr(myenum& valOut, const std::string& str);\n";
	  return res;
	};



   	res += "\n\n";

   res += "bool myenum_fromstr(myenum& valOut, const std::string& str)\n";
   res += "{\n";

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
   // if


   res += "    return false;\n";
   res += "};\n\n";

  return res;
}



//=================================================
int   main(int argc,   char* argv[])
{

	std::string  str  = "  enum myenum { one, two, three, four  }; " ;
	
	ss::preprocessCppComments(str);

	std::string sEnumLine ;
	int32_t posit = 0;
	if(!ss::findSubstringBetween(sEnumLine,	  str, '{', '}',   posit ))
	{
	  printf("not found ! ");
	  return -1;
	
	}

	std::vector<std::string> vec_items;
	ss::ksSplit(vec_items,  sEnumLine, ',', true );

	if(vec_items.size() == 0)
	{
	 printf("Enum not found \n");
	 return -1;
	}

	// trim vector
	std::string temp;
	for(size_t c=0 ;c<vec_items.size(); c++)
	{
	  temp = vec_items[c];
	  ss::trim(temp);
	   vec_items[c] = temp;
	}

	printf("  \n\n  Found items:  \n");
	for(int c=0; c<vec_items. size(); c++)
	{
	 printf("%s\n",  vec_items.at(c).c_str() );
	}



   int _stop = 0;


   std::string scode = make_code_tostr(vec_items);

   scode += "\n\n//*******************************\n\n"	;
   scode += make_code_fromstr(vec_items);

   ss::saveStrToFileA(scode, "z:\\temp\\enum_code.h"  );


	return 0;
}

