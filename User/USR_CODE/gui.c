#include "gui.h"
#include "sd_operate.h"
#include "usr_code.h"
GUI_STATE gui_state = GUI_OPENING;
u8 pointer_select = 0;
u8 pointer_show = 0;
u16 select_back_color = LBBLUE;
u16 reading_back_color = 0XF6F6;
void draw_select_frame()
{
    // draw select frame
    if (file_count == 0)
    {
        if (file_exist_flag == 0)
        {
            scan_sd_files();
        }
        else
        {
            LCD_Clear(WHITE);
            universal_show_str(30, 150, 200, 16, 16, "No files found!");
            return;
        }
    }
    POINT_COLOR = BLACK;
    BACK_COLOR = LIGHTBLUE;
    LCD_Color_Fill(0, 0, 240, TITLE_SPACE, LIGHTBLUE);
    universal_show_str(90, (int)TITLE_SPACE / 3, 120, TITLE_SPACE, 16, "�ļ�ѡ��");

    for (u8 i = 0; i < MAX_FILE_SHOW; i++)
    {
        if (i+pointer_show != pointer_select)
        {
            POINT_COLOR = BLACK;
            BACK_COLOR = LGRAY;
            LCD_DrawRectangle(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE);
            universal_show_str(10, TITLE_SPACE + i * SINGLE_FILE_SPACE + (int)SINGLE_FILE_SPACE / 3, 200, 16, 16, filenames[i+pointer_show]);
        }
        else
        {
            POINT_COLOR = BLACK;
            BACK_COLOR = LBBLUE;
            LCD_Color_Fill(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE, LBBLUE);
            LCD_DrawRectangle(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE);
            universal_show_str(10, TITLE_SPACE + i * SINGLE_FILE_SPACE + (int)SINGLE_FILE_SPACE / 3, 200, 16, 16, filenames[i+pointer_show]);
        }
    }
};
// һ�п�����30��Ӣ���ַ� 15������ Ҳ����˵һ��30���ֽ�
// Ҳ����˵ȫ��������״̬��  ����������600���ֽ�
u16 last_show_char_ptr = 0;
u8 reading_mode=0;
u32 scroll_time=2000;
u32 reading_time_hour=0;
u32 reading_time_min=0;
u32 reading_time_sec=0;
void draw_reading_frame()
{
    POINT_COLOR = BLACK;
    BACK_COLOR=LBBLUE;
    LCD_Color_Fill(0, 0, 240, 16, LBBLUE);
    universal_show_num(0, 0, 240, 16, 16, reading_time_hour);
    universal_show_str(16, 0, 240, 16, 16, ":");
    universal_show_num(32, 0, 240, 16, 16, reading_time_min);
    universal_show_str(48, 0, 240, 16, 16, ":");
    universal_show_num(64, 0, 240, 16, 16, reading_time_sec);
    if(reading_mode==1)
    {
        universal_show_str(96, 0, 240, 16, 16, "�Զ�����");
        universal_show_num(192, 0, 240, 16, 16, scroll_time);
        universal_show_str(224, 0, 240, 16, 16, "ms");
    }
    else
    {
        universal_show_str(96, 0, 240, 16, 16, "�ֶ���ҳ                 ");
    }
    BACK_COLOR = reading_back_color;
    last_show_char_ptr=show_for_reading(0,16, 240, 308, 16,txt_read_buffer);
};
u16 show_for_reading(u16 x, u16 y, u16 width, u16 height, u8 size, char *p)//�����ʾһ�� ���ø���
{
    u8 x0 = x;
    width += x;
    height += y;
    u16 usChar;
    u16 bytecount=0;
    while (*p != '\0') {
        if (*p <= 0x7F) { // �ж��Ƿ�ΪASCII�ַ�
            if (x > (width-size/2)) { x = x0; y += size; }
            if (y > (height-size)) break;

            LCD_ShowChar(x, y, *p, size, 0); // ��ʾASCII�ַ�
            x += size / 2;
            p++;
            bytecount++;
        } else { // ���������ַ�
            if (x > (width-size)) { x = x0; y += size; }
            if (y > (height-size)) break; // ������ʾ�����˳�

            usChar = (*p << 8) | (*(p + 1)); // ��ȡ�����ַ��������ֽ�
            LCD_ShowChar_CH(x, y, usChar, 0); 
            x += size; // �����ַ�ռ�ø���Ŀ��
            p += 2;
            bytecount+=2;
        }
    }
    return bytecount;  
}
void draw_setting_frame() {
    // draw setting frame
};