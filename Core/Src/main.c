/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adi_initialize.h"
//#include "a2bapp_bf.h"
#include "adi_a2b_externs.h"
#include "adi_a2b_busconfig.h"
#include "a2bapp_defs.h"
#include "a2bapp.h"
#include <errno.h>
#include <string.h>
#include "a2b/pluginapi.h"
#include "adi_a2b_externs.h"
#include <assert.h>
#include <stdio.h>
#include "adi_a2b_i2c_commandlist.h"
#include "..\adi_a2b_datatypes.h"

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
static a2b_App_t gApp_Info;
a2b_UInt8 CurrNode;

char __argv_string[] = "";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static a2b_HResult adi_a2b_NetworkSetup(void);
static void adi_a2b_Concat_Addr_Data(a2b_UInt8 pDstBuf[], a2b_UInt32 nAddrwidth, a2b_UInt32 nAddr);
a2b_HResult adi_a2b_SystemInit(void);
//void  adi_a2b_Delay(a2b_UInt32 nTime);
a2b_HResult adi_a2b_I2COpen(void);
a2b_HResult adi_a2b_I2CWrite(a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf);
a2b_HResult adi_a2b_I2CWriteRead(a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf, a2b_UInt16 nRead, a2b_UInt8* rBuf);
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

  //HAL_DBGMCU_EnableDBGStandbyMode();
  DBGMCU->APB2FZ |= DBGMCU_APB2_FZ_DBG_TIM10_STOP;
  HAL_TIM_Base_Start_IT(&htim10);

  a2b_UInt32 nResult = 0;
  bool bRunFlag = true;
  adi_initComponents();

  nResult = adi_a2b_SystemInit(); 		/* system/platform specific initialization */
  if(nResult != 0)
	  assert(nResult == 0);

  /* A2B Network Setup. Performs discovery and configuration of A2B nodes and its peripherals */
  nResult = a2b_setup(&gApp_Info);
  if (nResult)
  {
	  CurrNode = gApp_Info.faultNode;
	  printf("Currently found node number is:%d\n", CurrNode);
	  assert(nResult == 0);				/* failed to setup A2B network */
  }



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	nResult = a2b_fault_monitor(&gApp_Info);		/* Monitor a2b network for faults and initiate re-discovery if enabled */
	/*-----------------------------------------------------------*/
	/* Add your other continuous monitoring application code here */
	/*-----------------------------------------------------------*/
	if (nResult != 0)
		bRunFlag = false;							/* condition to exit the program */
	a2b_stackTick(gApp_Info.ctx);					/* tick keeps all process rolling.. so keep ticking */


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/****************************************************************************/
/*!
 @brief          This function does A2B network discovery and the peripheral configuration
 @return          None

 */
/********************************************************************************/
a2b_HResult adi_a2b_NetworkSetup()
{
	ADI_A2B_DISCOVERY_CONFIG* pOPUnit;
	uint32 nIndex, nIndex1;
	a2b_HResult status = 0;
	/* Maximum number of writes */
	static uint8 aDataBuffer[6000];
	static uint8 aDataWriteReadBuf[4u];
	uint32 nDelayVal;

	/* Loop over all the configuration */
	for (nIndex = 0; nIndex < CONFIG_LEN; nIndex++)
	{
		pOPUnit = &gaA2BConfig[nIndex];
		/* Operation code*/
		switch (pOPUnit->eOpCode)
		{
			/* Write */
			case WRITE:
				adi_a2b_Concat_Addr_Data(&aDataBuffer[0u], pOPUnit->nAddrWidth, pOPUnit->nAddr);
				(void)memcpy(&aDataBuffer[pOPUnit->nAddrWidth], pOPUnit->paConfigData, pOPUnit->nDataCount);
				/* PAL Call, replace with custom implementation  */
				status = adi_a2b_I2CWrite((uint16)pOPUnit->nDeviceAddr, (uint16)(pOPUnit->nAddrWidth + pOPUnit->nDataCount), &aDataBuffer[0u]);
				break;

				/* Read */
			case READ:
				(void)memset(&aDataBuffer[0u], 0u, pOPUnit->nDataCount);
				adi_a2b_Concat_Addr_Data(&aDataWriteReadBuf[0u], pOPUnit->nAddrWidth, pOPUnit->nAddr);
				/* PAL Call, replace with custom implementation  */
				status = adi_a2b_I2CWriteRead((uint16)pOPUnit->nDeviceAddr, (uint16)pOPUnit->nAddrWidth, &aDataWriteReadBuf[0u], (uint16)pOPUnit->nDataCount, &aDataBuffer[0u]);
				break;

				/* Delay */
			case DELAY:
				nDelayVal = 0u;
				for(nIndex1 = 0u; nIndex1 < pOPUnit->nDataCount; nIndex1++)
				{
					nDelayVal = pOPUnit->paConfigData[nIndex1] | nDelayVal << 8u;
				}
				//(void)adi_a2b_Delay(nDelayVal);
				HAL_Delay(nDelayVal);
				break;

			default:
				break;

		}
		if (status != 0)
		{
			/* I2C read/write failed! No point in continuing! */
			break;
		}
	}

	return status;
}

/****************************************************************************/
/*!
 @brief          This function calculates reg value based on width and adds
 it to the data array

 @param [in]     pDstBuf               Pointer to destination array
 @param [in]     nAddrwidth            Data unpacking boundary(1 byte / 2 byte /4 byte )
 @param [in]     nAddr            	  Number of words to be copied

 @return          Return code
 - 0: Success
 - 1: Failure
 */
/********************************************************************************/
static void adi_a2b_Concat_Addr_Data(a2b_UInt8 pDstBuf[], a2b_UInt32 nAddrwidth, a2b_UInt32 nAddr)
{
	/* Store the read values in the place holder */
	switch (nAddrwidth)
	{ /* Byte */
		case 1u:
			pDstBuf[0u] = (a2b_UInt8)nAddr;
			break;
			/* 16 bit word*/
		case 2u:

			pDstBuf[0u] = (a2b_UInt8)(nAddr >> 8u);
			pDstBuf[1u] = (a2b_UInt8)(nAddr & 0xFFu);

			break;
			/* 24 bit word */
		case 3u:
			pDstBuf[0u] = (a2b_UInt8)((nAddr & 0xFF0000u) >> 16u);
			pDstBuf[1u] = (a2b_UInt8)((nAddr & 0xFF00u) >> 8u);
			pDstBuf[2u] = (a2b_UInt8)(nAddr & 0xFFu);
			break;

			/* 32 bit word */
		case 4u:
			pDstBuf[0u] = (a2b_UInt8)(nAddr >> 24u);
			pDstBuf[1u] = (a2b_UInt8)((nAddr & 0xFF0000u) >> 16u);
			pDstBuf[2u] = (a2b_UInt8)((nAddr & 0xFF00u) >> 8u);
			pDstBuf[3u] = (a2b_UInt8)(nAddr & 0xFFu);
			break;

		default:
			break;

	}
}
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

