#include <stdio.h>
#include <stdlib.h>

volatile int procCounter = 0;

void RecursiveHello( int n, int procN) {
	if (n) {
		printf("Hi from processor PowerPC %d!\n", procN);
		RecursiveHello(n-1, procN);
	}
}

int main(int argc, char *argv[]){
	int procN; 

	// AcquireLock();
	procN = procCounter;
	procCounter++;
	RecursiveHello(10, procN);
	// ReleaseLock();


	
	exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}
