#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_GPT_TIM1_IRQ_PRIORITY
#define WB32_GPT_TIM1_IRQ_PRIORITY 3
