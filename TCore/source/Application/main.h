/**
  ****************************************************************************************
  * @file    main.h
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-27
  * @brief   header of main.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN__
#define __MAIN__

#include <stdint.h>
#include <string.h>
#include "common.h"
#include "ble_types.h"
#include "ble_hts.h"
#include "ble_bas.h"
#include "ble_dfu.h"


#define OFF					0
#define ON					1


/* gloable variables declare */
extern SemaphoreHandle_t 			g_semaphore_ble_event_ready;
extern uint16_t                     g_conn_handle;  
extern QueueHandle_t			    measureMentEventQueue;     
extern ble_hts_t                    g_hts;                       /**< Structure used to identify the health thermometer service. */
extern ble_bas_t                    g_bas;                       /**< Structure used to identify the battery service. */
extern ble_dfu_t                    g_dfus;                                         /**< Structure used to identify the DFU service. */ 


#endif // __MAIN__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


