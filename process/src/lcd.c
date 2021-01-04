#include "init.h"

#define LCD P2

sbit LC1=P1^0;
//1号数码管的控制端
sbit LC2=P1^1;
//2号数码管的控制端
sbit LC3=P1^2;
//3号数码管的控制端
sbit LC4=P1^3;
//4号数码管的控制端
unsigned char code smg[]= {
	0x3f,0x06,0x5b,0x4f
	,0x66,0x6d,0x7d,0x07,0x7f,
	0x6f,0x77,0x7c,0x39,0x5e,
	0x79,0x71,0x00
}
;
//0 1 2 3 4 5 6 7 8 9 C d E F
unsigned int ii;
LC_init(void) {
	LC1 = 1;
	LC2 = 1;
	LC3 = 1;
	LC4 = 1;
	//LC高电平时可变，低电平时锁存
	P2 = 0x00;
	LC1 = 0;
	LC2 = 0;
	LC3 = 0;
	LC4 = 0;
	return 0;
}
int show_number(int number,int S) {
	if(S==1) {
		LC1 = 1;
		P2 = smg[number];
		LC1 = 0;
	}
	if(S==2) {
		LC2 = 1;
		P2 = smg[number];
		LC2 = 0;
	}
	if(S==3) {
		LC3 = 1;
		P2 = smg[number];
		LC3 = 0;
	}
	if(S==4) {
		LC4 = 1;
		P2 = smg[number];
		LC4 = 0;
	}
	P2 = 0x00;
	return 0;
}
int show_off(void) {
	show_number(0,1);
	show_number(15,2);
	show_number(15,3);
	return 0;
}
int show_time(int Number) {
	show_number(Number    %10,4);
	show_number(Number/10 %10,3);
	show_number(Number/100%10,2);
	return 0;
}