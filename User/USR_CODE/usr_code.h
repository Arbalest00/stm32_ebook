#ifndef __USR_CODE_H
#define __USR_CODE_H
#include "universal_head.h"
void sys_init(void);
void usr_sd_init(void);
void rtp_test(void);
void LCD_ShowChar_CH(u16, u16 , u16, u8 );
void universal_show_str(u16, u16, u16, u16, u8, char *);
#endif
