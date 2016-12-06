#include "programMenuSearch.h"
#include "programMenuSearchShared.h"
#include "programMenuEditTemplate.h"

void *getNextSearchPointer(void *current)
{
    return ((MTsearch *)current) -> next;
}

void *getPreviousSearchPointer(void *current)
{
    return ((MTsearch *)current) -> previous;
}

bool deleteSelectedSearchResult()
{
    searchPageClear = false;
    deleteRecord(&( ((MTsearch *)currentChoicePointer)->data ));
    
    ( (MTsearch *)currentChoicePointer ) -> data = NULL;
    
    switch ( deleteSearchResult( (MTsearch **)&currentChoicePointer ) )
    {
        case ENDING:
            if (!searchPageClear)
            {
                choicesAvailable--;
                currentChoice--;
                break;
            }
        case EMPTY:
            searchTableNeedsRefresh = true;
            searchControlsLocked = true;
            return EXIT;
        default:
            break;
    }
    
    choicesNumber = choicesAvailable;
    
    somethingDeleted = true;
    return CONTINUE;
}

struct MachineTime *getCurrentSearchChoiceRecord(void *choice)
{
    return ((MTsearch *) choice) -> data;
}

void printSearchEditTable(int helpType)
{
    updateSearchString();
    printSearchResultTable(helpType);
}

void editSearchResults()

{
    EditArguments arguments = initEditStructArguments(getNextSearchPointer,
                                                      getPreviousSearchPointer,
                                                      deleteSelectedSearchResult,
                                                      printSearchEditTable,
                                                      getCurrentSearchChoiceRecord,
                                                      choicesAvailable,
                                                      searchResultHead);
    editStruct(searchResult, arguments);
}
