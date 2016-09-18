#ifndef __evaluation__
#define __evaluation__

/* 
 * Renvoie un score correspondant au plateau actuel.
 * Plus le score est élevé, plus la configuration est favorable au joueur.
 */
float evaluation(partie* Partie, int couleur);

/*
 * Renvoie la différence entre le nombre de pions du joueur et 
 * le nombre de pions de son adversaire.
 */
int pions(partie* Partie);

/*
 * Renvoie la différence entre le nombre de coins du joueur et
 * le nombre de coins de son adversaire.
 */
int coins(partie* Partie);

/*
 * Renvoie la différence entre le nombre de cases jouables par le
 * joueur et le nombre de cases jouables par son adversaire.
 */
int mobilite(partie* Partie);

/*
 * Renvoie la différence entre le nombre de pions définitifs du
 * joueur et le nombre de pions définitifs de son adversaire.
 */
int pionsDefinitifs(partie* Partie);

/* Ajoute un pion défintif au tableau tab s'il n'y est pas déjà. */
void ajoutePosDefinitive(int tab[NB_COUPS+5], int pos, int* nbPionsDefinitifs);

/* Renvoie 1 si la parité est favorable au joueur et -1 sinon. */
int parite(partie* Partie);

#endif