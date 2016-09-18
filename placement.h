#ifndef __placement__
#define __placement__

/* Renvoie True si le coup est jouable et False sinon */
bool jouable(partie* Partie, int position);

bool jouable2(partie* Partie, int position);

/* 
 * Ajoute les coups jouables par le joueur connu au plateau de jeu.
 * A appliquer au début du tour d'un joueur, avant l'affichage du plateau.
 * Renvoie True s'il y a au moins un coup jouable, False sinon
 */
bool ajouterCoupsJouables(partie* Partie);

/* 
 * Retire tous les coups jouables du plateau
 * A appliquer à la fin du tour d'un joueur.
 */
void enleverCoupsJouables(partie* Partie);

/*
 * Remplit le tableau pos de tous les coups jouables pour 
 * le joueur actuel. La dernière case du tableau contient 
 * la valeur -1.
 */
void coupsJouables(partie* Partie, int pos[NB_COUPS]);

#endif
