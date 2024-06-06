#include "gui.h"
#include "sd_operate.h"
#include "usr_code.h"
#define TITLE_SPACE 40
#define FILE_SPACE 280
#define MAX_FILE_SHOW 5
#define SINGLE_FILE_SPACE FILE_SPACE / MAX_FILE_SHOW
GUI_STATE gui_state = GUI_READING;
u8 pointer_select = 4;
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
    universal_show_str(60, (int)TITLE_SPACE / 3, 120, TITLE_SPACE, 16, "�ļ�ѡ��");

    for (u8 i = pointer_show; i < MAX_FILE_SHOW; i++)
    {
        if (i != pointer_select)
        {
            POINT_COLOR = BLACK;
            BACK_COLOR = LGRAY;
            LCD_DrawRectangle(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE);
            universal_show_str(10, TITLE_SPACE + i * SINGLE_FILE_SPACE + (int)SINGLE_FILE_SPACE / 3, 200, 16, 16, filenames[i]);
        }
        else
        {
            POINT_COLOR = BLACK;
            BACK_COLOR = LBBLUE;
            LCD_Color_Fill(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE, LBBLUE);
            LCD_DrawRectangle(0, TITLE_SPACE + i * SINGLE_FILE_SPACE, 240, TITLE_SPACE + (i + 1) * SINGLE_FILE_SPACE);
            universal_show_str(10, TITLE_SPACE + i * SINGLE_FILE_SPACE + (int)SINGLE_FILE_SPACE / 3, 200, 16, 16, filenames[i]);
        }
    }
};
// һ�п�����30��Ӣ���ַ� 15������ Ҳ����˵һ��30���ֽ�
// Ҳ����˵ȫ��������״̬��  ����������600���ֽ�
u16 last_show_char_ptr = 0;
void draw_reading_frame()
{
    POINT_COLOR = BLACK;
    BACK_COLOR = reading_back_color;
    universal_show_str(0, 0, 240, 16, 16, "test test test test test");
    last_show_char_ptr=show_for_reading(0, 16, 240, 304, 16,txt_read_buffer);
};
u16 show_for_reading(u16 x, u16 y, u16 width, u16 height, u8 size, char *p)//����ƫ��ֵ
{
    u8 x0 = x;
    width += x;
    height += y;
    u16 usChar;
    u16 bytecount=0;
    while (*p != '\0') {
        if (*p <= 0x7F) { // �ж��Ƿ�ΪASCII�ַ�
            if (x >= width) { x = x0; y += size; }
            if (y >= height) break;

            LCD_ShowChar(x, y, *p, size, 0); // ��ʾASCII�ַ�
            x += size / 2;
            p++;
            bytecount++;
        } else { // ���������ַ�
            if (x >= (width-size/2)) { x = x0; y += size; }
            if (y >= height) break; // ������ʾ�����˳�

            usChar = (*p << 8) | (*(p + 1)); // ��ȡ�����ַ��������ֽ�
            LCD_ShowChar_CH(x, y, usChar, 0); 
            x += size; // �����ַ�ռ�ø���Ŀ��
            p += 2;
            bytecount+=2;
        }
    }
    return bytecount;  
}
void change_page()
{
}
void draw_setting_frame() {
    // draw setting frame
};