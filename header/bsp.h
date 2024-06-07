#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx


#define   debounceVal      250
#define   half_sec_delay   500  // 500ms


//-------------------------------------------------------------
//            LCD abstraction
//-------------------------------------------------------------
// LCD Data
#define LCD_Data_Sel    P1SEL
#define LCD_Data_Dir    P1DIR
#define LCD_Data_Write  P1OUT
#define LCD_Data_Read   P1IN

// LCD Control
#define LCD_CTL_Sel     P2SEL
#define LCD_CTL_Dir     P2DIR
#define LCd_CTL_Write   P2OUT


//-------------------------------------------------------------
//            RGB + Buzzer abstraction: P2.0 - 2.2, P2.4
//-------------------------------------------------------------
#define RGB_Port_Sel     P2SEL
#define RGB_Port_Dir     P2DIR
#define RGB_Port_Write   P2OUT
#define RGB_Port_Read    P2IN


//-------------------------------------------------------------
//            LDR abstraction: P1.3
//-------------------------------------------------------------
#define UART_Port_Sel      P1SEL
#define UART_Port_Sel2     P1SEL2
#define UART_Port_Dir      P1DIR
#define UART_Port_Out      P1OUT
#define UART_Port_In       P1IN

//-------------------------------------------------------------
//            LDR abstraction: P1.3
//-------------------------------------------------------------
#define LDR_Port_Sel     P1SEL
#define LDR_Port_Dir     P1DIR
#define LDR_Port_Read    P1IN


//------------------------------------------------------------
// PushButtons abstraction
#define PBsArrPort         P1IN
#define PBsArrIntPend      P1IFG
#define PBsArrIntEn        P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL
#define PBsArrPortDir      P1DIR
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04


extern void GPIOconfig(void);
extern void TimerA0_Config(unsigned int Delay);
extern void TimerA1_Config_Buzzer(unsigned int Delay);
extern void ADC_config(void);


#endif

/*
// LEDs abstraction
#define LEDsArrPort        P9OUT
#define LEDsArrPortDir     P9DIR
#define LEDsArrPortSel     P9SEL

// Switches abstraction
#define SWsArrPort         P2IN
#define SWsArrPortDir      P2DIR
#define SWsArrPortSel      P2SEL
#define SWmask             0x0F

// PushButtons abstraction
#define PBsArrPort	       P1IN
#define PBsArrIntPend	   P1IFG
#define PBsArrIntEn	       P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL
#define PBsArrPortDir      P1DIR
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04
//#define PB3                0x08

// Keypad abstraction
#define KeypadPortIN          P10IN
#define KeypadPortOUT         P10OUT
#define KeyPadPortDir         P10DIR

// Keypad IRQ abstraction

#define KeyPad_IRQ_Port        P2IN
#define KeyPad_IRQ_Pend        P2IFG
#define KeyPad_IRQ_En          P2IE
#define KeyPad_IRQ_EdgeSel     P2IES
#define KeyPad_IRQ_Sel         P2SEL
#define KeyPad_IRQ_Dir         P2DIR
*/








