//
//  IMachineTime.h
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef IMachineTime_h
#define IMachineTime_h

#include "machineTime.h"
#include "programMenu.h"
#include <stdbool.h>
#include <locale.h>

#define TABLE_START_OFFSET 351
#define saveStruct(path, type) saveFile(path, type)

void startMenu();
int loadStructTable(FILE **machineTimeFile);
int loadStruct(const char * path, short type);
void startProgram();

#endif /* IMachineTime_h */
