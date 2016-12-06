#include "programMenu.h"
#include "machineTimeStruct.h"
#include "programMenuEditTemplate.h"

void *getNextMachineTimeRecord(void *current)
{
    return ((struct MachineTime *) current) -> next;
}

void *getPreviousMachineTimeRecord(void *current)
{
    return ((struct MachineTime *) current) -> previous;
}

bool deleteSelectedRecord()
{
    int currentChoicesNumber;
    int linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    
    if ( start == end )
    {
        start = end = NULL;
    }
    else if (currentChoicePointer == start)
    {
        start = start -> next;
    }

    switch ( deleteRecord((struct MachineTime **)&currentChoicePointer) )
    {
        case ENDING:
            currentChoice--;
            break;
        case EMPTY:
            updateTable();
            return EXIT;
        default:
            break;
    }
    end = getTableEnd(start, linesAvailable , GET_NORMAL);
    currentChoicesNumber = (int) getRecordCount(start, end) - 1;
    if ( currentChoicesNumber != choicesNumber )
    {
        choicesNumber = currentChoicesNumber;
        somethingDeleted = true;
    }
    updateTable();
    return CONTINUE;
}

void printEditTable(int helpType)
{
    updateTable();
    printTable(helpType);
}

struct MachineTime *getCurrentEditChoiceRecord(void *choice)
{
    return (struct MachineTime*) choice;
}

void editMachineTimeStruct()
{
    choicesNumber = (int) getRecordCount(start, end) - 1;
    EditArguments arguments = initEditStructArguments(getNextMachineTimeRecord,
                                                      getPreviousMachineTimeRecord,
                                                      deleteSelectedRecord,
                                                      printEditTable,
                                                      getCurrentEditChoiceRecord,
                                                      choicesNumber,
                                                      start);
    editStruct(table, arguments);
}

