/**
  ****************************************************************************************
  * @file    platform.h
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-27
  * @brief   the hardware platform define 
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM__
#define __PLATFORM__

/* includes */
#include <stdint.h>

/* debug switch define */
#define BOOTLOADER_TOP_LEVEL_DEBUG
#define BOOTLOADER_DFU_TRANSLATION_DEBUG
#define BOOTLOADER_DFU_HANDING_DEBUG



/* gpio and buffer define for uart */
#define RETARGET_ENABLED	1
#ifndef UART_TX_BUF_SIZE
    #define UART_TX_BUF_SIZE 1024         /**< UART TX buffer size. */
#endif
#ifndef UART_RX_BUF_SIZE
    #define UART_RX_BUF_SIZE 1            /**< UART RX buffer size. */
#endif
/* gpio define for uart */
#define RX_PIN_NUMBER               23
#define TX_PIN_NUMBER               18
#define CTS_PIN_NUMBER              7
#define RTS_PIN_NUMBER              5
#define HWFC                        false

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}

#endif // __PLATFORM__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


