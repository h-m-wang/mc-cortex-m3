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
*  This source file contains the basic definition about uart   
*
****************************************************************/


/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/
#include "hyTypes.h"
#include "BoardSupportPackage.h"
#include <string.h>

/*------------------------------------------------------------------------------
  Project include files:
------------------------------------------------------------------------------*/
#include "hyhw_SpiFlash.h"
#include "hyhwSpi.h"
#include "hyhwDma.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
// 注意 READ的时候用到了DMA，读写长度务必是4的倍数，否则可能会导致buf溢出。
void hyhwSpiFlash_Read( UInt8* str,UInt32 addr, UInt32 len )
{
    hyhwSpiFlash_ReadBuffer(str, addr, len);
}
UInt8 flashBufP[FLASH_SECTOR_SIZE];
void hyhwSpiFlash_Write( UInt8* str, UInt32 addr, UInt32 len )
{
	UInt32 totalWriteCnt;
	UInt32 flashSectorAddr;
	UInt32 flashWriteOffset;
	UInt32 subWriteCnt;
	
	UInt8 i;
	totalWriteCnt = 0;

	while( totalWriteCnt < len )
	{
		flashSectorAddr = addr / FLASH_SECTOR_SIZE;
		flashSectorAddr *= FLASH_SECTOR_SIZE;
		flashWriteOffset = addr % FLASH_SECTOR_SIZE;
		subWriteCnt = (len-totalWriteCnt) < (FLASH_SECTOR_SIZE - flashWriteOffset)?(len-totalWriteCnt):(FLASH_SECTOR_SIZE - flashWriteOffset);

		hyhwSpiFlash_ReadBuffer(flashBufP, flashSectorAddr, FLASH_SECTOR_SIZE);	
		memcpy(flashBufP+flashWriteOffset,str+totalWriteCnt, subWriteCnt);
		hyhwSpiFlash_EraseSector(flashSectorAddr);
		for(i=0;i<FLASH_PAGE_NUM_PER_SECTOR;i++)
		{
			hyhwSpiFlash_WritePage(flashBufP+(FLASH_PAGE_SIZE*i), (flashSectorAddr+FLASH_PAGE_SIZE*i), FLASH_PAGE_SIZE);
		}
		totalWriteCnt += subWriteCnt;
		addr += subWriteCnt;
	}

	return;	
}




/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void hyhwSpiFlash_Init(void)
{
		U32 i;
		SPI_FLASH->SPCR  |= SPIF_RESET;
		for(i=0;i<1000;i++);
		SPI_FLASH->SPCR  &= ~SPIF_RESET;
		SPI_FLASH->SPCR = 
										FLASH_CLK_DIV | 	// 分频
                    SPIF_LSB_EN;			//小端模式    
		hyhwDMAC_Init();
	
}

/**
  * @brief  Erases the specified FLASH sector.
  * @param  SectorAddr: address of the sector to erase.
  * @retval None
  */
void hyhwSpiFlash_EraseSector(UInt32 SectorAddr)
{
  U8 Byte1,Byte2,Byte3;
	/*!< Send write enable instruction */
  hyhwSpiFlash_WriteEnable();

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  //sFLASH_CS_LOW();
  /*!< Send Sector Erase instruction */
	SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; //
	Byte1 = 0xFF&(SectorAddr>>16);
	Byte2 = 0xFF&(SectorAddr>>8);
	Byte3 = 0xFF&(SectorAddr);
	SPI_FLASH->PHASE_DATA[0] = (sFLASH_CMD_SE)|(Byte1<<8)|(Byte2<<16)|(Byte3<<24);
	
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT1|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));
	 
  /*!< Deselect the FLASH: Chip Select high */
  //sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  hyhwSpiFlash_WaitForWriteEnd();
	
	hyhwSpiFlash_WriteDisable();
}


/**
  * @brief  Writes more than one byte but less than one page to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "sFLASH_PAGESIZE" value.
  * @retval None
  */
void hyhwSpiFlash_WritePage(UInt8* pBuffer, UInt32 WriteAddr, UInt16 NumByteToWrite)
{
	U8 Byte1,Byte2,Byte3;
	// add by ryan
	if( NumByteToWrite == 0)
	{
		return;
	}
  /*!< Enable the write access to the FLASH */
  hyhwSpiFlash_WriteEnable();

  /*!< Select the FLASH: Chip Select low */
  //sFLASH_CS_LOW();
  SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; 
	Byte1 = 0xFF&(WriteAddr>>16);
	Byte2 = 0xFF&(WriteAddr>>8);
	Byte3 = 0xFF&(WriteAddr);
	SPI_FLASH->PHASE_DATA[0] = (sFLASH_CMD_WRITE)|(Byte1<<8)|(Byte2<<16)|(Byte3<<24);

	SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|(NumByteToWrite)<<8; //+2 ??crc,???????
	
	hyhwDma_Config(DMA_CHANNEL2,(U32)pBuffer,(U32)(&(SPI_FLASH->PHASE_DATA[1])),NumByteToWrite,DMA_SI,DMA_DNI,DMA_WIDTH_8_BIT,DMA_WIDTH_32_BIT,DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL);
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPIF_USE_DMA_EN|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));

  /*!< Deselect the FLASH: Chip Select high */
  //sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  hyhwSpiFlash_WaitForWriteEnd();
	
	hyhwSpiFlash_WriteDisable();
}


/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void hyhwSpiFlash_ReadBuffer(UInt8* pBuffer, UInt32 ReadAddr, UInt16 NumByteToRead)
{
  U8 Byte1,Byte2,Byte3; 
	if(NumByteToRead > FLASH_SECTOR_SIZE)
		return;
	
	if(NumByteToRead < 4096)
	{
		SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; //???? 2??
		Byte1 = 0xFF&(ReadAddr>>16);
		Byte2 = 0xFF&(ReadAddr>>8);
		Byte3 = 0xFF&(ReadAddr);
		SPI_FLASH->PHASE_DATA[0] = (sFLASH_CMD_READ)|(Byte1<<8)|(Byte2<<16)|(Byte3<<24);
		SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_RX | SPIF_MODE_SINGLE|(NumByteToRead&0xfff)<<8; //最多只能配置小于4096个
	
		hyhwDma_Config(DMA_CHANNEL1,(U32)(&(SPI_FLASH->PHASE_DATA[1])),(U32)pBuffer,NumByteToRead,DMA_SNI,DMA_DI,DMA_WIDTH_32_BIT,DMA_WIDTH_8_BIT,DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL);
	
		SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPI_LE_MODE|SPIF_USE_DMA_EN;
		while(!(SPI_FLASH->SPCR & SPIF_DONE));
	}
	else
	{
		SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; //???? 2??
		Byte1 = 0xFF&(ReadAddr>>16);
		Byte2 = 0xFF&(ReadAddr>>8);
		Byte3 = 0xFF&(ReadAddr);
		SPI_FLASH->PHASE_DATA[0] = (sFLASH_CMD_READ)|(Byte1<<8)|(Byte2<<16)|(Byte3<<24);
		SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_RX | SPIF_MODE_SINGLE|(2048)<<8; //最多只能配置小于4096个
	
		hyhwDma_Config(DMA_CHANNEL1,(U32)(&(SPI_FLASH->PHASE_DATA[1])),(U32)pBuffer,2048,DMA_SNI,DMA_DI,DMA_WIDTH_32_BIT,DMA_WIDTH_8_BIT,DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL);
	
		SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPI_LE_MODE|SPIF_USE_DMA_EN;
		while(!(SPI_FLASH->SPCR & SPIF_DONE));
		//读另一半
		SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; 
		ReadAddr = ReadAddr +2048;
		Byte1 = 0xFF&(ReadAddr>>16);
		Byte2 = 0xFF&(ReadAddr>>8);
		Byte3 = 0xFF&(ReadAddr);
		SPI_FLASH->PHASE_DATA[0] = (sFLASH_CMD_READ)|(Byte1<<8)|(Byte2<<16)|(Byte3<<24);
		SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_RX | SPIF_MODE_SINGLE|(NumByteToRead-2048)<<8; //最多只能配置小于4096个
	
		hyhwDma_Config(DMA_CHANNEL1,(U32)(&(SPI_FLASH->PHASE_DATA[1])),(U32)(pBuffer+2048),(NumByteToRead-2048),DMA_SNI,DMA_DI,DMA_WIDTH_32_BIT,DMA_WIDTH_8_BIT,DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL);
	
		SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPI_LE_MODE|SPIF_USE_DMA_EN;
		while(!(SPI_FLASH->SPCR & SPIF_DONE));
		
	}
	
}

/**
  * @brief  Reads FLASH identification.
  * @param  None
  * @retval FLASH identification
  */
UInt32 hyhwSpiFlash_ReadID(void)
{
  UInt32 id;
	SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|1<<8; //
	SPI_FLASH->PHASE_DATA[0] = sFLASH_CMD_RDID;
	SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_RX | SPIF_MODE_SINGLE|3<<8; //???? 4??
	
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));
	
	id = SPI_FLASH->PHASE_DATA[1];
	return id;
}

/**
  * @brief  Reads FLASH unique identification.
  * @param  None
  * @retval FLASH identification 16bytes
  */
void hyhwSpiFlash_ReadUniqueID(unsigned char *pUID)
{
  UInt32 id;
	SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|4<<8; //
	SPI_FLASH->PHASE_DATA[0] = sFLASH_CMD_RDUID|0xFFFFFF00;
	SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|1<<8; //
	SPI_FLASH->PHASE_DATA[1] = 0xFF;
	
	SPI_FLASH->PHASE_CTRL[2] = SPIF_PHASE_ACTION_RX | SPIF_MODE_SINGLE|(16)<<8; //最多只能配置小于4096个
	
	hyhwDma_Config(DMA_CHANNEL1,(U32)(&(SPI_FLASH->PHASE_DATA[2])),(U32)pUID,16,DMA_SNI,DMA_DI,DMA_WIDTH_32_BIT,DMA_WIDTH_8_BIT,DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL);
	
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT3|SPI_LE_MODE|SPIF_USE_DMA_EN;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));
	return ;
}

/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void hyhwSpiFlash_WriteEnable(void)
{
  /*!< Select the FLASH: Chip Select low */
  //sFLASH_CS_LOW();

  /*!< Send "Write Enable" instruction */
  SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|1<<8; //
	SPI_FLASH->PHASE_DATA[0] = sFLASH_CMD_WREN;
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT1|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));
  /*!< Deselect the FLASH: Chip Select high */
  //sFLASH_CS_HIGH();
}
/**
  * @brief  Disable the write access to the FLASH.
  * @param  None
  * @retval None
  */
void hyhwSpiFlash_WriteDisable(void)
{
  /*!< Select the FLASH: Chip Select low */
  //sFLASH_CS_LOW();

  /*!< Send "Write Enable" instruction */
  SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|1<<8; //
	SPI_FLASH->PHASE_DATA[0] = sFLASH_CMD_WRDIS;
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT1|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));
  /*!< Deselect the FLASH: Chip Select high */
  //sFLASH_CS_HIGH();
}
/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void hyhwSpiFlash_WaitForWriteEnd(void)
{

  /*!< Select the FLASH: Chip Select low */
  //sFLASH_CS_LOW();

  /*!< Send "Read Status Register" instruction */
  SPI_FLASH->PHASE_CTRL[0] = SPIF_PHASE_ACTION_TX | SPIF_MODE_SINGLE|1<<8; //
	SPI_FLASH->PHASE_DATA[0] = sFLASH_CMD_RDSR;
	SPI_FLASH->PHASE_CTRL[1] = SPIF_PHASE_ACTION_POLL | SPIF_MODE_SINGLE; //???? 4??
	SPI_FLASH->PHASE_DATA[1] = (0x00<<24)|(sFLASH_WIP_FLAG<<16)|(0<<8);
	SPI_FLASH->SPCR = FLASH_CLK_DIV | SPIF_STSRT | SPIF_PHASE_CNT2|SPI_LE_MODE;
	while(!(SPI_FLASH->SPCR & SPIF_DONE));

  /*!< Deselect the FLASH: Chip Select high */
  //sFLASH_CS_HIGH();
}



