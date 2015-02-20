#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

	#include <avr/io.h>
	#include <avr/common.h>
	#include <stdbool.h>
	
	#define LEDPIN		PB4
	#define LEDPORT	PORTB
	
	#define RED		OCR1A
	#define GREEN	OCR1B
	#define BLUE	OCR1C

	/************************************************************************/
	/* Data Structures		                                                                         */
	/************************************************************************/

	typedef struct {
		uint8_t Red;
		uint8_t Green;
		uint8_t Blue;
		uint8_t Reserved : 5;
	} LedDriver_Color;
	

	/************************************************************************/
	/* Function Prototypes	                                                                         */
	/************************************************************************/
		
	// Initialize the driver	
	void LedDriver_Init(void);
	
	// Should be called in a millisecond timer loop
	void LedDriver_RenderTask(void);
	
	// Should be called at every millisecond tick
	//void LedDriver_MillisecondTask(void);
	
	// Set the color
	void LedDriver_SetTargetColor(const LedDriver_Color * const color);
	void LedDriver_SetTargetColorValues(uint8_t red, uint8_t green, uint8_t blue);
	
	// Set the fade duration in milliseconds
	//void LedDriver_SetFadeDuration(int durationMs);
	
#endif /* LEDDRIVER_H_ */