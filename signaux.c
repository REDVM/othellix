#include "main.h"

void connexionSignaux(partie* Partie){
	GtkBuilder* build = Partie->build;
	
	//Signaux de la fenetre principale :
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"delete-event", G_CALLBACK (cb_quit), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"destroy-event", G_CALLBACK (cb_quit), Partie);
					

	/*Connexion des boutons de la barre de menu
	 * * * Dans la liste des Actions : */
	g_signal_connect (gtk_builder_get_object(build, "menu_newPartieBouton"),
					"activate", G_CALLBACK (cb_newPartie), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "menu_sauvegarderBouton"),
					"activate", G_CALLBACK (cb_sauvegarderPartie), Partie);

	g_signal_connect (gtk_builder_get_object(build, "menu_chargerBouton"),
					"activate", G_CALLBACK (cb_chargerPartie), Partie);


	g_signal_connect (gtk_builder_get_object(build, "menu_annulerCoupBouton"),
					"activate", G_CALLBACK (cb_annulerCoup), Partie);


	g_signal_connect (gtk_builder_get_object(build, "menu_rejouerCoupBouton"),
					"activate", G_CALLBACK (cb_rejouerCoup), Partie);

	g_signal_connect (gtk_builder_get_object(build, "menu_inverserBouton"),
					"activate", G_CALLBACK (cb_inverser), Partie);

	g_signal_connect (gtk_builder_get_object(build, "menu_quitterBouton"),
					"activate", G_CALLBACK (cb_quit), Partie);
	
	
	
	/* * * Dans la liste des Préférences : */
	g_signal_connect (gtk_builder_get_object(build, "menu_modeBouton"),
					"activate", G_CALLBACK (cb_change_mode), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "menu_afficheGrilleBouton"),
					"activate", G_CALLBACK (cb_changeAffichage), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "menu_afficheDernierCoupBouton"),
					"activate", G_CALLBACK (cb_changeAffichage), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "menu_afficheCasesJouablesBouton"),
					"activate", G_CALLBACK (cb_changeAffichage), Partie);
				
	
	/* * * Dans la liste de l'aide : */
	g_signal_connect (gtk_builder_get_object(build, "menu_aproposBouton"),
					"activate", G_CALLBACK (cb_a_propos), Partie);
	
	g_signal_connect (gtk_builder_get_object(build, "menu_aideBouton"),
					"activate", G_CALLBACK (cb_aide), Partie);
					
					
	
	
	/* Dans la barre d'outils : */
					
					
	g_signal_connect (gtk_builder_get_object(build, "newPartieBouton"),
					"clicked", G_CALLBACK (cb_newPartie), Partie);
					
	g_signal_connect (gtk_builder_get_object(build, "annulerCoupBouton"),
					"clicked", G_CALLBACK (cb_annulerCoup), Partie);


	g_signal_connect (gtk_builder_get_object(build, "rejouerCoupBouton"),
					"clicked", G_CALLBACK (cb_rejouerCoup), Partie);
	
	g_signal_connect (gtk_builder_get_object(build, "enregistrerBouton"),
					"clicked", G_CALLBACK (cb_sauvegarderPartie), Partie);


	g_signal_connect (gtk_builder_get_object(build, "chargerBouton"),
					"clicked", G_CALLBACK (cb_chargerPartie), Partie);
					
					
	/* Pour le canvas */				
	g_signal_connect (gtk_builder_get_object(build, "canvas"),
					"expose-event", G_CALLBACK (cb_fill_canvas), Partie);
	
	g_signal_connect (gtk_builder_get_object(build, "canvas"),
					"configure-event", G_CALLBACK (cb_setup_canvas), Partie);


	gtk_widget_set_events (GTK_WIDGET(gtk_builder_get_object(build, "canvas")), GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
	g_signal_connect(gtk_builder_get_object(build, "canvas"), 
					"button_press_event", G_CALLBACK(cb_clickd), Partie);
	
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"key-press-event", G_CALLBACK (cb_key_press), Partie);
	
	/* Pour la boite de dialogue a propos :  */
	g_signal_connect (gtk_builder_get_object(build, "aproposDialog"),
					"response", G_CALLBACK (cb_quit_a_propos), Partie);
				
}
