 #include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO configuration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
  if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
   {
     while(1);                               // do not load, trap CPU!!
   }
   DCOCTL = 0;                               // Select lowest DCOx and MODx settings
   BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
   DCOCTL = CALDCO_1MHZ;

  //-------------------------------------------------------------
  //            LCD setup
  //-------------------------------------------------------------
    LCD_Data_Sel &= ~0xF0 ;             // makes P1.4 - P1.7 IO mode
    LCD_Data_Dir |= 0xF0 ;              // makes P1.4 - P1.7 Output mode
    LCD_Data_Write &= ~0xF0 ;           // CLR P1.4 - P1.7

    LCD_CTL_Sel &= ~0xE0 ;             // makes P2.5 - P2.7 IO mode
    LCD_CTL_Dir |= 0xE0 ;              // makes P2.5 - P2.7 Output mode
    LCd_CTL_Write &= ~0xE0 ;           // CLR P2.5 - P2.7

  //-------------------------------------------------------------
  //            RGB + Buzzer setup
  //-------------------------------------------------------------
    RGB_Port_Sel &= ~0x17 ;             // makes P2.0 - P2.2 , P2.4 IO mode
    RGB_Port_Dir |= 0x17 ;              // makes P2.0 - P2.2 , P2.4 Output mode
    RGB_Port_Write &= ~0x17 ;           // CLR P2.0 - P2.2 , P2.4

  //-------------------------------------------------------------
  //            UART setup
  //-------------------------------------------------------------
    UART_Port_Sel |= BIT1 + BIT2 ;      // P1.1 = RXD, P1.2=TXD
    UART_Port_Sel2 |= BIT1 + BIT2 ;     // P1.1 = RXD, P1.2=TXD
    UART_Port_Out &= ~(BIT1 + BIT2) ;

    UCA0CTL1 |= UCSSEL_2;                    // CLK = SMCLK
    UCA0BR0 = 104;                           // config the low bits of baud rate
    UCA0BR1 = 0x00;                          // config the high bits of baud rate
    UCA0MCTL = UCBRS0;
  //-------------------------------------------------------------
  //            LDR setup
  //-------------------------------------------------------------
    LDR_Port_Sel &= ~0x08 ;             // makes P1.3 IO mode
    LDR_Port_Dir &= ~0x08 ;           // makes P1.3 Input mode
  //-------------------------------------------------------------

/*
  // LEDs 8-bit Array Port configuration
  LEDsArrPortSel &= ~0xFF;            // GPIO capability
  LEDsArrPortDir |= 0xFF;             // output dir
  LEDsArrPort = 0x00;				  // clear all LEDs
  
  // Switches Setup
  SWsArrPortSel &= ~0x0F;
  SWsArrPortDir &= ~0x0F;
  */

  // PushButtons Setup
  PBsArrPortSel &= ~0x01;
  PBsArrPortDir &= ~0x01;
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x0C;         // pull-down mode
  PBsArrIntEn |= 0x01;
  PBsArrIntPend &= ~0xFF;            // clear pending interrupts

  /*
 //-------------------------------------------------------------------------------------
 //            KeyPad configuration
 //-------------------------------------------------------------------------------------
    KeyPadPortDir |= ( BIT0 + BIT1 + BIT2 + BIT3) ;
    KeypadPortOUT = 0x00 ;
    
    KeyPad_IRQ_Sel &= ~(BIT1) ; // makes P2.1 IO mode
    KeyPad_IRQ_Pend = 0x00 ; // Clear interrupts for P2.1
    KeyPad_IRQ_En |= (BIT1) ; // enable P2.1 for interrupts
    KeyPad_IRQ_Dir &= ~(BIT1) ;// makes P2.1 Input mode
    KeyPad_IRQ_EdgeSel |= (BIT1) ; // P2.1 falling Edge
*/

    _BIS_SR(GIE);                     // enable interrupts globally
}


//------------------------------------------------------------------------------------- 
//            Timers configuration
//-------------------------------------------------------------------------------------
void TimerA0_Config(unsigned int Delay) {
    TA0CTL = 0x0004 ;  //Clr
    TA0CCR0 = Delay ;
    TACTL = TASSEL_2 + MC_1 + ID_3 ;  //  select: 2 - SMCLK ; control: 1 - Up ; divider: 3 - /8
    TA0CCTL0 = CCIE ;
}

void TimerA1_Config_Buzzer(unsigned int Delay) {
    TA1CTL = 0x0004 ;  //Clr
    TA1CCR0 = Delay ;
    TA1CTL = TASSEL_2 + MC_1 + ID_3 ;  //  select: 2 - SMCLK ; control: 1 - Up ; divider: 3 - /8
    TA1CCTL0 = CCIE ;
    //__bis_SR_register(LPM0_bits+GIE);
}

void ADC_config(void) {
    ADC10AE0 = 0x08 ;     // Select Input A3
    ADC10CTL1 |= INCH_3 + ADC10DIV_7 + ADC10SSEL_3  ;
    ADC10CTL0 |= ADC10SHT_3 + ADC10SR + MSC + ADC10IE +ADC10ON  ;
}

void TimerA1_Config_LDR(unsigned int Delay) {
    TA1CTL = 0x0004 ;  //Clr
    TA1CCR0 = Delay ;
    TA1CTL = TASSEL_2 + MC_1 + ID_3 ;  //  select: 2 - SMCLK ; control: 1 - Up ; divider: 3 - /8
    TA1CCTL0 = CCIE ;
    //__bis_SR_register(LPM0_bits+GIE);
}


/*
//------------------------------------------------------------------------------------- 
//            DMA configuration
//-------------------------------------------------------------------------------------
void DMA_Config_Func2(void){
    DMA0CTL = DMAEN + DMASRCINCR_3 + DMASWDW + DMAIE; //repeated-single, source inc, word-word trans, Interupt enable
    DMACTL0 = DMA0TSEL_1; //TACCR2_IFG trigger
}
*/

             
             
            
  

