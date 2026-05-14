#include "main.h"
#include <stdlib.h>
#include <time.h>


void randomizaJogo(GameSettings * gs , MatrizJogo * mj){
    int n = gs->numBaralhos , arrCartas[n];
    initArrCartas(arrCartas,n);
    shuffleArray(arrCartas,n);
    initMatrizCartasJogo(arrCartas,mj);
}


void initMatrizCartasJogo(int arrayCartas[],MatrizJogo * mj){
    int i,j,counter=0;
    PilhaDeCartas * p = mj->linhasMatriz;
    for(i=0;i<mj->numLinhasMatriz;i++){
        for(j=0 ;j  < (p + i)->numCartasPilha ; j++ , counter++){
            ((p + i)->cartasPilha + j)->naipe = convertToNaipe(arrayCartas[counter]/4);
            ((p + i)->cartasPilha + j)->valor = valorCarta(arrayCartas[counter]);
        }
    }
}


void shuffleArray(int arrayCartas[] , int n){

}


void initArrCartas(int arrCartas[] , int n){
    for(int i=0;i<n;i++){
        arrCartas[i] = i + 1;
    }
}