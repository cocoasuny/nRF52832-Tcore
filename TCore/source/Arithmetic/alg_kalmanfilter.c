/**
 ******************************************************************************
 * @file    alg_kalmanfilter.c
 * @author  Jason
 * @version V1.0.0
 * @date    2017-12-11
 * @brief   The implement of kalman filter
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "alg_kalmanfilter.h"
#include "math.h"


/* private variable declare */
static float kalmanGain = 0;				//	卡尔曼增益
static float estimateCovariance = 0;		//	估计协方差
static float measureCovariance = 0;			//	测量协方差
static float estimateValue = 0;				//	估计值


/**
  * @brief  alg_kalmanfilter_init
  * @note   the init of kalmanfilter
  * @param  none
  * @retval none
  */
void alg_kalmanfilter_init(void)
{
	estimateValue = 0;
	estimateCovariance = 0.1;
	measureCovariance = 0.02;
}	


/**
  * @brief  alg_kalmanfilter
  * @note   the entry of the kalmanfilter
  * @param[in]  now measure value
  * @retval estimate value 
  */
float alg_kalmanfilter(float measure_val) 
{
	// 1. 计算卡尔曼增益
	kalmanGain = estimateCovariance*sqrt(1 / (estimateCovariance*estimateCovariance + measureCovariance*measureCovariance));
	
	// 2. 计算本次滤波估计值
	estimateValue = estimateValue + kalmanGain*(measure_val - estimateValue);
	
	// 3. 更新估计协方差
	estimateCovariance = sqrt(1-kalmanGain)*estimateCovariance;
	
	// 4. 更新测量方差
	measureCovariance = sqrt(1-kalmanGain)*measureCovariance;
	
	// 5. 返回预估值
	return estimateValue;
}	




















/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/

