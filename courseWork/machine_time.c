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

int getBlockSize()
{
    struct stat fileSystem;
    stat("/", &fileSystem);
    return fileSystem.st_blksize;
}

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
    *file = fopen(filename, "rb");
    
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
    int blockSize = getBlockSize();
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
    long recordEnd;
    
    char cafedraCode[4],
            cafedraName[40],
            поФакту[8],
            поПлану[8];
    
    for (recordEnd = startPosition;buffer[recordEnd] != L'\n'; recordEnd++)
    {
        printf("%lc", buffer[recordEnd]);
    }
    
    int recordLength = (int) recordEnd - startPosition;
    char record[recordLength];
    
    for (int i = startPosition,j = 0; i <= recordEnd; i++,j++)
    {
        record[j] = buffer[i];
    }
    
    printf("%s", record);
    
    for (int i = 16,j = 0; i < 16+5; i++,j++)
    {
        cafedraCode[j] = record[i];
    }
    
    int cafedraNameEnd = recordLength - 26;
    
    for(int i = 24,j = 0;i <= cafedraNameEnd; i++,j++)
    {
        cafedraName[j] = record[i];
    }
    
    for (int i = cafedraNameEnd + 4,j = 0; i < cafedraNameEnd + 4 + 8 ; i++,j++)
    {
        поФакту[j] = record[i];
    }
    
    for (int i = cafedraNameEnd + 4 + 8 + 3,j = 0; i < cafedraNameEnd + 4 + 8 + 3 + 8; i++,j++)
    {
        поПлану[j] = record[i];
    }
    
    
    return 0;
}
