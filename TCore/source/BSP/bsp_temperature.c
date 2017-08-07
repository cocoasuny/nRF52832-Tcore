/**
 ******************************************************************************
 * @file    bsp_temperature.c
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-3
 * @brief   This file provides a set of functions needed to measure core temperature.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "bsp_temperature.h"
#include "nrf_drv_saadc.h"
#include "platform.h"
#include "nrf_gpio.h"


/* private function declare */
static void core_temperature_channel_switch_IO_Init(void);
static void core_temperature_channel_switch_IO_DeInit(void);
static void core_temperature_channel_switch(SWITCH_CHANNEL_DEF channel);
static ret_code_t adc_init(void);
static void saadc_callback(nrf_drv_saadc_evt_t const * p_event);
static ret_code_t adc_convert(float * p_value);


/**
  * @brief  core_temperature_hw_init
  * @brief  参考温度测量
  * @param  None 
  * @retval None    
  */
void core_temperature_hw_init(void)
{
    ret_code_t err = NRF_ERROR_NULL;
    
	/* channel switch IO Init */
	core_temperature_channel_switch_IO_Init();
	
	/* ADC Init */
    err = adc_init();
    APP_ERROR_CHECK(err);
}
/**
  * @brief  core_TH2_temperature_sample
  * @brief  获取核心TH2温度AD采样电压值
  * @param[out]  VSens12, VSens23
  * @retval None    
  */
void core_TH2_temperature_sample(float *VSens12,float *VSens23)
{
	float V_sens = 0;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA0B0);
    adc_convert(&V_sens);
	*VSens12 = V_sens;
	
//    HAL_Delay(10);
    
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA1B1);
	adc_convert(&V_sens);
	*VSens23 = V_sens;	
    
//    HAL_Delay(10);
}
/**
  * @brief  core_TH1_temperature_sample
  * @brief  获取核心TH1温度AD采样电压值
  * @param  VSens12, VSens23
  * @retval None    
  */
void core_TH1_temperature_sample(float *VSens12,float *VSens23)
{
	float V_sens = 0;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA2B2);
	adc_convert(&V_sens);
	*VSens12 = V_sens;
    
//    HAL_Delay(10);
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA3B3);
	adc_convert(&V_sens);
	*VSens23 = V_sens;	
    
//    HAL_Delay(10);
}
/**
  * @brief  core_temperature_deinit
  * @brief  核心温度测量
  * @param  None 
  * @retval None    
  */
void core_temperature_hw_deinit(void)
{
	/* channel switch io deinit */
    core_temperature_channel_switch_IO_DeInit();
    
    /* adc deinit */
    
}
/**
  * @brief  core_temperature_channel_switch_IO_Init
  * @brief  核心温度测量模拟开关控制IO口初始化
  * @param  None 
  * @retval None    
  */
static void core_temperature_channel_switch_IO_Init(void)
{
	/* Configure CTL0 pins */
    nrf_gpio_cfg_output(GPIO_PIN_CORE_TEM_CTL0);

	/* Configure CTL1 pins */
    nrf_gpio_cfg_output(GPIO_PIN_CORE_TEM_CTL0);
}
/**
  * @brief  core_temperature_channel_switch_IO_DeInit
  * @brief  核心温度测量模拟开关控制IO口Deinit
  * @param  None 
  * @retval None    
  */
static void core_temperature_channel_switch_IO_DeInit(void)
{
	/* Configure CTL0 pins */
    nrf_gpio_cfg_default(GPIO_PIN_CORE_TEM_CTL0);

	/* Configure CTL1 pins */
    nrf_gpio_cfg_default(GPIO_PIN_CORE_TEM_CTL0);
}
/**
  * @brief  core_temperature_channel_switch
  * @brief  控制核心温度测量模拟开关通道
  * @param  channel
  * @retval None    
  */
static void core_temperature_channel_switch(SWITCH_CHANNEL_DEF channel)
{
	switch(channel)
	{
		case ChannelA0B0:
		{
            nrf_gpio_pin_clear(GPIO_PIN_CORE_TEM_CTL0);
            nrf_gpio_pin_clear(GPIO_PIN_CORE_TEM_CTL1);
		}
		break;
		case ChannelA1B1:
		{
            nrf_gpio_pin_set(GPIO_PIN_CORE_TEM_CTL0);
            nrf_gpio_pin_clear(GPIO_PIN_CORE_TEM_CTL1);		
		}
		break;
		case ChannelA2B2:
		{
            nrf_gpio_pin_clear(GPIO_PIN_CORE_TEM_CTL0);
            nrf_gpio_pin_set(GPIO_PIN_CORE_TEM_CTL1);
		}
		break;
		case ChannelA3B3:
		{
            nrf_gpio_pin_set(GPIO_PIN_CORE_TEM_CTL0);
            nrf_gpio_pin_set(GPIO_PIN_CORE_TEM_CTL1);            		
		}
		break;
		default:break;		
	}
}
/**
  * @brief  saadc_callback
  * @brief  saadc_callback
  * @param  nrf_drv_saadc_evt_t const * p_event
  * @retval None   
  */
static void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    //nothing to do at this moment
}
/**
  * @brief  adc_init
  * @brief  NTC电压采集初始化
  * @param  None
  * @retval error code    
  */
static ret_code_t adc_init(void)
{
    ret_code_t err_code = NRF_ERROR_NULL;
    
    nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(ADIN_P,ADIN_N);
    
    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code); 

    err_code = nrf_drv_saadc_channel_init(CORE_TEMPERATURE_ADC_NO, &channel_config);
    APP_ERROR_CHECK(err_code);
        
    return err_code;
}
/**
  * @brief  adc_convert
  * @brief  启动NTC AD转换
  * @param[out]  p_value
  * @retval error code    
  */
static ret_code_t adc_convert(float * p_value)
{
    ret_code_t              err_code = NRF_ERROR_NULL;
    nrf_saadc_value_t       adc_sum = 0;
    nrf_saadc_value_t       adc_val = 0;
    nrf_saadc_value_t       adc_avg = 0;
    uint8_t                 i = 0;
    
    for(i=0;i<ADC_AVARAGE_TIMES;i++)
    {
        err_code = nrf_drv_saadc_sample_convert(CORE_TEMPERATURE_ADC_NO,&adc_val);
        if(err_code == NRF_SUCCESS)
        {
            adc_sum = adc_sum + adc_val;
        }
        else
        {
            APP_ERROR_CHECK(err_code);
            return err_code;
        }     
    }
    
    adc_avg = (nrf_saadc_value_t)(adc_sum/ADC_AVARAGE_TIMES);
    (*p_value) = (float)(adc_avg*3.6/512);
    #ifdef DEBUG_TEMPERATURE_ADC
        printf("ADC Val:%d,%02f\r\n",adc_avg,(*p_value));
    #endif
    
    return err_code;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

