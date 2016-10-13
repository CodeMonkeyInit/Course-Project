//
//  saveStruct.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "machineTimeStruct.h"
#include "machineTime.h"

int saveFileAsTable(const char *path)
{
    FILE *tableFile = fopen(path, "w");
    // WTF?
    char *table = recordsToTable(machineTimeBegining,machineTimeEnding);
    
    if (NULL == tableFile)
    {
        return FILE_NOT_OPEN;
    }
    
    fprintf(tableFile, "%s%s%s%s", MACHINE_FILE_HEADER,
            TABLE_HEAD,
            table,
            TABLE_BOTTOM);
    
    free(table);
    
    fclose(tableFile);
    
    return 0;
}


int saveFileBinary(const char *path)
{
    FILE *binaryFile = fopen(path, "wb");
    
    if (NULL == binaryFile)
    {
        return FILE_NOT_OPEN;
    }
    
    fprintf(binaryFile, "%s", MACHINE_FILE_HEADER);
    
    struct MachineTime *temp = machineTimeBegining;
    int recordsSaved = 0;
    do
    {
        recordsSaved++;
        fprintf(binaryFile, "\n%s %s %d %d",
                temp -> cafedraCode,
                temp -> cafedraName,
                temp -> timeSpent.plan,
                temp -> timeSpent.realLife
                );
    } while ( NULL != (temp = temp -> next) );
    
    fclose(binaryFile);
    
    return 0;
}

int saveFile(const char *path, int type)
{
    if (NULL == machineTimeBegining)
    {
        return NOTHING_TO_SAVE;
    }
    else if (BINARY_TYPE_FILE == type)
    {
        return saveFileBinary(path);
    }
    else if (TABLE_TYPE_FILE == type)
    {
        return saveFileAsTable(path);
    }
    else
    {
        return UNKNOWN_FILE_TYPE;
    }
    
    return 0;
}
