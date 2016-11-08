//
//  programMenuSearch.c
//  courseWork
//
//  Created by Денис Кулиев on 06.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuSearch.h"
#include "searchStruct.h"

WINDOW *searchResult;
char *searchResultString;
MTsearch *searchResultHead, *searchResultTail, *searchResultPointer;
bool searchTableNeedsRefresh, searchControlsLocked;

int currentSearchPage;

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
    mvwchgat(searchResult, startY, offsetX, utf8len(pattern), A_BOLD, 3, NULL);
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
    
    if ( (EMPTY_SEARCH != searchResultString) && (NULL != searchResultString) )
    {
        free(searchResultString);
    }
    
    if ( SEARCH_FAILED == recordsFound || (0 == recordsFound) )
    {
        searchResultString = EMPTY_SEARCH;
    }
    else
    {
        if (recordsFound > linesAvailable)
        {
            recordsFound = linesAvailable;
        }
        searchResultString = calloc( recordsFound * RECORD_SIZE, sizeof(char) );
    }
    
    while ( (NULL != temp) && (i < linesAvailable) )
    {
        char *tempTableString = recordsToTable(temp -> data, temp -> data);
        strcat(searchResultString, tempTableString);
        free(tempTableString);
        searchResultTail = temp;
        temp = temp -> next;
        i++;
    }
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
            
            searchResultHead = searchResultHead -> previous;
            updateSearchPointerHead();
            updateSearchString();
        }
        
    }
}

void printSearchResult(int helpType)
{
    printHelp(helpType);
    
    wattron(searchResult,COLOR_PAIR(2));
    wprintw(searchResult, "%s", MENU_TABLE_HEAD);
    wprintw(searchResult, "%s", searchResultString);
    wprintw(searchResult, "%s", TABLE_BOTTOM);
    wattroff(searchResult, COLOR_PAIR(2));
    
    wrefresh(searchResult);
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
                    return EXIT;
                }
                loadNextSearchPage();
                break;
            case KEY_UP:
                loadSearchPreviousPage();
                break;
            case KEY_MAC_ENTER:
//TODO EditSearchResults
//                editStruct();
//                searchTableNeedsRefresh = true;
//                clear();
//                refresh();
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
    searchControlsLocked = false;
    searchTableNeedsRefresh = true;
    
    searchResultPointer = searchResultHead = searchInStruct(pattern);
    searchResultTail = NULL;
    
    int linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    
    int offsetX = (COLS - TABLE_WIDTH) / 2,
    offsetY = ( LINES - (linesAvailable + SPACES_OTHER_THAN_TABLE) ) / 2 ;
    
    currentPage = 0;
    
    searchResult = newwin(LINES,
                          TABLE_WIDTH,
                          offsetY,
                          offsetX);
    searchResultString = NULL;
    
    updateSearchString();
    
    do
    {
        if (searchTableNeedsRefresh)
        {
            printSearchResult(HELP_TABLE);
            colorSearchResult(pattern);
            windowRefreshAndClear(searchResult);
            searchTableNeedsRefresh = false;
        }
    } while ( EXIT != searchKeypressHandler( getch() ) );
    
    if (EMPTY_SEARCH != searchResultString)
    {
        free(searchResultString);
    }
    
    wclear(searchResult);
    delwin(searchResult);
    
    clear();
    refresh();
}
