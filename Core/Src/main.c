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
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdmmc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adi_initialize.h"
#include "adi_a2b_externs.h"
#include "adi_a2b_busconfig.h"
#include "a2bapp_defs.h"
#include <errno.h>
#include <string.h>
#include "a2b/pluginapi.h"

#include <assert.h>
#include <stdio.h>
#include "..\adi_a2b_datatypes.h"
#include "adi_a2b_commch_interface.h"

#ifdef A2B_FEATURE_COMM_CH
#include "adi_a2b_commch_appinterface.h"
#endif
#include "plugin_priv.h"
#include <a2bapp.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//#define PUSH_BUTTON1_PORT      (ADI_GPIO_PORT_A)	  /*!< GPIO port to which push button 1 is connected to */
//#define PUSH_BUTTON2_PORT      (ADI_GPIO_PORT_B)	  /*!< GPIO port to which push button 2 is connected to */
//
//#define PUSH_BUTTON1_PINT      (ADI_GPIO_PIN_INTERRUPT_0)	/*!< GPIO pint to which push button 1 is connected to */
//#define PUSH_BUTTON2_PINT      (ADI_GPIO_PIN_INTERRUPT_0)	/*!< GPIO port to which push button 2 is connected to */
//
//#define PUSH_BUTTON1_PIN       (ADI_GPIO_PIN_15)	  /*!< GPIO pin within the port to which push button 1 is connected to */
//#define PUSH_BUTTON2_PIN       (ADI_GPIO_PIN_0)	  	  /*!< GPIO pin within the port to which push button 2 is connected to */
//
//#define PUSH_BUTTON1_PINT_PIN  (ADI_GPIO_PIN_31)	  /*!< pin within the pint to which push button 1 is connected to */
//#define PUSH_BUTTON2_PINT_PIN  (ADI_GPIO_PIN_0)		  /*!< pin within the pint to which push button 2 is connected to */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/*static*/ a2b_App_t gApp_Info;
a2b_UInt8 CurrNode;

char __argv_string[] = "";

//uint32_t				goGpioMem[16*3];
//volatile a2b_Bool		gbPb1Pressed = false;
//volatile a2b_Bool		gbPb2Pressed = false;

uint16_t LD_Red_time=0;
uint16_t LD_Green_time=0;
uint16_t LD_Blue_time=0;

extern uint16_t enc_last;

//_g_r_g_w	//PCA9632
//01010101
uint8_t leds_off[]={0x08,0x00};
uint8_t led_red[]={0x08,0x10};
uint8_t led_green[]={0x08,0x04};
uint8_t led_write[]={0x08,0x01};
uint8_t msg_data0[]={0x08,0x51};//{0x08,0x05};
uint8_t msg_data1[]={0x08,0x55};
uint8_t msg_data2[]={0x08,0x05};
uint8_t msg_data3[]={0x08,0x50};


uint8_t vol[] = {0x12, 0x00, 0x40, 0x00, 0x00, 0x1F};
uint8_t seek_up[] = {0x21,0x0C};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

//void  adi_a2b_Delay(a2b_UInt32 nTime);
#ifdef A2B_FEATURE_COMM_CH
static void 			a2b_HandleCommChRxMsg(uint8 nMsgId, uint16 nMsgLenInBytes, uint8* pMsgPayload);
//static void 			PushButtons_Init(void);
//static ADI_GPIO_RESULT 	PushButtons_Setup(ADI_GPIO_PORT	ePbPort, uint32_t nPbPin, ADI_GPIO_PIN_INTERRUPT  ePbPinInt, uint32_t  nPbPinIntPin, ADI_GPIO_CALLBACK pfCallback);
//static void 			GpioCallback(ADI_GPIO_PIN_INTERRUPT ePinInt, uint32_t Data, void *pCBParam);
#endif
static void a2b_LED_toggle(struct a2b_Msg* msg);

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
  MX_TIM3_Init();
  MX_SDMMC1_SD_Init();
  MX_DMA_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  FRESULT res; // FatFs function common result code
  uint32_t byteswritten, bytesread; // File write/read counts
  uint8_t wtext[] = "STM32 FATFS works great!"; // File write buffer
  uint8_t rtext[_MAX_SS];// File read buffer



  if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
  {
	  A2B_APP_LOG("SD mount error\r\n");
	  //Error_Handler();
  }
  else
  {
	  A2B_APP_LOG("SD mounted\r\n");
	  /*if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext)) != FR_OK)
	  {
		  Error_Handler();
	  }
	  else
	  {
			//Open file for writing (Create)
			if(f_open(&SDFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
			{
				Error_Handler();
			}
			else
			{

				//Write to the text file
				res = f_write(&SDFile, wtext, strlen((char *)wtext), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					Error_Handler();
				}
				else
				{

					f_close(&SDFile);
				}
			}
	  }*/
  }
  //f_mount(&SDFatFS, (TCHAR const*)NULL, 0);


  gApp_Info.bDebug = true;
  //gApp_Info->pTargetProperties->bLineDiagnostics = 1;
  //gApp_Info->pTargetProperties->nAttemptsCriticalFault = 5;
  //HAL_DBGMCU_EnableDBGStandbyMode();
  DBGMCU->APB2FZ |= DBGMCU_APB2_FZ_DBG_TIM10_STOP;
  HAL_TIM_Base_Start_IT(&htim10);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);


  __HAL_TIM_SET_COUNTER(&htim3, enc_last);

  TIM3->SMCR &= ~(TIM_SMCR_TS_0 | TIM_SMCR_TS_1); /* 100: TI1 Edge Detector (TI1F_ED) */
  TIM3->SMCR |= TIM_SMCR_TS_2;

  TIM3->DIER |= TIM_DIER_TIE;/* 1: Trigger interrupt enabled. */
  NVIC_EnableIRQ(TIM3_IRQn);

  a2b_UInt32 nResult = 0;
  bool bRunFlag = true;

//  XfadePayload 	oXfadeData;
//  A2B_COMMCH_RET 	eCommChRet;

//  adi_initComponents();

//  nResult = adi_a2b_SystemInit(); 		/* system/platform specific initialization */
//  if(nResult != 0)
//	  assert(nResult == 0);

  /* A2B Network Setup. Performs discovery and configuration of A2B nodes and its peripherals */
  nResult = a2b_setup(&gApp_Info);
  if (nResult)
  {
	  CurrNode = gApp_Info.faultNode;
	  printf("Currently found node number is:%d\n", CurrNode);
	  assert(nResult == 0);				/* failed to setup A2B network */
  }

//  A2B_COMMCH_RET eRet = A2B_COMMCH_SUCCESS;
//  eRet = adi_a2b_app_CommChInit();

//  uint8_t err_reg=0x02;//{0x17};
//  uint8_t err_answ=0x0;
  //eRet = adi_a2b_app_CommChSendMsg(a2b_UInt8 nMsgId, a2b_UInt16 nMsgLenInBytes, a2b_UInt8* pMsgPayload, int16 nNodeAddr);

//  struct a2b_StackContext *ctx; /*!< Stack context already initialized */
//  a2b_CommChMsg oCommChTxMsg; /*!< Communication Channel message frame to be transmitted */

  //a2b_LED_toggle(struct a2b_Msg* msg);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	a2b_stackTick(gApp_Info.ctx);					/* tick keeps all process rolling.. so keep ticking */
	nResult = a2b_fault_monitor(&gApp_Info);		/* Monitor a2b network for faults and initiate re-discovery if enabled */
	/*-----------------------------------------------------------*/
	/* Add your other continuous monitoring application code here */
	/*-----------------------------------------------------------*/
	if (nResult != 0)
		bRunFlag = false;							/* condition to exit the program */

	//a2b_i2cPeriphWrite(struct a2b_StackContext* ctx, a2b_Int16 node, a2b_UInt16 i2cAddr, a2b_UInt16 nWrite, void* wBuf)
//	a2b_i2cPeriphWrite(gApp_Info.ctx, 0, 0x70, sizeof(msg_data0), led_green);
//	HAL_Delay(300);
//	a2b_i2cPeriphWrite(gApp_Info.ctx, 0, 0x70, sizeof(msg_data1), led_red);
//	HAL_Delay(300);


//	#define A2B_MSG_MY_MESSAGE (A2B_MSGREQ_CUSTOM + 1)
//
//	struct a2b_Msg *msg;
//	a2b_HResult result;
//	a2b_UInt32 *data;
//	a2b_UInt16 slaveNode = 1;
//
//	msg = a2b_msgAlloc(a2b>ctx, A2B_MSG_REQUEST, A2B_MSG_MY_MESSAGE);
//	if (msg != A2B_NULL)
//	{
//		data = (a2b_UInt32 *)a2b_msgGetPayload(msg);
//		*data = 0xABCDABCD;
//		result = a2b_msgRtrSendRequest(msg, slaveNode, NULL);
//		a2b_msgUnref(msg);
//	}






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


#ifdef A2B_FEATURE_COMM_CH
/***********************************************************************************/
/*!
    @brief          This is the call from Communication channel Application wrapper
    				for a new event

    @param [in]     nMsgId       	Message Id.
    @param [in]     nMsgLenInBytes  Message Length in Bytes
    @param [in]     pMsgPayload     Message Payload
    @param [in]     nNodeAddr       Node Address
    @param [in]     eEventType      Event Type

    @return         Return code
                    - 0: Success
                    - 1: Failure
*/
/***********************************************************************************/
void adi_a2b_app_CommChCallBk(uint8 nMsgId, uint16 nMsgLenInBytes, uint8* pMsgPayload, int16 nNodeAddr, A2B_COMMCH_EVENT eEventType)
{
	switch (eEventType)
	{
		case A2B_COMMCH_EVENT_RX_MSG: /* Action based on message Id */
			a2b_HandleCommChRxMsg(nMsgId, nMsgLenInBytes, pMsgPayload);
			//memcpy(&payload[0], pCommChEventInfo->pRxMsg->pMsgPayload, pCommChEventInfo->pRxMsg->nMsgLenInBytes);
			break;

		case A2B_COMMCH_EVENT_TX_DONE: /* Actions post Tx confirmation */
			break;

		case A2B_COMMCH_EVENT_TX_TIMEOUT: /* Tx timeout */
			break;

		case A2B_COMMCH_EVENT_FAILURE: /* Failure condition */
			break;
	}
}

/***********************************************************************************/
/*!
    @brief          This function handles various messages over Communication channel

    @param [in]     nMsgId       	Message Id.
    @param [in]     nMsgLenInBytes  Message Length in Bytes
    @param [in]     pMsgPayload     Message Payload

    @return         Return code
                    - 0: Success
                    - 1: Failure
*/
/***********************************************************************************/
static void a2b_HandleCommChRxMsg(uint8 nMsgId, uint16 nMsgLenInBytes, uint8* pMsgPayload)
{
	switch(nMsgId)
	{
		case A2B_COMMCH_MSG_RSP_XFADE_AUDIO_SRC:
			break;

		default:
			break;

	}
}

//static void PushButtons_Init(void)
//{
//    ADI_GPIO_RESULT 		eResult;
//    uint32_t 				nGpioMaxCallbacks;
//
//    eResult = adi_gpio_Init(goGpioMem, (16*3), &nGpioMaxCallbacks);
//
//    eResult = PushButtons_Setup(PUSH_BUTTON1_PORT,
//								PUSH_BUTTON1_PIN,
//								PUSH_BUTTON1_PINT,
//								PUSH_BUTTON1_PINT_PIN,
//								GpioCallback);
//
//    /* Setup Push Button 2 */
//    eResult = PushButtons_Setup(PUSH_BUTTON2_PORT,
//								PUSH_BUTTON2_PIN,
//								PUSH_BUTTON2_PINT,
//								PUSH_BUTTON2_PINT_PIN,
//								GpioCallback);
//
//    if(eResult != ADI_GPIO_SUCCESS)
//    {
//
//    }
//}
//
//static ADI_GPIO_RESULT PushButtons_Setup(ADI_GPIO_PORT			ePbPort,
//										uint32_t      			nPbPin,
//										ADI_GPIO_PIN_INTERRUPT  ePbPinInt,
//										uint32_t                nPbPinIntPin,
//										ADI_GPIO_CALLBACK 		pfCallback)
//{
//	ADI_GPIO_RESULT eResult;
//
//    /* set GPIO input */
//    eResult = adi_gpio_SetDirection(ePbPort, nPbPin, ADI_GPIO_DIRECTION_INPUT);
//    /* set input edge sense */
//    eResult = adi_gpio_SetPinIntEdgeSense(ePbPinInt, nPbPinIntPin, ADI_GPIO_SENSE_RISING_EDGE);
//    /* register gpio callback */
//    eResult = adi_gpio_RegisterCallback(ePbPinInt, nPbPinIntPin, pfCallback, (void*)NULL);
//	/* enable interrupt mask */
//	eResult = adi_gpio_EnablePinInterruptMask(ePbPinInt, nPbPinIntPin, true);
//
//	return (eResult);
//}
//static void GpioCallback(ADI_GPIO_PIN_INTERRUPT ePinInt, uint32_t Data, void *pCBParam)
//{
//    if (ePinInt == PUSH_BUTTON1_PINT)
//    {
//        if (Data & PUSH_BUTTON1_PINT_PIN)
//        {
//        	gbPb1Pressed = true;
//        }
//    }
//
//    if (ePinInt == PUSH_BUTTON2_PINT)
//    {
//    	if (Data & PUSH_BUTTON2_PINT_PIN)
//        {
//    		gbPb2Pressed = true;
//        }
//    }
//}
#endif


static
void
a2b_LED_toggle
    (
    struct a2b_Msg* msg
    )
{
    a2b_Int32 retCode = A2B_EXEC_COMPLETE;

    a2b_Plugin* plugin   = (a2b_Plugin*)a2b_msgGetUserData( msg );
    a2b_UInt32  nodeAddr = a2b_msgGetTid( msg );
    a2b_UInt32* payload = (a2b_UInt32*)a2b_msgGetPayload( msg );
    a2b_UInt8 nCfgBlocks = 0u;
    a2b_PeripheralNode* periphNode;


	a2b_i2cPeriphWrite(gApp_Info.ctx, 0, 0x70, sizeof(msg_data2), msg_data2);
	HAL_Delay(100);
	//(void)a2b_ActiveDelay(plugin->ctx, 100);
	a2b_i2cPeriphWrite(gApp_Info.ctx, 0, 0x70, sizeof(msg_data3), msg_data3);
	HAL_Delay(100);
	//(void)a2b_ActiveDelay(plugin->ctx, 100);

//    if ( payload )
//    {
//        nCfgBlocks = (a2b_UInt8)payload[0];
//    }

//    A2B_DSCVRY_SEQGROUP1( plugin->ctx,
//                          "periphCfgStartProcessing for nodeAddr %hd",
//                          &nodeAddr );
//
//    if ( nCfgBlocks == 0u )
//    {
//        A2B_DSCVRY_WARN0( plugin->ctx, "periphCfgStartProcessing",
//                          "EEPROM Cfg Blocks is Zero" );
//        A2B_DSCVRY_SEQEND( plugin->ctx );
//        return A2B_EXEC_COMPLETE;
//    }
//
//    A2B_DSCVRYNOTE_DEBUG1( plugin->ctx, "periphCfgStartProcessing",
//                           "Start Processing %bd Cfg Blocks",
//                           &nCfgBlocks );
//
//    periphNode = A2B_GET_PERIPHNODE( plugin, nodeAddr );
//
//#ifdef A2B_BCF_FROM_SOC_EEPROM
//
//        A2B_GET_UINT16_BE(periphNode->addr, plugin->periphCfg.pkgCfg, 2u* nodeAddr);
//        /* 4 bytes from marker */
//        periphNode->addr 	  += 4u;
//        periphNode->cfgIdx     = 0u;
//        periphNode->nodeAddr   = nodeAddr;
//        periphNode->nCfgBlocks = nCfgBlocks;
//
//#else
//		periphNode->addr       = 0x0008u;
//		periphNode->cfgIdx     = 0u;
//		periphNode->nodeAddr   = (a2b_Int16)nodeAddr;
//		periphNode->nCfgBlocks = nCfgBlocks;
//#endif
//    /* Change so the execution flow will change */
//    (void)a2b_msgSetCmd( msg, A2B_MPLUGIN_CONT_PERIPH_CFG );
//
//    /* Begin processing all peripheral configuration blocks */
//    retCode = a2b_periphCfgProcessing( plugin, (a2b_Int16)nodeAddr );
//
//    A2B_DSCVRY_SEQEND( plugin->ctx );

//    return retCode;

} /* a2b_periphCfgStartProcessing */







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
  f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
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

