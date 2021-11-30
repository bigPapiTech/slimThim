#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char *argv[]){

	char buffer[CODESIZE];

	buffer[0] = IADD;
	buffer[1] = 32; 
	buffer[2] = 16;
	buffer[3] = PRINT;
	buffer[4] = IADD;
	buffer[5] = 32;
	buffer[6] = 64;
	buffer[7] = PRINT;
	buffer[8] = IADD;
	buffer[9] = 64;
	buffer[10] = 64;
	buffer[11] = BR;
	buffer[12] = 16;
	buffer[13] = 0;
	buffer[14] = 0;
	buffer[15] = 0;
	buffer[16] = PRINT;
	buffer[17] = HALT;
	
	FILE *write_ptr;
	write_ptr = fopen("./build/program.bin","wb");  // w for write, b for binary
	fwrite(buffer,sizeof(buffer),1,write_ptr); // write from our buffer
	fclose(write_ptr);

	return 0;
}
