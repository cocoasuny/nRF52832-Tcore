/**
  ****************************************************************************************
  * @file    measurement.h
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-13
  * @brief   the header of measurement.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEASUREMENT__
#define __MEASUREMENT__

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* definitions */
#define MEASUREMENT_EVENT_QUEUE_SIZE    			(10)
#define TEM_SAMPLE_PER								pdMS_TO_TICKS(1000) //ms

/* Define sub-function status */
#define TEMPERATURE_MEASURE_STATUS 			        (1 << 0)

/* type struct define */
typedef enum
{
	EVENT_TEMPERATURE_DEFAULT=0,
	EVENT_START_CORETEM_MEASURE,
	EVENT_GET_CORETEM_RESULT,
    EVENT_HANDLE_CORETEM_RESULT,
	EVENT_STOP_CORETEM_MEASURE
}TEM_EVENT_ID_T;

typedef struct
{
	TEM_EVENT_ID_T		eventID;			
}TEM_MSG_T;



/* function declares */
void measurement_thread(void *pvParameters);
void gMeasurement_stat_set(uint16_t mask, uint8_t newState);
uint16_t gMeasurement_stat_get(uint16_t mask);




#endif //__MEASUREMENT__

/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/



