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
    return CONTINUE;
}

struct MachineTime *getCurrentSearchChoiceRecord(void *choice)
{
    return ((MTsearch *) choice) -> data;
}

void printSearchEditTable(int helpType)
{
    updateSearchString();
    printSearchResultTable(SEARCH_EDIT_HELP);
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
