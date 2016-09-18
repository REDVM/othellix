#ifndef __affichage__
#define __affichage__

#include "callbacks.h"

//Initialise les images necessitees par le programme
void initImages(partie* Partie);

//Affiche la fenetre de l'application.
void affichageFenetre(partie* Partie);

//Ajoute un texte dans la barre de status (ou barre d'état).
void pushStatusBar(partie* Partie, char* txt);

//on reactualise le score
void affichageScore(partie* Partie);

//On met les cases à cocher comme il faut.
void affichagePreferencesAffichage(partie* Partie);

//Affiche le dernier coup joué.
void affichageDernierCoup(partie* Partie, GtkWidget* canvas);

//Initialise la fenetre d'aide.
void affichageRegles(partie* Partie);

#endif
