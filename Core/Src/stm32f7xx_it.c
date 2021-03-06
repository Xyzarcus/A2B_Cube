/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adi_a2b_externs.h"
#include "a2bapp.h"

#include "string.h"
#include "a2bplugin-slave/adi_a2b_periconfig.h"
#include "a2b/regdefs.h"
#include "a2bplugin-slave/plugin.h"
#include "plugin_priv.h"
#include "a2b/stack.h"
#include "a2b/i2c.h"
#include "a2b/error.h"
#include "adi_a2b_datatypes.h"
#include "a2b/timer.h"
#include "a2b/util.h"
#include "a2b/trace.h"
#include "a2b/interrupt.h"
#include "a2b/i2c.h"
#include "a2b/timer.h"
#include "a2b/regdefs.h"
#include "a2b/seqchart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/*static*/
extern volatile a2b_PalEcb* pPalEcb;
extern a2b_App_t gApp_Info;

volatile int time5ms=0;//time10ms=0;
extern uint8_t vol[];
extern uint8_t seek_up[];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_sdmmc1_rx;
extern DMA_HandleTypeDef hdma_sdmmc1_tx;
extern SD_HandleTypeDef hsd1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim10;
/* USER CODE BEGIN EV */

bool enc_btn=false;
uint16_t enc_btn_cnt = 0;
bool enc_left=false, enc_right=false;
uint16_t enc_left_cnt = 0, enc_right_cnt = 0, enc_rotated_cnt = 0;
bool enc_rotated = false;
uint16_t enc_last = 5000;
uint16_t enc_current = 5000;
uint16_t enc_mark = 5000;
int16_t enc_change = 0;

bool brd_btn=false;
uint16_t brd_btn_cnt = 0;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  if (enc_btn)
  {
	  if (!HAL_GPIO_ReadPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin))
	  {
		  enc_btn_cnt++;
	  }
	  else
	  {
		  enc_btn_cnt=0;
		  enc_btn = false;
	  }
  }
  if (enc_btn_cnt>15)
  {
	enc_btn_cnt=0;
	enc_btn = false;

	printf("ENC_BTN\t\t");

	struct a2b_Msg *msg;
	a2b_HResult result;
	//a2b_UInt32 *data;
	a2b_UInt16 slaveNode = 1;
	a2b_radioEventInfo* radioEvt;


	msg = a2b_msgAlloc(gApp_Info.ctx, A2B_MSG_REQUEST, A2B_MSGREQ_RADIO);
	if (msg != A2B_NULL)
	{
		//data = (a2b_UInt32 *)a2b_msgGetPayload(msg);
		//*data = 0xABCDABCD;
		//a2b_msgSetUserData( msg, (a2b_Handle)a2b_Custom2, A2B_NULL );
		//a2b_Custom2	; \t%d\t%d\n\r", sizeof(a2b_msgGetUserData(msg)), sizeof(a2b_msgGetUserData(msg))/sizeof(a2b_msgGetUserData(msg)[0])
		radioEvt->pwBuf=seek_up;
		radioEvt->nDataSz= 2;
		a2b_msgSetUserData(msg, radioEvt, A2B_NULL);
		result = a2b_msgRtrSendRequest(msg, slaveNode, NULL);
		a2b_msgUnref(msg);
	}
  }


  if (enc_rotated)
	  enc_rotated_cnt++;
  if (enc_rotated_cnt>15)
  {
	enc_rotated=false;
	enc_rotated_cnt=0;
	//printf("enc_mark=%d, enc_current=%d\t", enc_mark, enc_current);
  	enc_change = enc_current-enc_mark;
  	//printf("enc_change=%d\t", enc_change);
  	enc_mark=enc_current;

  	printf("ENC_ROT\t\t");

	struct a2b_Msg *msg;
	a2b_HResult result;
	//a2b_UInt32 *data;

	a2b_UInt16 slaveNode = 1;
	a2b_radioEventInfo* radioEvt;

	msg = a2b_msgAlloc(gApp_Info.ctx, A2B_MSG_REQUEST, A2B_MSGREQ_RADIO);
	if (msg != A2B_NULL)
	{
		if (enc_change>0)
		{
			if (vol[5]+enc_change<=63)
				vol[5]+=enc_change;
			else
				vol[5]=63;

		}
		if (enc_change<0)
		{
			if (vol[5]+enc_change>=0)
				vol[5]+=enc_change;
			else
				vol[5]=0;
		}
		printf("%d\t",vol[5]);

		radioEvt->pwBuf=vol;
		radioEvt->nDataSz= 6;
		a2b_msgSetUserData(msg, radioEvt, A2B_NULL);
		result = a2b_msgRtrSendRequest(msg, slaveNode, NULL);
		a2b_msgUnref(msg);
	}

  }


  if (brd_btn)
  {
	  if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
	  {
		  brd_btn_cnt++;
	  }
	  else
	  {
		  brd_btn_cnt=0;
		  brd_btn = false;
	  }
  }

  if (brd_btn_cnt>15)
  {
	  brd_btn_cnt=0;
	  brd_btn = false;

	  printf("BRD_BTN\t\t\t");

	  struct a2b_Msg *msg;
	  a2b_HResult result;
	  a2b_UInt32 *data;
	  a2b_UInt16 slaveNode = 0;
	  //a2b_radioEventInfo* radioEvt;


	  msg = a2b_msgAlloc(gApp_Info.ctx, A2B_MSG_REQUEST, A2B_MSGREQ_LED);
	  if (msg != A2B_NULL)
	  {
		  data = (a2b_UInt32 *)a2b_msgGetPayload(msg);
		  *data = 0xABCDABCD;
		  //a2b_msgSetUserData( msg, (a2b_Handle)a2b_Custom2, A2B_NULL );
		  //a2b_Custom2	; \t%d\t%d\n\r", sizeof(a2b_msgGetUserData(msg)), sizeof(a2b_msgGetUserData(msg))/sizeof(a2b_msgGetUserData(msg)[0])
		  //radioEvt->pwBuf=seek_up;
		  //radioEvt->nDataSz= 2;
		  //a2b_msgSetUserData(msg, radioEvt, A2B_NULL);
		  result = a2b_msgRtrSendRequest(msg, slaveNode, NULL);
		  a2b_msgUnref(msg);
	  }
  }

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(MCO_Pin);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  enc_btn=true;
  //printf("EXTI0\r\n");

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim10);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */
  //HAL_GPIO_TogglePin(LD2_Blue_GPIO_Port, LD2_Blue_Pin);

  if (LD_Red_time) 		LD_Red_time--;
  if (LD_Green_time)  	LD_Green_time--;
  if (LD_Blue_time)		LD_Blue_time--;

  if (LD_Red_time)
	  HAL_GPIO_WritePin(LD_Red_GPIO_Port, LD_Red_Pin, GPIO_PIN_SET);
  else
	  HAL_GPIO_WritePin(LD_Red_GPIO_Port, LD_Red_Pin, GPIO_PIN_RESET);

  if (LD_Green_time)
	  HAL_GPIO_WritePin(LD_Green_GPIO_Port, LD_Green_Pin, GPIO_PIN_SET);
  else
	  HAL_GPIO_WritePin(LD_Green_GPIO_Port, LD_Green_Pin, GPIO_PIN_RESET);

  if (LD_Blue_time)
	  HAL_GPIO_WritePin(LD_Blue_GPIO_Port, LD_Blue_Pin, GPIO_PIN_SET);
  else
	  HAL_GPIO_WritePin(LD_Blue_GPIO_Port, LD_Blue_Pin, GPIO_PIN_RESET);


  pPalEcb->nCurrTime += 1u;

  if (time5ms == 5)//(time10ms == 10)
  {
	  HAL_GPIO_WritePin(LD_Blue_GPIO_Port, LD_Blue_Pin, GPIO_PIN_SET);
	  time5ms=0;//time10ms=0;
	  //a2b_stackTick(gApp_Info.ctx);
	  HAL_GPIO_WritePin(LD_Blue_GPIO_Port, LD_Blue_Pin, GPIO_PIN_RESET);
  }
  time5ms++;//time10ms++;


  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */


  //printf("TIM3\r\n");
  //printf("%d\r\n",(int)__HAL_TIM_GET_COUNTER(&htim3));
  enc_current = (int)__HAL_TIM_GET_COUNTER(&htim3);
  if (enc_current!=enc_last)
  {
	  enc_rotated=true;

  }
//  if (enc_current<enc_last)
//  {
//	  enc_left=true;
//  }
//  else
//  {
//	  enc_right=true;
//  }
  enc_last = enc_current;

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  //printf("EXTI15-10\r\n");
  brd_btn=true;
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles SDMMC1 global interrupt.
  */
void SDMMC1_IRQHandler(void)
{
  /* USER CODE BEGIN SDMMC1_IRQn 0 */

  /* USER CODE END SDMMC1_IRQn 0 */
  HAL_SD_IRQHandler(&hsd1);
  /* USER CODE BEGIN SDMMC1_IRQn 1 */

  /* USER CODE END SDMMC1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream3 global interrupt.
  */
void DMA2_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream3_IRQn 0 */

  /* USER CODE END DMA2_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdmmc1_rx);
  /* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

  /* USER CODE END DMA2_Stream3_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream6 global interrupt.
  */
void DMA2_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream6_IRQn 0 */

  /* USER CODE END DMA2_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdmmc1_tx);
  /* USER CODE BEGIN DMA2_Stream6_IRQn 1 */

  /* USER CODE END DMA2_Stream6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

