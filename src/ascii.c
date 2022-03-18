#include "utils.h"
#include "ascii.h"

void affichePlateauLigne(Game *jeu, int lig) {
    int *typechips = (int *)calloc(NBPOSITION, sizeof(int));
    int *typevirus = (int *)calloc(NBPOSITION, sizeof(int));
    Chips *tmp = jeu->chips, *chips;
    Virus *tmpVir = jeu->virus, *virus;
    char lettreChips, lettreVirus;
    int lifeVir, lifeChi;
    while(tmp) {
        if(tmp->position != 0 && tmp->line == lig) {
            typechips[tmp->position - 1] = tmp->type;
        }
        tmp = tmp->next;
    }
    while(tmpVir) {
        if(tmpVir->position != -20 && tmpVir->position != 0 && tmpVir->line == lig) {
            typevirus[tmpVir->position - 1] = tmpVir->type;
        }
        tmpVir = tmpVir->next;
    }
    // cas ou le nombre contient 2 chiffres en mets un seul espace aprés, sinon en mets 2 escpaces
    // pour que le plateau soit bien organisé
    if(lig > 9) printf("%d ", lig);
    else printf("%d|  ", lig);

    for(int j = 0; j < NBPOSITION; ++j) {
        if(typechips[j] == 0 && typevirus[j] == 0) printf(".   ");
        else if(typechips[j] != 0 && typevirus[j] != 0) {
            virus = virusMemeCase(jeu, lig, j+1);
            chips = chipsMemeCase(jeu, lig, j+1);
            virusNumVersLettre(typevirus[j], &lettreVirus, 'L', &lifeVir);
            tourelleNumVersLettre(typechips[j], &lettreChips, 'L', &lifeChi);
            printf("%c%d%d%c ", lettreChips, chips->life, virus->life, lettreVirus);
        } else if(typevirus[j] != 0 && typechips[j] == 0) {
            virus = virusMemeCase(jeu, lig, j+1);
            virusNumVersLettre(typevirus[j], &lettreVirus, 'L', &lifeVir);
            printf("%d%c  ", virus->life, lettreVirus);
        } else if(typevirus[j] == 0 && typechips[j] != 0){
            chips = chipsMemeCase(jeu, lig, j+1);
            tourelleNumVersLettre(typechips[j], &lettreChips, 'L', &lifeChi); // les 2 dernier argument juste pour que la fonction ne donne pas l'erreur de manque d'argument
            printf("%c%d  ", lettreChips, chips->life); //Afficher la vie aussi
        }
    }
    printf("\n\n");
    free(typechips);
    free(typevirus);
}


void affichePlateauAscii(Game *jeu) {
    printf("Game turn°: %d.\n", jeu->turn);
    for(int i = 1; i <= NBLIGNE; ++i) {
        affichePlateauLigne(jeu, i);
    }
}

void choixTourelle(Game *jeu) {
    char choix;
    int lig, col, res = 0, r = 0;
    Chips *chips;
    while(res != 2) {
        affichePlateauAscii(jeu);
        do {
            printf("Votre solde est de: %d\n", jeu->money);
            printf("What chips do you want to deploy ?\nA : ALU\nR : RAM\nP : PMMU\nX : Patch\nF : firewall\nQ : no more\nYour choice ?\n");
            scanf(" %c", &choix);
        } while((res = prixsuffisant(jeu, choix)) == 0);
        if(res != 2) {
            do {
                printf("Choisir la Position [N°Ligne] [N°Colone]");
                r = scanf("%d %d", &lig, &col);
                if(r != 2) viderBuffer();
            } while (positionValide(jeu, lig, col) == 0);
            chips = alloueTourelle(choix);
            chips->line = lig;
            chips->position = col;
            insereChips(jeu, chips);
        }
    }
}

void affichageJeuTerminal(Game *jeu, char*nmFic){
    char choix;
    int debut = 0;
    while(!debut){
        do{
            printf("Vous voulez voir la vague ou choisir vos tourelles ou commencer le jeu (V) pour vague (T) pour tourelles (C) pour commencer: ");
            scanf(" %c", &choix);
            if(tolower(choix) == 'v'){
                afficheVague(nmFic);   
            } else if(tolower(choix) == 't'){
                choixTourelle(jeu);
            } else if(tolower(choix) == 'c'){
                debut = 1;
            }
        } while(tolower(choix) == 'v' || tolower(choix) == 't');
    }
}

void ascii(char *nomFic) { 
    Game jeu;
    int res;
    initialiserJeu(&jeu, nomFic);
    affichageJeuTerminal(&jeu, nomFic);
    printf("Partie commencé.\n");
    while(!(res = finPartie(&jeu))) {
        jeu.turn += 1;
        updateInfoVirus(&jeu);
        updateInfoChips(&jeu, 'A');
        supprimeVirusMort(&jeu, 'A');
        supprimeChipsMort(&jeu, 'A');
        moveVirus(&jeu);
        affichePlateauAscii(&jeu);
        MLV_wait_seconds(2);
    }
    if(res == 2) printf("Partie Gagné.\n");
    else if(res == 1) printf("Partie Perdu.\n");
    libereListeChips(&jeu);
    libereListeVirus(&jeu);
}
