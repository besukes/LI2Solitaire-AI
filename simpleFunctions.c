#include "main.h"
#include <stdio.h>

int exp(int base,int expo){
    int ret=1;
    for(int i=0;i<expo;i++){
        ret*=base;
    }
    return ret;
}

char * criarTag(int * tag,char * line){
    int j=0;
    while(*line != ' '){
        *tag+=(*line)*exp(2,j++); // Multiplicamos por 2^j para cada tag ser unica
        line++;
    }
    return (line+1);
}


int numCaracteres(char * line){
    int i=(-1);
    while(*line != ' ') i++;
    return i;
}

int strToNumber(char * line){
    int i=numCaracteres(line) , num = 0;
    while(*line != '#' && *line!='\n' && *line!=' ' && *line != '\0'){
        num = (*line-48)*exp(10,i--);
        line++;
    }
    return num;
}

void calculaRulesPilha(RegrasPilha * rp , char * line){
    rp->cartaTopoVisivel=0;
    rp->existeMaxCartas=0;
    rp->todaPilhaVisivel=0;
    while(*line != '#' && *line!='\n' && *line!=' ' && *line != '\0'){
        if(*line == '=') rp->todaPilhaVisivel = 1;
        else if(*line == '^') rp->cartaTopoVisivel = 1;
        else if(*line == '1') rp->existeMaxCartas = 1;
    }
}
MovimentoEntrePilhas * comparaTags (GameSettings *gs ,int tagOrig , int tagDest)
{
    for (int i = 0; i < gs->jogo.numCondicoes; i++) {
        if (gs->jogo.movimentoPilhas[i].tagOrig == tagOrig && 
            gs->jogo.movimentoPilhas[i].tagDest == tagDest) {
            return &gs->jogo.movimentoPilhas[i];
        }
    }
    return NULL;
}

void calculaAutoFlags(AutoMoves * am , char * line){
    
}

