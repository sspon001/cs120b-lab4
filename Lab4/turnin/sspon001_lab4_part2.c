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

enum states {start, first, init, reset, add, sub, addPress, subPress} state ;
void Tick(){
	switch(state){
		case start:
			state = first ;
			break ;
		case first:
			state = init ;
			break ;
		case init:
			if((PINA & 0x03) == 0x03) state = reset ;
			else if((PINA & 0x01) == 0x01) state = addPress ;
			else if((PINA & 0x02) == 0x02) state = subPress ;
			break ;
		case reset:
			if((PINA & 0x03) == 0x03) state = reset ;
			else state = init ;
			break ;
		case add:
			if((PINA & 0x01) == 0x01) state = add ;
			else state = init ;
			break ;
		case addPress:
			state = add ;
			break ;
		case sub:
			if((PINA & 0x02) == 0x02) state = sub ; 
			else state = init ;
			break ;
		case subPress:
			state = sub ;
			break ;
		default:
			state = start ;
			break ;
	}
	switch(state){
		case start:
			PORTC = 0x07 ;
			break ;
		case first:
			PORTC = 0x07 ;
			break ;
		case init:
			break ;
		case add:
			break ;
		case addPress:
			if(PORTC < 0x09) PORTC = PORTC + 1 ;
			break ;
		case sub:
			break ;
		case subPress:
			if(PORTC < 0x09) PORTC = PORTC - 1 ;
			break ;
		case reset:
			PORTC = 0x00 ;
			break ;
		default:
			PORTC = 0x07 ;
			break ;
		}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00 ; PORTA = 0xFF ;
	DDRC = 0xFF ; PORTC = 0x00 ;
    /* Insert your solution below */
    while (1) {
	Tick() ;
    }
    return 1;
}
