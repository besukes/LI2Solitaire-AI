
typedef enum Boolean {falso,verdade} Boolean ;

typedef char * String;

////////////////////////////////////////////////////////Structs sobre Pilhas ///////////////////////////////////////////////
typedef struct MovimentoEntrePilhas{
    int tagOrig; //Pilha de onde vem cas cartas
    int tagDest; //Pilha onde vao parar as cartas
    int numFlags; //Num de Flags totais de uma dada pilha
    //array de 19 funcoes que recebem dois inteiros e as definicoes do Jogo e devolvem um inteiro
    int (* flagsPilha[19])(GameSettings *,int,int);
    Boolean variasCartasMoviveis;
}MovimentoEntrePilhas;

typedef struct RegrasPilha{
    Boolean pilhaVisivel;
    Boolean cartaTopoVisivel;
    int numMaxCartas;
}RegrasPilha;

typedef struct PilhasStruct{
    int tag; //tag da pilha dada pela soma dos caracteres ASCII
    int indicePilha; //Pilha de onde vêm as cartas (0 ate numPilhas-1) 
    //se a pilha nao for visivel toma o valor numPilhas-1 , e altera os outros indices
    RegrasPilha rules;
}PilhasStruct;

typedef struct JogoStruct{
    String nomeJogo;
    int numPilhas;
    PilhasStruct * pilhas;
    int numCondicoes;
    MovimentoEntrePilhas * movimentoPilhas;
}JogoStruct;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct WinCondition{
    int tagPilha;
    int numeroVitoriaPilha;
}WinCondition;

typedef struct OrdemFicheiro{
    int tamanho;
    String instructions;
}OrdemFicheiro;

typedef struct game{
    OrdemFicheiro file;
    int numBaralhos;
    JogoStruct jogo;
    int numCondicoesVitoria;
    WinCondition * winCon;
}GameSettings;


//Modulo structFunctions.c
GameSettings initStructs(void);

//Modulo readFiles.c
int readFiles(GameSettings * gs,String str);

//Modulo simpleFunctions.c
int exp(int base,int expo);

//Modulo flagFunctions.c