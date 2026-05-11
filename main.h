//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Typedefs e structs utilizados///////////////////////////////////////////////////
typedef int Boolean ;

typedef char * String;

typedef struct Carta{
    int valor; // 1-13
    char naipe; // C-Copas , E-Espadas , O-Ouro , P-Paus
}Carta;

typedef int (*FlagFunctionsP)(Carta,Carta);

typedef int (*FlagFunctionsC) (Carta,Carta);



typedef struct FlagFuncArray{
    int numFlagsPegavel; //Num de Flags que indicam cartas que se podem pegar de uma dada pilha
    FlagFunctionsP flagsPegavel[10];
    int numFlagsColocavel; //Num de Flags que indicam cartas que se podem colocar numa dada pilha
    FlagFunctionsC flagsColocavel[10];
}FlagFuncArray;


typedef struct MovimentoEntrePilhas{
    long tagOrig; //Pilha de onde vem cas cartas
    long tagDest; //Pilha onde vao parar as cartas
    int numMovs; //Num de movs de pilhaOrig para pilhaDest
    //Array de um struct que guarda o numero de funcoes de um dado movimento de pilhas
    FlagFuncArray * arr;
    Boolean variasCartasMoviveis;
}MovimentoEntrePilhas;

typedef struct RegrasPilha{
    Boolean todaPilhaVisivel;
    Boolean cartaTopoVisivel;
    Boolean existeMaxCartas; // MAX cartas 1
}RegrasPilha;

typedef struct PilhasStruct{
    long tag; //tag da pilha dada pela soma dos caracteres ASCII
    int indicePilha; //Pilha de onde vêm as cartas (0 ate numPilhas-1)
    int numCartasInicial; // Num de cartas com que a pilha inicia
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

//Modulo readFiles.c
int readFiles(GameSettings * gs,String str);

//Modulo simpleFunctions.c
int exp(int base,int expo);
char * criarTag(long * tag,char * line);
int strToNumber(char * line);
void calculaRulesPilha(RegrasPilha * rp , char * line);
void calculaAutoFlags(AutoMoves * am , char * line);

//Modulo flagFunctions.c