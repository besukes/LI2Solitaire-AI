//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Typedefs e structs utilizados///////////////////////////////////////////////////
typedef int Boolean ;

typedef char * String;

typedef struct Carta{
    int valor; // 1-13
    char naipe; // C-Copas , E-Espadas , O-Ouro , P-Paus
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

typedef struct LinkedListUltimaJogada{
    int indexPilhaAnterior;
    int indexNovaPilha;
    int numCartasMovidas;
    Carta * cartasMovidas;
    struct LinkedList * prox; // Aponta para o proximo elemento da lista
} * LinkedList;

typedef struct FlagFuncArray{
    int numFlagsPegavel; //Num de Flags que indicam cartas que se podem pegar de uma dada pilha
    FlagFunctionsP flagsPegavel[10];
    int numFlagsColocavel; //Num de Flags que indicam cartas que se podem colocar numa dada pilha
    FlagFunctionsC flagsColocavel[10];
    int numRestricoes;
    FlagFunctionsR flagRestricoes[4];
    Boolean variasCartasMoviveis;
    FlagFunctionsV colocaEmPilhaVazia;
}FlagFuncArray;


typedef struct MovimentoEntrePilhas{
    long tagOrig; //Pilha de onde vem cas cartas
    long tagDest; //Pilha onde vao parar as cartas
    int numMovs; //Num de movs de pilhaOrig para pilhaDest
    //Array de um struct que guarda o numero de funcoes de um dado movimento de pilhas
    FlagFuncArray * arr;
}MovimentoEntrePilhas;

typedef struct RegrasPilha{
    Boolean todaPilhaVisivel;
    Boolean cartaTopoVisivel;
    Boolean existeMaxCartas; // MAX cartas 1
}RegrasPilha;

typedef struct PilhasStruct{
    long tag; //tag da pilha dada pela soma dos caracteres ASCII
    RegrasPilha rules;
}PilhasStruct;

typedef MovimentoEntrePilhas AutoMoves;

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
    long tagPilha;
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
MatrizJogo initMatrizJogo(void);
void inicializaAutoMoves(AutoMoves * am , int tagOrig , int tagDest);
void initFlagFuncArray(FlagFuncArray * arr);

//Modulo readFiles.c
int readFiles(GameSettings * gs,String str,MatrizJogo * mj);

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
FlagFunctionsP flagPegavelCalc(FlagFuncArray * arr , char * line);
FlagFunctionsP flagPegavelCalcAux(char * line);
FlagFunctionsR flagRestricoesCalc(char * line);