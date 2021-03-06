/**
  ****************************************************************************************
  * @file    main.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-10
  * @brief   main program for nRF52832
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* gloable variables define */
SemaphoreHandle_t 			g_semaphore_ble_event_ready = NULL;				/**< Semaphore raised if there is a new event to be 
																				processed in the BLE thread. */
uint16_t                    g_conn_handle = BLE_CONN_HANDLE_INVALID;        /**< Handle of the current connection. */
QueueHandle_t			    measureMentEventQueue = NULL;                   //event queue for measurement
ble_hts_t                   g_hts;                                          /**< Structure used to identify the health thermometer service. */
ble_bas_t                   g_bas;                                          /**< Structure used to identify the battery service. */
ble_dfu_t                   g_dfus;                                         /**< Structure used to identify the DFU service. */            

/**
  * @brief  vApplicationIdleHook
  * @param  None
  * @retval None
  */
void vApplicationIdleHook( void )
{
     
}


/**
  * @brief  main
  * @note   the entry of the program
  * @param  None
  * @retval None
  */
int main(void)
{
    
    /* init for system */
    sys_init();
    
    /* Tasks creat */
    main_task_start();

//    /*****Trigger Hard fault handler for test  *****/
//    *(uint8_t *)(0xFFFFFFFF) = 0;
//    /************************/
    
    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;    
    
    // Start FreeRTOS scheduler.
    vTaskStartScheduler();

    while (true)
    {
        APP_ERROR_HANDLER(NRF_ERROR_FORBIDDEN);
    }
}


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/




