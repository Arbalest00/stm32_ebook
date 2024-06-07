#include "sd_operate.h"
#include "string.h"
#include "usr_code.h"
#include "gui.h"
u8 filenames[MAX_FILES][MAX_FILENAME_LENGTH]; // ���ڴ洢�ļ���
u8 file_count = 0;                            // �ļ�����
u8 file_exist_flag = 0;                       // �ļ�ɨ���־
void scan_sd_files(void)
{
    DIR dir;
    FILINFO fno;
    FRESULT res;
    memset(filenames, 0, sizeof(filenames));
    file_count = 0;
    res = f_opendir(&dir, "0:/");
    if (res == FR_OK)
    {
        while (1)
        {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0)
                break; // ����򵽴�Ŀ¼ĩβ
            if (!(fno.fattrib & AM_DIR))
            { // ����Ŀ¼���������ļ�
                strncpy(filenames[file_count], fno.fname, MAX_FILENAME_LENGTH - 1);
                file_count++;
                if (file_count >= MAX_FILES)
                    break; // �ﵽ����ļ���������
            }
        }
        f_closedir(&dir);
        if (file_count > 0)
        {
            file_exist_flag = 1;
        }
        memset(txt_read_buffer, 0, sizeof(txt_read_buffer));
    }
    /* for (u8 i = 0; i < file_count; i++)
    {
        universal_show_str(50, 10 + i * 20, 100, 10, 16, filenames[i]);
    } */
}
u8 txt_read_buffer[TXT_READ_BUFFER_SIZE];
u8 file_open_flag = 0;
u16 page_ptr = 0;
u16 page_addr[8192]; // ���֧��Լ4MB���ļ� ��n����n+1ҳ�ĵ�ַ
u32 file_ptr = 0;
FIL selected_txt_file;
UINT last_read = 0;
void txt_reset()
{
    file_open_flag = 0;
    page_ptr = 0;
    file_ptr = 0;
    memset(page_addr, 0, sizeof(page_addr));
    memset(txt_read_buffer, 0, sizeof(txt_read_buffer));
    f_close(&selected_txt_file);
}
UINT read_selected_txt()
{
    FRESULT res;
    UINT bytes_read;
    if (file_open_flag == 0)
    {
        res = f_open(&selected_txt_file, filenames[pointer_select], FA_READ);
        if (res != FR_OK)
        {
            universal_show_str(30, 130, 200, 16, 16, filenames[pointer_select]);
            universal_show_str(30, 150, 200, 16, 16, "���ļ�ʧ��");
            while (1)
                ;
        }
        file_open_flag = 1;
    }
    res = f_read(&selected_txt_file, txt_read_buffer, TXT_READ_BUFFER_SIZE, &bytes_read);
    if (res != FR_OK)
    {
        universal_show_str(30, 150, 200, 16, 16, "�ļ���ȡ����");
        while (1)
            ;
    }
    last_read = bytes_read;
    return bytes_read;
}

void load_new_page()
{
    if (last_read == TXT_READ_BUFFER_SIZE)
    {
        FRESULT res;
        memset(txt_read_buffer, 0, sizeof(txt_read_buffer));
        if (page_addr[page_ptr] == 0) // ������� �½���ַ��
        {
            if (page_ptr == 0)
                page_addr[page_ptr] = last_show_char_ptr;
            else
                page_addr[page_ptr] = page_addr[page_ptr - 1] + last_show_char_ptr;
            res = f_lseek(&selected_txt_file, page_addr[page_ptr]);
            read_selected_txt();
        }
        else // ������� ֱ�Ӳ��
        {
            res = f_lseek(&selected_txt_file, page_addr[page_ptr]);
            read_selected_txt();
        }
        if (res != FR_OK)
        {
            universal_show_str(30, 150, 200, 16, 16, "�ļ���ȡ����");
            while (1)
                ;
        }
        page_ptr++;
    }
}
void load_last_page()
{
    FRESULT res;
    memset(txt_read_buffer, 0, sizeof(txt_read_buffer));
    if (page_ptr > 1)
    {
        res = f_lseek(&selected_txt_file, page_addr[page_ptr - 2]);
        page_ptr--;
    }
    else
    {
        page_ptr = 0;
        res = f_lseek(&selected_txt_file, 0);
    }
    file_ptr = page_addr[page_ptr];
    read_selected_txt();
}