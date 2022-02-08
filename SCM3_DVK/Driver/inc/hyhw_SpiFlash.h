#ifndef HY_SPIFLASH_H_
#define HY_SPIFLASH_H_

#include "hyTypes.h"

#ifdef __cplusplus
 extern "C" {
#endif

	 


#define FLASH_PAGE_SIZE		0x100
#define FLASH_SECTOR_SIZE	0x1000
#define FLASH_PAGE_NUM_PER_SECTOR  (FLASH_SECTOR_SIZE/FLASH_PAGE_SIZE)



/* M25P SPI Flash supported commands */  
#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_WRDIS          0x04  /* Write Disable instruction */	 
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */
#define sFLASH_CMD_RDUID          0x4B  /* Read unique identification */	 
#define sFLASH_CMD_SE             0x20  /* Sector Erase instruction */
#define sFLASH_CMD_BE             0xD8  /* Bulk Erase instruction */



#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5




/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
//#define sFLASH_CS_LOW()       GPIO_ResetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)
/* Deselect sFLASH: Chip Select pin high */
//#define sFLASH_CS_HIGH()      GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)   

/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
//#define sFLASH_WP_LOW()       GPIO_ResetBits(FLASH_WP_PORT, FLASH_WP_PIN)
/* Deselect sFLASH: Chip Select pin high */
//#define sFLASH_WP_HIGH()      GPIO_SetBits(FLASH_WP_PORT, FLASH_WP_PIN)   



/* High layer functions  */

void hyhwSpiFlash_EraseSector(UInt32 SectorAddr);

void hyhwSpiFlash_WritePage(UInt8* pBuffer, UInt32 WriteAddr, UInt16 NumByteToWrite);
void hyhwSpiFlash_WriteBuffer(UInt8* pBuffer, UInt32 WriteAddr, UInt16 NumByteToWrite);
void hyhwSpiFlash_ReadBuffer(UInt8* pBuffer, UInt32 ReadAddr, UInt16 NumByteToRead);
void hyhwSpiFlash_Init(void);
UInt32 hyhwSpiFlash_ReadID(void);
void hyhwSpiFlash_ReadUniqueID(unsigned char *pUID);

/* Low layer functions */

void hyhwSpiFlash_WriteEnable(void);
void hyhwSpiFlash_WriteDisable(void);
void hyhwSpiFlash_WaitForWriteEnd(void);

void hyhwSpiFlash_Read( UInt8* str,UInt32 addr, UInt32 len );
void hyhwSpiFlash_Write( UInt8* str, UInt32 addr, UInt32 len );

#ifdef __cplusplus
}
#endif



#endif

