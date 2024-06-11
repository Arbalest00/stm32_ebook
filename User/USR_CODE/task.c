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
    {
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
void add_task(void (*task_func)(void), uint32_t period,u8 initial_status)
{
    if (task_count < MAX_TASKS)
    {
        tasks[task_count].task_func = task_func;
        tasks[task_count].period = period;
        tasks[task_count].last_run = 0;
        tasks[task_count].run_flag = initial_status;
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
void change_task_frequency(void (*func_to_change)(void), uint32_t new_period)
{
    for (u8 i = 0; i < task_count; i++)
    {
        if (tasks[i].task_func == func_to_change)
        {
            tasks[i].period = new_period;
            break;
        }
    }
}
void gui_draw_frame_task()
{
   gui_draw_frame();
}
void key_scan_task()
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        //POINT_COLOR = BLACK;
        //LCD_ShowNum(30+i*16, 30, key_state[i], 1, 16);
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
void time_count_task()
{
    if (gui_state == GUI_READING)
    {
        reading_time_sec++;
        gui_draw_frame();
        if (reading_time_sec == 60)
        {
            reading_time_sec = 0;
            reading_time_min++;
            if (reading_time_min == 60)
            {
                reading_time_min = 0;
                reading_time_hour++;
            }
        }
    }
}
void reading_auto_scroll_task()
{
    if (gui_state == GUI_READING)
    {
        if (reading_mode == 1)
        {
            LCD_Clear(reading_back_color);
            load_new_page();
            gui_draw_frame();
        }
    }
}