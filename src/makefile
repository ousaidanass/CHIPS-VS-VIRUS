app: main.o graphique.o ascii.o utils.o
	clang -Wall -std=c17 main.o graphique.o ascii.o utils.o -lMLV -o app

main.o: main.c
	clang -c main.c

graphique.o: graphique.c
	clang -c graphique.c

ascii.o: ascii.c
	clang -c ascii.c

utils.o: utils.c
	clang -c utils.c

clean:
	rm *.o app

