#ifndef __structures__
#define __structures__

/* 
 * L'othellier est constitué d'un tableau de 10*10 cases et 
 * des scores des deux joueurs/
 */
typedef struct{
  char Plateau[TAILLE * TAILLE];
  char Score[NB_JOUEURS];
} othellier;

/* 
 * Un coup est caractérisé par sa position, le nombre de pions 
 * qu'il permet de retourner dans chacune des directions et la 
 * couleur du pion posé.
 */
typedef struct{
  char position;
  char pionsRetournables[8];
  char couleur;
} coup;

/* 
 * Un joueur est caractérisé par son nom, son type (HUMAIN ou 
 * CPU), son niveau (pour le CPU) et la couleur qu'il joue. 
 */
typedef struct{
	char nom[50];
	char type;
	char niveau;
	char couleur;
	bool  enTrainDeJouer;
	float coef[NB_DECOUPAGES][NB_COEFS];
} joueur;

/* 
 * La structure préférence contient les différentes préférences d'affichage et de jeu. 
 */
typedef struct{
	bool afficheGrille;
	bool afficheDernierCoup;
	bool afficheCasesJouables;
	char Joueur1[2]; //Va contenir le type puis le niveau du premier joueur.
	char Joueur2[2]; //Va contenir le type puis le niveau du deuxieme joueur.
} preferences;

typedef struct{
	GdkPixbuf* imageBgCanvas;
	GdkPixbuf* imagePionBlanc;
	GdkPixbuf* imagePionNoir;
	//Les images des pions apres le redimensionnement
	GdkPixbuf* imageBgCanvas_resize;
	GdkPixbuf* imagePionBlanc_resize;
	GdkPixbuf* imagePionNoir_resize;
	
} images;

/*
 * Une partie est définie par son statut (True si la partie
 * est en cours et False si elle est terminée), un othellier, 
 * l'ensemble des coups joués (un tableau de 60 coups, le nombre 
 * total de coups joués et le numéro du coup actuel), les joueurs 
 * (les deux joueurs et le nombre de joueur(s) humain(s)), et les 
 * messages qui peuvent être affichés (le tableau de tous les 
 * messages et l'indice du message actuel).
 */
typedef struct{
	bool statut;
	bool tourPasse;
	bool inverse;
	
	othellier Othellier;
	
	coup Coup[NB_COUPS];
	char totalCoups;
	char numeroCoupActuel;
	
	joueur Joueur[NB_JOUEURS];
	char nbJoueurs;
	
	preferences Preferences;
	images Images;
	
	char tab_message[NB_MESSAGES][200];
	char messageActuel;
	
	GtkBuilder*  build; //Ce champ permettra d'acceder a tous les widgets a partir de partie.
} partie;

#endif
