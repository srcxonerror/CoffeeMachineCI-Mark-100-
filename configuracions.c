#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "config.h"
#include "GLCD.h"
#include "ascii.h"
#include "configuracions.h"

extern int timer;
extern int Duty;

void configPic() {

   ANSELA=0x00;
   ANSELB=0x00;
   ANSELC=0x00;
   ANSELD=0x00;

   TRISA=0x00;
   TRISB=0x00;
   TRISC=0xFF;
   TRISD=0x00;
   TRISE=0x02;

   GIE = 1;
   PEIE = 1;
   IPEN = 0;
   RC1IF = 0;
   RC1IE = 1;
}

void configTIMER() {
   T0CONbits.T08BIT = 0;
   T0CONbits.T0CS = 0;
   T0CONbits.PSA = 0;
   T0CONbits.T0PS2 = 0; //ens interessa tenir prescaler de 16
   T0CONbits.T0PS1 = 1;
   T0CONbits.T0PS0 = 1;
   TMR0 = timer;//(0.1/(100/tempspantalla))/(scicle*prescaler);
   T0CONbits.TMR0ON = 0;
   TMR0IF = 0;
   TMR0IP = 1;
   TMR0IE = 1;
   IPEN= 1;
   GIEH = 1;
   GIEL = 1;
}



void configUSART() {

 SPBRG1 = 16;
 SPBRGH1 = 0;
 BAUDCON1bits.BRG16 = 1;
 TXSTA1bits.BRGH = 1;
 TXSTA1bits.SYNC = 0;
 RCSTA1bits.SPEN = 1;
 TXSTA1bits.TXEN = 1;
 RCSTAbits.CREN = 1;
 PIR1bits.RC1IF = 0;
}

void configGLCD() {
   GLCDinit();		   //Inicialitzem la pantalla
   clearGLCD(0,7,0,127);   //Esborrem pantalla
   setStartLine(0);        //Definim linia d'inici
}

void configPWD(){

   CCPTMRS0bits.C3TSEL = 0x00; //PWM mode use timer2
   CCP3CONbits.CCP3M = 0xC; //PWM mode
   PR2 = 249;
   unsigned long value = Duty*4*(PR2 + 1)/100;
   CCP3CONbits.DC3B = value%4;
   CCPR3L = value/4;
   TMR2 = 0;
   T2CONbits.T2CKPS = 2;
   TMR2ON = 0;

   ADCON0bits.CHS = 0x6;
   ADCON0bits.ADON = 1;
   ADCON1bits.PVCFG = 0;
   ADCON1bits.NVCFG = 0;
   ADCON2bits.ADFM = 1;
   ADCON2bits.ACQT = 0x5;
   ADCON2bits.ADCS = 0x5;
}
