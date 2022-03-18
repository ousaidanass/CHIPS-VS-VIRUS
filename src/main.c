#include "graphique.h"
#include "ascii.h"


int main(int argc, char *argv[]) {
    if (argv[2] && argv[2][1] == 'a') ascii(argv[1]);
    else if (argv[2] && argv[2][1] == 'g') graphique(argv[1]);
    else {
        printf("Pour éxécuter le programme: \n");
        printf("./app nomFichier.txt modeJeu [-g ou -a]\n");
        exit(1);
    }
    return 0;
}