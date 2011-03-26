#include <gb/engineBlocks/StringFlyweight.h>

#include <iostream>

using namespace gb::engine_blocks;
using namespace gb::base;

int main()
{
	StringFlyweightFactory factory;

	PStringFlyweight str1 = CreateRFHolder(factory.create("Hello"));
	PStringFlyweight str2 = CreateRFHolder(factory.create("World"));
	PStringFlyweight str3 = CreateRFHolder(factory.create("Hello"));
	
	std::cout << *str1 << std::endl;
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	std::cout << str3 << std::endl;

	return 0;
}