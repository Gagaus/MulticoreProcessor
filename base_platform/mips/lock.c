#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define LOCK_ADDRESS 0x800000;

int procN, procCounter = 0; 

typedef struct __lock_t {
	int flag;
} lock_t;

lock_t *lock_aux = ( lock_t *) LOCK_ADDRESS;

void lock_init(lock_t *lock) {
	lock->flag = 0;
}

void lock(lock_t *lock) {
	int* plock = &lock->flag;
	int r;
	LoopLock:do {
	asm volatile ("ll %1, %0 \n"\
		: "=m" (*plock), "=r"(r)
		: 
		: );
	} while (r != 0);
	r = 1;

	printf("To no core %d\n", procN);

	asm volatile ("sc %1, %0 \n"\
		: "=m" (*plock), "=r"(r)
		: 
		: );

	if (r == 0)
		goto LoopLock;
}

void unlock(lock_t *lock) {
	lock->flag = 0;
}

void RecursiveHello( int n, int procN) {
	if (n) {
		printf("Hi from processor PowerPC %d!\n", procN);
		RecursiveHello(n-1, procN);
	}
}

main () {
	procN = procCounter;
	procCounter++;

	lock_init(lock_aux);
	printf("Teste");

	fork();
	lock(lock_aux);
	procN = procCounter;
	procCounter++;
	RecursiveHello(10, procN);
	unlock(lock_aux);

	return 0;
}

// rodar os asssemblys
// adicionar ao make
// integrar ao resto do código