#include "main.h"
#include <stdlib.h>

void inicializaAutoMoves(AutoMoves * am , int tagOrig , int tagDest){
    am->tagOrig = tagOrig;
    am->tagDest = tagDest;
    am->arr->numFlagsColocavel=0;
    am->arr->numFlagsPegavel=0;
    am->arr->colocaEmPilhaVazia = 0;
    am->arr->numRestricoes = 0 ; 
    am->arr->variasCartasMoviveis = 0;
    am->numMovs=0;
}

void initFlagFuncArray(FlagFuncArray * arr){
    arr->numFlagsColocavel=0;
    arr->numFlagsPegavel=0;
    arr->numRestricoes=0;
    arr->variasCartasMoviveis=0;
    arr->colocaEmPilhaVazia=NULL;
}


void initJogoStruct(GameSettings * gs){
    (gs->jogo).nomeJogo=NULL;
    (gs->jogo).numPilhas=0;
    (gs->jogo).numCondicoes=0;
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