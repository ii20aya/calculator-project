/*
 * buzzer.c
 *
 * Created: 10/11/2023 8:01:21 AM
 *  Author: HD STORE
 */ 
#include "DIO.h"
#include <avr/io.h>
void BUZZER_init(char port , char bin){

	
	
	DIO_SET_BINDIR(port, bin , 0);
	

}
/////////////////////////////////////////

void BUZZER_ON(unsigned char port ,unsigned char bin){
	DIO_WRITE(port , bin ,1);
}
//////////////////////////////////////////////////

void BUZZER_OFF(unsigned char port , unsigned char bin){
	
	
	
	DIO_WRITE(port, bin , 0);
	
}
//////////////////////////////////

void BUZZER_TOOGLE(unsigned char port , unsigned char bin){
	
	DIO_toggle(port, bin );
	
}
//////////////////////////////////////

char BUZZER_READSTATUS(char port, char bin ){
	return DIO_READ(port,bin);

}