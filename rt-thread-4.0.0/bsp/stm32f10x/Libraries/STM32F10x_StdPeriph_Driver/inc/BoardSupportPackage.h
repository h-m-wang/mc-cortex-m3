/*******************************************************************************
*   All rights reserved              
*
*  This source code and any compilation or derivative thereof is the sole      
*  property of xxxx Technology Co., Ltd and is provided pursuant 
*  to a Software License Agreement.  This code is the proprietary information of      
*  xxxx and is confidential in nature.  Its use and dissemination by    
*  any party other than xxxx is strictly limited by the confidential information 
*  provisions of the Agreement referenced above.      
*
*******************************************************************************
*
* Rev   Date    Author          Comments
*      (yymmdd)
* -------------------------------------------------------------
* 001   160506  ICE WANG		Primary version 
* -------------------------------------------------------------
*
*  This source file contains the basic definition of our own board  
*
****************************************************************/


#ifndef HY_HSA_BOARDSUPPORTPACKAGE_H_
#define HY_HSA_BOARDSUPPORTPACKAGE_H_



/*---------------------------------------------------------------------------
   Project include files:
   --------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
   Defines : APB BUS Clock
   --------------------------------------------------------------------------*/
#define HYHW_APB_CLOCK				80000000L

/*******************************KEY INPUT*********************************/ 
//KEY 0 ,�͵�ƽ��Ч
#define KEY0_PORT				GPIOB
#define KEY0_PIN				GPIO_2
//KEY 1 ,�͵�ƽ��Ч
#define KEY1_PORT				GPIOB
#define KEY1_PIN				GPIO_4
//KEY 2 ,�͵�ƽ��Ч
#define KEY2_PORT				GPIOA
#define KEY2_PIN				GPIO_1
//KEY 3 ,�͵�ƽ��Ч
#define KEY3_PORT				GPIOA
#define KEY3_PIN				GPIO_4
/*******************************OUTPUT*********************************/ 
//OUT0 
#define OUT0_PORT				GPIOA
#define OUT0_PIN				GPIO_3
//OUT1 
#define OUT1_PORT				GPIOB
#define OUT1_PIN				GPIO_7
//OUT2 
#define OUT2_PORT				GPIOA
#define OUT2_PIN				GPIO_7
/***********************************************************************
GPIO C7 ���룺����������
GPIO C6 ���������IC��SPIͨѶʱ��Ƭѡ��һ·SPIͨ����·Ƭѡ��ʵ��SPIͨѶ��չ��
GPIO C5 ���룺����оƬbusy���
GPIO C4 ���룺��FPGA spiͨѶʱ�������źš�FPGA busy��1�� FPGA ready��0
GPIO C3 ���룺SD��⣬FPGA��ʼ����SD�ɹ���FPGA��0��û��SD���߳�ʼ��ʧ�ܣ��øߡ�
GPIO C2 �������FPGAͨѶʱ��spiƬѡ
GPIO C1 ����� FPGA PIN151,������
GPIO C0 ����� FPGA PIN159��������
***********************************************************************/

/*******************************OUTPUT, LED IO Define*********************************/ 
//LED 0 ,�͵�ƽ����
#define LED0_PORT				GPIOC
#define LED0_PIN				GPIO_0
//LED 1 ,�͵�ƽ����
#define LED1_PORT				GPIOC
#define LED1_PIN				GPIO_1


/*******************************TSC Define*********************************/ 
//ʱ�ӷ�Ƶ
#define TSC_CLK_DIV				SPIF_SCK_DIV_64
//SPI CS
#define TSC_CS_PORT				GPIOC
#define TSC_CS_PIN				GPIO_6
//PEN DET
#define TSC_PENDET_PORT		GPIOC
#define TSC_PENDET_PIN		GPIO_7
//����оƬbusy���
#define TSC_BUSY_PORT			GPIOC
#define TSC_BUSY_PIN			GPIO_5
/*******************************FPGA SPI Define*********************************/ 
//ʱ�ӷ�Ƶ
#define FPGA_CLK_DIV				SPIF_SCK_DIV_32

//FPGA��M3��Ӳ�������ź�
#define FPGA_SH_PORT				GPIOC
#define FPGA_SH_PIN					GPIO_4 
//SD DET
#define SD_READY_DET_PORT		GPIOC
#define SD_READY_DET_PIN		GPIO_3
//FPGA SPI CS
#define FPGA_CS_PORT				GPIOC
#define FPGA_CS_PIN					GPIO_2
/*******************************SPI flah Define*********************************/ 
//ʱ�ӷ�Ƶ
#define FLASH_CLK_DIV				SPIF_SCK_DIV_4


#endif /* HSA_BOARDSUPPORTPACKAGE_H_ */


