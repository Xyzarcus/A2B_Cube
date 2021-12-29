/*******************************************************************************
Copyright (c) 2018 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
 * @file:    adi_a2b_commch_appinterface.h
 * @brief:   This  header file contains interfaces and messages to be used by comm ch application
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/** @addtogroup Communication_Channel Communication Channel Interface
 *  @{
 */

#ifndef ADI_A2B_COMMCH_APPINTERFACE_H_
#define	ADI_A2B_COMMCH_APPINTERFACE_H_

#include "adi_a2b_commch_interface.h"

/*============= D E F I N E S =============*/
/* Message ID's upto 0x0A are reserved to be used within master plugin */

/* Communication channel message: To indicate a common negative response from server to client */
#define A2B_COMMCH_MSG_NEGATIVE_RESP				(0x3F)

/* Communication channel message: Request and response message to indicate a slave node to cross fade the audio channels */
#define A2B_COMMCH_MSG_REQ_XFADE_AUDIO_SRC			(A2B_COMMCH_MSG_CUSTOM_START)
#define A2B_COMMCH_MSG_RSP_XFADE_AUDIO_SRC			(A2B_COMMCH_MSG_CUSTOM_START + 0x01)

typedef enum
{
	A2B_ORIG_RX_CHN = 0u,
	A2B_ALT_RX_CHN,
	A2B_MUTE_SRC,
	A2B_ADC_INPUT,
	A2B_SINETONE
}ADI_A2B_XFADE_SRC;

typedef enum
{
	A2B_RC_SLEW = 0u,
	A2B_LINEAR_SLEW
}ADI_A2B_XFADE_SLEWTYPE;

typedef struct{
	ADI_A2B_XFADE_SRC eXfadeSrc;
	ADI_A2B_XFADE_SLEWTYPE eSlewType;
	a2b_UInt8 nSlewFactor;
}XfadePayload;
/*============= G L O B A L  P R O T O T Y P E S =============*/

void adi_a2b_changeRouting(XfadePayload *pXfadePayload);

#endif /* ADI_A2B_COMMCH_INTERFACE_H_ */

/**@}*/
