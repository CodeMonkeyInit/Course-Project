//
//  customString.h
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
#ifndef customString_h
#define customString_h

#include <string.h>
#include <stdlib.h>

long countNewLines(char *buffer, long startPosition);
char *getStringFromBuffer(const char *buffer,long startPosition, long endPosition);
void freeArrayOfStrings(char **garbage, size_t stringNumber);

#endif /* customString_h */
