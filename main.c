/*
 * GccApplicationFinal.c
 *
 * Created: 2/27/2020 3:01:56 PM
 * Author : stewr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "scheduler.h"
#include "io.h"
#include "io.c"
#include "led_matrix.h"
#include "pwm.h"
#include "gyroscope.h"


//Shared Variables
unsigned char smile = 0x00;//variable should be modified according to ADC tick
//End Shared Variables

//enum Smile_States{start_state, smile_state, frown_state}smile_state;
void calc_slouch(){//GOOD RANGE: 55 +/- 10, ELSE: BAD RANGE
	uint16_t temp = ReadADC(0)-687;
	if(temp>=45 && temp<=65){
		smile = 1;
	}else{
		smile = 0;
	}
}
unsigned char freq_counter = 0x00;
double getFreq(){
	if(!smile){
		if(freq_counter >= 200){
			if(freq_counter%2==0){
				return 300.0;
			}else{
				return 600.0;
			}
		}else{
			freq_counter++;
			return 0;
		}
	}else{
		freq_counter = 0;
		return 0;
	}
}


unsigned char col_count = 0x00;
void smile_frown_tick(){
	switch(col_count){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		col_count++;
		break;
		
		default:
		col_count = 0x01;
		break;
	}
	
	switch(col_count){//flash each row... all bits should be zero'd except for the nth row
		case 1:
		PORTC = 0x00 | ROWA1 | COLA1 | COLA4 | COLA7 | COLA8;
		PORTD = 0x00 | COLB2 | COLB5;
		break;
		
		case 2:
		PORTC = 0x00 | ROWA2 | COLA1 | COLA4 | COLA7 | COLA8;
		PORTD = 0x00 | COLB2 | COLB5;
		break;
		
		case 3:
		PORTC = 0x00 | COLA1 | COLA4 | COLA7 | COLA8;
		PORTD = 0x00 | ROWB3 | COLB2 | COLB5;
		break;
		
		case 4:
		if(smile){
			PORTC = 0x00 | ROWA4 | COLA4 | COLA6 |COLA7;
			PORTD = 0x00 | COLB2 | COLB3 | COLB5 ;
		}else{
			PORTC = 0x00;
			PORTD = 0x00;
		}
		break;
		
		case 5:
		
		if(smile){
			PORTC = 0x00 | COLA1 | COLA4 | COLA6 |COLA8;
			PORTD = 0x00 | ROWB5 | COLB3 | COLB5;
			}else{
			PORTC = 0x00;
			PORTD = 0x00;
		}
		break;
		
		case 6:
		PORTC = 0x00 | COLA1 | COLA7 | COLA8;
		PORTD = 0x00 | ROWB6 | COLB2;
		break;
		
		case 7:
		if(smile){
			PORTC = 0x00;
			PORTD = 0x00;
		}else{
			PORTC = 0x00 | COLA1 | COLA4 | COLA6 |COLA8;
			PORTD = 0x00 | ROWB7 | COLB3 | COLB5;
		}
		break;
		
		case 8:
		if(smile){
			PORTC = 0x00;
			PORTD = 0x00;
		}else{
			PORTC = 0x00 | COLA4 | COLA6 |COLA7;
			PORTD = 0x00 | ROWB8 | COLB2 | COLB3 | COLB5 ;
		}
		break;
		
		default:
		break;
	}
}


uint16_t x_val = 0;
uint16_t i = 0x00;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	TimerSet(5);
	TimerOn();
	InitADC();
	PWM_on();
	double freq = 0;

    while (1) 
    {
		freq = getFreq();
		set_PWM(freq);
		calc_slouch();
		smile_frown_tick();
		while(!TimerFlag);
		TimerFlag = 0;		
    }
	return 0;
}