// утилита для поиска и включения всех cpp-файлов
//

#include "stdafx.h"
#include <boost/foreach.hpp>

namespace ff = gb::system::filefunc;
using namespace std;

#pragma  warning (disable : 4297)

void throw_err() 
{  
	throw runtime_error("Error");
}

void convert(vector<string>& dest,  const std::vector<ff::PathDataA>& src)
{
   dest.clear();
   string temp;
   for(size_t c=0; c<src.size(); c++)
   {
	temp = src[c].path;
	dest.push_back(temp);
   }

}

void openfile(const char* fname)  throw()
{
	HINSTANCE hi =  ShellExecuteA(
		NULL, //__in_opt  HWND hwnd,
		"open", //, __in_opt  LPCTSTR lpOperation,
		fname, //__in      LPCTSTR lpFile,
		NULL, //__in_opt  LPCTSTR lpParameters,
		NULL, //__in_opt  LPCTSTR lpDirectory,
		SW_SHOW //, //__in      INT nShowCmd
		);

	if(hi > (HINSTANCE)32) 
		return ;

	throw_err();

}

void raplaceslash(vector<string>& v)
{
	for(size_t c=0; c<v.size(); c++)
	{
		string& str = v[c];
		for(size_t j=0; j<str.length();  j++)
		{
			if( str[j] == '\\' )
			{
				str[j] = '/';
			}

		}


	}

}

void __print(const char* str)
{
	 printf("%s\n", str);
	 Sleep(500);	 
}

void extract_arg(string& dir, const int argc,   char* argv[] )
{
	
 
	if( argc <2 )
	{
		printf("need input dir \n");
		Sleep(1000);
		return;
	}
 	
	dir = argv[1];

	//GB_MBOX( dir.c_str() );
	// dir = "j:\\!!GB\\gameboost\\gb\\fmath\\context.h";

	char buffer[MAX_PATH];
	buffer[0] = 0;

	if( !ff::extractFilePathA( buffer,  dir.c_str() ) )
	{
	  printf("Error extract file name \n");
	  Sleep(1000);
	  throw_err();	
	}

  dir = buffer;
}

int  main(int argc, char* argv[])
{

  string dir;
  extract_arg(dir, argc, argv );
  printf("DIR: %s  \n", dir.c_str() );
  if(dir.length()==0)
  {
	  __print("Empty dir ");
	   return 0;
  }
 

	vector<ff::PathDataA> vector_source;
	vector_source.reserve(256);

	__print("Search files");
	ff::findFilesA(dir.c_str(), true, "cpp", vector_source );

	// convert
	vector<string> vec;
	convert(vec, vector_source);

	// repl slach
	raplaceslash(vec);
 
	// print
	__print("print");
	for(size_t c=0; c<vec.size(); c++)
	{
		cout << vec[c] << endl;
	}


	std::string text;
	text.reserve(1024);
	text += "\n";


	for(size_t c=0; c<vec.size(); c++)
	{
		text += " #include \"";
		text += vec[c];
		text += "\"\n";
 
	}


	string temp_fname = "c:\\temp\\temp_out.h";
	if(!ff::saveBinDataToFileA( temp_fname.c_str() , text.c_str(), (unsigned int)text.length() ) )
	{
		throw_err();
	}
   openfile( temp_fname.c_str()  );


 //system("pause");
	return 0;
}

