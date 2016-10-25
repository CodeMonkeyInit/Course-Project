//
//  machine_time.h
//  courseWork
//
//  Created by Денис Кулиев on 17.09.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef machine_time_h
#define machine_time_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnicodeMacOSLib.h"
#include "customFileFunctions.h"
#include "customString.h"

#define MACHINE_FILE_HEADER "courseWork_FILE"
#define TABLE_HEAD "\n┌──────────────────────────────────────────────────────────────────┐\n│   №│Код Кафедры│    Название Кафедры|По Плану|По Факту│Отклонения│"
#define TABLE_BOTTOM "\n└──────────────────────────────────────────────────────────────────┘"
#define CAFEDRA_CODE 0
#define CAFEDRA_NAME 1
#define TIME_USED 2
#define TIME_PLANNED 3
#define RECORD_ENTRIES 4
#define TABLE_TYPE_FILE 0
#define BINARY_TYPE_FILE 1
#define UNKNOWN_FILE_TYPE -1
#define NOTHING_TO_SAVE -2
#define RECORD_SIZE 102
#define TABLE_BOUNDRIES_SIZE 29
#define CAFEDRA_NAME_FORMAT_LENGTH 20
#define BUFFER_EMPTY -1
#define GET_NORMAL 0
#define GET_REVERSE 1
#define MIDDLE 0
#define BEGINING 1
#define ENDING 2
#define EMPTY -1

struct MachineTime *getMachineTimeStartingPointer();
struct MachineTime *getTableEnd(struct MachineTime *start,long recordsCount, int mode);
long getRecordCount(struct MachineTime *begin,struct MachineTime *end);
int loadBinary(FILE **binaryFile);
char *loadToBuffer(FILE *file);
void addRecord(struct MachineTime *record);
int deleteRecord(struct MachineTime **record);
struct MachineTime *createRecord(char **recordStrings);
int parseBuffer(char *buffer,long startPosition);
char *recordsToTable(struct MachineTime *begin, struct MachineTime *end);
int saveFile(const char *path, int type);

#endif /* machine_time_h */
