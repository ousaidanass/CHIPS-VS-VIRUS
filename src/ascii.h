#ifndef ASCII_H
#define ASCII_H





/*
    BUT: demande à l'utilisateur de choisir une tourelle avec la ligne et la colonne qu'il veut
        en vérifiant si les coordonnées et le type choisi sont bien valides et on l'insére dans le tableau
        si c'est bien le cas.
    PARAM: adresse: adresse de la structure du jeu principal.
*/
void choixTourelle(Game *jeu);


/*
    BUT: affichage d'une ligne du plateau selon des conditions spécifiques en allouant deux tableaux contenant
         les virus et chips du jeu au cas où une position du tableau est vide on affiche rien sinon on affiche 
         le contenu de la case en prenant en considérant les cas de collisions.
    PARAM: valeur: (int) la ligne du plateau du jeu à afficher
           adresse: adresse de la structure du jeu principal
*/
void affichePlateauLigne(Game *jeu, int lig);


/*
    BUT: affichage du plateau du jeu en terminal et le numéro du tour aussi en faisant appel à la fonction
         s'occupant de l'affichage de chaque ligne du plateau.
    PARAM: adresse: adresse de la structure du jeu principal
*/
void affichePlateauAscii(Game *jeu);


/*
    BUT: fonction responsable de l'affichade du jeu en mode terminal où on demande  à l'utilisateur son choix tant qu'il veut
         sinon s'il veut commencer le jeu on quitte la fonction
    PARAM: adresse: adresse de la structure du jeu principal et du nom fichier texte contenant la vague
*/
void affichageJeuTerminal(Game *jeu, char*nmFic);


/*
    BUT:  foonction du mode terminal 
    PARAM: adresse: nom du fichier texte contenant la vague
*/
void ascii(char *nomFic);


#endif
