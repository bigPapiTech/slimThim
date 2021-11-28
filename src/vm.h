#ifndef __vm_h__
#define __vm_h__

#define DATASIZE  500
#define CODESIZE  500
#define STACKSIZE 500

typedef enum
{
	HALT ,
	IADD,
	ISUB,
	IMUL,
	ILT,
	IEQ,
	BR,
	RRT,
	BRF,
	ICONST,
	LOAD,
	GLOAD,
	STORE,
	GSTORE,
	PRINT,
	POP,
	CALL,
	RET
}e_instructions;


#endif

