
#include <gb/clipboard/clipboard.h>
#include <gb/Config.h>



namespace gb 
{
namespace clipboard 
{


#ifdef WIN32

#ifndef _WINDOWS_
    #error Отсутствует включение windows.h
#endif


//===================================================================
 bool copyTextToClipBoardA(const char* szText) 
{
 
    //    Пример записи и чтения текста.
 
    //std::string source = "src";
    const int TXTLEN = (int)strlen(szText);

    //в эту переменную нужно записать текст, который в дальнейшем поместится в буфер обмена
    //запись текста в буфер обмена
    if(OpenClipboard( NULL ))//открываем буфер обмена
    {
        HGLOBAL hgBuffer;
        char* chBuffer;
        EmptyClipboard(); //очищаем буфер
        hgBuffer= GlobalAlloc(GMEM_DDESHARE,  TXTLEN + 1 );//выделяем память
        chBuffer= (char*)GlobalLock(hgBuffer); //блокируем память
        strcpy(chBuffer,   szText  );
        GlobalUnlock(hgBuffer);//разблокируем память
        SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
        CloseClipboard(); //закрываем буфер обмена

        return true;
    }


   return false;
};

//===================================================================
 bool readTextFromClipBoardA(  std::string& sDest) 
 {
    bool bresult =  false;
   sDest = "";

 
   //чтение текста из буфера обмена
 
   if ( OpenClipboard(NULL) )//открываем буфер обмена
   {
       HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
       char* chBuffer= (char*)GlobalLock(hData);//блокируем память

       if(chBuffer)
       {
         sDest = chBuffer;
       }
       else
       {
           bresult = false;
       }
       
       GlobalUnlock(hData);//разблокируем память
       CloseClipboard();//закрываем буфер обмена

       bresult =  true;
   }  

    return bresult;
};


#endif // WIN32 



}
}

// end file