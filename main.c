 /* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "config.h"
#include "GLCD.h"
#include "ascii.h"
#include "splash.h"
#include "dibuix.h"
#include "configuracions.h"
#include "calculs.h"
#include "calculinterr.h"


#define _XTAL_FREQ 8000000 
#define BAUD_RATE 115200 

typedef enum{
   Ready=0,
   Running=1,
   Finish=2
}state_t;


double b = 4050.0; // constant
int R2 = 4700; //resistencia donada al enunciat
double A = 0.0059257; // donada al enunciat
int long0 = 1; //valor que ens indica el tipus de temperatura
int long1 = 1; //15 //->2 20 // ->0 10 //Valor que ens indica el tipus de cafè
int long2 = 1; //10 //->2 15 // ->0 5 //Valor que ens indica la dosi de cafè
int bartype = 0; //Valor que ens indica quina barra estem usant
int timer = 65536 - 3125;  //0 seons + 25 (mode normal-normal)
int countimer = 0; //contador utilitzat per a la barra de càrrega
int haacabat = 0; //Contador utlitzat per a saber quan s'ha arribat al final de la càrrega
int i1 = 13; //Valor inical de on es comencen a dibuixar les barres de càrrega respecte les x
state_t quinestat = Ready; //Valor al que assignem el estat actual
int bool = 1; //Valor que es ajuda a realitzar un cert numero de càlculs NOMÉS UN COP en el while(1) del main.
int molinet = 10; //Valors inicial del temps afegit del molinet
int aigua = 15;//Valors inicial del temps afegit del injector d'aigua
int temp = 25;	//inicialment 25 per (15 + 10)
int temperatura = 60; //Valor de la temperatura inicial
int real = 60; //Valor de la temperatura inicial calculada amb la fórmula donada
int Duty = 50; //valor inicial del Duty
double vout = 0; 


void gestio_errors(){
   if (RCSTAbits.FERR || RCSTAbits.OERR) {
      RCSTAbits.CREN = 0;
      RCSTAbits.FERR = 0;
      RCSTAbits.OERR = 0;
      RCSTAbits.CREN = 1;
   }
}


void main(void)
{ 
   configPic(); //pic18f45k22
   configUSART(); //USART
   configGLCD(); //GLCD
   configTIMER();
   configPWD();
   show_init_program();
   
   int boto[5] = {0, 0, 0, 0, 0};
   
   while (1) {

      
      if(quinestat == Ready) {
      Duty = 0;
      bool = 1;
	 if (PORTCbits.RC0 && !boto[0]){ // up
	    bartype = (bartype - 1);
	    if (bartype == -1) bartype = 2;
	    boto[0] = 1;
	 }
	 else if (!PORTCbits.RC0 && boto[0]) boto[0] = 0;
	 
	 
	 if (PORTCbits.RC1 && !boto[1]){
	    bartype = (bartype + 1)%3;
	    boto[1] = 1;
	 }
	 else if (!PORTCbits.RC1 && boto[1]) boto[1] = 0;
	 
	 if (PORTCbits.RC2 && !boto[2]){
	    configA();
	    boto[2] = 1;
	 }
	 else if (!PORTCbits.RC2 && boto[2]) boto[2] = 0;
	 
	 if (PORTCbits.RC3 &&!boto[3]){
	    configD();
	    boto[3] = 1;
	 }
	 else if (!PORTCbits.RC3 && boto[3]) boto[3] = 0;
	 
	 if (PORTCbits.RC4 && !boto[4]){
	    quinestat = Running;
	    boto[4] = 1;
	 }
	 else if (!PORTCbits.RC4 && boto[4]) boto[4] = 0;
	 
	 if (RCSTA1bits.OERR == 1) {
	    RCSTA1bits.CREN = 0;
	    RCSTA1bits.CREN = 1;
	 }
	 punters(bartype);
	
	 tipus0(long0);
	 marge0(long0);
	
	 tipus1(long1);
	 marge1(long1);

	 tipus2(long2);
	 marge2(long2);
	 gestio_errors();
	 
      }
      else if(quinestat == Running) {

	 
	 if(bool == 1) { 
	    bool = 0;
	    calcular_temps();
	    clearGLCD(0,7,0,127);
	    marge();
	    __delay_ms(500);
	    PORTAbits.RA0 = 1;
	    char buff [256];
	    sprintf(buff, "Preparing coffe...\n");
	    writeTxt(5, 3, buff);
	    T0CONbits.TMR0ON = 1;
	 } 
      }
   }
}

