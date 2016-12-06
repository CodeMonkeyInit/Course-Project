#include "programMenu.h"

bool colorAvailable;

const char *menuChoices[] =
{
    "ГЛАВНОЕ МЕНЮ",
    "Добавить",
    "Вывод",
    "Сортировка",
    "Поиск",
    "Заключение",
    "Открытие/Создание файла",
    "Сохранить и Выйти"
};

const int MENU_CHOICES_COUNT = 8;

bool exitMenu;

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
    
    if (colorAvailable)
    {
        start_color();
        
        init_pair(ACTIVE_INPUT_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
        init_pair(MAIN_THEME_COLOR_PAIR,COLOR_WHITE, COLOR_BLUE);
        init_pair(ACTIVE_ELEMENT_COLOR_PAIR, COLOR_WHITE, COLOR_CYAN);
        init_pair(HIGHLIGHT_COLOR_PAIR , COLOR_WHITE, COLOR_YELLOW);
        init_pair(ERROR_COLOR_PAIR, COLOR_RED, COLOR_WHITE);
    }
    refresh();
}

void exitFunction()
{
    int result = FILE_NOT_OPEN;
    
    while ( FILE_SAVED_SUCCESSFULY != result )
    {
        result = saveStruct(path, true);
        
        if ( NOTHING_TO_SAVE == result )
        {
            printMessage("Нечего сохранять!");
            break;
        }
        else if ( UNKNOWN_FILE_TYPE == result)
        {
            strcat(path, ".bin");
        }
        else if ( FILE_SAVED_SUCCESSFULY != result )
        {
            printMessage("Файл не может быть сохранен введите другой путь");
            getUserInputDialog("Введите полный путь или имя файла (.table - таблица, .bin - сжатый)", path);
        }
        else
        {
            printMessage("Файл успешно сохранен!");
            openFile(path);
        }
    }
    
    programDestructor();
    
    exit(0);
    
}

void searchFunction()
{
    char pattern[50];
    if  ( getUserInputDialog("Введите условие поиска:", pattern) )
    {
        printSearchResults(pattern);
    }
}

void call_function(int function)
{
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
            
            searchFunction();
            break;
        
        case SUMMARY_FUNCTION:
            
            summaryMenu();
            break;
            
        case LOAD_FUNCTION:
            
            openFileMenu();
            break;
            
        case EXIT_FUNCTION:
            
            exitFunction();
            break;
            
        default:
            
            printMessage("Under Contruction 404");
            break;
    }
}
