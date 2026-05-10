#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>



void winInstruction(GameSettings * gs , char * line){
    gs->numCondicoesVitoria++;
    gs->winCon = realloc(gs->winCon,sizeof(WinCondition)*gs->numCondicoesVitoria);
    int tag = 0,num = 0,i = 0,j = 0;
    char * temp = line ;
    while(*temp !=' '){
        tag+=(*temp)*exp(2,j++); // Multiplicamos por 2^j para cada tag ser unica
        temp++;
    }
    while(*line != '#' && *line!='\n' && *line!=' '){
        num = (*line-48)*exp(10,i++);
        line++;
    }
    (gs->winCon + gs->numCondicoesVitoria)->tagPilha = tag; 
    (gs->winCon + gs->numCondicoesVitoria)->numeroVitoriaPilha = num;
}


void baralhoInstruction(GameSettings * gs , char * line){
    int baralhos=0,i=0;
    while(*line != '#' && *line!='\n' && *line!=' '){
        baralhos = (*line-48)*exp(10,i++);
    }
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

void readInstructionLine(GameSettings * gs , char * line){
    switch(*line){
        case 'M' :
            movInstruction(gs,line+4);
        break;
        case 'T' :
            tipoInstruction(gs,line+5);
        break;
        case 'I' :
            initInstruction(gs,line+5);
        break;
        case 'W' : 
            winInstruction(gs,line+4);
        break;
        case 'B' :
            baralhoInstruction(gs,line+9);
        break;
        default : 
           jogoInstruction(gs,line+5);
    }
}

void readInstructions(GameSettings * gs , struct dirent * entry , int * found){
    *found=1;
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
            readInstructions(gs,entry,&found);
        }
    }
    closedir(dir);
    if(!found) return 1;
    return 0;
}