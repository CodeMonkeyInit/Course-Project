#ifndef programMenuEditTemplate_h
#define programMenuEditTemplate_h

#include "programMenu.h"

extern int currentChoice;
extern int currentField;
extern int choicesNumber;
extern void *currentChoicePointer;
extern bool somethingDeleted;

typedef struct _editStructArguments
{
    void *(*getNextItem)(void *);
    void *(*getPreviousItem)(void *);
    bool (*deleteSelectedItem)();
    void (*printTable)(int);
    struct MachineTime *(*getCurrentChoiceRecord)(void*);
    int choicesNumber;
    void *start;
} EditArguments;

void toogleChoice(WINDOW *win, int choice,int type);
void moveCursorDown(WINDOW *win,void *(*getNextItem)(void *));
void moveCursorUp(WINDOW *win, void *(*getPreviousItem)(void *));
void editRecord(WINDOW *win, EditArguments arguments);
void editStruct(WINDOW *win, EditArguments arguments);
EditArguments initEditStructArguments(void *(*getNextItem)(void*),
                                      void *(*getPreviousItem)(void*),
                                      bool (*deleteSelectedItem)(),
                                      void (*printTable)(int),
                                      struct MachineTime *(*getCurrentChoiceRecord)(void*),
                                      int choicesNumber,
                                      void *start);

#endif /* programMenuEditTemplate_h */
