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
#include "programMenuConstants.h"


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
