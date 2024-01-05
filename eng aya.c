#include <avr/io.h>
#include <avr/interrupt.h>
#include "macro.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdbool.h>
#include "DIO.h"
#include <avr/interrupt.h>//to use bilt in functions in interrupt
#define cc   //common cathode
#include "lcd.h"
#include "keypad.h"
#include <stdio.h>
#include <math.h>
#include <float.h>
int main(void)
{	BUTTON_init('c',0);
	keypad_inti();
	label:	LCD_inti();
LCD_send_command(64); // to create a special char << refeer to continue list of menue
LCD_send_data(0x03);
LCD_send_data(0x03);
LCD_send_data(0x03);
LCD_send_data(0x1F);
LCD_send_data(0x1F);
LCD_send_data(0x03);
LCD_send_data(0x03);
LCD_send_data(0x03);
//power
LCD_send_data( 0x07);
LCD_send_data(0x05);
LCD_send_data(0x07);
LCD_send_data(0x00);
LCD_send_data(0x14);
LCD_send_data(0x08);
LCD_send_data(0x14);
LCD_send_data(0x00);

int counter;  // index of array
bool flag1=true; // to loop in first input and operation
bool flag2=false; //to loop on second number
int i,j,k,m; //counters used in loops
int count_num1=0 , count_num2=0 ,count_num3=0 ; //just to count number of digit in first number // number of digit in second input // digits in third cofficient "just when choose second degree equation"
long  powerr=0; 
double integralPart, fractionalPart;
//to display start in lcd
LCD_move_cursore(1,4);
LCD_send_string("start .  .  .");
_delay_ms(1500);
LCD_clear_screen();
while(1)
{
	flag1=true;
	flag2=false;
	counter=0;
int operation=0;
	double f_num=0; //collect all digits in first numbers
	double s_num=0; //collect all digits in second numbers
	count_num2=0;
	count_num1=0;
	double final_result=0;
	powerr=0;
	int arr[16]={NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,} ;
	LCD_move_cursore(1,4);
	LCD_clear_screen();
	LCD_send_string("1- Basic");
	_delay_ms(1000);
	LCD_move_cursore(2,1);
	_delay_ms(800);
	LCD_send_string("2- Advanced");
	_delay_ms(1500);
	LCD_clear_screen();
	if(BUTTON_read('c',0)==1){ // if button pressed mean the basic calculator is selected
	counter=1;	// to start write in array from index 1 , not 0 << to make access easy
	while(flag1){ 
	do
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED);
	
	if(arr[counter]=='+'||arr[counter]=='-'||arr[counter]=='*'||arr[counter]=='/')
	{
		LCD_send_data(arr[counter]);
		counter++;
		operation++;
		flag1=false;
		flag2=true;
		
	}
	else if( arr[counter]=='A'){ //delete
		LCD_send_command(0x10); //shift cursore  to left
		operation--;
		counter--;
		}
	else // number
	{
		LCD_send_data(arr[counter]); // normally send  number
		counter++;
		operation++;
		count_num1++;
	}	
	_delay_ms(300);
	}
	//count_num1== num of numbers+ index of operation;
	while(flag2){ //  start to access second input 
		do
		{
			arr[counter]=keypad_check_press();
			
		} while(arr[counter]==NOTPRESSED);
		
		if(arr[counter]=='=')
		{
			LCD_send_data(arr[counter]); //send ==
			flag2=false;
			flag1=true;
				
		}
		else
		{
			LCD_send_data(arr[counter]);
			counter++;
			count_num2++;
		}
		
		_delay_ms(300);
	}
	if(arr[counter]=='=')
	{
		// start to collect first num together
		powerr=pow(10,(count_num2-1));
		for(i=1;i<=count_num1;i++){
			f_num+=(((arr[i])-48)*powerr);
			if(powerr!=1){
			powerr=powerr/ 10;}
		}
		//start to collect second number together
		powerr=pow(10,(count_num2-1));
		for(j=2;j<=count_num2+1;j++){
			s_num+=(((arr[j+count_num1])-48)*powerr);
			if(powerr!=1){
			powerr=powerr/ 10;}}
		switch(arr[operation])
		{
							
			case '+':
			final_result=f_num+s_num;
			break;
		
			case '-':
			final_result=f_num-s_num;
			break;
			
			case '*':
			final_result=f_num*s_num;
			break;
			
			case '/':
		    final_result=f_num/s_num;
			break; }//end of switch
			
			//to display number
			LCD_move_cursore(2,1);
			fractionalPart = modf(final_result, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable 
			lcd_sendFloat(integralPart); //show int part 
			LCD_send_data('.');
			fractionalPart*=10000;
		lcd_sendFloat(fractionalPart); //show numbers after dot
	
		
	}

	}	
	
	else if(BUTTON_read('c',0)!=1){ //button not pressed refeeer to advanced calculator ( sqrt , equation triangle , equation of second degree , power , log)
		///////////////////////////////////////////////
		counter=0;
		flag1=true;
		flag2=false;
		LCD_move_cursore(1,1);
		LCD_send_string("1: Sqrt"); //squr root
		_delay_ms(800);
		LCD_move_cursore(1,9);
		LCD_send_string("2: "); //power
		LCD_send_data(1);
		_delay_ms(800);
		LCD_move_cursore(2,1); // ??????? ??????
		LCD_send_string("3: Log");	
	_delay_ms(800);
	LCD_move_cursore(2,16);
	LCD_send_data(0);
	_delay_ms(1500);
	LCD_clear_screen();
	LCD_move_cursore(1,1);
	LCD_send_string("4: triangle equ."); //log
	_delay_ms(800);
	LCD_move_cursore(2,1);
	LCD_send_string("5- convert");
	_delay_ms(1500);
	
	LCD_clear_screen();
	
	do // to choose one of these (five operation in advanced calculator) //counter==0
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED);
	 LCD_clear_screen();
	 counter++;
	if(arr[0]=='1' || arr[0]=='2' || arr[0]=='3'){ // choose sqrt / power / log
		
		if(arr[0]=='1'){
		LCD_send_string("Sqrt(");}
		if(arr[0]=='2'){
		LCD_send_string("pow(");}
			if(arr[0]=='3'){
			LCD_send_string("log(");}
		_delay_ms(800);
		while(flag1){
			do
			{
				arr[counter]=keypad_check_press();
				
			} while(arr[counter]==NOTPRESSED);
			
			if(arr[counter]=='=')
			{
				if(arr[0]=='1'){ // cause i need just to acess one num
				LCD_send_string(") ");
				LCD_send_string("= ");
				counter++;
				flag1=false;
				flag2=false;}
				else if(arr[0]=='2' || arr[0]=='3'){
					LCD_send_string(" , ");
					//LCD_send_string("= ");
					counter++;
					flag1=false;
					flag2=true; // to go to second loop to access num 2
				}
			}
			else // number
			{
				LCD_send_data(arr[counter]); // normally send  number
				counter++;
				count_num1++;
			}
			
			
			_delay_ms(300);
		}
		
		while(flag2){ //  start to access power
		do
		{
			arr[counter]=keypad_check_press();
			
		} while(arr[counter]==NOTPRESSED);
		
		if(arr[counter]=='=')
		{
			LCD_send_string(") ");
			_delay_ms(300);
			LCD_send_string("=");
			flag2=false;
			flag1=true;
		}
		else
		{
			LCD_send_data(arr[counter]);
			counter++;
			count_num2++;
		}
		
		_delay_ms(300);
	}
	if(arr[0]=='1' || arr[0]=='2' || arr[0]=='3'){ // to start to collect first num
		powerr=pow(10,(count_num1-1));
		for(i=1;i<=count_num1;i++){
			f_num+=(((arr[i])-48)*powerr);
			if(powerr!=1){
			powerr=powerr/ 10;}
		} }
		
		if( arr[0]=='2' || arr[0]=='3') { // if power | log choosen , i need to collect the second number
			powerr=pow(10,(count_num2-1));
			for(j=2;j<=count_num2+1;j++){
				s_num+=(((arr[j+count_num1])-48)*powerr);
				if(powerr!=1){
				powerr=powerr/ 10;}
			}
			}
		
		// display number
		if(arr[0]=='1'){
		final_result=sqrt(f_num);}
		
		if(arr[0]=='2'){
		final_result=final_result=pow(f_num,s_num);}
		if(arr[0]=='3'){
		final_result=(log(f_num))/(log(s_num));}
		//start to display
		
		LCD_move_cursore(2,1);
fractionalPart = modf(final_result, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
lcd_sendFloat(integralPart); //show int part
LCD_send_data('.');
fractionalPart*=10000;
lcd_sendFloat(fractionalPart); //show numbers after dot
		final_result=0;
	}
	
////////////////////////
if(arr[0]=='4'){ // choose Trigonometric equation 
	_delay_ms(500);
	LCD_move_cursore(1,1);
	LCD_send_string("1: Sin");
	_delay_ms(500);
	LCD_move_cursore(1,10);
	LCD_send_string("2: Cos");
	_delay_ms(500);
	LCD_move_cursore(2,1);
	LCD_send_string("3: Tan");
	_delay_ms(1600);
	LCD_clear_screen();
	arr[0]=NOTPRESSED; //overwrite again
	counter=0;
	do
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED); //get the read if user choose (sin | cos | tan) // counter here==0
	
    
	 if(arr[0]=='1' || arr[0]=='2' || arr[0]=='3'){// sin | cos | tan
		 counter++; //counter==1
		 if(arr[0]=='1'){
LCD_send_string("sin( ");}
if(arr[0]=='2'){
LCD_send_string("cos( ");}
if(arr[0]=='3'){
LCD_send_string("tan( ");}
_delay_ms(800);
while(flag1){ //access number
	do
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED);
	
	if(arr[counter]=='=')
	{
		LCD_send_string(" ) ");
		LCD_send_data(arr[counter]); //send = to lcd
		flag1=false;
	
	}
	else // number
	{
		LCD_send_data(arr[counter]); // normally send  number
		counter++;
		count_num1++;
	}
	_delay_ms(300);
}}

  //


//start to collect number together
	powerr=pow(10,(count_num1-1));
	for(i=1;i<=count_num1;i++){
		f_num+=(((arr[i])-48)*powerr);
		if(powerr!=1){
		powerr=powerr/ 10;}
	}
	
	// display number
	if(arr[0]=='1'){
	final_result=sin(f_num);}
	if(arr[0]=='2'){
	final_result=cos(f_num);}
	if(arr[0]=='3'){
	final_result=tan(f_num);}
LCD_move_cursore(2,1);
fractionalPart = modf(final_result, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
lcd_sendFloat(integralPart); //show int part
LCD_send_data('.');
fractionalPart*=10000;
lcd_sendFloat(fractionalPart); //show numbers after dot
final_result=0;}
//////////////////


	if(arr[0]=='5'){ // conversion
	_delay_ms(500);
	LCD_move_cursore(1,1);
	LCD_send_string("1: Hex");
	_delay_ms(500);
	LCD_move_cursore(1,9);
	LCD_send_string("2: Octal");
	_delay_ms(500);
	LCD_move_cursore(2,1);
	LCD_send_string("3: Binary");
	_delay_ms(1600);
	LCD_clear_screen();
	arr[0]=NOTPRESSED; //overwrite again
	counter=0;
	do
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED); //get the read if user choose (hex | binary | octal) // counter here==0
	if(arr[0]=='1' || arr[0]=='2' || arr[0]=='3'){
	counter++; //counter==1
	_delay_ms(800);
	while(flag1){ //access number
	do
	{
		arr[counter]=keypad_check_press();
		
	} while(arr[counter]==NOTPRESSED);
	
	if(arr[counter]=='=')
	{
		LCD_send_data(arr[counter]); //send = to lcd
		flag1=false;
		
	}
	else // number
	{
		LCD_send_data(arr[counter]); // normally send  number
		counter++;
		count_num1++;
	}
	_delay_ms(300);
}}

//


//start to collect number together
powerr=pow(10,(count_num1-1));
for(i=1;i<=count_num1;i++){
	f_num+=(((arr[i])-48)*powerr);
	if(powerr!=1){
	powerr=powerr/ 10;}
}
if(arr[0]=='3'){
	lcd_decimalToBinary(f_num);}
	
	 }	
	 
	}	 
	
	
	_delay_ms(2300);
		LCD_clear_screen();	
}
//end of big while
}	//end of main



















	

	