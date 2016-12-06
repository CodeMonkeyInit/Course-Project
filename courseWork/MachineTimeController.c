#include "MachineTimeController.h"

char path[PATH_MAX];
bool programEnded;
bool autosaveAvailable;

pthread_t backupThread;
pthread_mutex_t backupBeingSaved;

void programDestructor()
{
    clear();
    refresh();
    programEnded = true;
    
    pthread_mutex_lock(&backupBeingSaved);
    
    saveFilePathToSettingsFile(path);
    
    pthread_mutex_destroy(&backupBeingSaved);
    
    pthread_cancel(backupThread);
    
    freeStructMem(machineTimeBegining);
    endwin();
}

void removeFilenameFromPath(char *path)
{
    for (long i = strlen(path) - 1; i > 0; i-- )
    {
        if (path[i] == '/')
        {
            path[i] = '\0';
            break;
        }
    }
}


void openFile(char *path)
{
#ifdef __MACH__
    const char *OPEN_COMMAND = "open ";
#elif ifdef __linux__
    const char *OPEN_COMMAND = "eog";
#endif
    
    char openCommandLine[PATH_MAX];
    
    sprintf(openCommandLine, "%s%s", OPEN_COMMAND, path);
    
    system(openCommandLine);
}

void *autosave(void *aruments)
{
    const int BACKUP_EXTENSION_LENGTH = strlen(BACKUP_FILENAME);
    char backupPath[PATH_MAX + BACKUP_EXTENSION_LENGTH];
    
    strcpy(backupPath, path);
    
    removeFilenameFromPath(backupPath);
    
    strcpy(backupPath, BACKUP_FILENAME);
    
    while (!programEnded)
    {
        if (unsavedChangesExist)
        {
            pthread_mutex_lock(&backupBeingSaved);
            
            saveStruct(backupPath, false);
            
            saveFilePathToSettingsFile(backupPath);
            
            pthread_mutex_unlock(&backupBeingSaved);
        }

        sleep(AUTO_SAVE_PERIODICITY_SECONDS);

    }
    
    return NULL;
}

void loadPathFromSettingsFile()
{
    FILE *settingsFile = fopen("app.settings", "rb");
    
    if (NULL != settingsFile)
    {
        if (HEADERS_MATCH == checkFileHeader(settingsFile, MACHINE_FILE_HEADER) )
        {
            //get '\n'
            fgetc(settingsFile);
            fgets(path, sizeof(path), settingsFile);
        }
        fclose(settingsFile);
    }
}

void saveFilePathToSettingsFile(char *path)
{
    FILE *settingsFile = fopen("app.settings", "wb");
    
    if (NULL != settingsFile)
    {
        fprintf(settingsFile, "%s\n%s", MACHINE_FILE_HEADER, path);
        fclose(settingsFile);
    }
}

void setExecutablePathAsWorkDir()
{
    char executablePath[PATH_MAX];
    pid_t pid = getpid();
    if ( 0 < proc_pidpath ( pid, executablePath, sizeof(executablePath) ) )
    {
        //to delete executable name from path
        removeFilenameFromPath(executablePath);
        
        chdir(executablePath);
    }
}

void startMenu()
{
    MENU parameters;
    initMenuParameters(&parameters, menuChoices , MENU_CHOICES_COUNT, call_function);
    setlocale(LC_ALL, "");
    
    init_menu();
    
    if (!autosaveAvailable)
    {
        printMessage("Автосохранение недоступно.");
    }
    else
    {
        printMessage("Программа автосохраняет изменения в файле MTBackup каждую минуту.");
    }
    
    if ( FILE_LOADED != loadStruct(path) )
    {
        openFileMenu();
    }
    
    render_menu(parameters);
}

int loadStructTable(FILE **machineTimeFile)
{
    char *buffer;
    // + 1 to capture '\n' character
    const long tableStart = strlen(TABLE_HEAD) + strlen(MACHINE_FILE_HEADER) + 1;
    
    buffer = loadToBuffer(*machineTimeFile);
    
    return parseBuffer(buffer, tableStart);
}

int loadStruct(char *path)
{
    FILE *machineTimeFile = NULL;
    int type = getFileType(path);
    
    if ( loadFile(&machineTimeFile, path, MACHINE_FILE_HEADER) == FILE_LOADED)
    {
        if (TABLE_TYPE_FILE == type)
        {
            return loadStructTable(&machineTimeFile);
        }
        else if (BINARY_TYPE_FILE == type)
        {
            return loadBinary(&machineTimeFile);
        }
        else
        {
            strcat(path, ".bin");
            return UNKNOWN_FILE_TYPE;
        }
    }
    else
    {
        return FILE_NOT_OPEN;
    }
}

void startProgram()
{
    programEnded = false;
    autosaveAvailable = false;
    pthread_mutex_init(&backupBeingSaved, NULL);
    
    setExecutablePathAsWorkDir();
    loadPathFromSettingsFile();
    
    int threadStatus = pthread_create(&backupThread, NULL, autosave, NULL);
    
    if (0 == threadStatus)
    {
        autosaveAvailable = true;
    }
    
    startMenu();
    printMessage("Программа завершила выполнение");
    
    programDestructor();
    
}
