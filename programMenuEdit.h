//
//  programMenuEdit.h
//  courseWork
//
//  Created by Денис Кулиев on 15.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef programMenuEdit_h
#define programMenuEdit_h

#include "programMenuTableExtras.h"
#include "programMenu.h"
#include "machineTimeStruct.h"
#include "customGetInput.h"

#define TABLE_HEAD_SIZE 2
#define CAFEDRA_CODE_TABLE_OFFSET 6
#define CAFEDRA_NAME_TABLE_OFFSET 18
#define TIME_PLANNED_TABLE_OFFSET 39
#define TIME_USED_TABLE_OFFSET 48
#define CAFEDRA_CODE_LENGTH 11
#define TIME_LENGTH 8
#define FIELD_COUNT 4
#define TABLE_TIME_PLANNED 2
#define TABLE_TIME_USED 3


extern int currentChoice;
extern int currentField;
extern struct MachineTime *currentChoicePointer;
extern bool somethingDeleted;

void moveCursorUp();
void moveCursorDown();
void toogleChoice(int choice,int type);
bool deleteSelected();
void editRecord();

#endif /* programMenuEdit_h */
