/**
  ****************************************************************************************
  * @file    platform.h
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-27
  * @brief   the hardware platform define 
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM__
#define __PLATFORM__


/* debug switch define */
#define DEBUG_BLE_CONNECT
#define DEBUG_BLE_DFU
#define DEBUG_TEMPERATURE
#define DEBUG_TEMPERATURE_ADC

/* gpio define for uart */
#define RX_PIN_NUMBER               2
#define TX_PIN_NUMBER               3
#define CTS_PIN_NUMBER              17
#define RTS_PIN_NUMBER              15
#define HWFC                        false
    
/* gpio define for adc */
#define ADIN_P                      NRF_SAADC_INPUT_AIN0
#define ADIN_N                      NRF_SAADC_INPUT_AIN1
#define CORE_TEMPERATURE_ADC_NO     0
#define ADC_AVARAGE_TIMES	        10
#define ADC_GAIN                    NRF_SAADC_GAIN1_6

/* gpio define for sn74lv4052 */
#define GPIO_PIN_CORE_TEM_CTL0      6      
#define GPIO_PIN_CORE_TEM_CTL1      7



#endif // __PLATFORM__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


