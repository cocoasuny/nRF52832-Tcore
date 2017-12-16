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
static float estimateValue = 0;				//	估计值
static float ProcessNiose_Q = 0;			//  Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
static float MeasureNoise_R = 0;			//  R:测量噪声，R增大，动态响应变慢，收敛稳定性变好


/**
  * @brief  alg_kalmanfilter_init
  * @note   the init of kalmanfilter
  * @param  none
  * @retval none
  */
void alg_kalmanfilter_init(void)
{
	estimateValue = 0;
	estimateCovariance = 0;
	ProcessNiose_Q = 0.001;			//  Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
	MeasureNoise_R = 0.3;			//  R:测量噪声，R增大，动态响应变慢，收敛稳定性变好	
}	


/**
  * @brief  alg_kalmanfilter
  * @note   the entry of the kalmanfilter
  * @param[in]  now measure value
  * @retval estimate value 
  */
float alg_kalmanfilter(float measure_val) 
{

	// 1. 更新估计协方差
	estimateCovariance = estimateCovariance + ProcessNiose_Q;

	// 2. 计算卡尔曼增益
	kalmanGain = estimateCovariance/(estimateCovariance + MeasureNoise_R);

	printf(",kg:%0.5f,",kalmanGain);

	// 3. 计算本次滤波估计值
	estimateValue = estimateValue + kalmanGain*(measure_val - estimateValue);
	
	// 4. 更新估计协方差
	estimateCovariance = (1-kalmanGain)*estimateCovariance; 
	
	// 5. 返回预估值
	return estimateValue;
}	




















/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/

