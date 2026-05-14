#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>


void addMovInstructionAux(FlagFuncArray * arrFlags , char * line , FlagFunctionsC f){
    if(f==NULL){ //Se a flag nao for sobre colocar cartas numa pilha , vemos se e de restricao
        FlagFunctionsR f = flagRestricoesCalc(line);
        if(f==NULL){ //Se a flag nao for de restricao , so pode ser a flag V de vazia
            arrFlags->colocaEmPilhaVazia = &pilhaVazia;
        }
        else{
            arrFlags->flagRestricoes[arrFlags->numRestricoes ++] = f;
        }
    }
    else arrFlags->flagsColocavel[arrFlags->numFlagsColocavel ++ ] = f;
}

void addMovInstruction(MovimentoEntrePilhas * mov, long tagOrigem , long tagDestino , char * line){
    mov->tagOrig = tagOrigem;
    mov->tagDest = tagDestino;
    int n = ++mov->numMovs;
    mov->arr = realloc(mov->arr,sizeof(struct FlagFuncArray)*n);
    FlagFuncArray * arrFlags = (mov->arr) + n - 1;
    initFlagFuncArray(arrFlags);
    while(*line != '#' && *line!='\n' && *line!=' '){
        FlagFunctionsP f = flagPegavelCalc(arrFlags,line); //Caso a flag seja o "+" , altera o boolean do mov
        if(f==NULL && *line != '+'){ // Se a flag nao for de carta pegavel , entao vemos de que e
            addMovInstructionAux(arrFlags,line,flagColocavelCalc(line));
        }
        else arrFlags->flagsPegavel[arrFlags->numFlagsPegavel ++ ] = f;
        line++;
    }
}

void movInstruction(GameSettings * gs, char * line)
{
    long tagOrigem =0 , tagDestino = 0;
    line = criarTag(&tagOrigem , line);
    line = criarTag(&tagDestino , line);
    int n = ++gs->jogo.numCondicoes;
    //Agora line aponta para as flags
    MovimentoEntrePilhas * existeregra = comparaTags(gs->jogo.movimentoPilhas, tagOrigem, tagDestino,n);
    if(existeregra == NULL){ //Verificar se ja existem movimentos entre estas duas pilhas guardadas
        gs->jogo.movimentoPilhas = realloc(gs->jogo.movimentoPilhas,sizeof(struct MovimentoEntrePilhas)*n);
        existeregra = gs->jogo.movimentoPilhas + n - 1;
        existeregra->numMovs = 0;
    }
    addMovInstruction(existeregra,tagOrigem,tagDestino,line);
}

void autoInstruction(GameSettings * gs, char * line)
{
    long tagOrigem =0 , tagDestino = 0;
    line = criarTag(&tagOrigem , line);
    line = criarTag(&tagDestino , line);
    int n = ++gs->jogo.qntdAutoMoves;
    //Agora line aponta para as flags
    AutoMoves * existeregra = comparaTags(gs->jogo.movimentoPilhas, tagOrigem, tagDestino,n);
    if(existeregra == NULL){ //Verificar se ja existem movimentos entre estas duas pilhas guardadas
        gs->jogo.autoMoves = realloc(gs->jogo.movimentoPilhas,sizeof(struct MovimentoEntrePilhas)*n);
        existeregra = gs->jogo.autoMoves + n - 1;
        existeregra->numMovs = 0;
    }
    addMovInstruction(existeregra,tagOrigem,tagDestino,line);
}

void tipoInstruction(GameSettings * gs , char * line){
    int n = ++gs->jogo.numPilhas;
    gs->jogo.pilhas = realloc(gs->jogo.pilhas,sizeof(struct PilhasStruct)*n);
    long tag=0;
    line = criarTag(&tag,line);
    PilhasStruct * pilhaAtual = gs->jogo.pilhas + n - 1;
    pilhaAtual->tag = tag;
    calculaRulesPilha(&(pilhaAtual->rules),line);
}

void initInstruction(GameSettings * gs , char * line,MatrizJogo * mj){
    long insTag=0;
    int num = ++mj->numLinhasMatriz;
    num = criarTag(&insTag,line);
    mj->linhasMatriz = realloc(mj->linhasMatriz,sizeof(struct PilhaDeCartas)*num);
    PilhaDeCartas * p = mj->linhasMatriz + num - 1;
    p->tagPilha = insTag;
    p->cartasPilha = NULL;
    p->numCartasPilha = strToNumber(line);
}

void winInstruction(GameSettings * gs , char * line){
    gs->numCondicoesVitoria++;
    int n = gs->numCondicoesVitoria , num = 0;
    gs->winCon = realloc(gs->winCon,sizeof(struct WinCondition)*gs->numCondicoesVitoria);
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

void readInstructionLine(GameSettings * gs , char * line,MatrizJogo * mj){
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
            initInstruction(gs,line+5,mj);
        default: // Apenas para reduzir instrucoes
            readInstructionLineAux(gs,line);
    }
}

void readInstructions(GameSettings * gs , struct dirent * entry,MatrizJogo * mj){
    char path[100];
    snprintf(path,sizeof(path),"paciencias/%s",entry->d_name);
    FILE * file = fopen(path,"r");
    char line[50];
    while(fgets(line,sizeof(line),file)){
        readInstructionLine(gs,line,mj);
    }
    fclose(file);
}

int readNewGame(GameSettings * gs , String str , MatrizJogo * mj){
    struct dirent * entry;
    DIR * dir = opendir("paciencias");
    int found=0;
    while((entry = readdir(dir)) != NULL && !found){
        if(strcmp(entry->d_name,str) == 0){
            found=1;
            readInstructions(gs,entry,mj);
        }
    }
    closedir(dir);
    if(!found) return 1;
    return 0;
}

int readExistingGame(GameSettings * gs , String str , MatrizJogo * mj){
    
}

int readFiles(GameSettings * gs,MatrizJogo * mj){
    int op;
    char * str;
    printf("Olá jogador.Para continuar insira o número da opção que melhor descreve oque quer fazer :\n "
            "1- LOAD NEW GAME\n"
            "2- START NEW GAME\n"
            "DEFAULT - START NEW GAME\n");
    scanf("%d",&op);
    printf("Insira o nome do ficheiro do qual pretende fazer uso para jogar : \n");
    scanf("%s",&str);
    switch(op){
        case 1 :
            return readExistingGame(gs,str,mj);
        break;
        default : 
            return readNewGame(gs,str,mj);
        break;
    }
}
