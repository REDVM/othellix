#include "main.h"

bool sauvegarder(partie* Partie){
   
	int i;
   
	FILE* sauvegarde = NULL;
	sauvegarde = fopen("sauvegardeOthellix.data", "w");
	int position, i_noir;
	
	if (sauvegarde == NULL)
		return False;
		
	/* Si les couleurs sont inversées, on les remet (pour la position de départ). */
	if (Partie->inverse)
	{
		inverserCouleur(Partie);
		Partie->inverse = True;
	}
		
	/* Si la partie n'a pas été commencée */
	if (Partie->numeroCoupActuel == 0)
		fprintf(sauvegarde, " ");
	/* Sinon */
	else
	{
		for(i=0 ; i < Partie->numeroCoupActuel ; i++){ //On va lister tous les coups enregistrés
			
			position = Partie->Coup[i].position; //Position du coup etudié.
		
			fprintf(sauvegarde, "%c", Partie->Coup[i].couleur ? '-' : '+');
			fprintf(sauvegarde, "%c", position % TAILLE + 'A' - 1);
			fprintf(sauvegarde, "%c", position / TAILLE + '0');
		}
	}
       
    /* On calcule l'indice du joueur ayant les pions noirs. */
	i_noir = Partie->Joueur[0].couleur == NOIR ? 0 : 1;
	//Maintenant on écrit le score et les noms de joueurs. 
	fprintf(sauvegarde, ": %d %s %s", Partie->statut ? -99 : score[NOIR]-score[BLANC], Partie->Joueur[i_noir].nom, Partie->Joueur[(i_noir+1)%2].nom);
	fclose(sauvegarde);
	
	/* Si on a modifié les couleurs, on les rétablit. */
	if (Partie->inverse)
		inverserCouleur(Partie);
	
	return True;
}

bool chargerPartie(partie* Partie){
	int i = 0, j;
	char test[10];
	FILE* sauvegarde = NULL;
	sauvegarde = fopen("sauvegardeOthellix.data", "r");
   
	char coupsSauvegarde[500];
	int SCORE;
	
	if (sauvegarde == NULL) //Si le fichier n'existe pas, on quitte la fonction
		return False;
	fscanf(sauvegarde, "%[^:]: %d %s %[^EOF]", coupsSauvegarde, &SCORE, Partie->Joueur[0].nom, Partie->Joueur[1].nom);
	/* Remplissage des structures joueur */
	Partie->nbJoueurs = 2;
	Partie->Joueur[0].couleur = NOIR;
	Partie->Joueur[1].couleur = BLANC;
	
	for (i=0; i<2; i++)
	{
		if (cpu(Partie->Joueur[i].nom))
		{
			Partie->Joueur[i].type = CPU;
			Partie->Joueur[i].niveau = niveau(Partie->Joueur[i].nom);
			Partie->nbJoueurs--;
		}
		else
		{
			Partie->Joueur[i].type = HUMAIN;
			Partie->Joueur[i].niveau = 0;
		}
	}
		
	Partie->statut = SCORE == -99;
		
	/* Si la partie n'a pas été commencée */
	if (strlen(coupsSauvegarde) < 3)
		couleurActuelle = NOIR;
	/* Sinon */
	else
	{
		i = 0;
		while (coupsSauvegarde[i] != '\0'){  //On va prendre les positions (par ex : D3) et on va les placer.
			
			couleurActuelle = coupsSauvegarde[i] == '+' ? NOIR : BLANC;
			positionActuelle = (coupsSauvegarde[i+2] - '0')*TAILLE + (coupsSauvegarde[i+1] - 'A' + 1); 
		
			plateau[positionActuelle] = JOUABLE; //On sait que ce que l'on a deja joué avant la sauvegarde sont des emplacements possibles.
		
			/* On place le pion */
			placerPion(Partie);
			i+=3;
		}
	}
	fclose(sauvegarde);

	return True;
}

bool chargerCoefficients(float coef[NB_DECOUPAGES][NB_COEFS])
{
	int i, j;
	FILE* f = fopen("coef.data", "r");
   	if (!f)
   		exit(EXIT_FAILURE);
   		
   	printf("Chargement :\n");
   	for (i=0; i<NB_DECOUPAGES; i++)
   	{
   		for (j=0; j<NB_COEFS; j++)
   		{
   			fscanf(f, "%f ", &coef[i][j]);
   			printf("%lf ", coef[i][j]);
   		}
   		printf("\n");
   		fscanf(f, "\n");
   	}
	printf("Fin\n");
	
	fclose(f);
}
   
int niveau(const char* nom)
{
	int i = 3, niveau = 0;
	
	while (nom[i] != '\0')
	{
		niveau *= 10;
		niveau += nom[i] - '0';
		i++;
	}
	return niveau;
}

bool cpu(const char* nom)
{
	if (!nom || strlen(nom) < 3)
		return False;
	return nom[0] == 'C' && nom[1] == 'P' && nom[2] == 'U';
}
