/*	Author: sspon001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {start, onPress, onRelease, offPress, offRelease} state ;
void Tick(){
	switch(state){
		case start:
			state = onPress ;
			break ;
		case onPress:
			if((PINA & 0x01) == 0x01) state = onPress ;
			else state = onRelease ;
			break ;
		case onRelease:
			if((PINA & 0x01) == 0x01) state = offPress ;
			else state = onRelease ;
			break ;
		case offPress:
			if((PINA & 0x01) == 0x01) state = offPress ;
			else state = offRelease ;
			break ;
		case offRelease:
			if((PINA & 0x01) == 0x01) state = onPress ;
			else state = offRelease ;
			break ;
		default:
			state = start ;
			break ;
	}
	switch(state){
		case start:
			PORTB = 0x01 ;
			break ;
		case onPress:
			PORTB = 0x01 ;
			break ;
		case onRelease:
			break ;
		case offPress:
			PORTB = 0x02 ;
			break ;
		default:
			PORTB = 0x01 ;
			break ;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00 ; PORTA = 0xFF ;
	DDRB = 0xFF ; PORTB = 0x00 ;
    /* Insert your solution below */
    while (1) {
	Tick() ;
    }
    return 1;
}
