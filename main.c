#include <stdlib.h>
#include "main.h"


int main(int argc,char * argv[]){
    //Seria mais eficiente utilizar logo ponteiros de memoria inves de copiar memoria, mas assim poupa se instrucoes
    GameSettings currentGame = initStructs();
    MatrizJogo mj = initMatrizJogo();
    int notSuccess = readfiles(&currentGame,argv[1],&mj);
    //Se houver erro com o ficheiro success estara em 1
    if(argc<2 || notSuccess){
        printf("ERRO!! Não introduziu o nome do ficheiro ou introduziu-o incorretamente\n");
        return 1;
    }
}