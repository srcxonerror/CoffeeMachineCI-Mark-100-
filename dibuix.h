
//Funci� responsable d'escriure els textos per pantalla
void writeTxt(byte page, byte y, char * s);

//Imprimeix la part alta i baixa del pot de caf� amb el fum (animaci� 1)
void printTU1();

//Imprimeix la part alta i baixa del pot de caf� amb el fum (animaci� 2)
void printTU2();

//Itera entre les funcions del dibuix del pot de caf�
void fum();

//Funci� responsable de dibuixar el marge de la barra de c�rrega
void marge();  

//Funci� responsable de la animaci� de la barra
void updatebar();

//Funci� responsable de dibuixar el splash donat per l'enunciat
void paintSplash();

//Funci� responsable de enviar strings a la terminal
void sendString(char * s);

//Funci� responsable de imprimir els nostres noms i el nom del projecte al inici
void show_init_program();

//Imprimeix els marges de les barres de selecci� de temperatura
void marge0(int long0);

//Imprimeix els marges de les barres de selecci� de tipus de caf�
void marge1(int long1);

//Imprimeix els marges de les barres de selecci� de dosi
void marge2(int long2);

//Imprimeix la selecci� de temperatura
void tipus0(int long0);
//Imprimeix la selecci� de tipus de caf�

void tipus1(int long1);

//Imprimeix la selecci� de dosi
void tipus2(int long2);

//Imprimeix "<>" per indicar quina barra s'esta tractant
void punters(int bartype);











