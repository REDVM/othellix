#ifndef __init__
#define __init__

/* Initialise une partie. */
void initPartie(partie* Partie, int nbJoueurs, bool newPartie);


//Initialise les préférences d'affichage.
void initPreferences(partie* Partie);



//Initialise les joueurs
void initJoueurs(partie* Partie);
void initJoueurHumain(joueur* Joueur, int numero);
void initJoueurCPU(joueur* Joueur, int niveau);
void initCoefficients(float coef[NB_DECOUPAGES][NB_COEFS]);

/* Initialise l'othellier. */
void initOthellier(partie* Partie);

void initMessages(char tab[][200]);


#endif
