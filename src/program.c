#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char *argv[]){

	char buffer[CODESIZE];

	buffer[0] = IADD;
	buffer[1] = 1; 
	buffer[2] = 5;
	buffer[3] = PRINT;
	buffer[4] = IADD;
	buffer[5] = 3;
	buffer[6] = 4;
	buffer[7] = PRINT;
	buffer[8] = IADD;
	buffer[9] = 4;
	buffer[10] = 4;
	buffer[11] = PRINT;
	buffer[12] = HALT;
	
	FILE *write_ptr;
	write_ptr = fopen("./build/program.bin","wb");  // w for write, b for binary
	fwrite(buffer,sizeof(buffer),1,write_ptr); // write from our buffer
	fclose(write_ptr);

	return 0;
}
