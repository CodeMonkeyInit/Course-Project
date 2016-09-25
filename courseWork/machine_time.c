//
//  machine_time.c
//  courseWork
//
//  Created by Денис Кулиев on 17.09.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "machine_time.h"

struct TimeSpent
{
    int plan;
    int realLife;
};

struct MachineTime
{
    char cafedraCode[5];
    char cafedraName[20];
    struct TimeSpent timeSpent;
    struct MachineTime *next;
};

int checkFileHeader(FILE *unknown, const char *refernceHeader)
{
    char fileHeader[200];
    fscanf(unknown, "%s", fileHeader);
    rewind(unknown);
    
    if ( strcmp(fileHeader, refernceHeader) )
    {
        return HEADERS_MISMATCH;
    }
    else
    {
        return HEADERS_MATCH;
    }
}

int loadFile(FILE **file,const char *filename,const char *header)
{
    *file = fopen(filename, "r");
    
    if (*file == NULL)
    {
        return FILE_NOT_OPEN;
    }
    
    if ( checkFileHeader(*file, header) == HEADERS_MISMATCH )
    {
        fclose(*file);
        return INCORRECT_FILE;
    }
    
    
    return FILE_LOADED;
}

char *loadToBuffer(FILE *machineTimeFile)
{
    char *buffer;
    fseek(machineTimeFile, 0, SEEK_END);
    
    long fileLength = ftell(machineTimeFile);
    int blockSize = 1024;
    long blockCount = fileLength / blockSize + 1;
    
    rewind(machineTimeFile);
    
    buffer = (char *) malloc( sizeof(char) * fileLength + 1 );
    
    fread(buffer, blockSize, blockCount, machineTimeFile);
    buffer[fileLength] = '\0';
    
    fclose(machineTimeFile);
    
    return buffer;
}

int parseBuffer(char *buffer,int startPosition)
{
    for(long i = startPosition;; i++)
    {
        if (buffer[i] == '\0')
            break;
        printf("%c", buffer[i]);
    }
    return 0;
}
