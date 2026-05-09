typedef enum Boolean {falso,verdade} Boolean ;

typedef struct TipoMovimento{
    char * pilhaOrig; //Pilha de onde vêm as cartas
    char * pilhaDest; //Pilha onde vao parar as cartas
    int numFlags; //Num de Flags totais de uma dada pilha
    //array de 20 funcoes que recebem dois inteiros e devolvem um inteiro
    int (* flagsPilha[20])(int,int);
}TipoMovimento;


typedef struct PilhasStruct{
    int numPilhas;
    TipoMovimento movimentoPilhas[];
}PilhasStruct;


typedef struct JogoStruct{
    char * nomeJogo;
    int numPilhas;
    PilhasStruct pilhas;
}JogoStruct;


typedef struct WinCondition{
    char * pilhaDescrita;
    int numeroVitoriaPilha;
}WinCondition;


typedef struct OrdemFicheiro{
    int tamanho;
    char * instructions;
}OrdemFicheiro;


typedef struct game{
    OrdemFicheiro file;
    int numBaralhos;
    JogoStruct jogo;
    int numCondicoesVitoria;
    WinCondition winCon[];
}GameSettings;


//Modulo structFunctions.c
GameSettings initStructs(void);

//Modulo readFiles.c
void readFiles(GameSettings * gs);