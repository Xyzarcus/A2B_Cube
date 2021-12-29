/*******************************************************************************
Copyright (c) 2018 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
* @file: adi_a2b_nodeconfig.h
* @brief: This file contains macros and structure definitions used for slave node configuration
* @version: $Revision$
* @date: $Date$
* BCF Version - 1.0.0
* Developed by: Automotive Software and Systems team, Bangalore, India
* THIS IS A SIGMASTUDIO GENERATED FILE AND SHALL NOT BE MODIFIED OUTSIDE OF SIGMASTUDIO
*****************************************************************************/

#ifndef _ADI_A2B_NODECONFIG_H_
#define _ADI_A2B_NODECONFIG_H_

/*! \addtogroup Network_Configuration Network Configuration
* @{
*/

/** @defgroup Node_Configuration
*
* This module has structure definitions to describe SigamStudio exported slave node configuration/description file.
* The exported slave node configuration is interpreted using the structure \ref ADI_A2B_NCD.
*
*/

/*! \addtogroup Node_Configuration  Node Configuration
* @{
*/

/*
	Terms Usage
	BCF - Bus Configuration File
	NCF - Node Configuration File

	BCD  - Bus Configuration Data
	NCD  - Node Configuration Data

*/
/*======================= I N C L U D E S =========================*/
#include "adi_a2b_datatypes.h"

/*============= D E F I N E S =============*/

#define ADI_A2B_MAX_DEVICES_PER_NODE				(16u)

#define ADI_A2B_MAX_PERI_CONFIG_UNIT_SIZE			(6000u)

/* Diffrent types of peripheral device  */
#define A2B_AUDIO_SOURCE							(0u)
#define A2B_AUDIO_SINK								(1u)
#define A2B_AUDIO_UNKNOWN							(2u)
#define A2B_AUDIO_SOURCE_SINK						(3u)
#define A2B_AUDIO_HOST								(4u)
#define A2B_GENERIC_I2C_DEVICE						(5u)

/* I2S operational codes */
#define A2B_WRITE_OP								(0u)
#define A2B_READ_OP									(1u)
#define A2B_DEALY_OP								(2u)

#define ENABLED										(1u)
#define DISABLED									(0u)

#define A2B_HIGH									(1u)
#define A2B_LOW										(0u)
#define A2B_IGNORE									(2u)

#define RAISING_EDGE								(0u)
#define FALLING_EDGE								(1u)

/**************************************************** STRUCTURE DEFINITION *****************************/

/*! \enum ADI_A2B_PARTNUM
    Possible A2B part numbers
 */
typedef enum
{
 /*!  Enum forAD2410  */
    ADI_A2B_AD2410,
  /*!  Enum forAD2401  */
    ADI_A2B_AD2401,
/*!  Enum forAD2402 */
    ADI_A2B_AD2402 ,
 /*!  Enum for AD2403 */
    ADI_A2B_AD2403,
 /*!  Enum for AD2425 */
    ADI_A2B_AD2425,
 /*!  Enum forAD2421 */
    ADI_A2B_AD2421 ,
 /*!  Enum for AD2422 */
    ADI_A2B_AD2422,
 /*!  Enum for AD2428 */
    ADI_A2B_AD2428,
 /*!  Enum for AD2426 */
    ADI_A2B_AD2426,
 /*!  Enum for AD2427 */
    ADI_A2B_AD2427

}ADI_A2B_PARTNUM;

/*! \struct ADI_A2B_PERI_CONFIG_UNIT
	A2B peripheral config unit structure
 */
typedef struct
 {
	/*!  Operational code. Write - 0, Read - 1, Delay - 2*/
	a2b_UInt32 eOpCode;

	/*!  Sub address width */
	a2b_UInt32 nAddrWidth;

	/*!  Sub address */
	a2b_UInt32 nAddr;

	/*!  Data width */
	a2b_UInt32 nDataWidth;

	/*!  Data count */
	a2b_UInt32 nDataCount;

	/*!  Pointer to config data */
	a2b_UInt8* paConfigData;


} ADI_A2B_PERI_CONFIG_UNIT;

/*! \struct ADI_A2B_PERI_DEVICE_CONFIG
	A2B peripheral device config structure
 */typedef struct
 {
	/*!  I2C address of the device to be configured  */
	a2b_UInt32 nDeviceAddress;

	/*!  I2C address of the device to be configured  */
	a2b_UInt8 bActive;

	/*!  ID of the node to which the peripheral is connected  */
	a2b_UInt32 nConnectedNodeID;

	/*!  Number of peripheral config units to be programmed to the device  */
	a2b_UInt32 nNumPeriConfigUnit;

	/*!  Pointer to peripheral configuration unit */
	ADI_A2B_PERI_CONFIG_UNIT* paPeriConfigUnit;


} ADI_A2B_PERI_DEVICE_CONFIG, *ADI_A2B_PERI_DEVICE_CONFIG_PTR;

/*! \struct ADI_A2B_NODE_PERICONFIG
    Peripheral configuration information structure
*/
typedef struct
{
   /*! Array of device configurations  */
   ADI_A2B_PERI_DEVICE_CONFIG  aDeviceConfig[ADI_A2B_MAX_DEVICES_PER_NODE];

   /*! Number of valid configurations */
   a2b_UInt8  nNumConfig;

}ADI_A2B_NODE_PERICONFIG;

/*! \struct ADI_A2B_NODE_PERICONFIG
    Peripheral configuration information structure
*/
typedef struct
{
   /*! Array of nodes and devices attached to it  */
	ADI_A2B_NODE_PERICONFIG  aPeriDownloadTable[A2B_CONF_MAX_NUM_MASTER_NODES][A2B_CONF_MAX_NUM_SLAVE_NODES];

}ADI_A2B_NETWORK_PERICONFIG;


/*! \struct PERIPHERAL_DEVICE_CONFIG
   Peripheral device configuration
*/
typedef struct
{
	/*! I2C interface status  */
	a2b_UInt8  bI2CInterfaceUse;

	/*! 7 bit I2C address */
	a2b_UInt8  nI2Caddr;

	/*! Device type -audio source/sink/host  */
	a2b_UInt8  eDeviceType;

	/*! Tx0 Pin in use */
	a2b_UInt8  bUseTx0;

	/*! Rx0 Pin in use */
	a2b_UInt8  bUseRx0;

	/*! Tx1 Pin in use */
	a2b_UInt8  bUseTx1;

	/*! Rx1 Pin in use */
	a2b_UInt8  bUseRx1;

	/*! No of Tx0 channels  */
	a2b_UInt8  nChTx0;

	/*! No of Rx0 channels  */
	a2b_UInt8  nChRx0;

	/*! No of Tx1 channels  */
	a2b_UInt8  nChTx1;

	/*! No of Rx1 channels  */
	a2b_UInt8  nChRx1;

	/*! Enable Upstream */
	a2b_UInt8  nNumPeriConfigUnit;

	/*! Pointer to peripheral configuration unit */
	ADI_A2B_PERI_CONFIG_UNIT* paPeriConfigUnit;

}A2B_PERIPHERAL_DEVICE_CONFIG;

/*! \struct ADI_A2B_NODE_PERICONFIG_DATA
	Peripheral configuration data for a node on a chain
*/
typedef struct
{
	/*! Pointer to node device peripheral configurations */
	A2B_PERIPHERAL_DEVICE_CONFIG *apNodePeriDeviceConfig[ADI_A2B_MAX_DEVICES_PER_NODE];

	/*! Number of peripheral devices */
	a2b_UInt8  nNumPeriDevice;

}ADI_A2B_NODE_PERICONFIG_DATA;


/*============= D A T A T Y P E S=============*/


/*============= E X T E R N A L S ============*/

#endif /*_ADI_A2B_NODECONFIG_H_*/

/**
 @}
*/
/**
 @}
*/


/*
**
** EOF: adi_a2b_nodeconfig.h
**
*/
