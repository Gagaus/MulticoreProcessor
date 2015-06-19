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
	int* plock = lock->flag;
	asm ("
		ll 	r2, plock(r0) \n\
		bnez r2,  lockit \n\
		addi r2, r0, 1 \n\
		sc   r2, plock(r0) \n\
		beqz r2, lockit 
	");
	lockit();
}

void unlock(lock_t *lock) {
	lock->flag = 0;
}

// rodar os asssemblys
// adicionar ao make
// integrar ao resto do código