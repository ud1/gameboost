#pragma shader echo (#version 130)

#define SQR(x) x*x

#include "./test_include.h"

void main()
{
	vec4 p = vec4(Vertex*10, 1);
	gl_Position = MVP * p;
	
	float fog_distance = SQR(10) + MACRO_MUL(p.x, 42);
	
	color = vec3(0.6, 0.6, 0.6);
}
