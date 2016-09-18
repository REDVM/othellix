#ifndef __gestion__
#define __gestion__

/* Gère le déroulement d'une partie du début à la fin. */ 
bool gestionDuJeu(partie* Partie);

/* Lance coupCPU dans un thread si possible */
bool coupCPU_threadInit(void* arg);

/* Permet à un joueur contrôlé par ordinateur de joueur un coup. */
void coupCPU(void* Partie);

/* 
 * Place un pion sur l'othellier, retourne les pions
 * concernés et actualise les scores. 
 */
bool placerPion(partie* Partie);

void placerPion_opt(partie* Partie);

/* Annule le coup qui vient d'être joué. */
int annulerCoup(partie* Partie);

void annulerCoup_opt(partie* Partie);

/* Rejoue le coup qui vient d'être annulé. */
int rejouerCoup(partie* Partie);

/* Inverse les couleurs. */
void inverserCouleur(partie* Partie);

#endif
