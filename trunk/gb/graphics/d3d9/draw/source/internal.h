/** \file
 \brief   Для внутреннего использования draw 
 
 
 */
 

 #pragma once
 
typedef void (__cdecl *TFuncRelease)(void* pUserData); 

//! зарегистрировать функцию удаления
 bool __registerOnReleaseDataProc(TFuncRelease func, void* pUserData);




// end file