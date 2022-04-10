/*
 * main.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Dell
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MADC/MADC_Config.h"
#include"MCAL/MADC/MADC_Interface.h"
#include"HAL/HTEMPERATURE/HTEMPERATURE_Interface.h"
#include"HAL/HSTEPPER/HStepper_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"

#define F_CPU 16000000UL
#include<util/delay.h>

int main(void)
{
	/*LCD PIN initialize*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN7,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	/*LCD int*/
	HAL_VidHCLCD_4BitModeInit();
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"Tempread");

	/*Set ADC channel 1 as input*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN1,PIN_INPUT);
	HTEMP_VidInit();
	uint16 Loc_uint16Temp=0;
	while(1)
	{
		Loc_uint16Temp=HTEMP_uintGetTemp(1);
		HAL_VidHCLCD_4BitModeSetPosition(2,0);
		HAL_VidHCLCD_4BitModeWriteNumber(Loc_uint16Temp);
	}
	return 0;
}
