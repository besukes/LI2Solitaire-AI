#include "main.h"
#include <stdio.h>
#include <stdlib.h>



int verifyColocarCartas(MovimentoEntrePilhas * mov , Carta * ultimaCartaOrig , Carta * cartaDest){
    int valido = 1 , n = mov->numMovsC;
    ArrayFlagsColocar * arr = mov->arrC;
    for(int i=0;i<n && arr != NULL && valido == 1;i++,arr++){
        int k = arr->numFlagsColocavel;
        for(int j=0;j<k && valido == 1;j++){
            int (*func)(Carta,Carta) = arr->flagsColocavel[j];
            valido = valido && func(*ultimaCartaOrig,*cartaDest);
        }
    }
    return valido;
}


int validaCondicoes(ArrayFlagsPegar * arr , PilhaDeCartas * p , int num){
    int i = p->numCartasPilha , lim = i-num + 1 , max = arr->numFlagsPegavel ,
        verify = 1;
    for(;i>lim && verify == 1;i--){
        for(int j=0;j<max && verify == 1;j++){
            int (*func)(Carta,Carta) = arr->flagsPegavel[j];
            if(num>1 && !arr->variasCartasMoviveis) verify = 0;
            verify = verify && func(*(p->cartasPilha + i),*(p->cartasPilha + i - 1));
        }
    }
    return verify;
}

int validaRestricoes(ArrayFlagsPegar * arr , MatrizJogo * mj , int pilha1){
    int lim = arr->numRestricoes , valid = 1;
    for(int i=0;i<lim && valid == 1;i++){
        int (*func)(int,MatrizJogo) = arr->flagRestricoes[i];
        valid = valid && func(pilha1,*mj);
    }
    return valid;
}

int verificaPegarCartasValido(MovimentoEntrePilhas * mov , PilhaDeCartas * p, int num , MatrizJogo * mj , int pilha1){
    int valido = 0 , n = mov->numMovsP;
    ArrayFlagsPegar * arr = mov->arrP;
    for(int i=0;i<n && arr != NULL && valido == 0;i++,arr++){
        valido = validaCondicoes(arr,p,num) && validaRestricoes(arr,mj,pilha1);
    }
    return valido;
}


PossiveisJogadas jogadaValida(MovimentoEntrePilhas * mov , MatrizJogo * mj , int pilha1 , int pilha2 , int num){
    if(mov==NULL) return invalid;
    PilhaDeCartas * pilhaOrig = (mj->linhasMatriz + pilha1) , * pilhaDest = (mj->linhasMatriz + pilha2);
    if(pilhaOrig->numCartasPilha < num ) return invalid;
    Boolean validoPegavel = verificaPegarCartasValido(mov,pilhaOrig,num,mj,pilha1) , validoColocavel = 0;
    int norig = pilhaOrig->numCartasPilha - 1, ndest = pilhaDest->numCartasPilha - 1;
    if(validoPegavel){
        validoColocavel = verifyColocarCartas(mov,pilhaOrig->cartasPilha + norig - num,pilhaDest->cartasPilha + ndest);
    }
    if(validoColocavel && validoPegavel) return valid;
    else return invalid;
}


PossiveisJogadas handleEfetuaJogada(GameSettings * gs , MatrizJogo * mj ,LastMoveLL * lm , int pilha1,int pilha2,int numCartas){
    
}


PossiveisJogadas efetuaJogadaMovimentoCartas(GameSettings * gs , MatrizJogo * mj , LastMoveLL * undoState){
    int pilha1 , pilha2 , numCartas;
    PossiveisJogadas estadoJogada = valid;
    pedeJogadaUtilizador(&pilha1,&pilha2,&numCartas);
    long tag1 = procuraTag(mj,pilha1) , tag2 = procuraTag(mj,pilha2);
    if(tag1!=(-1) && tag2!=(-1)){
        MovimentoEntrePilhas * mov = comparaTags(gs->jogo.movimentoPilhas,tag1,tag2,gs->jogo.numCondicoesMov);
        estadoJogada = jogadaValida(mov,mj,pilha1,pilha2,numCartas);
        if(estadoJogada == valid){
            estadoJogada = handleEfetuaJogada(gs,mj,undoState,pilha1,pilha2,numCartas);
            efetuaAutoJogada(gs,mj,undoState); //NECESSITA SER FEITA
        }
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