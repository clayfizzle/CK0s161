#include <types.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <lib.h>
#include <machine/spl.h>
#include <test.h>
#include <synch.h>
#include <thread.h>
#include <scheduler.h>
#include <dev.h>
#include <vfs.h>
#include <vm.h>
#include <syscall.h>
#include <version.h>

int
sys_helloworld(){
	kprintf("hello world,  booya!\n");
	return 0;
}

int
sys__exit()
{
	thread_exit();
	return 0;

}

int
sys_printint(int input)
{
	kprintf("%d\n", input);
	return 0;
}

int
sys_printstring(char* input) {

	kprintf("%s\n",input);
	return 0;

}
