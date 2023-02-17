#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "helper.h"

int sp = -1; 			// Stack Pointer 
int fp = 0; 			// Frame Pointer
int ip = 0; 			// Instruction Pointer
int addr = 0;
int nargs = 0;
int rvalue = 0;
int gm = 0;
__int8_t bytecode = 0; 		// Operation Code
                          //
__int8_t code[CODESIZE] = {'\0'};	// Code memory
__int8_t data[DATASIZE] = {'\0'};	// Data memory
__int8_t stack[STACKSIZE] = {'\0'};	// memory

__int8_t start(__int8_t x){
  if(x-2 >= 0){
    return x-2;
  }else{
    return 0;
  }
}

char *get_bytecode_name(__int8_t bytecode){
  switch(bytecode){
			case ICONST: return  "ICONST";
      case IADD: return "IADD";  
      case IMUL: return "IMUL";  
      case ISUB: return "ISUB";  
      case PRINT: return "PRINT"; 
      case BR: return  "BR";
      case GSTORE: return "GSTORE";
      case LOAD: return "LOAD";
      case CALL: return "CALL";
      case RET: return "RET";
      case HALT: return "HALT";
      default: return "";
  }
}

void debug(){
  printf ("%s:\n", "code");
  for(int i = start(ip); i < start(ip)+5; i++){
    printf ("%04d\t%04d%s\n", i, code[i], ( i==ip ? " <-- ip": ""));
  }
  printf ("\n");
  printf ("%s:\n", "stack");
  for(int i = start(sp); i < start(sp)+5; i++){
    printf ("%04d\t%04d%s\n", i, stack[i], ( i==sp ? " <-- sp": ""));
  }
  printf ("\n");
  printf ("%s:\n", "data");
  for(int i = 0; i < gm; i++){
    printf ("%04d\t%04d\n", i, data[i]);
  }
  printf ("\n\n");
}

int main(int argc, char *argv[] ) {
	// Init
  //DEBUG_PRINT("Debugging is enabled.\n");    
  //DEBUG_PRINT("Debug level: %d\n", (int) DEBUG);	

  checkInput(argc);

	FILE *ptr;
	ptr = fopen(argv[1],"rb");  // r for read, b for binary
	fread(code,sizeof(code),1,ptr); // read 
	fclose(ptr);

  // Fetch Next Instruction
  bytecode = code[ip];

  if(DEBUG > 0){
    printf("Before %s %d\n", get_bytecode_name(bytecode), bytecode);
    debug();
  }

	// Decode and Execute
	//while (bytecode != HALT && ip < CODESIZE){ 	
	while (ip < CODESIZE){ 	
		// increment Instruction Pointer
		//ip++;
		switch(bytecode){ 
			case ICONST:
        stack[++sp] = code[++ip];
        ip++;
        break;
      case IADD:
        stack[++sp] = stack[sp--] + stack[sp--];
        ip++;
        break;
      case ISUB:
        stack[++sp] = stack[sp--] - stack[sp--];
        ip++;
        break;
      case IMUL:
        stack[++sp] = stack[sp--] * stack[sp--];
        ip++;
        break;
      case GSTORE:
        if(DEBUG > 0)
          gm++;
        data[code[++ip]] = stack[sp--];
        ip++;
        break;
      case GLOAD:
        stack[sp++] = data[code[++ip]];
        ip++;
        break;
      case LOAD:
        stack[++sp] = stack[sp+code[++ip]];
        ip++;
        break;
      case PRINT:
        printf("%d\n", stack[sp]);
        ip++;
        break;
      case CALL:
        addr = code[++ip];          // The function address
        stack[++sp] = code[++ip];   // Store the num of arguments on the stack 
        stack[++sp] = fp;           // Store the frame pointer address on the stack
        stack[++sp] = ++ip;         // Store the instrction pointer address on the stack (for the next instruction)
        fp = sp;                    // Frame pointer is now +3, the number of
        ip = addr;                  // Make the Call
        break;
      case RET:
        rvalue = stack[sp--];       // Pop the stack as return value
        ip = stack[sp--];           // Restore the IP
        fp = stack[sp--];           // Restore the FP
        sp -= stack[sp--];          // pop the num of arguments
        stack[++sp]=rvalue;         // push the return value on the tack
        break;
      case BR:
        ip=code[++ip];
        break;
      case HALT:
        return 0;

			default: exit(1);
		}
		// Fetch Next Instruction
    
    if(DEBUG > 0){
      printf("After %s %d\n", get_bytecode_name(bytecode), bytecode);
      debug();
    }

		bytecode = code[ip];
    
    if(DEBUG > 0){
      printf("Next: %s %d\n", get_bytecode_name(bytecode), bytecode);
      printf("Press ENTER key to Continue\n");
      getchar();
    }
  }
  return 0;
}
