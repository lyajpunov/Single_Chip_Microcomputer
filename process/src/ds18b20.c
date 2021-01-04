#include "init.h"

void delay_ds (unsigned int t)
{
	while(t--);
}

//DS18B20 初始化函数
bit init_ds18b20(void)
{
	bit initflag = 0;
	DQ = 1;
	delay_ds(12);
	DQ = 0;
	delay_ds(85); // 延时大于480us
	DQ = 1;
	delay_ds(10); // 14
	initflag = DQ; // initflag 等于1 初始化失败
	delay_ds(5);
	return initflag;
}

//通过单总线向器件写一个字节
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



//通过单总线从器件读一个字节
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



//温度转换、读取及数据处理器函数
int rd_temperature(void)
{
	unsigned int tmpvalue;
	unsigned char low,high;
	int value; // 存放温度数值
	float t;
	init_ds18b20();
	wr_ds18b20(0xCC);
	wr_ds18b20(0x44); // 启动温度转换
	delay_ds(200);
	init_ds18b20();
	wr_ds18b20(0xCC);
	wr_ds18b20(0xBE); // 读取寄存器
	low = rd_ds18b20(); // 低字节
	high = rd_ds18b20(); // 高字节
	tmpvalue = high;
	tmpvalue <<= 8;
	tmpvalue |= low;
	value = tmpvalue;
	//使用DS18B20 的默认分辨率12 位, 精确度为0.0625 度, 即读回数据的最低位代表0.0625度
	t = value * 0.0625;
	//将它放大100 倍, 使显示时可显示小数点后两位, 并对小数点后第三进行4 舍5 入
	//如t=11.0625, 进行计数后, 得到value = 1106, 即11.06 度
	//如t=-11.0625, 进行计数后, 得到value = -1106, 即-11.06 度
	// value = t * 100 + (value > 0 ? 0.5 : -0.5); // 大于0 加0.5, 小于0 减0.5
	value = t * 100/1.25+ (value > 0 ? 0.5 : -0.5);
	return value;
}