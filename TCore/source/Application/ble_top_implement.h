/**
  ****************************************************************************************
  * @file    freertos.h
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-11
  * @brief   the header of ble_top_implement.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLE_TOP_IMPLEMENT__
#define __BLE_TOP_IMPLEMENT__

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}


/* function declares */
void ble_top_implementation_thread(void * arg);


#endif // __BLE_TOP_IMPLEMENT__

/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/

