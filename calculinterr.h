
//Funci� responsable de redefinir els valors inicials del programa
void reset();

//Funci� responsable de gestionar les operacions i funcions quan ens trobem al estat "Finish"
void acabat();

//Funci� responsable de realitzar la gesti� de funcions cada 1/100 de la barra 
void segon();

//Funci� responsable de canviar el us de molinet a injector de aigua
void canvimode();

//Funci� principal de la gesti� de interrupcions
void interrupt RSI();
