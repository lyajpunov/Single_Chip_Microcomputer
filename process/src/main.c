/*************************** 
@LyaJpunov 按键： 按下key1健进行模式选择 P3.0 
按下s1健进行向上选择 P3.1
按下s2健进行向下选择 P3.2 
按下enter进行确认   P3.3 
***************************/ 


#include "reg52.h" 
#include "init.h" 
#include "delay.h" 
#include "Key.h" 
#include "lcd.h" 
#include "ds18b20.h" 
#include "moto.h"
#include "model.h" 
extern unsigned int model ; //模式 1 待机 2 智能 3 档位 4 定时 
extern unsigned int time ;  //定时时间（分钟） 
extern unsigned int Gear ;  //档位 
 /********************************************************************* 
 0FF 待机模式 此时前三位显示OFF 
 A智能模式 第一位蓝色显示A 后两位红色显示温度 此时可根据温度智能调整转速 
 B风速模式 第一位蓝色显示b 后两位红色显示档位 此时可以按键上下调整转速 
 C定时模式 此模式在AB两种均可用 使用时第一位呈现C，后三位可用于调整时间，单位为分钟（最高999分钟，16.65小时） 
 E进入模式选择模式 
 **********************************************************************/ 
 
int main(void) {
    init(); 
    model = 1; 
    Gear = 0; 
    while(1) { 
        key_scan(); 
        model_select(model); 
    } 
}
