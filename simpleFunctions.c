#include "main.h"
#include <stdio.h>


int valorCarta(int c){
    for(;c>13;c-=13);
    return c;
}

int exp(int base,int expo){
    int ret=1;
    for(int i=0;i<expo;i++){
        ret*=base;
    }
    return ret;
}

char * criarTag(long * tag,char * line){
    int j=0;
    while(*line != ' '){
        *tag+=(*line - 64)*exp(27,j++); //-64 por serem letras maisculas ('A' = 65)
        // Multiplicamos por 27^j para cada tag ser unica (26 letras no alfabeto e apenas letras maiusculas)
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


MovimentoEntrePilhas * comparaTags (MovimentoEntrePilhas * mp ,int tagOrig , int tagDest , int n)
{
    for (int i = 0; i < n; i++) {
        if (mp[i].tagOrig == tagOrig && mp[i].tagDest == tagDest) {
            return &mp[i];
        }
    }
    return NULL;
}


char convertToNaipe(int div){
    switch(div){
        case 0 : 
            return 'C';
        break;
        case 1 :
            return 'D';
        break;
        case 2 :
            return 'H';
        break;
        default :
            return 'S';
        break;
    }
}

