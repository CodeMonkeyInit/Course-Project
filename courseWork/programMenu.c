#include "programMenu.h"

bool colorAvailable;

const char *menuChoices[] =
{
    "ГЛАВНОЕ МЕНЮ",
    "Добавить",
    "Вывод",
    "Сортировка",
    "Поиск",
    "Открытие/Создание файла",
    "Выход"
};

const int MENU_CHOICES_COUNT = 7;

bool emergencyExit;

void toogleMenuChoice(WINDOW *menu,int highlight, int type)
{
    mvwchgat(menu,
             (MENU_BORDERS / 2 - 1) + highlight,
             2,
             MENU_HIGHLIGHT_LENGTH,
             type,
             2,
             NULL);
}

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

int getStringMiddlePostition(const char *string, const int width)
{
    return ( width - (int)utf8len(string) ) / 2;
}

void init_menu()
{
    setlocale(LC_ALL, "");
    
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);
    set_escdelay(0);

    colorAvailable = has_colors();
    
    if(colorAvailable)
    {
        start_color();
        init_pair(1,COLOR_WHITE, COLOR_BLACK);
        init_pair(2,COLOR_WHITE, COLOR_BLUE);
    }
    refresh();
}

void call_function(int function)
{
    char pattern[50];
    switch (function)
    {
        case ADD_FUNCTION:
            addNewMTRecord();
            break;
        case VIEW_FUNCTION:
            printStruct();
            break;
        case SORT_FUNCTION:
            printSortMenu();
            break;
        case SEARCH_FUNCTION:
            getUserInputDialog("Введите условие поиска:", pattern);
            printSearchResults(pattern);
            break;
        default:
            printMessage("Under Contruction 404");
            break;
    }
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
            refresh();
            return EXIT;
            break;
        case KEY_MAC_ENTER:
            //FIXME ASAP
            if (EXIT_CHOICE == *highlight)
            {
                return EXIT;
            }
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
    emergencyExit = false;
    refreshIfNeeded();
    
    const int MENU_HEIGHT = MENU_BORDERS + CHOICE_SIZE * CHOICES_COUNT;
    int offsetX = (COLS - MENU_WIDTH) / 2;
    int offsetY = (LINES - MENU_HEIGHT) / 2;
    int headerXoffset = getStringMiddlePostition(choices[MENU_HEADER], MENU_WIDTH);
    
    do
    {
        if (emergencyExit)
        {
            emergencyExit = false;
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
            
            if (NULL != menu)
            {
                delwin(menu);
            }
            menu = newwin(MENU_HEIGHT,
                          MENU_WIDTH,
                          offsetY,
                          offsetX);
            refreshNeeded = false;
            refreshIfNeeded();
            //TODO decide if box is needed
            box(menu, 0, 0);
            
            wbkgd(menu, COLOR_PAIR(parameters.colorPair));
            printHelp(HELP_MENU);
            
            mvwprintw(menu, 1, headerXoffset, "%s", choices[MENU_HEADER]);
            
            wmove(menu, MENU_BORDERS / 2 - 1, 0);
            
            for (int i = 1; i < CHOICES_COUNT; i++)
            {
                int choice_lenght  = (int) strlen(choices[i]);
                
                int x = 5,
                y = getcury(menu);
                
                mvwprintw(menu, y + 1, x, "%d: ", i);
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
