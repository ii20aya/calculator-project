/*
 * eng_aya.c
 *
 * Created: 10/7/2023 12:18:50 PM
 *  Author: HD STORE
 */ 



#include "macro.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "DIO.h"
#include "7seg.h"
#include "led.h"
#include "butt.h"
#include "buzzer.h"
#define cc   //common cathode

int main(void)
{				
	BUZZER_init('c',0);
	LED_init('c',2);
	BUTTON_init('c',7);
	seven_seg_bcd_inti('A');
	seven_seg_bcd_inti('B');
	unsigned char count=0;
	unsigned char flag1=0;
	unsigned char flag2=0;
	unsigned char readbutton=0;
	
	////////////////////// end of inti
	while(1){
		//////
		while(flag1<=9){ 
			readbutton= BUTTON_read('c',7);      //loop in first 7seg
			if(readbutton==1){
				count++;
			}
			if(count>9){
				count=0;
			}
			
			seven_segbcd_write('A',count);
			_delay_ms(200);
			
			if(count==7) //number 7 choosen by me 
			{  
			  BUZZER_ON('c',0); //point the number of pressing button == number i choose 
			  LED_ON('c',2);
			  _delay_ms(1000);
			   BUZZER_OFF('c',0);
		       LED_OFF('c',2);
		        break;
			}
			flag1++; 	        	
		
		}
		//////////////////end of while for 7seg connected porta
		while(flag2!=9){
			readbutton= BUTTON_read('c',7);
			if(readbutton==1){
				count++;
			}
			if(count>9){
				count=0;
			}
			seven_segbcd_write('b',count);
			_delay_ms(200);
			
			if(count==3){  //point the number is true
			BUZZER_ON('c',0);
			LED_ON('c',2);
			_delay_ms(1000);
			BUZZER_OFF('c',0);
			LED_OFF('c',2);
			break;
		}
		flag2++;
		}
			
		
		
	}	//end of  last while
	}
			
		
		/*
		
		
		if(BUTTON_read('c',7)==1){
			count++;
		}
		if(count<10){
			count=0;
		}
		seven_segbcd_write('a',count);
		
		
		if(count==7){  //point the number is true
		BUZZER_ON('c',0);
		LED_ON('c',2);
		_delay_ms(1000);
		BUZZER_OFF('c',0);
		LED_OFF('c',2);
	}
		
		
		
		
		
		
		
		
		
		
		LED_init('a',0);
		LED_init('a',3);
		LED_init('a',5);
		BUTTON_init('a',7);
		unsigned char count=0;
		while(1)
		{
			
			if(count==6){
				count=0;
			}
			
			
			if((BUTTON_read('a',7)==1) && (count==0)){                    
				_delay_ms(30); // to avoid bouncing switch
				if((BUTTON_read('a',7)==1) && (count=0)){
				LED_ON('a',0);
				count++;
				}}
				
				
				
				
				if((BUTTON_read('a',7)==0) && (count==1)){
					_delay_ms(30);
					if((BUTTON_read('a',7)==0) && (count==1)){
					LED_OFF('a',0);
					count++;
					
				}}
				
				
				
				
			
			if((BUTTON_read('a',7)==1) &&( count==2)){
				_delay_ms(30);
				if((BUTTON_read('a',7)==1) &&( count==2)){
				LED_ON('a',3);
				count++;
				
			}}
			
			
			
			if((BUTTON_read('a',7)==0) && (count==3)){
				_delay_ms(30);
				if((BUTTON_read('a',7)==0) && (count==3)){
				LED_OFF('a',3);
				count++;
				
			}}
			
			if((BUTTON_read('a',7)==1) && (count==4)){
				_delay_ms(30);
				if((BUTTON_read('a',7)==1) && (count==4)){
				LED_ON('a',5);
				count++;
				
			}}
			
			
			if((BUTTON_read('a',7)==0) && (count==5)){
				_delay_ms(30);
				if((BUTTON_read('a',7)==0) && (count==5)){
				LED_OFF('a',5);
				count++;
				
			}}


		}
		
		_delay_ms(200);*/
		
		
		/*while(1){
			if(   (BUTTON_read('d',0)==1) )  {
				_delay_ms(30);
				if(   (BUTTON_read('d',0)==1)  ) {
					press=1;}}
					
					
					
					
					if(press==1){
				    for(count=0;count<=9;count++){
					LED_ON('c',0);
					seven_seg_write_commka('a',count);
					
				         }
				LED_OFF('c',0);
				press++;
					}				
				
					if(press==2){			
			for(count=0;count<=9;count++){
					LED_ON('c',2);
					seven_seg_write_commka('a',count);
				}
				LED_OFF('c',2);
				press++;}		
				
				if(press==3){
				for(count=0;count<=9;count++){
					LED_ON('c',5);
					seven_seg_write_commka('a',count);
				}
				LED_OFF('c',5);
				
				press++;}
				
				if(press>3)
				press=0;
				
			}*/
			
													