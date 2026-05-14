#include <stdlib.h>
#include "main.h"


int main(void){
    //Seria mais eficiente utilizar logo ponteiros de memoria inves de copiar memoria, mas assim poupa se instrucoes
    GameSettings currentGame = initStructs();
    MatrizJogo mj = initMatrizJogo();
    int notSuccess = readfiles(&currentGame,&mj);
    //Se houver erro com o ficheiro success estara em 1
    if(notSuccess){
        printf("ERRO!! Não introduziu o nome do ficheiro ou introduziu-o incorretamente\n");
        return 1;
    }
    randomizaJogo(&currentGame,&mj);
    return 0;
}