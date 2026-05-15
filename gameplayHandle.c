#include "main.h"
#include <stdio.h>
#include <stdlib.h>




PossiveisJogadas efetuaJogada(GameSettings *gs , MatrizJogo * mj ,LastMoveLL * lm , int pilha1 , int pilha2 ,int num){

}


int verificaCondicoesPilha(ArrayFlagsPegar * arr , PilhaDeCartas * p , int num){
    
}

PossiveisJogadas cartasPegaveis(GameSettings *gs , MatrizJogo * mj , int pilha , int num){
    int lim = mj->numLinhasMatriz;
    if(pilha > lim) return invalid;
    int valido = 0;
    PilhaDeCartas * pilhaAtual = (mj->linhasMatriz + pilha);
    if(pilhaAtual->numCartasPilha < num ) return invalid;
    ArrayFlagsPegar * arr = encontraMovsTag(gs,pilhaAtual->tagPilha);
    valido = verificaCondicoesPilha(arr,pilhaAtual,num);
    if(valido) return valid;
    else return invalid;
}




void handleEfetuaJogada(GameSettings * gs , MatrizJogo * mj ,LastMoveLL * lm , int pilha1,int * pilha2,int numCartas){
    printf("Insira a pilha onde quer colocar essas cartas\n");
    scanf("%d",pilha2);
    efetuaJogada(gs,mj,lm,pilha1,*pilha2,numCartas);
}



void pedeJogadaUtilizador(int * p1 , int * num){
    printf("Insira o número da pilha à qual quer ir buscar cartas\n");
    scanf("%d",p1);
    printf("Insira o número de cartas que quer pegar\n");
    scanf("%d",num);
}



PossiveisJogadas recebeInput(char jogada){
    switch(jogada){
        case 'Q' :
            return quit;
        break;
        case 'D' : 
            return undo;
        break;
        case 'S' :
            return save;
        break;
        case 'J' :
            return valid;
        break;
        default :
            printf("Inseriste uma jogada inválida , portanto o jogo fechou.");
            return quit;
        break;
    }
}