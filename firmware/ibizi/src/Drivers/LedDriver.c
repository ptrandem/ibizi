/*
    ibizi Firmware
    Copyright (C) Paul Trandem 2016.
*/

#include "LedDriver.h"
#include "TransistorLabs/avr.h"


/************************************************************************/
/* Private Variables		                                                                         */
/************************************************************************/

static LedDriver_Color _currentColor;
static LedDriver_Color _targetColor;

const uint8_t gamma[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

/************************************************************************/
/* Private Function Prototypes                                                                    */
/************************************************************************/

static void InitHardware(void);
static void ProcessDelta(uint8_t * current, uint8_t target);
static void SetLedOn(void);
static void SetLedOff(void);

/************************************************************************/
/* Public Functions		                                                                         */
/************************************************************************/

void LedDriver_Init() 
{
	InitHardware();	
}

void LedDriver_RenderTask()
{
	ProcessDelta(&_currentColor.Red, _targetColor.Red);
	ProcessDelta(&_currentColor.Green, _targetColor.Green);
	ProcessDelta(&_currentColor.Blue, _targetColor.Blue);
	
	RED = gamma[_currentColor.Red];
	GREEN = gamma[_currentColor.Green];
	BLUE = gamma[_currentColor.Blue];
	
	if(_currentColor.Red == 0 && _currentColor.Green == 0 && _currentColor.Blue == 0)
	{
		SetLedOff();
	}
	else
	{
		SetLedOn();
	}
}

void LedDriver_SetTargetColor(const LedDriver_Color * const color)
{
	LedDriver_SetTargetColorValues(color->Red, color->Green, color->Blue);
}

void LedDriver_SetTargetColorValues(uint8_t red, uint8_t green, uint8_t blue)
{
	_targetColor.Red = red;
	_targetColor.Blue = blue;
	_targetColor.Green = green;
}


/************************************************************************/
/* Private Functions		                                                                         */
/************************************************************************/


static void SetLedOn()
{	
	LEDPORT |= (1 << LEDPIN);
}

static void SetLedOff()
{
	LEDPORT &= ~(1 << LEDPIN);
}

static void ProcessDelta(uint8_t * current, uint8_t target)
{
	if(*current > target)
	{
		-- (*current);
	}
	else if(*current < target)
	{
		++ (*current);
	}
}

static void InitHardware()
{
	/*
		The ATmegaxxU2 series has two timers, Timer0 and Timer1.  
		Timer1 features three 8-bit PWM outputs, so we'll use that one for all PWM needs.
	*/
	
	// Configure Timer1 for Fast PWM 8-bit
	TCCR1A |= _BV(WGM10);
	TCCR1B |= _BV(WGM12);
	
	// Turn on OC1A - inverted
	TCCR1A |=  _BV(COM1A1) | _BV(COM1A0);
	TCCR1A |=  _BV(COM1B1) | _BV(COM1B0);
	TCCR1A |=  _BV(COM1C1) | _BV(COM1C0);
	
	// Initialize Values
	RED = 0xff;
	GREEN = 0xff;
	BLUE = 0xff;

	DDRC |= _BV(PC5) | _BV(PC6);
	DDRB |= _BV(PB4) | _BV(PB7);
	
//	SETPINDIRECTION_OUTPUT(LEDPORT, LEDPIN);

	// enable PWM - using system clock, no prescaler
	TCCR1B |= _BV(CS10);
	
	
}













