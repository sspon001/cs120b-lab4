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

enum states {start, init, unlockP, unlockY, unlockYRelease, lock} state ;
void Tick(){
	switch(state){
		case start:
			state = init ;
			break ;
		case init:
			if((PINA & 0x07) == 0x07) state = unlockP ;
			else if((PINA & 0x87) == 0x80) state = lock ;
			else state = init ;
			break ;
		case unlockP:
			if((PINA & 0x07) == 0x04) state = unlockP ;
			else state = unlockY;
			break ;
		case unlockY:
			if((PINA & 0x07) == 0x02 && (PORTB & 0x01) == 0x01) state = lock ;
			else if((PINA == 0x07) == 0x02) state = unlockYRelease ;
			else if(PINA == 0x00) state = unlockY ;
			else state = init ;
			break ;
		case unlockYRelease:
			if((PINA & 0x07) == 0x02) state = unlockYRelease ;
			else state = init ;
			break ;
		case lock:
			if((PINA & 0x87) == 0x80) state = lock ; 
			else if((PINA & 0x07) == 0x02) state = lock ;
			else state = init ;
			break ;
	}
	switch(state){
		case start:
			PORTB = 0x00 ;
			break ;
		case init:
			break ;
		case unlockP:
			break ;
		case unlockY:
			break ;
		case unlockYRelease:
			PORTB = 0x01 ;
			break ;
		case lock:
			PORTB = 0x00 ;
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
