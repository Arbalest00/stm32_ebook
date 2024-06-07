//简易时分调度器
#ifndef TASK_H
#define __TASK_H
#include "universal_head.h"
#define MAX_TASKS 20
typedef struct {
    void (*task_func)(void); // 任务函数指针
    uint32_t period;         // 任务周期
    uint32_t last_run;       // 上次运行时间
    u8 run_flag;             // 运行标志
} Task;
extern Task tasks[MAX_TASKS];//线程池
extern u8 task_count;//线程数
void task_init(void);
void run_task(void);
void add_task(void (*task_func)(void), uint32_t period, u8 initial_status);
void stop_task(void (*func_to_stop)(void));
void wake_task(void (*func_to_wake)(void));
void change_task_frequency(void (*func_to_change)(void), uint32_t new_period);
void gui_draw_frame_task(void);
void key_scan_task(void);
void time_count_task(void);
void reading_auto_scroll_task(void);
#endif
