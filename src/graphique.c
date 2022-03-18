#include "utils.h"
#include "graphique.h"


void centerText(char *text, int posX, int posY, MLV_Font *police){
    int width_text, height_text;
    MLV_get_size_of_text_with_font(text, &width_text, &height_text, police);
    int positionX = posX - (width_text / 2) ;
    int positionY =  posY - (height_text / 2);
    MLV_draw_text_with_font(positionX, positionY, text, police, MLV_COLOR_GHOST_WHITE);
}


void centerBox(char *text, int posX, int posY, MLV_Font *police, int *width_box, int *height_box, int *xBox, int *yBox){
    MLV_get_size_of_adapted_text_box_with_font(text, police, 2, width_box, height_box);
    *xBox = posX - (*width_box / 2), *yBox = posY - (*height_box / 2);
    MLV_draw_adapted_text_box_with_font(*xBox, *yBox, text, police,2, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


void menu() {
    int width = 512, height = 512, width_box, height_box, clicY, clicX, xBox, yBox;
    char *debut = "Commencer";
    MLV_create_window("Chips Vs Virus", "", width, height );
    MLV_Font *police = MLV_load_font("./fonts/Comfortaa-Regular.ttf", width * 0.1);
    MLV_draw_filled_rectangle(0, 0, width, height, MLV_COLOR_DARK_GREEN);
    char* text = "Chips Vs Virus";
    centerText(text, 256, 100, police); 
    centerBox(debut, 256, 300, police, &width_box, &height_box, &xBox, &yBox);
    MLV_actualise_window();
    do {
        MLV_wait_mouse(&clicX, &clicY);
    } while(!(clicX >= xBox && clicX <= xBox + width_box && clicY >= yBox && clicY <= yBox + height_box));
    MLV_free_font(police);
}



ChipsGraphique *initImageChips() {
    ChipsGraphique *tabImage = (ChipsGraphique *)malloc(5 * sizeof(ChipsGraphique)); 
    tabImage[0].image = MLV_load_image("./images/tourelleA.png");
    tabImage[1].image = MLV_load_image("./images/tourelleR.png");
    tabImage[2].image = MLV_load_image("./images/tourelleP.png");
    tabImage[3].image = MLV_load_image("./images/tourelleX.png");
    tabImage[4].image = MLV_load_image("./images/tourelleF.png");
    for(int i = 0; i < 5; ++i) {
        if(i == 0) tabImage[i].x = TAILLE_MARGE + DIST_2_CHOSE;
        else tabImage[i].x = tabImage[i - 1].x + LARG_PHOTO + DIST_2_CHOSE;
        tabImage[i].y = DIST_2_CHOSE;
    }
    return tabImage;
}



Boutton *dessinButton(MLV_Font *police, int largeur) {
    int x, y;
    Boutton *tabBtn = (Boutton *)malloc(3 * sizeof(Boutton));
    y = DIST_2_CHOSE + (LARG_PHOTO/2);
    for(int i = 2; i >= 0; --i) {
        if(i == 2) {
            x = largeur - TAILLE_MARGE - 20;
            centerBox("Exit ", x, y, police, &tabBtn[i].largeur, &tabBtn[i].hauteur, &tabBtn[i].x, &tabBtn[i].y);
        } else if(i == 1) {
            x = largeur - 2 * tabBtn[i + 1].largeur - TAILLE_MARGE - DIST_2_CHOSE;
            centerBox("Debut", x, y, police, &tabBtn[i].largeur, &tabBtn[i].hauteur, &tabBtn[i].x, &tabBtn[i].y);
        } else if (i == 0) {
            x = largeur - 2 * tabBtn[i + 1].largeur - tabBtn[i + 2].largeur - TAILLE_MARGE - 2 * DIST_2_CHOSE;
            centerBox("Vague", x, y, police, &tabBtn[i].largeur, &tabBtn[i].hauteur, &tabBtn[i].x, &tabBtn[i].y);
        }
    }
    return tabBtn;
}

void dessinTourelle(int money, ChipsGraphique *tabImage, MLV_Font *police) {
    char *text = (char *)malloc(20 * sizeof(char));
    char *priceChar = (char *)malloc(6 * sizeof(char));
    char typelettre;
    int price;
    for(int i = 0; i < 5; ++i) {
        MLV_resize_image(tabImage[i].image, LARG_PHOTO, HAUT_PHOTO);
        MLV_draw_image(tabImage[i].image, tabImage[i].x, tabImage[i].y);
        tourelleNumVersLettre(i+1, &typelettre, 'P', &price);
        sprintf(priceChar, "%d", price);
        centerText(priceChar, tabImage[i].x + LARG_PHOTO/2, tabImage[i].y + HAUT_PHOTO + DIST_2_CHOSE + 10, police);
        MLV_free_image(tabImage[i].image);
    }
    sprintf(text, "Solde: %d", money);
    centerText(text, tabImage[4].x + 3 * LARG_PHOTO + DIST_2_CHOSE, DIST_2_CHOSE + (HAUT_PHOTO / 2), police);
    free(text);
    free(priceChar);
}



int coordVersIndice(int coor, char direction) {
    if (direction == 'H') return ((coor - (TAILLE_MARGE + LARG_PC)) / DIST_2_POINT) + 1;
    else return ((coor - (TAILLE_MARGE + HEIGHT_CHAMPINFO)) / DIST_2_POINT) + 1;
}



int indiceVersCoord(int i, char direction) {
    if(direction == 'H') return ((TAILLE_MARGE + LARG_PC) + i * DIST_2_POINT) - DIST_2_POINT / 2;
    else return ((TAILLE_MARGE + HEIGHT_CHAMPINFO) + i * DIST_2_POINT) - DIST_2_POINT / 2;
}



void dessinPoints() {
    for(int lig = 1; lig <= NBLIGNE; ++lig) {
        for(int col = 1; col <= NBPOSITION; ++col) {
            MLV_draw_filled_circle(indiceVersCoord(col, 'H'), indiceVersCoord(lig, 'V'), RAYON, MLV_COLOR_GREEN);
        }
    }
}





MLV_Image *typeVersImageChips(int i) {
    MLV_Image *chips;
    switch (i) {
        case 1:
            chips = MLV_load_image("./images/tourelleA.png");
            break;
        case 2:
            chips = MLV_load_image("./images/tourelleR.png");
            break;
        case 3:
            chips = MLV_load_image("./images/tourelleP.png");
            break;
        case 4:
           chips = MLV_load_image("./images/tourelleX.png");
            break;
        case 5:
            chips = MLV_load_image("./images/tourelleF.png");
            break;
        default:
            return NULL;
    }
    return chips;
}



MLV_Image *typeVersImageVirus(int i) {
    MLV_Image *virus;
    switch (i) {
        case 1:
            virus = MLV_load_image("./images/virusE.png");
            break;
        case 2:
            virus = MLV_load_image("./images/virusD.png");
            break;
        case 3:
            virus = MLV_load_image("./images/virusS.png");
            break;
        case 4:
            virus = MLV_load_image("./images/virusM.png");
            break;
        case 5:
            virus = MLV_load_image("./images/virusB.png");
            break;
        default:
            return NULL;
    }
    return virus;
}


void dessinPlateauLigne(Game *jeu, int lig, MLV_Font *police) {
    int *typechips = (int *)calloc(NBPOSITION, sizeof(int));
    int *typevirus = (int *)calloc(NBPOSITION, sizeof(int));
    Chips *tmp = jeu->chips, *chips;
    Virus *tmpVir = jeu->virus, *virus;
    char lettreChips, lettreVirus;
    char *LettreLifeChi = (char *)malloc(sizeof(char) * 5);
    char *LettreLifeVir = (char *)malloc(sizeof(char) * 5);
    int lifeVir, lifeChi;
    MLV_Image *imageVirus;
    MLV_Image *imageChips;
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
    for(int j = 0; j < NBPOSITION; ++j){
        if(typechips[j] != 0 && typevirus[j] != 0) {
            virusNumVersLettre(typevirus[j], &lettreVirus, 'L', &lifeVir);
            tourelleNumVersLettre(typechips[j], &lettreChips, 'L', &lifeChi);
            imageVirus = typeVersImageVirus(typevirus[j]); 
            imageChips = typeVersImageChips(typechips[j]);
            if(imageChips && imageVirus) {
                MLV_resize_image(imageVirus, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(imageVirus, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2) + 10, indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2));
                //affichage life
                virus = virusMemeCase(jeu, lig, j + 1);
                sprintf(LettreLifeVir, "%d", virus->life);
                centerText(LettreLifeVir, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2) + LARG_PHOTO, indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2) + HAUT_PHOTO, police);

                MLV_resize_image(imageChips, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(imageChips, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2), indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2));
                //affichage life
                chips = chipsMemeCase(jeu, lig, j + 1);
                sprintf(LettreLifeChi, "%d", chips->life);
                centerText(LettreLifeChi, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2), indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2) + HAUT_PHOTO, police);
            }
        } else if(typechips[j] == 0 && typevirus[j] != 0) {
            virusNumVersLettre(typevirus[j], &lettreVirus, 'L', &lifeVir);
            imageVirus = typeVersImageVirus(typevirus[j]);
            if (imageVirus) {
                MLV_resize_image(imageVirus, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(imageVirus, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2), indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2));
                //affichage life
                virus = virusMemeCase(jeu, lig, j + 1);
                sprintf(LettreLifeVir, "%d", virus->life);
                centerText(LettreLifeVir, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2) + LARG_PHOTO, indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2) + HAUT_PHOTO, police);
            }
        } else if(typevirus[j] == 0 && typechips[j] != 0) {
            tourelleNumVersLettre(typechips[j], &lettreChips, 'L', &lifeChi);
            imageChips = typeVersImageChips(typechips[j]);
            if(imageChips) {
                MLV_resize_image(imageChips, LARG_PHOTO, HAUT_PHOTO);
                MLV_draw_image(imageChips, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2), indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2));
                //affichage life
                chips = chipsMemeCase(jeu, lig, j + 1);
                sprintf(LettreLifeChi, "%d", chips->life);
                centerText(LettreLifeChi, indiceVersCoord(j+1, 'H') - (LARG_PHOTO / 2), indiceVersCoord(lig, 'V') - (HAUT_PHOTO / 2) + HAUT_PHOTO, police);
            }
        }
    }
    free(LettreLifeChi);
    free(LettreLifeVir);
    free(typevirus);
    free(typechips);
}



void voirVagueGraphique(int largeur, int longeur, char *nmFic, MLV_Font *police) {
    int money, tour, ligne, life, typeNum, x, y, lar, haut;
    FILE *fic = fopen(nmFic, "r");
    char type;
    MLV_Image *imageVirus;
    fscanf(fic, "%d", &money);
    while(fscanf(fic, "%d %d %c", &tour, &ligne, &type) != EOF) {
        virusLettreVersNum(type, &typeNum, 'L', &life);
        imageVirus = typeVersImageVirus(typeNum);
        MLV_resize_image(imageVirus, LARG_PHOTO, HAUT_PHOTO);
        if (ligne > NBLIGNE || tour > NBPOSITION) {
            centerBox("Vague trés long\nRegarder Le terminal", largeur/2, longeur/2, police, &lar, &haut, &x, &y);
            rewind(fic);
            afficheVague(nmFic);
            break;
        }
        else MLV_draw_image(imageVirus, indiceVersCoord(tour, 'H') - (LARG_PHOTO / 2) + 10, indiceVersCoord(ligne, 'V') - (HAUT_PHOTO / 2));
        MLV_free_image(imageVirus);
    }
    fclose(fic);
}




void dessinPlateau(Game *jeu, int largeur, int longeur, MLV_Font *police) {
    MLV_Image *pc = MLV_load_image("./images/pc.png");
    MLV_resize_image(pc, LARG_PC, HAUT_PC);
    MLV_draw_image(pc, TAILLE_MARGE, HEIGHT_CHAMPINFO + ((longeur - HEIGHT_CHAMPINFO - HAUT_PC) / 2));
    MLV_free_image(pc);
    dessinPoints();
    for(int i = 1; i <= NBLIGNE; ++i)
        dessinPlateauLigne(jeu, i, police);
}




void dessinFenetre(Game *jeu, MLV_Font *police, int largeur, int money, int longeur, ChipsGraphique **Image, Boutton **Btn){
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_Image *bg = MLV_load_image("./images/space.jpg");
    MLV_resize_image(bg, largeur, longeur);
    MLV_draw_image(bg, 0, 0);
    MLV_free_image(bg);
    MLV_draw_filled_rectangle(0, 0, largeur, HEIGHT_CHAMPINFO, MLV_COLOR_GRAY);
    *Image = initImageChips();
    dessinTourelle(money, *Image, police);
    *Btn = dessinButton(police, largeur);
    dessinPlateau(jeu, largeur, longeur, police);
    MLV_update_window();
}





int detecteTourelle(Game *jeu,ChipsGraphique *chipsImage, int x, int y, int *type) {
    for(int i = 0; i < 5; ++i) {
        if((x>= chipsImage[i].x && x <= chipsImage[i].x + LARG_PHOTO) && (y>= chipsImage[i].y && y <= chipsImage[i].y + HAUT_PHOTO)) {
            *type = i + 1;
            return 1;
        }
    }
    return 0;
}




int detecteBoutton(Boutton *btn, int x, int y, int *typeBtn) {
    for(int i = 0; i < 3; ++i) {
        if((x>= btn[i].x && x <= btn[i].x + btn[i].largeur) && (y>= btn[i].y && y <= btn[i].y + btn[i].hauteur)) {
            *typeBtn = i + 1;
            return 1;
        }
    }
    return 0;
}





void detecteClick(Game *jeu, Boutton *btn, ChipsGraphique *chipsImage, int largeur , int longeur, char *nomFic, MLV_Font *police) {
    int x, y, typeTourelle, typeBtn, resTour = 0, resVir = 0, emplacement = 0, life, commence = 0, res1;
    char typeLettre;
    Chips *chips;
    while(!commence) {
        resVir = 0;
        resTour = 0;
        do {
            MLV_wait_mouse(&x, &y);
            if((x >= 0 && x <= chipsImage[4].x + LARG_PHOTO) && (y >= 0 && y <= HEIGHT_CHAMPINFO))
                resTour = detecteTourelle(jeu, chipsImage, x, y, &typeTourelle);
            else if ((x > chipsImage[4].x + LARG_PHOTO && x <= largeur) && (y >= 0 && y <= HEIGHT_CHAMPINFO))
                resVir = detecteBoutton(btn, x, y, &typeBtn);
        } while(resTour == 0 && resVir == 0);
        if(resTour) {
            MLV_draw_rectangle(chipsImage[typeTourelle - 1].x, chipsImage[typeTourelle - 1].y, LARG_PHOTO, HAUT_PHOTO, MLV_COLOR_GREEN);
            MLV_update_window();
            do {
                MLV_wait_mouse(&x, &y);
                if((x >= (TAILLE_MARGE + LARG_PC) && x <= largeur) && (y >= (HEIGHT_CHAMPINFO + TAILLE_MARGE) && y <= longeur))
                    emplacement = positionValide(jeu, coordVersIndice(y, 'V'), coordVersIndice(x, 'H'));
            } while(emplacement == 0);
            tourelleNumVersLettre(typeTourelle, &typeLettre, 'L', &life);
            if ((res1 = prixsuffisant(jeu, typeLettre)) == 1) {
                chips = alloueTourelle(typeLettre);
                chips->line = coordVersIndice(y, 'V');
                chips->position = coordVersIndice(x, 'H');
                insereChips(jeu, chips);
                dessinFenetre(jeu, police, largeur, jeu->money, longeur, &chipsImage, &btn);
            } else {
                int width, height, x1, y1;
                centerBox("Sold Insufisant", largeur/2, longeur/2, police, &width, &height, &x1, &y1);
                MLV_update_window();
            }
        } else if(resVir) {
            switch (typeBtn) {
                case 1:
                    voirVagueGraphique(largeur, longeur, nomFic, police);
                    MLV_update_window();
                    MLV_wait_mouse(&x, &y);
                    resVir = detecteBoutton(btn, x, y, &typeBtn);
                    if(resVir && typeBtn == 1) dessinFenetre(jeu, police, largeur, jeu->money, longeur, &chipsImage, &btn);
                    break;
                case 2:
                    commence = 1;
                    break;
                case 3:
                    MLV_wait_seconds(1);
                    MLV_free_window();
                    exit(1);
            }
        }
        MLV_update_window();
    }
}




void graphique(char *nomFic) {   
    Game jeu;
    ChipsGraphique *tabChips;
    Boutton *tabBtn;
    int res, width, height, xBox, yBox;
    initialiserJeu(&jeu, nomFic);
    int longeur = HEIGHT_CHAMPINFO + 2 * TAILLE_MARGE + NBLIGNE * DIST_2_POINT;
    int largeur = 2 * TAILLE_MARGE + NBPOSITION * DIST_2_POINT + LARG_PC;
    menu();
    MLV_change_window_size(largeur, longeur);
    MLV_Font *police = MLV_load_font("./fonts/Comfortaa-Regular.ttf", largeur * 0.015);
    dessinFenetre(&jeu, police, largeur, jeu.money, longeur, &tabChips, &tabBtn);
    detecteClick(&jeu, tabBtn, tabChips, largeur, longeur, nomFic, police);
    while(!(res = finPartie(&jeu))) {
        jeu.turn += 1;
        updateInfoVirus(&jeu);
        updateInfoChips(&jeu, 'G');
        supprimeVirusMort(&jeu, 'G');
        supprimeChipsMort(&jeu, 'G');
        moveVirus(&jeu);
        dessinFenetre(&jeu, police, largeur, jeu.money, longeur, &tabChips, &tabBtn);
        MLV_wait_seconds(2);
    }
    if(res == 2) {
        centerBox("Partie Gagné", largeur/2, longeur/2, police, &width, &height, &xBox, &yBox);
    } else if(res == 1) {
        centerBox("Partie Perdu", largeur/2, longeur/2, police, &width, &height, &xBox, &yBox);
    }
    libereListeChips(&jeu);
    libereListeVirus(&jeu);
    free(tabBtn);
    free(tabChips);
    MLV_update_window();
    MLV_wait_seconds(2);
    MLV_free_window();
}

