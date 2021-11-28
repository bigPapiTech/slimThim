#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
int main(int argc, char *argv[] ) {
	// Init
	
	
	int sp = -1; 			// Stack Pointer 
	int fp = 0; 			// Frame Pointer
	int ip = 0; 			// Instruction Pointer
	__int8_t bytecode = 0; 		// Operation Code
	__int8_t code[CODESIZE] = {0};	// Code memory
	int data[DATASIZE] = {0};	// Data memory
	int stack[STACKSIZE] = {0};	// memory

	printf("Starting VM.\nDATASIZE:\t%d\nCODESIZE:\t%d\nSTACKSIZE:\t%d\n", DATASIZE, CODESIZE, STACKSIZE);
	

	// Test Case
	/*
	code[0] = IADD;
	code[1] = 1;
	code[2] = 5;
	code[3] = IADD;
	code[4] = 3;
	code[5] = 4;
	code[6] = IADD;
	code[7] = 4;
	code[8] = 4;
	code[9] = PRINT;
	code[10] = 1;
	code[11] = HALT;
	*/

	FILE *ptr;
	ptr = fopen("./build/program.bin","rb");  // r for read, b for binary
	fread(code,sizeof(code),1,ptr); // read 10 bytes to our buffer
	fclose(ptr);

	for(int i = 0; i < CODESIZE; i++){
		printf ("%d", code[i]);
	}
	printf ("\n");
	// Fetch Next Instruction
	bytecode = code[ip];

	// Decode and Execute
	while (bytecode != HALT && ip < CODESIZE){ 	
		// increment Instruction Pointer
		ip++;

		switch(bytecode){ 

			case HALT:
				return 0;
			case IADD:
				stack[sp++] = code[ip++];
				stack[sp] = code[ip++];
				stack[sp] = stack[sp--] + stack[sp--];
				break;
			case PRINT:
				printf("%d\n", stack[sp]);
				break;
			default: exit(1);
		}



		//stack[++sp];

		// Fetch Next Instruction
		bytecode = code[ip];

	}
	return 0;
}
