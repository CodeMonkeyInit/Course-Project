#ifndef searchStruct_h
#define searchStruct_h

#include "machineTimeStruct.h"

typedef struct _strpos
{
    int cafedraCode;
    int cafedraName;
    int timePlanned;
    int timeSpent;
    int timeDifference;
} SubstringPositions;

typedef struct _searchMT
{
    struct MachineTime *data;
    SubstringPositions positions;
    struct _searchMT *previous;
    struct _searchMT *next;
} MTsearch;

#endif /* searchStruct_h */
