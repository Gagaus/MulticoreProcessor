#include <stdio.h>
#include <stdlib.h>

volatile int procCounter = 0;

void RecursiveHello( int n, int procN, int value) {
	if (n) {
		printf("Hi from processor MIPS %d!, valor = %d\n", procN, value*64);
		RecursiveHello(n-1, procN, (value * 2));
	}
}

int main(int argc, char *argv[]){
	int procN; 
	// AcquireLock();
    // Pros pauses e resumes funcionarem, os locks tem que estar funcionando
	procN = procCounter;
	procCounter++;
  if (procN == 0){    
    int *outro;
    int i;
    // pausa os registradores de 1 a 7
    for (i = 1; i < 8; i++) {
      outro = (int*) (0x700000 + i*4);
      *outro = 1000;
    }
  }
	RecursiveHello(10, procN, 12);
  if (procN == 0){
    // resume proc 1
    int *outro = (int*) (0x701000 + 1*4);
    *outro = 1000;
    // pausa proc 0
    outro = (int*) (0x700000);
    *outro = 1000;
  }
  if (procN==1) {
    // resume proc 2
    int *outro = (int*) (0x701000 + 2*4);
    *outro = 1000;
    // pausa proc 1
    outro = (int*) (0x700000 + 1*4);
    *outro = 1000;
  }

  if (procN==2) {
    // resume proc 3
    int *outro = (int*) (0x701000 + 3*4);
    *outro = 1000;
    // pausa proc 2
    outro = (int*) (0x700000 + 2*4);
    *outro = 1000;
  }
  
  if (procN==3) {
    // resume proc 4
    int *outro = (int*) (0x701000 + 4*4);
    *outro = 1000;
    // pausa proc 3
    outro = (int*) (0x700000 + 3*4);
    *outro = 1000;
  }
  
  if (procN==4) {
    // resume proc 5
    int *outro = (int*) (0x701000 + 5*4);
    *outro = 1000;
    // pausa proc 4
    outro = (int*) (0x700000 + 4*4);
    *outro = 1000;
  }
  
  if (procN==5) {
    // resume proc 6
    int *outro = (int*) (0x701000 + 6*4);
    *outro = 1000;
    // pausa proc 5
    outro = (int*) (0x700000 + 5*4);
    *outro = 1000;
  }
  
  if (procN==6) {
    // resume proc 7
    int *outro = (int*) (0x701000 + 7*4);
    *outro = 1000;
    // pausa proc 6
    outro = (int*) (0x700000 + 6*4);
    *outro = 1000;
  }
  
  if (procN==7) {
    // resume todos os processadores
    int *outro;
    int i;
    for (i = 0; i < 7; i++) {
      outro = (int*) (0x701000 + i*4);
      *outro = 1000;
    }
  }
  
	// ReleaseLock();


	
	exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}
