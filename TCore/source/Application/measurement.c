/**
  ****************************************************************************************
  * @file    measurement.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-13
  * @brief   the implement of menasure
  *         据说，路的尽头是海的入口...
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "measurement.h"
#include "app_freertos.h"
#include "ble_hts.h"
#include "battery_management.h"
#include "alg_temperature.h"
#include "bsp_temperature.h"


/* private define */
#define TEMP_TYPE_AS_CHARACTERISTIC     0                   /**< Determines if temperature type is given as characteristic (1) 
                                                                or as a field of measurement (0). */

/* private variable declare */
static TimerHandle_t				temSampleTime = NULL;
static uint16_t 					gSubFuncState = OFF;
static ble_hts_meas_t               m_healthThermometerValue;               

/* private function declare */
static void temperature_sampleTimer_cb(xTimerHandle pxTimer);
static void core_temperature_result_package(ble_hts_meas_t * p_meas, float Val);
static void core_temperature_rt_sample(uint32_t *TH2Rt,uint32_t *TH1Rt);

/**
  * @brief  measurement_thread
  * @note   测量任务
  * @param  pvParameters
  * @retval None    
  */
void measurement_thread(void *pvParameters)
{
	const TickType_t 		xMaxBlockTime = pdMS_TO_TICKS(300); /* 设置最大等待时间为 300ms */
	TEM_MSG_T 				temQueueMsgValue;
    uint32_t                TH2Rt = 0;
    uint32_t                TH1Rt = 0;
	float					TH2 = 0;
	float					TH1 = 0;
    float                   temperatureVal = 0;
    ret_code_t              err_code = NRF_ERROR_NULL;
	
	/* creat event queue for core temperature */
	measureMentEventQueue = xQueueCreate(MEASUREMENT_EVENT_QUEUE_SIZE,sizeof(TEM_MSG_T));
	#ifdef DEBUG_TEMPERATURE
		if(measureMentEventQueue == NULL)
		{
			printf("temperature queue creat fail\r\n");
		}
	#endif
		
	/* temperture event queue init */
	temQueueMsgValue.eventID = EVENT_TEMPERATURE_DEFAULT;
	gMeasurement_stat_set(TEMPERATURE_MEASURE_STATUS,OFF);
	
	while(1)
	{
		if(pdPASS == xQueueReceive(measureMentEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime))
		{
			/* 接收到消息，对消息事件进行处理 */
			switch(temQueueMsgValue.eventID)
			{
				case EVENT_START_CORETEM_MEASURE:
				{				
                    #ifdef DEBUG_TEMPERATURE
                        printf("start core temperature\r\n");
                    #endif
					/* init core temperature measure arithmetic */
					alg_core_temperature_calculate_init();
					
					/* start the time for temperature measure freq */
					if(temSampleTime != NULL)
					{
						xTimerDelete(temSampleTime,0);
					}
					temSampleTime = xTimerCreate("temTime",TEM_SAMPLE_PER,pdTRUE,(void *)0,temperature_sampleTimer_cb);
					xTimerStart(temSampleTime,0);
					
					gMeasurement_stat_set(TEMPERATURE_MEASURE_STATUS,ON);
				}
				break;
				case EVENT_GET_CORETEM_RESULT:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("get core temperature\r\n");
                    #endif                    
					if(
                        (gMeasurement_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF)  &&
                        (g_conn_handle != BLE_CONN_HANDLE_INVALID)
                    )
					{
						/* core temperature sample */
                        core_temperature_rt_sample(&TH2Rt,&TH1Rt);

						/* core temperature measure and update the value */
						ntc_temperature_calculate(TH2Rt,&TH2,NTC_10K);
						ntc_temperature_calculate(TH1Rt,&TH1,NTC_10K);
						
						/* calculate the core temperature through TH1,TH2 */
						core_temperature_calculate(TH1,TH2,&temperatureVal);
						#ifdef DEBUG_TEMPERATURE
//							printf("core tem val:%0.1f\r\n",g_TemVal);
						#endif
                        
                        /* for test */
                        static uint8_t i = 0;
                        i++;
                        
                        /* for test, update the battery level */
                        ble_battery_level_transmit(i);
                        
                        /* package the result of core temperature */
                        core_temperature_result_package(&m_healthThermometerValue,i);
                        
                        /* handle with the core temperature result */
                        temQueueMsgValue.eventID = EVENT_HANDLE_CORETEM_RESULT;
                        xQueueSend(measureMentEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime);  
					}
				}
				break;
                case EVENT_HANDLE_CORETEM_RESULT:
                {
                    /* handle with the core temperature result */
                    #ifdef DEBUG_TEMPERATURE
                        printf("ble transmit the core tem result:\r\n");
                    #endif
                    
                    if(
                        (gMeasurement_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF)  &&
                        (g_conn_handle != BLE_CONN_HANDLE_INVALID)
                    )
                    {                    
                        /* transmit the core temperature result */
                        err_code = ble_hts_measurement_send(&g_hts, &m_healthThermometerValue);
                        APP_ERROR_CHECK(err_code);
                    }
                }
                break;
				case EVENT_STOP_CORETEM_MEASURE:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("stop core temperature\r\n");
                    #endif                    
					xTimerDelete(temSampleTime,0);
					temSampleTime = NULL;
					gMeasurement_stat_set(TEMPERATURE_MEASURE_STATUS,OFF);
				}
				break;                
				default:break;
			}
		}
	}    
}

/**
  * @brief  gMeasurement_stat_set
  * @note   设置测量状态
  * @param  mask,newState
  * @retval None    
  */
void gMeasurement_stat_set(uint16_t mask, uint8_t newState)
{
	gSubFuncState = (newState == OFF)? gSubFuncState & (~mask) : gSubFuncState | mask;
}
/**
  * @brief  gMeasurement_stat_get
  * @note   获取测量状态
  * @param  mask
  * @retval status    
  */
uint16_t gMeasurement_stat_get(uint16_t mask)
{
	return(gSubFuncState & mask);
}


/**
  * @brief  temperature_sampleTimer_cb
  * @note   Tcore测量定时器回调函数，用于控制温度测量频率
  * @param  pxTimer
  * @retval None    
  */
static void temperature_sampleTimer_cb(xTimerHandle pxTimer)
{
	TEM_MSG_T 				temQueueMsgValue;
	BaseType_t              xHigherPriorityTaskWoken = pdFALSE;
    
	pxTimer = pxTimer;
	
    if(gMeasurement_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF)
    {        
        temQueueMsgValue.eventID = EVENT_GET_CORETEM_RESULT;
    }
    else    //the measurement of thermometer is off
    {
        temQueueMsgValue.eventID = EVENT_STOP_CORETEM_MEASURE;      
    }
    xQueueSendFromISR(measureMentEventQueue,(void *)&temQueueMsgValue,&xHigherPriorityTaskWoken);
    if(xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
/**
  * @brief  core_temperature_result_package
  * @note   核心温度结果打包   
  * @param[out]  ble_hts_meas_t * p_meas
  * @param[in]  float Val
  * @retval None    
  */
static void core_temperature_result_package(ble_hts_meas_t * p_meas, float Val)
{
    static ble_date_time_t time_stamp = { 2012, 12, 5, 11, 50, 0 };

    p_meas->temp_in_fahr_units = false;
    p_meas->time_stamp_present = true;
    p_meas->temp_type_present  = (TEMP_TYPE_AS_CHARACTERISTIC ? false : true);

    p_meas->temp_in_celcius.exponent = -2;
    p_meas->temp_in_celcius.mantissa = Val;
    p_meas->temp_in_fahr.exponent    = -2;
    p_meas->temp_in_fahr.mantissa    = (32 * 100) + ((Val * 9) / 5);
    p_meas->time_stamp               = time_stamp;
    p_meas->temp_type                = BLE_HTS_TEMP_TYPE_BODY;    
}

/**
  * @brief  core_temperature_rt_sample
  * @note   NTC阻值采集
  * @param  *TH2Rt,*TH1Rt(Ω)
  * @retval None    
  */
static void core_temperature_rt_sample(uint32_t *TH2Rt,uint32_t *TH1Rt)
{
    float Vsens12 = 0;
	float Vsens23 = 0;
    
    /* init core temperature measure hw source */
    core_temperature_hw_init();
    
    /* calculate the value of Rt */
    core_TH2_temperature_sample(&Vsens12,&Vsens23);
    *TH2Rt = (uint32_t)(Vsens12 / (Vsens23/R_CAL));
    
//    core_TH1_temperature_sample(&Vsens12,&Vsens23);
//    *TH2Rt = (uint32_t)(Vsens12 / (Vsens23/R_CAL));    

    core_TH1_temperature_sample(&Vsens12,&Vsens23);
    *TH1Rt = (uint32_t)(Vsens12 / (Vsens23/R_CAL));

    #ifdef DEBUG_TEMPERATURE
        printf("TH2Rt:%d,  TH1Rt:%d\r\n",*TH2Rt,*TH1Rt);
	#endif
    
    /* deinit core temperature measure hw source */	
    core_temperature_hw_deinit();
}

/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/

