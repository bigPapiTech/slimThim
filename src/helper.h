#ifndef HELPER_H
#define HELPER_H

void checkInput(int);
void die(char*);
char *mallocChar(int);
char* copyStr(char*);
char *copyFpToMem(FILE*, int );
FILE* openFile(char*, char*);
int getFileSize(FILE*);

#endif
