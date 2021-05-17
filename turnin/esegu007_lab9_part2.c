/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab 9  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://drive.google.com/file/d/1Jdt4cAGQ6o9txNGToNNbPfrDm4etNZl5/view?usp=sharing
 */
#include <avr/io.h>
#include "../header/timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    unsigned char threeLEDs;
    unsigned char blinkingLED;
    unsigned char threeCount = 0x01;
    unsigned char blinkCount = 0x01;
    enum ThreeLEDsSMs {SM_Start, SM_0, SM_1, SM_2} ThreeLEDsSM;
    enum BlinkLEDsSMs {SM_Start1, SM_On, SM_Off} BlinkLEDsSM;
    enum CombineLEDsSMs {SM_Start2, SM_Combine} CombineLEDsSM;
    void TickFct(){
    	switch(ThreeLEDsSM){
    		case SM_Start:
    			ThreeLEDsSM = SM_0;
    		break;
    		case SM_0:
    		if(threeCount == 0x3){
    			ThreeLEDsSM = SM_1;
    			threeCount = 0x1;
    		}
    		else{
    			threeCount++;
    		}
    		break;
    		case SM_1:
    		if(threeCount == 0x3){
    			ThreeLEDsSM = SM_2;
    			threeCount = 0x1;
    		}
    		else{
    			threeCount++;
    		}
    		break;
    		case SM_2:
    		if(threeCount == 0x3){
    			ThreeLEDsSM = SM_0;
    			threeCount = 0x1;
    		}
    		else{
    			threeCount++;
    		}
    		break;
    	}
    	switch(ThreeLEDsSM){
    		case SM_Start:
    		break;
    		case SM_0:
    			threeLEDs = 0x01;
    		break;
    		case SM_1:
    			threeLEDs = 0x02;
    		break;
    		case SM_2:
    			threeLEDs = 0x04;
    		break;
    	}
    }
     void BlinkTickFct(){
    	switch(BlinkLEDsSM){
    		case SM_Start1:
    			BlinkLEDsSM = SM_On;
    		break;
    		case SM_On:
    			if(blinkCount == 0x0A){
    				BlinkLEDsSM = SM_Off;
    				blinkCount = 0x01;
    			}
    			else{
    				blinkCount++;
    			}
    		break;
    		case SM_Off:
     			if(blinkCount == 0x0A){
    				BlinkLEDsSM = SM_On;
    				blinkCount = 0x01;
    			}
    			else{
    				blinkCount++;
    			}
    		break;
    	}
    	switch(BlinkLEDsSM){
    		case SM_Start1:
    		break;
    		case SM_On:
    			blinkingLED = 0x01;
    		break;
    		case SM_Off:
    			blinkingLED = 0x00;
    		break;
    	}
    }
     void CombineTickFct(){
    	switch(CombineLEDsSM){
    		case SM_Start:
    		CombineLEDsSM = SM_Combine;
    		break;
    		case SM_Combine:
    		CombineLEDsSM = SM_Combine;
    		break;
    	}
    	switch(CombineLEDsSM){
    		case SM_Start:
    		break;
    		case SM_Combine:
    			PORTB = blinkingLED << 3;
    			PORTB += threeLEDs;
    		break;
    }
}
    TimerSet(100);
    TimerOn();
    ThreeLEDsSM = SM_Start;
    CombineLEDsSM = SM_Start2;
    BlinkLEDsSM = SM_Start1;
    /* Insert your solution below */
    while (1) {
    	TickFct();
    	BlinkTickFct();
    	CombineTickFct();
    	while(!TimerFlag);
    	TimerFlag = 0;
    }
    return 1;
}
