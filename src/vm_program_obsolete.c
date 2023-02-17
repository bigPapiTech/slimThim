#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char *argv[]){

/*
__int8_t code[CODESIZE] = {     // Code memory
  ICONST, 1,
  ICONST, 5,
  IADD,
  PRINT,
  ICONST, 71,
  GSTORE, 0,
  ICONST, 72,
  GSTORE, 1,
  ICONST, 0,
  GSTORE, 2,
  ICONST, 74,
  GSTORE, 3,
  ICONST, 85,
  GLOAD,  0,
  HALT,
  '\0',
};
*/
/*
__int8_t code[CODESIZE] = {     // Code memory
  ICONST, 5,
  ICONST, 5,
  CALL, 9, 2,
  PRINT,
  HALT,
  LOAD, -3,
  LOAD, -4,
  IADD,
  RET,
};
*/

__int8_t code[CODESIZE] = {     // Code memory
  ICONST, 2,
  ICONST, 1,
  IADD,
  ICONST, 9,
  IADD,
  HALT
};



	FILE *write_ptr;
	write_ptr = fopen("./test/program.bin","wb");  // w for write, b for binary
	fwrite(code,sizeof(code),1,write_ptr); // write from our buffer
	fclose(write_ptr);

	return 0;
}
