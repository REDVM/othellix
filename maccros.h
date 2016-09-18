#ifndef __maccros__
#define __maccros__

/* 
 * Définition d'une maccro permettant la portabilité 
 * du programme.
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
# define effacer() system("cls")
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__) || defined(macintosh)
# define effacer() system("clear")
#endif

/* 
 * Définition des quelques maccros permettant d'accéder
 * rapidement aux variables souvent utilisées.
 */
#define plateau				 Partie->Othellier.Plateau
#define score                Partie->Othellier.Score

#define coupActuel           Partie->Coup[Partie->numeroCoupActuel]
#define positionActuelle     coupActuel.position
#define couleurActuelle      coupActuel.couleur

#define dernierCoup          Partie->Coup[Partie->numeroCoupActuel-1]
#define dernierePosition     dernierCoup.position
#define derniereCouleur      dernierCoup.couleur

#define indiceJoueurActuel   couleurActuelle == Partie->Joueur[0].couleur ? 0 : 1
#define joueurActuel         couleurActuelle == Partie->Joueur[0].couleur ? Partie->Joueur[0].nom : Partie->Joueur[1].nom
#define dernierJoueur        derniereCouleur == Partie->Joueur[0].couleur ? Partie->Joueur[0].nom : Partie->Joueur[1].nom

#define message              Partie->tab_message[Partie->messageActuel]

#endif
