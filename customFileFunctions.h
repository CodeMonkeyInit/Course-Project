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

#define FILE_LOADED 1
#define FILE_NOT_OPEN -1
#define INCORRECT_FILE -2
#define HEADERS_MISMATCH -1
#define HEADERS_MATCH 1

int checkFileHeader(FILE *unknown, const char *referenceHeader);
int loadFile(FILE **file, const char *path,const char *header);

#endif /* customFileFunctions_h */
