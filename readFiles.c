#include "main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>



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