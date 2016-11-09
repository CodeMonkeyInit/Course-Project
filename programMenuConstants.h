//
//  programMenuConstants.h
//  courseWork
//
//  Created by Денис Кулиев on 04.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef programMenuConstants_h
#define programMenuConstants_h

//COLOR PAIRS
#define ACTIVE_INPUT_COLOR_PAIR   1
#define MAIN_THEME_COLOR_PAIR     2
#define ACTIVE_ELEMENT_COLOR_PAIR 3
#define HIGHLIGHT_COLOR_PAIR      4
#define ERROR_COLOR_PAIR          5

//MENU
#define MENU_HEADER           0
#define MENU_BORDERS          16
#define CHOICE_SIZE           1
#define ADD_FUNCTION          1
#define VIEW_FUNCTION         2
#define SORT_FUNCTION         3
#define SEARCH_FUNCTION       4
#define LOAD_FUNCTION         5
#define EXIT_FUNCTION         6
#define MENU_WIDTH            40
#define MENU_HIGHLIGHT_LENGTH MENU_WIDTH - 4
#define TABLE_WIDTH           69
#define DEFAULT_COLOR_PAIR    2

//DIALOG
#define DIALOG_WIDTH          75
#define DIALOG_HEIGHT         10
#define OK_BUTTON             "OK"
#define CHOICE_INPUT_FIELD    0
#define CHOICE_OK_BUTTON      1
#define INPUT_FIELD_MARGIN    6
#define INPUT_FIELD_LENGTH    DIALOG_WIDTH - INPUT_FIELD_MARGIN
#define TEXT_FIELD_MARGIN     2
#define TEXT_FIELD_LENGTH     INPUT_FIELD_LENGTH - TEXT_FIELD_MARGIN

//HELP
#define HELP_MENU             0
#define HELP_TABLE            1
#define HELP_EDIT_MODE        2
#define MESSAGE_HELP          3
#define ADD_HELP              4
#define DIALOG_HELP           5

//ADD
#define CAFEDRA_CODE_CHOICE 0
#define CAFEDRA_NAME_CHOICE 1
#define TIME_PLANNED_CHOICE 2
#define TIME_USED_CHOICE    3
#define NORMAL_CHOICE_SIZE  25
#define ADD_BUTTON_SIZE     50
#define ADD_RECORD          2

//VIEW and EDIT
#define TABLE_CHOICE_WIDTH 66
#define SPACES_OTHER_THAN_TABLE 6
#define EXIT               true
#define CONTINUE           false
#define EMPTY_TABLE "\n│                      На этой странице записей нет!               │"
#define MENU_TABLE_HEAD "┌──────────────────────────────────────────────────────────────────┐\n│   №│Код Кафедры│    Название Кафедры│По Плану│По Факту│Отклонения│\n│    │           │                    │        │        │          │"

//EDIT
#define TABLE_HEAD_SIZE           3
#define CAFEDRA_CODE_TABLE_OFFSET 6
#define CAFEDRA_NAME_TABLE_OFFSET 18
#define TIME_PLANNED_TABLE_OFFSET 39
#define TIME_USED_TABLE_OFFSET    48
#define CAFEDRA_CODE_LENGTH       11
#define TIME_LENGTH               8
#define FIELD_COUNT               4
#define TABLE_TIME_PLANNED        2
#define TABLE_TIME_USED           3

//SORT
#define BY_CAFEDRA_CODE 1
#define BY_CAFEDRA_NAME 2
#define BY_TIME_PLANNED 3
#define BY_TIME_SPENT   4
#define BY_DIFFERENCE   5

#define ASCENDING  1
#define DESCENDING 2
#define SORT_ABORTED 0

//SEARCH
#define SEARCH_TABLE_START       3
#define CAFEDRA_CODE_OFFSET_X    7
#define CAFEDRA_NAME_OFFSET_X    19
#define TIME_PLANNED_OFFSET_X    40
#define TIME_SPENT_OFFSET_X      49
#define TIME_DIFFERENCE_OFFSET_X 58
#define EMPTY_SEARCH             "\n│                       Ничего не найдено!                         │"


#endif /* programMenuConstants_h */
