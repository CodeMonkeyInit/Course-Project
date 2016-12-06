#ifndef programMenuTableVariables_h
#define programMenuTableVariables_h

#include <ncurses.h>
#include "programMenu.h"
#include "machineTimeStruct.h"
#include "programMenuConstants.h"

extern struct MachineTime *start,
*end;
extern char *tableString;
extern int currentPage;
extern WINDOW *table;
extern bool controlsLocked;

void printTable(int helpType);
void editMachineTimeStruct();
void updateTable();
void printCurrentPageNumber(int currentPage);

#endif /* programMenuTableVariables_h */
