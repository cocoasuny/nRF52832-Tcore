/**
  ****************************************************************************************
  * @file    freertos.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-11
  * @brief   the implement of task
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"
#include "bsp_cli.h"
#include "main.h"
#include "ble_top_implement.h"
#include "measurement.h"

/* private variables define */
static TaskHandle_t 				m_logger_thread;					  	/**< Definition of Logger thread. */
static TaskHandle_t 				m_creat_task_thread;					/**< Definition of creat task thread. */
static TaskHandle_t 				m_ble_top_implementation_thread;      	/**< Definition of BLE stack thread. */
static TaskHandle_t                 m_measurement_thread;                   /**< Definition of measurement thread. */

/* private function declare*/
static void logger_thread(void * arg);
static void app_task_creat(void);
static void creat_task_thread(void * arg);


/**@brief Thread for handling the logger.
 *
 * @details This thread is responsible for processing log entries if logs are deferred.
 *          Thread flushes all log entries and suspends. It is resumed by idle task hook.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void logger_thread(void * arg)
{
    ret_code_t ret = NRF_ERROR_NULL;
    
    UNUSED_PARAMETER(arg);
    
    /* init for cli,and start */
    ret = cli_init();
    APP_ERROR_CHECK(ret);
    cli_start();

    while(1)
    {
        cli_process();
		vTaskDelay(50);
    }
}

/**@brief Thread for handling the creat tasks and bsp initalize.
 *
 * @details This thread is responsible for processing log entries if logs are deferred.
 *          Thread flushes all log entries and suspends. It is resumed by idle task hook.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void creat_task_thread(void * arg)
{
    ret_code_t ret = NRF_ERROR_NULL;
    
    UNUSED_PARAMETER(arg);
    
    /* bsp init */
    
    /* creat tasks */
    app_task_creat();
    
    UNUSED_PARAMETER(ret);
    
    /* delete the creat task */
    vTaskDelete(m_creat_task_thread);
}

/**
  * @brief  creat the tasks
  * @param  None
  * @retval None
  */
static void app_task_creat(void)
{
    
	/* Init a semaphore for the BLE thread. */
    g_semaphore_ble_event_ready = xSemaphoreCreateBinary();
    if (NULL == g_semaphore_ble_event_ready)
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

	/* creat a thread for ble top level implementation*/
	if(
		pdPASS != xTaskCreate(ble_top_implementation_thread,"ble",BLE_TOP_IMPLEMENTATION_STACK,NULL,
							  	BLE_TOP_IMPLEMENTATION_PRIORITY,&m_ble_top_implementation_thread)
	)
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}    
      
    /* creat a thread for measurement */
	if(
		pdPASS != xTaskCreate(measurement_thread,"meat",MEASUREMENT_STACK,NULL,
							  	MEASUREMENT_PRIORITY,&m_measurement_thread)
	)
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}  
}
/**
  * @brief  start the main task to start the system
  * @param  None
  * @retval None
  */
void main_task_start(void)
{
	/* creat a thread for logger */	
    if (pdPASS != xTaskCreate(logger_thread, "LOG", TASK_LOG_STACK, NULL, TASK_LOG_PRIORITY, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
    
	/* creat a thread for creat tasks */	
    if (pdPASS != xTaskCreate(creat_task_thread, "CTT", TASK_LOG_STACK, NULL, 1, &m_creat_task_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }    
}





/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/



