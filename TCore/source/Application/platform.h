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


/* debug switch define */
#define DEBUG_BLE_CONNECT
#define DEBUG_BLE_DFU
#define DEBUG_TEMPERATURE

/* gpio define for uart */
#define RX_PIN_NUMBER               2
#define TX_PIN_NUMBER               3
#define CTS_PIN_NUMBER              7
#define RTS_PIN_NUMBER              5
#define HWFC                        false



#endif // __PLATFORM__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


