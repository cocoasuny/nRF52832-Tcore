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


#define OFF					0
#define ON					1


/* gloable variables declare */
extern SemaphoreHandle_t 			g_semaphore_ble_event_ready;
extern uint16_t                     g_conn_handle;  
extern QueueHandle_t			    measureMentEventQueue;     


#endif // __MAIN__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


