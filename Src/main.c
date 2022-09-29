/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "ssd1306.h"
#include "gfx.h"
#include "assets.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  // Delay for a while for waiting for debugger
  LL_mDelay(20);

  // Initialize Display
  ssd1306_init_device();

  uint8_t config_cmd[] = {
          0xE3, // NOP
          0x02, // Column Address: 0x02
          0x10, // Column Address: 0x02
          0xB7, // Page 7
  };

  ssd1306_command_buffer_t cmd[2];
  cmd[0].dc = 0;
  cmd[0].first_command = (uint8_t*)config_cmd;
  cmd[0].length = sizeof(config_cmd);
  cmd[0].next = &cmd[1];

  cmd[1].dc = 1;
  cmd[1].first_command = (uint8_t*)font8x8;
  cmd[1].length = 128;//sizeof(font8x8)-511;
  cmd[1].next = NULL;

  for (int p = 0; p < 8; ++p) {
      ssd1306_submit_command_buffer(&cmd[0]);
      // ssd1306_submit_command_buffer(&cmd[1]);
      ssd1306_wait_for_complete();
      config_cmd[3]--; // Page Decrement
      cmd[1].first_command += 128; // Next Page Data
  }

  LL_mDelay(500);

  gfx_frame_description_t frame_desc;

  memset(&frame_desc, 0, sizeof(frame_desc));

  frame_desc.sprite_table_size = SPRITE_TABLE_SIZE_128;
  frame_desc.sprite_table = (uint8_t*)font8x8;
  frame_desc.mask_table = (uint8_t*)font8x8;

  int32_t pos_x[2] = {0, 16};
  int32_t pos_y[2] = {0, 30};
  int32_t vol_x[2] = {1, -1};
  int32_t vol_y[2] = {1, -1};

    gfx_sprite_info_t sprite[2];
    sprite[0].sprite_size_x = SPRITE_SIZE_16;
    sprite[0].sprite_size_y = SPRITE_SIZE_16;
    sprite[0].sprite_idx_x = 0;
    sprite[0].sprite_idx_y = 4;
    sprite[0].invert_color = 0;
    sprite[0].flip_x = 1;

    sprite[1].sprite_size_x = SPRITE_SIZE_16;
    sprite[1].sprite_size_y = SPRITE_SIZE_16;
    sprite[1].sprite_idx_x = 0;
    sprite[1].sprite_idx_y = 4;
    sprite[1].invert_color = 0;
    sprite[1].flip_x = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */

    // Demo: draw sprite
    gfx_begin_frame(&frame_desc);

    for (int i = 0; i < 2; ++i) {
        sprite[i].sprite_pos_x = SP_ENCODE_POS(pos_x[i]);
        sprite[i].sprite_pos_y = SP_ENCODE_POS(pos_y[i]);

        gfx_draw_sprite(sprite[i]);

        pos_x[i] += vol_x[i];
        pos_y[i] += vol_y[i];

        if (pos_x[i] < -8 || pos_x[i] + 8 > 128) {
            vol_x[i] = -vol_x[i];
        }

        if (pos_y[i] < -8 || pos_y[i] + 8 > 64) {
            vol_y[i] = -vol_y[i];
        }
    }

    gfx_end_frame();


    // 33ms per frame
    LL_mDelay(16);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(48000000);
  LL_SetSystemCoreClock(48000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
