#ifndef __constantes__
#define __constantes__

/* Définition de quelques constantes. */
#define TAILLE                   10
#define NB_JOUEURS               2
#define NB_COUPS                 60
#define VITESSE_ACTUALISATION    500 //Temps en ms qu'attendra le Cpu avant de jouer (sinon il est trop rapide pour bien comprendre ou il joue)
#define NB_COEFS                 5
#define NB_DECOUPAGES            10

/* 
 * Définition des différentes valeurs que peuvent 
 * prendre les cases de l'othellier.
 */
#define NOIR     0
#define BLANC    1
#define JOUABLE  2
#define BORD    -2
#define VIDE    -1

/* 
 * Définition des 4 directions principales.
 * Les diagonales sont obtenues par les sommes des
 * 2 directions principales qui la composent (par
 * exemple, la direction haut-gauche vaut HAUT+GAUCHE).
 */
#define HAUT     -TAILLE
#define BAS       TAILLE
#define GAUCHE   -1
#define DROITE    1

#define INFINI   INT_MAX
#define INFINI_f 200.0 //INFINITY

/* Définition du type booléen. */
typedef char bool;
enum {False, True};

/* Enumeration des différents types de messages. */
enum {PAS_DE_COUP, PAS_DE_COUP_2, JEU_IMPOSSIBLE, JEU_IMPOSSIBLE_2, 
	  EGALITE, VICTOIRE, VICTOIRE_2, INVERSION, SAUVEGARDE_REUSSIE, CHARGEMENT_REUSSI,
      ECHEC_SAUVEGARDE, ECHEC_CHARGEMENT, ECHEC_ANNULATION, ECHEC_REJOUER, AUCUN, NB_MESSAGES};

/* 
 * Définition des contantes utilisée par la fonction
 * victoire().
 */
#define PAS_FINI -1
#define EGALITE  -2
       
/* 
 * Définit le premier caractère à modifier dans le message 
 * CASE_NON_JOUABLE pour inscire la case concernée. 
 */
#define PREMIER_CARACTERE_CASE 27
       
/* Enumération des différents types de joueurs. */
enum {HUMAIN, CPU};

/* Définition de la profondeur utilisée pour chaque niveau d'IA. */
#define NONE              0
#define NOVICE            1
#define DEBUTANT          4 
#define INTERMEDIAIRE     7
#define EXPERT            9


#endif
