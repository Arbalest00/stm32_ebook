#include "usr_key.h"
#include "gui.h"
#include "usr_code.h"
#include "sd_operate.h"
// ˳��PG13 PG11 PG2 PG4 PG6 PF1 PF3 PF5
u8 key_state[8] = {0};
//�������������� ��Ҫ��� ��Ҫ��� ��Ҫ���
void usr_key_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // ���� GPIO ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // ���� GPIOG ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_11 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    // ���� GPIOF ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_1 | GPIO_Pin_3;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    // ���� EXTI �ߵ� GPIO ����
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource6);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource11);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource13);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource5);

    // ���� EXTI ��
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_Init(&EXTI_InitStructure);

    // �����ж����ȼ��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}
void key_handler_up()
{
    //universal_show_str(30, 150, 200, 16, 16, "UP����");
    switch(gui_state)
    {
        case GUI_SELECT:
            if(pointer_select>0)
            {
                if(pointer_show==pointer_select)
                {
                    pointer_show--;
                }
                pointer_select--;
            }
            LCD_Clear(LGRAY);
            break;
    }
    key_state[KEY_UP] = 0;
}
void key_handler_down()
{
    //universal_show_str(30, 150, 200, 16, 16, "DOWN����");
    switch(gui_state)
    {
        case GUI_SELECT:
            if(pointer_select<file_count-1)
            {
                if(pointer_select-pointer_show==MAX_FILE_SHOW-1)
                {
                    pointer_show++;
                }
                pointer_select++;
            }
            LCD_Clear(LGRAY);
            break;
    }
    key_state[KEY_DOWN] = 0;
}
void key_handler_back()
{
    universal_show_str(30, 150, 200, 16, 16, "BACK����");
    key_state[KEY_BACK] = 0;
}
void key_handler_confirm()
{
    universal_show_str(30, 150, 200, 16, 16, "CONFIRM����");
    key_state[KEY_CONFIRM] = 0;
}
void key_handler_setting()
{
    universal_show_str(30, 150, 200, 16, 16, "SETTING����");
    key_state[KEY_SETTING] = 0;
}
void key_handler_alternative()
{
    universal_show_str(30, 150, 200, 16, 16, "ALTERNATIVE����");
    key_state[KEY_ALTERNATIVE] = 0;
}