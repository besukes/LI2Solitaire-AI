#include "main.h"
#include <stdlib.h>
#include <time.h>

void initMatrizCartasJogo(int arrayCartas[],MatrizJogo * mj){
    int i,j,counter=0;
    for(i=0;i<mj->numLinhasMatriz;i++){
        PilhaDeCartas * p = mj->linhasMatriz + i;
        int maxPilha = p->numCartasPilha;
        for(j=0 ;j  < maxPilha ; j++ , counter++){
            Carta * c = p->cartasPilha + j ;
            c->naipe = convertToNaipe(arrayCartas[counter]/4);
            c->valor = valorCarta(arrayCartas[counter]);
        }
    }
}


void shuffleArray(int arrayCartas[] , int n){
    srand(time(NULL));
    for(int i = 0 ; i < n-1 ; i++){
        int j = rand() % 52;
        int temp = arrayCartas[i];
        arrayCartas[i] = arrayCartas[j];
        arrayCartas[j] = temp;
    }
}

void initArrCartas(int arrCartas[] , int n){
    for(int i=0;i<n;i++){
        arrCartas[i] = i + 1;
    }
}

void randomizaJogo(GameSettings * gs , MatrizJogo * mj){
    int n = gs->numBaralhos , arrCartas[n];
    initArrCartas(arrCartas,n);
    shuffleArray(arrCartas,n);
    initMatrizCartasJogo(arrCartas,mj);
}



