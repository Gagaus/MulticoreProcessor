#include <stdio.h>

#define LOCK_ADDRESS 0x800000;

volatile int *lock_aux = ( volatile int *) LOCK_ADDRESS;

int * lockit(int *ptr);

typedef struct __lock_t {
	int flag;
} lock_t;

void lock_init(lock_t *lock) {
	lock->flag = 0;
}

void lock(lock_t *lock) {
	int* plock = &lock->flag;
	asm volatile ("ll $2, %0 \n"\
		"bnez $2,  0 \n"\
		"addi $2, $0, 1 \n"\
		"sc   $2, %0 \n"\
		"beqz $2, 0 "\
		: "=m" (*plock)
		: 
		: );
	// lockit();
}

void unlock(lock_t *lock) {
	lock->flag = 0;
}

main () {
	printf("Teste");

}
// rodar os asssemblys
// adicionar ao make
// integrar ao resto do código