/** \file
   \brief  Копирование в системный буфер  обмена   и чтение из него.
   
   \todo  Добавить решение для других ос.
*/

#pragma once

#include <string>


namespace gb
{

//! \brief Копирование в системный буфер  обмена   и чтение из него.
namespace clipboard
{
//-----------------------------------------------------

#ifdef WIN32 // пока только для винды.  Незнаю как там с этим в других осях. 

/** \brief Копировать ANSI текст  szText в буфер обмена      */
 bool copyTextToClipBoardA(const char* szText);

/** \brief Прочитать ANSI текст из буфера обмена  в строку   sDest   */
 bool readTextFromClipBoardA( std::string& sDest);

#else

	// ?????

#endif

//-----------------------------------------------------

}
}

// end file