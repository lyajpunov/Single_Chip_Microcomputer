#include "init.h"

extern unsigned int model =1 ;
//ģʽ
extern unsigned int Gear  =0 ;
//��λ
extern unsigned int time  =0 ;
//��ʱʱ�䣨���ӣ�
extern unsigned int Temp_T = 1;
//�¶�
extern unsigned int model_flag[] = {0,0,0,0};
//ģʽ��ʾ��־λ


//��ʱ��һЩ����
unsigned int temp_a = 0;
unsigned int temp_a_last = 0;
unsigned int temp_b = 0;
unsigned int temp_b_last = 0;
unsigned int temp_time_a = 0;
unsigned int temp_time_a_last = 0;
unsigned int temp_time_b = 0;
unsigned int temp_time_b_last = 0;
unsigned int temp_time_c = 0;
unsigned int temp_time_c_last = 0;
unsigned int timer0_min_flag  = 0;
unsigned int timer0_min_count = 0;
unsigned int time_last = 0;


int model_select(unsigned int Model) {
	//ģʽһ ����ģʽ
	if(Model == 1) {
		if(model_flag[0] == 0) {
			show_off();
			show_number(16,4);
			model_flag[0]++;
		}
		Moto_start(0);
	}
	//ģʽ�� ����ģʽ 
	if(Model == 2) {
		//��ȡ�¶�
		Temp_T = rd_temperature()/10;
		//������¶�
		//��ʾ����
		if (model_flag[1] == 0) {
			show_number(10,1);
			show_number(16,2);
			show_number(16,3);
			show_number(16,4);
			model_flag[1] ++ ;
		}
		temp_a = Temp_T%10;
		if (temp_a != temp_a_last) {
			show_number(temp_a,4);
		}
		temp_a_last = temp_a;
		temp_b = Temp_T / 10 % 10;
		if (temp_b != temp_b_last) {
			show_number(temp_b,3);
		}
		temp_b_last = temp_b;
		//�����ѹ����
		Temp_T = temp_b*10+temp_a;
		if(Temp_T <= 21) {
			Gear = 0;
		}
		if(Temp_T <= 22 && Temp_T > 21) {
			Gear = 1;
		}
		if(Temp_T <= 23 && Temp_T > 22) {
			Gear = 2;
		}
		if(Temp_T <= 24 && Temp_T > 23) {
			Gear = 3;
		}
		if(Temp_T <= 25 && Temp_T > 24) {
			Gear = 4;
		}
		if(Temp_T <= 26 && Temp_T > 25) {
			Gear = 5;
		}
		if(Temp_T <= 27 && Temp_T > 26) {
			Gear = 6;
		}
		if(Temp_T <= 28 && Temp_T > 27) {
			Gear = 7;
		}
		if(Temp_T <= 29 && Temp_T > 28) {
			Gear = 8;
		}
		if(Temp_T <= 30 && Temp_T > 29) {
			Gear = 9;
		} 
		if(Temp_T > 30){
			Gear = 10;
		}
		Moto_start(Gear);
	}
	//ģʽ�� ��λģʽ
	if(Model == 3) {
		//��ʾ����
		if (model_flag[2] == 0) {
			show_number(11,1);
			show_number(16,2);
			show_number(16,3);
			show_number(16,4);
			model_flag[2] ++ ;
		}
		show_number(Gear,4);
		Moto_start(Gear);
	}
	if(Model == 4) {
		//��ʾ����
		if (model_flag[3] == 0) {
			show_number(12,1);
			show_number(16,2);
			show_number(16,3);
			show_number(16,4);
			model_flag[3] ++ ;
		}
		if(time_last != time) {
				show_time(time);
				time_last = time;
		}
	}
	delay(100);
	//100ms��Ѳһ��
	timer0_min_flag++;
	if(timer0_min_flag == 500) {
		timer0_min_flag = 0;
		time --;
		if(time == 0) {
			show_number(16,4);
			model = 1;
		}
	}
	return 0;
}