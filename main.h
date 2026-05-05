typedef enum Boolean {falso,verdade} Boolean ;

typedef struct PilhasStruct{

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