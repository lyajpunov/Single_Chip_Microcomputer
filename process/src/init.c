#include "init.h"

sbit CS_DAC=P1^5;//DAC0832的片选端口
sbit WR_DAC=P1^6;//DAC0832的数据写入端口
extern void init(void)
{
    P0=0xff;
    P1=0xff;
    P2=0xff;
    P3=0xff;
    CS_DAC=0;//一直片选中DAC0832,低电平有效啊~
    WR_DAC=0;//一直写入数据到DAC0832
		Moto_init();
		LC_init();
}



