#include "usr_code.h"
#include "ff.h"
#include "diskio.h"
#include "lcd.h"
#include "usr_key.h"
#include "fonts.h"
void sys_init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // 设置系统中断优先级分组2
    delay_init(168);                                // 初始化延时函数
    uart_init(115200);                              // 不写这行LCD用不了 闹麻了
    LED_Init();                                     // 屁用没有 写着乐呵
    LCD_Init();                                     // LCD初始化
    usr_key_init();
    usr_sd_init();									
    // tp_dev.init();
    POINT_COLOR = RED; // 设置字体为红色
    LCD_ShowString(30, 30, 200, 16, 16, "STM32F4 EBOOK ");
    POINT_COLOR = GREEN;
    LCD_ShowString(30, 70, 200, 16, 16, "SYS INIT COMPLETE");
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
    else
    {
        POINT_COLOR = GREEN;
        LCD_ShowString(30, 90, 200, 16, 16, "SD INIT COMPLETE.");
    }
}
void LCD_ShowChar_CH(u16 x, u16 y, u16 usChar, u8 mode)
{
    uint8_t rowCount, bitCount;
    uint8_t ucBuffer[WIDTH_CH_CHAR * HEIGHT_CH_CHAR / 8]; // 字模数据缓冲区
    GetGBKCode(ucBuffer, usChar);                         // 获取 32x32 中文字符点阵数据

    u16 x0 = x;
    u8 csize = WIDTH_CH_CHAR * HEIGHT_CH_CHAR / 8; // 字符对应点阵集所占的字节数

    // 注意顺序
    for (rowCount = 0; rowCount < HEIGHT_CH_CHAR; rowCount++)
    {
        for (bitCount = 0; bitCount < WIDTH_CH_CHAR; bitCount++)
        {
            uint8_t byteIndex = (rowCount * WIDTH_CH_CHAR + bitCount) / 8;
            uint8_t bitIndex = 7 - (bitCount % 8);
            if (ucBuffer[byteIndex] & (1 << bitIndex))
            {
                LCD_Fast_DrawPoint(x + bitCount, y + rowCount, POINT_COLOR); // 绘制点
            }
            else if (mode == 0)
            {
                LCD_Fast_DrawPoint(x + bitCount, y + rowCount, BACK_COLOR); // 绘制背景
            }
        }
    }
}
//英文占1字节 汉字2字节
void universal_show_str(u16 x, u16 y, u16 width, u16 height, u8 size, char *p)
{
    u8 x0 = x;
    width += x;
    height += y;
    u16 usChar;

    while (*p != '\0') {
        if (*p <= 0x7F) { // 判断是否为ASCII字符
            if (x >= width) { x = x0; y += size; }
            if (y >= height) break;

            LCD_ShowChar(x, y, *p, size, 0); // 显示ASCII字符
            x += size / 2;
            p++;
        } else { // 处理中文字符
            if (x >= (width-size/2)) { x = x0; y += size; }
            if (y >= height) break; // 超出显示区域，退出

            usChar = (*p << 8) | (*(p + 1)); // 获取中文字符的两个字节
            LCD_ShowChar_CH(x, y, usChar, 0); 
            x += size; // 中文字符占用更多的宽度
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
        if (tp_dev.sta & TP_PRES_DOWN) // 触摸屏被按下
        {
            if (tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height)
            {
                TP_Draw_Big_Point(tp_dev.x[0], tp_dev.y[0], RED); // 画图
            }
        }
        else
            delay_ms(10);     // 没有按键按下的时候
        if (key == KEY0_PRES) // KEY0按下,则执行校准程序
        {
            LCD_Clear(WHITE); // 清屏
            TP_Adjust();      // 屏幕校准
            TP_Save_Adjdata();
        }
        i++;
        if (i % 20 == 0)
            LED0 = !LED0;
    }
}