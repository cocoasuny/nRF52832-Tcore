/**
  ****************************************************************************************
  * @file    battery_management.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-24
  * @brief   the implement of battery management
  *       竹杖芒鞋轻胜马，谁怕，一蓑烟雨任平生.  
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "battery_management.h"
#include "ble_bas.h"


/**
  * @brief  ble_battery_level_transmit
  * @note   蓝牙发送电池电量
  * @param  uint8_t batLevel (%)
  * @retval None    
  */
void ble_battery_level_transmit(uint8_t batLevel)
{
    ret_code_t err_code;

    err_code = ble_bas_battery_level_update(&g_bas, batLevel);
    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != NRF_ERROR_RESOURCES)
       )
    {
        APP_ERROR_HANDLER(err_code);
    }    
}





/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


