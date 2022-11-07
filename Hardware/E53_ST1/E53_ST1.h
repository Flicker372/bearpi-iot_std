/********************************************************************************
    * 文件名称 ：E53_ST1.h
    * 作     者：小熊派开源社区
    * 版     本：V1.0
    * 编写日期 ：2019-5-27
    * 功     能：E53_ST1扩展板驱动
*********************************************************************************
    * 说    明 ：本例程配套小熊派开源社区开发板使用
    *
    * 淘     宝：https://shop336827451.taobao.com/
    * 论     坛：https://bbs.huaweicloud.com/forum/forum-734-1.html
    * 微信公众号：小熊派开源社区
*********************************************************************************/
#ifndef __E53_ST1_H__
#define __E53_ST1_H__
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* 控制设备IO口定义 ------------------------------------------------------------*/

#define ST1_GPS_POW_Pin GPIO_PIN_9
#define ST1_GPS_POW_GPIO_Port GPIOC
#define ST1_GPS_POW_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

/***************************************************************
* 名        称: GasStatus_ENUM
* 说    明：枚举状态结构体
***************************************************************/
typedef enum
{
    OFF = 0,
    ON
} E53_ST1_Status;

/***************************************************\
*GPS NMEA-0183协议重要参数结构体定义
*卫星信息
\***************************************************/
__packed typedef struct
{
    uint32_t latitude_bd;                    //纬度   分扩大100000倍，实际要除以100000
    uint8_t nshemi_bd;                        //北纬/南纬,N:北纬;S:南纬    
    uint32_t longitude_bd;              //经度 分扩大100000倍,实际要除以100000
    uint8_t ewhemi_bd;                        //东经/西经,E:东经;W:西经
}gps_msg;

/* E53_ST1传感器数据类型定义 ------------------------------------------------------------*/
typedef struct {
    float    Longitude;         // 经度
    float    Latitude;          // 纬度
} E53_ST1_Data;


extern TIM_HandleTypeDef htim16;

void E53_ST1_Init(void);
void E53_ST1_Read_Data(E53_ST1_Data *ReadData);
void E53_ST1_LED_Set(E53_ST1_Status status);
void E53_ST1_Beep_Set(E53_ST1_Status status);

#endif





