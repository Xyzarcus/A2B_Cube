/*******************************************************************************
Copyright (c) 2017 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
* @file: a2bapp_sh.h
* @brief: This file contains Typedefs,configurable macros, structures for running
*          A2B application
* @version: $Revision: 3888 $
* @date: $Date: 2016-01-17 18:46:38 +0530 (Sun, 17 Jan 2016) $
* Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/

#ifndef __A2BAPP_SH_H__
#define __A2BAPP_SH_H__

/* Add your custom header content here */
/*============= I N C L U D E S =============*/
#include "adi_a2b_datatypes.h"
#include "adi_a2b_commch.h"
#include "adi_a2b_commch_appinterface.h"

/* Application global structure */
typedef struct
{
	a2b_CommChMsg 		goCommChTxMsg;		/* Communication channel message structure instance */
	a2b_CommPalCtx		goCommPalCtx;		/* Communication channel slave PAL context instance */
	a2b_CommChPal 		goCommChPal;		/* Communication channel slave PAL context instance */
	a2b_CommChConfig 	goCommChConfig;	/* Communication channel slave configuration instance */
	a2b_CommChInfo		gCommChInfo;		/* Communication channel slave state information instance */
	a2b_Handle			ghCommCh;			/* Communication channel handle */
}a2b_App_t;

#endif /* __A2BAPP_SH_H__ */
