/********************************************************************************
    * 文件名称 ：E53_SC2.h
    * 作     者：小熊派开源社区
    * 版     本：V1.0
    * 编写日期 ：2019-5-27
    * 功     能：E53_SC2扩展板驱动
*********************************************************************************
    * 说    明 ：本例程配套小熊派开源社区开发板使用
    *
    * 淘     宝：https://shop336827451.taobao.com/
    * 论     坛：https://bbs.huaweicloud.com/forum/forum-734-1.html
    * 微信公众号：小熊派开源社区
*********************************************************************************/
#ifndef __E53_SC2_H__
#define __E53_SC2_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "i2c.h"

/* E53_SC2传感器数据类型定义 ------------------------------------------------------------*/
typedef struct {
    short   Temperature;
    short   Accel[3];
} E53_SC2_Data;

typedef enum {
    OFF = 0,
    ON
} E53_SC2_Status;

enum AccelAxisNum {
    ACCEL_X_AXIS = 0,
    ACCEL_Y_AXIS = 1,
    ACCEL_Z_AXIS = 2,
    ACCEL_AXIS_BUTT= 3,
};

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
#define MPU6050_GYRO_OUT            0x43  //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT             0x3B  //MPU6050加速度数据寄存器地址
#define MPU6050_SLAVE_ADDRESS       0xd0  //MPU6050器件读地址
#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F  //运动检测阀值设置寄存器
#define MPU6050_RA_MOT_DUR          0x20  //运动检测时间阀值
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_INT_PIN_CFG      0x37   //中断/旁路设置寄存器
#define MPU6050_RA_INT_ENABLE       0x38   //中断使能寄存器
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_WHO_AM_I         0x75

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void MPU6050ReadTemp(short *tempData);
void MPU6050ReadGyro(short *gyroData);
void MPU6050ReadAcc(short *accData);
void MPU6050_ReturnTemp(short*Temperature);
void MPU6050_Init(void);
uint8_t MPU6050ReadID(void);
void PMU6050_ReadData(uint8_t reg_add,unsigned char*Read,uint8_t num);
void PMU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat);

void MPU6050_PWR_MGMT_1_INIT(void);

void Motion_Interrupt(void);             //运动中断
void Zero_Motion_Interrupt(void);        //静止中断
void Free_Fall_Interrupt(void);        //自由落体中断

void E53_SC2_Init(void);
void E53_SC2_Read_Data(E53_SC2_Data *ReadData);
void E53_SC2_LedD1_Set(E53_SC2_Status status);
void E53_SC2_LedD2_Set(E53_SC2_Status status);


#endif 
