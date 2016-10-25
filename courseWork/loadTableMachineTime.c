//
//  loadTableMachineTime.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "machineTime.h"

char *loadToBuffer(FILE *file)
{
    char *buffer;
    fseek(file, 0, SEEK_END);
    
    long fileLength = ftell(file);
    int blockSize = getBlockSize();
    long blockCount = fileLength / blockSize + 1;
    
    rewind(file);
    
    buffer = (char *) malloc( sizeof(char) * fileLength + 1 );
    
    fread(buffer, blockSize, blockCount, file);
    buffer[fileLength] = '\0';
    
    fclose(file);
    
    return buffer;
}

int parseMachineTimeRecord(char *record)
{
    const int OTHER_FIELDS_SIZE = 38,
    CAFEDRA_CODE_START = 16,
    CAFEDRA_CODE_END = 21,
    CAFEDRA_NAME_START = 24,
    TIME_USED_START_OFFSET = 14,
    TIME_USED_END_OFFSET = 22,
    TIME_PLANNED_START_OFFSET = 3,
    TIME_PLANNED_END_OFFSET = 11;
    
    const long RECORD_LENGTH = strlen(record);
    const int CAFEDRA_NAME_END = (int)RECORD_LENGTH - OTHER_FIELDS_SIZE;
    
    const int TIME_USED_START = CAFEDRA_NAME_END + TIME_USED_START_OFFSET,
    TIME_USED_END = CAFEDRA_NAME_END + TIME_USED_END_OFFSET,
    TIME_PLANNED_START = CAFEDRA_NAME_END + TIME_PLANNED_START_OFFSET,
    TIME_PLANNED_END = CAFEDRA_NAME_END + TIME_PLANNED_END_OFFSET;
    
    char **parsedRecord = (char **) malloc(sizeof(char*) * RECORD_ENTRIES);
    
    parsedRecord[CAFEDRA_CODE] = getStringFromBuffer(record, CAFEDRA_CODE_START, CAFEDRA_CODE_END);
    parsedRecord[CAFEDRA_NAME] = getStringFromBuffer(record, CAFEDRA_NAME_START, CAFEDRA_NAME_END);
    parsedRecord[TIME_USED] = getStringFromBuffer(record, TIME_USED_START , TIME_USED_END);
    parsedRecord[TIME_PLANNED] = getStringFromBuffer(record, TIME_PLANNED_START, TIME_PLANNED_END);
    
    addRecord( createRecord(parsedRecord) );
    
    freeArrayOfStrings(parsedRecord, RECORD_ENTRIES);
    
    return 0;
}

int parseBuffer(char *buffer,long startPosition)
{
    long recordsCount = 0,
    recordsProcessed = 0;
    
    recordsCount = countNewLines(buffer, startPosition);
    
    if (0 == recordsCount)
    {
        return BUFFER_EMPTY;
    }
    
    while (recordsProcessed < recordsCount)
    {
        long recordEnd;
        
        for (recordEnd = startPosition;buffer[recordEnd] != '\n'; recordEnd++);
        
        char *record = getStringFromBuffer(buffer, startPosition, recordEnd);

        startPosition = recordEnd + 1;
        
        parseMachineTimeRecord(record);
        
        free(record);
        recordsProcessed++;
    }
    
    free(buffer);
    
    return FILE_LOADED;
}
