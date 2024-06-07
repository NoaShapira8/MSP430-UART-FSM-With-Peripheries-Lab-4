#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer




void RGB_FUNC(void) {
    while(state == state1) {
        RGB_Port_Write = 0x00 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x01 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x02 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x03 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x04 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x05 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x06 ;
        Get_X_Delay() ;
        RGB_Port_Write = 0x07 ;
        Get_X_Delay() ;
    }
}

void COUNT_UP(void) {
    while(state == state2) {
        lcd_clear();
        counter_Func2 = counter_Func2 + 1 ;
        Int2Str(CountUp_Str , counter_Func2) ;
        if (counter_Func2 < 10){
            lcd_puts(CountUp_Str) ;
        }

        else if (counter_Func2 < 100){
            lcd_puts(CountUp_Str) ;
        }

        else if (counter_Func2 < 1000){
            lcd_puts(CountUp_Str) ;
        }

        else if (counter_Func2 < 10000){
            lcd_puts(CountUp_Str) ;
        }

        else {
            lcd_puts(CountUp_Str) ;
        }
        Get_X_Delay() ;
    }
}

void Buzzer_Func(void){
  Get_X_Delay() ;
  while (state==state3) {
  }
}

void LDR_Func(void) {
  ADC_config() ;
  ADC10_on() ;
  __bis_SR_register(LPM0_bits + GIE);

  ADC_VAL = Get_ADC_Val() ;                   // get val in range [0-1023]
  q_5 = (unsigned long int)ADC_VAL * 103 ;    //linear trans, new range of [0 - 3330*2^5]
  rotate32BitInt(&q_5);                       //rotate 5 times to get val of [mv]
  q_5_new = (unsigned int)q_5 ;               //use only 16 LSB bits

  Calc_float(q_5_new) ;
  ADC10_off() ;

  lcd_home();                       //start printing the Val on LCD
  if (Shalem == 0){
     lcd_puts("0");
   }
   else {
     lcd_puts(Shalem_Str) ;
   }
  lcd_puts(".") ;
  lcd_puts(Sh1_Str) ;
  lcd_puts(Sh2_Str) ;
  lcd_puts(Sh3_Str) ;
}


void ClearAll(void) {
    disable_interrupts() ;
    lcd_home() ;
    lcd_clear() ;
    CLR_RGB() ;
    Stop_Buzzer() ;
    counter_Func2 = 0 ;
    enable_interrupts();
    state = state0 ;
}

void Real_time_func(void) {
    TimerA1_Config_Buzzer(tone_series_RT[tone_index_RT]);
    Timer_A1_On();
    __bis_SR_register(LPM0_bits+GIE);

}





