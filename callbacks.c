#include "main.h"

void cb_fill_canvas(GtkWidget* canvas, GdkEventExpose* event, partie* Partie){

	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	int i, cellule, X, Y, rayon;
	int x, y;
	
	//Cote des images des pions
	int cotePion = gdk_pixbuf_get_width(Partie->Images.imagePionNoir_resize); 
	
	rayon = (largeur*1.0/(TAILLE-2))-8; //Rayon des pions sur le plateau.
	
	//On va créer une couleur verte pour marquer les cases jouables
	GdkGC* gc = gdk_gc_new(canvas->window);  
	GdkGC* gc2 = gdk_gc_new(canvas->window);  
	GdkColormap* colormap = gdk_colormap_get_system(); //Sans ca, on a des couleurs vives aleatoires a chaque execution, ca peut etre interessant.
	GdkColor couleur, couleurFond, rouge;
	
	gdk_color_parse("#25ee00", &couleur);
	gdk_colormap_alloc_color (colormap, &couleur, FALSE, FALSE);
	gdk_gc_set_foreground (gc, &couleur);
	
	gdk_color_parse("#009900", &couleurFond);
	gdk_colormap_alloc_color (colormap, &couleurFond, FALSE, FALSE);
	gdk_gc_set_foreground (gc2, &couleurFond);
	//Fin de la couleur
	
	
	
                                   
	// On dessine le fond, puis les lignes
	if(hauteur > HAUTEUR_BG || largeur >LARGEUR_BG) 
		//Si l'image en fond est plus petite que le canevas, on met un fond uni
		gdk_draw_rectangle(canvas->window, gc2, TRUE, 0, 0, largeur, hauteur);
	else{ //Sinon on met l'image
		gdk_draw_pixbuf((GdkDrawable *)canvas->window, gc, Partie->Images.imageBgCanvas_resize, 0, 0, 0, 0, largeur, hauteur, GDK_RGB_DITHER_NONE, 0, 0);
	}
	
	if(Partie->Preferences.afficheGrille){
		for(i=0 ; i	< TAILLE; i++){
			gdk_draw_line (canvas->window, canvas->style->black_gc, (largeur*1.0/(TAILLE-2))*i, 0, (largeur*1.0/(TAILLE-2))*i, hauteur);
			gdk_draw_line (canvas->window, canvas->style->black_gc, 0, (hauteur*1.0/(TAILLE-2))*i, largeur, (hauteur*1.0/(TAILLE-2))*i);
		}
			gdk_draw_line (canvas->window, canvas->style->black_gc, largeur-1, 0, largeur-1, hauteur-1);
			gdk_draw_line (canvas->window, canvas->style->black_gc, 0, hauteur-1, largeur-1, hauteur-1);
	}
	
	for(i=TAILLE+1 ; i < TAILLE * (TAILLE-1); i++){
		cellule = plateau[i];
		Y = (i/TAILLE);
		X = (i-TAILLE*Y);

		switch(cellule){
			case NOIR: //Pour dessiner un cercle : gdk_draw_arc (canvas->window, canvas->style->black_gc, True, (X-1)*(largeur*1.0/(TAILLE-2))+4, (Y-1)*(hauteur*1.0/(TAILLE-2))+4, rayon, rayon, 0, 360*64);
			    gdk_draw_pixbuf((GdkDrawable *)canvas->window, gc, Partie->Images.imagePionNoir_resize,
					0, 0, (X-1)*(largeur*1.0/(TAILLE-2)), (Y-1)*(hauteur*1.0/(TAILLE-2)), cotePion, 
					cotePion, GDK_RGB_DITHER_NONE, 0, 0);	
				break;
			case BLANC:
				gdk_draw_pixbuf((GdkDrawable *)canvas->window, gc, Partie->Images.imagePionBlanc_resize,
					0, 0, (X-1)*(largeur*1.0/(TAILLE-2)), (Y-1)*(hauteur*1.0/(TAILLE-2)), cotePion, 
					cotePion, GDK_RGB_DITHER_NONE, 0, 0);	

				break;
			case JOUABLE:
				if(Partie->Preferences.afficheCasesJouables)
					gdk_draw_rectangle (canvas->window, gc, True, (X-1)*(largeur*1.0/(TAILLE-2))+1, (Y-1)*(hauteur*1.0/(TAILLE-2))+1, largeur/(TAILLE-2)-1, hauteur/(TAILLE-2)-1);
				break;
		}
	}
	(Partie->Preferences.afficheDernierCoup) ? affichageDernierCoup(Partie, canvas) : 0;
}

void cb_setup_canvas(GtkWidget* canvas, GdkEventConfigure *event, partie* Partie){
	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	
	
	if (Partie->Images.imagePionBlanc_resize != NULL &&  Partie->Images.imagePionNoir_resize != NULL && Partie->Images.imageBgCanvas_resize !=  NULL){
		gdk_pixbuf_unref (Partie->Images.imagePionNoir_resize);
		gdk_pixbuf_unref (Partie->Images.imagePionBlanc_resize);
		gdk_pixbuf_unref (Partie->Images.imageBgCanvas_resize);
	}
	
	//On change la dimension des images des pions selon la taille du canvas
	Partie->Images.imagePionBlanc_resize = gdk_pixbuf_scale_simple (Partie->Images.imagePionBlanc, largeur/(TAILLE-2), hauteur/(TAILLE-2), GDK_INTERP_BILINEAR);
	Partie->Images.imagePionNoir_resize   = gdk_pixbuf_scale_simple (Partie->Images.imagePionNoir,  largeur/(TAILLE-2), hauteur/(TAILLE-2), GDK_INTERP_BILINEAR);
	Partie->Images.imageBgCanvas_resize = gdk_pixbuf_scale_simple (Partie->Images.imageBgCanvas, largeur, hauteur, GDK_INTERP_BILINEAR);
	
	
}
void cb_clickd(GtkWidget* canvas, GdkEventButton* event, partie* Partie){
	
	if(!(Partie->statut)) //Si la partie est terminée
		return (void)0;
		
	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	double X = event->x, Y = event->y;	
	
	int indice; //indice dans le tableau correspondant au clique de souris sur l'othellier.
	
	
	indice = TAILLE * ((int)(Y/(largeur*1.0/(TAILLE-2)))+1) + (int)(X/(largeur*1.0/(TAILLE-2))) + 1;
	
	positionActuelle = indice;
	if(placerPion(Partie))
		gestionDuJeu(Partie);
		
}

void cb_key_press(GtkWidget* w, GdkEventKey* event, partie* Partie){ 

    switch (event->keyval) 
    { 
        // Si on appuie sur une touche de raccourci : 
        case GDK_z: cb_annulerCoup(w, Partie);         break; 
        case GDK_y: cb_rejouerCoup(w, Partie);         break; 
        case GDK_s: cb_sauvegarderPartie(w, Partie);   break; 
        case GDK_o: cb_chargerPartie(w, Partie);       break; 
        case GDK_n: cb_newPartie(w, Partie);           break;
        case GDK_q: cb_quit(w, Partie);                break;
        default:                                       break; 
    } 

} 
void cb_newPartie(GtkWidget* widget, partie* Partie){
   	initPartie(Partie, Partie->nbJoueurs, False);
   	affichagePreferencesAffichage(Partie);
   	gestionDuJeu(Partie);	
}

void cb_annulerCoup(GtkWidget* widget, partie* Partie){
	int couleurCPU = Partie->Joueur[0].type == CPU ? Partie->Joueur[0].couleur : Partie->Joueur[1].couleur;
	
	/* A remplacer par if (couleurActuelle == couleurCPU) ??? */
	if (cpu(joueurActuel)){ //On ne peut pas annuler si le CPU va jouer.
		Partie->messageActuel = ECHEC_ANNULATION;
		return (void)0;
	}
	
	if (!Partie->statut)
		Partie->statut = True;
	
	Partie->messageActuel = annulerCoup(Partie);
	
	/* Permet d'annuler les coups du CPU jusqu'a ce que ca soit a l'humain de jouer.
	 * Très utile quand le CPU joue plusieurs fois d'affilé.*/
	while(couleurActuelle == couleurCPU  && Partie->nbJoueurs == 1 && Partie->messageActuel != ECHEC_ANNULATION)
		Partie->messageActuel = annulerCoup(Partie);


   	if (Partie->messageActuel != ECHEC_ANNULATION)
		Partie->statut = True; //Dans le cas ou on aurait fini la partie et on voudrait revenir en arriere.
   	gestionDuJeu(Partie);	
}

void cb_rejouerCoup(GtkWidget* widget, partie* Partie){
	int couleurCPU = Partie->Joueur[0].type == CPU ? Partie->Joueur[0].couleur : Partie->Joueur[1].couleur;
	
	/* Même remarque que pour annuler. */
	if (cpu(joueurActuel)){ //On ne peut pas rejouer si le CPU va jouer.
		Partie->messageActuel = ECHEC_REJOUER;
		return (void)0;
	}
	
	
	Partie->messageActuel = rejouerCoup(Partie);
	
	/*Permet de rejouer les coups du CPU jusqu'a ce que ca soit a l'humain de jouer.
	 * Très utile quand le CPU a joué plusieurs fois d'affilé.*/
	while(couleurActuelle == couleurCPU  && Partie->nbJoueurs == 1 && Partie->messageActuel != ECHEC_REJOUER)
		Partie->messageActuel = rejouerCoup(Partie);

   	gestionDuJeu(Partie);	
}

void cb_sauvegarderPartie(GtkWidget* widget, partie* Partie){
	Partie->messageActuel = sauvegarder(Partie) ? SAUVEGARDE_REUSSIE : ECHEC_SAUVEGARDE;
   	gestionDuJeu(Partie);	
}

void cb_chargerPartie(GtkWidget* widget, partie* Partie){
	initPartie(Partie, Partie->nbJoueurs, False);
	Partie->messageActuel = chargerPartie(Partie) ? CHARGEMENT_REUSSI : ECHEC_CHARGEMENT;
	
   	gestionDuJeu(Partie);	
}

void cb_changeAffichage(GtkCheckMenuItem *item, partie* Partie){
	if (!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(item)), "Afficher la grille"))
		Partie->Preferences.afficheGrille = (gtk_check_menu_item_get_active(item)) ? True : False;
	else if (!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(item)), "Afficher le dernier coup"))
		Partie->Preferences.afficheDernierCoup = (gtk_check_menu_item_get_active(item)) ? True : False;
	else
		Partie->Preferences.afficheCasesJouables = (gtk_check_menu_item_get_active(item)) ? True : False;
	gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(Partie->build, "canvas"))); //On actualise le canevas.
}

void cb_change_mode_valider(GtkWidget* widget, partie* Partie){

	int i=0, j=0;
	GtkRadioButton* itemN = GTK_RADIO_BUTTON(gtk_builder_get_object(Partie->build, "radio_humainNoir"));
	GtkRadioButton* itemB = GTK_RADIO_BUTTON(gtk_builder_get_object(Partie->build, "radio_humainBlanc"));
	//GSList est une structure de liste simplement chainée basique
	GSList *lN = gtk_radio_button_get_group(itemN); //Cette liste chainée contient les différents boutons des différents joueurs (humain, CPU débutant, ...).
	GSList *lB = gtk_radio_button_get_group(itemB); //Cette liste chainée contient les différents boutons des différents joueurs (humain, CPU débutant, ...).
	
	while (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lN->data))){
		lN = lN->next;
		i++;
	}
	while (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lB->data))){
		lB = lB->next;
		j++;
	}
	//i et j vont etre une sorte d'identifiant pour savoir quel GtkRadioButton est actif dans le groupe des blancs et dans celui des noirs.
	
	//Ultra moche mais si efficace : 
	int nbJoueurs = i==3 ? (j==3 ? 2 : 1 ) : (j==3 ? 1 : 0 );
	switch(i){
		case 3:
			Partie->Preferences.Joueur1[0] = HUMAIN;
			Partie->Preferences.Joueur1[1] = NONE;
			break;
		case 2:
			Partie->Preferences.Joueur1[0] = CPU;
			Partie->Preferences.Joueur1[1] = DEBUTANT;
			break;
		case 0:
			Partie->Preferences.Joueur1[0] = CPU;
			Partie->Preferences.Joueur1[1] = EXPERT;
			break;

		default:
			Partie->Preferences.Joueur1[0] = CPU;
			Partie->Preferences.Joueur1[1] = INTERMEDIAIRE;
	}
	switch(j){
		case 3:
			Partie->Preferences.Joueur2[0] = HUMAIN;
			Partie->Preferences.Joueur2[1] = NONE;
			break;
		case 2:
			Partie->Preferences.Joueur2[0] = CPU;
			Partie->Preferences.Joueur2[1] = DEBUTANT;
			break;
		case 0:
			Partie->Preferences.Joueur2[0] = CPU;
			Partie->Preferences.Joueur2[1] = EXPERT;
			break;

		default:
			Partie->Preferences.Joueur2[0] = CPU;
			Partie->Preferences.Joueur2[1] = INTERMEDIAIRE;
		}
		
	Partie->nbJoueurs = nbJoueurs;
	cb_newPartie(widget, Partie);
}

void cb_change_mode(GtkWidget* widget, partie* Partie){
	gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "modeJeuDialog")));
	gint reponse = gtk_dialog_run(GTK_DIALOG(gtk_builder_get_object(Partie->build, "modeJeuDialog")));
	
	if (reponse == GTK_RESPONSE_ACCEPT)
		   cb_change_mode_valider(widget, Partie);


	gtk_widget_hide_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "modeJeuDialog")));

}

void cb_inverser(GtkWidget* widget, partie* Partie){
	
	inverserCouleur(Partie);
	Partie->messageActuel = INVERSION;
	
   	gestionDuJeu(Partie);	
}

void cb_a_propos(GtkWidget* widget, partie* Partie){
	gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "aproposDialog")));
}

void cb_quit_a_propos(GtkWidget* widget, GdkEvent* event, partie* Partie){
	gtk_widget_hide_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "aproposDialog")));
}

void cb_aide(GtkWidget* widget, partie* Partie){
	gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "aideDialog")));
	gtk_dialog_run(GTK_DIALOG(gtk_builder_get_object(Partie->build, "aideDialog")));
	
	gtk_widget_hide_all(GTK_WIDGET(gtk_builder_get_object(Partie->build, "aideDialog")));
}

void cb_quit(GtkWidget* widget, partie* Partie){
	gtk_main_quit ();
}

