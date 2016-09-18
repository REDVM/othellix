#include "main.h"

extern int nb_calculs[2];
		
float evaluation(partie* Partie, int couleur)
{
	nb_calculs[1]++;
	
	/* indice permet de choisir les bons coefficients en fonction de 
	 * l'avancement de la partie. */
	int i, indice;
	float val[5], somme = 0;
	
	indice = (Partie->numeroCoupActuel-Partie->Joueur[couleur].niveau)/(NB_COUPS/NB_DECOUPAGES);
	/* Stockage des coefficients */
	for (i=0; i<NB_COEFS; i++)
	{
		val[i] = (float)Partie->Joueur[couleurActuelle].coef[indice][i];
		//printf("%lf ", val[i]);
	}
	//printf("\n");
		
	/* Attributions des valeurs par rapport aux critères */
	val[0] *= pions(Partie);
	val[1] *= coins(Partie);
	val[2] *= mobilite(Partie);
	val[3] *= pionsDefinitifs(Partie);
	val[4] *= parite(Partie);
	
	/* Calcul de la somme */
	for (i=0; i<NB_COEFS; i++)
		somme += val[i];
		
	return somme;
}

int pions(partie* Partie)
{
	return score[couleurActuelle] - score[!couleurActuelle];
}

int coins(partie* Partie)
{
	int i, posCoins[4] = {11, 18, 81, 88}, nb_coins = 0;
	
	for (i=0; i<4; i++)
	{
		if (plateau[posCoins[i]] == couleurActuelle)
			nb_coins++;
		else if (plateau[posCoins[i]] == !couleurActuelle)
			nb_coins--;
	}
		
	return nb_coins;
}

int mobilite(partie* Partie)
{
	int mobiliteJoueur = 0, mobiliteAdversaire = 0, i;
	
	for (i=TAILLE+1; i<TAILLE * (TAILLE-1) - 1; i++)
	{
		if (plateau[i] == VIDE)
		{
			/* Si le joueur peut poser un pion à cet endroit : */
			if (jouable(Partie, i))
				mobiliteJoueur++;
			/* Sinon, on regarde si son adversaire en a la possibilité : */
			else
			{
				couleurActuelle = !couleurActuelle;
				if (jouable(Partie, i))
					mobiliteAdversaire++;
				couleurActuelle = !couleurActuelle;
			}
		}
	}
	
	return mobiliteJoueur - mobiliteAdversaire;
}

int pionsDefinitifs(partie* Partie)
{
	int i, j, k;
	int posCoins[4] = {11, 18, 81, 88};
	/* Définit les directions dans lesquelles on peut se déplacer à partir d'un coin. */
	int dirCoins[4][2] = {{DROITE, BAS},
	                      {GAUCHE, BAS},
	                      {DROITE, HAUT},
	                      {GAUCHE, HAUT}};
	int couleurCoin, posH, posV, pos;
	int posPionsDefinitifs[2][NB_COUPS+5];
	int nbPionsDefinitifs[2] = {0, 0};
	int pionsLigne = 0, pionsColonne = 0, maxLigne, maxColonne;
	
	posPionsDefinitifs[0][0] = -1;
	posPionsDefinitifs[1][0] = -1;

	/* Pour chaque coin */
	for (i=0; i<4; i++)
	{
		/* On définit la couleur de coin. */
		couleurCoin = plateau[posCoins[i]];
		maxLigne = TAILLE-1;
		maxColonne = TAILLE-1;
				
		/* Si le coin n'est pas vide : */
		if (couleurCoin != VIDE)
		{
			/* Pour chaque pion de la demi-diagonale */
			for (j=0; j<4; j++)
			{
				pos = posCoins[i] + j*(dirCoins[i][0] + dirCoins[i][1]);
				posH = pos;
				posV = pos;
				pionsLigne = 0;
				pionsColonne = 0;
		
				/* Si le pion est vide, on passe au prochain coin. */
				if (plateau[pos] != couleurCoin)
					break;
				
				/* Si le pion est définitif, on l'ajoute à la liste. */
				if (maxLigne > 1 && maxColonne > 1)
					ajoutePosDefinitive(posPionsDefinitifs[plateau[pos]], pos, &nbPionsDefinitifs[plateau[pos]]);
				
				/* Pour chaque pion de la ligne : */
				for (k=j+1; k<TAILLE-2; k++)
				{
					/* On se déplace horizontalement. */
					posH += dirCoins[i][0];
					/* Si on rencontre un pion qui n'est pas définitif, on s'arrête. */
					if (plateau[posH] != couleurCoin || k - (j-2) > maxLigne)
						break;
					
					/* On ajoute le pion à la liste. */
					ajoutePosDefinitive(posPionsDefinitifs[couleurCoin], posH, &nbPionsDefinitifs[couleurCoin]);
					pionsLigne++;
				}
			
				/* Pour chaque pion de la colonne */
				for (k=j+1; k<TAILLE-2; k++)
				{
					/* Idem que pour les pions de la ligne. */
					posV += dirCoins[i][1];
					if (plateau[posV] != couleurCoin || k - (j-2) > maxColonne)
						break;
					
					ajoutePosDefinitive(posPionsDefinitifs[couleurCoin], posV, &nbPionsDefinitifs[couleurCoin]);
					pionsColonne++;
				}
			
				/* On actualise les maximas locaux. */
				maxLigne = pionsLigne;
				maxColonne = pionsColonne;
			}
		}
	}
	
	return nbPionsDefinitifs[couleurActuelle] - nbPionsDefinitifs[!couleurActuelle];
}

void ajoutePosDefinitive(int tab[NB_COUPS+5], int pos, int* nbPionsDefinitifs)
{
	int i;
	bool present = False;
	
	/* On cherche le pion dans le tableau */
	for (i=0; i<NB_COUPS+5 && tab[i] != -1; i++)
		if (tab[i] == pos)
			present = True;
			
	/* S'il n'y est pas, on l'y ajoute. */
	if (!present)
	{
		tab[i] = pos;
		tab[i+1] = -1;
		(*nbPionsDefinitifs)++;
	}
}

int parite(partie* Partie)
{
	return (Partie->numeroCoupActuel%2) * 2 - 1;
}
