#include "init.h"

sbit CS_DAC=P1^5;//DAC0832��Ƭѡ�˿�
sbit WR_DAC=P1^6;//DAC0832������д��˿�
extern void init(void)
{
    P0=0xff;
    P1=0xff;
    P2=0xff;
    P3=0xff;
    CS_DAC=0;//һֱƬѡ��DAC0832,�͵�ƽ��Ч��~
    WR_DAC=0;//һֱд�����ݵ�DAC0832
		Moto_init();
		LC_init();
}



