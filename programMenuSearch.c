#include "programMenuSearch.h"
#include "searchStruct.h"
#include "programMenuSearchShared.h"

WINDOW *searchResult;
char *searchResultString;
int choicesAvailable;
MTsearch *searchResultHead, *searchResultTail, *searchResultPointer;
bool searchTableNeedsRefresh, searchControlsLocked, searchPageClear;

int currentSearchPage;
int searchResultsOnscreen;

int getPrintableResultsCount(int linesAvailble)
{
    MTsearch *temp = searchResultHead;
    int resultsCount = 0;
    
    while ( (temp != NULL) && (resultsCount < linesAvailble) )
    {
        temp = temp -> next;
        resultsCount++;
    }
    return resultsCount;
}

int deleteSearchResult(MTsearch **record)
{
    int position;
    MTsearch *deleting = *record,
             *previous = deleting -> previous,
             *next = deleting -> next;
    
    if ( (NULL == previous) && (NULL == next) )
    {
        searchResultPointer = searchResultHead = searchResultTail = *record = NULL;
        position = EMPTY;
    }
    else if (NULL == next)
    {
        //конец
        
        //и если результаты поиска пусты
        if (searchResultTail == searchResultHead)
        {
            searchPageClear = true;
            searchResultHead = NULL;
        }
        *record = previous;
        previous -> next = NULL;
        position = ENDING;
    }
    else if (NULL == previous)
    {
        //начало
        searchResultPointer = searchResultHead = *record = next;
        next -> previous = NULL;
        position = BEGINING;
    }
    else
    {
        //середина
        if (searchResultHead == *record)
        {
            searchResultHead = searchResultHead -> next;
        }
        *record = next;
        next -> previous = previous;
        previous -> next = next;
        position = MIDDLE;
    }
    free(deleting);
    
    deleting = NULL;
    
    return position;
}


void updateSearchPointerHead()
{
    int linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    int i = 0;
    while ( (NULL != searchResultHead -> previous) && (i < linesAvailable) )
    {
        searchResultHead = searchResultHead -> previous;
        i++;
    }
}

void colorSubstring(int startY, int startX ,char *pattern, int substingPosition)
{
    int offsetX = startX + substingPosition - 1;
    mvwchgat(searchResult, startY, offsetX, utf8len(pattern), A_BOLD, HIGHLIGHT_COLOR_PAIR, NULL);
}

void colorSearchResult(char *pattern)
{
    MTsearch *temp = searchResultHead;
    if ( has_colors() && temp != NULL )
    {
        int offsetY = SEARCH_TABLE_START;
        {
            while (temp != searchResultTail -> next)
            {
                SubstringPositions positions = temp -> positions;
                if (SUBSTRING_NOT_FOUND != positions.cafedraCode)
                {
                    colorSubstring(offsetY, CAFEDRA_CODE_OFFSET_X, pattern, positions.cafedraCode);
                }
                
                if (SUBSTRING_NOT_FOUND != positions.cafedraName)
                {
                    colorSubstring(offsetY, CAFEDRA_NAME_OFFSET_X, pattern, positions.cafedraName);
                }
                
                if (SUBSTRING_NOT_FOUND != positions.timePlanned)
                {
                    colorSubstring(offsetY, TIME_PLANNED_OFFSET_X, pattern, positions.timePlanned);
                }
                
                if (SUBSTRING_NOT_FOUND != positions.timeSpent)
                {
                    colorSubstring(offsetY, TIME_SPENT_OFFSET_X, pattern, positions.timeSpent);
                }
                if (SUBSTRING_NOT_FOUND != positions.timeDifference)
                {
                    colorSubstring(offsetY, TIME_DIFFERENCE_OFFSET_X, pattern, positions.timeDifference);
                }
                temp = temp -> next;
                offsetY++;
            }
        }
    }
}

void updateSearchString()
{
    MTsearch *temp = searchResultHead;
    int recordsFound = getRecordsFound();
    int linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    int i = 0;
    searchResultsOnscreen = getPrintableResultsCount(linesAvailable);
    
    if (NULL != searchResultString)
    {
        free(searchResultString);
    }
    
    if ( SEARCH_FAILED == recordsFound || (0 == recordsFound) ||  (0 == searchResultsOnscreen) )
    {
        searchControlsLocked = true;
        searchResultString = malloc( sizeof(char) * strlen(EMPTY_SEARCH) + 1);
        strcpy(searchResultString, EMPTY_SEARCH);
        return;
    }
    else
    {
        searchResultString = calloc( searchResultsOnscreen * RECORD_SIZE, sizeof(char) );
    }
    
    while ( (NULL != temp) && (i < searchResultsOnscreen) )
    {
        char *tempTableString = recordsToTable(temp -> data, temp -> data);
        strcat(searchResultString, tempTableString);
        free(tempTableString);
        searchResultTail = temp;
        temp = temp -> next;
        i++;
    }
    
    choicesAvailable = i - 1;
}

void loadNextSearchPage()
{
    MTsearch *temp;
    
    if (NULL == searchResultTail -> next)
    {
        searchTableNeedsRefresh = false;
        return;
    }
    temp = searchResultHead;
    
    searchResultHead = searchResultTail -> next;
    
    updateSearchString();
    
    if ( searchResultString != EMPTY_SEARCH )
    {
        searchTableNeedsRefresh = true;
        currentSearchPage++;
    }
    else
    {
        searchTableNeedsRefresh = false;
        searchResultHead = temp;
        updateSearchString();
    }
}

void loadSearchPreviousPage()
{
    if (currentSearchPage <= 0 )
    {
        searchTableNeedsRefresh = false;
        return;
    }
    else
    {
        if (NULL != searchResultHead -> previous)
        {
            currentSearchPage--;
            searchTableNeedsRefresh = true;
            
            updateSearchPointerHead();
            updateSearchString();
        }
    }
}

void printSearchResultTable(int helpType)
{
    printHelp(stdscr, helpType);
    
    printCurrentPageNumber(currentSearchPage);
    
    wmove(searchResult, 0, 0);
    wattron( searchResult, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD | A_REVERSE );
    wprintw(searchResult, "%s", MENU_TABLE_HEAD);
    wattroff(searchResult, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD | A_REVERSE  );
    
    wattron(searchResult,COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
    wprintw(searchResult, "%s", searchResultString);
    wprintw(searchResult, "%s", TABLE_BOTTOM);
    wattroff(searchResult, COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
}

bool searchKeypressHandler(int key)
{
    if (searchControlsLocked)
    {
        if (NULL != searchResultPointer)
        {
            searchResultHead = searchResultPointer;
            currentPage = 0;
            searchControlsLocked = false;
            updateSearchString();
            searchTableNeedsRefresh = true;
        }
        if (KEY_ESC == key)
        {
            return EXIT;
        }
    }
    else
    {
        switch (key)
        {
            case KEY_DOWN:
                if (NULL == searchResultTail)
                {
                    searchTableNeedsRefresh = false;
                    break;
                }
                loadNextSearchPage();
                break;
            case KEY_UP:
                loadSearchPreviousPage();
                break;
            case KEY_MAC_ENTER:
                editSearchResults(LINES - SPACES_OTHER_THAN_TABLE);
                updateSearchString();
                searchTableNeedsRefresh = true;
                break;
            case KEY_ESC:
                return EXIT;
                break;
            default:
                break;
        }
    }
    return CONTINUE;
}

void printSearchResults(char *pattern)
{
    int previousPageSearchReultsCount = searchResultsOnscreen;
    refresh();
    searchControlsLocked = false;
    searchTableNeedsRefresh = true;
    searchResultTail = NULL;
    searchResultString = NULL;
    choicesAvailable = 0;
    
    searchResultPointer = searchResultHead = searchInStruct(pattern);
    
    int linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    
    int offsetX = (COLS - TABLE_WIDTH) / 2,
    offsetY = ( LINES - (linesAvailable + SPACES_OTHER_THAN_TABLE) ) / 2 ;
    
    currentSearchPage = 0;
    
    searchResult = newwin(LINES,
                          TABLE_WIDTH,
                          offsetY,
                          offsetX);
    
    updateSearchString();
    
    do
    {
        if (searchTableNeedsRefresh)
        {
            if (previousPageSearchReultsCount != searchResultsOnscreen)
            {
                wclear(searchResult);
                previousPageSearchReultsCount = searchResultsOnscreen;
            }
            printSearchResultTable(SEARCH_HELP);
            colorSearchResult(pattern);
            wrefresh(searchResult);
            searchTableNeedsRefresh = false;
        }
    } while ( EXIT != searchKeypressHandler( getch() ) );

    free(searchResultString);
    
    freeSearchResults(searchResultPointer);
    delwin(searchResult);
    
    clear();
}
