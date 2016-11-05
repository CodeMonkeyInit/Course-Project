//
//  programMenuTableVariables.h
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef programMenuTableVariables_h
#define programMenuTableVariables_h

#include <ncurses.h>
#include "programMenu.h"
#include "machineTimeStruct.h"
#include "programMenuConstants.h"

extern struct MachineTime *start,
*end;
extern char *tableString;
extern long currentPage;
extern WINDOW *table;
extern bool controlsLocked;

void printTable(int helpType);
void editStruct();
void updateTable();

#endif /* programMenuTableVariables_h */
