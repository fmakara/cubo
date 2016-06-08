/*
 * serial.h
 *
 * Created: 13/05/2015 11:22:29
 *  Author: Makara
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_
#include <avr/interrupt.h>
//LER / escrever em UDR
#define SIZE_OUTBUFF 200
#define SIZE_INBUFF 20
char INBUFF[SIZE_INBUFF], OUTBUFF[SIZE_OUTBUFF];
uint8_t iniINBUFF, fimINBUFF;
uint8_t iniOUTBUFF, fimOUTBUFF;
void initSerial(uint32_t baud){
	UBRR0 = 1000000/baud;
	UCSR0A = (1<<U2X0);//Double transmission rate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);//habilita tx+rx + interrupcoes
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);//assync, 8 bit, np, 1 sb
	iniINBUFF = 0;
	fimINBUFF = 0;
	iniOUTBUFF = 0;
	fimOUTBUFF = 0;
	sei();
}
ISR(USART_RX_vect){
	INBUFF[fimINBUFF] = UDR0;
	fimINBUFF++;
	if(fimINBUFF>=SIZE_INBUFF)fimINBUFF = 0;
}
ISR(USART_TX_vect){
	if(iniOUTBUFF!=fimOUTBUFF){
		UDR0 = OUTBUFF[iniOUTBUFF];
		iniOUTBUFF++;
		if(iniOUTBUFF>=SIZE_OUTBUFF)iniOUTBUFF = 0;
	}
}
void putch(char a){
	cli();
	if((UCSR0A & (1<<UDRE0))&&(iniOUTBUFF==fimOUTBUFF)){//mandar imediatamente
		UDR0 = a;
	}else{//botar no buffer
		uint8_t b=fimOUTBUFF;
		if(b<iniOUTBUFF)b+=SIZE_OUTBUFF;
		while(b-iniOUTBUFF>=SIZE_OUTBUFF-1);//Espera que o buff esteja com um slot vasio
		OUTBUFF[fimOUTBUFF] = a;
		fimOUTBUFF++;
		if(fimOUTBUFF>=SIZE_OUTBUFF)fimOUTBUFF=0;
	}
	sei();
}
char getch(){
	if(iniINBUFF==fimINBUFF)return 0;
	uint8_t a = iniINBUFF;
	iniINBUFF++;
	if(iniINBUFF>=SIZE_INBUFF)iniINBUFF = 0;
	return INBUFF[a];
}
char peek(){
	return INBUFF[iniINBUFF];
}
uint8_t available(){
	uint8_t a = iniINBUFF;
	if(a>fimINBUFF)a+=SIZE_INBUFF;
	return fimINBUFF-a;
}
void putStr(char* s){
	while(*s != 0){
		putch(*s);
		s++;
	}
}
void printIntCasas(int a, int casas){
	char buff[10] = {'0','0','0','0','0','0','0','0','0','0'};
	int b;
	if(a<0){
		putch('-');
		a = -a;
	}
	for(b=9 ; a>0 ; b--,a/=10)buff[b] = (a%10)+'0';
	for(b=0;b<9 && buff[b]=='0';b++);
	for(;casas>10-b;casas--)putch('0');
	for(;b<10;b++)putch(buff[b]);
}
void printInt(int32_t a){
	char buff[10] = {'0','0','0','0','0','0','0','0','0','0'};
	int b;
	if(a<0){
		putch('-');
		a = -a;
	}
	for(b=9 ; a>0 ; b--,a/=10)buff[b] = (a%10)+'0';
	for(b=0;b<9 && buff[b]=='0';b++);
	for(;b<10;b++)putch(buff[b]);
}


#endif /* SERIAL_H_ */