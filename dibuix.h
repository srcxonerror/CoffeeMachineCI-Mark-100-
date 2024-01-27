
//Funció responsable d'escriure els textos per pantalla
void writeTxt(byte page, byte y, char * s);

//Imprimeix la part alta i baixa del pot de cafè amb el fum (animació 1)
void printTU1();

//Imprimeix la part alta i baixa del pot de cafè amb el fum (animació 2)
void printTU2();

//Itera entre les funcions del dibuix del pot de cafè
void fum();

//Funció responsable de dibuixar el marge de la barra de càrrega
void marge();  

//Funció responsable de la animació de la barra
void updatebar();

//Funció responsable de dibuixar el splash donat per l'enunciat
void paintSplash();

//Funció responsable de enviar strings a la terminal
void sendString(char * s);

//Funció responsable de imprimir els nostres noms i el nom del projecte al inici
void show_init_program();

//Imprimeix els marges de les barres de selecció de temperatura
void marge0(int long0);

//Imprimeix els marges de les barres de selecció de tipus de cafè
void marge1(int long1);

//Imprimeix els marges de les barres de selecció de dosi
void marge2(int long2);

//Imprimeix la selecció de temperatura
void tipus0(int long0);
//Imprimeix la selecció de tipus de cafè

void tipus1(int long1);

//Imprimeix la selecció de dosi
void tipus2(int long2);

//Imprimeix "<>" per indicar quina barra s'esta tractant
void punters(int bartype);











