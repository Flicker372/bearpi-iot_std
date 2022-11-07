################################################################################
# this is used for compile the user defined oc demo
################################################################################

#if you have defined multiple demos by yourself, modify this file to compile the chosen demo.

#example 

	ifeq ($(CONFIG_A1_BASIC_LED), y)		
		user_demo_src  = applications/A1_basic_led/main.c 
	endif

	ifeq ($(CONFIG_A2_BASIC_KEY), y)		
		user_demo_src  = applications/A2_basic_key/main.c 
	endif

	ifeq ($(CONFIG_A3_BASIC_KEY_IRQ), y)		
		user_demo_src  = applications/A3_basic_key_irq/main.c 
	endif

	ifeq ($(CONFIG_A4_BASIC_UART), y)		
		user_demo_src  = applications/A4_basic_uart/main.c 
	endif

	ifeq ($(CONFIG_A5_BASIC_DAC), y)		
		user_demo_src  = applications/A5_basic_dac/main.c 
	endif

	ifeq ($(CONFIG_A6_BASIC_ADC_DMA), y)		
		user_demo_src  = applications/A6_basic_adc_dma/main.c 
	endif

	ifeq ($(CONFIG_A7_BASIC_TIM2), y)		
		user_demo_src  = applications/A7_basic_tim2/main.c 
	endif

	ifeq ($(CONFIG_A8_BASIC_SPI_LCD), y)		
		user_demo_src  = applications/A8_basic_spi_lcd/main.c 
	endif

	ifeq ($(CONFIG_A9_BASIC_FLASH), y)		
		user_demo_src  = applications/A9_basic_flash/main.c 
	endif

	ifeq ($(CONFIG_A10_BASIC_QSPI_W25Q64), y)		
		user_demo_src  = applications/A10_basic_qspi_w25q64/main.c 
	endif

	ifeq ($(CONFIG_A11_BASIC_SDIO_SDMMC1), y)		
		user_demo_src  = applications/A11_basic_sdio_sdmmc1/main.c 
	endif

	ifeq ($(CONFIG_A12_BASIC_SDIO_SDMMC1_FATFS), y)		
		user_demo_src  = applications/A12_basic_sdio_sdmmc1_fatfs/main.c 
	endif

	ifeq ($(CONFIG_B1_E53_SC1_PLS), y)		
		user_demo_src  = applications/B1_e53_sc1_pls/main.c 
	endif

	ifeq ($(CONFIG_B2_E53_IA1_TEMP_HUMI_PLS), y)		
		user_demo_src  = applications/B2_e53_ia1_temp_humi_pls/main.c 
	endif

	ifeq ($(CONFIG_B3_E53_SF1_SMOKE), y)		
		user_demo_src  = applications/B3_e53_sf1_smoke/main.c 
	endif

	ifeq ($(CONFIG_B4_E53_SC2_AXIS), y)		
		user_demo_src  = applications/B4_e53_sc2_axis/main.c 
	endif

	ifeq ($(CONFIG_B5_E53_ST1_GPS), y)		
		user_demo_src  = applications/B5_e53_st1_gps/main.c 
	endif

	ifeq ($(CONFIG_B6_E53_IS1_INFRARED), y)		
		user_demo_src  = applications/B6_e53_is1_infrared/main.c 
	endif

	C_SOURCES += $(user_demo_src)

