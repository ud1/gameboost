#include <gb/engineBlocks/BaseApplication.h>

int main()
{
	gb::engine_blocks::BaseApplication application;
	
	if (!application.init())
		return 0;
	
	application.run();
	
}