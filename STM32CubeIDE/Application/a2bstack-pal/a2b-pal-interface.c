/*****************************************************************************
 * a2b-pal-interface.c
 *****************************************************************************/

//#include "a2b-commandlist-app.h"
//#include <sys/platform.h>
#include "adi_initialize.h"
#include "..\adi_a2b_datatypes.h"
#include "..\adi_a2b_framework.h"
#include "adi_a2b_externs.h"
//#include "adi_a2b_timer.h"
//#include "adi_a2b_twidriver.h"

#include "i2c.h"
#include "stm32f7xx_hal_def.h"

a2b_Handle i2chnd;
A2B_ECB ecb;

a2b_HResult adi_a2b_I2COpen()
{
	a2b_HResult nResult = 0;
//	ecb.palEcb.oTWIConfig.i2c_speed = A2B_I2C_BUS_SPEED_100KHZ;
//	i2chnd = adi_a2b_TwiOpen(&ecb, NULL);
//
//	if (i2chnd == NULL)
//		nResult = 1;

	return nResult;
}

a2b_HResult adi_a2b_I2CWrite(a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf)
{
	a2b_HResult nResult = 0;
	//nResult = adi_a2b_TwiWrite(i2chnd, nDeviceAddress, nWrite, wBuf);
	nResult = HAL_I2C_Master_Transmit(&hi2c1, nDeviceAddress, (a2b_UInt8*)wBuf, nWrite, 100);
	return nResult;
}

a2b_HResult adi_a2b_I2CWriteRead(a2b_UInt16 nDeviceAddress, a2b_UInt16 nWrite, a2b_UInt8* wBuf, a2b_UInt16 nRead, a2b_UInt8* rBuf)
{
	a2b_HResult nResult = 0;
	//nResult = adi_a2b_TwiWriteRead(i2chnd, nDeviceAddress, nWrite, wBuf, nRead, rBuf);
	nResult = HAL_I2C_Master_Transmit(&hi2c1, nDeviceAddress, (a2b_UInt8*)wBuf, nWrite, 100);
	nResult = HAL_I2C_Master_Receive(&hi2c1, nDeviceAddress, rBuf, nRead, 100);
	return nResult;
}


void adi_a2b_I2CWrite8()
{

}
