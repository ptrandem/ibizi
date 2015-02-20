/*
 * Created: 1/27/2013 8:55:42 AM
 *  Author: paul trandem
 *  Copyright (c) 2013 Paul Trandem
 */ 

#include "Timer0Config.h"
#include <avr/interrupt.h>

void Timer0Config_EnableCTCMode(uint8_t compareMatchTopA, uint8_t compareMatchTopB, Timer0Config_Prescaler prescaler)
{

//TODO: This can be filled out (or split out) to enable more Timer/Counter0 options
	
	// TIMER0 Configuration

	// Pin Outputs disabled (default)
	// CTC MODE = WGM:01,00 = 1,0
	TCCR0A |= _BV(WGM10);

	// CTC MODE = WGM:02 = 0
	// clk/64 Prescale: CS:02,01,00 = 0,1,1
	//TCCR0B |= (_BV(CS01) | _BV(CS00));
	TCCR0B |= (uint8_t)prescaler;

	OCR0A = compareMatchTopA;
	OCR0B = compareMatchTopB;

}

void Timer0Config_EnableMatchInterrupts(bool configureMatchA, bool configureMatchB, bool globalInterruptEnable)
{
	// shut down global interrupts
	//cli();
	
	if(configureMatchA == true)
	{
	// Enable Timer0 Compare Match A interrupts
		TIMSK0 |= _BV(OCIE0A);
	}

	if(configureMatchB)
	{
		// Enable Timer0 Compare Match B interrupts
		TIMSK0 |= _BV(OCIE0B);
	}
	
	// ENABLE GLOBAL INTERRUPTS?
	if(globalInterruptEnable == true)
	{
		//sei();
	}
}