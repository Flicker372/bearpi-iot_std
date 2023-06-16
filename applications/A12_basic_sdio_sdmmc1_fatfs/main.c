// 头文件
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "quadspi.h"
#include "sdmmc.h"
#include "spi.h"
#include "gpio.h"
#include "fatfs.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"

// 宏定义
#define pic_size 115200 // 图片大小，填单个bin文件大小，存储16进制颜色信息，在小熊派上过大编译时会报内存溢出
#define filename "pic.bin" // 文件名称

// 声明函数
void SystemClock_Config(void); // 系统时钟
void PeriphCommonClock_Config(void); // 外部时钟
void MountSD(void); // 挂载SD卡
void Show_Pic_Auto(TCHAR const*); // LCD显示数组中的图片
void Show_Pic_Manual(TCHAR const*); // LCD显示数组中的图片

// 声明
int stats = 0; // 状态
int file_size = 0; // 声明并初始化文件大小变量
int offset = 0; // 声明并初始化偏移量变量，从头开始
int jet = 1;
FATFS fs;
FIL file;
UINT br;

// 主函数
int main(void)
{
  // 硬件抽象层初始化
  HAL_Init();

  // 配置时钟
  SystemClock_Config();
  PeriphCommonClock_Config();

  // 初始化外围设备
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_QUADSPI_Init();
  MX_SDMMC1_SD_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
	MX_FATFS_Init();
  LCD_Init(); // LCD屏初始化

  MountSD(); // 挂载SD卡

  while (1)
  {
    Show_Pic_Auto(filename); // 文件放在SD卡根目录，传入bin文件名称
  }
}

void MountSD()
{
  f_mount(&fs, (TCHAR const*)SDPath, 1); // 挂载SD卡
}

// 逐帧显示数组中的图片
void Show_Pic_Auto(TCHAR const* OpenOrCreatTXTFileName)
{
  uint16_t i;
  uint8_t data[1200]; //存储五行像素点240 的 16进制颜色信息 240*5=1200

  f_open(&file, OpenOrCreatTXTFileName, FA_READ);
  file_size = f_size(&file); // 计算合并后bin文件的大小

  while (stats == 1 || stats == 0)
  {
    if (stats == 0)
    {
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET); // 亮
      for(i = 0; i < 96; i++)
      {
        f_read(&file, data, 1200, &br);//x方向240个像素点，每个像素点 2 个
        SPI2_WriteByte(data, 1200);//显示 5 行像素点
      }
      HAL_Delay(1000);
      offset += pic_size; // 偏移量，下一张图片
      if (offset >= file_size)
      {
        offset = 0;
      }
      f_lseek(&file, offset); // 移动文件流的读写位置
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); // 灭
      HAL_Delay(1000);
    }
    else if (stats == 1)
    {
      for(i = 0; i < 96; i++)
      {
        f_read(&file, data, 1200, &br);//x方向240个像素点，每个像素点 2 个
        SPI2_WriteByte(data, 1200);//显示 5 行像素点
      }
      offset = 0;
      offset += pic_size * jet; // 偏移量，下一张图片
      if (offset >= file_size)
      {
        offset = 0;
        jet = 0;
      }
      f_lseek(&file, offset); // 移动文件流的读写位置
    }
  }

  f_close(&file);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_RCCEx_EnableMSIPLLMode();
}

void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 16;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK|RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

// 外部中断
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // 外部中断回调函数
 {
  if (GPIO_Pin == KEY1_Pin) // 检测是否为外部中断2
	{
    stats = 1;
    jet++;
	}
	if (GPIO_Pin == KEY2_Pin) // 检测是否为外部中断3
	{
    stats = 2;
	}
 }

void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
