#include "stm32f4xx.h"
#include "ff.h"
#include "universal_head.h"
#include "task.h"
#include "usr_code.h"
#include "sd_operate.h"
#include "usr_key.h"
#include "gui.h"
#include "led.h"
#include "fonts.h"
//时分调度器青春版
void task_register()
{
	//add_task(gui_draw_frame_task,50);
	add_task(key_scan_task,25);
}
int main(void)
{
	sys_init();
	scan_sd_files();
	task_register();
	task_init();
	read_selected_txt();
	while (1)
	{
		run_task();
		//lv_timer_handler();
	}			    	 


}
