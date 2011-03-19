#include <gb/engineBlocks/GameApplication.h>

int main()
{
	gb::engine_blocks::GameApplication application(true);
	
	if (!application.init("../data/config.txt"))
		return 0;
	
	application.run();
	
}