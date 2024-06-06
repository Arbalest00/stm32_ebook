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
void add_task(void (*task_func)(void), uint32_t period);
void stop_task(void (*func_to_stop)(void));
void wake_task(void (*func_to_wake)(void));
void gui_draw_frame_task(void);
void key_scan_task(void);
#endif
