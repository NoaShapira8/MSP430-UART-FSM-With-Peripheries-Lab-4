#include  "../header/halGPIO.h"     // private library - HAL layer


const char MENU[] = "\n"
                    "-------------------------MENU-------------------------\n"
                    "1. Blink RGB LED, color by color with delay of X[ms]\n"
                    "2. Count up onto LCD screen with delay of X[ms]\n"
                    "3. Circular tone series via Buzzer with delay of X[ms]\n"
                    "4. Get delay time X[ms]:\n"
                    "5. LDR 3-digit value [v] onto LCD\n"
                    "6. Clear LCD screen\n"
                    "7. On each PB1 pressed, activate the Buzzer at f(i)\n"
                    "8. Show menu\n"
                    "9. Sleep\n"
                    "------------------------------------------------------\r" ;


//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
}

//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}

//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}

//---------------------------------------------------------------------
//            Get_X_Delay Func
//---------------------------------------------------------------------
void Get_X_Delay() {
    unsigned int Shalem ;
    unsigned int Res ;
    int i ;
    Shalem = (int) x / half_sec_delay ;
    Res = x % half_sec_delay ;

    for(i = 0 ; i < Shalem ; i++) {
        TimerA0_Config(half_sec_delay * 131) ;     // 500 * 131 = FFFF (Convert ms to CCR0 val)
        if (state==state3){
            tikon_buzz1++ ;
        }
        __bis_SR_register(LPM0_bits+GIE);
    }
    if(Res != 0) {
    TimerA0_Config(Res * 131) ;
    if (state==state3){
        tikon_buzz1++ ;
    }
    __bis_SR_register(LPM0_bits+GIE);
    }
}

//---------------------------------------------------------------------
//            Int2Str converter
//---------------------------------------------------------------------
void Int2Str(char *str, unsigned int num){

    int strSize = 0;
    long tmp = num, len = 0;

    // Find the size of the intPart by repeatedly dividing by 10
    while(tmp){
        len++;
        tmp /= 10;
    }

    // Print out the numbers in reverse
    int j;
    for(j = len - 1; j >= 0; j--){
        str[j] = (num % 10) + '0';
        num /= 10;
    }
    strSize += len;
    str[strSize] = '\0';
}

//---------------------------------------------------------------------
//            Str2int converter
//---------------------------------------------------------------------
// this function convert string to integers  to use them after arrived as string from the uart

int str2int( char volatile *str){
int i,res = 0;
for (i = 0; str[i] != '\0'; ++i) {
    if (str[i]> '9' || str[i]<'0')
        return -1;
    res = res * 10 + str[i] - '0';
}

return res;
}

//---------------------------------------------------------------------
//            RotateRight Function
//---------------------------------------------------------------------
void rotateRight(unsigned long int *value, unsigned int rotateBy) {
    *value = (*value >> rotateBy) | (*value << (32 - rotateBy));
}

void rotate32BitInt(unsigned long int *value) {
    int i ;
    for (i = 0; i < 5; i++) {
        rotateRight(value, 1);
    }
}

//---------------------------------------------------------------------
//            Calc_float- converter
//---------------------------------------------------------------------
void Calc_float(unsigned int x) {
    Shalem = x / 1000 ;
    x = x - (Shalem * 1000) ;
    Int2Str(Shalem_Str , Shalem) ;

    Sh1 = x / 100 ;
    x = x - (Sh1 * 100) ;
    Int2Str(Sh1_Str,Sh1) ;

    Sh2 = x / 10 ;
    x = x - (Sh2 * 10) ;
    Int2Str(Sh2_Str,Sh2) ;

    Sh3 = x ;
    Int2Str(Sh3_Str,Sh3) ;
}

//---------------------------------------------------------------------
//            Get_ADC_Val Function
//---------------------------------------------------------------------
unsigned int Get_ADC_Val(void) {
    return ADC10MEM ;
}

//---------------------------------------------------------------------
//            ADC10_on Function
//---------------------------------------------------------------------
void ADC10_on(void) {
    ADC10CTL0 |= ENC + ADC10SC ;  // Start the ADC
}

//---------------------------------------------------------------------
//            ADC10_off Function
//---------------------------------------------------------------------
void ADC10_off(void) {
    ADC10CTL0 &= ~ADC10ON ;     // Stop the ADC
}

//---------------------------------------------------------------------
//            Timer_A0_Off Function
//---------------------------------------------------------------------
void Timer_A0_Off(void) {
    TA0CTL = 0x0000 ;
    TA0CCTL0 = 0x0000 ;
    TACCR0 = 0x0000 ;
    TACCTL1 = 0x0000 ;
    TACCTL2 = 0x0000 ;
}
void Timer_A1_On(void){
    TA1CCTL0 |= CCIFG ;
}
//---------------------------------------------------------------------
//            Timer_A1_Off Function
//---------------------------------------------------------------------
void Timer_A1_Off(void) {
    TA1CTL = 0x0000 ;
    TA1CCTL0 = 0x0000 ;
    TA1CCR0 = 0x0000 ;
    TA1CCTL1 = 0x0000 ;
    TA1CCTL2 = 0x0000 ;
}
//---------------------------------------------------------------------
//            CLR_RGB Function
//---------------------------------------------------------------------
void CLR_RGB(void) {
    RGB_Port_Write &= ~0x07 ;
}

//---------------------------------------------------------------------
//            CLR_LCD Function
//---------------------------------------------------------------------
void CLR_LCD(void) {
    lcd_clear();
}

//---------------------------------------------------------------------
//            Stop_Buzzer Function
//---------------------------------------------------------------------
void Stop_Buzzer(void) {
    Timer_A1_Off();
}
  //*********************************************************************
  //            TimerA0 Interrupt Service Routine
  //*********************************************************************

  #pragma vector = TIMER0_A0_VECTOR
  __interrupt void Timer_A0_ISR (void){
    LPM0_EXIT ;
    if (state==state3){
        tikon_buzz2++ ;
        if (tikon_buzz2 == tikon_buzz1) {
            tone_index++ ;
            tone_index = tone_index % 7 ;
            TimerA1_Config_Buzzer(tone_series[tone_index]) ;
            tikon_buzz2=0 ;
        }
    }
}

  //*********************************************************************
  //            TimerA1 Interrupt Service Routine
  //*********************************************************************

  #pragma vector = TIMER1_A0_VECTOR
  __interrupt void Timer_A1_ISR (void){
    LPM0_EXIT ;
    RGB_Port_Write ^= 0x10 ;
  }


  //*********************************************************************
  //            ADC10 Interrupt Service Rotine
  //*********************************************************************

  #pragma vector = ADC10_VECTOR
  __interrupt void ADC10_ISR(void) {
    LPM0_EXIT ;
  }

  //---------------------------------------------------------------------
  //            Enter from LPM0 mode
  //---------------------------------------------------------------------
  void enterLPM(unsigned char LPM_level){
      if (LPM_level == 0x00)
        _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
          else if(LPM_level == 0x01)
        _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
          else if(LPM_level == 0x02)
        _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
      else if(LPM_level == 0x03)
        _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
          else if(LPM_level == 0x04)
        _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
  }

  //*********************************************************************
  //         USCI A0/B0 Transmit Interrupt Service Rotine
  //*********************************************************************
  #pragma vector=USCIAB0TX_VECTOR
  __interrupt void USCI0TX_ISR(void)
  {
    UCA0TXBUF = MENU[Menu_index++];                 // TX next character

    if (Menu_index == sizeof MENU - 1) {             // TX over?
        Menu_index = 0;
        IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
        IE2 |= UCA0RXIE;                         // Enable USCI_A0 RX interrupt
        state = state0 ;
    }
  }


  //*********************************************************************
  //         USCI A0/B0 Receive Interrupt Service Rotine
  //*********************************************************************
  #pragma vector=USCIAB0RX_VECTOR
  __interrupt void USCI0RX_ISR(void)
  {
      if(state != 4){
          state = UCA0RXBUF - 48;
          __bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
      }
      else{
        X[RX_index++] = UCA0RXBUF;
        if (X[RX_index - 1] == '\0'){
            RX_index = 0;
            x = str2int(X);
                    state = state7;
        }
      }
  }

  //---------------------------------------------------------------------
  //            LCD
  //---------------------------------------------------------------------
  //******************************************************************
  // send a command to the LCD
  //******************************************************************
  void lcd_cmd(unsigned char c){

      LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

      if (LCD_MODE == FOURBIT_MODE)
      {
          LCD_Data_Write &= ~OUTPUT_DATA;// clear bits before new write
          LCD_Data_Write |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
          lcd_strobe();
          LCD_Data_Write &= ~OUTPUT_DATA;
          LCD_Data_Write |= (c & (0x0F)) << LCD_DATA_OFFSET;
          lcd_strobe();
      }
      else
      {
          LCD_Data_Write = c;
          lcd_strobe();
      }
  }


  //******************************************************************
  // send data to the LCD
  //******************************************************************
  void lcd_data(unsigned char c){

      LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_RS(1);
      if (LCD_MODE == FOURBIT_MODE)
      {
              LCD_Data_Write &= ~OUTPUT_DATA;
              LCD_Data_Write |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
              lcd_strobe();
              LCD_Data_Write &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
              LCD_Data_Write &= ~OUTPUT_DATA;
              LCD_Data_Write |= (c & 0x0F) << LCD_DATA_OFFSET;
              lcd_strobe();
      }
      else
      {
              LCD_Data_Write = c;
              lcd_strobe();
      }

      LCD_RS(0);
  }

  //******************************************************************
  // write a string of chars to the LCD
  //******************************************************************
  void lcd_puts(const char * s){

      while(*s)
          lcd_data(*s++);
  }

  //******************************************************************
  // initialize the LCD
  //******************************************************************
  void lcd_init(){

      char init_value;

      if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
      else init_value = 0x3F;

      LCD_RS_DIR(OUTPUT_PIN);
      LCD_EN_DIR(OUTPUT_PIN);
      LCD_RW_DIR(OUTPUT_PIN);
      LCD_Data_Dir |= OUTPUT_DATA;
      LCD_RS(0);
      LCD_EN(0);
      LCD_RW(0);

      DelayMs(15);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();
      DelayMs(5);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();
      DelayUs(200);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();

      if (LCD_MODE == FOURBIT_MODE){
          LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
          LCD_Data_Write &= ~OUTPUT_DATA;
          LCD_Data_Write |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
          lcd_strobe();
          lcd_cmd(0x28); // Function Set
      }
      else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots

      lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
      lcd_cmd(0x1); //Display Clear
      lcd_cmd(0x6); //Entry Mode
      lcd_cmd(0x80); //Initialize DDRAM address to zero
  }



  //******************************************************************
  // lcd strobe functions
  //******************************************************************
  void lcd_strobe(){
    LCD_EN(1);
    asm("nOp");
    //asm("NOP");
    LCD_EN(0);
  }

  //******************************************************************
  // Delay usec functions
  //******************************************************************
  void DelayUs(unsigned int cnt){

      unsigned char j;
      for(j=cnt ; j>0 ; j--) asm("n0p"); // the command asm("nop") takes raphly 1usec

  }
  //******************************************************************
  // Delay msec functions
  //******************************************************************
  void DelayMs(unsigned int cnt){

      unsigned char j;
      for(j=cnt ; j>0 ; j--) DelayUs(1000); // the command asm("nop") takes raphly 1usec

  }


//*********************************************************************
//            PB's Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){

    delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
    if(PBsArrIntPend & PB0){
      PBsArrIntPend &= ~PB0;
      tone_index_RT++ ;
      tone_index_RT=tone_index_RT % 4 ;
        }


//---------------------------------------------------------------------
//            Exit from a given LPM
//---------------------------------------------------------------------
        switch(lpm_mode){
        case mode0:
         LPM0_EXIT; // must be called from ISR only
         break;

        case mode1:
         LPM1_EXIT; // must be called from ISR only
         break;

        case mode2:
         LPM2_EXIT; // must be called from ISR only
         break;

                case mode3:
         LPM3_EXIT; // must be called from ISR only
         break;

                case mode4:
         LPM4_EXIT; // must be called from ISR only
         break;
    }

}





 
