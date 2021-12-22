/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
* @file: adi_a2b_framework.h
* @brief: This file contains Typedefs,configurable macros and A2B framework structures
* @version: $Revision: 3888 $
* @date: $Date: 2016-01-17 18:46:38 +0530 (Sun, 17 Jan 2016) $
* Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/*! \addtogroup PAL_SH PAL_SH
* @{
*/

/** @defgroup Configuration_Macros_Structures
 *
 * This module has structure definitions, enums and Macros used for framework configuration
 *
 */

/*! \addtogroup Configuration_Macros_Structures Configuration Macros & Structures
* @{
*/

#ifndef _ADI_A2B_FRAMEWORK_H_
#define _ADI_A2B_FRAMEWORK_H_

/*============= I N C L U D E S =============*/
#include "a2b/ctypes.h"
#include "a2bapp_defs.h"
/*============= D E F I N E S =============*/
/*!< Maximum number of Timers */
#define A2B_MAX_TIMERS			(2U)
/*!< PCLK for ADSP-21489 */
#define A2B_SYSTEM_CLK				(24.576*16/2)
/*!< CCLK for ADSP-21489 */
#define A2B_CORE_CLK				(216000000U)

/*! Abstracted timer identification number used for A2B transceiver related events (FIXED to 1) */
#define A2B_TOTAL_LOG_CH                   (A2B_CONF_MAX_NUM_MASTER_NODES * A2B_CONF_LOG_NUM_CHANNELS)

/*! Abstracted timer identification number used for A2B transceiver related events (FIXED to 1) */
#define A2B_TIMER_NO                                        (1u) 
 
/*! Node discovery time-out period in micro-seconds */
#define A2B_NODE_DISCOVERY_TIMEOUT                          (50000u)

/*! System clock */
#define A2B_SCLK                                            (49152000u*2u)


/* Memory sections for App and PAL */
#define A2B_APP_L1_CODE   __attribute__ ((section ("L1_code")))
#define A2B_APP_L3_CODE   __attribute__ ((section ("L3_code")))
/*! External memory code sections */
#define A2B_PAL_L1_CODE   __attribute__ ((section ("L1_code")))
#define A2B_PAL_L3_CODE   __attribute__ ((section ("L3_code")))
/*! Internal memory data sections */
#define A2B_APP_L1_DATA   __attribute__ ((section ("L1_data")))
#define A2B_APP_L3_DATA   __attribute__ ((section ("L3_data")))
/*! External memory data sections */
#define A2B_PAL_L1_DATA   __attribute__ ((section ("L1_data")))
#define A2B_PAL_L3_DATA   __attribute__ ((section ("L3_data")))

/*! Abstracted TWI peripheral identification number used for A2B connection */
#define A2B_TWI_NO                                          (0u)

/*! A2B IRQ pin number  */ 
#define A2B_IRQ_PIN                                         (0u)

/*! Abstracted SPI peripheral identification number */
#define A2B_SPI_NO                                          (0u)

/*! Maximum number of errors stored in the framework */
#define A2B_MAX_NUM_ERROR                                   (10u) 

/*! Total number of nodes per branch: 1-master + 15-slave nodes */
#define A2B_MAX_NUMBER_OF_NODES_PER_BRANCH                  (ADI_A2B_MAX_SLAVE_NODES_PER_MASTER + 1)

/*! Maximum number of AD2410 registers configured in a function */
#define A2B_MAX_NUM_REG                                     (100)

/*! Communication buffer size in words  */
#define A2B_MAX_MSG_TXBUFFERSIZE                            (250u)

/*! Communication buffer size in words  */
#define A2B_MAX_MSG_RXBUFFERSIZE                            (1000u)

/*! EEPROM TWI device address */
#define A2B_EEPROM_I2C                                      (0x50u)

/*! A2B software version number */
#define A2B_VERSION_NUMBER                                  (0x130000u)

/*! Starting address for EEPROM Schematic save  */
#define A2B_SCHEMATIC_SAVE_EEPROM_START_ADDR                (0xFEu)

/*! 16 bit Header value used in  EEPROM schematic Save option */
#define A2B_SCHEMATIC_DATA_HEADER                           (0xADABu)   
   
/*! First byte of Header value used in EEPROM Schematic Save option */
#define A2B_SCHEMATIC_DATA_HEADER1                          (0xADu)

/*! Second byte of Header value used in EEPROM Schematic Save option */
#define A2B_SCHEMATIC_DATA_HEADER2                          (0xABu)

/*! Post discovery timer interval */
#define A2B_POST_DISC_TIME_INTERVAL                         (5000000u)

/*********************************************************************
 *
 * PLATFORM SPECIFIC MACROS - CONF
 *********************************************************************/
/** The length of the buffer to hold the path to the I2C device. This
 * is typically something like /dev/i2c-N where 'N' is the device number.
 */
#define A2B_PAL_I2C_DEVICE_PATH_LEN (32)

/** Define the default (7-bit) A2B master node I2C address */
#define A2B_CONF_DEFAULT_MASTER_NODE_I2C_ADDR   (0x68)

/** Define the name of the TRACE log channel in terms of a URL.
 * The URL is encoded as follows:
 *      \verbatim      <protocol>//:<resource>:<port>      \endverbatim
 *
 * With the following supported protocol options:
 *      \verbatim
        file://<filename>
        stdio://stderr
        stdio://stdout
        tcp://<host>:<port>
        udp://<host>:<port>
        syslog://<level>
            where level = emerg, alert, crit, err, warning, notice, info, debug
        \endverbatim
 *
 * Example:
 *      \verbatim       udp://localhost:18001       \endverbatim
 */

#define A2B_INVALID_FD          			(-1)
/*============================================== Configurable MACROs ===============================================*/

#ifdef A2B_PRINT_CONSOLE
/*! Debug macro - used only for printing PAL configuration status */
#define A2B_PRINT_FOR_DEBUG                                 (1u)

#else
/*! Debug macro - used only for printing PAL configuration status */
#define A2B_PRINT_FOR_DEBUG                                 (0u)
#endif


/*============================================== Debug MACROs ===============================================*/

/*! Enable I2C word store  */
#define A2B_DEBUG_STORE_CONFIG                               (0u)

/*! Enable cycle measurement */
#define DO_CYCLE_COUNTS

/*! Number of TWI words, increase according to network size */
#define A2B_TWI_DEBUG_NUM                                    (500u)
/*============= D A T A T Y P E S=============*/
 /*! \enum ADI_A2B_RESULT
    Execution status
 */
typedef enum
{
 /*!  Success */
  ADI_A2B_SUCCESS,
 /*!  Failure */
  ADI_A2B_FAILURE,
 /*!  Undefined */
  ADI_A2B_UNDEFINED

}ADI_A2B_RESULT;

/*! \enum ADI_A2B_DISCOVERY_TYPE
    Possible discovery modes 
 */
typedef enum
{
 /*!  Simple discovery  */
  ADI_A2B_SIMPLE_DISCOVERY ,
 /*!  Modified discovery */  
  ADI_A2B_MODIFED_DISCOVERY ,
  /*! Optimized discovery  */ 
  ADI_A2B_OPTIMIZED_DISCOVERY ,
  /*! Advanced discovery */ 
  ADI_A2B_ADVANCED_DISCOVERY

}ADI_A2B_DISCOVERY_TYPE;


/*! \enum ADI_A2B_NETWORK_CLK_SRC
    Network clock source 
 */
typedef enum
{
 /*! Target frame sync as source  */
  ADI_A2B_TARGET_FS,
 /*! Master codec as clock source  */ 
  ADI_A2B_MASTER_CODEC 

}ADI_A2B_NETWORK_CLK_SRC;

/*! \enum ADI_A2B_TIMER_CONTEXT
    Context of timer run 
 */
typedef enum
{
 /*!  During discovery   */
  ADI_A2B_SYS_CLK,
 /*!  For I2C event  */  
  ADI_A2B_I2C,

}ADI_A2B_TIMER_CONTEXT;


/*! Timer callback */
typedef void (*TIMER_CALL_BACK)(void* pHandle);


/*! \struct ADI_A2B_TIMER_HANDLER
    Configuration structure for GPT
*/
typedef struct ADI_A2B_TIMER_HANDLER
{
  /*! Flag to notify Timer expiry*/  
  volatile uint8_t bTimeout;
  
  /*! Application call back function pointer*/
  TIMER_CALL_BACK pCallbackhandle;
  
  /*! Timer Number */
  uint32_t nTimerNo;
  
  /*! Timer Expire value in milliSecond */
  uint32_t nTimerExpireVal;
  
  /*! A2B timer context */
  ADI_A2B_TIMER_CONTEXT eContext; 

}ADI_A2B_TIMER_HANDLER,*ADI_A2B_TIMER_HANDLER_PTR;


typedef void (*GPIO_CALL_BACK)(uint8_t nGPIONum, void* pHandle);

/*! \struct ADI_A2B_CONFIG_TABLE
    Structure to store config words
*/

typedef struct 
{
    /*! Register address */
    uint8_t nAddress;
    /*! Value  */
    uint8_t nValue;

}ADI_A2B_CONFIG_TABLE;

/*! \struct ADI_A2B_TWI_DATA_DEBUG
    TWI data configuration structure
*/
typedef struct
{
    /*! Operation  */
    uint8_t eOp;

    /*! TWI address  */
    uint8_t nTwiAddr;

    /*! Register address  */
    uint8_t nRegAddr;

    /*! nValue  */
    uint8_t nDatVal;

}ADI_A2B_TWI_DATA_DEBUG;


/*! \struct ADI_A2B_TWI_DATA_DEBUG_CONFIG
    TWI data configuration structure
*/
typedef struct
{
    /*! Number of values  */
   ADI_A2B_TWI_DATA_DEBUG aStoreDataVal[A2B_TWI_DEBUG_NUM];

    /*! Total  */
    uint32_t nNum;

}ADI_A2B_TWI_DATA_DEBUG_CONFIG;

/*! \enum A2B_LOGGING_MODE
    Modes of Logging
*/
typedef enum
{
    PAL_LOG_UNKNOWN = 0,
    PAL_LOG_FILE
} A2B_LOGGING_MODE;

/*! \struct A2B_LOG_INFO
    Logging Information Structure
*/
typedef struct pal_LogConfig
{
    a2b_Bool inUse;
    a2b_UInt32 fd;
    A2B_LOGGING_MODE elogmode;
} A2B_LOG_INFO;

/** 
 @}
*/


/** 
 @}
*/

/*======= P U B L I C P R O T O T Y P E S ========*/

#endif /* _ADI_A2B_FRAMEWORK_H_ */

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
