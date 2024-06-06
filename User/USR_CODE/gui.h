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
extern GUI_STATE gui_state;
extern u8 pointer_select;
extern u16 last_show_char_ptr;
void draw_select_frame(void);
void draw_reading_frame(void);
void draw_setting_frame(void);
u16 show_for_reading(u16 x, u16 y, u16 width, u16 height, u8 size, char *p);
#endif
