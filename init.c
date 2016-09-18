#include "main.h"

extern float tab_coef[NB_DECOUPAGES][NB_COEFS];

void initPartie(partie* Partie, int nbJoueurs, bool newPartie)
{
	initOthellier(Partie);
	
	Partie->numeroCoupActuel = 0;
	Partie->totalCoups = 0;
	
	Partie->statut = True;
	Partie->tourPasse = False;
	Partie->inverse = False;
	
	couleurActuelle = NOIR;
	Partie->nbJoueurs = nbJoueurs;
	
	//Au lancement du programme, on charge les préférences par défaut.
	if(newPartie){
		initPreferences(Partie);
	}

	Partie->Joueur[0].couleur = NOIR;
	Partie->Joueur[1].couleur = BLANC;
	initMessages(Partie->tab_message);
	Partie->messageActuel = AUCUN;
	initJoueurs(Partie);
}


void initPreferences(partie* Partie){
	Partie->Preferences.afficheGrille = True;
	Partie->Preferences.afficheDernierCoup = True;
	Partie->Preferences.afficheCasesJouables = True;
	
	Partie->Preferences.Joueur1[0] = (Partie->nbJoueurs>0) ? HUMAIN : CPU;
	Partie->Preferences.Joueur1[1] = (Partie->nbJoueurs>0) ? NONE : INTERMEDIAIRE;
	
	Partie->Preferences.Joueur2[0] = (Partie->nbJoueurs>1) ? HUMAIN : CPU;
	Partie->Preferences.Joueur2[1] = (Partie->nbJoueurs>1) ? NONE : INTERMEDIAIRE;
}

void initJoueurs(partie* Partie){
	int numero = 1;  //Pour la numérotation des joueurs humains.
	if (Partie->Preferences.Joueur1[0] == HUMAIN){
		initJoueurHumain(&(Partie->Joueur[0]), numero);
		numero++;
	}
	else
		initJoueurCPU(&(Partie->Joueur[0]), Partie->Preferences.Joueur1[1]);
	
	
	if (Partie->Preferences.Joueur2[0] == HUMAIN)
		initJoueurHumain(&(Partie->Joueur[1]), numero);
	else
		initJoueurCPU(&(Partie->Joueur[1]), Partie->Preferences.Joueur2[1]);
}

void initJoueurHumain(joueur* Joueur, int numero)
{	
	sprintf(Joueur->nom, "J%c", '0' + numero);
	Joueur->type = HUMAIN;
	Joueur->niveau = NONE;
	Joueur->enTrainDeJouer = False;
	
	initCoefficients(Joueur->coef);
}

void initJoueurCPU(joueur* Joueur, int niveau)
{
	int i, j;
	
	Joueur->type = CPU;
	Joueur->niveau = niveau;
	Joueur->enTrainDeJouer = False;
	sprintf(Joueur->nom, "CPU%d", Joueur->niveau);

	/* Coefficients fixés à la main temporairement. */
	/*
	for (i=0; i<NB_DECOUPAGES; i++)
	{
		Joueur->coef[i][0] = 0.1;
		Joueur->coef[i][1] = 1.;
		Joueur->coef[i][2] = 0.5;
		Joueur->coef[i][3] = 0.7;
		Joueur->coef[i][4] = 1.;
	}
	//*/
	initCoefficients(Joueur->coef);
	 
	/*
	printf("initJoueur : \n");
	for (i=0; i<NB_DECOUPAGES; i++)
	{
		for (j=0; j<NB_COEFS; j++)
			printf("%.1lf ", Joueur->coef[i][j]);
		printf("\n");
	}
	//*/
}

void initCoefficients(float coef[NB_DECOUPAGES][NB_COEFS])
{
	int i, j;
	
	for (i=0; i<NB_DECOUPAGES; i++)
		for (j=0; j<NB_COEFS; j++)
			coef[i][j] = tab_coef[i][j];
}

void initOthellier(partie* Partie){
	
	int i;
	
	/* On remplit la première ligne de BORD */
	for (i=0 ; i < TAILLE ; i++)
		plateau[i] = BORD;
	
	/* On remplit les 8 lignes suivantes de BORD ou de VIDE */
	for (; i <  9*TAILLE ; i++){
		if (i % TAILLE == 0 || i % TAILLE == 9)
			plateau[i] = BORD;
		else
			plateau[i] = VIDE;
	}
	
	/* On remplit la dernière ligne de BORD */
	for (; i < TAILLE * TAILLE; i++)
		plateau[i] = BORD;
	
	/* On place les 4 pions de départ */
	plateau[44] = BLANC;
	plateau[55] = BLANC;
	plateau[45] = NOIR;
	plateau[54] = NOIR;
	
	/* On initialise les scores */
	score[NOIR] = 2;
	score[BLANC] = 2;
}

void initMessages(char tab[][200])
{
	
	sprintf(tab[PAS_DE_COUP+NOIR], "** Le joueur noir n'a pas pu jouer.");
	sprintf(tab[PAS_DE_COUP+BLANC], "** Le joueur blanc n'a pas pu jouer.");
	sprintf(tab[JEU_IMPOSSIBLE], "** Il n'y a plus de cases jouables. Les cases vides ont été ajoutées au score de ");
	sprintf(tab[JEU_IMPOSSIBLE_2], "** Il n'y a plus de cases jouables. Les cases vides ont été ajoutées aux scores des deux joueurs de facon équitable.");
	sprintf(tab[EGALITE], "Les deux joueurs sont ex aequo.");
	sprintf(tab[VICTOIRE+NOIR], " Le joueur noir a gagné !");
	sprintf(tab[VICTOIRE+BLANC], " Le joueur blanc a gagné !");
	sprintf(tab[INVERSION], "** Les couleurs ont été inversées.");
	sprintf(tab[SAUVEGARDE_REUSSIE], "** La partie a été sauvegardée.");
	sprintf(tab[CHARGEMENT_REUSSI], "** La partie a été chargée avec succés.");
	sprintf(tab[ECHEC_SAUVEGARDE], "** Erreur lors de la sauvegarde.");
	sprintf(tab[ECHEC_SAUVEGARDE], "** Erreur lors du chargement.");
	sprintf(tab[ECHEC_ANNULATION], "** Impossible d'annuler le coup.");
	sprintf(tab[ECHEC_REJOUER], "** Impossible de rejouer le coup.");
	sprintf(tab[AUCUN], "");
}

