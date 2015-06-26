#include <stdio.h>

#define N 256000
#define N_PROC 8
#define LOCK_ADDRESS 0x400000;

volatile int procCounter = 0;

volatile int vetor1[N], vetor2[N];
volatile int result[N];

volatile int terminados = 0;

typedef struct __lock_t {
	int flag;
} lock_t;

// lock_t *lock_aux = ( lock_t *) LOCK_ADDRESS;

void lock_init(lock_t *lock) {
    // printf("estou iniciando\n");
	lock->flag = 0;
    // printf("Valor do lock %d\n", lock->flag);
}

void lock(lock_t *lock) {
	int* plock = &lock->flag;
	int r, one;
	do {
		one = 1;
		asm ("ll %0, %2 \n"\
			"sc %3, %1 \n"\
			: "=r" (r), "=m"(*plock)
			: "m" (*plock), "r" (one)
			: );
        // printf("Me da meu lock flavio %d\n",*plock);
	} while (!(r == 0 && one == 1  && *plock == 1));

    // printf("Peguei o lock\n");
}

void unlock(lock_t *lock,  int procN) {
	lock->flag = 0;
	// printf("Soltei o lock %d\n", procN);
}


int main(){
    // printf("Estou live\n");
    int procN, i; 
    lock_t *lock_aux = ( lock_t *) LOCK_ADDRESS;
    if (procCounter == 0) {
        lock_init(lock_aux);       
    }
    // lock_aux = &lock_2;
	lock(lock_aux);
    // Pros pauses e resumes funcionarem, os locks tem que estar funcionando
	procN = procCounter;
	procCounter++;
    unlock(lock_aux, procN);

    if (procN==0){ // o processador 0 inicia os vetores e acorda os outros
        for(i=0; i<N; i++){
            vetor1[i] = i;
            vetor2[i] = i;
        }
        for(i=1; i<N_PROC; i++){
            int *vouAcordarOsOutros = (int*) (0x701000 + 4*i);
            *vouAcordarOsOutros = 1000;
        }
    }
    for (i = procN * N / N_PROC; i < (procN + 1) * N / N_PROC; i++){
        result[i] = vetor1[i] + vetor2[i];
    }
    
    lock(lock_aux);
    terminados++;
    if (terminados == N_PROC){
        for (i = 0; i < N; i++)
            printf ("%d ", result[i]);
        printf ("\n");
    }
    unlock(lock_aux, procN);
    
    return 0;
}
