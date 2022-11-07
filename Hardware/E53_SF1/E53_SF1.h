/********************************************************************************
    * 文件名称 ：E53_SF1.h
    * 作     者：小熊派开源社区
    * 版     本：V1.0
    * 编写日期 ：2019-5-27
    * 功     能：E53_SF1扩展板驱动
*********************************************************************************
    * 说    明 ：本例程配套小熊派开源社区开发板使用
    *
    * 淘     宝：https://shop336827451.taobao.com/
    * 论     坛：https://bbs.huaweicloud.com/forum/forum-734-1.html
    * 微信公众号：小熊派开源社区
*********************************************************************************/
#ifndef __E53_SF1_H__
#define __E53_SF1_H__
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32l4xx_hal.h"


#define MQ2_CONSTANT_1          4
#define MQ2_CONSTANT_2          613.9f
#define MQ2_CONSTANT_3          (-2.074f)

#define CAL_PPM 20 // 校准环境中PPM值
#define RL 1       // RL阻值

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim16;

/***************************************************************
* 名        称: GasStatus_ENUM
* 说    明：枚举状态结构体
***************************************************************/
typedef enum
{
    OFF = 0,
    ON
} E53_SF1_Status;

void E53_SF1_Init(void);
int E53_SF1_Read_Data(float *ppm);
void E53_SF1_LED_Set(E53_SF1_Status status);
void E53_SF1_Beep_Set(E53_SF1_Status status);

#endif





