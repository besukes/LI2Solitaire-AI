#include <stdlib.h>
#include <stdio.h>
#include "main.h"


PossiveisJogadas interfacePessoaJogo(GameSettings * gs , MatrizJogo * mj ,LastMoveLL * undoState){
    char jogada = 0;
    PossiveisJogadas estadoJogada = valid;
    printf("Indique a jogada que quer efetuar :\n" 
            "Q - Sair\n"
            "D - Desfazer Jogada\n"
            "S - Salvar Jogo\n"
            "J - Efetuar Movimento de Cartas\n"
            "CUIDADO! Se inserires uma jogada inválida , o jogo irá fechar..!\n"
    );
    scanf("%c",&jogada);
    estadoJogada = recebeInput(jogada);
    if(estadoJogada==undo) undoMove(mj,undoState); //tem que se adicionar ao .h
    else if(estadoJogada==valid) estadoJogada = efetuaJogadaMovimentoCartas(gs,mj,undoState);
    return estadoJogada;
}

void gameLoop(GameSettings * gs , MatrizJogo * mj,LastMoveLL * undoState){
    PossiveisJogadas option = valid;
    while(option != quit && option != GameWon ){
        if(option == invalid) printf("Jogada inválida , tente outra vez , mas algo diferente!!\n");
        desenhaInterfaceJogo(gs,*mj);
        option = interfacePessoaJogo(gs,mj,undoState);
    }
    if(option==GameWon) printf("Parabéns , ganhas-te o jogo!!\n");
    else if(option==save){
        //Temos de fazer uma coisa pa salvar o jogo
    }
    else printf("Maior sorte para a próxima!!\n");
    printf("Obrigado por testar o nosso jogo\n");
}


int main(void){
    //Seria mais eficiente utilizar logo ponteiros de memoria inves de copiar memoria, mas assim poupa se instrucoes
    GameSettings currentGame = initStructs();
    MatrizJogo mj = initMatrizJogo();
    LastMoveLL undoState = NULL;
    int notSuccess = readFiles(&currentGame,&mj);
    //Se houver erro com o ficheiro success estara em 1
    if(notSuccess){
        printf("ERRO!! Não introduziu o nome do ficheiro ou introduziu-o incorretamente\n");
        return 1;
    }
    gameLoop(&currentGame,&mj,&undoState);
    memoryFree(currentGame,mj,undoState);
    return 0;
}