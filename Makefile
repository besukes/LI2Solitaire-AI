userInterface.o:userInterface.c
	gcc -Wall -ggdb -c userInterface.c
structFunctions.o:structFunctions.c
	gcc -Wall -ggdb -c structFunctions.c
simpleFunctions.o:simpleFunctions.c
	gcc -Wall -ggdb -c simpleFunctions.c
readFiles.o:readFiles.c
	gcc -Wall -ggdb -c readFiles.c
randomizeCards.o:randomizeCards.c
	gcc -Wall -ggdb -c randomizeCards.c
gameplayHandle.o:gameplayHandle.c
	gcc -Wall -ggdb -c gameplayHandle.c
freeMemory.o:freeMemory.c
	gcc -Wall -ggdb -c freeMemory.c
flagFunctions.o:flagFunctions.c
	gcc -Wall -ggdb -c flagFunctions.c
undoMove.o:undoMove.c
	gcc -Wall -ggdb -c undoMove.c
main.o:main.c
	gcc -Wall -ggdb -c main.c
fase3:main.o flagFunctions.o freeMemory.o gameplayHandle.o randomizeCards.o readFiles.o simpleFunctions.o structFunctions.o userInterface.o undoMove.o
	gcc -ggdb $^ -o $@
clean:
	rm fase3 main.o flagFunctions.o freeMemory.o gameplayHandle.o randomizeCards.o readFiles.o simpleFunctions.o structFunctions.o userInterface.o undoMove.o