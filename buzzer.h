/*
 * buzzer.h
 *
 * Created: 10/11/2023 8:01:37 AM
 *  Author: HD STORE
 */ 


void BUZZER_init(char port , char bin);

void BUZZER_ON(char port , char bin);

void BUZZER_OFF(char port , char bin);

void BUZZER_TOOGLE(char port , char bin);

char BUZZER_READSTATUS(char port, char bin );
