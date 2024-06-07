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
	add_task(gui_draw_frame_task,100,1);//改完速度记得拿秒表掐系统中断被拖慢了多少
	add_task(key_scan_task,50,1);
	add_task(time_count_task,(u32)(1000/3),1);//早知道 换个时钟源
	add_task(reading_auto_scroll_task,(u32)(scroll_time/3),1);
}
int main(void)
{
	sys_init();
	task_register();
	task_init();
	while (1)
	{
		run_task();
		//lv_timer_handler();
	}			    	 


}
