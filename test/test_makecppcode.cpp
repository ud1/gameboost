//  тест использования makecppcode
//

#include <gb/makecppcode/makecppcode.h>
#include <windows.h>
#include <stdexcept>

void __openFileWithAppl(const char* fname) 
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
	{
		return  ;
	}

	return ; //0-1;
};

int main()
{
	using namespace  gb::makecppcode;

	CppHeaderFile* phed = new CppHeaderFile("header.h", " ");
	CppClass* pclass= phed->AddClass("myclass",  "", NULL, true);

	pclass->AddMember(DECL_VISIBLE::PUBLIC , "string", "VALUE", "");

	phed->Save();
	__openFileWithAppl("header.h");
	delete phed;



}