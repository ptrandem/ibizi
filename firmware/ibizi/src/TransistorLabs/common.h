/*
 * Created: 2/4/2013 8:17:56 PM
 *  Author: paul trandem
 *  Copyright (c) 2013 Paul Trandem
 */ 


#ifndef TRANSISTORLABS_COMMON_H_
#define TRANSISTORLABS_COMMON_H_

	#include <stdint.h>
	
	uint8_t Max(uint8_t a, uint8_t b);
	uint8_t Min(uint8_t a, uint8_t b);
	uint16_t RotateLeft(uint16_t byte);
	uint16_t RotateRight(uint16_t byte);
	
	uint16_t Rotate11BitsLeft(uint16_t byte);
	uint16_t Rotate11BitsRight(uint16_t byte);
	uint16_t Rotate12BitsLeft(uint16_t byte);
	uint16_t Rotate12BitsRight(uint16_t byte);
	

#endif /* TRANSISTORLABS_COMMON_H_ */