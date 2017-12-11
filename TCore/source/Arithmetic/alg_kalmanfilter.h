/**
 ******************************************************************************
 * @file    alg_kalmanfilter.h
 * @author  Jason
 * @version V1.0.0
 * @date    2017-12-11
 * @brief   The header of alg_kalmanfilter.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ALG_KALMANFILTER_H
#define __ALG_KALMANFILTER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* function declare */
void alg_kalmanfilter_init(void);
float alg_kalmanfilter(float measure_val);

#endif /* __ALG_KALMANFILTER_H */


/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/
