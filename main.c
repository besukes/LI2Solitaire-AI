#include <dirent.h>
#include <stdlib.h>
#include "main.h"
//ver dirent
//fgets


int main(void){
    //Seria mais eficiente utilizar logo ponteiros de memoria inves de copiar memoria, mas assim poupa se instrucoes
    GameSettings currentGame=initStructs();
    readfiles(&currentGame);
}