#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <test.h>

static struct semaphore *tsem = NULL;
static struct lock *tlock = NULL;
static int counter = 0;


static
void
init_sem(void)
{
	if(tsem==NULL)
	{
		tsem = sem_create("tsem", 0);
		if(tsem == NULL){
			panic("thread test: sem_create failed\n");
								}
					}
			}

static
void
init_lock(void)
{
	if(tlock==NULL)
	{
		tlock = lock_create("tlock");
		if(tlock==NULL){
			panic("thread test: lock_create failed\n");
				}
		}
}

int 
child(void *arg1, int arg2)
{
	kprintf("Hello I'm thread %d\n", arg2+1);
	V(tsem);
	
	return 0;
}

int
threadfun(int nargs, char **args)
{
	if (nargs!=2)
		return 0;
	char name[16];
	int i, result;
	int nthreads = atoi(args[1]);
	init_sem();
	kprintf("Attempting to spin up %d threads...\n", nthreads);
	for(i = 0; i < nthreads; i++)
	{
		snprintf(name, sizeof(name), "threadfork%d", i);
		result = thread_fork(name, NULL, i, child, NULL);
		P(tsem);
		if(result) {
				panic("thread test: thread_fork failed %d)\n", result);
			}
		
		
	}

	kprintf("thread test done\n");

	return 0;		
}

int
unsafechild(void *arg1, int arg2)
{
	int i;
	for(i = 0; i < arg2; i++)
	{
		lock_acquire(tlock);
		counter++;
		lock_release(tlock);
	}
	V(tsem);

	return 0;
}

int
unsafethreadcounter(int nargs, char** args)
{
	if(nargs != 3)
		return 0;
	char name[16];
	int i, result;
	int nthreads = atoi(args[1]);
	int numLoops = atoi(args[2]);
	counter = 0;
	init_sem();
	init_lock();
	kprintf("Attempting to spin up %d threads\n", nthreads);
	
	for(i = 0; i < nthreads; i++)
	{
		snprintf(name, sizeof(name), "unsafethread%d", i);
		result = thread_fork(name, NULL, numLoops, unsafechild, NULL);
		if(result)
		{
			panic("unsafe thread test: thread_fork failed %d)\n", result);
		}


	}

	for(i=0;i<nthreads;i++)
		P(tsem);

	kprintf("unsafe thread test done\n");
	kprintf("unsafe counter is: %d\n", counter);


	return 0;

}
