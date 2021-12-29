/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*******************************************************************************

   Name       : adi_a2b_pal.c
   
   Description: This file is responsible for handling all TWI related functions.        
                 
   Functions  : a2b_I2cInit()
                a2b_I2cOpenFunc()
                a2b_I2cCloseFunc()
                a2b_I2cReadFunc()
                a2b_I2cWriteFunc()
                a2b_I2cWriteReadFunc()
                a2b_I2cShutdownFunc()
               
                 
   Prepared &
   Reviewed by: Automotive Software and Systems team, 
                IPDC, Analog Devices,  Bangalore, India
                
   @version: $Revision: 3626 $
   @date: $Date: 2015-10-05 14:04:13 +0530 (Mon, 05 Oct 2015) $
               
******************************************************************************/
/*! \addtogroup Target_Dependent Target Dependent
 *  @{
 */

/** @defgroup PAL
 *
 * This module handles all the pal CB wrappers for the underlying target
 * platform
 *
 */

/*! \addtogroup PAL
 *  @{
 */


/*============= I N C L U D E S =============*/

//#include <drivers/twi/adi_twi.h>
#include <string.h>
//#include <cdefbf527.h>
#include <stdio.h>
#include <errno.h>
#include "adi_a2b_datatypes.h"
#include "adi_a2b_framework.h"
#include "adi_a2b_externs.h"
//#include "adi_a2b_twidriver.h"
//#include "adi_a2b_timer.h"
#include "a2bplugin-slave/adi_a2b_periconfig.h"
#include "a2b/stack.h"
#include "a2b/util.h"
#include "a2b/conf.h"
#include "a2b/i2c.h"
//#include "a2bapp_bf.h"
#include "a2bplugin-master/plugin.h"
#include "plugin_priv.h"

#include "i2c.h"
#include "stm32f7xx_hal_def.h"
#include "tim.h"

/*============= D E F I N E S =============*/

/*============= D A T A =============*/

/* Pointer to Platform ECB */
//static
volatile a2b_PalEcb* pPalEcb;
A2B_PAL_L3_DATA
static a2b_UInt8 aDataBuffer[ADI_A2B_MAX_PERI_CONFIG_UNIT_SIZE];

/*============= C O D E =============*/
/*
** Function Prototype section
*/
//static
//void adi_a2b_TimerCallback(ADI_A2B_TIMER_HANDLER_PTR pTimerHandle);
//static a2b_UInt32 adi_a2b_AudioHostConfig(A2B_ECB* ecb, ADI_A2B_PERI_DEVICE_CONFIG* psDeviceConfig);

/*
** Function Definition section
*/

/*!****************************************************************************
*
*  \b              a2b_palInit
*
*  <b> API Details: </b><br>
*  Initializes the Platform Abstraction Layer (PAL) structure [function
*  pointers] with defaults for the given platform. These defaults can be
*  over-ridden as needed if necessary.
*                                                                       <br><br>
*  <b> Linux Implementation Details: </b><br>
*  This sets up all the function pointers for core PAL functionality used
*  by the A2B stack.  If A2B_FEATURE_MEMORY_MANAGER is NOT defined then
*  Linux malloc/free is used instead of the stack memory manager.  This
*  also implements some environment variable support for Linux:             <br>
*  - A2B_CONF_TRACE_CHAN_URL                                                <br>
*  - A2B_CONF_TRACE_LEVEL                                                   <br>
*  - A2B_CONF_I2C_DEVICE_PATH                                               <br>
*  - A2B_CONF_PLUGIN_SEARCH_PATTERN                                         <br>
*                                                                           <br>
*  \param          [in]    pal      Pointer to the Platform Abstraction Layer to
*                                   initialize with defaults.
*
*  \param          [in]    ecb      The environment control block (ecb) for
*                                   this platform.
*
*  \pre            None
*
*  \post           The pal function pointer API will be fully
*                  populated with default values.
*
*  \return         None
*
******************************************************************************/
A2B_PAL_L1_CODE
void
a2b_palInit
    (
    struct a2b_StackPal*    pal,
    A2B_ECB*                ecb
    )
{
    a2b_Char* envValue;

    if ( A2B_NULL != pal )
    {
        a2b_memset(pal, 0, sizeof(*pal));
        a2b_memset(ecb, 0, sizeof(*ecb));

        /* Do necessary base initialization */
        a2b_stackPalInit(pal, ecb);

#ifndef A2B_FEATURE_MEMORY_MANAGER
        /* Use Linux malloc/free */
        pal->memMgrInit      = a2b_pal_memMgrInit;
        pal->memMgrOpen      = a2b_pal_memMgrOpen;
        pal->memMgrMalloc    = a2b_pal_memMgrMalloc;
        pal->memMgrFree      = a2b_pal_memMgrFree;
        pal->memMgrClose     = a2b_pal_memMgrClose;
        pal->memMgrShutdown  = a2b_pal_memMgrShutdown;
#endif

//        pal->timerInit       = a2b_pal_TimerInitFunc;
        pal->timerGetSysTime = a2b_pal_TimerGetSysTimeFunc;
//        pal->timerShutdown   = a2b_pal_TimerShutdownFunc;

#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
        pal->logInit         = a2b_pal_logInit;
        pal->logOpen         = a2b_pal_logOpen;
        pal->logClose        = a2b_pal_logClose;
        pal->logWrite        = a2b_pal_logWrite;
        pal->logShutdown     = a2b_pal_logShutdown;
#endif

        pal->i2cInit         = a2b_pal_I2cInit;
        pal->i2cOpen         = a2b_pal_I2cOpenFunc;
        pal->i2cClose        = a2b_pal_I2cCloseFunc;
        pal->i2cRead         = a2b_pal_I2cReadFunc;
        pal->i2cWrite        = a2b_pal_I2cWriteFunc;
        pal->i2cWriteRead    = a2b_pal_I2cWriteReadFunc;
        pal->i2cShutdown     = a2b_pal_I2cShutdownFunc;

//        pal->audioInit       = a2b_pal_AudioInitFunc;
        pal->audioOpen       = a2b_pal_AudioOpenFunc;
        pal->audioClose      = a2b_pal_AudioCloseFunc;
        pal->audioConfig     = a2b_pal_AudioConfigFunc;
        pal->audioShutdown   = a2b_pal_AudioShutdownFunc;

        pal->pluginsLoad     = a2bapp_pluginsLoad;
        pal->pluginsUnload   = a2bapp_pluginsUnload;

        pal->getVersion      = a2b_pal_infoGetVersion;
        pal->getBuild        = a2b_pal_infoGetBuild;

        if ( A2B_NULL != ecb )
        {
            ecb->baseEcb.i2cAddrFmt    = A2B_I2C_ADDR_FMT_7BIT;
            ecb->baseEcb.i2cBusSpeed   = A2B_I2C_BUS_SPEED_400KHZ;
            ecb->baseEcb.i2cMasterAddr = A2B_CONF_DEFAULT_MASTER_NODE_I2C_ADDR;
        }
    }
} /* a2b_palInit */

/*****************************************************************************/
/*!
@brief  This API initializes I2C subsystem.

@param [in]:ecb  - PAL ECB structure.
  
    
@return Return code
        -1: Failure
        -0: Success
        
\note I2C and TWI terms are used  interchangeably        
  
*/   
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_UInt32 a2b_pal_I2cInit(A2B_ECB* ecb)
{
    a2b_UInt32 nReturnValue = (a2b_UInt32)0;
//    ecb->palEcb.oTWIConfig.nTWIDeviceNo = A2B_TWI_NO;
//    ecb->palEcb.oTWITimer.nTimerNo = TWI_TIMER;
    return nReturnValue;

//    A2B_UNUSED( ecb );
//    return A2B_RESULT_SUCCESS;
}

/*****************************************************************************/
/*!
@brief  This API Post Initialization of I2C subsystem and
        returns the handle

@param [in]:fmt  - 7-bit or 10-bit address.
@param [in]:speed  - I2C Bus Speed.
@param [in]:ecb  - PAL ECB structure.

@return Return code
			Handle to the I2C module

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_Handle a2b_pal_I2cOpenFunc(a2b_I2cAddrFmt fmt,
        a2b_I2cBusSpeed speed, A2B_ECB* ecb)
{
	a2b_Handle nReturnValue = 0;//NULL;
//    ecb->palEcb.oTWIConfig.a2b_fmt = fmt;
//    ecb->palEcb.oTWIConfig.i2c_speed = speed;
	nReturnValue = 1;//adi_a2b_TwiOpen(ecb, NULL);
    ecb->palEcb.i2chnd = nReturnValue;
    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API Reads a bytes of data from an I2C device

@param [in]:hnd  - Handle to the I2C Sub-system.
@param [in]:addr  - Device Address to which I2C communication
                    should happen.
@param [in]:nRead  - Number of bytes to be read.
@param [in]:rBuf  - Pointer to the buffer where read bytes are
                    to be stored.
@return Return code
        -1: Failure
        -0: Success

*/
/*****************************************************************************/
A2B_PAL_L1_CODE	/*ADI_MEM_A2B_CODE_CRIT*/
a2b_HResult a2b_pal_I2cReadFunc(a2b_Handle hnd,
        a2b_UInt16 addr, a2b_UInt16 nRead, a2b_Byte* rBuf)
{
	//a2b_HResult nReturnValue = NULL;
	HAL_StatusTypeDef nReturnValue = HAL_ERROR;
    //nReturnValue = adi_a2b_TwiRead(hnd, addr, nRead, rBuf);
	nReturnValue = HAL_I2C_Master_Receive(&hi2c1, addr<<1, rBuf, nRead, 100);

    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API writes a bytes of data to an I2C device

@param [in]:hnd  - Handle to the I2C Sub-system.
@param [in]:addr  - Device Address to which I2C communication
                    should happen.
@param [in]:Write  - Number of bytes to be written.
@param [in]:wBuf  - Pointer to the buffer from where bytes are
                    to be written.
@return Return code
        -1: Failure
        -0: Success


*/
/*****************************************************************************/
A2B_PAL_L1_CODE	/*ADI_MEM_A2B_CODE_CRIT*/
a2b_HResult a2b_pal_I2cWriteFunc(a2b_Handle hnd,
        a2b_UInt16 addr, a2b_UInt16 nWrite,
        const a2b_Byte* wBuf)
{
	//a2b_HResult nReturnValue = NULL;
	HAL_StatusTypeDef nReturnValue = HAL_ERROR;
    //nReturnValue = adi_a2b_TwiWrite(hnd, addr, nWrite, (a2b_UInt8*)wBuf);
	nReturnValue = HAL_I2C_Master_Transmit(&hi2c1, addr<<1, /*(a2b_UInt8*)*/wBuf, nWrite, 100);

    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API writes a bytes of data to an I2C device

@param [in]:hnd  - Handle to the I2C Sub-system.
@param [in]:addr  - Device Address to which I2C communication
                    should happen.
@param [in]:nWrite  - Number of bytes to be written.
@param [in]:wBuf  - Pointer to the buffer from where bytes are
                    to be written.
@param [in]:nRead  - Number of bytes to be read.
@param [in]:rBuf  - Pointer to the buffer where read bytes are
                    to be stored.
@return Return code
        -1: Failure
        -0: Success

*/
/*****************************************************************************/
A2B_PAL_L1_CODE	/*ADI_MEM_A2B_CODE_CRIT*/
a2b_HResult a2b_pal_I2cWriteReadFunc(a2b_Handle hnd,
        a2b_UInt16 addr, a2b_UInt16 nWrite,
        /*const a2b_Byte**/uint8_t* wBuf, a2b_UInt16 nRead,
        a2b_Byte* rBuf)
{
	//a2b_HResult nReturnValue = NULL;
	HAL_StatusTypeDef nReturnValue = HAL_ERROR;
    //nReturnValue = adi_a2b_TwiWriteRead(hnd, addr, nWrite, (a2b_UInt8*)wBuf, nRead, rBuf );
	nReturnValue = HAL_I2C_Master_Transmit(&hi2c1, addr<<1, wBuf, nWrite, 100);
	nReturnValue = HAL_I2C_Master_Receive(&hi2c1, addr<<1, rBuf, nRead, 100);

    return nReturnValue;
}

A2B_PAL_L1_CODE
a2b_HResult a2b_EepromWriteRead(a2b_Handle hnd, a2b_UInt16 addr, a2b_UInt16 nWrite,
        const a2b_Byte* wBuf, a2b_UInt16 nRead,
        a2b_Byte* rBuf)
{

	//a2b_HResult nReturnValue = NULL;
	HAL_StatusTypeDef nReturnValue = HAL_ERROR;
	if(hnd != 0)
    //nReturnValue = adi_a2b_TwiWriteRead(hnd, addr, nWrite, (a2b_UInt8*)wBuf, nRead, rBuf );
	nReturnValue = HAL_I2C_Master_Transmit(&hi2c1, addr<<1, wBuf, nWrite, 100);
	nReturnValue = HAL_I2C_Master_Receive(&hi2c1, addr<<1, rBuf, nRead, 100);
	return nReturnValue;


}
/*****************************************************************************/
/*!
@brief  This API initializes I2C subsystem.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE	//ADI_MEM_A2B_CODE_NO_CRIT
a2b_UInt32 a2b_pal_I2cShutdownFunc(A2B_ECB* ecb)
{
    //a2b_UInt32 nReturnValue = (a2b_UInt32)0;
    ecb->palEcb.i2chnd = NULL;
    /*return nReturnValue;

    A2B_UNUSED( ecb );*/

    return 0;//A2B_RESULT_SUCCESS;
}


/*****************************************************************************/
/*!
@brief  This API Post Initialization of I2C subsystem and
        returns the handle

@param [in]:fmt  - 7-bit or 10-bit address.
@param [in]:speed  - I2C Bus Speed.
@param [in]:ecb  - PAL ECB structure.

@return Return code
			Handle to the I2C module

*/
/*****************************************************************************/
A2B_PAL_L3_CODE	//ADI_MEM_A2B_CODE_NO_CRIT
a2b_HResult a2b_pal_I2cCloseFunc(a2b_Handle hnd)
{
	a2b_HResult nReturnValue = NULL;
//    nReturnValue = adi_a2b_TwiClose(hnd);
    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API initializes Timer subsystem.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE	//ADI_MEM_A2B_CODE_NO_CRIT
a2b_HResult a2b_pal_TimerInitFunc(A2B_ECB* ecb)
{
	pPalEcb = &ecb->palEcb;
	a2b_HResult nReturnValue = (a2b_UInt32)0;
//    a2b_UInt32  nDummy;
//    nDummy = (a2b_UInt32)&adi_a2b_TimerCallback;
//    ecb->palEcb.nCurrTime = 0u;
//    ecb->palEcb.oTimerHandler.pCallbackhandle = (TIMER_CALL_BACK)nDummy;
//    ecb->palEcb.oTimerHandler.nTimerExpireVal = 1000u;  /* One millisec counter */
//    ecb->palEcb.oTimerHandler.nTimerNo = A2B_TIMER_NO;
//    nReturnValue = adi_a2b_TimerOpen(ecb->palEcb.oTimerHandler.nTimerNo, &ecb->palEcb.oTimerHandler);
//    if(nReturnValue == 0u)
//    {
//		nReturnValue = adi_a2b_TimerStart(ecb->palEcb.oTimerHandler.nTimerNo,
//				ecb->palEcb.oTimerHandler.nTimerExpireVal);
//    }

//    HAL_TIM_Base_Start_IT(&htim10);

    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API gives the current system time

@return Return : Current time in millisec

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L1_CODE	//ADI_MEM_A2B_CODE_CRIT
a2b_UInt32 a2b_pal_TimerGetSysTimeFunc(void)
{
    //return pPalEcb->nCurrTime;
    return HAL_GetTick();
}

/****************************************************************************/
/*!
    @brief          A2B timer(timer1)call back function. It
                    is called from timer driver ISR.

    @param [in]     pTimerHandle    Pointer to Timer configuration structure

    @return         none
*/
/********************************************************************************/
A2B_PAL_L1_CODE	//ADI_MEM_A2B_CODE_CRIT
static void adi_a2b_TimerCallback(ADI_A2B_TIMER_HANDLER_PTR pTimerHandle)
{
//	a2b_HResult nReturnValue = (a2b_UInt32)0;
//	adi_a2b_TimerStop(pPalEcb->oTimerHandler.nTimerNo);
//	nReturnValue = adi_a2b_TimerStart(pPalEcb->oTimerHandler.nTimerNo,
//			pPalEcb->oTimerHandler.nTimerExpireVal);
    pPalEcb->nCurrTime += 1u;

}

/*****************************************************************************/
/*!
@brief  This API shuts the Timer subsystem.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE	//ADI_MEM_A2B_CODE_NO_CRIT
a2b_HResult a2b_pal_TimerShutdownFunc(A2B_ECB* ecb)
{
	pPalEcb = &ecb->palEcb;
	a2b_HResult nReturnValue = (a2b_UInt32)0;

//	nReturnValue = adi_a2b_TimerStop(pPalEcb->oTimerHandler.nTimerNo);
//    nReturnValue = adi_a2b_TimerClose(pPalEcb->oTimerHandler.nTimerNo);

//	ecb->palEcb.nCurrTime = 0u;
//	pPalEcb->oTimerHandler.pCallbackhandle = NULL;
//	pPalEcb->oTimerHandler.nTimerExpireVal = 0u;  /* One millisec counter */
	HAL_TIM_Base_Stop_IT(&htim10);
    return nReturnValue;
}

/*****************************************************************************/
/*!
@brief  This API Initializes the audio sub-system.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_AudioInitFunc(A2B_ECB* ecb)
{
//    a2b_UInt8 nReturn = 0xFFu;
    a2b_UInt8 nIndex;
    ADI_A2B_PERI_DEVICE_CONFIG* psDeviceConfig;
    ADI_A2B_NODE_PERICONFIG *psPeriConfig;
//    a2b_UInt8 wBuf[2];
//    a2b_UInt8 rBuf[8];

    /* A2B feature EEPROM processing */
#ifdef A2B_BCF_FROM_SOC_EEPROM
    a2b_PeripheralNode oPeriphNode, *pPeriphNode;
    a2b_HResult status = A2B_RESULT_SUCCESS;
    a2b_UInt16 nOffset = 0u, payloadLen = 0u, payloadDataLen = 0u;
    a2b_UInt8 cfgType = 0u, cfgCrc = 0u,  nCfgBlocks = 0u, regAddr = 0u, crc8 = 0u;

    nReturn 	= 0u;
    pPeriphNode = &oPeriphNode;

    /* To read the number of EEPROM */
    A2B_GET_UINT16_BE(nOffset, ecb->palEcb.pEepromAudioHostConfig , 0);
    nOffset += 3u;
    A2B_PUT_UINT16_BE(nOffset, wBuf,0);

    status  = a2b_pal_I2cWriteReadFunc( ecb->palEcb.i2chnd,A2B_I2C_EEPROM_ADDR,
                                      2u,  wBuf,
                                      1u,  &nCfgBlocks );


    A2B_GET_UINT16_BE(pPeriphNode->addr, ecb->palEcb.pEepromAudioHostConfig, 0);

    /* 4 bytes from marker */
    pPeriphNode->addr 	  += 4u;
    pPeriphNode->cfgIdx     = 0u;
    pPeriphNode->nodeAddr   = -1;
    pPeriphNode->nCfgBlocks = nCfgBlocks;

    for (pPeriphNode->cfgIdx = 0u;
         pPeriphNode->cfgIdx < pPeriphNode->nCfgBlocks;
         pPeriphNode->cfgIdx++)
    {

        /* Read the config block header bytes */
        /* [Two byte internal EEPROM address] */
        wBuf[0] = (a2b_UInt8)(pPeriphNode->addr >> 8u);
        wBuf[1] = (a2b_UInt8)(pPeriphNode->addr & 0xFFu);
        status  = a2b_pal_I2cWriteReadFunc( ecb->palEcb.i2chnd, A2B_I2C_EEPROM_ADDR,
                                          2u,  wBuf,
                                          3u,  &aDataBuffer[0u] );
        if(status != 0u)
        {
        	nReturn = 0xFFu;
			return (nReturn);
        }

        pPeriphNode->addr += 3u;
        cfgType = (aDataBuffer[0u] >> 4u);
        cfgCrc  = aDataBuffer[2];

        payloadLen = (a2b_UInt16)((a2b_UInt16)(((a2b_UInt16)aDataBuffer[0u]) << (a2b_UInt16)8u) |
                       ((a2b_UInt16)aDataBuffer[1])) & (a2b_UInt16)0xFFFu;
        payloadDataLen = payloadLen;

        /* Read the payload if needed */
        if ( (a2b_UInt8)A2B_DEALY_OP == cfgType )
        {
        	(void)adi_a2b_Delay(payloadLen);
        }
        else
        {
        	/* The cfgCrc is byte[2] which for this message
			 * it equates to the addr/reg
			 */
        	regAddr = cfgCrc;

            /* Read the payload */
            wBuf[0] = (a2b_UInt8)(pPeriphNode->addr >> 8u);
            wBuf[1] = (a2b_UInt8)(pPeriphNode->addr & 0xFFu);
            status  = a2b_pal_I2cWriteReadFunc( ecb->palEcb.i2chnd,
            								  	  A2B_I2C_EEPROM_ADDR,
												  2u, wBuf,
												  payloadLen,
												  &aDataBuffer[0u] );
            if(status != 0u)
			{
				nReturn = 0xFFu;
				return (nReturn);
			}

	        /* Write to the peripheral */
	        status = a2b_pal_I2cWriteFunc( ecb->palEcb.i2chnd,
	                                     (a2b_UInt16)regAddr,
										 payloadDataLen,
										 &aDataBuffer[0u] );
	        if(status != 0u)
			{
				nReturn = 0xFFu;
				return (nReturn);
			}

	        pPeriphNode->addr += payloadLen;
        }
    }

#else
    psPeriConfig = ecb->palEcb.pAudioHostDeviceConfig;

    /* Check with exported peripheral configuration */
    for(nIndex  = 0u; nIndex < (a2b_UInt8)psPeriConfig->nNumConfig; nIndex++)
    {
        psDeviceConfig = &psPeriConfig->aDeviceConfig[nIndex];
        //nReturn = (a2b_UInt8)adi_a2b_AudioHostConfig(ecb, psDeviceConfig);
    }
#endif
    return( 0	/*nReturn*/);

}

/*****************************************************************************/
/*!
@brief  This API Initializes the audio sub-system.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_Handle a2b_pal_AudioOpenFunc(void)
{
    /* A2B feature EEPROM processing */
#ifdef A2B_BCF_FROM_SOC_EEPROM
	return( 1u);

#else
   return (pPalEcb->pAudioHostDeviceConfig);
#endif
}

/*****************************************************************************/
/*!
@brief  This API configures the audio sub-system based on the Master
        TDM settigns

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_AudioConfigFunc(a2b_Handle hnd,
                                a2b_TdmSettings* tdmSettings)
{
	A2B_UNUSED(hnd);
	return 0;
}

/*****************************************************************************/
/*!
@brief  This API Initializes the audio sub-system.

@param [in]:hnd  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_AudioCloseFunc(a2b_Handle hnd)
{
	A2B_UNUSED(hnd);
	return 0;
}

/*****************************************************************************/
/*!
@brief  This API Initializes the audio sub-system.

@param [in]:ecb  - PAL ECB structure.


@return Return code
        -1: Failure
        -0: Success

\note I2C and TWI terms are used  interchangeably

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_AudioShutdownFunc(A2B_ECB* ecb)
{
	A2B_UNUSED(ecb);
	return 0;
}

/*****************************************************************************/
/*!
@brief  This API starts audio processing (to be called from application directly )

@param [in]:


@return Return code
        -1: Failure
        -0: Success

\note

*/
/*****************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult adi_a2b_EnableAudioHost(void)
{
	return 0;
}
/****************************************************************************/
/*!
    @brief          This function configures devices connected to slave node
                    through remote I2C

    @param [in]     pNode                   Pointer to A2B node
    @param [in]     psDeviceConfig          Pointer to peripheral device configuration structure

    @return          Return code
                    - 0: Success
                    - 1: Failure
*/
/********************************************************************************/
A2B_PAL_L3_CODE
static a2b_UInt32 adi_a2b_AudioHostConfig(A2B_ECB* ecb, ADI_A2B_PERI_DEVICE_CONFIG* psDeviceConfig)
{
	A2B_PAL_L3_DATA
    static a2b_UInt8 aDataWriteReadBuf[4u];

    a2b_UInt32 nReturn = 0u;
    ADI_A2B_PERI_CONFIG_UNIT* pOPUnit;
    a2b_UInt8 nIndex, nIndex1;
    a2b_UInt32 nNumOpUnits;
    a2b_UInt32 nDelayVal;
    a2b_Int16 nodeAddr;

    nNumOpUnits = psDeviceConfig->nNumPeriConfigUnit;

    for(nIndex= 0u ; nIndex < nNumOpUnits ; nIndex++ )
    {
        pOPUnit = &psDeviceConfig->paPeriConfigUnit[nIndex];
        /* Operation code*/
        switch(pOPUnit->eOpCode)
        {
           /* write */
            case 0u:
                    adi_a2b_Concat_Addr_Data(&aDataBuffer[0u], pOPUnit->nAddrWidth, pOPUnit->nAddr);
            	    memcpy(&aDataBuffer[pOPUnit->nAddrWidth], pOPUnit->paConfigData, pOPUnit->nDataCount);

            	    a2b_pal_I2cWriteFunc(ecb->palEcb.i2chnd, (a2b_UInt16)psDeviceConfig->nDeviceAddress,
            	    		(pOPUnit->nAddrWidth + pOPUnit->nDataCount), &aDataBuffer[0u]);
                    break;
            /* read */
            case 1u:
            	    adi_a2b_Concat_Addr_Data(&aDataWriteReadBuf[0u], pOPUnit->nAddrWidth, pOPUnit->nAddr);
            	    a2b_pal_I2cWriteReadFunc(ecb->palEcb.i2chnd, (a2b_UInt16)psDeviceConfig->nDeviceAddress,
            	    		pOPUnit->nAddrWidth, &aDataWriteReadBuf[0u],
							pOPUnit->nDataCount, &aDataBuffer[0u]);

                    break;
            /* delay */
            case 2u:nDelayVal = 0u;
			for(nIndex1 = 0u; nIndex1 < pOPUnit->nDataCount; nIndex1++)
			{
				nDelayVal = (pOPUnit->paConfigData[nIndex1] << (8u * nIndex1)) | nDelayVal;
			}
            //(void)adi_a2b_Delay(nDelayVal);
            HAL_Delay(nDelayVal);
            break;


            default: break;

        }

        if(nReturn !=0u)
        {
            break;
        }
    }

    return(nReturn);
}

/****************************************************************************/
/*!
    @brief          This function returns the Version of the A2B Stack Software

    @param [in]     major                   Major Version
    @param [in]     minor                   Minor Version
    @param [in]     release           Release number of Software

    @return          Return code
                    - 0: Success
                    - 1: Failure
*/
/********************************************************************************/
A2B_PAL_L3_CODE
void a2b_pal_infoGetVersion(a2b_UInt32* major,
        a2b_UInt32* minor,
        a2b_UInt32* release)
{
	*major = 0x1u;
	*minor = 0x0u;
	*release = 0x10000000u;
}

/****************************************************************************/
/*!
    @brief          This function returns the Version of the A2B Stack Software

    @param [in]     major                   Major Version
    @param [in]     minor                   Minor Version
    @param [in]     release           Release number of Software

    @return          Return code
                    - 0: Success
                    - 1: Failure
*/
/********************************************************************************/
A2B_PAL_L3_CODE
void a2b_pal_infoGetBuild(a2b_UInt32* buildNum,
        const a2b_Char** const buildDate,
        const a2b_Char** const buildOwner,
        const a2b_Char** const buildSrcRev,
        const a2b_Char** const buildHost)
{
	*buildNum = 0x20000000u;
}

#if defined(A2B_FEATURE_SEQ_CHART) || defined(A2B_FEATURE_TRACE)
/*!****************************************************************************
*
*  \b              a2b_pal_logInit
*
*  <b> API Details: </b><br>
*  This routine is called to do initialization the log subsystem
*  during the stack allocation process.
*
*
*
*  \param          [in]    ecb      The environment control block (ecb) for
*                                   this platform.
*
*  \pre            None
*
*  \post           None
*
*  \return         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_logInit(A2B_ECB*   ecb)
{
	a2b_UInt8 i = 0u;
	for(i=0; i<(A2B_TOTAL_LOG_CH); i++)
	{
		ecb->palEcb.oLogConfig[i].fd = A2B_INVALID_FD;
		ecb->palEcb.oLogConfig[i].inUse = false;
	}
	return A2B_RESULT_SUCCESS;
}

/*!****************************************************************************
*
*  \b              a2b_pal_logShutdown
*
*  <b> API Details: </b><br>
*  This routine is called to shutdown the log subsystem
*  during the stack destroy process.  This routine is called immediately
*  after the a2b_pal_logClose (assuming the close was successful).
*
*
*  \param          [in]    ecb      The environment control block (ecb) for
*                                   this platform.
*
*  \pre            None
*
*  \post           None
*
*  \return         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_logShutdown(A2B_ECB* ecb)
{
    A2B_UNUSED(ecb);
    return A2B_RESULT_SUCCESS;
} /* pal_logShutdown */


/*!****************************************************************************
*
*  \b              a2b_pal_logOpen
*
*  This routine is called to do post-initialization the log subsystem
*  during the stack allocation process.  This routine is called immediately
*  after the pal_logInit (assuming the init was successful).
*
*
*
*  \param          [in]    ecb      The environment control block (ecb) for
*                                   this platform.
*
*  \pre            None
*
*  \post           None
*
*  \return         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_Handle a2b_pal_logOpen(const a2b_Char* url)
{
	a2b_UInt8 i = 0u;
	a2b_HResult nHandle = 0U;

	if ( A2B_NULL != url )
	{
		for(i=0; i<(A2B_TOTAL_LOG_CH); i++)
		{
			if(!pPalEcb->oLogConfig[i].inUse)
			{
				pPalEcb->oLogConfig[i].fd = (a2b_UInt32)fopen(url, "w");
				nHandle = (a2b_HResult)&pPalEcb->oLogConfig[i];
				pPalEcb->oLogConfig[i].inUse = true;
				break;
			}
		}
	}

	return nHandle;
}

/*!****************************************************************************
*
*  \b              a2b_pal_logClose
*
*  This routine is called to de-initialization the log subsystem
*  during the stack destroy process.
*
*
*
*  \param          [in]    ecb      The environment control block (ecb) for
*                                   this platform.
*
*  \pre            None
*
*  \post           None
*
*  \return         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_logClose(a2b_Handle  hnd)
{
	a2b_UInt8 i = 0u;
	a2b_HResult nResult = 0xFFFFFFFFU;
	A2B_LOG_INFO *pLogInfo;

	if ( A2B_NULL != hnd )
	{
		pLogInfo = (A2B_LOG_INFO *)hnd;

		fclose(pLogInfo->fd);
		pLogInfo->fd = A2B_INVALID_FD;
		pLogInfo->inUse = false;
		nResult = A2B_RESULT_SUCCESS;
	}

	return nResult;
}

/*!****************************************************************************
*
*  \b              a2b_pal_logWrite
*
*  <b> API Details: </b><br>
*  This routine writes to a log channel.
*
*
*  \param          [in]    hnd      The handle returned from pal_logOpen
*
*  \param          [in]    msg      NULL terminated string to log
*
*  \pre            None
*
*  \post           None
*
*  \return         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L1_CODE
a2b_HResult a2b_pal_logWrite(
    a2b_Handle      hnd,
    const a2b_Char* msg)
{
	a2b_HResult nResult = 0xFFFFFFFFu;
	a2b_UInt32 msg_len = 0u;
	A2B_LOG_INFO *pLogInfo;
	a2b_Char* newline = "\n";

	if ( (A2B_NULL != hnd) && (A2B_NULL != msg) )
	{
		strcat((char *__restrict__)msg, (char *__restrict__)newline);
		pLogInfo = (A2B_LOG_INFO *)hnd;
		msg_len = a2b_strlen(msg) * sizeof(a2b_Char);
		fwrite(msg, 1, msg_len, pLogInfo->fd);
		nResult = A2B_RESULT_SUCCESS;
	}
	return nResult;
}
#endif

#if !defined(A2B_FEATURE_MEMORY_MANAGER)
 /*!****************************************************************************
*
*  a2b_pal_memMgrInit
*
*  This routine is called to do initialization required by the memory manager
*  service during the stack [private] allocation process.
*
*  return:         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_memMgrInit(A2B_ECB *ecb)
{
    A2B_UNUSED( ecb );
    return A2B_RESULT_SUCCESS;
}


/*!****************************************************************************
*
*  a2b_MemMgrOpenFunc
*
*  This routine opens a memory managed heap located at the specified address
*  and of the specified size. If the A2B stack's heap cannot be opened and
*  managed at the specified location (perhaps because the size is insufficient)
*  then the returned handle will be A2B_NULL. The managed heap will use
*  memory pools to avoid fragmentation within the managed region.
*
*  return:         If non-zero the open was considered sucessfully.  If A2B_NULL
*                  I2C initialization must have failed and the stack
*                  allocation will fail.  This returned handle will be passed
*                  back into the other PAL I2C (pal_memMgrXXX) API calls.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_Handle a2b_MemMgrOpenFunc(a2b_Byte *heap, a2b_UInt32  heapSize)
{
    A2B_UNUSED( heap );
    A2B_UNUSED( heapSize );

    /* MUST be a non-NULL value -- Dummy value */
    return (a2b_Handle)1;
}


/*!****************************************************************************
*
*  a2b_pal_memMgrMalloc
*
*  This routine is called to get/allocate a fixed amount of memory.
*
*  return:         Returns an aligned pointer to memory or A2B_NULL if memory
*                  could not be allocated.
*
******************************************************************************/
A2B_PAL_L1_CODE
void *a2b_pal_memMgrMalloc(a2b_Handle  hnd, a2b_UInt32  size)
{
    A2B_UNUSED( hnd );
    A2B_UNUSED( size );

    return A2B_NULL;
}


/*!****************************************************************************
*
*  a2b_pal_memMgrFree
*
*  This routine is called to free previously allocated memory.
*
*  return:         None
*
******************************************************************************/
A2B_PAL_L1_CODE
void a2b_pal_memMgrFree(a2b_Handle  hnd, void *p)
{
    A2B_UNUSED( hnd );
    A2B_UNUSED( p );
}


/*!****************************************************************************
*
*  a2b_pal_memMgrClose
*
*  This routine is called to de-initialization the memory management subsystem
*  during the stack destroy process.  All resources associated with the
*  heap are freed.
*
*  return:         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_memMgrClose(a2b_Handle  hnd)
{
    A2B_UNUSED( hnd );
    return A2B_RESULT_SUCCESS;
}


/*!****************************************************************************
*
*  a2b_pal_memMgrShutdown
*
*  This routine is called to shutdown the memory manager subsystem
*  during the stack destroy process.  This routine is called immediately
*  after the adi_a2b_pal_memMgrClose (assuming the close was successful).
*
*  return:         A status code that can be checked with the A2B_SUCCEEDED()
*                  or A2B_FAILED() for success or failure.
*
******************************************************************************/
A2B_PAL_L3_CODE
a2b_HResult a2b_pal_memMgrShutdown(A2B_ECB*    ecb)
{
    A2B_UNUSED( ecb );
    return A2B_RESULT_SUCCESS;
}
#endif /* A2B_FEATURE_MEMORY_MANAGER */
/** 
 @}
*/

/**
 @}
*/

                        
/*
**
** EOF: $URL$
**
*/


