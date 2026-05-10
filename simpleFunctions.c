#include "main.h"

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
    while(*line != '#' && *line!='\n' && *line!=' '){
        num = (*line-48)*exp(10,i--);
        line++;
    }
    return num;
}