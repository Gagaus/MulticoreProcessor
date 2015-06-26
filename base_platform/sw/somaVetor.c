#include <stdio.h>
#include <stdint.h>

#define N 256000
#define N_PROC 8
#define LOCK_ADDRESS 0x400000;

volatile int procCounter = 0;

volatile int vetor1[N], vetor2[N];
volatile int resultMap[N], resultReduce[8];

volatile int terminadoMap = 0, terminadoReduce = 0;

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
    
    int procN, i; 
    lock_t *lock_aux = ( lock_t *) LOCK_ADDRESS;
    if (procCounter == 0) {
        lock_init(lock_aux);       
    }
    
	lock(lock_aux);
	procN = procCounter;
	procCounter++;
    unlock(lock_aux, procN);

    if (procN==0){ // o processador 0 inicia os vetores e acorda os outros
        for(i=0; i<N; i++){
            vetor1[i] = 1;
            vetor2[i] = 1;
        }
        for (i = 0; i < 8; i++)
            resultReduce[i] = 0;
            
        for(i=1; i<N_PROC; i++){
            int *vouAcordarOsOutros = (int*) (0x701000 + 4*i);
            *vouAcordarOsOutros = 1000;
        }
    }
    for (i = procN * N / N_PROC; i < (procN + 1) * N / N_PROC; i++){
        resultMap[i] = vetor1[i] + vetor2[i];
    }
    
    lock(lock_aux);
    terminadoMap++;
    unlock(lock_aux, procN);
    
    while(terminadoMap < N_PROC) {} // espera todos terminarem o map
    
    for (i = procN * N / N_PROC; i < (procN + 1) * N / N_PROC; i++){
        resultReduce[procN] += resultMap[i];
    }
    
    lock(lock_aux);
    terminadoReduce++;
    unlock(lock_aux, procN);
    
    while(terminadoReduce < N_PROC) {} // espera todos terminarem o reduce
    
    
    if (procN == 0){
        lock(lock_aux);
        int resultFinal = 0;
        for (i = 0; i < N_PROC; i++)
            resultFinal += resultReduce[i];
        printf ("\n\n      ********    Resultado Final: %d    **********   \n\n\n", resultFinal);
        unlock(lock_aux, procN);
    }
    
    return 0;
}
