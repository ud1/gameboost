// тест и десонстрация использования ini
//

#include "stdafx.h"

#include <gb/base/ini.h>



int  main()
{

	gb::base::ini::Ini ini;
   ini.setValue("section", "dfsfsd", "fsddfsf");
   ini.setValue("section", "vcvx", "fdg");
   ini.setValue("section", "vbxbvb", "bmbnmbn");
   ini.setValue("section", "er5435", "hgfdhfh");	 
   ini.setValue("section", "cxvxxcv", "fdfggfd");

   std::cout << ini;

   std::string str;
  ini.writeToStr(str);
  ini.writeToFileA("myini.ini");
  ini.clearAllData();

  std::cout << "\n------------\n\n";

  ini.readFromFileA("myini.ini");
   std::cout << ini;

 



 int _end =0;


	return 0;
}

