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

struct MachineTime *getTableEnd(struct MachineTime *start,long recordsCount, int mode)
{
    struct MachineTime *temp = start;
    if (NULL == start)
    {
        return NULL;
    }

    if (GET_NORMAL == mode)
    {
        for (long i = 0;i < recordsCount && temp -> next != NULL; i++)
        {
            temp = temp -> next;
        }
    }
    else if (GET_REVERSE == mode)
    {
        for (long i = 0;(i < recordsCount) && (temp -> previous != NULL); i++)
        {
            temp = temp -> previous;
        }
    }
    
    return temp;
}

long getRecordCount(struct MachineTime *begin,struct MachineTime *end)
{
    long recordCount;
    struct MachineTime *temp = begin;
    if (NULL == begin)
    {
        return 0;
    }
    for (recordCount = 0;temp != end -> next ; recordCount++)
    {
        temp = temp -> next;
    }
    
    return recordCount;
}

char *recordsToTable(struct MachineTime *begin, struct MachineTime *end)
{
    long recordCount = getRecordCount(begin,end);
    
    if (NULL == begin || 0 == recordCount)
    {
        return NULL;
    }
    
    char *table =  calloc( recordCount * RECORD_SIZE, sizeof(char) );
    
    struct MachineTime *temp = begin;
    
    long currentRecordNumber = getRecordCount(machineTimeBegining, begin) - 1;
    
    do
    {
        char tableString[RECORD_SIZE + TABLE_BOUNDRIES_SIZE] ;
        int difference = abs( (temp -> timeSpent.plan) - (temp -> timeSpent.realLife) );
        
        currentRecordNumber++;
        sprintf(tableString, "\n│%4ld│%11.11s│%s│%8d│%8d│%10d│",
                currentRecordNumber,
                temp -> cafedraCode,
                temp -> cafedraName,
                temp -> timeSpent.plan,
                temp -> timeSpent.realLife,
                difference
                );
        tableString[RECORD_SIZE + TABLE_BOUNDRIES_SIZE - 1] = '\0';
        strcat(table, tableString);
        temp = temp -> next;
    } while (temp != end -> next);
    
    return table;
}

