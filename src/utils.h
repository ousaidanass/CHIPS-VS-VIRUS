#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <MLV/MLV_all.h>

#define NBPOSITION 24
#define NBLIGNE 7
#define HEIGHT_CHAMPINFO 90
#define TAILLE_MARGE 20
#define DIST_2_POINT 50 
#define DIST_2_CHOSE 5
#define LARG_PHOTO 60
#define HAUT_PHOTO 60
#define LARG_PC 150
#define HAUT_PC 150
#define RAYON 5
#define MAXTOURVAGUE 25


typedef struct chips{
    int type;
    int life;
    int line;
    int position;
    int price;
    int degat;
    struct chips* next;
} Chips;

typedef struct virus{
    int type;
    int life;
    int line;
    int position;
    int speed;
    int turn;
    struct virus* next;
    struct virus* next_line;
    struct virus* prev_line;
} Virus;

typedef struct{
    Virus* virus;
    Chips* chips;
    int turn;
    int money;
} Game;

//Structure contenant les coordonnées de chaque chips du plateau graphique pour faciliter la détection des clics
typedef struct{
    MLV_Image *image;
    int x;
    int y;
} ChipsGraphique;

//Structure contenant les coordonnées de chaque boutton du plateau graphique pour faciliter la détection des clics
typedef struct{
    int x;
    int y;
    int largeur;
    int hauteur;
} Boutton;



/*
    BUT: vider le buffer de l'entrée standard
*/
void viderBuffer();



/*
    BUT: conversion d'un type de tourelle d'un int vers un char
    PARAM: valeur: numéro de la tourelle qu'on veut convertir et le type d'information
                   que l'on souhaite price ou degat
           adresse: adresse du caractère de la tourelle et l'information que l'on veut
    RETURN: renvoie 1 si tout est bien passé 0 si y a pas de choix disponibles
*/
int tourelleNumVersLettre(int num, char *lettre, char info, int *res);



/*
    BUT: conversion d'un type de tourelle d'un char vers un int
    PARAM: valeur: caractère de la tourelle qu'on veut convertir et le type d'information
                   que l'on souhaite price ou degat
           adresse: adresse du int de la tourelle et l'information que l'on veut
    RETURN: renvoie 1 si tout est bien passé 0 si y a pas de choix dispnibles
*/
int tourelleLettreVersNum(char choix, int *num, char info, int *res);



/*
    BUT: conversion d'un type de virus d'un int vers un char
    PARAM: valeur: numéro du virus qu'on veut convertir et le type d'information
                   que l'on souhaite price ou degat
           adresse: adresse du caractère du virus et l'information que l'on veut
    RETURN: renvoie 1 si tout est bien passé 0 si y a pas de choix dispnibles
*/
int virusNumVersLettre(int num, char *lettre, char info, int *res);


/*
    BUT: conversion d'un type de virus d'un char vers un int
    PARAM: valeur: caractère du virus qu'on veut convertir et le type d'information
                   que l'on souhaite price ou degat
           adresse: adresse du int du virus et l'information que l'on veut
    RETURN: renvoie 1 si tout est bien passé 0 si y a pas de choix dispnibles
*/
int virusLettreVersNum(char choix, int *num, char info, int *res);




/*
    BUT: Trouver la tourelle qui se trouve dans la même ligne et colonne passé en paramètre
    PARAM: valeur: numéro du ligne de la colonne où on cherche à trouver si y a un tourelle
                   qui se trouve au même coordonnées.
           adresse: adresse du jeu
    RETURN: renvoie l'adresse de la tourelle s'elle existe NUll sinon
*/
Chips *chipsMemeCase(Game *jeu, int lig, int col);





/*
    BUT: Trouver le virus qui se trouve dans la même ligne et colonne passé en paramètre
    PARAM: valeur: numéro du ligne de la colonne où on cherche à trouver si y a un virus
                   qui se trouve au même coordonnées.
           adresse: adresse du jeu
    RETURN: renvoie l'adresse du virus  s'il existe NUll sinon
*/
Virus *virusMemeCase(Game *jeu, int lig, int col);



/*
    BUT: allocation d'un virus spécifique dans la mémoire avec des caractéristiques passées en param
    PARAM: valeur: numéro de ligne et tour et le type de virus qu'on le souhaite allouer.
    RETURN: renvoie l'adresse du virus si tout est bien passé sinon on existe le programme. après avoir
            affiché un message d'erreur.
*/
Virus *alloueVirus(int tour, int ligne, char type);


/*
    BUT: insertion d'un virus dans la liste principale qui les contient 
    PARAM: adresse du jeu principal
           adresse d'une structure virus celui qu'on veut insérer
           un tableau de pointeur dont chaque pointeur est un pointeur vers une structure virus
*/
void insereVirus(Game *jeu, Virus *virus, Virus **tabVirusLigne);


/*
    BUT: intialisation de liste des virus du jeu principal en la remplissant avec des données
         d'un fichier txt en faisant appel a la fonction d'allocation et d'insertion.
    PARAM: adresse du jeu principal
           adresse d'un fichier 
*/
void initialiseVirus(Game *jeu, FILE *fic);



/*
    BUT: affichage des virus par ligne en lisant le fichier en créeant un tableau 
         dynamique qui contiendra le type de chaque virus à chaque tour donnée;
    PARAM: valeur: la ligne qu'on veut afficher
           adresse: adresse du fichier texte
*/
void afficheVagueLigne(FILE *fic, int i);



/*
    BUT: affichage de la vague du jeu selon le fichier texte en faisant appel à la fonction
         qui s'occupe de l'affiche de la vague pour chaque ligne.
    PARAM: adresse: nom du fichier texte content la vague.
*/
void afficheVague(char *nmFic);

/*
    BUT: intialisation du jeu principal en affectant à tous les champs la valeur 0 ou NULL
         avec l'initialisation des virus aussi avec le fichier text passé en argument
    PARAM: adresse du jeu principal et nom du fichier texter contenant la vague.   
*/
void initialiserJeu(Game *jeu, char *nmFic);





/*
    BUT: allocation d'une tourelle  spécifique dans la mémoire avec le type  passé en param
    PARAM: valeur: (char)type de la tourelle qu'on le souhaite allouer.
    RETURN: renvoie l'adresse de la tourelle si tout est bien passé sinon on existe le programme. après avoir
            affiché un message d'erreur.
*/
Chips *alloueTourelle(char choix);



/*
    BUT: vérification si le joueur à l'argent suffisant pour acheter la tourelle dont le type est passé en param
    PARAM: valeur: (char) type de la tourelle choisi par l'utilisateur.
           adresse: adresse de la structure du jeu principal
    RETURN: renvoie 1 si l'utilisateur a la possibilité d'acheter la tourelle 0 sinon et s'il pas choisi une tourelle valide.
*/
int prixsuffisant(Game *jeu, char choix);


/*
    BUT: insertion d'un chips dans la liste principale qui les contient 
    PARAM: adresse du jeu principal
           adresse d'une structure chips celui qu'on veut insérer
*/
void insereChips(Game *jeu, Chips *chips);


/*
    BUT: vérifie si une case (lig, col) passé en paramètre est bien dans le plateau du jeu
    PARAM: (int) la ligne et la colonne qu'on veut vérifier
    RETURN: renvoie 1 si la case est bien dans le tableau 0 sinon
*/
int estDansTableau(int lig, int col);


/*
    BUT: vérifie si une case (lig, col) passé en paramètre est vide dans le plateau du jeu
    PARAM: valeur: (int) la ligne et la colonne qu'on veut vérifier
           adresse: adresse de la structure du jeu principal.
    RETURN: renvoie 1 si la case est bien vide 0 sinon
*/
int positionVide(Game *jeu, int lig, int col);

/*
    BUT: vérifie si une case (lig, col) passé en paramètre est bien valide dans le plateau du jeu
         en faisant appel aux fonctions qui vérfient s'elle est vide et dans le tableau.
    PARAM: valeur: (int) la ligne et la colonne qu'on veut vérifier
           adresse: adresse de la structure du jeu principal.
    RETURN: renvoie 1 si la case est bien valide dans le plateau 0 sinon
*/
int positionValide(Game *jeu, int lig, int col) ;




/*
    BUT: Suppresion d'un virus de la liste des virus
    PARAM: adresse: adresse de la structure du jeu principal.
                    adresse du virus qu'on veut supprimer et celui qui le précéde
    RETURN: renvoie l'adresse du virus supprimé sinon renvoie NULL
*/
Virus *supprimeVirus(Game *jeu, Virus *avant, Virus *virus);



/*
    BUT: libération de liste contenant les virus
    PARAM: adresse: adresse de la structure du jeu principal.
*/
void libereListeVirus(Game *jeu);



/*
    BUT: Suppresion d'un chips de la liste dont les coordonées (line, position) sont passés en param
    PARAM: adresse: adresse de la structure du jeu principal.
           valeur: (int) ligne et colonne du chips qu'on veut supprimer
    RETURN: renvoie l'adresse du chips supprimé sinon renvoie NULL
*/
Chips *supprimeChips(Game *jeu, int lig, int col);


/*
    BUT: libération de liste contenant les chips
    PARAM: adresse: adresse de la structure du jeu principal.
*/
void libereListeChips(Game *jeu);


/*
    BUT: fonction responsable de renvoyer le chips qui est au début de la ligne passé en paramètre
    PARAM: adresse: adresse de la structure du jeu principal.
           valeur: (int) la ligne où on cherche le premier chips
    RETURN: renvoie l'adresse du chips sinon renvoie NULL
*/
Chips *chipsDebutLigne(Game *jeu, int lig);


/*
    BUT: fonction responsable de renvoyer le virus qui est au début de la ligne passé en paramètre
    PARAM: adresse: adresse de la structure du jeu principal.
           valeur: (int) la ligne où on cherche le premier virus
    RETURN: renvoie l'adresse du virus sinon renvoie NULL
*/
Virus *virusDebutLigne(Game *jeu, int lig);

/*
    BUT: fonction responsable de renvoyer le précédent du virus passé en paramètre
    PARAM: adresse: adresse de la structure du jeu principal et du virus à qui on cherche le précedent
    RETURN: renvoie l'adresse du virus précédentn
*/
Virus *avantVirus(Game *jeu, Virus *virus);


/*
    BUT: fonction responsable de'accélérer un virus en diminuant sa position d'un.
    PARAM: adresse: adresse de la structure du jeu principal et du virus que l'on veut accélérer.
           valeur: (int) la ligne où se trouve le virus que l'on veut accélérer.
*/
void accelereVirusLigne(Game *jeu, Virus *virus, int lig);

/*
    BUT: fonction qui s'occupe des caractéristiques du virus de type D qui est responsable d'accélérer le premier 
         de sa ligne ainsi que les deux premieres des lignes voisines en faisant appel à la fonction d'acceleration.
    PARAM: adresse: adresse de la structure du jeu principal et du virus de ce type.
*/
void virusTypeD(Game *jeu, Virus *virus);


/*
    BUT: fonction qui s'occupe des caractéristiques du virus de type B qui est responsable d'ajouter 1
         à la vie du virus qui se trouve derrière et devant lui 
    PARAM: adresse: adresse de la structure du jeu principal et du virus de ce type.
*/
void virusTypeB(Game *jeu, Virus *virus);



/*
    BUT: fonction qui mis à jour la vie du virus qui se trouve au début de chaque ligne  selon le type de
         chips qui se trouve au début sur la même ligne passé en param
    PARAM: adresse: adresse de la structure du jeu principal 
           valeur: (int) ligne où on veut faire la mise à jour de la vie des virus.
*/
void updateLifeVirusDevant(Game *jeu, int lig);



/*
    BUT: fontion qui est responsable de la mise à jour de tous les virus selon leur types et en faisant
            appel aux fonction responsable de chaque type et la mise à jour des virus qui se trouve au début de chaque ligne
    PARAM: adresse: adresse de la structure du jeu principal 
*/
void updateInfoVirus(Game *jeu);




/*
    BUT:  fonction responsable de mettre à jour la vie des chips selon les virus qui se trouve au début de chaque ligne
    PARAM: valeur: (char) mode du jeu
           adresse: adresse de la structure du jeu principal
*/
void updateInfoChips(Game *jeu, char mode);




/*
    BUT: fonction prenant en paramètre une case et renvoyant le chips qui se trouve à ces coordonnées
    PARAM: adresse: adresse de la structure du jeu principal 
           valeur: (int) ligne et colonne du chips que l'on cherche
    RETURN: renvoie le chips au cas où il est bien dans la liste NULL sinon
*/
Chips *detecterChipsLigne(Game *jeu, int lig, int col);

/*
    BUT: fonction responsable de l'initialisation des positions des virus 
    PARAM: adresse: adresse de la structure du jeu principal 
*/
void apparaitreVirus(Game *jeu);



/*
    BUT: fonction responsable du mouvement des virus en prenant compte la vitesse de chaque virus qui suit le virus 
         actuel et en initialisant leur positions.
    PARAM: adresse: adresse de la structure du jeu principal 
*/
void moveVirus(Game *jeu);




/*
    BUT:  fonction supprimant tous les virus morts en détectant si leur vie égal à 0
    PARAM: valeur: (char) mode du jeu
           adresse: la structure du jeu principal
*/
void supprimeVirusMort(Game *jeu, char mode);


/*
    BUT:  fonction supprimant tous les chips morts en détectant si leur vie égal à 0
    PARAM: valeur: (char) mode du jeu
           adresse: la structure du jeu principal
*/
void supprimeChipsMort(Game *jeu, char mode);


/*
    BUT: fonction responsable de la détection de la fin de la partie 
    PARAM: adresse: adresse de la structure du jeu principal 
    RETURN: renvoie 1 si la partie est finie 0 sinon.
*/
int finPartie(Game *jeu);







#endif