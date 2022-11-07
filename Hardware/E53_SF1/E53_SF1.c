/********************************************************************************
    * 文件名称 ：E53_SF1.c
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

#include "E53_SF1.h"
#include "stm32l4xx.h"
#include "adc.h"
#include "math.h"

uint16_t ADCvalue = 0;
static float R0; // 元件在洁净空气中的阻值

/***************************************************************
* 函数名称: GetVoltage
* 说    明: 获取电压值函数
* 参    数: 无
*
* 返 回 值: 无
***************************************************************/
static float GetVoltage(void)
{
    return (float)ADCvalue * 3.41 / 4096;
}

/***************************************************************
 * 函数名称: MQ2PPMCalibration
 * 说    明: 传感器校准函数
 * 参    数: 无
 * 返 回 值: 无
 ***************************************************************/
static void MQ2PPMCalibration(void)
{
    float voltage = GetVoltage();
    if (voltage != 0) {
        float RS = (MQ2_CONSTANT_1 - voltage) / voltage * RL;
        R0 = RS / pow(CAL_PPM / MQ2_CONSTANT_2, 1 / MQ2_CONSTANT_3);
    }
}

/***************************************************************
* 函数名称: E53_SF1_Init
* 说    明: 初始化E53_SF1扩展板
* 参    数: 无
* 返 回 值: 无
***************************************************************/
void E53_SF1_Init(void)
{
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADCvalue,1);
    HAL_Delay(1000);
    MQ2PPMCalibration();
}

/***************************************************************
 * 函数名称: E53_SF1_Read_Data
 * 说    明: 获取PPM函数
 * 参    数: ppm 烟雾浓度
 * 返 回 值: 0 成功; -1 失败
 ***************************************************************/
int E53_SF1_Read_Data(float *ppm)
{
    float voltage, RS;

    voltage = GetVoltage();
    RS = (MQ2_CONSTANT_1 - voltage) / voltage * RL;     // 计算RS
    *ppm = MQ2_CONSTANT_2 * pow(RS / R0, MQ2_CONSTANT_3); // 计算ppm
    return 0;
}

/***************************************************************
* 函数名称: E53_SF1_LED_Set
* 说    明: E53_SF1开发板上的LED灯的亮灭控制
* 参    数: status,LED灯的状态
*                                    OFF,关灯
*                                    ON,开灯
* 返 回 值: 无
***************************************************************/
void E53_SF1_LED_Set(E53_SF1_Status status)
{
    HAL_GPIO_WritePin(E53_GPIO1_GPIO_Port, E53_GPIO1_Pin, status != ON ? GPIO_PIN_RESET : GPIO_PIN_SET );    
}

/***************************************************************
* 函数名称: E53_SF1_Beep_Set
* 说    明: E53_SF1蜂鸣器报警与否
* 参    数: status,ENUM枚举的数据
*                                    OFF,蜂鸣器
*                                    ON,开蜂鸣器
* 返 回 值: 无
***************************************************************/
void E53_SF1_Beep_Set(E53_SF1_Status status)
{
  if (status == ON)
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
  if (status == OFF)
    HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
}


