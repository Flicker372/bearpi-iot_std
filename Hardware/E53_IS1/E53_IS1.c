/********************************************************************************
    * 文件名称 ：E53_IS1.c
    * 作     者：小熊派开源社区
    * 版     本：V1.0
    * 编写日期 ：2019-5-27
    * 功     能：E53_IS1扩展板驱动
*********************************************************************************
    * 说    明 ：本例程配套小熊派开源社区开发板使用
    *
    * 淘     宝：https://shop336827451.taobao.com/
    * 论     坛：https://bbs.huaweicloud.com/forum/forum-734-1.html
    * 微信公众号：小熊派开源社区
*********************************************************************************/
#include "E53_IS1.h"
#include "gpio.h"

void Infrared_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
    
  GPIO_InitStruct.Pin = E53_GPIO2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(E53_GPIO2_GPIO_Port, &GPIO_InitStruct);    
}


/***************************************************************
* 函数名称: E53_IS1_Init
* 说    明: 初始化E53_IS1扩展板
* 参    数: 无
* 返 回 值: 无
***************************************************************/
void E53_IS1_Init(void)
{
  Infrared_Init();
}

/***************************************************************
 * 函数名称: E53_IS1_Read_Data
 * 说    明: 读取数据
 * 参    数: 无
 * 返 回 值: 1 有人 0 没人
 ***************************************************************/
int E53_IS1_Read_Data(void)
{
    if (HAL_GPIO_ReadPin(E53_GPIO2_GPIO_Port, E53_GPIO2_Pin) == GPIO_PIN_SET) {
        return 1;
    }
    return 0;
}
/***************************************************************
* 函数名称: E53_IS1_Beep_Set
* 说    明: E53_IS1蜂鸣器报警与否
* 参    数: status,枚举的数据
*                                    OFF,关蜂鸣器
*                                    ON,开蜂鸣器
* 返 回 值: 无
***************************************************************/
void E53_IS1_Beep_Set(E53_IS1_Status status)
{
    if(status == ON)
        HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
    if(status == OFF)
        HAL_TIM_PWM_Stop(&htim16,TIM_CHANNEL_1);
}
