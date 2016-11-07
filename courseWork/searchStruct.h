//
//  searchStruct.h
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef searchStruct_h
#define searchStruct_h

#include "machineTimeStruct.h"

typedef struct _strpos
{
    int cafedraCode;
    int cafedraName;
    int timePlanned;
    int timeSpent;
} SubstringPositions;

typedef struct _searchMT
{
    struct MachineTime *data;
    SubstringPositions positions;
    struct _searchMT *previous;
    struct _searchMT *next;
} MTsearch;

#endif /* searchStruct_h */
