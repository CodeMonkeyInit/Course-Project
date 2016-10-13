//
//  getMachineTimeAsTable.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "machineTime.h"
#include "machineTimeStruct.h"

struct MachineTime *getMachineTimeStartingPointer()
{
    return machineTimeBegining;
}

struct MachineTime *getTableEnd(struct MachineTime *start,long recordsCount)
{
    struct MachineTime *temp = start;
    
    for (long i = 0;i < recordsCount && temp -> next != NULL; i++)
    {
        temp = temp -> next;
    }
    
    return temp;
}

long getRecordCount(struct MachineTime *begin,struct MachineTime *end)
{
    long recordCount;
    struct MachineTime *temp = begin;
    
    for (recordCount = 0;(temp = temp -> next) != end -> next ; recordCount++);
    
    return recordCount;
}

char *recordsToTable(struct MachineTime *begin, struct MachineTime *end)
{
    long recordCount = getRecordCount(begin,end);
    
    if (NULL == begin || 0 == recordCount)
    {
        return "";
    }
    
    char *table = malloc(sizeof(char) * recordCount * RECORD_SIZE);
    struct MachineTime *temp = begin;
    
    int recordsSaved = 0;
    
    do
    {
        char tableString[RECORD_SIZE + TABLE_BOUNDRIES_SIZE] ;
        int difference = temp-> timeSpent.plan - temp-> timeSpent.realLife;
        
        recordsSaved++;
        sprintf(tableString, "\n│%4d│%11.11s│%s│%8d│%8d│%10d│",
                recordsSaved,
                temp -> cafedraCode,
                temp -> cafedraName,
                temp -> timeSpent.plan,
                temp -> timeSpent.realLife,
                difference
                );
        strcat(table, tableString);
        temp = temp -> next;
    } while (temp != end -> next);
    
    return table;
}

