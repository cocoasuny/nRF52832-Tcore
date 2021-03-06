/**
  ****************************************************************************************
  * @file    bsp.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-10
  * @brief   the implement of bsp
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"


/**
  * @brief  sys_init
  * @note   the init of system
  * @param  None
  * @retval None
  */
void sys_init(void)
{
    ret_code_t ret = NRF_ERROR_NULL;
    
    /* init for clock */
    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    
    /* init for power */
    ret = nrf_drv_power_init(NULL);
    APP_ERROR_CHECK(ret);
}




/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/



