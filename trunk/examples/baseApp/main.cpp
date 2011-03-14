#include <gb/engineBlocks/BaseApplication.h>

int main()
{
	gb::engine_blocks::BaseApplication application;
	
	if (!application.init("../data/config.txt"))
		return 0;
	
	application.run();
	
}