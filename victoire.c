#include "main.h"

bool plateauRempli(partie* Partie)
{
	return score[NOIR] + score[BLANC] >= NB_COUPS + 4;
}

bool pasDePion(partie* Partie, int joueur)
{
	return score[joueur] == 0;
}

int victoire(partie* Partie)
{
	if (pasDePion(Partie, NOIR))
		return BLANC;
	else if (pasDePion(Partie, BLANC))
		return NOIR;
	else if (plateauRempli(Partie))
		if (score[NOIR] > score[BLANC])
			return NOIR;
		else if (score[BLANC] > score[NOIR])
			return BLANC;
		else
			return EGALITE;
	else
		return PAS_FINI;
}

void rajouterCasesVides(partie* Partie)
{
	int i, nbCasesVides = 0;
	
	for (i=TAILLE; i<(TAILLE-1)*TAILLE; i++)
		if (plateau[i] == VIDE)
			nbCasesVides++;
			
	if (score[NOIR] > score[BLANC])
		score[NOIR] += nbCasesVides;
	else if (score[BLANC] > score[NOIR])
		score[BLANC] += nbCasesVides;
	else
	{
		score[NOIR] += nbCasesVides/2;
		score[BLANC] += nbCasesVides/2;
	}
}

