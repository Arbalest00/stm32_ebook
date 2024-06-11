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
//ʱ�ֵ������ഺ��
void task_register()
{
	//add_task(gui_draw_frame_task,1000,1);//�����ٶȼǵ��������ϵͳ�жϱ������˶���
	add_task(key_scan_task,20,1);
	add_task(time_count_task,(u32)(50/6),1);//��֪�� ����ʱ��Դ
	//add_task(reading_auto_scroll_task,(u32)(scroll_time/5),1);
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
