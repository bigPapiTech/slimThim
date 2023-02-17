#ifndef DEBUGROW_H
#define DEBUGROW_H

typedef struct DebugRow{
 int line;
 int word;
 int character;
} DebugRow;

DebugRow*
newDebugRow(int, int, int);

#endif

