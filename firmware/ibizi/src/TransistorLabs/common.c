/*
 * Created: 2/4/2013 8:18:03 PM
 *  Author: paul trandem
 *  Copyright (c) 2013 Paul Trandem
 */ 

#include "common.h"

uint8_t Max(uint8_t a, uint8_t b)
{
	if(a > b)
	{
		return a;
	}
	return b;
}

uint8_t Min(uint8_t a, uint8_t b)
{
	if(a < b)
	{
		return a;
	}
	return b;
}

uint16_t RotateLeft(uint16_t byte) {
	uint16_t highbit = byte & 0x8000;
	byte <<= 1;
	if (highbit) byte |= 0x0001;
	return byte;
}

uint16_t RotateRight(uint16_t byte) {
	uint16_t lowbit = byte & 0x0001;
	byte >>= 1;
	if (lowbit) byte |= 0x8000;
	return byte;
}


//TODO: review these functions to see if they can be refactored with dynamic bit values while remaining "performant"

// This assumes the top 5 bits are ignored and rotates the bottom 11
uint16_t Rotate11BitsLeft(uint16_t byte) {
	uint16_t highbit = byte & 0x0400;
	byte <<= 1;
	if (highbit) byte |= 0x0001;
	return byte;
}

// This assumes the top 5 bits are ignored and rotates the bottom 11
uint16_t Rotate11BitsRight(uint16_t byte) {
	uint16_t lowbit = byte & 0x0001;
	byte >>= 1;
	if (lowbit) byte |= 0x0400;
	return byte;
}

// This assumes the top 4 bits are ignored and rotates the bottom 12
uint16_t Rotate12BitsLeft(uint16_t byte) {
	uint16_t highbit = byte & 0x0800;
	byte <<= 1;
	if (highbit) byte |= 0x0001;
	return byte;
}

// This assumes the top 4 bits are ignored and rotates the bottom 12
uint16_t Rotate12BitsRight(uint16_t byte) {
	uint16_t lowbit = byte & 0x0001;
	byte >>= 1;
	if (lowbit) byte |= 0x0800;
	return byte;
}