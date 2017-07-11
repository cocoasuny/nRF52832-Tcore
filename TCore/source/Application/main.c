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
    
    /* init for bsp */
    bsp_init();

    /* Tasks creat */
    app_task_creat();
    
    printf("start...\r\n");
    
    // Start FreeRTOS scheduler.
    vTaskStartScheduler();

    while (true)
    {
        APP_ERROR_HANDLER(NRF_ERROR_FORBIDDEN);
    }
}


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/




