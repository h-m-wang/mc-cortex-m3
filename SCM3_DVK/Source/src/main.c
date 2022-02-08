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
	*((volatile unsigned int*)(0x40016000)) = 0x01;  //ʹ��AHB,����ܹؼ�������HREADY������
	
  
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
	
//	/*IO ��ʼ��*/
//	hyhwSpiFlash_Init();
//	gSpiFlashID = hyhwSpiFlash_ReadID();
//	//hyhwSpiFlash_ReadUniqueID(gRdBuf);  //ע������������flash֧�ָù��ܵ�
//	/*˵���� ��hyhw_SpiFlash.h ����page_size��sector size
//					 ��boardsupportPackage.h������FLASH_CLK_DIV��ʱ�ӣ���֤spi��ʱ�Ӳ�����25Mhz
//					 hyhwSpiFlash_WritePage��д��ʱ��ע�ⳤ�Ȳ���̫�󣬲��ܿ�page
//					 hyhwSpiFlash_Write����д֮ǰ�Ὣsector�����ݶ����ٻ�д��ȥ��Ϊ��׼����һ��sector��С��ȫ��buffer������Ҫ��������Ļ�������ȥ����
//					 hyhwSpiFlash_Read�����Ȳ��ܴ���1��sector��
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
