/*
 * Created: 1/27/2013 8:54:07 AM
 *  Author: paul trandem
 *  Copyright (c) 2013 Paul Trandem
 */ 


#ifndef TIMER0CONFIG_H_
#define TIMER0CONFIG_H_

	#include <avr/io.h>
	#include <stdbool.h>

	typedef enum
	{
		Timer0Config_NoClockSource			= 0x00,
		Timer0Config_IOClk_1				= 0x01,
		Timer0Config_IOClk_8				= 0x02,
		Timer0Config_IOClk_64				= 0x03,
		Timer0Config_IOClk_256				= 0x04,
		Timer0Config_IOClk_1024				= 0x05,
		Timer0Config_ExtClk_T0_FallingEdge	= 0x06,
		Timer0Config_ExtClk_T0_RisingEdge	= 0x07
	} Timer0Config_Prescaler;
	
	void Timer0Config_EnableCTCMode(uint8_t compareMatchTopA, uint8_t compareMatchTopB, Timer0Config_Prescaler prescaler);
	void Timer0Config_EnableMatchInterrupts(bool configureMatchA, bool configureMatchB, bool globalInterruptEnable);

#endif /* TIMER0CONFIG_H_ */