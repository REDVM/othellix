#ifndef __evaluation__
#define __evaluation__

/* Renvoie True si le tableau est rempli et False sinon. */
bool plateauRempli(partie* Partie);

/* Renvoie True si le joueur n'a plus de pion. */
bool pasDePion(partie* Partie, int joueur);

/*
 * Renvoie NOIR si le joueur qui a les pions noirs a gagné,
 * BLANC si le joueur qui a les pions blancs a gagné, 
 * EGALITE si la partie s'est terminée avec un score identique
 * pour les deux joueurs et PAS_FINI si la partie n'est
 * pas terminée.
 */
int victoire(partie* Partie);

/*
 * Comptabilise le nombre de cases vides du plateau et les
 * ajoute au score du joueur qui mène la partie.
 * En cas d'égalite, chaque joueur se voit attribuer la
 * moitié des cases vides.
 */
void rajouterCasesVides(partie* Partie);

#endif
