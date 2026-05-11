#include "main.h"
#include <stdlib.h>




FlagFunctionsP flagPegavelCalcAux(MovimentoEntrePilhas * mov, char * line){
    switch(*line){
        case 'x' :
            return &alternadosNaipes;
        break;
        case 'c' :
            return &mesmaCor;
        break;
        case 'd' : 
            return &diferentesCores;
        break;
        default:
            return NULL;
        break;
    }
}

FlagFunctionsP flagPegavelCalc(MovimentoEntrePilhas * mov , char * line){
    switch(*line){
        case '*' :
            mov->variasCartasMoviveis=1;
            return &sempreMovivel;
        break;
        case '+' :
            mov->variasCartasMoviveis=1;
            return NULL;
        break;
        case '[' :
            return &flagDecrescente;
        break;
        case ']' :
            return &flagCrescente;
        break;
        case 'm' :
            return &mesmoNaipe;
        break;
        default:
            return flagPegavelCalcAux(mov,line);
        break;
    }
}

// NECESSITO FAZER ESTA FUNCAO AINDA NAO ESTA FEITA
FlagFunctionsP flagColocavelCalcAux(MovimentoEntrePilhas * mov, char * line){
    switch(*line){
        case 'C' :
            return ;
        break;
        case 'D' :
            return ;
        break;
        case 'V' : 
            return ;
        break;
        default:
            return calcUltimaCarta(mov,line);
        break;
    }
}
// NECESSITO FAZER ESTA FUNCAO AINDA NAO ESTA FEITA
FlagFunctionsC flagColocavelCalc(MovimentoEntrePilhas * mov , char * line){
    switch(*line){
        case '<' :
            return ;
        break;
        case '>' :
            return ;
        break;
        case '~' :
            return ;
        break;
        case 'M' :
            return ;
        break;
        case 'X' :
            return ;
        break;
        default:
            return flagColocavelCalcAux(mov,line);
        break;
    }
}


/////////////////////////////////////////////////Funcoes de ver se as cartas sao pegaveis////////////////////////////////////

int diferentesCores(Carta carta1,Carta carta2){
    if(carta1.naipe == 'C' || carta1.naipe == 'O'){
        return (carta2.naipe == 'E' || carta2.naipe == 'P');
    }
    else return (carta2.naipe == 'O' || carta2.naipe != 'C');
}

int mesmaCor(Carta carta1,Carta carta2){
    if(carta1.naipe == 'C' || carta1.naipe == 'O'){
        return (carta2.naipe == 'C' || carta2.naipe == 'O');
    }
    else return (carta2.naipe == 'E' || carta2.naipe == 'P');
}

int alternadosNaipes(Carta carta1,Carta carta2){
    return(carta1.naipe != carta2.naipe); // !mesmoNaipe
}

int mesmoNaipe(Carta carta1,Carta carta2){
    return (carta1.naipe == carta2.naipe);
}

int flagCrescente(Carta carta1,Carta carta2){
    return (carta1.valor-carta2.valor == (-1));
}

int flagDecrescente(Carta carta1,Carta carta2){
    return (carta1.valor-carta2.valor == 1);
}

int sempreMovivel(Carta c1,Carta c2){
    return 1;
}