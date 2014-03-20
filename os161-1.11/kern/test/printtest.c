#include <types.h>
#include <lib.h>
#include <thread.h>

int printtest(int nargs, char **args)
{
	kprintf("Hello World\n");	
	return 0;
	thread_bootstrap();
}
