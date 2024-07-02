#include "fonts.h"

#if GBKCODE_FLASH

#include "fatfs_flash_spi.h"

#else

#include "ff.h"

#endif

//选择使用FLASH字模还是SD卡的字模
#if GBKCODE_FLASH



/*使用FLASH字模*/
//字模GB2312_H3232配套的函数

//中文字库存储在FLASH的起始地址 ：
//GBKCODE_START_ADDRESS 在fonts.h文件定义
/**
  * @brief  获取FLASH中文显示字库数据
	* @param  pBuffer:存储字库矩阵的缓冲区
	* @param  c ： 要获取的文字
  * @retval None.
  */
int GetGBKCode_from_EXFlash( uint8_t * pBuffer, uint16_t c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
	
		static uint8_t everRead=0;
		
		/*第一次使用，初始化FLASH*/
		if(everRead == 0)
		{
			TM_FATFS_FLASH_SPI_disk_initialize();
			everRead = 1;
		}
	
	  High8bit= c >> 8;     /* 取高8位数据 */
    Low8bit= c & 0x00FF;  /* 取低8位数据 */		
	  	
		/*GB2312 公式*/
    pos = ((High8bit-0xa1)*94+Low8bit-0xa1)*WIDTH_CH_CHAR*HEIGHT_CH_CHAR/8; 
		SPI_FLASH_BufferRead(pBuffer,GBKCODE_START_ADDRESS+pos,WIDTH_CH_CHAR*HEIGHT_CH_CHAR/8); //读取字库数据  
//	  printf ( "%02x %02x %02x %02x\n", pBuffer[0],pBuffer[1],pBuffer[2],pBuffer[3]);
	
		return 0;  
     
}







#else //SD卡字模

/*使用SD字模*/

static FIL fnew;													/* file objects */
static FATFS fs;													/* Work area (file system object) for logical drives */
static FRESULT res_sd; 
static UINT br;            					/* File R/W count */

//字库文件存储位置，fonts.h中的宏：
//#define GBKCODE_FILE_NAME			"0:/Font/GB2312_H3232.FON"

/**
  * @brief  获取SD卡中文显示字库数据
	* @param  pBuffer:存储字库矩阵的缓冲区
	* @param  c ： 要获取的文字
  * @retval None.
  */
int GetGBKCode_from_sd ( uint8_t * pBuffer, uint16_t c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    High8bit= c >> 8;     /* 取高8位数据 */
    Low8bit= c & 0x00FF;  /* 取低8位数据 */
		
    pos = ((High8bit-0xa1)*94+Low8bit-0xa1)*WIDTH_CH_CHAR*HEIGHT_CH_CHAR/8;
    res_sd = f_open(&fnew , GBKCODE_FILE_NAME, FA_OPEN_EXISTING | FA_READ);
    
    if ( res_sd == FR_OK ) 
    {
        f_lseek (&fnew, pos);		//指针偏移
			
				//32*32大小的汉字 其字模 占用32*32/8个字节
        res_sd = f_read( &fnew, pBuffer, WIDTH_CH_CHAR*HEIGHT_CH_CHAR/8, &br );		 
        
        f_close(&fnew);
        
        return 0;  
    }    
    else
        return -1;    
}
#endif
/*----------------------------end of file--------------------------*/


