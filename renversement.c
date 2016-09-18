#include "main.h"

extern int dir[8];

void compterPions(partie* Partie)
{
	int i, j, pos;
	
	for (i=0; i<8; i++)
	{
		/* On initialise la valeur du tableau et la position */
		coupActuel.pionsRetournables[i] = 0;
		pos = positionActuelle + dir[i];
		/* Tant qu'on rencontre un pion adverse, on avance dans la direction */
		while (plateau[pos] == !couleurActuelle)
		{
			coupActuel.pionsRetournables[i]++;
			pos += dir[i];
		}
		/* Si au final on ne trouve pas un pion du joueur, c'est qu'on ne peut pas 
		   retourner de pion */
		if (plateau[pos] != couleurActuelle)
			coupActuel.pionsRetournables[i] = 0;
			
		/* On retourne le nombre de pions indiqué dans le tableau, en revenant 
		   en arrière. */
		for (j=0; j<coupActuel.pionsRetournables[i]; j++)
		{
			pos -= dir[i];
			plateau[pos] = !plateau[pos];
			score[couleurActuelle]++;
			score[!couleurActuelle]--;
		}
	}
}

void renverserPions(partie* Partie)
{
	int i, ret, pos;
	
	for (i=0; i<8; i++)
	{
		/* Initialisation de la position */
		pos = positionActuelle + dir[i];
		for (ret=0; ret<coupActuel.pionsRetournables[i]; ret++)
		{
			/* On retourne le pion */
			plateau[pos] = !plateau[pos];
			/* On actualise les scores */
			score[couleurActuelle]++;
			score[!couleurActuelle]--;
			/* On modifie la position */
			pos += dir[i];
		}
	}
}


void renverserPionsAnnulation(partie* Partie)
{
	int i, ret, pos;
	
	for (i=0; i<8; i++)
	{
		/* Initialisation de la position */
		pos = positionActuelle + dir[i];
		for (ret=0; ret<coupActuel.pionsRetournables[i]; ret++)
		{
			/* On retourne le pion */
			plateau[pos] = !plateau[pos];
			/* On actualise les scores */
			score[couleurActuelle]--;
			score[!couleurActuelle]++;
			/* On modifie la position */
			pos += dir[i];
		}
	}
}
