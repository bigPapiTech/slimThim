CC = clang
CFLAGS = -Wall -g
# NCURSES := -lncurses
INCLUDEDIR = ./
LDFLAGS = -lm

TARGET = build/main.out
VM = build/vm.out
#VM_PROGRAM = build/vm_program.out

HEADERS = ./src/main.h ./src/vm.h ./src/lex.h ./src/parser.h ./src/token.h ./src/helper.h ./src/symtbl.h ./src/debugrow.h

VM_HEADERS = ./src/vm.h ./src/helper.h ./src/symtbl.h

OBJECTS = ./src/parser.o ./src/lex.o ./src/token.o ./src/helper.o ./src/main.o ./src/debugrow.o ./src/symtbl.o
VM_OBJECTS = ./src/vm.o ./src/helper.o
#VM_PROGRAM_OBJECTS = ./src/vm_program.o

.SUFFIXES: .c .o

all: ${TARGET} ${VM} #${VM_PROGRAM}

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} ${NCURSES} -o $@ ${OBJECTS} 


${OBJECTS}: ${HEADERS} 
	${CC} ${CFLAGS} -c $< -o $@ 

${VM}: ${VM_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${VM_OBJECTS}

${VM_OBJECTS}: ${VM_HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

#${VM_PROGRAM}: ${VM_PROGRAM_OBJECTS}
#	 ${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${VM_PROGRAM_OBJECTS}


#${VM_PROGRAM_OBJECTS}: ${VM_HEADERS}
#	${CC} ${CFLAGS} -c $< -o $@

test:
	${TARGET} ./test/source.txt
#	${VM_PROGRAM}
	${VM} ./test/program.bin
test_vm:
#	${VM_PROGRAM}
	${VM} ./test/program.bin
test_main:
	cat ./test/source.txt
	${TARGET} ./test/source.txt

clean:
	rm src/*.o
	rm build/*.out

debug_vm:
	lldb ${VM} ./test/program.bin

debug_main:
	lldb ${TARGET} ./test/source.txt


