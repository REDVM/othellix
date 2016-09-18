#include "main.h"

int nb_calculs[2];

int MinMax(int profondeur, const int couleur, int* meilleur, partie* Partie)
{
	int i, j, jouables[NB_COUPS], pt_meilleur;
	int meilleur_score, score_actuel;

	/* Si la partie est finie */
	int gagnant = victoire(Partie);
	switch(gagnant)
	{
		case NOIR:
		case BLANC:
			return couleur == gagnant ? INT_MAX : INT_MIN;
		case EGALITE:
			return 0;
		default:
			break;
	}
	
	/* Si on atteint la profondeur max, on appelle la fonction d'évaluation */
	if (profondeur <= 0)
		return evaluation(Partie, couleur);
	
	coupsJouables(Partie, jouables);
	
	/* Le coup est la couleur du joueur ayant appelé la fonction : on cherche le MAX */
	if (couleur == couleurActuelle)
	{
		//printf("On cherche le MAX\n");
		meilleur_score = -INFINI;
		if (jouables[0] != -1)
		{
			*meilleur = jouables[0];
			for (i=0; i < NB_COUPS && jouables[i] != -1; i++)
			{
				/* On joue le coup */
				positionActuelle = jouables[i];
				placerPion_opt(Partie);
					
  				/* On effectue l'appel récursif */
  				score_actuel = MinMax(profondeur-1, couleur, &pt_meilleur, Partie);
  					
  				/* On enlève le coup */
  				annulerCoup_opt(Partie);
				
				if (score_actuel > meilleur_score)
				{
					meilleur_score = score_actuel;
					*meilleur = jouables[i];
  				}
  			}
  		}
  		/* Si on ne peut pas jouer, On appelle la fonction avec la couleur adverse. */
  		else if (!Partie->tourPasse)
  		{
  			Partie->tourPasse = True;
  			couleurActuelle = !couleurActuelle;
  			return MinMax(profondeur, couleur, &pt_meilleur, Partie);
  		}
  		/* Si l'adversaire n'a pas pu jouer non plus */
  		else
  		{
  			if (score[NOIR] == score[BLANC])
  				return 0;
  			else if (score[NOIR] > score[BLANC])
  				return couleur == NOIR ? INFINI : -INFINI;
  			else
  				return couleur == BLANC ? INFINI : -INFINI;
  		}
  	}
  	/* Le coup est la couleur du joueur adverse : on cherche le MIN */
  	else
  	{
		meilleur_score = INFINI;
		if (jouables[0] != -1)
  		{
  			*meilleur = jouables[0];
			for (i=0; jouables[i] != -1 && i < NB_COUPS; i++)
  			{
				/* On joue le coup */
				positionActuelle = jouables[i];
				placerPion_opt(Partie);
  					
  				/* On effectue l'appel récursif */
  				score_actuel = MinMax(profondeur-1, couleur, &pt_meilleur, Partie);
  					
  				/* On enlève le coup */
  				annulerCoup_opt(Partie);
				
				if (score_actuel < meilleur_score)
				{
					meilleur_score = score_actuel;
					*meilleur = jouables[i];
  				}
  			}
  		}
  		else if (!Partie->tourPasse)
  		{
  			Partie->tourPasse = True;
  			couleurActuelle = !couleurActuelle;
  			return MinMax(profondeur, couleur, &pt_meilleur, Partie);
  		}
  		else
  		{
  			if (score[NOIR] == score[BLANC])
  				return 0;
  			else if (score[NOIR] > score[BLANC])
  				return couleur == NOIR ? INFINI : -INFINI;
  			else
  				return couleur == BLANC ? INFINI : -INFINI;
  		}
  	}
  	
  	return meilleur_score;
}

int Negamax(int profondeur, const int couleur, int* meilleur, partie* Partie)
{
	int i, jouables[NB_COUPS], pt_meilleur;
	int meilleur_score = -INFINI, score_actuel;

	int gagnant = victoire(Partie);
	switch(gagnant)
	{
		case NOIR:
		case BLANC:
			return couleur == gagnant ? INFINI : -INFINI;
		case EGALITE:
			return 0;
		default:
			break;
	}
	
	if (profondeur <= 0)
		return (int)(10.0*evaluation(Partie, couleur));
	
	coupsJouables(Partie, jouables);
		
	if (jouables[0] != -1)
	{
		*meilleur = jouables[0];
		for (i=0; i < NB_COUPS && jouables[i] != -1; i++)
		{
			positionActuelle = jouables[i];
			placerPion_opt(Partie);
			score_actuel = -Negamax(profondeur-1, couleur, &pt_meilleur, Partie);
  			annulerCoup_opt(Partie);
				
			if (profondeur == 7)
				printf("%c%c => %d\n", jouables[i]%10 + 'A' - 1, jouables[i]/10 + '0', score_actuel);
				
			if (score_actuel > meilleur_score)
			{
				meilleur_score = score_actuel;
				*meilleur = jouables[i];
			}
  		}
  	}
  	else if (!Partie->tourPasse)
  	{
  		Partie->tourPasse = True;
  		couleurActuelle = !couleurActuelle;
  		return -Negamax(profondeur, couleur, &pt_meilleur, Partie);
  	}
  	else
  	{
  		if (score[NOIR] == score[BLANC])
  			return 0;
  		else if (score[NOIR] > score[BLANC])
  			return couleur == NOIR ? INFINI : -INFINI;
  		else
  			return couleur == BLANC ? INFINI : -INFINI;
  	}
  	
  	return meilleur_score;
}

float AlphaBeta(int profondeur, const int couleur, int* meilleur, partie* Partie, float alpha, float beta)
{
	nb_calculs[0]++;
	
	int i, jouables[NB_COUPS], pt_meilleur;
	float score_actuel;

	int gagnant = victoire(Partie);
	switch(gagnant)
	{
		case NOIR:
		case BLANC:
			return couleur == gagnant ? INFINI_f : -INFINI_f;
		case EGALITE:
			return 0;
		default:
			break;
	}
	
	if (profondeur <= 0)
		return evaluation(Partie, couleur);
	
	coupsJouables(Partie, jouables);
	
	if (jouables[0] != -1)
	{
		*meilleur = jouables[0];
		for (i=0; i < NB_COUPS && jouables[i] != -1; i++)
		{
			positionActuelle = jouables[i];
			
			placerPion_opt(Partie);
  			score_actuel = -AlphaBeta(profondeur-1, couleur, &pt_meilleur, Partie, -beta, -alpha);
  			annulerCoup_opt(Partie);
  			
  			if (score_actuel >= alpha)
			{
				if (score_actuel != alpha)
					*meilleur = jouables[i];
				alpha = score_actuel;
				if (alpha >= beta)
					break;
			}
  		}
  	}
  	else if (!Partie->tourPasse)
  	{
  		Partie->tourPasse = True;
  		couleurActuelle = !couleurActuelle;
  		return -AlphaBeta(profondeur, couleur, &pt_meilleur, Partie, -beta, -alpha);
  	}
  	else
  	{
  		if (score[NOIR] == score[BLANC])
  			return 0;
  		else if (score[NOIR] > score[BLANC])
  			return couleur == NOIR ? INFINI_f : -INFINI_f;
  		else
  			return couleur == BLANC ? INFINI_f : -INFINI_f;
  	}
  	
  	return alpha;
}

int NegaScout(int profondeur, const int couleur, int* meilleur, partie* Partie, int alpha, int beta)
{
	int i, jouables[NB_COUPS], pt_meilleur;
	int score_actuel, courant;

	int gagnant = victoire(Partie);
	switch(gagnant)
	{
		case NOIR:
		case BLANC:
			return couleur == gagnant ? INFINI : -INFINI;
		case EGALITE:
			return 0;
		default:
			break;
	}
	
	if (profondeur <= 0)
		return evaluation(Partie, couleur);
	
	coupsJouables(Partie, jouables);
	
	if (jouables[0] != -1)
	{
		/* On joue le premier coup */
		*meilleur = jouables[0];
		positionActuelle = jouables[0];
		placerPion_opt(Partie);
		courant = -NegaScout(profondeur-1, couleur, &pt_meilleur, Partie, -beta, -alpha);
		annulerCoup_opt(Partie);
		
		if (profondeur == 7)
			printf("%c%c => %d\n", jouables[0]%10 + 'A' - 1, jouables[0]/10 + '0', courant);
		
		if (courant >= alpha)
			alpha = courant;
		if (courant < beta)
		{
			for (i=1; i<NB_COUPS && jouables[i] != -1; i++)
			{
				positionActuelle = jouables[i];
				placerPion_opt(Partie);
				score_actuel = -NegaScout(profondeur-1, couleur, &pt_meilleur, Partie, -(alpha+1), -alpha);
				annulerCoup_opt(Partie);
				
				if (profondeur == 7)
					printf("%c%c => %d\n", jouables[i]%10 + 'A' - 1, jouables[i]/10 + '0', score_actuel);
				
				if (score_actuel >= courant)
				{
					if (courant != score_actuel)
						*meilleur = jouables[i];
					courant = score_actuel;
					if (score_actuel >= alpha)
					{
						alpha = score_actuel;
						if (score_actuel >= beta)
							break;
					}
				}
			}
		}
	}
	else if (!Partie->tourPasse)
  	{
  		Partie->tourPasse = True;
  		couleurActuelle = !couleurActuelle;
  		return -NegaScout(profondeur, couleur, &pt_meilleur, Partie, -beta, -alpha);
  	}
  	else
  	{
  		if (score[NOIR] == score[BLANC])
  			return 0;
  		else if (score[NOIR] > score[BLANC])
  			return couleur == NOIR ? INFINI : -INFINI;
  		else
  			return couleur == BLANC ? INFINI : -INFINI;
  	}
  	
  	return courant;
}

