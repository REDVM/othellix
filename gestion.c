#include "main.h"

extern int nb_calculs[2];


bool gestionDuJeu(partie* Partie){
	char tmp[150] = "";         // Entree de l'utilisateur
	int gagnant;
	
	enleverCoupsJouables(Partie);
	
	gagnant = victoire(Partie);
	if (score[NOIR] + score[BLANC] < NB_COUPS + 4 && !Partie->statut)
  		rajouterCasesVides(Partie);
	else if (gagnant != PAS_FINI)
	{
		if (gagnant != EGALITE)
			Partie->messageActuel = VICTOIRE+gagnant;
		else
			Partie->messageActuel = EGALITE;
		Partie->statut = False;
	}
	affichageScore(Partie);
	gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(Partie->build, "canvas"))); //On actualise le canevas.
	pushStatusBar(Partie, message); // on affiche les messages dans la barre d'état
	
	if (!(Partie->statut)) // Si c'est fini on s'arrete.
		return False;
	
	if(ajouterCoupsJouables(Partie)){
		gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(Partie->build, "canvas"))); //On redessine apres avoir ajouter les coups jouables.
		if (Partie->Joueur[indiceJoueurActuel].type == CPU && (!(Partie->Joueur[indiceJoueurActuel].enTrainDeJouer))) {
			Partie->Joueur[indiceJoueurActuel].enTrainDeJouer = True;
			enleverCoupsJouables(Partie);
			
			g_timeout_add(VITESSE_ACTUALISATION, (GSourceFunc)coupCPU_threadInit, (void*)Partie);//On fait jouer le CPU apres une certaine durée en millisecondes, pour bien comprendre comment il joue !
		}
	}
	else
	{
		
		/* On modifie le message */
		Partie->messageActuel = PAS_DE_COUP + couleurActuelle;
		/* On change la couleur qui doit jouer */
		couleurActuelle = !couleurActuelle;
		
		/* On vérifie si le joueur d'avant a pu jouer. 
		   Si ce n'est pas le cas, on arrête la partie */
  		if (!Partie->tourPasse)
  			Partie->tourPasse = True;
  		else
  		{
  			if (score[NOIR] == score[BLANC])
  				Partie->messageActuel = JEU_IMPOSSIBLE_2;
  			else
  			{
  				Partie->messageActuel = JEU_IMPOSSIBLE;
  				gagnant = score[NOIR] > score[BLANC] ? NOIR : BLANC;
  				sprintf(tmp, "%s (pions %s).", Partie->Joueur[0].couleur == gagnant ? Partie->Joueur[0].nom : Partie->Joueur[1].nom, gagnant == NOIR ? "noirs" : "blancs");
  				strcat(message, tmp);
  				pushStatusBar(Partie, message);
  			}
  			Partie->statut = False;
  			
  		}
  		gestionDuJeu(Partie);
	}
	return False;
}


bool coupCPU_threadInit(void* arg){
	partie* Partie= (partie*)arg;
	pthread_t t0;
	
	
	if (pthread_create(&t0, NULL, (void * (*)(void *))coupCPU, arg)){
		coupCPU(arg);//Si on a pas pu lancer le thread, on appele la fonction dans le thread principal
	}
	return False;
	
	
	//~ coupCPU((partie*)arg);
}
void coupCPU(void* Partie_void){
	partie* Partie = (partie*) Partie_void;
	int indiceCourant=indiceJoueurActuel;

	int i, j;
	int profondeur, meilleurePosition;
	float ret;
	GTimer* chrono = g_timer_new();
	
	/* On détermine la profondeur. */
	profondeur = Partie->Joueur[indiceJoueurActuel].niveau;
	
	/* On lance l'algorithme Alpha-bêta. */
	if (Partie->numeroCoupActuel >= 45)
	{
		//profondeur = NB_COUPS - Partie->numeroCoupActuel;
		printf("\n** Profondeur MAX : %d\n", profondeur);
	}
	else
		printf("\nProfondeur : %d\n", profondeur);
		
	nb_calculs[0] = 0;
	nb_calculs[1] = 0;
	g_timer_start(chrono);
	ret = AlphaBeta(profondeur, couleurActuelle, &meilleurePosition, Partie, -INFINI_f, INFINI_f);
	g_timer_stop(chrono);
	printf("AlphaBeta : %d appels (%.3f secondes)\n", nb_calculs[0], g_timer_elapsed(chrono, NULL));
	printf("%d évaluations.\n", nb_calculs[1]);
		
	/* On place le coup. */
	positionActuelle = meilleurePosition;
	plateau[positionActuelle] = JOUABLE;
	placerPion(Partie);
	
	g_timer_destroy(chrono);
	Partie->Joueur[indiceCourant].enTrainDeJouer = False;
	g_idle_add((GSourceFunc)gestionDuJeu, Partie);
}

bool placerPion(partie* Partie){
   	if(plateau[positionActuelle] == JOUABLE){
   	
		placerPion_opt(Partie);
  		Partie->totalCoups = Partie->numeroCoupActuel;
  		return True;
  	}
  	else
  	{
  		
  		return False;
  	}
}

void placerPion_opt(partie* Partie)
{
	/* On pose le pion */
	plateau[positionActuelle] = couleurActuelle;
	score[couleurActuelle]++;
		
	/* On renverse les pions voisins concernés */
	compterPions(Partie);
		
	/* On incrémente l'indice du coup actuel */
  	Partie->numeroCoupActuel++;
  	
  	/* On modifie la couleur */
  	couleurActuelle = !derniereCouleur;
  		
  	/* On indique que le joueur a pu jouer */
  	Partie->tourPasse = False;
}

int annulerCoup(partie* Partie)
{
	/* Si le coup n'est pas le premier (on peut l'annuler) */
	if (Partie->numeroCoupActuel > 0)
	{
		enleverCoupsJouables(Partie);
		annulerCoup_opt(Partie);
		ajouterCoupsJouables(Partie);
		
		return AUCUN;
	}
	else
		return ECHEC_ANNULATION;
}

void annulerCoup_opt(partie* Partie)
{	
	/* On décrémente l'indice du coup actuel */
	Partie->numeroCoupActuel--;
	/* On enlève le pion posé */
	plateau[positionActuelle] = VIDE;
	score[couleurActuelle]--;
	/* On retoune à nouveau les pions voisins pour revenir à la situation précédente */
	renverserPionsAnnulation(Partie);
}

int rejouerCoup(partie* Partie)
{
	/* Si le coup n'est pas le premier (on peut l'annuler) */
	if (Partie->numeroCoupActuel < Partie->totalCoups)
	{
		enleverCoupsJouables(Partie);
			
		//On ajoute le pion.
		plateau[positionActuelle] = couleurActuelle;
		//On augmente le score et on renverse les pions
		score[couleurActuelle]++;
		renverserPions(Partie);
		
		// On incrémente l'indice du coup actuel
		Partie->numeroCoupActuel++;
		
		ajouterCoupsJouables(Partie);
		
		return AUCUN;
	}
	else
		return ECHEC_REJOUER;
}

void inverserCouleur(partie* Partie)
{
	int i;
		
	/* Inversion de la couleur des joueurs */
	for (i=0; i<2; i++)
		Partie->Joueur[i].couleur = !Partie->Joueur[i].couleur;
	
	/* Inversion de la couleur des coups joués */
	for (i=0; i<=Partie->totalCoups; i++)
		Partie->Coup[i].couleur = !Partie->Coup[i].couleur;
		
	/* Inversion des pions sur l'othellier */
	for (i=TAILLE; i<(TAILLE-1)*TAILLE; i++)
		if (plateau[i] == NOIR || plateau[i] == BLANC)
			plateau[i] = !plateau[i];
			
	/* Inversion des scores */
	i = score[NOIR];
	score[NOIR] = score[BLANC];
	score[BLANC] = i;
	
	Partie->inverse = !Partie->inverse;
		
	/* Actualisation du message */
	Partie->messageActuel = INVERSION;
}

