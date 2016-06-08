/*
 * motores.h
 *
 * Created: 13/05/2015 11:22:29
 *  Author: Makara
 */ 


#ifndef MOTORES_H_
#define MOTORES_H_
#include <util/delay.h>
//posicao repouso -> empurrando = 45
//posicao repouso -> caido = 250
//girando 90 graus = 120
void sendFullSPI(uint8_t v){
	uint8_t a;
	for(a=0;a<8;a++,v=v<<1){
		if(v&(1<<7))PORTD |= (1<<3);
		else        PORTD &=~(1<<3);
		_delay_us(10);
		PORTD |= (1<<4);
		_delay_us(10);
		PORTD &=~(1<<4);
	}
	_delay_us(10);
	PORTD |= (1<<2);
	_delay_us(10);
	PORTD &=~(1<<2);
}
uint8_t BUFFER_BYTE;
int16_t SUBPASSO_ROT, SUBPASSO_TRANS;
void initMotors(){
	DDRD |= 0b10011100;
	DDRB |= 0b00000111;
	PORTD &= ~(1<<7);
	PORTB &= ~((1<<0)|(1<<1)|(1<<2));
	BUFFER_BYTE = 1;
	sendFullSPI(BUFFER_BYTE);
	SUBPASSO_ROT = 0;
	SUBPASSO_TRANS = 0;
	DDRB &= ~((1<<6)|(1<<7));//Sensores
	DDRD &= ~((1<<5)|(1<<6));
	
}
void levantaBraco(){
	BUFFER_BYTE |= (1<<1);
	BUFFER_BYTE &=~(1<<0);
	sendFullSPI(BUFFER_BYTE);
	while(PIND&(1<<6));
	_delay_ms(50);
	BUFFER_BYTE &=~(1<<1);
	sendFullSPI(BUFFER_BYTE);
	_delay_ms(300);
}
void soltaBraco(){
	BUFFER_BYTE |= (1<<0);
	BUFFER_BYTE &=~(1<<1);
	sendFullSPI(BUFFER_BYTE);
	_delay_ms(200);
	BUFFER_BYTE &=~(1<<0);
	sendFullSPI(BUFFER_BYTE);
	_delay_ms(200);
}
void soltaROT(){
	PORTD &= ~(1<<7);
	PORTB &= ~((1<<0)|(1<<1)|(1<<2));
}
void passoROTHOR(){
	uint8_t a = SUBPASSO_ROT&0b00000111;
	switch(a){
		case 0:
		PORTD |= (1<<7);
		PORTB &= ~((1<<0)|(1<<1)|(1<<2));
		break;
		case 1:
		PORTB &= ~((1<<1)|(1<<2));
		PORTD |= (1<<7);
		PORTB |= (1<<0);
		break;
		case 2:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<1)|(1<<2));
		PORTB |= (1<<0);
		break;
		case 3:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<2));
		PORTB |= (1<<1)|(1<<0);
		break;
		case 4:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0)|(1<<2));
		PORTB |= (1<<1);
		break;
		case 5:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0));
		PORTB |= (1<<1)|(1<<2);
		break;
		case 6:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0)|(1<<1));
		PORTB |= (1<<2);
		break;
		case 7:
		PORTB &= ~((1<<0)|(1<<1));
		PORTB |= (1<<2);
		PORTD |= (1<<7);
		break;
	}
	SUBPASSO_ROT++;
	_delay_ms(3);
}
void passoROTANT(){
	uint8_t a = SUBPASSO_ROT&0b00000111;
	switch(a){
		case 0:
		PORTD |= (1<<7);
		PORTB &= ~((1<<0)|(1<<1)|(1<<2));
		break;
		case 1:
		PORTB &= ~((1<<1)|(1<<2));
		PORTD |= (1<<7);
		PORTB |= (1<<0);
		break;
		case 2:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<1)|(1<<2));
		PORTB |= (1<<0);
		break;
		case 3:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<2));
		PORTB |= (1<<1)|(1<<0);
		break;
		case 4:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0)|(1<<2));
		PORTB |= (1<<1);
		break;
		case 5:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0));
		PORTB |= (1<<1)|(1<<2);
		break;
		case 6:
		PORTD &= ~(1<<7);
		PORTB &= ~((1<<0)|(1<<1));
		PORTB |= (1<<2);
		break;
		case 7:
		PORTB &= ~((1<<0)|(1<<1));
		PORTB |= (1<<2);
		PORTD |= (1<<7);
		break;
	}
	SUBPASSO_ROT--;
	_delay_ms(3);
}
void passoFRENTE(){
	uint8_t a = SUBPASSO_TRANS&0b00000111;
	BUFFER_BYTE &= ~(0b11110000);
	switch(a){
		case 0:
		BUFFER_BYTE |=  (0b00010000);
		break;
		case 1:
		BUFFER_BYTE |=  (0b01010000);
		break;
		case 2:
		BUFFER_BYTE |=  (0b01000000);
		break;
		case 3:
		BUFFER_BYTE |=  (0b01100000);
		break;
		case 4:
		BUFFER_BYTE |=  (0b00100000);
		break;
		case 5:
		BUFFER_BYTE |=  (0b10100000);
		break;
		case 6:
		BUFFER_BYTE |=  (0b10000000);
		break;
		case 7:
		BUFFER_BYTE |=  (0b10010000);
		break;
	}
	sendFullSPI(BUFFER_BYTE);
	SUBPASSO_TRANS++;
	SUBPASSO_TRANS++;
	_delay_ms(1);
	sendFullSPI(BUFFER_BYTE&0b00001111);
	_delay_ms(3);
}
void passoTRAS(){
	if(PIND&(1<<5)){
		uint8_t a = SUBPASSO_TRANS&0b00000111;
		BUFFER_BYTE &= ~(0b11110000);
		switch(a){
			case 0:
			BUFFER_BYTE |=  (0b00010000);
			break;
			case 1:
			BUFFER_BYTE |=  (0b01010000);
			break;
			case 2:
			BUFFER_BYTE |=  (0b01000000);
			break;
			case 3:
			BUFFER_BYTE |=  (0b01100000);
			break;
			case 4:
			BUFFER_BYTE |=  (0b00100000);
			break;
			case 5:
			BUFFER_BYTE |=  (0b10100000);
			break;
			case 6:
			BUFFER_BYTE |=  (0b10000000);
			break;
			case 7:
			BUFFER_BYTE |=  (0b10010000);
			break;
		}
		sendFullSPI(BUFFER_BYTE);
		SUBPASSO_TRANS--;
		SUBPASSO_TRANS--;
		_delay_ms(3);
		sendFullSPI(BUFFER_BYTE&0b00001111);
		_delay_ms(1);
	}else{
		SUBPASSO_TRANS = 0;
	}		
}
void soltaTrans(){
	BUFFER_BYTE &= ~(0b11110000);
	sendFullSPI(BUFFER_BYTE);
}
void zerarRotacao(){
	while(!(PIND&(1<<5))){
		passoROTANT();
	}
	while(PIND&(1<<5)){
		passoROTANT();
	}
	SUBPASSO_ROT = 0;
}
void translateTo(int16_t pos){
	if(pos<=0){
		while(PIND&(1<<5)){
			passoTRAS();
			
		}
		SUBPASSO_TRANS = 0;
	}else{
		if(pos>SUBPASSO_TRANS){
			while(pos>SUBPASSO_TRANS){
				passoFRENTE();
			}				
		}else{
			while(pos<SUBPASSO_TRANS){
				passoTRAS();
			}			
		}
	}
	soltaTrans();
}
void treme(){
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoTRAS();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	passoFRENTE();
	soltaTrans();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTANT();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	passoROTHOR();
	soltaROT();
	_delay_ms(50);
}

#endif /* MOTORES_H_ */