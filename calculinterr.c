#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "config.h"
#include "GLCD.h"
#include "ascii.h"
#include "calculinterr.h"
#include "dibuix.h"
#include "configuracions.h"
#include "calculs.h"


typedef enum{
   Ready=0,
   Running=1,
   Finish=2
}state_t;


extern int haacabat;
extern int long0;
extern int long1;
extern int long2;
extern int bartype;
extern int timer;
extern int i1;
extern int Duty;
extern int countimer;
extern int aigua;
extern state_t quinestat;

void reset(){ 
   quinestat = Ready;
   clearGLCD(0, 7, 0, 127);
   
   haacabat = 0;
   long0 = 1;
   long1 = 1;
   long2 = 1;
   bartype = 0;
   
   timer = 65536 - 3125;
   i1 = 13;
}


 void acabat(){
   quinestat = Finish; 
   T0CONbits.TMR0ON = 0;
   //TMR2ON = 0;
   Duty = 0;
   
   unsigned long value = Duty*10;
   CCP3CONbits.DC3B = value%4;
   CCPR3L = value/4;
   
   PORTAbits.RA1 = 0;
   clearGLCD(1, 1, 45, 65);
   char buff [256];
   sprintf(buff, "Ready to drink!   \n");
   writeTxt(5, 3, buff);
   fum();
   //__delay_ms(3000);
   reset();
}


void segon(){
   ++haacabat;
   updatebar();
   countimer = 0;
}


void canvimode() {
   PORTAbits.RA0 = 0;
   PORTAbits.RA1 = 1;
   TMR2ON = 1;
}

 
void interrupt RSI() {
   if (RC1IF && RC1IE) {
      char dir = RCREG1; // si volguessim guardar quina tecla estem clicant, el guardem de RCREG1
      quinboto(dir);
   }
   else if(TMR0IF && TMR0IE) {
      TMR0 = timer;//(0.1/(100/tempspantalla))/(scicle*prescaler); //625
      TMR0IF = 0;
      if (countimer == 9){
	 if (haacabat == 99) acabat();
	 else segon();
	 if (haacabat == aigua) canvimode();
      }
      
      else ++countimer;
   }
}
