
// temp !!
//#include "d3d9pch.h"
//#include "stdafx.h"


#include <gb/util/SourceInit.h>

namespace gb
{

namespace util
{


//==============================================================
	SourceInit::SourceInit(
		gb::util::SourceInit::TFunc_SourceInitialize funcInit, 
		gb::util::SourceInit::TFunc_SourceFinalize funcFinal, 
		void *pUserData)
	{
     m_Func_SourceInitialize = funcInit;
	 m_Func_SourceFinalize = funcFinal;
	 m_pUserData = pUserData;


     if(m_Func_SourceInitialize)
	 {
       m_Func_SourceInitialize(m_pUserData);
	 }


	}


//=========================================================================
	SourceInit::~SourceInit()
	{
		if(m_Func_SourceFinalize)
		{
			m_Func_SourceFinalize(m_pUserData);
		}
	}





}

}
// end file