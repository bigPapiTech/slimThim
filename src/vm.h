#ifndef __vm_h__
#define __vm_h__

#define DATASIZE  100
#define CODESIZE  100
#define STACKSIZE 100

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

typedef enum
{
	HALT ,
	ICONST,
	IADD,
	ISUB,
	IMUL,
	ILT,
	IEQ,
	BR,
	RRT,
	BRF,
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

