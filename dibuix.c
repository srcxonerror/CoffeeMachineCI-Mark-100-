
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
#define _XTAL_FREQ 8000000 
#define BAUD_RATE 115200 

int TU1[15] = {0x00, 0xC0, 0x46, 0x5B, 0x40, 0x4C, 0x53, 0x40, 0x46, 0x5B, 0xC0, 0x80, 0x80}; 
int TU2[15] = {0x00, 0xC0, 0x4C, 0x53, 0x40, 0x46, 0x5B, 0x40, 0x4C, 0x53, 0xC0, 0x80, 0x80}; 
int TL[15] = {0x30, 0x57, 0x58, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x58, 0x57, 0x34, 0x07};

const char * s1 = "L4A GLCD\n\r";
const char * s2 = "Adam Sarrate Nejjari\n\r ";
const char * s3 = "Abel Perello Vidal\n\r";
const char * s4 = "--------\n\r";

extern int i1;

void writeTxt(byte page, byte y, char * s) { 
   int i=0;
   while (*s!='\n' && *s!='\0') {
      putchGLCD(page, y+i, *(s++));
      i++;
   }
}


void printTU1(){
   for (int i = 0; i < 15; ++i){
      writeByte(2, i + 54, TU1[i]);
      writeByte(3, i + 54, TL[i]);
   }
}


void printTU2(){
   for (int i = 0; i < 15; ++i){
     writeByte(2, i + 54, TU2[i]);
     writeByte(3, i + 54, TL[i]);
   }
}


void fum(){
   for (int i = 0; i < 5; ++i){
      printTU1();
      __delay_ms(500);
      printTU2();
      __delay_ms(500);
   }	
}


void marge(){
   for (int i = 0; i < 101; ++i){
      writeByte(7, i + 12, 0x02);
      writeByte(6, i + 12, 0x04);
   }
  writeByte(7, 11, 0x03); writeByte (6, 11, 0xFC);
  writeByte(7, 113, 0x03); writeByte (6, 113, 0xFC);
}


void updatebar(){
     if (i1%4 == 0) writeByte(6, i1, 0x04);
     else writeByte(6, i1, 0xF4);
     //SetDot(50, i1);
     ++i1;
} 	


void paintSplash() {
   for (byte p = 0; p < 8; ++p) for (byte y = 0; y < 128; ++y) writeByte(p,y,bitmap[p*128+y]); 
}


void sendString(char * s) {
   while (*s!='\0') {
      while (!TX1IF);
      TXREG1 = *s;
      ++s;
   }
}


void show_init_program() {
   paintSplash();			
   __delay_ms(2000);
   clearGLCD(0,7,0,127); //Esborrem pantalla

   writeTxt(2, 9, s1); //Nom proj
   writeTxt(3, 9, s4); //separador
   writeTxt(4, 4, s3); //Abel
   writeTxt(6, 3, s2); //Adam
   __delay_ms(2000);
   clearGLCD(0,7,0,127); //Esborrem pantalla
   
   sendString(s1);			
   sendString(s4);
   sendString(s3);
   sendString(s2);
   __delay_ms(500);
}


void marge0(int long0){
   if(long0 == 1) {
      for (int i = 0; i < 67; ++i) {
	 if(i != 33)
	    writeByte(2, i+12, 0xBD);
	 else writeByte(2, i+12, 0x81);
      }
      for (int i = 67; i < 101; ++i){
	 writeByte(2, i + 12, 0x81);
      }
      writeByte(2, 10, 0xFF); writeByte(2, 114, 0xFF);
      writeByte(2, 11, 0x81); writeByte(2, 113, 0x81);
   }
   
   else if(long0 == 0) {
      for (int i = 0; i < 34; ++i) {
	 writeByte(2, i+12, 0xBD);
      }
      for (int i = 34; i < 101; ++i){
	 if (i == 66) writeByte(2, 78, 0xFF);
	 else writeByte(2, i + 12, 0x81); 
      }
      writeByte(2, 10, 0xFF); writeByte(2, 114, 0xFF);
      writeByte(2, 11, 0x81); writeByte(2, 113, 0x81);
   }
   
   else if(long0 == 2) {
      for (int i = 0; i < 101; ++i){
	 if(i != 33 && i != 66)
	    writeByte(2, i + 12, 0xBD);
	 else writeByte(2, i+12, 0x81);
      }
      writeByte(2, 10, 0xFF); writeByte(2, 114, 0xFF);
      writeByte(2, 11, 0x81); writeByte(2, 113, 0x81);
   }
}


void marge1(int long1){
   if(long1 == 1) {
      for (int i = 0; i < 67; ++i) {
	 if(i != 33)
	    writeByte(4, i+12, 0xBD);
	 else writeByte(4, i+12, 0x81);
      }
      for (int i = 67; i < 101; ++i){
	 writeByte(4, i + 12, 0x81);
      }
      writeByte(4, 10, 0xFF); writeByte(4, 114, 0xFF);
      writeByte(4, 11, 0x81); writeByte(4, 113, 0x81);
   }
   
   else if(long1 == 0) {
      for (int i = 0; i < 34; ++i) {
	 writeByte(4, i+12, 0xBD);
      }
      for (int i = 34; i < 101; ++i){
	 if (i == 66) writeByte(4, 78, 0xFF);
	 else writeByte(4, i + 12, 0x81); 
      }
      writeByte(4, 10, 0xFF); writeByte(4, 114, 0xFF);
      writeByte(4, 11, 0x81); writeByte(4, 113, 0x81);
   }
   
   else if(long1 == 2) {
      for (int i = 0; i < 101; ++i){
	 if(i != 33 && i != 66)
	    writeByte(4, i + 12, 0xBD);
	 else writeByte(4, i+12, 0x81);
      }
      writeByte(4, 10, 0xFF); writeByte(4, 114, 0xFF);
      writeByte(4, 11, 0x81); writeByte(4, 113, 0x81);
   }
}


void marge2(int long2){
   if(long2 == 1) {
      for (int i = 0; i < 67; ++i) {
	 if(i != 33)
	    writeByte(6, i+12, 0xBD);
	 else writeByte(6, i+12, 0x81);
      }
      for (int i = 67; i < 101; ++i){
	 writeByte(6, i + 12, 0x81);
      }
      writeByte(6, 10, 0xFF); writeByte(6, 114, 0xFF);
      writeByte(6, 11, 0x81); writeByte(6, 113, 0x81);
      
   }
   else if(long2 == 0) {
      for (int i = 0; i < 34; ++i) {
	 writeByte(6, i+12, 0xBD);
      }
      for (int i = 34; i < 101; ++i){
	 if (i == 66) writeByte(6, 78, 0xFF);
	 else writeByte(6, i + 12, 0x81); 
      }
      writeByte(6, 10, 0xFF); writeByte(6, 114, 0xFF);
      writeByte(6, 11, 0x81); writeByte(6, 113, 0x81);
   }
   
   else if(long2 == 2) {
      for (int i = 0; i < 101; ++i){
	 if(i != 33 && i != 66)
	    writeByte(6, i + 12, 0xBD);
	 else writeByte(6, i+12, 0x81);
      }
      writeByte(6, 10, 0xFF); writeByte(6, 114, 0xFF);
      writeByte(6, 11, 0x81); writeByte(6, 113, 0x81);
   }
}


void tipus0(int long0) {
   if(long0 == 0) {
      writeTxt(1, 3, "Temperatura: Freda  ");	//50º
   }
   else if(long0 == 1) {
      writeTxt(1, 3, "Temperatura: Tebia  ");	//60º
   }
   else if(long0 == 2) {
      writeTxt(1, 3, "Temperatura: Calenta");	//70º
   }
}


void tipus1(int long1) {
   if(long1 == 0) {
      writeTxt(3, 3, "Tipus: Curt  ");	// 10seg
   }
   else if(long1 == 1) {
      writeTxt(3, 3, "Tipus: Normal");	//15 seg
   }
   else if(long1 == 2) {
      writeTxt(3, 3, "Tipus: Llarg ");	//20 seg
   }
}


void tipus2(int long2) {	
   if(long2 == 0) {
      writeTxt(5, 3, "Dosi: Suau  ");	//5 seg
   }
   else if(long2 == 1) {
      writeTxt(5, 3, "Dosi: Normal");	//10 seg
   }
   else if(long2 == 2) {
      writeTxt(5, 3, "Dosi: Fort  ");	//15 seg
   }
}


void punters(int bartype) {
   if(bartype == 0) {
      writeTxt(2, 0, "<");
      writeTxt(4, 0, " ");
      writeTxt(6, 0, " ");
      writeTxt(2, 24, ">");
      writeTxt(4, 24, " ");
      writeTxt(6, 24, " ");
   }
   
   if(bartype == 1) {
      writeTxt(2, 0, " ");
      writeTxt(4, 0, "<");
      writeTxt(6, 0, " ");
      writeTxt(2, 24, " ");
      writeTxt(4, 24, ">");
      writeTxt(6, 24, " ");
   }
   
   if(bartype == 2) {
      writeTxt(2, 0, " ");
      writeTxt(4, 0, " ");
      writeTxt(6, 0, "<");
      writeTxt(2, 24, " ");
      writeTxt(4, 24, " ");
      writeTxt(6, 24, ">");
   }
}









