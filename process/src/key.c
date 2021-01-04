#include "init.h"

extern unsigned int model ;
//ģʽ
extern unsigned int time  ;
//��ʱʱ�䣨���ӣ�
extern unsigned int Gear  ;
//��λ
extern unsigned int model_flag[];
sbit Model_select = P3^0;
sbit key_up       = P3^1;
sbit key_down     = P3^2;
sbit enter        = P3^3;
unsigned int model_list_flag = 1;
unsigned int model_list_flag_last = 1;
unsigned int gear_list_flag = 1;
unsigned int gear_list_flag_last = 1;
unsigned int time_list_flag = 1;
unsigned int time_list_flag_last = 1;
//ѡ���־λ�������־λ��λ1ʱ����ѡ��ģʽ
unsigned int Model_select_flag = 1;
unsigned int enter_1 = 0;
unsigned int enter_2 = 0;
unsigned int enter_3 = 0;
void key_scan(void) {
	if (Model_select == 0) {
		//��������
		delay(10);
		if (Model_select == 0) {
			Model_select_flag = 1;
			show_number(14,1);
			show_number(16,2);
			show_number(16,3);
			show_number(model_list_flag,4);
			while(Model_select_flag) {
				if(!key_up) {
					delay(10);
					if(!key_up && (model_list_flag < 4)) {
						model_list_flag ++;
						while(key_up == 0);
					}
					if(!key_up && (model_list_flag >= 4)) {
						model_list_flag = 4;
						while(key_up == 0);
					}
				}
				if(!key_down) {
					delay(10);
					if(!key_down && (model_list_flag > 1)) {
						model_list_flag --;
						while(key_down == 0);
					}
					if(!key_down && (model_list_flag <= 1)) {
						model_list_flag = 1;
						while(key_down == 0);
					}
				}
				if(model_list_flag_last != model_list_flag) {
					show_number(model_list_flag,4);
					model_list_flag_last = model_list_flag;
				}
				if (!enter) {
					delay(10);
					if(!enter) {
						enter_1 = 1;
						while(enter == 0);
					}
				}
				while(enter_1) {
					//ѡ��һ��ģʽ���߶���ģʽ
					if(model_list_flag == 1 || model_list_flag == 2 ) {
						model = model_list_flag;
						Model_select_flag = 0;
						enter_1 = 0;
						Model_select_flag = 0;
						show_number(model_list_flag,2);
						model_flag[0] = 0;
						model_flag[1] = 0;
						model_flag[2] = 0;
						model_flag[3] = 0;
					}
					//ѡ��3��ģʽ
					if(model_list_flag == 3) {
						if(!key_up) {
							delay(10);
							if(!key_up && (gear_list_flag < 10)) {
								gear_list_flag ++;
								while(key_up == 0);
							}
							if(!key_up && (gear_list_flag >= 10)) {
								gear_list_flag = 10;
								while(key_up == 0);
							}
						}
						if(!key_down) {
							delay(10);
							if(!key_down && (gear_list_flag > 1)) {
								gear_list_flag --;
								while(key_down == 0);
							}
							if(!key_down && (gear_list_flag <= 1)) {
								gear_list_flag = 1;
								while(key_down == 0);
							}
						}
						if(gear_list_flag_last != gear_list_flag) {
							show_number(gear_list_flag,4);
							gear_list_flag_last = gear_list_flag;
						}
						if(!enter) {
							delay(10);
							if(!enter) {
								enter_2 = 1;
								while(enter == 0);
							}
						}
						while(enter_2) {
							Gear = gear_list_flag;
							model = 3;
							enter_1 = 0;
							enter_2 = 0;
							Model_select_flag = 0;
							model_flag[0] = 0;
							model_flag[1] = 0;
							model_flag[2] = 0;
							model_flag[3] = 0;
						}
					}
					//ѡ��4��ģʽ
					if(model_list_flag == 4) {
						if(!key_up) {
							delay(10);
							if(!key_up && (time_list_flag < 999)) {
								time_list_flag ++;
								while(key_up == 0);
							}
							if(!key_up && (time_list_flag >= 999)) {
								time_list_flag = 10;
								while(key_up == 0);
							}
						}
						if(!key_down) {
							delay(10);
							if(!key_down && (time_list_flag > 1)) {
								time_list_flag --;
								while(key_down == 0);
							}
							if(!key_down && (time_list_flag <= 1)) {
								time_list_flag = 1;
								while(key_down == 0);
							}
						}
						if(time_list_flag_last != time_list_flag) {
							show_time(time_list_flag);
							time_list_flag_last = time_list_flag;
						}
						if(!enter) {
							delay(10);
							if(!enter) {
								enter_2 = 1;
								while(enter == 0);
							}
						}
						while(enter_2) {
							time = time_list_flag;
							enter_1 = 0;
							enter_2 = 0;
							Model_select_flag = 0;
							model = 4;
							model_flag[0] = 0;
							model_flag[1] = 0;
							model_flag[2] = 0;
							model_flag[3] = 0;
						}
					}
				}
			}
		}
	}
}