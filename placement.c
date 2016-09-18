#include "main.h"

/* Définition des 8 directions */	
int dir[8] = {HAUT, BAS, GAUCHE, DROITE, HAUT+GAUCHE, 
	              BAS+DROITE, BAS+GAUCHE, HAUT+DROITE};

bool jouable(partie* Partie, int position)
{
	int i, pos;
	
	/* Si la case concernée n'est pas vide, le coup n'est pas jouable */
	if (plateau[position] != VIDE)
		return False;
	
	for (i=0; i<8; i++)
	{
		/* On regarde le voisin de la position du coup que l'on veut jouer */
		pos = position + dir[i];
		/* S'il s'agit d'un pion de l'adversaire */
		
		/* Supprimer le if ?*/
		
		if (plateau[pos] == !couleurActuelle)
		{
			/* On se déplace jusqu'au bout de la série des pions adverses */
			while (plateau[pos] == !couleurActuelle)
				pos += dir[i];
			/* Si le pion qui suit est un pion du joueur, alors le coup est jouable */
			if (plateau[pos] == couleurActuelle)
				return True;
		}
	}
	
	/* Si on arrive là, c'est que le coup n'est pas jouable */
	return False;
}

bool ajouterCoupsJouables(partie* Partie)
{
	int i;
	bool auMoinsUn = False, res;
 	
 	GTimer* chrono = g_timer_new();
	
	
	/* On parcourt tout l'othellier (sauf la première et la dernière ligne) */
	for (i=TAILLE+1; i<TAILLE*(TAILLE-1)-1; i++)
	{
		if (jouable(Partie, i))
		{
			plateau[i] = JOUABLE;
			auMoinsUn = True;
		}
		if (i%TAILLE == TAILLE-2)
			i+=2;
	}
	
	return auMoinsUn;
}

void enleverCoupsJouables(partie* Partie)
{
	int i;
	
	/* On parcourt tout l'othellier (sauf la première et la dernière ligne) */
	for (i=TAILLE; i<TAILLE * (TAILLE-1); i++)
		/* On met les cases JOUABLE à VIDE */
		if (i % TAILLE != 0 && i % TAILLE != 9 && plateau[i] == JOUABLE)
			plateau[i] = VIDE;
}

void coupsJouables(partie* Partie, int pos[NB_COUPS])
{
	int i, i_pos = 0;
	for (i=TAILLE+1; i<TAILLE*(TAILLE-1)-1; i++)
	{
		if (jouable(Partie, i))
		{
			pos[i_pos] = i;
			i_pos++;
		}
	}
	
	pos[i_pos] = -1;
}