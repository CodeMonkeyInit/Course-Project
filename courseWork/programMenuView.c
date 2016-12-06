#include "programMenuTableExtras.h"

int linesAvailable;

WINDOW *table;

struct MachineTime *start,
                   *end;
char *tableString;
int currentPage;
bool refreshTable;
bool controlsLocked;

void printCurrentPageNumber(int currentPage)
{
    const int offsetY = -1;
    const int offsetX = -13;
    
    wattron(stdscr, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD);
    
    wmove(stdscr, LINES + offsetY, COLS + offsetX);
    wprintw(stdscr, "Страница %3d", currentPage + 1);
    
    wattroff(stdscr, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD);
}

void printTable(int helpType)
{
    printHelp(stdscr, helpType);
    
    printCurrentPageNumber(currentPage);
    
    wmove(table, 0, 0);
   
    wattron(table, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD | A_REVERSE);
    
    wprintw(table, "%s", MENU_TABLE_HEAD);
    
    wattroff(table, COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR) | A_BOLD | A_REVERSE );
    
    wattron(table,COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
    
    wprintw(table, "%s", tableString);
    wprintw(table, "%s", TABLE_BOTTOM);
    
    wattroff(table, COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
}

void loadNextPage()
{
    struct MachineTime *temp;
    
    if (NULL == end -> next)
    {
        refreshTable = false;
        return;
    }
    
    temp = end -> next;
    temp = getTableEnd(temp, linesAvailable, GET_NORMAL);
    
    free(tableString);
    
    tableString = recordsToTable(end -> next, temp);
    if ( tableString != NULL )
    {
        refreshTable = true;
        start = end -> next;
        end = temp;
        currentPage++;
    }
    else
    {
        refreshTable = false;
        tableString = recordsToTable(start, end);
    }
}

void loadPreviousPage()
{
    if (currentPage <= 0 )
    {
        refreshTable = false;
        return;
    }
    else
    {
        currentPage--;
        refreshTable = true;
        start = start -> previous;
        end = start;
        start = getTableEnd(end, linesAvailable, GET_REVERSE);
        
        free(tableString);
        tableString = recordsToTable(start, end);
    }
}

bool keypressHandler(int key)
{
    if (controlsLocked)
    {
        if (NULL != machineTimeBegining)
        {
            start = machineTimeBegining;
            end = getTableEnd(start, linesAvailable, GET_NORMAL);
            currentPage = 0;
            controlsLocked = false;
            updateTable();
            refreshTable = true;
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
                
                loadNextPage();
                break;
                
            case KEY_UP:
                
                loadPreviousPage();
                break;
                
            case KEY_MAC_ENTER:
                
                editMachineTimeStruct(linesAvailable);
                refreshTable = true;
                clear();
                refresh();
                
                break;
            case KEY_F(8):
                
                printSortMenu();
                refreshTable = true;
                return EXIT;
                
                break;
            case KEY_F(5):
                
                searchFunction();
                return EXIT;
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

void updateTable()
{
    if (NULL != tableString)
    {
        free(tableString);
    }
    
    tableString = recordsToTable(start, end);
    if (NULL == tableString)
    {
        if (0 == currentPage)
        {
            tableString = malloc(sizeof(char) * strlen(EMPTY_TABLE) + 1);
            strcpy(tableString, EMPTY_TABLE);
        }
        else
        {
            tableString = malloc(sizeof(char) * strlen(EMPTY_PAGE) + 1);
            strcpy(tableString, EMPTY_PAGE);
        }
        controlsLocked = true;
    }
}

void printStruct()
{
    clear();
    refresh();
    controlsLocked = false;
    
    linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    
    currentPage = 0;
    
    int offsetX = (COLS - TABLE_WIDTH) / 2,
        offsetY = ( LINES - (linesAvailable + SPACES_OTHER_THAN_TABLE) ) / 2 ;
    
    table = newwin(LINES,
                   TABLE_WIDTH,
                   offsetY,
                   offsetX);
    tableString = NULL;
    start = getMachineTimeStartingPointer();
    end = getTableEnd(start, linesAvailable, GET_NORMAL);
    updateTable();
    
    refreshTable = true;
    
    do
    {
        if (refreshTable)
        {
            if ( (NULL != start) && (NULL == end -> next) )
            {
                wclear(table);
            }
            
            printTable(HELP_TABLE);
            wrefresh(table);
            refreshTable = false;
        }
    } while ( EXIT != keypressHandler( getch() ) );

    free(tableString);
    
    delwin(table);
    
    clear();
}
