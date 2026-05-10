//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Typedefs e structs utilizados///////////////////////////////////////////////////
typedef int Boolean ;

typedef char * String;


typedef struct MovimentoEntrePilhas{
    int tagOrig; //Pilha de onde vem cas cartas
    int tagDest; //Pilha onde vao parar as cartas
    int numFlags; //Num de Flags totais de uma dada pilha
    //array de 19 funcoes que recebem dois inteiros e as definicoes do Jogo e devolvem um inteiro
    int (* flagsPilha[19])(GameSettings *,int,int);
    Boolean variasCartasMoviveis;
}MovimentoEntrePilhas;

typedef struct RegrasPilha{
    Boolean todaPilhaVisivel;
    Boolean cartaTopoVisivel;
    Boolean existeMaxCartas; // MAX cartas 1
}RegrasPilha;

typedef struct PilhasStruct{
    int tag; //tag da pilha dada pela soma dos caracteres ASCII
    int indicePilha; //Pilha de onde vêm as cartas (0 ate numPilhas-1)
    int numCartasInicial; // Num de cartas com que a pilha inicia
    RegrasPilha rules;
}PilhasStruct;

typedef struct AutoMoves{
    int tagOrig;
    int tagDest;
    Boolean variasCartasMoviveis;
    int numFlags;
    int (* flagsMoves[19])(GameSettings *,int,int);
}AutoMoves;

typedef struct JogoStruct{
    String nomeJogo;
    int numPilhas;
    PilhasStruct * pilhas;
    int numCondicoes;
    MovimentoEntrePilhas * movimentoPilhas;
    int qntdAutoMoves;
    AutoMoves * autoMoves;
}JogoStruct;


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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Definições de algumas funções de vários módulos/////////////////////////////////////////

//Modulo structFunctions.c
GameSettings initStructs(void);

//Modulo readFiles.c
int readFiles(GameSettings * gs,String str);

//Modulo simpleFunctions.c
int exp(int base,int expo);
char * criarTag(int * tag,char * line);
int strToNumber(char * line);
void calculaRulesPilha(RegrasPilha * rp , char * line);
void calculaAutoFlags(AutoMoves * am , char * line);

//Modulo flagFunctions.c