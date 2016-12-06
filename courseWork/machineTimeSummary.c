#include "machineTime.h"
#include "machineTimeStruct.h"

MTSummary getMTSummary()
{
    struct MachineTime *temp = machineTimeBegining;
    MTSummary result;
    
    result.timePlanned = 0;
    result.timeSpend = 0;
    
    while (NULL != temp)
    {
        result.timePlanned += temp -> timeSpent.plan;
        result.timeSpend += temp -> timeSpent.realLife;
        temp = temp -> next;
    }
    
    return result;
}


