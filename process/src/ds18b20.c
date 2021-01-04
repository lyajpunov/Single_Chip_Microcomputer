#include "init.h"

void delay_ds (unsigned int t)
{
	while(t--);
}

//DS18B20 ��ʼ������
bit init_ds18b20(void)
{
	bit initflag = 0;
	DQ = 1;
	delay_ds(12);
	DQ = 0;
	delay_ds(85); // ��ʱ����480us
	DQ = 1;
	delay_ds(10); // 14
	initflag = DQ; // initflag ����1 ��ʼ��ʧ��
	delay_ds(5);
	return initflag;
}

//ͨ��������������дһ���ֽ�
void wr_ds18b20(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = byt&0x01;
		delay_ds(5);
		DQ = 1;
		byt >>= 1;
	}
	delay_ds(5);
}



//ͨ�������ߴ�������һ���ֽ�
unsigned char rd_ds18b20(void)
{
	unsigned char i;
	unsigned char byt;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		byt >>= 1;
		DQ = 1;
		if(DQ)
		{
			byt |= 0x80;
		}
		delay_ds(5);
	}
	return byt;
}



//�¶�ת������ȡ�����ݴ���������
int rd_temperature(void)
{
	unsigned int tmpvalue;
	unsigned char low,high;
	int value; // ����¶���ֵ
	float t;
	init_ds18b20();
	wr_ds18b20(0xCC);
	wr_ds18b20(0x44); // �����¶�ת��
	delay_ds(200);
	init_ds18b20();
	wr_ds18b20(0xCC);
	wr_ds18b20(0xBE); // ��ȡ�Ĵ���
	low = rd_ds18b20(); // ���ֽ�
	high = rd_ds18b20(); // ���ֽ�
	tmpvalue = high;
	tmpvalue <<= 8;
	tmpvalue |= low;
	value = tmpvalue;
	//ʹ��DS18B20 ��Ĭ�Ϸֱ���12 λ, ��ȷ��Ϊ0.0625 ��, ���������ݵ����λ����0.0625��
	t = value * 0.0625;
	//�����Ŵ�100 ��, ʹ��ʾʱ����ʾС�������λ, ����С������������4 ��5 ��
	//��t=11.0625, ���м�����, �õ�value = 1106, ��11.06 ��
	//��t=-11.0625, ���м�����, �õ�value = -1106, ��-11.06 ��
	// value = t * 100 + (value > 0 ? 0.5 : -0.5); // ����0 ��0.5, С��0 ��0.5
	value = t * 100/1.25+ (value > 0 ? 0.5 : -0.5);
	return value;
}