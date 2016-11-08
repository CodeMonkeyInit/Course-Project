//
//  customFileFunctions.h
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef customFileFunctions_h
#define customFileFunctions_h

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILE_LOADED 1
#define FILE_NOT_OPEN -1
#define INCORRECT_FILE -2
#define HEADERS_MISMATCH -1
#define HEADERS_MATCH 1
#define TABLE_TYPE_FILE 0
#define BINARY_TYPE_FILE 1
#define UNKNOWN_FILE_TYPE -1

int checkFileHeader(FILE *unknown, const char *referenceHeader);
int loadFile(FILE **file, const char *path,const char *header);
int getFileType(const char *path);

#endif /* customFileFunctions_h */
