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

/* private variables define */
static TaskHandle_t 				m_logger_thread;					  	/**< Definition of Logger thread. */


/* private function declare*/
static void logger_thread(void * arg);

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
    UNUSED_PARAMETER(arg);

    while(1)
    {
        cli_process();
		vTaskDelay(100);
    }
}

/**
  * @brief  creat the tasks
  * @param  None
  * @retval None
  */
void app_task_creat(void)
{
	/* creat a thread for logger */	
    if (pdPASS != xTaskCreate(logger_thread, "LOG", TASK_LOG_STACK, NULL, TASK_LOG_PRIORITY, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }    
}





/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/



