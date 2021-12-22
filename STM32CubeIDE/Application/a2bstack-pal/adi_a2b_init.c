/*******************************************************************************
Copyright (c) 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************

   Name       : adi_a2b_init.c
   
   Description: This file contains functions which initializes host/target processor  
                       
                 
   Functions  : adi_a2b_SystemInit()
                 

   Prepared &
   Reviewed by: Automotive Software and Systems team, 
                IPDC, Analog Devices,  Bangalore, India
                
   @version: $Revision: 3626 $
   @date: $Date: 2015-10-05 14:04:13 +0530 (Mon, 05 Oct 2015) $
               
******************************************************************************/
/*! \addtogroup Target_Dependent Target Dependent
 *  @{
 */

/*! \addtogroup System_Init System Init
 *  @{
 */

/*============= I N C L U D E S =============*/

#include "adi_a2b_datatypes.h"
#include "adi_a2b_framework.h"
#include "adi_a2b_externs.h"
//#include "adi_a2b_timer.h"
//#include "adi_a2b_twidriver.h"
//#include "adi_initialize.h"    /* PRQA S 0602*/
#include "string.h"
//#include <services\pwr\adi_pwr.h>
//#include <services/gpio/adi_gpio.h>

#if A2B_PRINT_FOR_DEBUG
#include <stdio.h>
#endif
/*============= D E F I N E S =============*/


/*============= D A T A =============*/



/*============= C O D E =============*/
/*
** Function Prototype section
*/
/*
** Function Definition section
*/


 
/********************************************************************************/
/*!
@brief This function does the system initialization. Sets Core and system clock

@param [in] none
   
    
@return     ADI_A2B_RESULT
            - ADI_A2B_FAILURE : Failure(If any of the peripheral initialization fails)
            - ADI_A2B_SUCEESS : Success    
    
*/
/***********************************************************************************/
#pragma section("L1_code")
a2b_HResult adi_a2b_SystemInit(void)
{
	uint32 nResult = 0u;
	uint32 nCClk, nSClk;
	a2b_HResult eResult = 0u;
//	ADI_PWR_RESULT ePwrResult;

	/* Initialize managed drivers and/or services- auto generated code  */
//	nResult = (uint32)adi_initComponents();

	/* SDRAM controller initialization */
//	*pEBIU_AMGCTL = 0x00F9u;
//	*pEBIU_AMBCTL0 = 0x7BB07BB0u;
//	*pEBIU_AMBCTL1 = 0x7BB07BB0u;

//	nSClk = A2B_SCLK;
//	nCClk = A2B_CORE_CLOCK;

//	ePwrResult = adi_pwr_Init(A2B_CRYSTAL_CLOCK, A2B_MAX_CORECLOCK, A2B_MAX_SYSCLOCK, 2);
//	ePwrResult = adi_pwr_SetFreq(nCClk, nSClk);

	return eResult;
}





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

