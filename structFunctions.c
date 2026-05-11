#include "main.h"
#include <stdlib.h>

void inicializaAutoMoves(AutoMoves * am , int tagOrig , int tagDest){
    am->tagOrig = tagOrig;
    am->tagDest = tagDest;
    am->arr->numFlagsColocavel=0;
    am->arr->numFlagsPegavel=0;
    am->numMovs=0;
    am->variasCartasMoviveis=0;
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