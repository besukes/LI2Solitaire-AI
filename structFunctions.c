#include "main.h"
#include <stdlib.h>


void initArrC(MovimentoEntrePilhas * mov){

}

void initArrP(MovimentoEntrePilhas * mov){
    
}


void initJogoStruct(GameSettings * gs){
    (gs->jogo).nomeJogo=NULL;
    (gs->jogo).numPilhas=0;
    (gs->jogo).numCondicoesMov=0;
    (gs->jogo).movimentoPilhas=NULL;
    (gs->jogo).pilhas=NULL;
}

void initFileStruct(GameSettings * gs){
    (gs->file).tamanho=0;
    (gs->file).instructions=NULL;
}

GameSettings initStructs(void){
    GameSettings gs ;
    initFileStruct(&gs);
    gs.numBaralhos=0;
    initJogoStruct(&gs);
    gs.numCondicoesVitoria=0;
    gs.winCon = NULL;
    gs.jogo.qntdAutoMoves = 0;
    gs.jogo.autoMoves = NULL;
}

MatrizJogo initMatrizJogo(void){
    MatrizJogo mj;
    mj.numLinhasMatriz=0;
    mj.linhasMatriz = NULL;
    return mj;
}

void addCartasLinkedList(LastMoveLL novo , int indx , int num , MatrizJogo m){
    int i = (m.linhasMatriz + indx)->numCartasPilha;
    Carta * pilha = (m.linhasMatriz + indx)->cartasPilha;
    for(int j=i-num , counter = 0 ; j<i ; j++ , counter++){
        (novo->cartasMovidas + counter)->naipe = (pilha + j)->naipe;
        (novo->cartasMovidas + counter)->valor = (pilha + j)->valor;
    }
}


void headLinkedList(LastMoveLL * l , int indexAnterior, int indexNovo, int numCartasMovidas , MatrizJogo matriz){
    LastMoveLL novo = malloc(sizeof(struct LastMoveLL));
    novo->indexPilhaAnterior = indexAnterior;
    novo->indexNovaPilha = indexNovo;
    novo->numCartasMovidas = numCartasMovidas;
    novo->prox = *l;
    novo->cartasMovidas = malloc(sizeof(struct Carta)*numCartasMovidas);
    addCartasLinkedList(novo,indexAnterior,numCartasMovidas,matriz);
    *l=novo;
}