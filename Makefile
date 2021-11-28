CC = clang
CFLAGS = -Wall -g
# NCURSES := -lncurses
INCLUDEDIR = ./
LDFLAGS = -lm

HEADERS = ./src/vm.h

MAIN = build/main.out
MAIN_OBJECTS = ./src/main.o

PROGRAM = build/program.out
PROGRAM_OBJECTS = ./src/program.o

.SUFFIXES: .c .o

all: ${MAIN} ${PROGRAM}

${MAIN}: ${MAIN_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${MAIN_OBJECTS} 


${MAIN_OBJECTS}: ${HEADERS} 
	${CC} ${CFLAGS} -c $< -o $@ 

${PROGRAM}: ${PROGRAM_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${PROGRAM_OBJECTS} 


${PROGRAM_OBJECTS}: ${HEADERS} 
	${CC} ${CFLAGS} -c $< -o $@ 

test:
	${PROGRAM}
	${MAIN}

clean:
	rm src/*.o
	rm build/*.*
