#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>


void addMovInstruction(MovimentoEntrePilhas * mov, long tagOrigem , long tagDestino , char * line){
    mov->tagOrig = tagOrigem;
    mov->tagDest = tagDestino;
    int n = ++mov->numMovs;
    mov->arr = realloc(mov->arr,sizeof(FlagFuncArray)*n);
    FlagFuncArray * movAtual = (mov->arr) + n - 1;
    movAtual->numFlagsPegavel = 0;
    movAtual->numFlagsColocavel = 0;
    mov->variasCartasMoviveis=0;
    while(*line != '#' && *line!='\n' && *line!=' '){
        FlagFunctionsP f = flagPegavelCalc(mov,line); //Caso a flag seja o "+" , altera o boolean do mov
        if(f==NULL && *line != '+'){
            movAtual->flagsColocavel[movAtual->numFlagsColocavel ++ ] = flagColocavelCalc(mov,line);
        }
        else movAtual->flagsPegavel[movAtual->numFlagsPegavel ++ ] = f;
        line++;
    }
}

void movInstruction(GameSettings * gs, char * line)
{
    long tagOrigem =0 , tagDestino = 0;
    line = criarTag(&tagOrigem , line);
    line = criarTag(&tagDestino , line);
    //Agora line aponta para as flags
    MovimentoEntrePilhas * existeregra = comparaTags(gs->jogo.movimentoPilhas, tagOrigem, tagDestino,gs->jogo.numCondicoes);
    int n = ++gs->jogo.numCondicoes;
    if(existeregra == NULL){ //Verificar se ja existem movimentos entre estas duas pilhas guardadas
        gs->jogo.movimentoPilhas = realloc(gs->jogo.movimentoPilhas,sizeof(MovimentoEntrePilhas)*n);
        gs->jogo.movimentoPilhas->numMovs = 0;
        addMovInstruction(gs->jogo.movimentoPilhas + n - 1,tagOrigem,tagDestino,line);
    }
    else addMovInstruction(existeregra,tagOrigem,tagDestino,line);
}

void autoMovesCalc(AutoMoves * am , char * line){
    
}

void autoInstruction(GameSettings * gs , char * line){
    int n = ++(gs->jogo.qntdAutoMoves);
    long tagOrig=0,tagDest=0;
    line=criarTag(&tagOrig,line);
    line=criarTag(&tagDest,line);
    AutoMoves * am = comparaTags(am,tagOrig,tagDest);
    if(am==NULL){
        gs->jogo.autoMoves = realloc(gs->jogo.autoMoves,sizeof(AutoMoves)*n);
        am = gs->jogo.autoMoves + n -1;
        inicializaAutoMoves(am,tagOrig,tagDest);
    }
    else{
        am->numMovs++;
        am->variasCartasMoviveis=0;
    }
    autoMovesCalc(am,line); // NECESSITO FAZER ESTA FUNCAO AINDA NAO ESTA FEITA
}

void tipoInstruction(GameSettings * gs , char * line){
    int n = ++gs->jogo.numPilhas;
    gs->jogo.pilhas = realloc(gs->jogo.pilhas,sizeof(PilhasStruct)*n);
    long tag=0;
    line = criarTag(&tag,line);
    PilhasStruct * pilhaAtual = gs->jogo.pilhas + n - 1;
    pilhaAtual->tag = tag;
    calculaRulesPilha(&(pilhaAtual->rules),line);
    pilhaAtual->indicePilha = n - 1;
    pilhaAtual->numCartasInicial=0;
}

void initInstruction(GameSettings * gs , char * line){
    long insTag=0;
    int counter=0;
    line = criarTag(&insTag,line);
    PilhasStruct * p = gs->jogo.pilhas;
    while(gs->jogo.numPilhas > counter && p->tag != insTag){
        counter++;
        p++;
    }
    if(counter<gs->jogo.numPilhas) p->numCartasInicial = strToNumber(line);
}

void winInstruction(GameSettings * gs , char * line){
    gs->numCondicoesVitoria++;
    int n = gs->numCondicoesVitoria , num = 0;
    gs->winCon = realloc(gs->winCon,sizeof(WinCondition)*gs->numCondicoesVitoria);
    long tag = 0;
    line = criarTag(&tag,line);
    num = strToNumber(line);
    WinCondition * wn = gs->winCon ;
    (wn + n - 1)->tagPilha = tag; 
    (wn + n - 1)->numeroVitoriaPilha = num;
}


void baralhoInstruction(GameSettings * gs , char * line){
    int baralhos=strToNumber(line);
    gs->numBaralhos=baralhos;
}

void jogoInstruction(GameSettings * gs,char * line){
    int i;
    char * temp = line;
    //Para verificar o tamanho do nome do jogo
    for(i=0;*temp != '#' && *temp!='\n' && *temp!=' ';i++,temp++);
    gs->jogo.nomeJogo = malloc(sizeof(char)*i + 1);
    char * nome = gs->jogo.nomeJogo;
    for(;*line != '#' && *line!='\n' && *line!=' ';i++,nome++,line++){
        *nome=*line;
    }
    *nome = '\0';
}


void readInstructionLineAux(GameSettings * gs, char * line){
    switch(*line){
        case 'W' : 
            winInstruction(gs,line+4);
        break;
        case 'B' :
            baralhoInstruction(gs,line+9);
        break;
        case 'J' :
            jogoInstruction(gs,line+5);
        break;
        default: // Se a linha for vazia nao faz nada (i.e, comeca com espaco)
        break;
    }
}

void readInstructionLine(GameSettings * gs , char * line){
    switch(*line){
        case 'M' :
            movInstruction(gs,line+4);
        break;
        case 'A' :
            autoInstruction(gs,line+5);
        break;
        case 'T' :
            tipoInstruction(gs,line+5);
        break;
        case 'I' :
            initInstruction(gs,line+5);
        default: // Apenas para reduzir instrucoes
            readInstructionLineAux(gs,line);
    }
}

void readInstructions(GameSettings * gs , struct dirent * entry){
    char path[100];
    snprintf(path,sizeof(path),"paciencias/%s",entry->d_name);
    FILE * file = fopen(path,"r");
    char line[50];
    while(fgets(line,sizeof(line),file)){
        readInstructionLine(gs,line);
    }
    fclose(file);
}

int readFiles(GameSettings * gs,String str){
    struct dirent * entry;
    DIR * dir = opendir("paciencias");
    int found=0;
    while((entry = readdir(dir)) != NULL && !found){
        if(strcmp(entry->d_name,str) == 0){
            found=1;
            readInstructions(gs,entry);
        }
    }
    closedir(dir);
    if(!found) return 1;
    return 0;
}
