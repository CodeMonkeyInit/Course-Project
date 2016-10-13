//
//  customString.c
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "customString.h"

long countNewLines(char *buffer, long startPosition)
{
    long linesCount = 0;
    
    for (long i = startPosition; buffer[i] != '\0'; i++)
    {
        if ( '\n' == buffer[i] )
        {
            linesCount++;
        }
    }
    
    return linesCount;
}

char *getStringFromBuffer(const char *buffer,long startPosition, long endPosition)
{
    long i,j;
    
    long stringLength = endPosition - startPosition;
    char *string = malloc(sizeof(char) * stringLength);
    
    for (i = startPosition, j = 0; i < endPosition; i++,j++)
    {
        string[j] = buffer[i];
    }
    
    string[j] = '\0';
    
    return string;
}

void freeArrayOfStrings(char **garbage, size_t stringNumber)
{
    for (size_t i = 0; i < stringNumber; i++)
    {
        free(garbage[i]);
    }
    free(garbage);
}
