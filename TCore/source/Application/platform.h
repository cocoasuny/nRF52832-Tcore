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
#define DEBUG_BLE_CONNECT							1	//enable ble connect debug
#define DEBUG_BLE_DFU								1	//enable ble DFU debug
#define DEBUG_TEMPERATURE_TOP_LEVEL					1	//enable temperature top level debug
#define DEBUG_TEMPERATURE							0	//enable temperature debug
#define DEBUG_TEMPERATURE_ADC						0	//disable temperature adc debug
	
/* gpio define for uart */
#define RX_PIN_NUMBER               23
#define TX_PIN_NUMBER               18
#define CTS_PIN_NUMBER              17
#define RTS_PIN_NUMBER              15
#define HWFC                        false
    
/* gpio define for adc */
#define ADIN_P                      NRF_SAADC_INPUT_AIN2
#define ADIN_N                      NRF_SAADC_INPUT_AIN3
#define CORE_TEMPERATURE_ADC_NO     0
#define ADC_AVARAGE_TIMES	        16		//notice:必须大于2，即从3开始（因为adc最终值采用去掉最大最小值，求平均值的方式得到最终结果）
#define ADC_GAIN                    NRF_SAADC_GAIN1_6

/* gpio define for sn74lv4052 */
#define GPIO_PIN_CORE_TEM_CTL0      12      
#define GPIO_PIN_CORE_TEM_CTL1      14



#endif // __PLATFORM__


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/


