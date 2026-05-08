typedef enum Boolean {falso,verdade} Boolean ;

typedef struct TipoMovimento{
    char * pilhaOrig;
    char * pilhaDest;
    int * (* flagsPilha);
    int numFlags;
}TipoMovimento;

typedef struct PilhasStruct{
    char * nomePilha;
    int numPilhas;
    int * pilhas;
    int * numCartasPilha;
    TipoMovimento * movimentoPilha;
}PilhasStruct;

typedef struct JogoStruct{
    char * nomeJogo;
    int numPilhas;
    PilhasStruct * pilhas;
}JogoStruct;

typedef struct WinCondition{

}WinCondition;

typedef struct OrdemFicheiro{
    int tamanho;
    char * instructions;
}OrdemFicheiro;


typedef struct game{
    int numBaralhos;
    OrdemFicheiro file;
    JogoStruct jogo;
    WinCondition winCon;
}GameSettings;