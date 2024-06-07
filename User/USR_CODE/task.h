//����ʱ�ֵ�����
#ifndef TASK_H
#define __TASK_H
#include "universal_head.h"
#define MAX_TASKS 20
typedef struct {
    void (*task_func)(void); // ������ָ��
    uint32_t period;         // ��������
    uint32_t last_run;       // �ϴ�����ʱ��
    u8 run_flag;             // ���б�־
} Task;
extern Task tasks[MAX_TASKS];//�̳߳�
extern u8 task_count;//�߳���
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
