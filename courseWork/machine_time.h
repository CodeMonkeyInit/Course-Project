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
#include <sys/stat.h>



#define FILE_LOADED 1
#define FILE_NOT_OPEN -1
#define INCORRECT_FILE -2
#define HEADERS_MISMATCH -1
#define HEADERS_MATCH 1
#define MACHINE_FILE_HEADER "courseWork_FILE"

struct MachineTime;

int getBlockSize();
int checkFileHeader(FILE *unknown, const char *referenceHeader);
int loadFile(FILE **file, const char *filename,const char *header);
char *loadToBuffer(FILE *machineTimeFile);
int parseBuffer(char *buffer,int startPosition);



#endif /* machine_time_h */
