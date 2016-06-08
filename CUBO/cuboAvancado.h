/*
 * cuboAvancado.h
 *
 * Created: 15/05/2015 18:00:05
 *  Author: Makara
 */ 


#ifndef CUBOAVANCADO_H_
#define CUBOAVANCADO_H_
//#define VERBOSE

#include <string.h>
#include <avr/pgmspace.h>
//              0   1   2 
//              7   U   3
//              6   5   4
// 8    9  10 |16  17  18 |24  25  26 |32  33  34
// 15   L  11 |23  F   19 |31   R  27 |39   B  35
// 14  13  12 |22  21  20 |30  29  28 |38  37  36
//             40  41  42
//             47   D  43   U L F R B D  CW CCW
//             46  45  44
#define MAX_JOGADAS 250
void rot(uint8_t *vetor, uint8_t tipo){
   uint8_t a;
#define quadraSwap(b,c,d,e) {a=vetor[b];vetor[b]=vetor[c];vetor[c]=vetor[d];vetor[d]=vetor[e];vetor[e]=a;}
   switch(tipo){
      case 0:// Up CW
         quadraSwap(0,6,4,2);
         quadraSwap(1,7,5,3);
         quadraSwap(8 ,16,24,32);
         quadraSwap(9 ,17,25,33);
         quadraSwap(10,18,26,34);
         break;
      case 1:// Up CCW
         quadraSwap(0,2,4,6);
         quadraSwap(1,3,5,7);
         quadraSwap(8 ,32,24,16);
         quadraSwap(9 ,33,25,17);
         quadraSwap(10,34,26,18);
         break;
      case 2:// Left CW
         quadraSwap(8,14,12,10);
         quadraSwap(9,15,13,11);
         quadraSwap(0,36,40,16);
         quadraSwap(7,35,47,23);
         quadraSwap(6,34,46,22);
         break;
      case 3:// Left CCW
         quadraSwap(8,10,12,14);
         quadraSwap(9,11,13,15);
         quadraSwap(0,16,40,36);
         quadraSwap(7,23,47,35);
         quadraSwap(6,22,46,34);
         break;
      case 4:// Front CW
         quadraSwap(16,22,20,18);
         quadraSwap(17,23,21,19);
         quadraSwap(6,12,42,24);
         quadraSwap(5,11,41,31);
         quadraSwap(4,10,40,30);
         break;
      case 5:// Front CCW
         quadraSwap(16,18,20,22);
         quadraSwap(17,19,21,23);
         quadraSwap(6,24,42,12);
         quadraSwap(5,31,41,11);
         quadraSwap(4,30,40,10);
         break;
      case 6:// Right CW
         quadraSwap(24,30,28,26);
         quadraSwap(25,31,29,27);
         quadraSwap(4,20,44,32);
         quadraSwap(3,19,43,39);
         quadraSwap(2,18,42,38);
         break;
      case 7:// Right CCW
         quadraSwap(24,26,28,30);
         quadraSwap(25,27,29,31);
         quadraSwap(4,32,44,20);
         quadraSwap(3,39,43,19);
         quadraSwap(2,38,42,18);
         break;
      case 8:// Back CW
         quadraSwap(32,38,36,34);
         quadraSwap(33,39,37,35);
         quadraSwap(2,28,46,8);
         quadraSwap(1,27,45,15);
         quadraSwap(0,26,44,14);
         break;
      case 9:// Back CCW
         quadraSwap(32,34,36,38);
         quadraSwap(33,35,37,39);
         quadraSwap(2,8,46,28);
         quadraSwap(1,15,45,27);
         quadraSwap(0,14,44,26);
         break;
      case 10:// Down CW
         quadraSwap(40,46,44,42);
         quadraSwap(41,47,45,43);
         quadraSwap(22,14,38,30);
         quadraSwap(21,13,37,29);
         quadraSwap(20,12,36,28);
         break;
      case 11:// Down CCW
         quadraSwap(40,42,44,46);
         quadraSwap(41,43,45,47);
         quadraSwap(22,30,38,14);
         quadraSwap(21,29,37,13);
         quadraSwap(20,28,36,12);
         break;
   }
}
//              0   1   2 
//              7   U   3
//              6   5   4
// 8    9  10 |16  17  18 |24  25  26 |32  33  34
// 15   L  11 |23  F   19 |31   R  27 |39   B  35
// 14  13  12 |22  21  20 |30  29  28 |38  37  36
//             40  41  42
//             47   D  43   U L F R B D  CW CCW
//             46  45  44
void flop(uint8_t *vetor, uint8_t tipo){
   uint8_t a;
   //QuadraSwap ja foi definido anteriormente
   switch(tipo){
      case 0:// Up CW
	     for(a=0;a<48;a++)if(vetor[a]==1)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==2)vetor[a]=1;
	     for(a=0;a<48;a++)if(vetor[a]==3)vetor[a]=2;
	     for(a=0;a<48;a++)if(vetor[a]==4)vetor[a]=3;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=4;
         quadraSwap(0,6,4,2);
         quadraSwap(1,7,5,3);
         quadraSwap(8 ,16,24,32);
         quadraSwap(9 ,17,25,33);
         quadraSwap(10,18,26,34);
         quadraSwap(15,23,31,39);
         quadraSwap(11,19,27,35);
         quadraSwap(14,22,30,38);
         quadraSwap(13,21,29,37);
         quadraSwap(12,20,28,36);
         quadraSwap(40,42,44,46);
         quadraSwap(41,43,45,47);
         break;
      case 1:// Up CCW
	     for(a=0;a<48;a++)if(vetor[a]==1)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==4)vetor[a]=1;
	     for(a=0;a<48;a++)if(vetor[a]==3)vetor[a]=4;
	     for(a=0;a<48;a++)if(vetor[a]==2)vetor[a]=3;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=2;
         quadraSwap(0,2,4,6);
         quadraSwap(1,3,5,7);
         quadraSwap(8 ,32,24,16);
         quadraSwap(9 ,33,25,17);
         quadraSwap(10,34,26,18);
         quadraSwap(35,27,19,11);
         quadraSwap(39,31,23,15);
         quadraSwap(36,28,20,12);
         quadraSwap(37,29,21,13);
         quadraSwap(38,30,22,14);
         quadraSwap(40,46,44,42);
         quadraSwap(41,47,45,44);
         break;
      case 2:// Front CW
	     for(a=0;a<48;a++)if(vetor[a]==0)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==1)vetor[a]=0;
	     for(a=0;a<48;a++)if(vetor[a]==5)vetor[a]=1;
	     for(a=0;a<48;a++)if(vetor[a]==3)vetor[a]=5;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=3;
         quadraSwap(16,22,20,18);
         quadraSwap(17,23,21,19);
         quadraSwap(6,12,42,24);
         quadraSwap(5,11,41,31);
         quadraSwap(4,10,40,30);
         
         quadraSwap(7,13,43,25);
         quadraSwap(3,9,47,29);
         quadraSwap(0,14,44,26);
         quadraSwap(1,15,45,27);
         quadraSwap(2,8,46,28);
         quadraSwap(32,34,36,38);
         quadraSwap(33,35,37,39);
         break;
      case 3:// Front CCW
	     for(a=0;a<48;a++)if(vetor[a]==0)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==3)vetor[a]=0;
	     for(a=0;a<48;a++)if(vetor[a]==5)vetor[a]=3;
	     for(a=0;a<48;a++)if(vetor[a]==1)vetor[a]=5;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=1;
         quadraSwap(16,18,20,22);
         quadraSwap(17,19,21,23);
         quadraSwap(6,24,42,12);
         quadraSwap(5,31,41,11);
         quadraSwap(4,30,40,10);
         
         quadraSwap(7,25,43,13);
         quadraSwap(3,29,47,9);
         quadraSwap(0,26,44,14);
         quadraSwap(1,27,45,15);
         quadraSwap(2,28,46,8);
         quadraSwap(32,38,36,34);
         quadraSwap(33,39,37,35);
         break;
      case 4:// Right CW
	     for(a=0;a<48;a++)if(vetor[a]==0)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==2)vetor[a]=0;
	     for(a=0;a<48;a++)if(vetor[a]==5)vetor[a]=2;
	     for(a=0;a<48;a++)if(vetor[a]==4)vetor[a]=5;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=4;
         quadraSwap(24,30,28,26);
         quadraSwap(25,31,29,27);
         quadraSwap(4,20,44,32);
         quadraSwap(3,19,43,39);
         quadraSwap(2,18,42,38);
         
         quadraSwap(1,17,41,37);
         quadraSwap(5,21,45,33);
         quadraSwap(0,16,40,36);
         quadraSwap(7,23,47,35);
         quadraSwap(6,22,46,34);
         quadraSwap(8,10,12,14);
         quadraSwap(9,11,13,15);
//              0   1   2 
//              7   U   3
//              6   5   4
// 8    9  10 |16  17  18 |24  25  26 |32  33  34
// 15   L  11 |23  F   19 |31   R  27 |39   B  35
// 14  13  12 |22  21  20 |30  29  28 |38  37  36
//             40  41  42
//             47   D  43   U L F R B D  CW CCW
//             46  45  44
         break;
      case 5:// Right CCW
	     for(a=0;a<48;a++)if(vetor[a]==0)vetor[a]=6;
	     for(a=0;a<48;a++)if(vetor[a]==4)vetor[a]=0;
	     for(a=0;a<48;a++)if(vetor[a]==5)vetor[a]=4;
	     for(a=0;a<48;a++)if(vetor[a]==2)vetor[a]=5;
	     for(a=0;a<48;a++)if(vetor[a]==6)vetor[a]=2;
         quadraSwap(24,26,28,30);
         quadraSwap(25,27,29,31);
         quadraSwap(4,32,44,20);
         quadraSwap(3,39,43,19);
         quadraSwap(2,38,42,18);
         
         quadraSwap(1,37,41,17);
         quadraSwap(5,33,45,21);
         quadraSwap(0,36,40,16);
         quadraSwap(7,35,47,23);
         quadraSwap(6,34,46,22);
         quadraSwap(8,14,12,10);
         quadraSwap(9,15,13,11);
         break;
   }
}
//              0   1   2 
//              7   U   3
//              6   5   4
// 8    9  10 |16  17  18 |24  25  26 |32  33  34
// 15   L  11 |23  F   19 |31   R  27 |39   B  35
// 14  13  12 |22  21  20 |30  29  28 |38  37  36
//             40  41  42
//             47   D  43   U L F R B D  CW CCW
//             46  45  44
void fill(uint8_t *v){
   for(int a=0;a<6;a++)for(int b=0;b<8;b++)v[a*8+b]=a;
}
void Numberfill(uint8_t *v){
   for(int a=0;a<6;a++)for(int b=0;b<8;b++)v[a*8+b]=a*8+b;
}
void transform(uint8_t *v, uint8_t *s){
   while(*s>=0){
      rot(v,*s);
      s++;
   }
}
//              0   1   2 
//              7   U   3
//              6   5   4
// 8    9  10 |16  17  18 |24  25  26 |32  33  34
// 15   L  11 |23  F   19 |31   R  27 |39   B  35
// 14  13  12 |22  21  20 |30  29  28 |38  37  36
//             40  41  42
//             47   D  43   U L F R B D  CW CCW
//             46  45  44
const uint8_t _CRUZ[56][8] PROGMEM = {
	{35, 0, 15, 1, 2, -1},
	{23, 0, 11, 1, 3, -1},
	{11, 0, 23, 2, 4, -1},
	{31, 0, 19, 2, 5, -1},
	{19, 0, 31, 3, 6, -1},
	{39, 0, 27, 3, 7, -1},
	{27, 0, 39, 4, 8, -1},
	{15, 0, 35, 4, 9, -1},
	{47, 0, 13, 1, 2, -1},
	{41, 0, 21, 2, 4, -1},//10
	{43, 0, 29, 3, 6, -1},
	{45, 0, 37, 4, 8, -1},
	{41, 0, 21, 3, 10, -1},
	{41, 0, 21, 4, 10, 10, -1},
	{41, 0, 21, 1, 11, -1},
	{43, 0, 29, 4, 10, -1},
	{43, 0, 29, 1, 10, 10, -1},
	{43, 0, 29, 2, 11, -1},
	{45, 0, 37, 1, 10, -1},
	{45, 0, 37, 2, 10, 10, -1},//20
	{45, 0, 37, 3, 11, -1},
	{47, 0, 13, 2, 10, -1},
	{47, 0, 13, 3, 10, 10, -1},
	{47, 0, 13, 4, 11, -1},
	{29, 0, 43, 1, 10, -1},
	{21, 0, 41, 1, 10, 10, -1},
	{13, 0, 47, 1, 11, -1},
	{37, 0, 45, 1, 9, 2, 8, -1},
	{37, 0, 45, 2, 10, -1},
	{29, 0, 43, 2, 10, 10, -1},//30
	{21, 0, 41, 2, 11, -1},
	{13, 0, 47, 2, 3, 4, 2, -1},
	{13, 0, 47, 3, 10, -1},
	{37, 0, 45, 3, 10, 10, -1},
	{29, 0, 43, 3, 11, -1},
	{21, 0, 41, 3, 5, 6, 4, -1},
	{21, 0, 41, 4, 10, -1},
	{13, 0, 47, 4, 10, 10, -1},
	{37, 0, 45, 4, 11, -1},
	{29, 0, 43, 4, 7, 8, 6, -1},//40
	{35, 1, 15, 1, 3, 10, 2, -1},//regra inversa: segunda não pode ser peça
	{11, 1, 23, 2, 5, 10, 4, -1},
	{19, 1, 31, 3, 7, 10, 6, -1},
	{27, 1, 39, 4, 9, 10, 8, -1},
	{15, 1, 35, 4, 3, 10, 2, -1},
	{23, 1, 11, 1, 5, 10, 4, -1},
	{31, 1, 19, 2, 7, 10, 6, -1},
	{39, 1, 27, 3, 9, 10, 8, -1},
	{1, 1, 33, 4, 8, -1},
	{3, 1, 25, 3, 6, -1},//50
	{5, 1, 17, 2, 4, -1},
	{7, 1, 9, 1, 2, -1},
	{33, 1, 1, 6, 8, -1},
	{25, 1, 3, 6, 6, -1},
	{17, 1, 5, 6, 4, -1},
	{9, 1, 7, 6, 2, -1}//56
};
const uint8_t _FLC[48][10] PROGMEM= {
	{22, 0, 12, 4, 40, 1, 8, 11, 9, -1},
	{30, 0, 20, 1, 42, 2, 2, 11, 3, -1},
	{38, 0, 28, 2, 44, 3, 4, 11, 5, -1},
	{14, 0, 36, 3, 46, 4, 6, 11, 7, -1},
	{36, 0, 14, 2, 46, 1, 5, 10, 4, -1},
	{12, 0, 22, 3, 40, 2, 7, 10, 6, -1},
	{20, 0, 30, 4, 42, 3, 9, 10, 8, -1},
	{28, 0, 38, 1, 44, 4, 3, 10, 2, -1},//ideais
	{14, 0, 36, 4, 46, 1, 10, -1},//rotacoes de base
	{30, 0, 20, 4, 42, 1, 11, -1},//10
	{22, 0, 12, 1, 40, 2, 10, -1},
	{38, 0, 28, 1, 44, 2, 11, -1},
	{30, 0, 20, 2, 42, 3, 10, -1},
	{14, 0, 36, 2, 46, 3, 11, -1},
	{38, 0, 28, 3, 44, 4, 10, -1},
	{22, 0, 12, 3, 40, 4, 11, -1},
	{28, 0, 38, 2, 44, 1, 10, -1},
	{12, 0, 22, 2, 40, 1, 11, -1},
	{36, 0, 14, 3, 46, 2, 10, -1},
	{20, 0, 30, 3, 42, 2, 11, -1},//20
	{12, 0, 22, 4, 40, 3, 10, -1},
	{28, 0, 38, 4, 44, 3, 11, -1},
	{20, 0, 30, 1, 42, 4, 10, -1},
	{36, 0, 14, 1, 46, 4, 11, -1},
	{12, 0, 22, 1, 40, 4, 10, 10, -1},
	{36, 0, 14, 4, 46, 3, 10, 10, -1},
	{28, 0, 38, 3, 44, 2, 10, 10, -1},
	{20, 0, 30, 2, 42, 1, 10, 10, -1},
	{30, 0, 20, 3, 42, 4, 10, 10, -1},
	{22, 0, 12, 2, 40, 3, 10, 10, -1},//30
	{14, 0, 36, 1, 46, 2, 10, 10, -1},
	{38, 0, 28, 4, 44, 1, 10, 10, -1},
	{0, 1, 8, 1, 34, 4, 3, 11, 2, -1},//tirando do topo
	{8, 1, 0, 6, 34, 6, 3, 11, 2, -1},
	{34, 1, 0, 6, 34, 6, 8, 10, 9, -1},
	{6, 1, 16, 2, 10, 1, 5, 11, 4, -1},
	{16, 1, 6, 6, 10, 6, 5, 11, 4, -1},
	{10, 1, 6, 6, 16, 6, 2, 10, 3, -1},
	{4, 1, 24, 3, 18, 2, 7, 11, 6, -1},
	{24, 1, 4, 6, 18, 6, 7, 11, 6, -1},//40
	{18, 1, 4, 6, 24, 6, 4, 10, 5, -1},
	{2, 1, 32, 4, 26, 3, 9, 11, 8, -1},
	{32, 1, 2, 6, 26, 6, 9, 11, 8, -1},
	{26, 1, 2, 6, 32, 6, 6, 10, 7, -1},
	{40, 1, 12, 6, 22, 6, 5, 10, 4, -1},//flip
	{42, 1, 20, 6, 30, 6, 7, 10, 6, -1},
	{44, 1, 28, 6, 38, 6, 9, 10, 8, -1},
	{46, 1, 36, 6, 14, 6, 3, 10, 2, -1}//48
};
const uint8_t _SLS[36][13] PROGMEM= {
	{0, 45, 2, 37, 1, 5, 10, 4, 10, 2, 11, 3, -1},
	{0, 47, 3, 13, 2, 7, 10, 6, 10, 4, 11, 5, -1},
	{0, 41, 4, 21, 3, 9, 10, 8, 10, 6, 11, 7, -1},
	{0, 43, 1, 29, 4, 3, 10, 2, 10, 8, 11, 9, -1},
	{0, 43, 1, 29, 2, 2, 11, 3, 11, 5, 10, 4, -1},
	{0, 45, 2, 37, 3, 4, 11, 5, 11, 7, 10, 6, -1},
	{0, 47, 3, 13, 4, 6, 11, 7, 11, 9, 10, 8, -1},
	{0, 41, 4, 21, 1, 8, 11, 9, 11, 3, 10, 2, -1},//jogadas finais
	{0, 43, 2, 29, 1, 10, -1},//Gira Topo
	{0, 47, 2, 13, 1, 11, -1},//10
	{0, 45, 3, 37, 2, 10, -1},
	{0, 41, 3, 21, 2, 11, -1},
	{0, 47, 4, 13, 3, 10, -1},
	{0, 43, 4, 29, 3, 11, -1},
	{0, 41, 1, 21, 4, 10, -1},
	{0, 45, 1, 37, 4, 11, -1},
	{0, 41, 1, 21, 2, 10, -1},
	{0, 45, 1, 37, 2, 11, -1},
	{0, 43, 2, 29, 3, 10, -1},
	{0, 47, 2, 13, 3, 11, -1},//20
	{0, 45, 3, 37, 4, 10, -1},
	{0, 41, 3, 21, 4, 11, -1},
	{0, 47, 4, 13, 1, 10, -1},
	{0, 43, 4, 29, 1, 11, -1},
	{0, 45, 4, 37, 1, 10, 10, -1},
	{0, 43, 3, 29, 4, 10, 10, -1},
	{0, 41, 2, 21, 3, 10, 10, -1},
	{0, 47, 1, 13, 2, 10, 10, -1},
	{0, 47, 1, 13, 4, 10, 10, -1},
	{0, 45, 4, 37, 3, 10, 10, -1},//30
	{0, 43, 3, 29, 2, 10, 10, -1},
	{0, 41, 2, 21, 1, 10, 10, -1},
	{1, 11, 1, 23, 2, 5, 10, 4, 10, 2, 11, 3, -1},//tirar peças erradas
	{1, 19, 2, 31, 3, 7, 10, 6, 10, 4, 11, 5, -1},
	{1, 27, 3, 39, 4, 9, 10, 8, 10, 6, 11, 7, -1},
	{1, 35, 4, 15, 1, 3, 10, 2, 10, 8, 11, 9, -1}//36
};
const uint8_t _OLL[58][30] PROGMEM= {
	{46, 47, 40, 45, 41, 44, 43, 42,   -1},//Finalizado
	{14, 47, 22, 45, 41, 38, 43, 42,   5, 10, 10, 4, 10, 5, 10, 4, -1},//Crosses
	{36, 47, 12, 45, 41, 28, 43, 42,   9, 10, 4, 11, 8, 10, 5, -1},
	{14, 47, 22, 45, 41, 28, 43, 20,   8, 11, 5, 10, 9, 10, 4, 10, 5, 10, 4, -1},
	{36, 47, 22, 45, 41, 38, 43, 20,   4, 10, 5, 10, 4, 11, 5, 10, 4, 10, 10,  5, -1},
	{46, 47, 12, 45, 41, 44, 43, 30,   5, 7, 8, 6, 4, 7, 9, 6, -1},
	{46, 47, 12, 45, 41, 38, 43, 42,   5, 7, 9, 6, 4, 7, 8, 6, -1},
	{46, 47, 40, 45, 41, 28, 43, 30,   4, 4, 0, 5, 10, 10, 4, 1, 5, 10, 10, 5, -1},
	{36, 13, 22, 37, 21, 38, 29, 20,   4, 10, 3, 4, 2, 5, 5, 11, 5, 6, 4, 7, -1},//Dots
	{36, 13, 22, 37, 21, 28, 29, 30,   5, 6, 4, 7, 10, 10, 5, 6, 4, 6, 6, 10, 10, 6, -1},
	{14, 13, 22, 37, 21, 38, 29, 42,   7, 2, 2, 8, 3, 8, 6, 11, 11, 7, 8, 3, 6, -1},//10
	{36, 13, 40, 37, 21, 28, 29, 20,   5, 10, 10, 5, 6, 4, 7, 11, 7, 11, 6, 11, 4, -1},
	{46, 13, 40, 37, 21, 38, 29, 20,   5, 10, 10, 6, 4, 10, 5, 11, 6, 6, 10, 10, 6, 4, -1},
	{14, 13, 12, 37, 21, 44, 29, 42,   6, 4, 10, 5, 10, 7, 10, 10, 7, 8, 6, 9, -1},
	{46, 13, 12, 37, 21, 38, 29, 42,   4, 10, 5, 10, 5, 6, 4, 7, 10, 10, 5, 6, 4, 7, -1},
	{46, 13, 40, 37, 21, 44, 29, 42,   5, 8, 6, 6, 4, 9, 10, 10, 5, 8, 6, 4, 9, 10, 10, 5, 8, 6, 6, 4, 9, -1},
	{46, 13, 40, 45, 41, 44, 29, 42,   9, 4, 10, 5, 11, 8, 5, 6, 4, 7, -1},  //All corners
	{46, 13, 40, 45, 21, 44, 43, 42,   5, 8, 7, 4, 9, 11, 11, 5, 8, 7, 4, 9, -1},
	{36, 47, 22, 37, 21, 38, 43, 20,   4, 11, 2, 2, 0, 3, 10, 10, 2, 1, 2, 2, 10, 5, -1},//Lines
	{14, 47, 22, 37, 21, 28, 43, 20,   5, 11, 7, 10, 7, 8, 6, 9, 6, 4, -1},
	{14, 13, 22, 45, 41, 28, 29, 20,   6, 10, 4, 11, 5, 10, 4, 11, 5, 7, -1},//20
	{36, 13, 22, 45, 41, 38, 29, 20,   9, 3, 8, 11, 5, 10, 4, 11, 5, 10, 4, 9, 2, 8, -1},
	{36, 13, 12, 45, 41, 28, 29, 42,   5, 6, 4, 10, 5, 7, 4, 6, 11, 7, -1},//Big Ls
	{14, 13, 22, 45, 41, 44, 29, 30,   8, 7, 9, 11, 8, 6, 9, 7, 10, 6, -1},
	{36, 13, 12, 45, 41, 44, 29, 20,   4, 2, 5, 8, 10, 9, 11, 4, 3, 5, -1},
	{14, 13, 22, 45, 41, 38, 29, 42,   9, 3, 8, 5, 11, 4, 10, 9, 2, 8, -1},
	{36, 13, 40, 45, 41, 38, 29, 42,   6, 4, 10, 5, 11, 7, -1},//Ts
	{14, 13, 40, 45, 41, 28, 29, 42,   4, 10, 5, 11, 5, 6, 4, 7, -1},
	{46, 13, 12, 45, 41, 38, 29, 42,   5, 6, 4, 10, 5, 11, 7, 10, 4, -1},//Zs
	{14, 13, 40, 45, 41, 44, 29, 20,   8, 7, 9, 11, 8, 10, 6, 11, 9, -1},
	{46, 47, 22, 37, 21, 44, 43, 20,   4, 10, 4, 3, 5, 2, 11, 5, -1},//Cs//30
	{36, 13, 22, 45, 41, 44, 29, 42,   4, 10, 5, 11, 3, 5, 6, 4, 7, 2, -1},
	{36, 47, 12, 45, 21, 38, 29, 30,   6, 4, 10, 5, 11, 4, 10, 5, 11, 7, -1},//Little Ls
	{14, 47, 22, 37, 41, 28, 29, 20,   7, 9, 11, 8, 10, 9, 11, 8, 10, 6, -1},
	{36, 13, 12, 37, 41, 38, 43, 30,   8, 11, 7, 11, 11, 7, 10, 6, 11, 6, 10, 10, 6, 11, 9, -1},
	{36, 47, 12, 37, 41, 38, 29, 30,   5, 6, 5, 7, 4, 4, 10, 10, 3, 4, 2, 5, -1},
	{14, 47, 12, 37, 41, 28, 29, 30,   5, 6, 4, 7, 10, 10, 4, 4, 3, 5, 2, 5, -1},
	{14, 47, 12, 45, 21, 28, 29, 30,   8, 7, 9, 6, 10, 10, 8, 8, 2, 8, 3, 8, -1},
	{14, 47, 22, 45, 21, 44, 29, 30,   8, 6, 5, 6, 4, 6, 6, 9, -1},
	{46, 13, 12, 45, 21, 28, 43, 20,   9, 3, 8, 11, 5, 10, 4, 9, 2, 8, -1},
	{36, 13, 12, 45, 21, 28, 43, 42,   10, 10, 8, 5, 5, 7, 4, 7, 5, 6, 6, 4, 7, 4, 9, -1},//40
	{14, 13, 22, 37, 41, 44, 43, 30,   10, 10, 5, 8, 8, 6, 9, 6, 8, 6, 6, 9, 6, 4, 9, -1},
	{46, 13, 40, 45, 21, 38, 43, 20,   3, 4, 3, 5, 5, 10, 4, 10, 5, 11, 4, 2, 2, -1},
	{36, 47, 12, 45, 21, 28, 29, 42,   5, 11, 4, 6, 5, 7, 10, 6, 4, 7, -1},
	{14, 13, 40, 45, 21, 38, 43, 30,   4, 10, 5, 3, 4, 2, 11, 3, 5, 2, -1},
	{46, 13, 40, 37, 41, 38, 43, 20,   2, 9, 2, 8, 8, 11, 9, 11, 8, 10, 9, 3, 3, -1},//5, 5, 10, 5, 2, 4, 11, 5, 5, 10, 4, 2, 5, -1},
	{14, 47, 12, 45, 21, 44, 29, 42,   11, 4, 11, 11, 5, 11, 4, 11, 4, 4, 7, 11, 6, 10, 4, -1},
	{14, 47, 12, 37, 41, 44, 29, 42,   11, 5, 10, 10, 4, 10, 5, 10, 4, 4, 2, 10, 3, 11, 5, -1},
	{14, 47, 40, 37, 41, 44, 29, 20,   5, 10, 10, 4, 4, 3, 5, 2, 5, 10, 10, 4, -1},
	{46, 47, 22, 45, 21, 29, 29, 42,   6, 5, 7, 4, 10, 4, 11, 5, -1},
	{14, 13, 22, 37, 41, 38, 43, 42,   9, 2, 2, 4, 2, 5, 2, 8, -1},//50
	{36, 47, 40, 37, 41, 28, 29, 20,   8, 6, 6, 5, 7, 4, 7, 9, -1},
	{46, 47, 12, 45, 21, 44, 29, 30,   8, 10, 7, 11, 9, 10, 8, 6, 9, -1},//Ps
	{14, 47, 40, 37, 41, 28, 29, 42,   5, 11, 6, 10, 4, 11, 5, 7, 4, -1},
	{46, 47, 22, 45, 21, 44, 29, 20,   6, 10, 4, 11, 5, 7, -1},
	{36, 47, 40, 37, 41, 38, 29, 42,   7, 11, 9, 10, 8, 6, -1},
	{36, 13, 40, 37, 41, 44, 43, 30,   8, 10, 9, 10, 8, 11, 9, 11, 9, 2, 8, 3, -1},//Ws
	{46, 13, 22, 45, 21, 28, 43, 42,   5, 11, 4, 11, 5, 10, 4, 10, 4, 3, 5, 2, -1}
};
const uint8_t _PLL[22][33] PROGMEM= {//21+12
	{14, 13, 12, 22, 21, 20, 28, 29, 30, 36, 37, 38,   -1},//Resolvido
	{22, 13, 20, 30, 21, 36, 14, 29, 28, 38, 37, 12,   4, 4, 2, 2, 4, 6, 5, 2, 2, 4, 7, 4, -1},
	{30, 13, 36, 14, 21, 12, 22, 29, 28, 38, 37, 20,   2, 2, 4, 4, 3, 9, 2, 4, 4, 3, 8, 3, -1},
	{14, 29, 12, 22, 37, 20, 30, 13, 28, 38, 21, 36,   4, 9, 4, 9, 0, 4, 9, 4, 9, 10, 10, 4, 9, 4, 9, 0, 4, 9, 4, 9, -1},
	{14, 37, 12, 22, 29, 20, 30, 21, 28, 38, 13, 36,   5,11, 4, 4,10, 4,10, 5,11, 4,10, 4,11, 4,11, 5,10,10, -1},
	{14, 37, 12, 22, 13, 20, 30, 29, 28, 38, 21, 36,   5, 10, 5, 11, 5, 11, 5, 10, 4, 10, 4, 4, -1},
	{14, 21, 12, 22, 37, 20, 30, 29, 28, 38, 13, 36,   4, 4, 11, 5, 11, 4, 10, 4, 10, 4, 11, 4, -1},
	{22, 13, 36, 14, 21, 28, 38, 29, 20, 30, 37, 12,   5, 7, 9, 6, 4, 7, 8, 6, 5, 7, 8, 6, 4, 7, 9, 6, -1},
	{14, 29, 20, 30, 21, 12, 22, 13, 28, 38, 37, 36,   11, 5, 10, 4, 11, 4, 4, 7, 11, 6, 10, 4, 6, 5, 7, 4, 4, -1},
	{14, 13, 20, 30, 37, 12, 22, 29, 28, 38, 21, 36,   4, 10, 5, 11, 5, 6, 4, 4, 11, 5, 11, 4, 10, 5, 7, -1},
	{14, 13, 20, 30, 29, 12, 22, 21, 28, 38, 37, 36,   4, 10, 5, 7, 4, 10, 5, 11, 5, 6, 4, 4, 11, 5, 11, -1},//10
	{38, 13, 12, 22, 21, 20, 30, 37, 36, 14, 29, 28,   9, 11, 8, 6, 9, 11, 8, 10, 8, 7, 8, 8, 10, 8, 10, -1},
	{22, 13, 36, 14, 29, 20, 30, 21, 28, 38, 37, 12,   5, 10, 10, 4, 10, 10, 5, 6, 4, 10, 5, 11, 5, 7, 4, 4, 11, -1},
	{22, 13, 36, 14, 21, 20, 30, 37, 28, 38, 29, 12,   8, 10, 10, 9, 10, 10, 8, 7, 9, 11, 8, 10, 8, 6, 8, 8, 10, -1},
	{30, 21, 12, 22, 13, 36, 14, 29, 28, 38, 37, 20,   5, 10, 5, 11, 3, 0, 3, 1, 2, 2, 5, 3, 4, 2, 4, -1},
	{30, 37, 12, 22, 21, 36, 14, 29, 28, 38, 13, 20,   6, 4, 11, 5, 11, 4, 10, 5, 7, 4, 10, 5, 11, 5, 6, 4, 7, -1},
	{30, 13, 12, 22, 37, 36, 14, 29, 28, 38, 21, 20,   5, 10, 4, 11, 5, 7, 11, 6, 4, 10, 5, 6, 5, 7, 4, 11, 4, -1},
	{14, 13, 28, 38, 37, 20, 30, 29, 12, 22, 21, 36,   4, 11, 5, 10, 4, 2, 10, 3, 5, 11, 4, 3, 4, 2, 5, 10, 5, -1},
	{38, 29, 12, 22, 21, 36, 14, 37, 20, 30, 13, 28,   3, 3, 0, 9, 10, 9, 11, 8, 1, 2, 2, 5, 10, 4, -1},//X
	{30, 37, 12, 22, 21, 28, 38, 13, 36, 14, 29, 20,   5, 11, 4, 2, 2, 0, 9, 10, 8, 11, 8, 1, 2, 2, -1},//X
	{14, 29, 20, 30, 13, 28, 38, 21, 12, 22, 37, 36,   3, 3, 1, 4, 11, 4, 10, 5, 0, 2, 2, 8, 11, 9, -1},//20//X
	{14, 21, 28, 38, 29, 12, 22, 13, 20, 30, 37, 36,   8, 10, 9, 2, 2, 1, 4, 11, 5, 10, 5, 0, 2, 2, -1}//X
};
char solve_enhanced(uint8_t *v, int8_t *s){
	unsigned int max = MAX_JOGADAS;
	//Tamanho da função: 448 + 480 + 468 + 1740 + 726 = 3862
	uint8_t a, b, cw;
	//Condições: 1:2 e 3:4 então adicionar à S 5...[-1]
	uint8_t k[48];
	memcpy(k, v, 48);
	//------CRUZ--------------
#ifdef VERBOSE
	putStr(" CROSS ");
	printInt(max);
#endif
	a = 0;
	while(a<56){
		int8_t cruz[8];
		memcpy_P(cruz, _CRUZ[a], 8); 
		if( (!cruz[1] && k[cruz[0]]==0 && k[cruz[2]]==cruz[3])||
		( cruz[1] && k[cruz[0]]==0 && k[cruz[2]]!=cruz[3]) ){
			for(b=4;cruz[b]>=0;b++){
				*(s++)=cruz[b];
				max--;if(!max)return 0;
				rot(k,cruz[b]);
			}
			a = -1;
		}
		a++;
	}
	//-------First layer----------
#ifdef VERBOSE
	putStr(" FL ");
	printInt(max);
#endif
	a = 0;
	while(a<48){
		int8_t flc[10];
		memcpy_P(flc, _FLC[a], 10);
		if( (!flc[1] && k[flc[0]]==0 && k[flc[2]]==flc[3] && k[flc[4]]==flc[5])||
		( flc[1] && k[flc[0]]==0 && k[flc[2]]!=flc[3] && k[flc[4]]!=flc[5]) ){
			for(b=6;flc[b]>=0;b++){
				*(s++)=flc[b];
				max--;if(!max)return 0;
				rot(k,flc[b]);
			}
			a = -1;
		}
		a++;
	}
	//---------Second layer-------
#ifdef VERBOSE
	putStr(" SL ");
	printInt(max);
#endif
	a = 0;
	while(a<36){
		int8_t sls[13];
		memcpy_P(sls, _SLS[a], 13);
		if( (!sls[0] &&  k[sls[1]]==sls[2] && k[sls[3]]==sls[4])||
		( sls[0] && (k[sls[1]]!=sls[2] || k[sls[3]]!=sls[4])) ){
			for(b=5;sls[b]>=0;b++){
				*(s++)=sls[b];
				max--;if(!max)return 0;
				rot(k,sls[b]);
			}
			a = -1;
		}
		a++;
	}
	//--------OLL------------
#ifdef VERBOSE
	putStr(" OLL ");
	printInt(max);
#endif
	b = 1;
	while(b){
		for(a=0;a<58 && b;a++){
			int8_t oll[30];
			memcpy_P(oll, _OLL[a], 30);
			if(k[oll[0]]==5 && k[oll[1]]==5 && k[oll[2]]==5 && k[oll[3]]==5 &&
			k[oll[4]]==5 && k[oll[5]]==5 && k[oll[6]]==5 && k[oll[7]]==5){
				cw = 8;
				while(oll[cw]>0){
					*(s++) = oll[cw];
					max--;if(!max)return 0;
					rot(k, oll[cw]);
					cw++;
				}
				b = 0;
			}
		}
		if(b>0){
			*(s++) = 10;
			max--;if(!max)return 0;
			rot(k, 10);
		}
	}
	//----------PLL----------
#ifdef VERBOSE
	putStr(" PLL ");
	printInt(max);
#endif
	b = 1;
	while(b){
		for(a=0;a<22 && b;a++){
			int8_t pll[33];
			memcpy_P(pll, _PLL[a], 33);
			if(k[pll[ 0]]==k[pll[ 1]] && k[pll[ 0]]==k[pll[ 2]] &&
			k[pll[ 3]]==k[pll[ 4]] && k[pll[ 3]]==k[pll[ 5]] &&
			k[pll[ 6]]==k[pll[ 7]] && k[pll[ 6]]==k[pll[ 8]] &&
			k[pll[ 9]]==k[pll[10]] && k[pll[ 9]]==k[pll[11]] ){
				cw = 12;
				while(pll[cw]>=0){
					*(s++) = pll[cw];
					max--;if(!max)return 0;
					rot(k, pll[cw]);
					cw++;
				}
				b = 0;
			}
		}
		if(b>0){
			*(s++) = 10;
			max--;if(!max)return 0;
			rot(k, 10);
		}
	}
#ifdef VERBOSE
	putStr(" ROT ");
	printInt(max);
#endif
	while(k[13]!=1){
		*(s++) = 10;
		max--;if(!max)return 0;
		rot(k, 10);
	}
#ifdef VERBOSE
	putStr(" done!\n");
#endif
	*(s++) = -1;
	return 1;
}
void simplify(int8_t* l);

char multipleTry(uint8_t *v, int8_t *s){
   int8_t solucoes[24][MAX_JOGADAS], jogadas[24], menor, menorIndex, a;
   for(int j=0;j<24;j++)for(int i=0;i<MAX_JOGADAS;i++)solucoes[j][i]=-1;
   a=0;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=1;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=2;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=3;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   flop(v,2);
   a=4;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=5;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=6;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=7;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   flop(v,2);
   a=8;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=9;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=10;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=11;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   flop(v,5);
   a=12;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=13;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=14;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=15;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   flop(v,2);
   a=16;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=17;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=18;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=19;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   flop(v,2);
   a=20;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=21;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=22;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   a=23;
   if(solve_enhanced(v,solucoes[a])){
	   simplify(solucoes[a]);
	   for(jogadas[a]=0;solucoes[a][jogadas[a]]>=0;jogadas[a]++);
   }else jogadas[a] = MAX_JOGADAS;
   flop(v,0);
   
   menor = jogadas[0];
   menorIndex = 0;
   for(int i=1;i<24;i++)if(menor>jogadas[i]){menorIndex = i; menor = jogadas[i];}
	if(menor==MAX_JOGADAS)return 0;
   for(int i=0;solucoes[menorIndex][i]>=0;i++)s[i]=solucoes[menorIndex][i]>=0;
   return menorIndex+1;
}

void simplify(int8_t *l){
	putStr("simplify...");
   const int8_t P[36][14] = {
       {1, 0, -1,   -1},
       {0, 1, -1,   -1},
       {1, 1, -1,   0, 0, -1},
       {3, 2, -1,   -1},
       {2, 3, -1,   -1},
       {3, 3, -1,   2, 2, -1},
       {5, 4, -1,   -1},
       {4, 5, -1,   -1},
       {5, 5, -1,   4, 4, -1},
       {2, 6, -1,   6, 2, -1},
       {3, 6, -1,   6, 3, -1},
       {7, 6, -1,   -1},
       {2, 7, -1,   7, 2, -1},
       {3, 7, -1,   7, 3, -1},
       {6, 7, -1,   -1},
       {7, 7, -1,   6, 6, -1},
       {4, 8, -1,   8, 4, -1},
       {5, 8, -1,   8, 5, -1},
       {9, 8, -1,   -1},
       {4, 9, -1,   9, 4, -1},
       {5, 9, -1,   9, 5, -1},
       {8, 9, -1,   -1},
       {9, 9, -1,   8, 8, -1},
       {0, 10, -1,   10, 0, -1},
       {1, 10, -1,   10, 1, -1},
       {11, 10, -1,   -1},
       {0, 11, -1,   11, 0, -1},
       {1, 11, -1,   11, 1, -1},
       {10, 11, -1,   -1},
       {11, 11, -1,   10, 10, -1},
       {0, 0, 0, -1,   1, -1},
       {2, 2, 2, -1,   3, -1},
       {4, 4, 4, -1,   5, -1},
       {6, 6, 6, -1,   7, -1},
       {8, 8, 8, -1,   9, -1},
       {10, 10, 10, -1,   11, -1}};//const uint8_t P[780][14] = {
   int a, b, c, d, e, T;
   int i, j, k;
   for(T=0;l[T]>=0;T++);//T - Tamanho do vetor L
   for(a=0;a<T;a++){
      d = 0;
      for(b=0;b<36 && !d;b++){
         e = 0;
         for(c=0;P[b][c]>=0 && !e;c++)if(P[b][c]!=l[a+c])e = 1;
         if(!e){
            d = 1;//achou elemento, tem que resetar lista
            //Substituir sequencia
            for(i=0;P[b][i]>=0;i++);//tamanho a ser substituido
            for(j=0;P[b][i+j+1]>=0;j++);//tamanho da nova sequencia
            for(k=0;k<j;k++)l[a+k]=P[b][i+1+k];//copia sequencia
            for(k=0;k<T-a-j;k++)l[a+j+k] = l[a+i+k];//move resto
            T = T+j-i;
         }
      }
      if(d)a=a-1;
      //if(a<0)a=-1;
   }
   putStr("done!\n");
}

#endif /* CUBOAVANCADO_H_ */