#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>




int initEVerificaTipoFlag(MovimentoEntrePilhas * mov , char * line){
    char str[8] = "*[]mxcd" , str2[7]= "<>MXCD" , str3[5] = "aAkK";
    if(pertenceString(*line,str)){
        mov->numMovsP++;
        initArrP(mov);
        return 1;
    }
    else{
        if(pertenceString(*line,str2)){
            mov->numMovsC++;
            initArrC(mov);
            return 2;
        }
        else if(pertenceString(*line,str3)){
            mov->numMovsC++;
            initArrC(mov);
            return 3;
        }
        else return 4;
    }
}


void addMovInstruction(MovimentoEntrePilhas * mov,long tagDestino , char * line){
    while(*line != '#' && *line!='\n' && *line!=' '){
        int u = initEVerificaTipoFlag(mov,line);
        int n1= mov->numMovsC , n2 = mov->numMovsP;
        if(u==1) (mov->arrP + n1 - 1)->flagsPegavel[mov->arrP->numFlagsPegavel ++] = flagPegavelCalc(line);
        else if(u==2)  (mov->arrC + n2 - 1)->flagsColocavel[mov->arrC->numFlagsColocavel ++] = flagColocavelCalc(line);
        else if(u==3) (mov->arrC + n2 - 1)->flagRestricoes[mov->arrC->numRestricoes ++] = flagRestricoesCalc(line);
        else if(u==4) mov->colocaEmPilhaVazia = &pilhaVazia;
        line++;
    }
}

void movInstruction(GameSettings * gs, char * line)
{
    long tagOrigem = 0 , tagDestino = 0;
    line = criarTag(&tagOrigem , line);
    line = criarTag(&tagDestino , line);
    int n = ++gs->jogo.numCondicoesMov;
    //Agora line aponta para as flags
    MovimentoEntrePilhas * existeregra = comparaTags(gs->jogo.movimentoPilhas, tagOrigem, tagDestino,n);
    if(existeregra == NULL){ //Verificar se ja existem movimentos entre estas duas pilhas guardadas
        gs->jogo.movimentoPilhas = realloc(gs->jogo.movimentoPilhas,sizeof(struct MovimentoEntrePilhas)*n);
        existeregra = gs->jogo.movimentoPilhas + n - 1;
        existeregra->numMovsC = 0;
        existeregra->numMovsP=0;
        existeregra->tagOrig = tagOrigem;
        existeregra->tagDest = tagDestino;
        existeregra->colocaEmPilhaVazia = NULL;
    }
    addMovInstruction(existeregra,tagDestino,line);
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
        existeregra->numMovsC = 0;
        existeregra->numMovsP=0;
        existeregra->tagOrig = tagOrigem;
        existeregra->tagDest = tagDestino;
        existeregra->colocaEmPilhaVazia = NULL;
    }
    addMovInstruction(existeregra,tagDestino,line);
}

void tipoInstruction(GameSettings * gs , char * line){
    int n = ++gs->jogo.numPilhas;
    gs->jogo.pilhas = realloc(gs->jogo.pilhas,sizeof(struct RegrasPilha)*n);
    long tag=0;
    line = criarTag(&tag,line);
    RegrasPilha * pilhaAtual = gs->jogo.pilhas + n - 1;
    pilhaAtual->tag = tag;
    calculaRulesPilha(&pilhaAtual,line);
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

int readGameInstructions(GameSettings * gs , String str , MatrizJogo * mj){
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
    return (!found);
}

void initMatriz(MatrizJogo * mj , int index , char * line){
    
}

int readGameFiles(GameSettings * gs , MatrizJogo * mj , struct dirent * entry){
    int i=0 , found=0;
    char path[100];
    snprintf(path,sizeof(path),"paciencias/%s",entry->d_name);
    FILE * file = fopen(path,"r");
    char line[50] = fgets(line,sizeof(line),file), nomeJogo[50];
    sscanf("%s",nomeJogo,line);
    found = readGameInstructions(gs,nomeJogo,mj);
    while(fgets(line,sizeof(line),file)){
        initMatriz(mj,i++,line);
    }
    fclose(file);
    return (!found);
}


int readExistingGame(GameSettings * gs , String str , MatrizJogo * mj){
    struct dirent * entry;
    DIR * dir = opendir("paciencias");
    int foundDir = 0 , foundFile;
    while((entry = readdir(dir)) != NULL && !foundDir){
        if(strcmp(entry->d_name,str) == 0){
            foundDir = 1 ;
            foundFile = readGameFiles(gs,mj,entry);
        }
    }
    closedir(dir);
    if(foundDir && foundFile) return 0;
    return 1;
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
            int ret = readGameInstructions(gs,str,mj);
            randomizaJogo(gs,mj);
            return ret;
        break;
    }
}
