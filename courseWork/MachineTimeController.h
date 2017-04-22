#ifndef IMachineTime_h
#define IMachineTime_h

#include <stdbool.h>
#include <locale.h>
#include <sys/syslimits.h>
#include <libproc.h>
#include <pthread.h>

#include "machineTime.h"
#include "programMenu.h"

#define AUTO_SAVE_PERIODICITY_SECONDS 1

#define BACKUP_FILENAME "MTbackup.bin"
#define TABLE_START_OFFSET 351
#define saveStruct(path, savedByUser) saveFile(path, savedByUser)

extern char path[PATH_MAX];

extern bool programEnded;
extern bool autosaveAvailable;

//PTHREADS
extern pthread_t backupThread;
extern pthread_mutex_t backupBeingSaved;


void openFile(char *path);
void programDestructor();


int loadStruct(char * path);
void startProgram();
void saveFilePathToSettingsFile(char *path);

#endif /* IMachineTime_h */
