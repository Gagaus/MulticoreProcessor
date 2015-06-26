#include <stdio.h>
#include <stdlib.h>

volatile int procCounter = 0;

#define LOCK_ADDRESS 0x800000;

int procN;

typedef struct __lock_t {
	int flag;
} lock_t;

lock_t *lock_aux = ( lock_t *) LOCK_ADDRESS;

void lock_init(lock_t *lock) {
	lock->flag = 0;
}

void lock(lock_t *lock, int procN) {
	int* plock = &lock->flag;
	int r, one;
	do {
		one = 1;
		asm ("ll %0, %2 \n"\
			"sc %3, %1 \n"\
			: "=r" (r), "=m"(*plock)
			: "m" (*plock), "r" (one)
			: );
	} while (!(r == 0 && one == 1  && *plock == 1));


	printf("Peguei o lock %d\n",procN);
}

void unlock(lock_t *lock,  int procN) {
	lock->flag = 0;
	printf("Soltei o lock %d\n", procN);
}

void RecursiveHello( int n, int procN) {
	if (n) {
		printf("Hi from processor PowerPC %d!\n", procN);
		RecursiveHello(n-1, procN);
	}
}

int main(int argc, char *argv[]){
	// trocar estas linhas pela inicialização no prim core
	int i; 
	lock_init(lock_aux);
	for (i = 0; i < 100000; i++) {}  

	lock(lock_aux, procN);
	procN = procCounter;
	procCounter++;
	RecursiveHello(10, procN); 
	unlock(lock_aux, procN);
	
	// exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}
