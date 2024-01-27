
//Funció responsable de redefinir els valors inicials del programa
void reset();

//Funció responsable de gestionar les operacions i funcions quan ens trobem al estat "Finish"
void acabat();

//Funció responsable de realitzar la gestió de funcions cada 1/100 de la barra 
void segon();

//Funció responsable de canviar el us de molinet a injector de aigua
void canvimode();

//Funció principal de la gestió de interrupcions
void interrupt RSI();
