#ifndef __renversement__
#define __renversement__

/* Remplit le tableau pionsRetournables du coup, et retournes les pions. */
void compterPions(partie* Partie);

/* 
 * Retourne le nombre des pions indiqué dans le tableau.
 * Utilisée dans la fonction rejouerCoup(), effectue moins de calculs que
 * compterPions().
 */
void renverserPions(partie* Partie);

/*
 * Retourne le nombre de pions indiqué dans le tableau, et actualise les scores en tenant compte 
 * du fait qu'il s'agit de l'annulation d'un coup.
 */
void renverserPionsAnnulation(partie* Partie);

#endif
