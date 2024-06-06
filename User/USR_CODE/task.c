#include "task.h"
#include "gui.h"
#include "stm32f4xx_it.h"
#include "usr_key.h"
#include "usr_code.h"
Task tasks[MAX_TASKS];
u8 task_count = 0;
void task_init()
{
    if (SysTick_Config(SystemCoreClock / 1000))
    { // 1 ms÷–∂œ“ª¥Œ
        while (1)
        {
            POINT_COLOR = RED;
            LCD_ShowString(30, 150, 200, 16, 16, "SysTick_Config Error!");
        }
    }
}
void run_task()
{
    u32 i;
    for (i = 0; i < task_count; i++)
    {
        if (tasks[i].run_flag == 1)
        {
            if ((tick_count - tasks[i].last_run) >= tasks[i].period)
            {
                tasks[i].task_func();
                tasks[i].last_run = tick_count;
            }
        }
        else
        {
            tasks[i].last_run = tick_count;
        }
    }
}
void add_task(void (*task_func)(void), uint32_t period)
{
    if (task_count < MAX_TASKS)
    {
        tasks[task_count].task_func = task_func;
        tasks[task_count].period = period;
        tasks[task_count].last_run = 0;
        tasks[task_count].run_flag = 1;
        task_count++;
    }
};
void stop_task(void (*func_to_stop)(void))
{
    for (u8 i = 0; i < task_count; i++)
    {
        if (tasks[i].task_func == func_to_stop)
        {
            tasks[i].run_flag = 0;
            break;
        }
    }
}
void wake_task(void (*func_to_wake)(void))
{
    for (u8 i = 0; i < task_count; i++)
    {
        if (tasks[i].task_func == func_to_wake)
        {
            tasks[i].run_flag = 1;
            break;
        }
    }
}
void gui_draw_frame_task()
{
    switch (gui_state)
    {
    case GUI_OPENING:
        break;
    case GUI_SELECT:
        draw_select_frame();
        break;
    case GUI_READING:
        draw_reading_frame();
        break;
    case GUI_SETTING:
        draw_setting_frame();
        break;
    }
}
void key_scan_task()
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        POINT_COLOR = BLACK;
        LCD_ShowNum(30+i*16, 30, key_state[i], 1, 16);
        if (key_state[i] == 1)
        {
            switch (i)
            {
            case KEY_UP:
                key_handler_up();
                break;
            case KEY_DOWN:
                key_handler_down();
                break;
            case KEY_BACK:
                key_handler_back();
                break;
            case KEY_CONFIRM:
                key_handler_confirm();
                break;
            case KEY_SETTING:
                key_handler_setting();
                break;
            case KEY_ALTERNATIVE:
                key_handler_alternative();
                break;
            default:
                break;
            }
        }
    }
}