﻿#include "stdafx.h"

#include "color3.h"
#include "color_functions.h"


inline Color3f& Color3f::operator = (const uicolor32_t col) 
{
	r = colorExtractRf(col);
	g = colorExtractGf(col);
	b = colorExtractBf(col); 
	return *this;
};


