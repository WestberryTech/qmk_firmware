/*
    Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include "eeprom_wb32.h"
/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
 ******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// __ASM void FLASH_OP_EXEC_RAM(uint32_t code, uint32_t fmc_base)
// {
//   STR   R0, [R1, #0x00]   // FMC->CON = 0x00800080; # WR=1
//   NOP
// LB_CK
//   LDR   R0, [R1, #0x00]
//   LSLS  R0, R0, #24
//   BMI   LB_CK             // while(FMC->CON & FMC_CON_WR);
//   BX    LR
// }
/* Do not change if it is not necessary */
// #define FLASH_OP_RAM_CODE {0xBF006008, 0x06006808, 0x4770D4FC}

static const uint32_t pre_op_code[] = {0x4FF0E92D, 0x21034832, 0x210C6281, 0xF8DF62C1, 0x2100C0C4, 0x1000F8CC, 0xF44F4608, 0x1C40767A, 0xDBFC42B0, 0xF8CC2201, 0x20002000, 0x42B01C40, 0x4829DBFC, 0xF0436803, 0x60030380, 0x302C4826, 0xF4436803, 0x60036320, 0x46104691, 0x323C4A22, 0x468A6010, 0x49214608, 0x48216008, 0x0340F8D0, 0x25004F1E, 0x5107F3C0, 0x3BFFF04F, 0x22001F3F, 0x4610465C, 0xEA5F683B, 0xD10678C0, 0xD10142A3, 0xE0002401, 0x44222400, 0x1C40461C, 0xDBF12814, 0xD91B2A02, 0xD9012910, 0xE0003910, 0x480D2100, 0x68021F00, 0x627FF022, 0x5201EA42, 0xF8CC6002, 0x2000A000, 0x42B01C40, 0xF8CCDBFC, 0x20009000, 0x42B01C40, 0x1C6DDBFC, 0xDBD02D05, 0x8FF0E8BD, 0x40010000, 0x40010438, 0x40010C20, 0x4000B804, 0x1FFFF000};
#define PRE_OP() ((void (*)(void))((unsigned int)(pre_op_code) | 0x01))()
/* Functions -----------------------------------------------------------------*/

uint8_t DataBuf[FEE_PAGE_SIZE];
/*****************************************************************************
 *  Delete Flash Space used for user Data, deletes the whole space between
 *  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
 ******************************************************************************/
uint16_t EEPROM_Init(void) {
    /* Unlocks write to ANCTL registers */
    PWR->ANAKEY1 = 0x03;
    PWR->ANAKEY2 = 0x0C;
    /* Enables or disables the Internal 48MHz oscillator (FHSI). */
    ANCTL->FHSIENR = (uint32_t)ENABLE;
    /* Locks write to ANCTL registers */
    PWR->ANAKEY1 = 0x00;
    PWR->ANAKEY2 = 0x00;

    return FEE_DENSITY_BYTES;
}

/*****************************************************************************
 *  Execute FLASH operation.
 ******************************************************************************/

static uint32_t FLASH_OP_EXEC(uint32_t op) {
    // volatile uint32_t flash_op_ram_code[] = FLASH_OP_RAM_CODE;

    /* Start FLASH operation and wait for a FLASH operation to complete  */
    RCC->PCLKENR = 0x01;
    FMC->CON     = 0x7F5F0D40 | (op & 0x1F); /* [14:8]=0x0D, WREN=1, [4:0]=op */
    FMC->KEY     = 0x5188DA08;
    FMC->KEY     = 0x12586590;
    // ((void(*)(uint32_t, uint32_t))((unsigned int)(flash_op_ram_code) | 0x01))(0x00800080, FMC_BASE);
    FMC->CON = 0x00800080;
    while (FMC->CON & FMC_CON_WR)
        ;

    RCC->PCLKENR = 0x00;
    /* Clear WREN and OP[4:0] bits */
    FMC->CON = 0x005F0000;

    if (FMC->STAT & FMC_STAT_ERR)
        return 1; /* Any error occur */
    else
        return 0; /* FLASH operation complete */
}

/*****************************************************************************
 *  Programs the data to the specified page address.
 ******************************************************************************/
uint32_t FMC_ProgramPage(uint32_t Page_Address) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    PRE_OP();
    FMC->ADDR = Page_Address;
    ret       = FLASH_OP_EXEC(0x0C);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Erase a specified FLASH page.
 ******************************************************************************/
uint32_t FMC_ErasePage(uint32_t Page_Address) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    PRE_OP();
    FMC->ADDR = Page_Address;
    ret       = FLASH_OP_EXEC(0x08);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Clear page latches.
 ******************************************************************************/
uint32_t FMC_ClearPageLatch(void) {
    uint32_t ret;
    int      state;

    state = __get_PRIMASK();
    __disable_irq();
    ret = FLASH_OP_EXEC(0x04);
    if (!state) {
        __enable_irq();
    }

    return ret;
}

/*****************************************************************************
 *  Erase the whole reserved Flash Space used for user Data.
 ******************************************************************************/
void EEPROM_Erase(void) {
    int page_num = 0;

    /* delete all pages from specified start page to the last page.*/
    do {
        FMC_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
        page_num++;
    } while (page_num < FEE_DENSITY_PAGES);
}

/*****************************************************************************
 *  Read flash data.
 ******************************************************************************/
void WBFLASH_Read(uint32_t ReadAddr, uint8_t* pBuffer, uint16_t NumToRead) {
    uint16_t i;

    for (i = 0; i < NumToRead; i++) {
        pBuffer[i] = (__IO uint8_t)(*(__IO uint8_t *)ReadAddr);
        ReadAddr++;
    }
}
/*****************************************************************************
 *  Writes once data byte to flash on specified address. If a byte is already
 *  written, the whole page must be copied to a buffer, the byte changed and
 *  the manipulated buffer written after PageErase.
 *******************************************************************************/
uint8_t  wb_flash_buffer[FEE_PAGE_SIZE] = {0};
uint16_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte) {
    FLASH_Status FlashStatus = FLASH_COMPLETE;
    uint32_t     raw_address;
    uint32_t     pagpos;
    uint16_t     pagoff;
    uint32_t     offaddr;
    /* exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages).*/
    if (Address > FEE_DENSITY_BYTES) {
        return 0;
    }

    raw_address = Address + FEE_PAGE_BASE_ADDRESS;
    offaddr     = raw_address - WB32_FLASH_BASE;
    /* calculate which page is affected (Pagenum1/Pagenum2...PagenumN).*/
    pagpos = offaddr / FEE_PAGE_SIZE;
    pagoff = offaddr % FEE_PAGE_SIZE;
    WBFLASH_Read(pagpos * FEE_PAGE_SIZE + WB32_FLASH_BASE, wb_flash_buffer, FEE_PAGE_SIZE);
    wb_flash_buffer[pagoff] = DataByte;
    /* Erase the specified FLASH page */
    FMC_ErasePage(pagpos * FEE_PAGE_SIZE + WB32_FLASH_BASE);
    /* Clear page latch */
    FMC_ClearPageLatch();

    for (int i = 0; i < (FEE_PAGE_SIZE >> 2); i++) {
        FMC->BUF[i] = (*((volatile uint32_t *)(wb_flash_buffer + i * 4)));
    }
    /* Program data in page latch to the specified FLASH page */
    FMC_ProgramPage(pagpos * FEE_PAGE_SIZE + WB32_FLASH_BASE);

    return FlashStatus;
}
/*****************************************************************************
 *  Read once data byte from a specified address.
 *******************************************************************************/
uint8_t EEPROM_ReadDataByte(uint16_t Address) {
    uint8_t DataByte = 0x00;

    // Get Byte from specified address
    DataByte = (*(__IO uint8_t *)(FEE_PAGE_BASE_ADDRESS + (Address)));

    return DataByte;
}

/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
uint8_t eeprom_read_byte(const uint8_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p);
}

void eeprom_write_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, Value);
}

void eeprom_update_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, Value);
}

uint16_t eeprom_read_word(const uint16_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8);
}

void eeprom_write_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
}

void eeprom_update_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
}

uint32_t eeprom_read_dword(const uint32_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8) | (EEPROM_ReadDataByte(p + 2) << 16) | (EEPROM_ReadDataByte(p + 3) << 24);
}

void eeprom_write_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p = (const uint32_t)Address;
    EEPROM_WriteDataByte(p, (uint8_t)Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
    EEPROM_WriteDataByte(p + 2, (uint8_t)(Value >> 16));
    EEPROM_WriteDataByte(p + 3, (uint8_t)(Value >> 24));
}

void eeprom_update_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p             = (const uint32_t)Address;
    uint32_t existingValue = EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p + 1) << 8) | (EEPROM_ReadDataByte(p + 2) << 16) | (EEPROM_ReadDataByte(p + 3) << 24);
    if (Value != existingValue) {
        EEPROM_WriteDataByte(p, (uint8_t)Value);
        EEPROM_WriteDataByte(p + 1, (uint8_t)(Value >> 8));
        EEPROM_WriteDataByte(p + 2, (uint8_t)(Value >> 16));
        EEPROM_WriteDataByte(p + 3, (uint8_t)(Value >> 24));
    }
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
