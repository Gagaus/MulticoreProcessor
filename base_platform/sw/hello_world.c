#include <stdio.h>
#include <stdlib.h>

volatile int procCounter = 0;

void RecursiveHello( int n, int procN, int value) {
	if (n) {
		printf("Hi from processor PowerPC %d!, valor = %d\n", procN, value*64);
		RecursiveHello(n-1, procN, (value * 2));
	}
}

int main(int argc, char *argv[]){
	int procN; 
	// AcquireLock();
	procN = procCounter;
	procCounter++;
    int *outro = (int*) (0x700000 + 4*procN);
    *outro = 1000;
	RecursiveHello(10, procN, 12);
	// ReleaseLock();


	
	exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}
