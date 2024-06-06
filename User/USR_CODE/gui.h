#ifndef __GUI_H
#define __GUI_H
#include "universal_head.h"
typedef enum
{
    GUI_OPENING,
    GUI_SELECT,
    GUI_READING,
    GUI_SETTING
} GUI_STATE;
#define TITLE_SPACE 40
#define FILE_SPACE 280
#define MAX_FILE_SHOW 5
#define SINGLE_FILE_SPACE FILE_SPACE / MAX_FILE_SHOW
extern GUI_STATE gui_state;
extern u8 pointer_select;
extern u8 pointer_show;
extern u16 last_show_char_ptr;
void draw_select_frame(void);
void draw_reading_frame(void);
void draw_setting_frame(void);
u16 show_for_reading(u16 x, u16 y, u16 width, u16 height, u8 size, char *p);
#endif
