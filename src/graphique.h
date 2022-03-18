#include <MLV/MLV_all.h>
#include "utils.h"
/*
    BUT: fonction responsable de lcentrer un text passé en paramètre à une position x et y
    PARAM: adresse: adresse du texte que l'on veut écrire et la police
           valeur: (int) coordonnées x et y où on veut placer le texte
*/
void centerText(char *text, int posX, int posY, MLV_Font *police);


/*
    BUT: fonction responsable de lcentrer un box passé en paramètre à une position x et y
    PARAM: adresse: adresse du texte que l'on veut écrire et la police
                    les coordonnées de la box initialement vide avant l'appel de la fonction
           valeur: (int) coordonnées x et y où on veut placer le texte
*/
void centerBox(char *text, int posX, int posY, MLV_Font *police, int *width_box, int *height_box, int *xBox, int *yBox);


/*
    BUT: fonction responsable d'afficher le menu graphique 
*/
void menu();



/*
    BUT: fonction responsable d'initialiser les images des tourelles avec leurs coordonnées
         dans la structure ChipsGraphique
*/
ChipsGraphique *initImageChips();


/*
    BUT: fonction responsable de dessiner les bouttons graphique avec affectation de leurs coordonnées
         dans la structure Boutton
*/
Boutton *dessinButton(MLV_Font *police, int largeur);


/*
    BUT: fonction responsable de dessiner les tourelles avec affectation de leurs coordonnées
         dans la structure ChipsGraphique
    PARAM: valeur: (int) valeur de l'argenet que possède le joueur
           adresse: adresse de tableau contenant les images de tourelles et la police.
*/
void dessinTourelle(int money, ChipsGraphique *tabImage, MLV_Font *police);


/*
    BUT: Transformer les coordonnées passés en paramètres en indice valide dans le plateau du jeu suivant la direction 
         soit horizontale soit verticale
    PARAM: valeur: (int) valeur des coordonnées
                   (char) direction soir horizontale soit vertiacle
    RETURN: renvoie l'indice corresponsant aux coordonées passées en paramètre
*/
int coordVersIndice(int coor, char direction);


/*
    BUT: Transformer l'indice passé en paramètre en coorodonnée valide dans le plateau du jeu suivant la direction 
         soit horizontale soit verticale
    PARAM: valeur: (int) valeur de l'indice
                   (char) direction soir horizontale soit vertiacle
    RETURN: renvoie les coordonnées correspondant à l'indice  passé en paramètre suivant la direction
*/
int indiceVersCoord(int i, char direction);



/*
    BUT: Fonction dessinant les points dans le plateau du jeu
*/
void dessinPoints();


/*
    BUT:  fonction transformant un type d'image de tourelle vers un pointeur d'une image
    PARAM: valeur: (int) type de la tourelle
    RETURN: renvoie un pointeur vers une image MLV_image *image
*/
MLV_Image *typeVersImageChips(int i);



/*
    BUT:  fonction transformant un type d'image de virus vers un pointeur d'une image
    PARAM: valeur: (int) type de virus
    RETURN: renvoie un pointeur vers une image MLV_image *image
*/
MLV_Image *typeVersImageVirus(int i);


/*
    BUT:  fonction dessinant une ligne du plateau graphique en prenant en considérant les cas
          cas de collision.
    PARAM: valeur: (int) la ligne que l'on veut dessiner
           adresse: la police
*/
void dessinPlateauLigne(Game *jeu, int lig, MLV_Font *police);


/*
    BUT:  fonction dessinant la vague dans le plateau
    PARAM: valeur: (int) largeur et hauteur de la fenetre
           adresse: la police et le nom de fichier contenant la vague
*/
void voirVagueGraphique(int largeur, int longeur, char *nmFic, MLV_Font *police);


/*
    BUT:  fonction dessinant le plateau graphique
    PARAM: valeur: (int) largeur et hauteur de la fenetre
           adresse: la police et ll'adresse de la structure du jeu principal.
*/
void dessinPlateau(Game *jeu, int largeur, int longeur, MLV_Font *police);


/*
    BUT:  fonction dessinant la fenêtre graphique
    PARAM: valeur: (int) largeur et hauteur de la fenetre
           adresse: la police et ll'adresse de la structure du jeu principal l'adresse du tableau contenant
                     les bouttons et l'images des tourelles.
*/
void dessinFenetre(Game *jeu, MLV_Font *police, int largeur, int money, int longeur, ChipsGraphique **Image, Boutton **Btn);



/*
    BUT:  fonction responsable de la détection des clics des tourelles
    PARAM: valeur: (int) x et y les coordonnées du clic de l'utilisateur
           adresse: la structure du jeu principale l'adresse du type de la tourelle et le tableau contenant les images des tourelles
    RETURN: renvoie 1 au cas où l'utilisateur a bien cliqué sur une tourelle 0 sinon
*/
int detecteTourelle(Game *jeu,ChipsGraphique *chipsImage, int x, int y, int *type);



/*
    BUT:  fonction responsable de la détection des clics des bouttons
    PARAM: valeur: (int) x et y les coordonnées du clic de l'utilisateur
           adresse: la structure du jeu principale l'adresse du type du boutton et le tableau contenant les bouttons
    RETURN: renvoie 1 au cas où l'utilisateur a bien cliqué sur une boutton 0 sinon
*/
int detecteBoutton(Boutton *btn, int x, int y, int *typeBtn);



/*
    BUT:  fonction responsable de la détection des clics du jeu avec l'emplacement des tourelles selon le clic de l'utilisateur
    PARAM: valeur: (int) largeur et hauteur de la fenêtre.
           adresse: la structure du jeu principale et le tableau contenant les images des tourelles et boutton et la polic et le nom de fichier
*/
void detecteClick(Game *jeu, Boutton *btn, ChipsGraphique *chipsImage, int largeur , int longeur, char *nomFic, MLV_Font *police);




/*
    BUT:  foonction du mode graphique 
    PARAM: adresse: nom du fichier texte contenant la vague
*/
void graphique(char *nomFic);

