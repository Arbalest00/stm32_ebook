#include "usr_code.h"
#include "ff.h"
#include "diskio.h"
#include "lcd.h"
#include "usr_key.h"
#include "fonts.h"
#include "gui.h"
#include "sd_operate.h"
void sys_init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // ����ϵͳ�ж����ȼ�����2
    delay_init(168);                                // ��ʼ����ʱ����
    uart_init(115200);                              // ��д����LCD�ò��� ������
    LED_Init();                                     // ƨ��û�� д���ֺ�
    LCD_Init();                                     // LCD��ʼ��
    POINT_COLOR = RED;
    LCD_ShowString(50, 10, 200, 16, 16, "STM32F4 EBOOK ");
    POINT_COLOR = BLUE;
    LCD_ShowString(50, 30, 200, 16, 16, "SYS INIT COMPLETE");
    usr_key_init();
    LCD_ShowString(50, 50, 200, 16, 16, "KEY INIT COMPLETE");
    usr_sd_init();									
    LCD_ShowString(50, 70, 200, 16, 16, "SD INIT COMPLETE");
    scan_sd_files();
    LCD_ShowString(50, 90, 200, 16, 16, "FILE SCAN COMPLETE");
    LCD_ShowString(50, 110, 200, 16, 16, "FIND FILES: ");
    LCD_ShowNum(50 + 16 * 12, 110, file_count, 3, 16);
    LCD_ShowString(50, 130, 200, 16, 16, "THREAD START");
    // tp_dev.init();
    gui_state = GUI_SELECT;
    delay_ms(2000);
    LCD_Clear(LGRAY);
}
void usr_sd_init(void)
{
    FATFS fs;
    FATFS fl;
    FRESULT res_sd;

    // Mount the file system
    res_sd = f_mount(&fs, "0:", 1);
    if (res_sd == FR_NO_FILESYSTEM)
    {
        // Format the filesystem
        res_sd = f_mkfs("0:", 0, 0);
        if (res_sd == FR_OK)
        {
            // Unmount after formatting
            res_sd = f_mount(NULL, "0:", 1);
            // Remount the filesystem
            res_sd = f_mount(&fs, "0:", 1);
        }
        else
        {
            POINT_COLOR = RED;
            LCD_ShowString(30, 90, 200, 16, 16, "Formatting failed.");
            while (1)
                ;
        }
    }
    else if (res_sd != FR_OK)
    {
        POINT_COLOR = RED;
        LCD_ShowString(30, 90, 200, 16, 16, "Failed to mount filesystem.");
        while (1)
            ;
    }

}
void LCD_ShowChar_CH(u16 x, u16 y, u16 usChar, u8 mode)
{
    uint8_t rowCount, bitCount;
    uint8_t ucBuffer[WIDTH_CH_CHAR * HEIGHT_CH_CHAR / 8]; // ��ģ���ݻ�����
    GetGBKCode(ucBuffer, usChar);                         // ��ȡ 32x32 �����ַ���������

    u16 x0 = x;
    u8 csize = WIDTH_CH_CHAR * HEIGHT_CH_CHAR / 8; // �ַ���Ӧ������ռ���ֽ���

    // ע��˳��
    for (rowCount = 0; rowCount < HEIGHT_CH_CHAR; rowCount++)
    {
        for (bitCount = 0; bitCount < WIDTH_CH_CHAR; bitCount++)
        {
            uint8_t byteIndex = (rowCount * WIDTH_CH_CHAR + bitCount) / 8;
            uint8_t bitIndex = 7 - (bitCount % 8);
            if (ucBuffer[byteIndex] & (1 << bitIndex))
            {
                LCD_Fast_DrawPoint(x + bitCount, y + rowCount, POINT_COLOR); // ���Ƶ�
            }
            else if (mode == 0)
            {
                LCD_Fast_DrawPoint(x + bitCount, y + rowCount, BACK_COLOR); // ���Ʊ���
            }
        }
    }
}
//Ӣ��ռ1�ֽ� ����2�ֽ�
void universal_show_str(u16 x, u16 y, u16 width, u16 height, u8 size, char *p)
{
    u8 x0 = x;
    width += x;
    height += y;
    u16 usChar;

    while (*p != '\0') {
        if (*p <= 0x7F) { // �ж��Ƿ�ΪASCII�ַ�
            if (x >= width) { x = x0; y += size; }
            if (y >= height) break;

            LCD_ShowChar(x, y, *p, size, 0); // ��ʾASCII�ַ�
            x += size / 2;
            p++;
        } else { // ���������ַ�
            if (x >= (width-size/2)) { x = x0; y += size; }
            if (y >= height) break; // ������ʾ�����˳�

            usChar = (*p << 8) | (*(p + 1)); // ��ȡ�����ַ��������ֽ�
            LCD_ShowChar_CH(x, y, usChar, 0); 
            x += size; // �����ַ�ռ�ø���Ŀ��
            p += 2;
        }
    }  
}
void rtp_test(void)
{
    u8 key;
    u8 i = 0;
    while (1)
    {
        key = KEY_Scan(0);
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN) // ������������
        {
            if (tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height)
            {
                TP_Draw_Big_Point(tp_dev.x[0], tp_dev.y[0], RED); // ��ͼ
            }
        }
        else
            delay_ms(10);     // û�а������µ�ʱ��
        if (key == KEY0_PRES) // KEY0����,��ִ��У׼����
        {
            LCD_Clear(WHITE); // ����
            TP_Adjust();      // ��ĻУ׼
            TP_Save_Adjdata();
        }
        i++;
        if (i % 20 == 0)
            LED0 = !LED0;
    }
}