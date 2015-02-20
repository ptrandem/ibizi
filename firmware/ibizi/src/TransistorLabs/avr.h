/*
 * Created: 2/4/2013 8:29:55 PM
 *  Author: paul trandem
 *  Copyright (c) 2013 Paul Trandem
 */ 


#ifndef TRANSISTORLABS_AVR_H_
#define TRANSISTORLABS_AVR_H_

	#ifndef _AVR_SFR_DEFS_H_
		#include <avr/sfr_defs.h>
	#endif

	#define SETPINDIRECTION_INPUT(ddrx, pin)	ddrx &= ~_BV(pin);
	#define SETPINDIRECTION_OUTPUT(ddrx, pin)	ddrx |= _BV(pin);
	
	#define SETINTERNALPULLUP_OFF(portx, pin)	portx &= !_BV(pin);
	#define SETINTERNALPULLUP_ON(portx, pin)	portx |= _BV(pin);
	

#endif /* TRANSISTORLABS_AVR_H_ */