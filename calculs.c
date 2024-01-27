#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "config.h"
#include "GLCD.h"
#include "ascii.h"
#include "calculs.h"


typedef enum{
   Ready=0,
   Running=1,
   Finish=2
}state_t;


extern int temperatura;
extern int real;
extern int Duty;
extern int temp;
extern int molinet;
extern int aigua;
extern int long0;
extern int long1;
extern int long2;
extern int bartype;
extern int timer;
extern state_t quinestat;


void checktemperatura(){
   float err = (temperatura - real);
   if (err <= - 5) Duty = 100;
   else if (err >= 5) Duty = 0;
   else Duty =(5 - err)*10;
   unsigned long value = Duty*10;
   CCP3CONbits.DC3B = value%4;
   CCPR3L = value/4;
}


void calcular_temps() {
   temp = 25;
   molinet = 10;
   aigua = 15;
   temperatura = 60;
   
   if(long1 == 0) {temp = temp - 5; timer = timer + 625; aigua = aigua - 5;}
   else if(long1 == 2) {temp = temp + 5; timer = timer - 625; aigua = aigua + 5;}
   
   if(long2 == 0) {temp = temp - 5; timer = timer + 625; molinet = molinet - 5;}
   else if(long2 == 2) {temp = temp + 5; timer = timer - 625; molinet = molinet + 5;}
   
   if(long0 == 0) {temperatura = temperatura - 10;}
   else if(long0 == 2) {temperatura = temperatura + 10;}
   
   checktemperatura();
   
   molinet = ((double)molinet / temp)* 100 ;
   aigua = 99 - ((double)aigua / temp)* 100 ;
}


void configD (){
    if(bartype == 0){
	 ++long0;
	 if (long0 == 3) long0 = 2;
      }
      if(bartype == 1){
	 ++long1;
	 if (long1 == 3) long1 = 2;	    
      }
      
      if(bartype == 2){
	 ++long2;
	 if (long2 == 3) long2 = 2;	 
      }
 }
 
 
void configA() {
   if(bartype == 0){
	 --long0;
	 if (long0 == -1) long0 = 0;
      }
      if(bartype == 1){
	 --long1;
	 if (long1 == -1) long1 = 0;	    
      }
      
      if(bartype == 2){
	 --long2;
	 if (long2 == -1) long2 = 0;	 
      }
 }
 
 
 void quinboto(char dir){
   if (dir == 'x') bartype = (bartype + 1)%3;
   else if (dir == 'w') {bartype = (bartype - 1); if (bartype == -1) bartype = 2;}
   else if(dir == 'd') configD();
   else if(dir == 'a') configA();
   else if(dir == 's') quinestat = Running;

}

 
