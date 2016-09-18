#ifndef __CPU__
#define __CPU__

/*
 * Algorithme MinMax.
 * Prend en argument la profondeur de calcul souhaitée, la couleur
 * du joueur actuel, un pointeur sur le meilleur coup et la partie.
 * Renvoie le score obtenue par le meilleur coup.
 */
int MinMax(int profondeur, const int couleur, int* meilleur, partie* Partie);

/*
 * Algorithme NegaMax.
 * Il s'agit d'une autre écriture de l'algorithme MinMax (plus courte).
 */
int Negamax(int profondeur, const int couleur, int* meilleur, partie* Partie);

/*
 * Algorithme AlphaBeta.
 * Amélioration de MinMax par élagage alpha-beta.
 * La fonction doit être appelée avec alpha = -INFINI_f et beta = INFINI_f.
 */
float AlphaBeta(int profondeur, const int couleur, int* meilleur, partie* Partie, float alpha, float beta);

/* 
 * Amélioration de AlphaBeta (variation Principal Variation Search). 
 * !!! Pas encore valide !!!
 */
int NegaScout(int profondeur, const int couleur, int* meilleur, partie* Partie, int alpha, int beta);

#endif
