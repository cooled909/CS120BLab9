/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab 9  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://drive.google.com/file/d/1jP4Y9SCfY3OdzGd9YHETEuVENG0XTtWJ/view?usp=sharing
 */
#include <avr/io.h>
#include "../header/timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned char threeLEDs;
    unsigned char blinkingLED;
    unsigned char soundOut;
    unsigned short threeCount = 0x01;
    unsigned short blinkCount = 0x01;
    unsigned char SoundCount = 0x01;
    unsigned char SoundFreq = 0x01;
    unsigned char OnOffSound = 0x00;
    unsigned char button0;
    unsigned char button1;
    unsigned char button2;
    enum ThreeLEDsSMs {SM_Start, SM_0, SM_1, SM_2} ThreeLEDsSM;
    enum BlinkLEDsSMs {SM_Start1, SM_On, SM_Off} BlinkLEDsSM;
    enum SoundSMs {SM_Start3, SM_OffAll, SM_SoundOff, SM_SoundOn} SoundSM;
    enum ButtonSMs {SM_Start4, SM_Wait, SM_Up, SM_Down, SM_OnSound, SM_Press} ButtonSM;
    enum CombineLEDsSMs {SM_Start2, SM_Combine} CombineLEDsSM;
    void ButtonFct(){
    	switch(ButtonSM){
    		case SM_Start4:
    		ButtonSM = SM_Wait;
    		break;
    		case SM_Wait:
    		if(button0 && !button1 && !button2){
    			ButtonSM = SM_Up;
    		}
    		else if(!button0 && button1 && !button2){
    			ButtonSM = SM_Down;
    		}
    		else if(!button0 && !button1 && button2){
    			ButtonSM = SM_OnSound;
    		}
    		break;
    		case SM_OnSound:
    		if(!button0 && !button1 && !button2){
    			ButtonSM = SM_Wait;
    		}
    		break;
    		case SM_Up:
    		ButtonSM = SM_Press;
    		break;
    		case SM_Down:
    		ButtonSM = SM_Press;
    		break;
    		case SM_Press:
    		if(!button0 && !button1 && !button2){
    			ButtonSM = SM_Wait;
    		}
    		break;
    	}
    	switch(ButtonSM){
    		case SM_Start4:
    		break;
    		case SM_Wait:
    		OnOffSound = 0x00;
    		break;
    		case SM_OnSound:
    		OnOffSound = 0x01;
    		break;
    		case SM_Up:
    		if(SoundFreq > 1){
    		SoundFreq--;
    		}
    		break;
    		case SM_Down:
    		SoundFreq++;
    		break;
    		case SM_Press:
    		break;
    }
}
    void TickFct(){
    	switch(ThreeLEDsSM){
    		case SM_Start:
    			ThreeLEDsSM = SM_0;
    		break;
    		case SM_0:
    		if(threeCount == 0x12C){
    			ThreeLEDsSM = SM_1;
    			threeCount = 0x1;
    		}
    		else{
    			threeCount++;
    		}
    		break;
    		case SM_1:
    		if(threeCount == 0x12C){
    			ThreeLEDsSM = SM_2;
    			threeCount = 0x1;
    		}
    		else{
    			threeCount++;
    		}
    		break;
    		case SM_2:
    		if(threeCount == 0x12C){
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
    			if(blinkCount == 0x3E8){
    				BlinkLEDsSM = SM_Off;
    				blinkCount = 0x01;
    			}
    			else{
    				blinkCount++;
    			}
    		break;
    		case SM_Off:
     			if(blinkCount == 0x3E8){
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
    			PORTB = soundOut << 4;
    			PORTB += blinkingLED << 3;
    			PORTB += threeLEDs;
    		break;
    	}
    }
    void SoundTickFct(){
    	switch(SoundSM){
    		case SM_Start3:
    		SoundSM = SM_OffAll;
    		break;
    		case SM_OffAll:
    		if(OnOffSound == 0x01){
    			SoundSM = SM_SoundOn;
    		}
    		break;
    		case SM_SoundOn:
    		if(OnOffSound == 0x00){
    			SoundSM = SM_OffAll;
    		}
    		else if(SoundCount == SoundFreq){
    			SoundSM = SM_SoundOff;
    			SoundCount = 0x01;
    		}
    		else{
    			SoundCount++;
    		}
    		break;
    		case SM_SoundOff:
    		if(OnOffSound == 0x00){
    			SoundSM = SM_OffAll;
    		}
    		else if(SoundCount == SoundFreq){
    			SoundSM = SM_SoundOn;
    			SoundCount = 0x01;
    		}
    		else{
    			SoundCount++;
    		}
    		break;
    	}
    	switch(SoundSM){
    		case SM_Start3:
    		break;
    		case SM_OffAll:
    		soundOut = 0;
    		break;
    		case SM_SoundOn:
    		soundOut = 0x01;
    		break;
    		case SM_SoundOff:
    		soundOut = 0;
    		break;
    	}
    }
    TimerSet(1);
    TimerOn();
    ThreeLEDsSM = SM_Start;
    CombineLEDsSM = SM_Start2;
    BlinkLEDsSM = SM_Start1;
    SoundSM = SM_Start3;
    ButtonSM = SM_Start4;
    /* Insert your solution below */
    while (1) {
    	button0 = ~PINA & 0x01;
    	button1 = ~PINA & 0x02;
    	button2 = ~PINA & 0x04;
    	TickFct();
    	BlinkTickFct();
    	ButtonFct();
    	SoundTickFct();
    	CombineTickFct();
    	while(!TimerFlag);
    	TimerFlag = 0;
    }
    return 1;
}
