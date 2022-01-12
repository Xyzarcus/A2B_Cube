/*******************************************************************************
Copyright (c) 2018 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
 * @file:    adi_a2b_commch_app.c
 * @brief:   This is the implementation of API wrappers for Communication channel
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
***************************************************************************/
/*============= I N C L U D E S =============*/
#include <a2bapp.h>
#include "adi_a2b_commch_interface.h"

/*============= D E F I N E S =============*/

/*============= D A T A =============*/
extern a2b_App_t 	gApp_Info;
a2b_CommChMsg 		oCommChTxMsg;

/*============= L O C A L  P R O T O T Y P E S =============*/
static void a2b_app_onCommChEvent(struct a2b_Msg* msg, a2b_Handle userData);

/*============= C O D E =============*/

/*****************************************************************************/
/*!
@brief			This function initializes the communication channel

@return			A2B_COMMCH_RET type
                - 0: A2B_COMMCH_SUCCESS
                - 1: A2B_COMMCH_FAILED
*/
/*****************************************************************************/
A2B_COMMCH_RET adi_a2b_app_CommChInit()
{
	A2B_COMMCH_RET eRet = A2B_COMMCH_SUCCESS;
	/* Register for notifications on communication channel events */
	gApp_Info.notifyInterrupt = a2b_msgRtrRegisterNotify(gApp_Info.ctx,
			A2B_MSGNOTIFY_COMMCH_EVENT, a2b_app_onCommChEvent,
	A2B_NULL,
	A2B_NULL);
	if(gApp_Info.notifyInterrupt == A2B_NULL)
	{
		eRet = A2B_COMMCH_FAILED;
	}

	return (eRet);
}

/*****************************************************************************/
/*!
@brief			This function sends a message using communication channel

@param [in]     nMsgId			Message Id
@param [in]     nMsgLenInBytes	Message Length in bytes
@param [in]     pMsgPayload		Pointer to payload Data Buffer
@param [in]     nNodeAddr		Node Address

@return			A2B_COMMCH_RET type
                - 0: A2B_COMMCH_SUCCESS
                - 1: A2B_COMMCH_FAILED
*/
/*****************************************************************************/
A2B_COMMCH_RET adi_a2b_app_CommChSendMsg(a2b_UInt8 nMsgId, a2b_UInt16 nMsgLenInBytes, a2b_UInt8* pMsgPayload, int16 nNodeAddr)
{
	A2B_COMMCH_RET eRet = A2B_COMMCH_SUCCESS;
	a2b_CommChTxInfo* pCommChTxInfo;
	struct a2b_Msg* msg;

	oCommChTxMsg.nMsgId = nMsgId;
	oCommChTxMsg.nMsgLenInBytes = nMsgLenInBytes;
	oCommChTxMsg.pMsgPayload = pMsgPayload;

	/* Create a Communication channel Transmission request message */
	msg = a2b_msgAlloc(gApp_Info.ctx, A2B_MSG_REQUEST, A2B_MSGREQ_COMMCH_SEND_MSG);
	/* Attach the Boolean flag to the message */
	pCommChTxInfo = (a2b_CommChTxInfo*)a2b_msgGetPayload(msg);
	pCommChTxInfo->req.pTxMsg = &oCommChTxMsg;
	pCommChTxInfo->req.nSlvNodeAddr = nNodeAddr;

	a2b_msgRtrSendRequest(msg, A2B_NODEADDR_MASTER, A2B_NULL);
	a2b_msgUnref(msg);

	return (eRet);
}

/*****************************************************************************/
/*!
@brief			The handler for Communication channel notifications.

@param [in]     msg				The Communication channel notification message
@param [in]     userData		User data associated with the notification registration.

@return			None
*/
/*****************************************************************************/
static void a2b_app_onCommChEvent(struct a2b_Msg* msg, a2b_Handle userData)
{
	a2b_CommChEventInfo* pCommChEventInfo;

	A2B_UNUSED(userData);

	if (msg)
	{
		pCommChEventInfo = a2b_msgGetPayload(msg);
		adi_a2b_app_CommChCallBk(pCommChEventInfo->pRxMsg->nMsgId, pCommChEventInfo->pRxMsg->nMsgLenInBytes, pCommChEventInfo->pRxMsg->pMsgPayload, pCommChEventInfo->nNodeId, pCommChEventInfo->eEvent);
	}
}
