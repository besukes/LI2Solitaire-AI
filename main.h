//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Typedefs e structs utilizados///////////////////////////////////////////////////
typedef int Boolean ;

typedef enum {quit,undo,save,invalid,valid,GameWon} PossiveisJogadas;

typedef char * String;

typedef char Naipe;

typedef struct Carta{
    int valor; // 1-13
    Naipe naipe; // C-Paus , D-Ouros , H-Copas , S-Espadas
}Carta;

typedef struct PilhaDeCartas{
    int tagPilha;
    int numCartasPilha;
    struct Carta * cartasPilha;
}PilhaDeCartas;


typedef struct MatrizJogo{
    int numLinhasMatriz;
    struct PilhaDeCartas * linhasMatriz;
} MatrizJogo;


typedef int (*FlagFunctionsP)(Carta,Carta);

typedef int (*FlagFunctionsC) (Carta,Carta);

typedef int (*FlagFunctionsR) (int,MatrizJogo);

typedef int (*FlagFunctionsV) (int,MatrizJogo);

typedef struct LastMoveLL{
    int indexPilhaAnterior;
    int indexNovaPilha;
    int numCartasMovidas;
    Carta * cartasMovidas;
    struct LastMoveLL * prox; // Aponta para o proximo elemento da lista
} * LastMoveLL;


typedef struct FlagFuncArrayP{
    int numFlagsPegavel; //Num de Flags que indicam cartas que se podem pegar de uma dada pilha
    FlagFunctionsP flagsPegavel[7];
    Boolean variasCartasMoviveis;
}ArrayFlagsPegar;

typedef struct FlagFuncArrayC{
    int numFlagsColocavel; //Num de Flags que indicam cartas que se podem colocar numa dada pilha
    FlagFunctionsC flagsColocavel[7];
    int numRestricoes;
    FlagFunctionsR flagRestricoes[4];
}ArrayFlagsColocar;


typedef struct MovimentoEntrePilhas{
    long tagOrig; //Pilha de onde vem cas cartas
    long tagDest; //Pilha onde vao parar as cartas
    int numMovsP; //Num de movs que condicionam pegar cartas
    //Array de um struct que guarda as condicoes de pegar Cartas de uma dada pilha
    ArrayFlagsPegar * arrP;
    int numMovsC; //Num de movs que condicionam a colocação de cartas
    //Array de um struct que guarda o numero de funcoes de um dado movimento de pilhas
    ArrayFlagsColocar * arrC;
    FlagFunctionsV colocaEmPilhaVazia;
}MovimentoEntrePilhas;


typedef struct RegrasPilha{
    long tag; //tag da pilha dada pela soma dos caracteres ASCII
    Boolean todaPilhaVisivel;
    Boolean cartaTopoVisivel;
    Boolean existeMaxCartas; // MAX cartas 1
}RegrasPilha;

typedef MovimentoEntrePilhas AutoMoves;

typedef struct JogoStruct{
    String nomeJogo;
    int numPilhas;
    RegrasPilha * pilhas;
    int numCondicoesMov;
    MovimentoEntrePilhas * movimentoPilhas;
    int qntdAutoMoves;
    AutoMoves * autoMoves;
}JogoStruct;


typedef struct WinCondition{
    long tagPilha;
    int numeroVitoriaPilha;
}WinCondition;

typedef struct OrdemFicheiro{
    int tamanhoMemoria;
    int tamanhoReal;
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
MatrizJogo initMatrizJogo(void);
void inicializaAutoMoves(AutoMoves * am , int tagOrig , int tagDest);
void initFlagFuncArrayC(ArrayFlagsColocar * arr1);
void initFlagFuncArrayP(ArrayFlagsPegar * arr2);

//Modulo readFiles.c
int readFiles(GameSettings * gs,MatrizJogo * mj);

//Modulo simpleFunctions.c
int exp(int base,int expo);
char * criarTag(long * tag,char * line);
int strToNumber(char * line);
void calculaRulesPilha(RegrasPilha * rp , char * line);
MovimentoEntrePilhas * comparaTags (MovimentoEntrePilhas * mp ,int tagOrig , int tagDest , int n);

//Modulo flagFunctions.c
int pilhaVazia(int linha,MatrizJogo * m);
FlagFunctionsC flagColocavelCalc(char * line);
FlagFunctionsP flagColocavelCalcAux(char * line);
FlagFunctionsP flagPegavelCalc(char * line);
FlagFunctionsP flagPegavelCalcAux(char * line);
FlagFunctionsR flagRestricoesCalc(char * line);

//Modulo randomizeCards.c
void randomizaJogo(GameSettings * gs , MatrizJogo * mj);