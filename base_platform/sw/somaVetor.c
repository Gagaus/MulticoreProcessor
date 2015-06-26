#include <stdio.h>

#define N 100000
#define N_PROC 8

volatile int procCounter = 0;

volatile int vetor1[N], vetor2[N];
volatile int result[N];

volatile int terminados = 0;

int main(){
    int procN, i; 
	// AcquireLock();
    // Pros pauses e resumes funcionarem, os locks tem que estar funcionando
	procN = procCounter;
	procCounter++;
    // ReleaseLock();
    
    for (i = 1; i < N; i++){ // todos os processadores menos o 0 sao pausados
        if (procN == i){
            int *vouMePausar = (int*) 0x700000 + procN*4;
            *vouMePausar = 1000;
        }
    }

    if (procN==0){ // o processador 0 inicia os vetores e acorda os outros
        for(i=0; i<N; i++){
            vetor1[i] = i;
            vetor2[i] = i;
        }
        for(i=1; i<N; i++){
            int *vouAcordarOsOutros = (int*) 0x701000 + procN*4;
            *vouAcordarOsOutros = 1000;
        }
    }
    for (i = procN * N / N_PROC; i < (procN + 1) * N / N_PROC; i++){
        result[i] = vetor1[i] + vetor2[i];
    }
    
    // AcquireLock();
    terminados++;
    if (terminados == N_PROC){
        for (i = 0; i < N; i++)
            printf ("%d ", result[i]);
        printf ("\n");
    }
    // ReleaseLock();
    
    return 0;
}
