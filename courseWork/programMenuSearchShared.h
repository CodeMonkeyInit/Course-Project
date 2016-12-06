#ifndef programMenuSearchSharedVariables_h
#define programMenuSearchSharedVariables_h

extern WINDOW *searchResult;
extern char *searchResultString;
extern MTsearch *searchResultHead, *searchResultTail, *searchResultPointer;
extern bool searchTableNeedsRefresh, searchControlsLocked;
extern int choicesAvailable;
extern int searchResultsOnscreen;
extern bool searchPageClear;

void updateSearchString();
void printSearchResultTable(int helpType);
#endif /* programMenuSearchSharedVariables_h */
