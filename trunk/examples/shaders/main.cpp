#include <gb/graphics/ShaderPreprocessor.h>
#include <gb/fs/LocalFS.h>

#include <iostream>

int main()
{
	gb::fs::LocalFS fs;
	gb::shaders::ShaderPreprocessor shdp(&fs);
	
	std::vector<std::string> macros;
	macros.push_back("MACRO_MUL(x, y)=x*y");
	
	std::string shader;
	
	shdp.load("../shaders/test.vert", macros, shader);
	
	std::cout << shader << std::endl;
	return 0;
}
