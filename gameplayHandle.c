#include "main.h"
#include <stdio.h>
#include <stdlib.h>


int verificaCondicoesPilha(ArrayFlagsPegar * arr , PilhaDeCartas * p , int num){
    
}



PossiveisJogadas jogadaValida(MovimentoEntrePilhas * mov , MatrizJogo * mj , int pilha1 , int pilha2 , int num){
    int lim = mj->numLinhasMatriz;
    if(pilha1 > lim) return invalid;
    int valido = 0;
    PilhaDeCartas * pilhaAtual = (mj->linhasMatriz + pilha1);
    if(pilhaAtual->numCartasPilha < num ) return invalid;
    ArrayFlagsPegar * arr = encontraMovsTag(gs,pilhaAtual->tagPilha);
    valido = verificaCondicoesPilha(arr,pilhaAtual,num);
    if(valido) return valid;
    else return invalid;
}


PossiveisJogadas handleEfetuaJogada(GameSettings * gs , MatrizJogo * mj ,LastMoveLL * lm , int pilha1,int * pilha2,int numCartas){
    
}


PossiveisJogadas efetuaJogadaMovimentoCartas(GameSettings * gs , MatrizJogo * mj , LastMoveLL * undoState){
    int pilha1 , pilha2 , numCartas;
    PossiveisJogadas estadoJogada = valid;
    pedeJogadaUtilizador(&pilha1,&pilha2,&numCartas);
    long tag1 = procuraTag(mj,pilha1) , tag2 = procuraTag(mj,pilha2);
    if(tag1!=(-1) && tag2!=(-1)){
        MovimentoEntrePilhas * mov = comparaTags(gs->jogo.movimentoPilhas,tag1,tag2,gs->jogo.numCondicoesMov);
        estadoJogada = jogadaValida(mov,mj,pilha1,pilha2,numCartas);
        if(estadoJogada == valid) estadoJogada = handleEfetuaJogada(gs,mj,undoState,pilha1,&pilha2,numCartas);
    }
    else estadoJogada = invalid;
    return estadoJogada;
}




void pedeJogadaUtilizador(int * p1 , int * p2 ,int * num){
    printf("Insira o número da pilha à qual quer ir buscar cartas\n");
    scanf("%d",p1);
    printf("Insira o número de cartas que quer pegar\n");
    scanf("%d",num);
    printf("Insira a pilha onde quer colocar essas cartas\n");
    scanf("%d",p2);
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