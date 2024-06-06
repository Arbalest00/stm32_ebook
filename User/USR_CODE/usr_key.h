#ifndef __USR_KEY_H
#define __USR_KEY_H
#include "universal_head.h"
//±¸Ñ¡PG13 PG11 PG2 PG4 PG6 PG1 PG3 PF5
#define KEY_UP 0 //PG13
#define KEY_DOWN 1 //PG11
#define KEY_BACK 2 //PG2
#define KEY_CONFIRM 3 //PG4
#define KEY_SETTING 4 //PG6
#define KEY_ALTERNATIVE 5 //PG1
extern u8 key_state[8];
void usr_key_init(void);
void key_handler_up(void);
void key_handler_down(void);
void key_handler_back(void);
void key_handler_confirm(void);
void key_handler_setting(void);
void key_handler_alternative(void);
#endif
