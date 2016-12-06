#include "programMenu.h"

MTSummary MTsummary;

long difference;

float additionHalf;
float percent;

const char *summaryChoices[] =
{
    "ЗАКЛЮЧЕНИЕ",
    "Просмотреть",
    "Сохранить",
};

const int SUMMARY_CHOICES_COUNT = 3;

char *getVerdict(long difference)
{
    if (difference > 0)
    {
        return "Возник избыток машинного времени.";
    }
    else if (difference < 0)
    {
        return "Возник недостаток машинного времени.";
    }
    else
    {
        return "Машинное время было израсходовано полностью.";
    }
}

void viewSummary()
{
    const int STRING_MAX_LENGTH = 60;
    const int MAX_LINES = 7;
    
    
    int summaryLines = LINES;
    int summaryCols  = COLS;
    
    clear();
    
    WINDOW *summary =  newwin(summaryLines, summaryCols, 0, 0);
    
    do
    {
        wclear(summary);
        
        summaryLines = LINES;
        summaryCols  = COLS;
        
        wresize(summary, summaryLines, summaryCols);
        
        int currentLine = 1;
        int middlePositionX = (summaryCols - STRING_MAX_LENGTH) / 2;
        int middlePositionY = (summaryLines - MAX_LINES) / 2;
        
        wbkgd(summary, COLOR_PAIR(MAIN_THEME_COLOR_PAIR));
        wmove(summary, middlePositionY + currentLine++, middlePositionX);
        wprintw(summary, "ЗАКЛЮЧЕНИЕ ПО ИНСТИТУТУ");
        
        wmove(summary, middlePositionY + currentLine++ , middlePositionX);
        wprintw(summary, "Показатель запланированного времени      : %ld часов", MTsummary.timePlanned);
        
        wmove(summary, middlePositionY + currentLine++ , middlePositionX);
        wprintw(summary, "Показатель фактического расхода          : %ld часов", MTsummary.timeSpend);
        
        currentLine++;
        wmove(summary, middlePositionY + currentLine++ , middlePositionX);
        
        wattron(summary, A_BOLD | A_UNDERLINE);
        
        wprintw(summary, "%s" , getVerdict(difference));
        
        wattroff(summary, A_BOLD | A_UNDERLINE);
        
        wmove(summary, middlePositionY + currentLine++ , middlePositionX);
        wprintw(summary, "Отклонение от нормы (абсолютное значение): %ld", difference);
        
        wmove(summary, middlePositionY + currentLine++ , middlePositionX);
        wprintw(summary, "Отклонение от нормы  (в процентах)       : %.2f%%", percent);
        
        printHelp(summary, SUMMARY_HELP);
        
        wrefresh(summary);
        
    } while (!keyWasPressed(summary ,KEY_ESC));
    
    delwin(summary);
}

void saveSummary(char *path)
{

    FILE *summaryFile;
    
    if ( TEXT_TYPE_FILE != getFileType(path) )
    {
        strcat(path, ".txt");
    }
    
    summaryFile = fopen(path, "w");
    
    if (NULL == summaryFile)
    {
        printMessage("Не удалось сохранить файл, попробуйте другой путь");
    }
    else
    {
        
        fprintf(summaryFile, "ЗАКЛЮЧЕНИЕ ПО ИНСТИТУТУ");
        fprintf(summaryFile, "\nПоказатель запланированного времени      : %ld часов", MTsummary.timePlanned);
        fprintf(summaryFile, "\nПоказатель фактического расхода          : %ld часов", MTsummary.timeSpend);
        fprintf( summaryFile, "\n\n%s", getVerdict(difference) );
        fprintf(summaryFile, "\nОтклонение от нормы (абсолютное значение): %ld", difference);
        fprintf(summaryFile, "\nОтклонение от нормы  (в процентах)       : %.2f%%", percent);
        
        fclose(summaryFile);
        
        openFile(path);
        
        printMessage("Файл успешно сохранен.");
    }
}

void summaryCallFunction(int function)
{
    const int VIEW_SUMMARY = 1;
    const int SAVE_SUMMARY = 2;

    char *path;
    
    switch (function)
    {
        case VIEW_SUMMARY:
            
            viewSummary();
            break;
            
        case SAVE_SUMMARY:
            
            path = malloc(sizeof(char) * PATH_MAX);
            if ( getUserInputDialog("Введите полный путь или имя файла", path) )
            {
                saveSummary(path);
            }
            free(path);
            break;
            
        default:
            
            printMessage("Неизвестный пункт меню или он скоро будет");
            break;
    }
}

void summaryMenu()
{
    MTsummary = getMTSummary();
    difference = MTsummary.timePlanned - MTsummary.timeSpend;
    additionHalf   = (MTsummary.timePlanned + MTsummary.timeSpend) / 2;
    
    percent = fabs( (float)difference / additionHalf ) * 100;
    
    MENU parameters;
    initMenuParameters(&parameters, summaryChoices , SUMMARY_CHOICES_COUNT, summaryCallFunction);
    render_menu(parameters);
    
}

