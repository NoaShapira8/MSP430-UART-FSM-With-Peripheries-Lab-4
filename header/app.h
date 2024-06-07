#ifndef _app_H_
#define _app_H_


enum FSMstate{state0,state1,state2,state3,state4,state5,state6,state7,state8}; // global variable
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern int x,tone_index,LDR_val,tone_index_RT ;
extern unsigned int counter_Func2 ;
extern char CountUp_Str[5],LDR_Str[5] ;
extern unsigned int tone_series[7],tone_series_RT[4] ;
extern float LDR_val_float ;
extern unsigned int Shalem,Sh1,Sh2,Sh3 ;
extern char Shalem_Str[1],Sh1_Str[1],Sh2_Str[1],Sh3_Str[1] ;
//extern const char MENU[] ;
extern unsigned int Menu_index, RX_index;
extern unsigned long int q_5 ;
extern unsigned int q_5_new, ADC_VAL ;
extern char X[] ;
extern int tikon_buzz1,tikon_buzz2 ;
#endif







