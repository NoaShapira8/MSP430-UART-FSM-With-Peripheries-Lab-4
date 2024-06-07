#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
#include     <string.h>
#include    <stdio.h>

enum FSMstate state;
enum SYSmode lpm_mode;
int x = half_sec_delay ;
unsigned int counter_Func2 = 0 ;
unsigned int tone_series [7] = {133 ,106 ,89 ,76 ,66 ,59 ,53} ;
unsigned int tone_series_RT [4] = {76 ,66 ,59 ,53} ;

char CountUp_Str[5],LDR_Str[5] ;
int tone_index=0 ,LDR_val ,tone_index_RT=0;
float LDR_val_float ;
unsigned int Shalem,Sh1,Sh2,Sh3 ;
char Shalem_Str[1],Sh1_Str[1],Sh2_Str[1],Sh3_Str[1] ;
unsigned int Menu_index = 0, RX_index = 0;
unsigned long int q_5;
unsigned int q_5_new ,ADC_VAL;
char X[] ;
int tikon_buzz1=0,tikon_buzz2=0 ;




void main(void){

  state = state8;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  lcd_init() ;
  lcd_clear() ;

  
// ------------FSM-----------------
  while(1){
	switch(state){
	  case state0:
          __bis_SR_register(LPM0_bits+GIE);
		break;
		 
	  case state1:
	      CLR_LCD() ;
	      Stop_Buzzer() ;
          RGB_FUNC() ;
          break;

      case state2:
          CLR_RGB() ;
          Stop_Buzzer() ;
          COUNT_UP();
          break;

      case state3:
          CLR_LCD() ;
          CLR_RGB() ;
          Buzzer_Func() ;
          break;

      case state4:
          //Delay_Time
          CLR_LCD() ;
          CLR_RGB() ;
          Stop_Buzzer() ;
          tikon_buzz1=0 ;
          tikon_buzz2=0 ;
          __bis_SR_register(LPM0_bits+GIE);
          break;

      case state5:
          CLR_RGB() ;
          Stop_Buzzer() ;
          LDR_Func();
          break;

      case state6:
          ClearAll() ;
          break;

      case state7:
          CLR_LCD() ;
          CLR_RGB() ;
          Real_time_func() ;
           break;

      case state8:
          UCA0CTL1 &= ~UCSWRST;                 // **Initialize USCI state machine**
          IE2 |= UCA0TXIE;                      // Enable USCI_A0 TX interrupt
          __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0
          break;

      default:
          state = state8;
          break;
  }
}
}
  
  
  
  
  
  
