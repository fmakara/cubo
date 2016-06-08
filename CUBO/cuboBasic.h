/*
 * cuboBasic.h
 *
 * Created: 14/05/2015 09:29:50
 *  Author: Makara
 */ 


#ifndef CUBOBASIC_H_
#define CUBOBASIC_H_
#include "motores.h"
#include "sensores.h"
#include <util/delay.h>

char girarCubo(int16_t graus){
	levantaBraco();
	switch(graus){
		case 90:
		for(int a=0;a<120;a++)passoROTHOR();
		break;
		case 180:
		for(int a=0;a<240;a++)passoROTHOR();
		break;
		case 270:
		for(int a=0;a<360;a++)passoROTHOR();
		break;
		case 360:
		for(int a=0;a<480;a++)passoROTHOR();
		break;
		case -90:
		for(int a=0;a<120;a++)passoROTANT();
		break;
		case -180:
		for(int a=0;a<240;a++)passoROTANT();
		break;
		case -270:
		for(int a=0;a<360;a++)passoROTANT();
		break;
		case -360:
		for(int a=0;a<480;a++)passoROTANT();
		break;
	}
	soltaROT();
	soltaBraco();
	return 1;
}
char torceCubo(int16_t graus){
	const int k = 10;
	switch(graus){
		case 90:
		for(int a=0;a<120+k;a++)passoROTHOR();
		for(int a=0;a<k;a++)passoROTANT();
		break;
		case 180:
		for(int a=0;a<240+k;a++)passoROTHOR();
		for(int a=0;a<k;a++)passoROTANT();
		break;
		case 270:
		for(int a=0;a<360+k;a++)passoROTHOR();
		for(int a=0;a<k;a++)passoROTANT();
		break;
		case 360:
		for(int a=0;a<480+k;a++)passoROTHOR();
		for(int a=0;a<k;a++)passoROTANT();
		break;
		case -90:
		for(int a=0;a<120+k;a++)passoROTANT();
		for(int a=0;a<k;a++)passoROTHOR();
		break;
		case -180:
		for(int a=0;a<240+k;a++)passoROTANT();
		for(int a=0;a<k;a++)passoROTHOR();
		break;
		case -270:
		for(int a=0;a<360+k;a++)passoROTANT();
		for(int a=0;a<k;a++)passoROTHOR();
		break;
		case -360:
		for(int a=0;a<480+k;a++)passoROTANT();
		for(int a=0;a<k;a++)passoROTHOR();
		break;
	}
	soltaROT();
	return 1;
}
char tombaCubo(){
	uint16_t a, b;
	for(a=0;a<4;a++){
		translateTo(0);
		//Levanta braco por breve periodo
		BUFFER_BYTE |= (1<<1);
		BUFFER_BYTE &=~(1<<0);
		sendFullSPI(BUFFER_BYTE);
		_delay_ms(15);
		BUFFER_BYTE &=~(1<<1);
		sendFullSPI(BUFFER_BYTE);
		for(b=0;b<64000;b++){
			if(!(PIND&(1<<6)))b = 65000;
			_delay_us(10);
		}
		if(b<65000){
			BUFFER_BYTE |= (1<<1);
			BUFFER_BYTE &=~(1<<0);
			sendFullSPI(BUFFER_BYTE);
			_delay_ms(15);
			BUFFER_BYTE &=~(1<<1);
			sendFullSPI(BUFFER_BYTE);
			
			for(b=0;b<64000;b++){
				if(!(PIND&(1<<6)))b = 65000;
				_delay_us(10);
			}
		}
		if(b<65000){
			BUFFER_BYTE |= (1<<1);
			BUFFER_BYTE &=~(1<<0);
			sendFullSPI(BUFFER_BYTE);
			_delay_ms(15);
			BUFFER_BYTE &=~(1<<1);
			sendFullSPI(BUFFER_BYTE);
			
			for(b=0;b<64000;b++){
				if(!(PIND&(1<<6)))b = 65000;
				_delay_us(10);
			}
		}
		translateTo(310);
		translateTo(275);
		if(b>=65000){
			a = 6;
		}else{
			treme();
		}
	}
	if(a==4)return 0;
	return 1;
}
uint8_t FACES[6];//U L F R B D, Front para fora
#define UP 0
#define LF 1
#define FR 2
#define RI 3
#define BK 4
#define DW 5

//Idéia: guardar as faces todo o tempo e quando executar um movimento, trocar as faces de lugar
//Face[a] = b -> face B está na posicao A
void resetFaces(){
	for(int a=0;a<6;a++)FACES[a] = a;
}
#define UP_CW 0
#define UP_CC 1
#define LF_CW 2
#define LF_CC 3
#define FR_CW 4
#define FR_CC 5
#define RI_CW 6
#define RI_CC 7
#define BK_CW 8
#define BK_CC 9
#define DW_CW 10
#define DW_CC 11
char executarMovimento(uint8_t m){//UCW UCCW LCW LCCW FCW FCCW RCW RCCW BCW BCCW DCW DCCW
	uint8_t face = m>>1, a, pos = 0;
	for(a=0;a<6;a++)if(face==FACES[a])pos=a;
	//for(a=0;a<6;a++){
	//	printInt(FACES[a]);
	//	putch(' ');
	//}
	//printInt(pos);
	//putch('=');
	//printInt(face);
	//putch('\n');
	switch(pos){
		case UP://Up -> tomba, tomba
		//UP LF FR RI BK DW
		//DW LF BK RI FR UP
		a = FACES[DW];
		FACES[DW] = FACES[UP];
		FACES[UP] = a;
		a = FACES[BK];
		FACES[BK] = FACES[FR];
		FACES[FR] = a;
		treme();
		if(!tombaCubo())return 0;
		treme();
		if(!tombaCubo())return 0;
		break;
		case LF://Left--> CW, tomba
		//UP LF FR RI BK DW
		//BK DW LF UP RI FR
		a = FACES[UP];
		FACES[UP] = FACES[RI];
		FACES[RI] = FACES[BK];
		FACES[BK] = a;
		a = FACES[LF];
		FACES[LF] = FACES[FR];
		FACES[FR] = FACES[DW];
		FACES[DW] = a;
		treme();
		if(!girarCubo(90))return 0;
		treme();
		if(!tombaCubo())return 0;
		break;
		case FR: //Front--> CW, CW, tomba ***alternativa: tomba, tomba, tomba
		//UP LF FR RI BK DW
		//BK RI DW LF UP FR
		/*
		a = FACES[LF];
		FACES[LF] = FACES[RI];
		FACES[RI] = a;
		a = FACES[UP];
		FACES[UP] = FACES[BK];
		FACES[BK] = a;
		a = FACES[FR];
		FACES[FR] = FACES[DW];
		FACES[DW] = a;*/
		//Usando tomba, tomba, tomba pra nao sobrecarregar levantador
		//UP LF FR RI BK DW
		//FR LF DW RI UP BK
		a = FACES[FR];
		FACES[FR] = FACES[UP];
		FACES[UP] = FACES[BK];
		FACES[BK] = FACES[DW];
		FACES[DW] = a;
		treme();
		if(!tombaCubo())return 0;
		treme();
		if(!tombaCubo())return 0;
		treme();
		if(!tombaCubo())return 0;
		break;
		case RI: //Right--> CCW, tomba
		//UP LF FR RI BK DW
		//BK UP RI DW LF FR
		a = FACES[UP];
		FACES[UP] = FACES[LF];
		FACES[LF] = FACES[BK];
		FACES[BK] = a;
		a = FACES[FR];
		FACES[FR] = FACES[DW];
		FACES[DW] = FACES[RI];
		FACES[RI] = a;
		treme();
		if(!girarCubo(-90))return 0;
		treme();
		if(!tombaCubo())return 0;
		break;
		case BK: //Back--> tomba
		//UP LF FR RI BK DW
		//BK LF UP RI DW FR
		a = FACES[UP];
		FACES[UP] = FACES[FR];
		FACES[FR] = FACES[DW];
		FACES[DW] = FACES[BK];
		FACES[BK] = a;
		treme();
		if(!tombaCubo())return 0;
		break;
		case DW: //Já tá na posicao certa
		break;
	}
	treme();
	if(m&1){
		if(!torceCubo(90))return 0;
	}else{
		if(!torceCubo(-90))return 0;
	}
	return 1;
}
void leituraInicial(uint16_t *cores){//[54]
	//gira ccw, tomba, gira cw******APENAS PARA VERIFICAR CAMINHO!!
	girarCubo(-90);
	tombaCubo();
	girarCubo(90);
	//Leitura Left ---------------------------------------------------------------------
	//putStr("LEFT\n");
	levantaBraco();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[10*4+0] = ULTIMA_LEITURA[0][0];
	cores[10*4+1] = ULTIMA_LEITURA[0][1];
	cores[10*4+2] = ULTIMA_LEITURA[0][2];
	cores[10*4+3] = 0;
	cores[11*4+0] = ULTIMA_LEITURA[1][0];
	cores[11*4+1] = ULTIMA_LEITURA[1][1];
	cores[11*4+2] = ULTIMA_LEITURA[1][2];
	cores[11*4+3] = 1;
	cores[12*4+0] = ULTIMA_LEITURA[2][0];
	cores[12*4+1] = ULTIMA_LEITURA[2][1];
	cores[12*4+2] = ULTIMA_LEITURA[2][2];
	cores[12*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[9*4+0] = ULTIMA_LEITURA[0][0];
	cores[9*4+1] = ULTIMA_LEITURA[0][1];
	cores[9*4+2] = ULTIMA_LEITURA[0][2];
	cores[9*4+3] = 0;
	cores[49*4+0] = ULTIMA_LEITURA[1][0];
	cores[49*4+1] = ULTIMA_LEITURA[1][1];
	cores[49*4+2] = ULTIMA_LEITURA[1][2];
	cores[49*4+3] = 1;
	cores[13*4+0] = ULTIMA_LEITURA[2][0];
	cores[13*4+1] = ULTIMA_LEITURA[2][1];
	cores[13*4+2] = ULTIMA_LEITURA[2][2];
	cores[13*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[14*4+0] = ULTIMA_LEITURA[0][0];
	cores[14*4+1] = ULTIMA_LEITURA[0][1];
	cores[14*4+2] = ULTIMA_LEITURA[0][2];
	cores[14*4+3] = 0;
	cores[15*4+0] = ULTIMA_LEITURA[1][0];
	cores[15*4+1] = ULTIMA_LEITURA[1][1];
	cores[15*4+2] = ULTIMA_LEITURA[1][2];
	cores[15*4+3] = 1;
	cores[8*4+0] = ULTIMA_LEITURA[2][0];
	cores[8*4+1] = ULTIMA_LEITURA[2][1];
	cores[8*4+2] = ULTIMA_LEITURA[2][2];
	cores[8*4+3] = 2;
	translateTo(310);
	//Leitura Right----------------------------------------------------------------
	//putStr("RIGHT\n");
	tombaCubo();
	tombaCubo();
	levantaBraco();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[30*4+0] = ULTIMA_LEITURA[0][0];
	cores[30*4+1] = ULTIMA_LEITURA[0][1];
	cores[30*4+2] = ULTIMA_LEITURA[0][2];
	cores[30*4+3] = 0;
	cores[31*4+0] = ULTIMA_LEITURA[1][0];
	cores[31*4+1] = ULTIMA_LEITURA[1][1];
	cores[31*4+2] = ULTIMA_LEITURA[1][2];
	cores[31*4+3] = 1;
	cores[24*4+0] = ULTIMA_LEITURA[2][0];
	cores[24*4+1] = ULTIMA_LEITURA[2][1];
	cores[24*4+2] = ULTIMA_LEITURA[2][2];
	cores[24*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[29*4+0] = ULTIMA_LEITURA[0][0];
	cores[29*4+1] = ULTIMA_LEITURA[0][1];
	cores[29*4+2] = ULTIMA_LEITURA[0][2];
	cores[29*4+3] = 0;
	cores[51*4+0] = ULTIMA_LEITURA[1][0];
	cores[51*4+1] = ULTIMA_LEITURA[1][1];
	cores[51*4+2] = ULTIMA_LEITURA[1][2];
	cores[51*4+3] = 1;
	cores[25*4+0] = ULTIMA_LEITURA[2][0];
	cores[25*4+1] = ULTIMA_LEITURA[2][1];
	cores[25*4+2] = ULTIMA_LEITURA[2][2];
	cores[25*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[26*4+0] = ULTIMA_LEITURA[0][0];
	cores[26*4+1] = ULTIMA_LEITURA[0][1];
	cores[26*4+2] = ULTIMA_LEITURA[0][2];
	cores[26*4+3] = 0;
	cores[27*4+0] = ULTIMA_LEITURA[1][0];
	cores[27*4+1] = ULTIMA_LEITURA[1][1];
	cores[27*4+2] = ULTIMA_LEITURA[1][2];
	cores[27*4+3] = 1;
	cores[28*4+0] = ULTIMA_LEITURA[2][0];
	cores[28*4+1] = ULTIMA_LEITURA[2][1];
	cores[28*4+2] = ULTIMA_LEITURA[2][2];
	cores[28*4+3] = 2;
	translateTo(310);
	//Leitura Back--------------------------------------------------------------
	//putStr("BACK\n");
	tombaCubo();
	levantaBraco();
	translateTo(50);
	for(int a=0;a<120;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[32*4+0] = ULTIMA_LEITURA[0][0];
	cores[32*4+1] = ULTIMA_LEITURA[0][1];
	cores[32*4+2] = ULTIMA_LEITURA[0][2];
	cores[32*4+3] = 0;
	cores[33*4+0] = ULTIMA_LEITURA[1][0];
	cores[33*4+1] = ULTIMA_LEITURA[1][1];
	cores[33*4+2] = ULTIMA_LEITURA[1][2];
	cores[33*4+3] = 1;
	cores[34*4+0] = ULTIMA_LEITURA[2][0];
	cores[34*4+1] = ULTIMA_LEITURA[2][1];
	cores[34*4+2] = ULTIMA_LEITURA[2][2];
	cores[34*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[39*4+0] = ULTIMA_LEITURA[0][0];
	cores[39*4+1] = ULTIMA_LEITURA[0][1];
	cores[39*4+2] = ULTIMA_LEITURA[0][2];
	cores[39*4+3] = 0;
	cores[52*4+0] = ULTIMA_LEITURA[1][0];
	cores[52*4+1] = ULTIMA_LEITURA[1][1];
	cores[52*4+2] = ULTIMA_LEITURA[1][2];
	cores[52*4+3] = 1;
	cores[35*4+0] = ULTIMA_LEITURA[2][0];
	cores[35*4+1] = ULTIMA_LEITURA[2][1];
	cores[35*4+2] = ULTIMA_LEITURA[2][2];
	cores[35*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[36*4+0] = ULTIMA_LEITURA[0][0];
	cores[36*4+1] = ULTIMA_LEITURA[0][1];
	cores[36*4+2] = ULTIMA_LEITURA[0][2];
	cores[36*4+3] = 0;
	cores[37*4+0] = ULTIMA_LEITURA[1][0];
	cores[37*4+1] = ULTIMA_LEITURA[1][1];
	cores[37*4+2] = ULTIMA_LEITURA[1][2];
	cores[37*4+3] = 1;
	cores[38*4+0] = ULTIMA_LEITURA[2][0];
	cores[38*4+1] = ULTIMA_LEITURA[2][1];
	cores[38*4+2] = ULTIMA_LEITURA[2][2];
	cores[38*4+3] = 2;
	translateTo(310);
	//Leitura Down-------------------------------------------------------------
	//putStr("DOWN\n");
	tombaCubo();
	levantaBraco();
	translateTo(50);
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[44*4+0] = ULTIMA_LEITURA[0][0];
	cores[44*4+1] = ULTIMA_LEITURA[0][1];
	cores[44*4+2] = ULTIMA_LEITURA[0][2];
	cores[44*4+3] = 0;
	cores[45*4+0] = ULTIMA_LEITURA[1][0];
	cores[45*4+1] = ULTIMA_LEITURA[1][1];
	cores[45*4+2] = ULTIMA_LEITURA[1][2];
	cores[45*4+3] = 1;
	cores[46*4+0] = ULTIMA_LEITURA[2][0];
	cores[46*4+1] = ULTIMA_LEITURA[2][1];
	cores[46*4+2] = ULTIMA_LEITURA[2][2];
	cores[46*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[43*4+0] = ULTIMA_LEITURA[0][0];
	cores[43*4+1] = ULTIMA_LEITURA[0][1];
	cores[43*4+2] = ULTIMA_LEITURA[0][2];
	cores[43*4+3] = 0;
	cores[53*4+0] = ULTIMA_LEITURA[1][0];
	cores[53*4+1] = ULTIMA_LEITURA[1][1];
	cores[53*4+2] = ULTIMA_LEITURA[1][2];
	cores[53*4+3] = 1;
	cores[47*4+0] = ULTIMA_LEITURA[2][0];
	cores[47*4+1] = ULTIMA_LEITURA[2][1];
	cores[47*4+2] = ULTIMA_LEITURA[2][2];
	cores[47*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[40*4+0] = ULTIMA_LEITURA[0][0];
	cores[40*4+1] = ULTIMA_LEITURA[0][1];
	cores[40*4+2] = ULTIMA_LEITURA[0][2];
	cores[40*4+3] = 0;
	cores[41*4+0] = ULTIMA_LEITURA[1][0];
	cores[41*4+1] = ULTIMA_LEITURA[1][1];
	cores[41*4+2] = ULTIMA_LEITURA[1][2];
	cores[41*4+3] = 1;
	cores[42*4+0] = ULTIMA_LEITURA[2][0];
	cores[42*4+1] = ULTIMA_LEITURA[2][1];
	cores[42*4+2] = ULTIMA_LEITURA[2][2];
	cores[42*4+3] = 2;
	translateTo(310);
	//Leitura Front-----------------------------------------------------------
	//putStr("FRONT\n");
	tombaCubo();
	levantaBraco();
	translateTo(50);
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[20*4+0] = ULTIMA_LEITURA[0][0];
	cores[20*4+1] = ULTIMA_LEITURA[0][1];
	cores[20*4+2] = ULTIMA_LEITURA[0][2];
	cores[20*4+3] = 0;
	cores[21*4+0] = ULTIMA_LEITURA[1][0];
	cores[21*4+1] = ULTIMA_LEITURA[1][1];
	cores[21*4+2] = ULTIMA_LEITURA[1][2];
	cores[21*4+3] = 1;
	cores[22*4+0] = ULTIMA_LEITURA[2][0];
	cores[22*4+1] = ULTIMA_LEITURA[2][1];
	cores[22*4+2] = ULTIMA_LEITURA[2][2];
	cores[22*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[19*4+0] = ULTIMA_LEITURA[0][0];
	cores[19*4+1] = ULTIMA_LEITURA[0][1];
	cores[19*4+2] = ULTIMA_LEITURA[0][2];
	cores[19*4+3] = 0;
	cores[50*4+0] = ULTIMA_LEITURA[1][0];
	cores[50*4+1] = ULTIMA_LEITURA[1][1];
	cores[50*4+2] = ULTIMA_LEITURA[1][2];
	cores[50*4+3] = 1;
	cores[23*4+0] = ULTIMA_LEITURA[2][0];
	cores[23*4+1] = ULTIMA_LEITURA[2][1];
	cores[23*4+2] = ULTIMA_LEITURA[2][2];
	cores[23*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[16*4+0] = ULTIMA_LEITURA[0][0];
	cores[16*4+1] = ULTIMA_LEITURA[0][1];
	cores[16*4+2] = ULTIMA_LEITURA[0][2];
	cores[16*4+3] = 0;
	cores[17*4+0] = ULTIMA_LEITURA[1][0];
	cores[17*4+1] = ULTIMA_LEITURA[1][1];
	cores[17*4+2] = ULTIMA_LEITURA[1][2];
	cores[17*4+3] = 1;
	cores[18*4+0] = ULTIMA_LEITURA[2][0];
	cores[18*4+1] = ULTIMA_LEITURA[2][1];
	cores[18*4+2] = ULTIMA_LEITURA[2][2];
	cores[18*4+3] = 2;
	translateTo(310);
	//Leitura top---------------------------------------------------------------------------
	//putStr("TOP\n");
	tombaCubo();
	levantaBraco();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	cores[0*4+0] = ULTIMA_LEITURA[0][0];
	cores[0*4+1] = ULTIMA_LEITURA[0][1];
	cores[0*4+2] = ULTIMA_LEITURA[0][2];
	cores[0*4+3] = 0;
	cores[1*4+0] = ULTIMA_LEITURA[1][0];
	cores[1*4+1] = ULTIMA_LEITURA[1][1];
	cores[1*4+2] = ULTIMA_LEITURA[1][2];
	cores[1*4+3] = 1;
	cores[2*4+0] = ULTIMA_LEITURA[2][0];
	cores[2*4+1] = ULTIMA_LEITURA[2][1];
	cores[2*4+2] = ULTIMA_LEITURA[2][2];
	cores[2*4+3] = 2;
	translateTo(70);
	fazerLeituraCorBruto();
	cores[7*4+0] = ULTIMA_LEITURA[0][0];
	cores[7*4+1] = ULTIMA_LEITURA[0][1];
	cores[7*4+2] = ULTIMA_LEITURA[0][2];
	cores[7*4+3] = 0;
	cores[48*4+0] = ULTIMA_LEITURA[1][0];
	cores[48*4+1] = ULTIMA_LEITURA[1][1];
	cores[48*4+2] = ULTIMA_LEITURA[1][2];
	cores[48*4+3] = 1;
	cores[3*4+0] = ULTIMA_LEITURA[2][0];
	cores[3*4+1] = ULTIMA_LEITURA[2][1];
	cores[3*4+2] = ULTIMA_LEITURA[2][2];
	cores[3*4+3] = 2;
	for(int a=0;a<240;a++)passoROTHOR();
	soltaROT();
	translateTo(160);
	fazerLeituraCorBruto();
	cores[4*4+0] = ULTIMA_LEITURA[0][0];
	cores[4*4+1] = ULTIMA_LEITURA[0][1];
	cores[4*4+2] = ULTIMA_LEITURA[0][2];
	cores[4*4+3] = 0;
	cores[5*4+0] = ULTIMA_LEITURA[1][0];
	cores[5*4+1] = ULTIMA_LEITURA[1][1];
	cores[5*4+2] = ULTIMA_LEITURA[1][2];
	cores[5*4+3] = 1;
	cores[6*4+0] = ULTIMA_LEITURA[2][0];
	cores[6*4+1] = ULTIMA_LEITURA[2][1];
	cores[6*4+2] = ULTIMA_LEITURA[2][2];
	cores[6*4+3] = 2;
	translateTo(310);
	translateTo(275);
	//putStr("FIM_LEITURA\n");
}
uint16_t CALIB[2][3][3];//[MAX,min][R,G,B][sens1,sens2,sens3]
void autoAjustar(uint16_t *cores){
	CALIB[0][0][0] = 1024;CALIB[0][0][1] = 1024;CALIB[0][0][2] = 1024;
	CALIB[0][1][0] = 1024;CALIB[0][1][1] = 1024;CALIB[0][1][2] = 1024;
	CALIB[0][2][0] = 1024;CALIB[0][2][1] = 1024;CALIB[0][2][2] = 1024;
	CALIB[1][0][0] = 0;CALIB[1][0][1] = 0;CALIB[1][0][2] = 0;
	CALIB[1][1][0] = 0;CALIB[1][1][1] = 0;CALIB[1][1][2] = 0;
	CALIB[1][2][0] = 0;CALIB[1][2][1] = 0;CALIB[1][2][2] = 0;
	for(int a=0;a<54;a++){
		if(cores[a*4+0]>CALIB[1][0][cores[a*4+3]])CALIB[1][0][cores[a*4+3]] = cores[a*4+0];
		if(cores[a*4+1]>CALIB[1][1][cores[a*4+3]])CALIB[1][1][cores[a*4+3]] = cores[a*4+1];
		if(cores[a*4+2]>CALIB[1][2][cores[a*4+3]])CALIB[1][2][cores[a*4+3]] = cores[a*4+2];
		if(cores[a*4+0]<CALIB[0][0][cores[a*4+3]])CALIB[0][0][cores[a*4+3]] = cores[a*4+0];
		if(cores[a*4+1]<CALIB[0][1][cores[a*4+3]])CALIB[0][1][cores[a*4+3]] = cores[a*4+1];
		if(cores[a*4+2]<CALIB[0][2][cores[a*4+3]])CALIB[0][2][cores[a*4+3]] = cores[a*4+2];
	}
	for(int a=0;a<54;a++){
		uint8_t b = cores[a*4+3];
		cores[a*4+0] = ((CALIB[1][0][b]-cores[a*4+0])<<8)/(CALIB[1][0][b]-CALIB[0][0][b]);
		cores[a*4+1] = ((CALIB[1][1][b]-cores[a*4+1])<<8)/(CALIB[1][1][b]-CALIB[0][1][b]);
		cores[a*4+2] = ((CALIB[1][2][b]-cores[a*4+2])<<8)/(CALIB[1][2][b]-CALIB[0][2][b]);
	}
}
char verificaCores(char *coresOriginal, char *cuboAtual){
	uint8_t coresLidas[6][3];
	uint8_t facesLidas[6];
	//Ler cor e calibrar
	levantaBraco();
	translateTo(160);
	soltaBraco();
	fazerLeituraCorBruto();
	coresLidas[0][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[0][0])<<8)/(CALIB[1][0][0]-CALIB[0][0][0]);
	coresLidas[0][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[0][1])<<8)/(CALIB[1][1][0]-CALIB[0][1][0]);
	coresLidas[0][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[0][2])<<8)/(CALIB[1][2][0]-CALIB[0][2][0]);
	coresLidas[1][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[1][0])<<8)/(CALIB[1][0][1]-CALIB[0][0][1]);
	coresLidas[1][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[1][1])<<8)/(CALIB[1][1][1]-CALIB[0][1][1]);
	coresLidas[1][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[1][2])<<8)/(CALIB[1][2][1]-CALIB[0][2][1]);
	coresLidas[2][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[2][0])<<8)/(CALIB[1][0][2]-CALIB[0][0][2]);
	coresLidas[2][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[2][1])<<8)/(CALIB[1][1][2]-CALIB[0][1][2]);
	coresLidas[2][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[2][2])<<8)/(CALIB[1][2][2]-CALIB[0][2][2]);
	translateTo(70);
	fazerLeituraCorBruto();
	coresLidas[3][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[0][0])<<8)/(CALIB[1][0][0]-CALIB[0][0][0]);
	coresLidas[3][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[0][1])<<8)/(CALIB[1][1][0]-CALIB[0][1][0]);
	coresLidas[3][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[0][2])<<8)/(CALIB[1][2][0]-CALIB[0][2][0]);
	coresLidas[4][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[1][0])<<8)/(CALIB[1][0][1]-CALIB[0][0][1]);
	coresLidas[4][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[1][1])<<8)/(CALIB[1][1][1]-CALIB[0][1][1]);
	coresLidas[4][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[1][2])<<8)/(CALIB[1][2][1]-CALIB[0][2][1]);
	coresLidas[5][0] = ((CALIB[1][0][0]-ULTIMA_LEITURA[2][0])<<8)/(CALIB[1][0][2]-CALIB[0][0][2]);
	coresLidas[5][1] = ((CALIB[1][1][0]-ULTIMA_LEITURA[2][1])<<8)/(CALIB[1][1][2]-CALIB[0][1][2]);
	coresLidas[5][2] = ((CALIB[1][2][0]-ULTIMA_LEITURA[2][2])<<8)/(CALIB[1][2][2]-CALIB[0][2][2]);
	translateTo(310);
	//Achar cor mais proxima
	
	//uint32_t distancias[6], menor;
	for(int a=0;a<6;a++){
		uint32_t distancias[6], menor;
		for(int b=0;b<6;b++){
			int32_t x, y, z;
			x = coresLidas[a][0]-coresOriginal[(48+b)*4+0];
			y = coresLidas[a][1]-coresOriginal[(48+b)*4+1];
			z = coresLidas[a][2]-coresOriginal[(48+b)*4+2];
			distancias[b] = x*x+y*y+z*z;
		}
		//resultado[a] = 0;
		menor = distancias[0];
		for(int b=1;b<6;b++)if(distancias[b]<menor){
			menor = distancias[b];
			facesLidas[a] = b;
		}
	}
	return 1;
	
}
void printColor(uint16_t *cores){
	for(int a=0;a<54;a++){
		printInt(a);
		putch('=');
		printInt(cores[a*4+0]);
		putch(',');
		printInt(cores[a*4+1]);
		putch(',');
		printInt(cores[a*4+2]);
		putch('\n');
		_delay_ms(50);
	}
}
void achaMenorDistancia(int16_t *cores, uint8_t *resultado){
	//Distancia direta
	for(int a=0;a<8*6;a++){
		uint32_t distancias[6], menor;
		for(int b=0;b<6;b++){
			int32_t x, y, z;
			x = cores[a*4+0]-cores[(48+b)*4+0];
			y = cores[a*4+1]-cores[(48+b)*4+1];
			z = cores[a*4+2]-cores[(48+b)*4+2];
			distancias[b] = x*x+y*y+z*z;
		}
		resultado[a] = 0;
		menor = distancias[0];
		for(int b=1;b<6;b++)if(distancias[b]<menor){
			menor = distancias[b];
			resultado[a] = b;
		}
	}
}
uint8_t checaConsistencia(uint8_t *posicoes){
	//int8_t movimentos[MAX_JOGADAS];
	uint8_t a[6] = {0,0,0,0,0,0};
	for(int b=0;b<48;b++)a[posicoes[b]]++;
	if(a[0]!=8 || a[1]!=8 || a[2]!=8 || a[3]!=8 || a[4]!=8 || a[5]!=8)return 0;
	return 1;
}

#endif /* CUBOBASIC_H_ */