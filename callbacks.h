#ifndef __callbacks__
#define __callbacks__

#define HAUTEUR_BG 1920
#define LARGEUR_BG 1239


//= gdk_pixbuf_new_from_file("tapids.jpg", NULL)


//Callbacks connectées aux differents signaux des differents objets.

//Connectée au bouton Quitter
void cb_quit (GtkWidget * widget, partie* Partie);

//On dessine l'interieur de la zone de dessin (plateau, pions, et companies ...)
void cb_fill_canvas(GtkWidget* canvas, GdkEventExpose *event, partie* Partie);

//Quand le canvas change de taille, on change certaines constantes
void cb_setup_canvas(GtkWidget* canvas, GdkEventConfigure *event, partie* Partie);

//Lors du clique sur le canevas.
void cb_clickd(GtkWidget* widget, GdkEventButton* event, partie* Partie);

//Lors de l'appuie sur n'importe quelle touche 
void cb_key_press(GtkWidget* w, GdkEventKey* event, partie* Partie);

//Recommence une nouvelle partie
void cb_newPartie(GtkWidget* widget, partie* Partie);

//Sauvegarder partie
void cb_sauvegarderPartie(GtkWidget* widget, partie* Partie);

//Charger partie
void cb_chargerPartie(GtkWidget* widget, partie* Partie);

//Callback pour annuler un coup
void cb_annulerCoup(GtkWidget* widget, partie* Partie);

//Callback pour rejouer un coup
void cb_rejouerCoup(GtkWidget* widget, partie* Partie);

//Affiche la fenetre qui permet de changer le mode de jeu (Humain vs Humain, CPU vs CPU, ...)
void cb_change_mode(GtkWidget* widget, partie* Partie);

//On change le mode de jeu en fonction des boutons radio de la fenetre change mode.
void cb_change_mode_valider(GtkWidget* widget, partie* Partie);

//Changer l'affichage du plateau de jeu
void cb_changeAffichage(GtkCheckMenuItem *item, partie* Partie);

//On inverse les couleurs
void cb_inverser(GtkWidget* widget, partie* Partie);

//Ouvre la fenetre A propos
void cb_a_propos(GtkWidget* widget, partie* Partie);

//Ferme la fenetre A propos
void cb_quit_a_propos(GtkWidget* widget, GdkEvent* event, partie* Partie);

//Ouvre la fenetre d'aide.
void cb_aide(GtkWidget* widget, partie* Partie);

#endif
