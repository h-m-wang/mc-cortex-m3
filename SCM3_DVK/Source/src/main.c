#include "SCM3.h"
#include <stdio.h>

#include "BoardSupportPackage.h"
#include "hyhwUart.h"
#include "hyhwTimer.h"
#include "hyhwGpio.h"
#include "hyhwDma.h"
#include "hyhwSpi.h"
#include "hyhwWatchdog.h"
#include "hyhw_SpiFlash.h"

unsigned char gRdBuf[5*1024],gWrBuf[1024*5];
unsigned int gRdAhb[100];
extern U32 x,y;
//const U8 a[32*1024];
unsigned char keytest;
U32 gSpiFlashID;

U32 *ptr;
U32 readfromahb;
int main(void)
{
  uint32_t i, j;
	*((volatile unsigned int*)(0x40016000)) = 0x01;  //使能AHB,这个很关键，否则HREADY不能用
	
  
	hyhwGpio_SetOut(GPIOA,GPIO_0);
	
	while(1){
	hyhwGpio_SetHigh(GPIOA,GPIO_0);
	for(i=10000;i>0;i--) 
     for(j=1000;j>0;j--)
       {
            __NOP();
				 }
	
	hyhwGpio_SetLow(GPIOA,GPIO_0);
	for(i=10000;i>0;i--) 
     for(j=1000;j>0;j--)
       {
            __NOP();
				 }
	}
	
	//hyhwTimerA_InitTimer1(1000*1000,INTMODE_WRAPPING);
	//NVIC_EnableIRQ(TIMERA_IRQn);
//	ptr = (U32*)0xa0000000;
//	for(i=0;i<1000;i++)
//	{
//		*ptr++ = i;
//	}
//	while(1);
	
//	/*IO 初始化*/
//	hyhwSpiFlash_Init();
//	gSpiFlashID = hyhwSpiFlash_ReadID();
//	//hyhwSpiFlash_ReadUniqueID(gRdBuf);  //注明：不是所有flash支持该功能的
//	/*说明： 在hyhw_SpiFlash.h 设置page_size和sector size
//					 在boardsupportPackage.h中设置FLASH_CLK_DIV的时钟，保证spi的时钟不超过25Mhz
//					 hyhwSpiFlash_WritePage中写的时候注意长度不能太大，不能跨page
//					 hyhwSpiFlash_Write，在写之前会将sector的内容读出再回写回去。为此准备了一个sector大小的全局buffer，不需要这个函数的话，可以去掉。
//					 hyhwSpiFlash_Read，长度不能大于1个sector。
//	*/					
//	hyhwSpiFlash_Read( gRdBuf,0x0, 512);
//	for(i=0;i<1024;i++)
//	{
//		gRdBuf[i] = 0;

//	}
//	for(i=0;i<5*1024;i++)
//	{
//		gWrBuf[i] = i;
//	}
//	hyhwSpiFlash_EraseSector(82*FLASH_SECTOR_SIZE);
//	hyhwSpiFlash_WritePage(gWrBuf, 82*FLASH_SECTOR_SIZE, 256);
//	hyhwSpiFlash_Read( gRdBuf,82*FLASH_SECTOR_SIZE, 512);
//	hyhwSpiFlash_Write( gWrBuf, 82*FLASH_SECTOR_SIZE+5,5*1024);
//	hyhwSpiFlash_Read( gRdBuf,82*FLASH_SECTOR_SIZE, 4*1024);
//	hyhwSpiFlash_Read( gRdBuf,82*FLASH_SECTOR_SIZE+4096, 1024);
//	while(1);
}



/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
