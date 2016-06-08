/*
 * sensores.h
 *
 * Created: 13/05/2015 11:26:03
 *  Author: Makara
 */ 


#ifndef SENSORES_H_
#define SENSORES_H_
#include <util/delay.h>
#include <avr/eeprom.h>

#define PINO_ESQ 4
#define PINO_MID 5
#define PINO_DIR 3
#define ACENDE_RED {PORTC=(1<<2);}
#define ACENDE_GRE {PORTC=(1<<0);}
#define ACENDE_BLU {PORTC=(1<<1);}
#define APAGA_TODOS {PORTC=0;}
#define TEMPO_LEITURA (100) //ms

void carregarCalibracaoEEPROM();
void initSensores(){
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);//div 64
	//resultado em ADC
	DIDR0 = (1<<PINO_DIR)|(1<<PINO_ESQ)|(1<<PINO_MID);//quando 1=ADC, 0=GPIO
	DDRC |= 0b00000111;
	APAGA_TODOS
	/*
	230,298,384,864,503,543,620,924
	199,278,349,877,480,537,624,946
	197,240,324,848,459,501,595,928
*/
	//carregarCalibracaoEEPROM();
}
uint16_t lerPino(uint8_t p){
	ADMUX = (ADMUX&0b11110000)|(p&0b00001111);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return ADC;
}
uint16_t CALIBRACAO[3][8] = {
	{230,298,384,864,503,543,620,924},
	{199,278,349,877,480,537,624,946},
	{197,240,324,848,459,501,595,928}};


uint16_t ULTIMA_LEITURA[3][4];
void calibrarBranco(){
	uint8_t a, b;
	for(a=0;a<3;a++)
		for(b=0;b<4;b++)CALIBRACAO[a][b]=0;
	for(int a=0;a<4;a++){
		ACENDE_RED;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][0]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][0]+=lerPino(PINO_MID);
		CALIBRACAO[2][0]+=lerPino(PINO_DIR);
		ACENDE_GRE;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][1]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][1]+=lerPino(PINO_MID);
		CALIBRACAO[2][1]+=lerPino(PINO_DIR);
		ACENDE_BLU;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][2]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][2]+=lerPino(PINO_MID);
		CALIBRACAO[2][2]+=lerPino(PINO_DIR);
		APAGA_TODOS;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][3]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][3]+=lerPino(PINO_MID);
		CALIBRACAO[2][3]+=lerPino(PINO_DIR);
	}
	for(a=0;a<3;a++)
		for(b=0;b<4;b++)CALIBRACAO[a][b]>>=2; // => /=4
}
void calibrarPreto(){
	uint8_t a, b;
	for(a=0;a<3;a++)
	for(b=4;b<8;b++)CALIBRACAO[a][b]=0;
	for(int a=0;a<4;a++){
		ACENDE_RED;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][4]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][4]+=lerPino(PINO_MID);
		CALIBRACAO[2][4]+=lerPino(PINO_DIR);
		ACENDE_GRE;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][5]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][5]+=lerPino(PINO_MID);
		CALIBRACAO[2][5]+=lerPino(PINO_DIR);
		ACENDE_BLU;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][6]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][6]+=lerPino(PINO_MID);
		CALIBRACAO[2][6]+=lerPino(PINO_DIR);
		APAGA_TODOS;
		_delay_ms(TEMPO_LEITURA);
		CALIBRACAO[0][7]+=lerPino(PINO_ESQ);
		CALIBRACAO[1][7]+=lerPino(PINO_MID);
		CALIBRACAO[2][7]+=lerPino(PINO_DIR);
	}
	for(a=0;a<3;a++)
		for(b=4;b<8;b++)CALIBRACAO[a][b]>>=2; // => /=4
}
void fazerLeituraCorBruto(){
	ACENDE_RED;
	_delay_ms(TEMPO_LEITURA);
	ULTIMA_LEITURA[0][0] = lerPino(PINO_ESQ);
	ULTIMA_LEITURA[1][0] = lerPino(PINO_MID);
	ULTIMA_LEITURA[2][0] = lerPino(PINO_DIR);
	ACENDE_GRE;
	_delay_ms(TEMPO_LEITURA);
	ULTIMA_LEITURA[0][1] = lerPino(PINO_ESQ);
	ULTIMA_LEITURA[1][1] = lerPino(PINO_MID);
	ULTIMA_LEITURA[2][1] = lerPino(PINO_DIR);
	ACENDE_BLU;
	_delay_ms(TEMPO_LEITURA);
	ULTIMA_LEITURA[0][2] = lerPino(PINO_ESQ);
	ULTIMA_LEITURA[1][2] = lerPino(PINO_MID);
	ULTIMA_LEITURA[2][2] = lerPino(PINO_DIR);
	APAGA_TODOS;
	_delay_ms(TEMPO_LEITURA);
	ULTIMA_LEITURA[0][3] = lerPino(PINO_ESQ);
	ULTIMA_LEITURA[1][3] = lerPino(PINO_MID);
	ULTIMA_LEITURA[2][3] = lerPino(PINO_DIR);
}
void fazerLeituraCor(){
	if(CALIBRACAO[0][4]>CALIBRACAO[0][0]){
		ACENDE_RED;
		_delay_ms(TEMPO_LEITURA);
		int32_t a, b, c;
		a = ((CALIBRACAO[0][0]-lerPino(PINO_ESQ))<<8)/(CALIBRACAO[0][4]-CALIBRACAO[0][0]);
		b = ((CALIBRACAO[1][0]-lerPino(PINO_MID))<<8)/(CALIBRACAO[1][4]-CALIBRACAO[1][0]);
		c = ((CALIBRACAO[2][0]-lerPino(PINO_DIR))<<8)/(CALIBRACAO[2][4]-CALIBRACAO[2][0]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][0] = a;
		ULTIMA_LEITURA[1][0] = b;
		ULTIMA_LEITURA[2][0] = c;
		ACENDE_GRE;
		_delay_ms(TEMPO_LEITURA);
		a = ((CALIBRACAO[0][1]-lerPino(PINO_ESQ))<<8)/(CALIBRACAO[0][5]-CALIBRACAO[0][1]);
		b = ((CALIBRACAO[1][1]-lerPino(PINO_MID))<<8)/(CALIBRACAO[1][5]-CALIBRACAO[1][1]);
		c = ((CALIBRACAO[2][1]-lerPino(PINO_DIR))<<8)/(CALIBRACAO[2][5]-CALIBRACAO[2][1]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][1] = a;
		ULTIMA_LEITURA[1][1] = b;
		ULTIMA_LEITURA[2][1] = c;
		ACENDE_BLU;
		_delay_ms(TEMPO_LEITURA);
		a = ((CALIBRACAO[0][2]-lerPino(PINO_ESQ))<<8)/(CALIBRACAO[0][6]-CALIBRACAO[0][2]);
		b = ((CALIBRACAO[1][2]-lerPino(PINO_MID))<<8)/(CALIBRACAO[1][6]-CALIBRACAO[1][2]);
		c = ((CALIBRACAO[2][2]-lerPino(PINO_DIR))<<8)/(CALIBRACAO[2][6]-CALIBRACAO[2][2]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][2] = a;
		ULTIMA_LEITURA[1][2] = b;
		ULTIMA_LEITURA[2][2] = c;
		APAGA_TODOS;
		_delay_ms(TEMPO_LEITURA);
		a = ((CALIBRACAO[0][3]-lerPino(PINO_ESQ))<<8)/(CALIBRACAO[0][7]-CALIBRACAO[0][3]);
		b = ((CALIBRACAO[1][3]-lerPino(PINO_MID))<<8)/(CALIBRACAO[1][7]-CALIBRACAO[1][3]);
		c = ((CALIBRACAO[2][3]-lerPino(PINO_DIR))<<8)/(CALIBRACAO[2][7]-CALIBRACAO[2][3]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][3] = a;
		ULTIMA_LEITURA[1][3] = b;
		ULTIMA_LEITURA[2][3] = c;
	}else{
		ACENDE_RED;
		_delay_ms(TEMPO_LEITURA);
		int32_t a, b, c;
		a = ((lerPino(PINO_ESQ)-CALIBRACAO[0][0])<<8)/(CALIBRACAO[0][0]-CALIBRACAO[0][4]);
		b = ((lerPino(PINO_MID)-CALIBRACAO[1][0])<<8)/(CALIBRACAO[1][0]-CALIBRACAO[1][4]);
		c = ((lerPino(PINO_DIR)-CALIBRACAO[2][0])<<8)/(CALIBRACAO[2][0]-CALIBRACAO[2][4]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][0] = a;
		ULTIMA_LEITURA[1][0] = b;
		ULTIMA_LEITURA[2][0] = c;
		ACENDE_GRE;
		_delay_ms(TEMPO_LEITURA);
		a = ((lerPino(PINO_ESQ)-CALIBRACAO[0][1])<<8)/(CALIBRACAO[0][1]-CALIBRACAO[0][5]);
		b = ((lerPino(PINO_MID)-CALIBRACAO[1][1])<<8)/(CALIBRACAO[1][1]-CALIBRACAO[1][5]);
		c = ((lerPino(PINO_DIR)-CALIBRACAO[2][1])<<8)/(CALIBRACAO[2][1]-CALIBRACAO[2][5]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][1] = a;
		ULTIMA_LEITURA[1][1] = b;
		ULTIMA_LEITURA[2][1] = c;
		ACENDE_BLU;
		_delay_ms(TEMPO_LEITURA);
		a = ((lerPino(PINO_ESQ)-CALIBRACAO[0][2])<<8)/(CALIBRACAO[0][2]-CALIBRACAO[0][6]);
		b = ((lerPino(PINO_MID)-CALIBRACAO[1][2])<<8)/(CALIBRACAO[1][2]-CALIBRACAO[1][6]);
		c = ((lerPino(PINO_DIR)-CALIBRACAO[2][2])<<8)/(CALIBRACAO[2][2]-CALIBRACAO[2][6]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][2] = a;
		ULTIMA_LEITURA[1][2] = b;
		ULTIMA_LEITURA[2][2] = c;
		APAGA_TODOS;
		_delay_ms(TEMPO_LEITURA);
		a = ((lerPino(PINO_ESQ)-CALIBRACAO[0][3])<<8)/(CALIBRACAO[0][3]-CALIBRACAO[0][7]);
		b = ((lerPino(PINO_MID)-CALIBRACAO[1][3])<<8)/(CALIBRACAO[1][3]-CALIBRACAO[1][7]);
		c = ((lerPino(PINO_DIR)-CALIBRACAO[2][3])<<8)/(CALIBRACAO[2][3]-CALIBRACAO[2][7]);
		if(a>255)a=255;		if(a<0)a=0;
		if(b>255)b=255;		if(b<0)b=0;
		if(c>255)c=255;		if(c<0)c=0;
		ULTIMA_LEITURA[0][3] = a;
		ULTIMA_LEITURA[1][3] = b;
		ULTIMA_LEITURA[2][3] = c;
	}		
}
void carregarCalibracaoEEPROM(){
	for(int a=0;a<3;a++)
		for(int b=0;b<8;b++)CALIBRACAO[a][b] = eeprom_read_word((uint16_t*)(b*2+a*16));
}
void salvarCalibracaoEEPROM(){
	for(int a=0;a<3;a++)
		for(int b=0;b<8;b++)eeprom_write_word((uint16_t*)(b*2+a*16),CALIBRACAO[a][b]);
}


#endif /* SENSORES_H_ */