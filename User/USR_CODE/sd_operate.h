#ifndef __SD_OPERATE_H
#define __SD_OPERATE_H
#include "universal_head.h"
#define MAX_FILES 100 //不会塞这么多
#define MAX_FILENAME_LENGTH 128 //根本到不了这么长好吗
#define TXT_READ_BUFFER_SIZE 601 //加一个 怕爆炸
extern u8 filenames[MAX_FILES][MAX_FILENAME_LENGTH]; // 用于存储文件名
extern u8 file_count; // 文件计数
extern u8 file_exist_flag;
extern u8 file_open_flag;
extern u16 page_ptr;
extern u32 file_ptr;
extern u8 txt_read_buffer[TXT_READ_BUFFER_SIZE]; 
void txt_reset(void); 
void scan_sd_files(void);
UINT read_selected_txt(void);
void load_new_page(void);
void load_last_page(void);
#endif
