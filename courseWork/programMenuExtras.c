#include "programMenu.h"

int _nCols,
    _nRows;

void windowRefreshAndClear(WINDOW *window)
{
    wrefresh(window);
    wclear(window);
}

bool refreshIfNeeded()
{
    if ( (_nCols != COLS) || (_nRows != LINES) )
    {
        _nCols = COLS;
        _nRows = LINES;
        clear();
        refresh();
        
        return true;
    }
    else
    {
        return false;
    }
}

bool keyWasPressed(WINDOW *win, int key)
{
    if( key == wgetch(win) )
    {
        return  true;
    }
    else
    {
        return false;
    }
}

void printError(WINDOW *win ,char *error)
{
    const int FORMAT_MAX_LENGTH = 40;
    char *clearErrorSpaceFormat = calloc ( FORMAT_MAX_LENGTH, sizeof(char) );
    
    sprintf(clearErrorSpaceFormat, "%%%ds", COLS - 1);
    
    mvwprintw(win, 1, 1, clearErrorSpaceFormat , " ");
    wmove(win, 1, 1);
    
    free(clearErrorSpaceFormat);
    
    wattron(win, COLOR_PAIR(5) | A_BOLD);
    
    waddstr(win, error);
  
    wattron(win, COLOR_PAIR(5) | A_BOLD);
}

void printHelp(WINDOW *win, int type)
{
    attron(COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR));
    
    mvwprintw(win, LINES - 2, 0, "%80s", " ");
    switch (type)
    {
        case HELP_MENU:
            
            mvwprintw(win, LINES - 1, 0, "ESC - чтобы выйти без сохранения, ↑↓ для навигации ↲ для потверждения выбора");
            break;
            
        case HELP_TABLE:
            
            mvwprintw(win, LINES - 2, 1, "ESC чтобы вернутся в меню, ↑↓ смена страниц  ↲ режим редактирования");
            mvwprintw(win, LINES - 1, 1, "F5 поиск F8 сортировка");
            break;
            
        case HELP_EDIT_MODE:
            
            mvwprintw(win, LINES - 2, 1, "ESC чтобы вернутся, ↑↓ движение вверх/вниз ↲ редактировать ← удалить запись");
            mvwprintw(win, LINES - 1, 1, "%25s", "");
            break;
            
        case MESSAGE_HELP:
            
            mvwprintw(win, LINES - 2, 1, "Нажмите ↲ , чтобы продолжить");
            break;
            
        case ADD_HELP:
            
            attron(COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
            mvwprintw(win, LINES - 2, 0, "%80s", " ");
            mvwprintw(win, LINES - 2, 1, "ESC - чтобы выйти, ↑↓ для навигации ↲ для потверждения");
            attroff(COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
            break;
            
        case DIALOG_HELP:
            
            mvwprintw(win, LINES - 1, 0, "ESC - чтобы вернуться, ↑↓ для навигации ↲ для потверждения выбора");
            break;
            
        case SEARCH_HELP:
            
            mvwprintw(win, LINES - 2, 1, "ESC чтобы вернутся в меню, ↑↓ смена страниц  ↲ режим редактирования");
            break;
            
        case SEARCH_EDIT_HELP:
            
            mvwprintw(win, LINES - 2, 1, "ESC чтобы вернутся, ↑↓ движение вверх/вниз ↲ редактировать");
            break;
            
        case SUMMARY_HELP:
            
            mvwprintw(win, LINES - 2, 1, "ESC - чтобы вернуться");
            break;
        
        default:
            mvwprintw(win, LINES - 2, 1, "Нажмите ↲  или esc (если ↲ не работает), чтобы продолжить help to be written...");
            break;
    }
    attroff(COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR));
}

void printMessage(char *message)
{
    WINDOW *dialog;
    clear();
    
    do
    {
        int offsetX = (COLS - DIALOG_WIDTH) / 2,
        offsetY = (LINES - DIALOG_HEIGHT) / 2;
        int buttonOffsetX = getStringMiddlePostition(OK_BUTTON, DIALOG_WIDTH),
            buttonOffsetY = DIALOG_HEIGHT - 3;
        refreshIfNeeded();
        
        dialog = newwin(DIALOG_HEIGHT,
                        DIALOG_WIDTH,
                        offsetY,
                        offsetX);
        
        box(dialog, 0, 0);
        wbkgd(dialog, COLOR_PAIR(2));
        mvwprintw(dialog, 3, 3, "%s", message);
        mvwprintw(dialog, buttonOffsetY, buttonOffsetX, "%s", OK_BUTTON);
        mvwchgat(dialog, buttonOffsetY, buttonOffsetX - 2 , utf8len(OK_BUTTON) + 4 , A_REVERSE, MAIN_THEME_COLOR_PAIR, NULL);
        
        printHelp(stdscr, MESSAGE_HELP);
        refresh();
        
        wrefresh(dialog);
    } while ( !keyWasPressed(dialog, KEY_MAC_ENTER) );
    
    delwin(dialog);
    clear();
}


