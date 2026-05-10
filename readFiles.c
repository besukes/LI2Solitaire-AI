#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>


void initInstruction(GameSettings * gs , char * line){
    int insTag=0,j=0;
    line = criarTag(&insTag,line);
    int counter=0;
    PilhasStruct * p = gs->jogo.pilhas;
    while(gs->jogo.numPilhas > counter && p->tag != insTag){
        counter++;
        p++;
    }
    if(counter<gs->jogo.numPilhas) p->numCartasInicial = strToNumber(line);
}

void winInstruction(GameSettings * gs , char * line){
    gs->numCondicoesVitoria++;
    gs->winCon = realloc(gs->winCon,sizeof(WinCondition)*gs->numCondicoesVitoria);
    int tag = 0,num=0;
    line = criarTag(&tag,line);
    num = strToNumber(line);
    (gs->winCon + gs->numCondicoesVitoria - 1)->tagPilha = tag; 
    (gs->winCon + gs->numCondicoesVitoria - 1)->numeroVitoriaPilha = num;
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