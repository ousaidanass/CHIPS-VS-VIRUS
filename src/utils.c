#include "utils.h"
#include "graphique.h"

void viderBuffer(){
    int c; 
    while((c = getchar()) != '\n');
}

int tourelleNumVersLettre(int num, char *lettre, char info, int *res) {
    switch(num) {
        case 1:
            *lettre = 'A';
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 100;
            else if(info == 'D') *res = 1;
            return 1;
        case 2:
            *lettre = 'R';
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 400;
            else if(info == 'D') *res = 2;
            return 1;
        case 3:
            *lettre = 'P';
            if(info == 'L') *res = 2;
            else if(info == 'P') *res = 200;
            else if(info == 'D') *res = 1;
            return 1;
        case 4:
            *lettre = 'X';
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 150;
            else if(info == 'D') *res = 1;
            return 1;
        case 5:
            *lettre = 'F';
            if(info == 'L') *res = 5;
            else if(info == 'P') *res = 200;
            else if(info == 'D') *res = 0;
            return 1;
        default:
            return 0;
        
    }
}

int tourelleLettreVersNum(char choix, int *num, char info, int *res) { 
    switch(choix) {
        case 'A': 
            *num = 1;
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 100;
            else if(info == 'D') *res = 1;
            return 1;
        case 'R': // damage sur sa ligne et les deux lignes voisines
            *num = 2;
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 400;
            else if(info == 'D') *res = 2;
            return 1;
        case 'P': // explosant au contact en tuant le premier gros villain
            *num = 3;
            if(info == 'L') *res = 1;
            else if(info == 'P') *res = 200;
            else if(info == 'D') *res = 1;
            return 1;
        case 'X': // ralenti les virus
            *num = 4;
            if(info == 'L') *res = 3;
            else if(info == 'P') *res = 150;
            else if(info == 'D') *res = 1;
            return 1;
        case 'F':
            *num = 5;
            if(info == 'L') *res = 5;
            else if(info == 'P') *res = 200;
            else if(info == 'D') *res = 0;
            return 1;
        default:
            return 0;
    }
}
int virusNumVersLettre(int num, char *lettre, char info, int *res) {
    switch(num) {
        case 1:
            *lettre = 'E';
            if(info == 'L') *res = 3;
            else if(info == 'S') *res = 2;
            return 1;
        case 2:
            *lettre = 'D'; //accelere le  premier de sa ligne ainsi les deux premiers des autres lignes voisines
            if(info == 'L') *res = 3;
            else if(info == 'S') *res = 2;
            return 1;
        case 3:
            *lettre = 'S';
            if(info == 'L') *res = 6;
            else if(info == 'S') *res = 1;
            return 1;
        case 4:
            *lettre = 'M';
            if(info == 'L') *res = 3;
            else if(info == 'S') *res = 4;
            return 1;
        case 5:
            *lettre = 'B';
            if(info == 'L') *res = 2; //soigne devant et derriere lui
            else if(info == 'S') *res = 1;
            return 1;
        default:
            return 0;
    }
}

int virusLettreVersNum(char choix, int *num, char info, int *res) {
    switch(choix) {
        case 'E':
            *num = 1;
            if(info == 'L') *res = 2;
            else if(info == 'S') *res = 2;
            return 1;
        case 'D':
            *num = 2;
            if(info == 'L') *res = 2;
            else if(info == 'S') *res = 2;
            return 1;
        case 'S':
            *num = 3;
            if(info == 'L') *res = 6;
            else if(info == 'S') *res = 2;
            return 1;
        case 'M':
            *num = 4;
            if(info == 'L') *res = 3;
            else if(info == 'S') *res = 4;
            return 1;
        case 'B':
            *num = 5;
            if(info == 'L') *res = 2;
            else if(info == 'S') *res = 1;
            return 1;
        default:
            return 0;
    }
}

Chips *chipsMemeCase(Game *jeu, int lig, int col) {
    Chips *tmp = jeu->chips;
    while(tmp) {
        if(tmp->line == lig && tmp->position == col) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

Virus *virusMemeCase(Game *jeu, int lig, int col) {
    Virus *tmp = jeu->virus;
    while(tmp) {
        if(tmp->line == lig && tmp->position == col) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

Virus *alloueVirus(int tour, int ligne, char type) {
    Virus *virus = (Virus *)malloc(sizeof(Virus));
    if(!virus) {
        printf("Problème d'Allocation du virus !!!\n");
        exit(1);
    }
    if(virusLettreVersNum(type, &(virus->type), 'S', &(virus->speed))) {
        if(virusLettreVersNum(type, &(virus->type), 'L', &(virus->life))) {
            virus->turn = tour;
            virus->line = ligne;
            virus->position = -20;
            virus->next = NULL;
            virus->next_line = NULL;
            virus->prev_line = NULL;
            return virus;
        } else {
            printf("Erreur de choix de Type de Tourelle !!!\n");
            exit(1);
        }
    } else {
        printf("Erreur de choix de Type de Tourelle !!!\n");
        exit(1);
    }
}

void insereVirus(Game *jeu, Virus *virus, Virus **tabVirusLigne) {
    if(jeu->virus == NULL) {
        jeu->virus = virus;
    } else {
        if(tabVirusLigne[virus->line] != NULL) {
            virus->next = jeu->virus;
            jeu->virus = virus;
            virus->next_line = tabVirusLigne[virus->line];
            virus->next_line->prev_line = virus;
        } else {
            virus->next = jeu->virus;
            jeu->virus = virus;
        }
    }
    tabVirusLigne[virus->line] = virus;
}

void initialiseVirus(Game *jeu, FILE *fic) {
    Virus *virus;
    Virus **tabVirusLigne = (Virus **)malloc(NBLIGNE * sizeof(Virus));
    if(tabVirusLigne ==  NULL){
        printf("Problème d'allocation!\n");
        exit(1);
    }
    jeu->virus = NULL;
    for(int i = 0; i < NBLIGNE; ++i)
        tabVirusLigne[i] = NULL;
    char type;
    int tour, ligne;
    while(fscanf(fic, "%d %d %c", &tour, &ligne, &type) != EOF) {
        virus = alloueVirus(tour, ligne, type);
        insereVirus(jeu, virus, tabVirusLigne);
    }
    rewind(fic);
    free(tabVirusLigne);
}

void afficheVagueLigne(FILE *fic, int i) {
    int money, tour, ligne;
    char type;
    char *virus = (char *)calloc(MAXTOURVAGUE, sizeof(char));
    if(!virus) {
        printf("Problème d'allocation du tableau des Vagues de Virus !!!\n");
        exit(1);
    }
    fscanf(fic, "%d", &money);
    while(fscanf(fic, "%d %d %c", &tour, &ligne, &type) != EOF) {
        if(i == ligne) {
            virus[tour - 1] = type;
        }
    }
    printf("%d| ", i);
    for(int i = 0; i < MAXTOURVAGUE; ++i) {
        if((int)virus[i] == 0) printf("  ");
        else printf("%c ", virus[i]);
    }
    printf("\n");
    rewind(fic);
    free(virus);
}

void afficheVague(char *nmFic) {
    printf("Here is the wave of problems approaching...\n");
    FILE *fic = fopen(nmFic, "r");
    for(int i = 1; i <= NBLIGNE; ++i) {
        afficheVagueLigne(fic, i);
    }
    fclose(fic);
    rewind(fic);
}

void initialiserJeu(Game *jeu, char *nmFic) {
    FILE *fic = fopen(nmFic, "r");
    int money;
    if(!fic) {
        printf("Erreur de lecture du fichier !!!\n");
        exit(1);
    }
    fscanf(fic, "%d", &money);
    jeu->money = money;
    initialiseVirus(jeu, fic);
    jeu->chips = NULL;
    jeu->turn = 0;
    rewind(fic);
    fclose(fic);
}


Chips *alloueTourelle(char choix) {
    Chips *chips = (Chips *)malloc(sizeof(Chips));
    if(!chips) {
        printf("Problème d'allocation du Chips !!!");
        exit(1);
    }
    if (choix == 'Q') {
        free(chips);
        return NULL;
    }
    if(tourelleLettreVersNum(choix, &(chips->type), 'L', &(chips->life))) {
        if(tourelleLettreVersNum(choix, &(chips->type), 'P', &(chips->price))) {
            if(tourelleLettreVersNum(choix, &(chips->type), 'D', &(chips->degat))) {
                chips->next = NULL;
                chips->position = 0;
                chips->line = 0;
                return chips;
            } else {
                printf("Erreur de choix de Type de Tourelle. Ressayé !!!\n");
                return NULL;
            }
        } else {
            printf("Erreur de choix de Type de Tourelle. Ressayé !!!\n");
            return NULL;
        }
    } else {
        printf("Erreur de choix de Type de Tourelle. Ressayé !!!\n");
        return NULL;
    }
}

int prixsuffisant(Game *jeu, char choix) {
    if(choix == 'Q') return 2;
    int typeChoix, prix;
    if (tourelleLettreVersNum(choix, &typeChoix, 'P', &prix)) {
        if(jeu->money >= prix) {
            jeu->money -= prix;
            return 1;
        } else {
            printf("Sold insuffisant. Choisissé une autre Tourelle moins chere !!!\n");
            return 0;
        }
    } else {
        printf("Erreur de choix de Type de Tourelle. Ressayé !!!\n");
        return 0;
    }
}

void insereChips(Game *jeu, Chips *chips) {
    if(!(jeu->chips)) {
        jeu->chips = chips;
        return;
    }
    Chips *tmp = jeu->chips;
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = chips;
}


int estDansTableau(int lig, int col) {
    if( (1 <= col && NBPOSITION >= col) && (1 <= lig && NBLIGNE >= lig)) return 1;
    return 0;
}


int positionVide(Game *jeu, int lig, int col) {
    if(!(jeu->chips)) return 1;
    Chips *tmp = jeu->chips;
    while(tmp) {
        if(tmp->line == lig && tmp->position == col) return 0;
        tmp = tmp->next;
    }
    return 1;
}


int positionValide(Game *jeu, int lig, int col) {
    if(estDansTableau(lig, col) == 0) return 0;
    if(positionVide(jeu, lig, col)) return 1;
    else return 0;
}

Virus *supprimeVirus(Game *jeu, Virus *avant, Virus *virus) {
    Virus *res = virus;
    if(avant == virus) jeu->virus = virus->next;
    else avant->next = virus->next;
    if(!(virus->next_line) && !(virus->prev_line)) return res;
    if(virus->next_line && !(virus->prev_line)) virus->next_line->prev_line = NULL;
    else if(!(virus->next_line) && virus->prev_line) virus->prev_line->next_line = NULL;
    else if(virus->next_line && virus->prev_line) {
        virus->next_line->prev_line = virus->prev_line;
        virus->prev_line->next_line = virus->next_line;
    }
    res->next_line = NULL;
    res->prev_line = NULL;
    return res;
}


void libereListeVirus(Game *jeu){
    Virus *next;
    while(jeu->virus) {
        next = jeu->virus->next;
        jeu->virus->next_line = NULL;
        jeu->virus->prev_line = NULL;
        free(jeu->virus);
        jeu->virus = next;
    }
}

Chips *supprimeChips(Game *jeu, int lig, int col) {
    Chips *tmp = jeu->chips;
    Chips *res = NULL;
    if(tmp == NULL) return NULL;
    if(tmp && (tmp->line == lig && tmp->position == col)) {
        res = tmp;
        jeu->chips = tmp->next;
        res->next = NULL;
        return res;
    }
    while(tmp->next && (tmp->next->line != lig && tmp->next->position != col)){
        tmp = tmp->next;
    }
    if(tmp->next == NULL) return NULL;
    res = tmp->next;
    tmp->next = res->next;
    res->next = NULL;
    return res;
}
void libereListeChips(Game *jeu){
    Chips *next;
    while(jeu->chips){
        next = jeu->chips->next;
        free(jeu->chips);
        jeu->chips = next;
    }
}
Chips *chipsDebutLigne(Game *jeu, int lig) {
    Chips *tmp = jeu->chips;
    Chips *debut = NULL;
    while(tmp) { 
        if(tmp->line == lig) {
            if(!debut) debut = tmp;
            else if(tmp->position > debut->position) debut = tmp;
        }
        tmp = tmp->next;
    }
    return debut;
}


Virus *virusDebutLigne(Game *jeu, int lig) {
    Virus *tmp = jeu->virus;
    while(tmp && (tmp->line != lig)) {
        tmp = tmp->next;
    }
    if(!tmp) return NULL; // cas ou aucun virus dans cette ligne lig
    while(tmp->next_line) {
        tmp = tmp->next_line;
    }
    if(tmp->position == -20) return NULL;
    return tmp;
}


Virus *avantVirus(Game *jeu, Virus *virus) {
    Virus *tmp = jeu->virus;
    Virus *avant = jeu->virus;
    if(tmp == virus) return avant;
    while(tmp->next && tmp->next != virus) {
        avant = tmp;
        tmp = tmp->next;
    }
    return avant;
}



void accelereVirusLigne(Game *jeu, Virus *virus, int lig) {
    Virus *debutVir = virusDebutLigne(jeu, lig);
    Chips *debutChip = chipsDebutLigne(jeu, lig);
    if(debutChip && debutVir && debutChip->position == debutVir->position) return;
    if(debutVir && debutVir != virus) debutVir->position -= 1; //ajouter 1 à la postion c'est equivalent à accelere la vitesse de 1
}

void virusTypeD(Game *jeu, Virus *virus) {
    accelereVirusLigne(jeu, virus, virus->line - 1); // accelere le premier virus a la ligne en haut
    accelereVirusLigne(jeu, virus, virus->line + 1); // accelere le premier virus a la ligne en bas
    accelereVirusLigne(jeu, virus, virus->line); // accelere le premier de sa ligne
}




void virusTypeB(Game *jeu, Virus *virus) {
    if(virus->next_line && virus->next_line->position != -20) virus->next_line->life += 1;
    if(virus->prev_line && virus->prev_line->position != -20) virus->prev_line->life += 1;
}


void updateLifeVirusDevant(Game *jeu, int lig) {
    Virus *debutVir = virusDebutLigne(jeu, lig);
    Chips *debutChi = chipsDebutLigne(jeu, lig);
    if(debutChi && debutVir) debutVir->life -= debutChi->degat;
}




void updateInfoVirus(Game *jeu) {
    Virus *tmp = jeu->virus;
    while (tmp) {
        if(tmp->position != -20) {
            if(tmp->type == 2) virusTypeD(jeu, tmp);
            else if(tmp->type == 5) virusTypeB(jeu, tmp);
        }
        tmp = tmp->next;
    }
    for(int i = 1; i <= NBLIGNE; ++i) updateLifeVirusDevant(jeu, i);
}

void updateInfoChips(Game *jeu, char mode) {
    Chips *debutChips;
    Virus *debutVirus;
    for(int i = 1; i <= NBLIGNE; ++i) {
        debutChips = chipsDebutLigne(jeu, i);
        if(debutChips) {
            debutVirus = virusMemeCase(jeu, i, debutChips->position);
            if(debutVirus) { //cas de colision
                if(debutChips->type == 3) {
                    Chips *chipsPourSup = supprimeChips(jeu, debutChips->line, debutChips->position);
                    Virus *virusPourSup = supprimeVirus(jeu, avantVirus(jeu, debutVirus), debutVirus);
                    if(mode == 'G') {
                        MLV_Image *explosion = MLV_load_image("./images/explosion.png");
                        MLV_resize_image(explosion, LARG_PHOTO, HAUT_PHOTO);
                        MLV_draw_image(explosion, indiceVersCoord(debutChips->position, 'H') - (LARG_PHOTO / 2) + 10, indiceVersCoord(debutChips->line, 'V') - (HAUT_PHOTO / 2));
                        MLV_init_audio();
                        MLV_Sound *sound = MLV_load_sound("./sounds/audio.ogg");
                        MLV_play_sound(sound, 100.0);
                        MLV_free_image(explosion);
                        MLV_update_window();
                    }
                    free(chipsPourSup);
                    free(virusPourSup);
                } else {
                    debutChips->life -= 1; //cas de colision la vie du chips diminue de 1
                }
            }
            if(debutChips->type == 2) {
                Virus *debutLigneHaut = virusDebutLigne(jeu, debutChips->line + 1);
                Virus *debutLigneBas = virusDebutLigne(jeu, debutChips->line - 1);
                if(debutLigneHaut) debutLigneHaut->life -= debutChips->degat;
                if(debutLigneBas) debutLigneBas->life -= debutChips->degat;
            } else if(debutChips->type == 4) {
                Virus *virusdebut = virusDebutLigne(jeu, debutChips->line);
                if(virusdebut) virusdebut->speed = 1;
            }
        }
    }
}


Chips *detecterChipsLigne(Game *jeu, int lig, int col){
    Chips *tmp= jeu->chips;
    while(tmp){
        if(tmp->line == lig && tmp->position == col){
            return tmp;
        }   
        tmp = tmp->next;
    }
    return NULL;
}
void apparaitreVirus(Game *jeu) {
    Virus *tmp = jeu->virus;
    while(tmp) {
        if(tmp->position == -20 && tmp->turn == jeu->turn) {
            tmp->position = NBPOSITION;
        }
        tmp = tmp->next;
    }
}


void moveVirus(Game *jeu){
    Virus *tmp = NULL;
    Virus *debut;
    Chips *debutChips;
    for(int i = 1; i <= NBLIGNE; ++i) {
        debut = virusDebutLigne(jeu, i);
        if(debut) {
            tmp = debut;
            while (tmp && tmp->position != -20){
                if(tmp->next_line == NULL) {
                    debutChips = chipsDebutLigne(jeu, i);
                    if(debutChips && (tmp->position - tmp->speed) < debutChips->position) {
                        tmp->position = debutChips->position;
                    } else tmp->position -= tmp->speed;
                } else {
                    if((tmp->position - tmp->speed) <= tmp->next_line->position) {
                        tmp->position = tmp->next_line->position + 1;
                    } else tmp->position -= tmp->speed;
                }
                tmp = tmp->prev_line;
            }
        }
    }
    apparaitreVirus(jeu);
}

void supprimeChipsMort(Game *jeu, char mode){
    Chips *chips = jeu->chips;
    Chips *apres;
    Chips *supp;
    while(chips){
        if(chips->life <= 0) {
            apres = chips->next;
            supp = supprimeChips(jeu, chips->line, chips->position);
            if(mode == 'G') {
                MLV_Image *explosion = MLV_load_image("./images/explosion.png");
                MLV_resize_image(explosion, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(explosion, indiceVersCoord(chips->position, 'H') - (LARG_PHOTO / 2) + 10, indiceVersCoord(chips->line, 'V') - (HAUT_PHOTO / 2));
                MLV_init_audio();
                MLV_Sound *sound = MLV_load_sound("./sounds/audio.ogg");
                MLV_play_sound(sound, 100.0);
                MLV_free_image(explosion);
                MLV_update_window();
            }
            free(supp);
            chips = apres;
        } else {
            chips = chips->next;
        }
    }
    
}


void supprimeVirusMort(Game *jeu, char mode){
    Virus *virus = jeu->virus;
    Virus *sup = NULL;
    Virus *avant = jeu->virus;
    while(virus) {
        if(virus->life <= 0 && virus->position != -20) {
            sup = supprimeVirus(jeu, avant, virus);
            if(avant == sup) avant = avant->next;
            if(mode == 'G') {
                MLV_Image *explosion = MLV_load_image("./images/explosion.png");
                MLV_resize_image(explosion, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(explosion, indiceVersCoord(virus->position, 'H') - (LARG_PHOTO / 2) + 10, indiceVersCoord(virus->line, 'V') - (HAUT_PHOTO / 2));
                MLV_init_audio();
                MLV_Sound *sound = MLV_load_sound("./sounds/audio.ogg");
                MLV_play_sound(sound, 100.0);
                MLV_free_image(explosion);
                MLV_update_window();
            }
            free(sup);
        } else {
            avant = virus;
        }
        virus = virus->next;
    }
}


int finPartie(Game *jeu){
    Virus *tmp = jeu->virus;
    if(!tmp) return 2;
    while(tmp){
        if(tmp->position <= 1 && tmp->position != -20) return 1;
        tmp = tmp->next;
    }
    return 0;
}

