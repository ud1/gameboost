/** \file
 \brief Диалоговыен окна и сопутствующее
 
 
   \author ksacvet777
   
   \todo добавить диалоги для других платформ.
*/


#pragma once

#include <gb/Base/Types.h>
#include <string>

namespace gb
{
//! \brief Диалоговыен окна и сопутствующее
namespace dialog
{

//----------------------------------------------------------------------------



/** \brief Открыть диалог выбора файла для открытия ( szFilter пример:  "All\0*.*\0Text\0*.TXT\0";)   */
bool openFileDialog(  std::string& sOutFileName,  const char* szFilter); 

/** \brief Открыть диалог выбора файла для сохранения  ( szFilter пример:  "All\0*.*\0Text\0*.TXT\0";)   */
bool saveFileDialog(  std::string& sOutFileName, const char* szFilter);
 

/** \brief Открыть диалог выбора цвета по float-компонентам  */
bool DialogSelectColor(  float& r,   float& g,   float& b  );


 


//----------------------------------------------------------------------------

}

}

// end file