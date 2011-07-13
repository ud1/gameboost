/**  \file
 \brief ??????


*/

#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif


namespace gb 
{

	namespace fmath
	{
	
	
	
 
		//! \brief описание состояния пространственого  пересачения объектов
		enum  ObjContainsE   
		{ 
			SC_NOOVERLAP, ///<   объект не касается другого объекта
			SC_CONTAINSFULLY, ///<   объект  полностью расположен  в другом
			SC_CONTAINSPARTIALLY  ///< объект частично содержится в другом
		};

	
	
	
	
	
	
	
	
	}
}
