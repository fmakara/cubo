/*
 * CUBO.c
 *
 * Created: 11/05/2015 15:16:03
 *  Author: Makara
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "serial.h"
#include "motores.h"
#include "sensores.h"
#include "cuboBasic.h"
#include "cuboAvancado.h"

char resolver();
int main(void){
	initMotors();
	initSerial(9600);
	initSensores();
	putStr("Inicializado!\n");
	soltaBraco();
	tombaCubo();
	while(1){
		char erro = resolver();
		switch(erro){
			case 0:
				putStr("Resolvido!");
				levantaBraco();
				for(int a=0;a<4*480;a++)passoROTHOR();
				soltaROT();
				soltaBraco();
				_delay_ms(10000);
				break;
			case 1:
				putStr("Erro de consistencia\n");
				_delay_ms(10000);
				break;
			case 2:
				putStr("Erro ao solucionar cubo\n");
				_delay_ms(10000);
				break;
			case 3:
				putStr("Erro ao executar movimento\n");
				_delay_ms(10000);
				break;
			case 4:
				putStr("Erro de sincronia\n");
				_delay_ms(10000);
				break;	
		}
	}
}

char resolver(){
	resetFaces();
	uint16_t cores[54*4];
	uint8_t cubo[48];
	int8_t movimentos[MAX_JOGADAS];
	leituraInicial(cores);
	autoAjustar(cores);
	//printColor(cores);
	achaMenorDistancia((int16_t*)cores,cubo);
	printColor(cores);
	if(!checaConsistencia(cubo))return 1;
	if(!solve_enhanced(cubo, movimentos))return 2;
	simplify(movimentos);
	int nrJogadas = 0;
	for(nrJogadas=0;movimentos[nrJogadas]>=0 && nrJogadas<MAX_JOGADAS;nrJogadas++);
	putStr("Resolvendo agora com ");
	printInt(nrJogadas);
	putStr(" jogadas\n");
	_delay_ms(10);
	for(int a=0;a<nrJogadas;a++){
		putStr("J:");
		printInt(a);
		putStr(" => ");
		printInt(movimentos[a]);
		putch('\n');
		if(!executarMovimento(movimentos[a]))return 3;
	}	
	return 0;
}