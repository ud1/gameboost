#include <gb/base/Timer.h>

#include <stdio.h>

int test();
int virt_test();

int main()
{
	gb::base::Timer timer;
	
	const int loops = 100;
	const int count = 100000;
	int res;
	
	double t, test_time = 0.0, virt_time = 0.0;
	
	for (int k = 0; k < loops; ++k)
	{
		res = 0;
		timer.reset();
		for (int i = 0; i < count; ++i)
			res += test();
		t = timer.getTime();
		test_time += t;
		printf("test: %f %d\n", t, res);
		
		res = 0;
		timer.reset();
		for (int i = 0; i < count; ++i)
			res += virt_test();
		t = timer.getTime();
		virt_time += t;
		printf("virt_test: %f %d\n", t, res);
	}
	
	printf("\n%f %f %f\n", test_time, virt_time, (virt_time - test_time)/test_time);
	
	return 0;
}