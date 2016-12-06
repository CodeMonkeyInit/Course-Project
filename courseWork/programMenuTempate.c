#include "programMenu.h"

void initMenuParameters(MENU *parameters,
                        const char *choices[] ,
                        const int choicesCount,
                        void (*menuCallFunction)(int))
{
    parameters -> choices = choices;
    parameters -> choicesCount = choicesCount;
    parameters -> colorPair = DEFAULT_COLOR_PAIR;
    parameters -> highlight = 1;
    parameters -> menuCallFunction = menuCallFunction;
}

void toogleMenuChoice(WINDOW *menu,int highlight, int type)
{
    mvwchgat(menu,
             (MENU_BORDERS / 2 - 1) + highlight,
             2,
             MENU_HIGHLIGHT_LENGTH,
             type,
             MAIN_THEME_COLOR_PAIR,
             NULL);
}

bool menuHandler(WINDOW *menu, MENU *parameters, bool *refreshNeeded)
{
    int *highlight = &(parameters -> highlight);
    const int CHOICES_COUNT = parameters -> choicesCount;
    
    int key = getch();
    
    toogleMenuChoice(menu, *highlight, A_NORMAL);
    
    if (isdigit(key))
    {
        int temp = key - '0';
        if ( (temp < CHOICES_COUNT) && (temp >= 1) )
        {
            *highlight = temp;
            key = KEY_WAS_USED;
        }
    }
    switch (key)
    {
        case KEY_DOWN:
            (*highlight)++;
            if (*highlight >= CHOICES_COUNT)
            {
                *highlight = 1;
            }
            break;
        case KEY_UP:
            (*highlight)--;
            if (*highlight < 1)
            {
                *highlight = CHOICES_COUNT - 1;
            }
            break;
        case KEY_ESC:
            clear();
            return EXIT;
            break;
        case KEY_MAC_ENTER:
            parameters -> menuCallFunction(*highlight);
            *refreshNeeded = true;
            break;
        case KEY_WAS_USED:
            break;
        default:
            break;
    }
    toogleMenuChoice(menu, *highlight, A_REVERSE);
    return CONTINUE;
}

void render_menu(MENU parameters)
{
    WINDOW *menu = NULL;
    bool refreshNeeded = true;
    const int CHOICES_COUNT = parameters.choicesCount;
    const char **choices = parameters.choices;
    exitMenu = false;
    refreshIfNeeded();
    
    const int MENU_HEIGHT = MENU_BORDERS + CHOICE_SIZE * CHOICES_COUNT;
    int offsetX = (COLS - MENU_WIDTH) / 2;
    int offsetY = (LINES - MENU_HEIGHT) / 2;
    int headerXoffset = getStringMiddlePostition(choices[MENU_HEADER], MENU_WIDTH);
    
    menu = newwin(MENU_HEIGHT,
                  MENU_WIDTH,
                  offsetY,
                  offsetX);
    do
    {
        if (exitMenu)
        {
            exitMenu = false;
            break;
        }
        
        if ( refreshIfNeeded() )
        {
            refreshNeeded = true;
        }
        
        if (refreshNeeded)
        {
            clear();
            
            offsetX = (COLS - MENU_WIDTH) / 2;
            offsetY = (LINES - MENU_HEIGHT) / 2;
            
            mvwin(menu, offsetY, offsetX);
            
            refreshNeeded = false;

            box(menu, 0, 0);
            
            wbkgd(menu, COLOR_PAIR(parameters.colorPair));
            printHelp(stdscr, HELP_MENU);
            
            mvwprintw(menu, 1, headerXoffset, "%s", choices[MENU_HEADER]);
            
            wmove(menu, MENU_BORDERS / 2 - 1, 0);
            
            for (int i = 1; i < CHOICES_COUNT; i++)
            {
                int choice_lenght  = (int) strlen(choices[i]);
                
                int x = 5,
                y = getcury(menu);
                wmove(menu, y + 1, x);
                wmove( menu, y + 1, getStringMiddlePostition(choices[i], MENU_WIDTH) );
                
                for (int j = 0; j < choice_lenght; j++)
                {
                    wprintw(menu, "%c", choices[i][j]);
                }
            }
            refresh();
        }
        
        toogleMenuChoice(menu, parameters.highlight, A_REVERSE);
        wmove(stdscr, 0, 0);
        wrefresh(menu);
    } while (EXIT != menuHandler(menu, &parameters, &refreshNeeded) );
    
    delwin(menu);
}
