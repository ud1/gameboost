#include "d3d9pch.h"

#include <gb/graphics/d3d9/draw/draw.h>
#include "internal.h"
#include <gb/t/func.h>
#include <assert.h>

//=====================================================================



//-------------------------------------------------------

//  STL и подобное тут не катит  
//

//! размер массива в классе	__OnRelDataFunctions
#define __ARRAY_LEN   32

//! хранит обр. вызовы для draw
class __OnRelDataFunctions
{
public:
	__OnRelDataFunctions()
	{
		__init();
	}

	struct DataFuncItem
	{
		TFuncRelease func;
		void* pUserData;

		bool empty() const 
		{
			if(func) return false;
			if(pUserData) return false;
			return true;
		}
	};

	DataFuncItem  array[__ARRAY_LEN];


	//-------------------------------------------
	void __init()
	{
		static bool stb_firstcall = true;
		if(stb_firstcall)  return  ;

		memset(array,0, sizeof(array));

		stb_firstcall = false;
	}

	//-----------------------------------------------------
	bool addfunc(TFuncRelease func, void* pUsedData)
	{
		__init();
		const int INDEX = gb::t::func::findFirstEmptyFromBuffer(array, __ARRAY_LEN);
		if(INDEX<0)
		{
			// full !
			assert(false&&" array is full ");
			return false;
		}

		array[INDEX].func=func;
		array[INDEX].pUserData=pUsedData;

		return true;
	}

	//-----------------------------------------------------
	void doExecuteFunctions()
	{
		__init();
		for(int c=0; c<__ARRAY_LEN; c++)
		{
			if(array[c].func)
			{
				try
				{
					array[c].func(array[c].pUserData);
				}
				catch (...)
				{
					assert(false && " call func exception!");
					throw std::runtime_error("call func exception!");
				}


			}

		}
	}


};

static	__OnRelDataFunctions  g_OnRelDataFunctions;

 
//=====================================================================

namespace gb       
{
namespace graphics 
{
namespace d3d9     
{
namespace draw     
{


//=========================================================================
GB_D3D9_API HRESULT ReleaseAllInternalData()
{
	HRESULT hr =0;

	g_OnRelDataFunctions.doExecuteFunctions();
 
	return hr;
};

//=========================================================================

}
// end namespace
}
// end namespace
}
// end namespace
}
// end namespace



//=========================================================================
bool __registerOnReleaseDataProc(TFuncRelease func, void* pUserData)
{
	if(!g_OnRelDataFunctions.addfunc(func,pUserData))
	{

		assert(false && " register error ! ");
		return false;
	}


	return true;
};



// end file