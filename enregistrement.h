#ifndef __enregistrement__
#define __enregistrement__

/* 
 * Sauvegarde une partie dans le fichier "sauvegardeOthellix.data".
 * Renvoie False en cas d'erreur.
 */
bool sauvegarder(partie* Partie);


/* 
 * Charge la partie stockée dans le fichier "sauvegardeOthellix.data".
 * Renvoie False en cas d'erreur.
 */
bool chargerPartie(partie* Partie);

/* 
 * Charge les coefficients pour la fonction d'évaluation à partir
 * du fichier "coefficients.data".
 */
bool chargerCoefficients(float coef[NB_DECOUPAGES][NB_COEFS]);

/* 
 * Calcule le niveau d'un joueur contrôlé par ordinateur
 * à partir de son nom.
 */
int niveau(const char* nom);

/* Détermine si un joueur est contrôlé par l'ordinateur ou non. */
bool cpu(const char* nom);

#endif
