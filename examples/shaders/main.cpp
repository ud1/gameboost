// #include <gb/shaders/ShaderPreprocessor.h>
// #include <gb/fs/LocalFS.h>
// 
// #include <iostream>
// 
// int main()
// {
// 	gb::fs::LocalFS fs;
// 	gb::shaders::ShaderPreprocessor shdp(&fs);
// 	
// 	std::vector<std::string> macros;
// 	macros.push_back("MACRO_MUL(x, y)=x*y");
// 	
// 	std::string shader;
// 	
// 	shdp.load("../shaders/test.vert", macros, shader);
// 	
// 	std::cout << shader << std::endl;
// 	return 0;
// }

#include <gb/base/Timer.h>
#include <iostream>
using namespace gb::base;

struct TimerTest {
	void start()
	{
		timer.reset();
	}
	
	void finish(){
		std::cout << timer.getTime() << std::endl;
	}
	
	virtual void virtCall()
	{
		timer.getTime();
	}
	
	void call()
	{
		timer.getTime();
	}
	
	Timer timer;
};

const int CALL_NUMBER = 100000000;

void testVirt(TimerTest *test)
{
	test->start();
	for (int i = 0; i < CALL_NUMBER; ++i)
	{
		test->virtCall();
	}
	test->finish();
}

void testNonVirt(TimerTest *test)
{
	test->start();
	for (int i = 0; i < CALL_NUMBER; ++i)
	{
		test->call();
	}
	test->finish();
}

int main()
{
	TimerTest *test = new TimerTest;
	testVirt(test);
	testNonVirt(test);
	return 0;
}