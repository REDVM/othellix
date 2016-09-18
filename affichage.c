#include "main.h"

void affichageFenetre(partie* Partie)
{
	GtkBuilder*  build	= NULL;
	GError*  p_err		 = NULL;

	/* Initialisation de GTK+ */
	gtk_init (NULL, NULL);
	
	initImages(Partie);

	/* Creation d'un nouveau GtkBuilder */
	build = gtk_builder_new ();

	if (build != NULL)
	{
		/* Chargement du XML dans build */
		gtk_builder_add_from_file (build, "interface.glade", &p_err);

		if (p_err == NULL)
		{
			Partie->build = build;
			
			GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object(build, "fen1"); //p_win pointe vers la fenetre


			connexionSignaux(Partie);
			affichageRegles(Partie);
			
			gtk_widget_show_all (p_win); //On affiche la fenetre
			gestionDuJeu(Partie);        //On lance un premier coup la gestion
			gtk_main ();				 //Et enfin la boucle d'evenenement.
			return (void)0;
			
		}

	}
	printf("Erreur lors du chargement de l'interface.\n");
	printf("Verifiez que le fichier 'interface.glade' est bien present dans le dossier et que vous avez les droits de lecture et d'execution dessus.");
}

void pushStatusBar(partie* Partie, char* txt){
	
	gtk_statusbar_push (
	GTK_STATUSBAR(gtk_builder_get_object(Partie->build, "statusBar")), 
	gtk_statusbar_get_context_id (
			GTK_STATUSBAR(gtk_builder_get_object(Partie->build, "statusBar")), "Info"), 
	txt
	);
}

void initImages(partie* Partie){
	GError* error = NULL;
	Partie->Images.imageBgCanvas  = gdk_pixbuf_new_from_file("images/tapis.jpg", &error);
	Partie->Images.imagePionBlanc = gdk_pixbuf_new_from_file("images/pion_blanc.png", &error);
	Partie->Images.imagePionNoir  = gdk_pixbuf_new_from_file("images/pion_noir.png", &error);
	Partie->Images.imagePionBlanc_resize = NULL;
	Partie->Images.imagePionNoir_resize   = NULL;
	Partie->Images.imageBgCanvas_resize = NULL;
	
	if(error != NULL)
		printf("Erreur lors du chargement des images.");
}
void affichageScore(partie* Partie){
	//On actualise le score
	
	char buffer[20];
	
	GdkColormap* colormap = gdk_colormap_get_system();
	GdkColor couleur, couleur2, tmp;
	
	gdk_color_parse("#ee0009", &couleur);
	gdk_color_parse("#808080808080", &couleur2);
	
	gdk_colormap_alloc_color (colormap, &couleur, FALSE, FALSE);
	
	if(couleurActuelle == BLANC){
		tmp = couleur;
		couleur = couleur2;
		couleur2 = tmp;
	}
	
	sprintf(buffer, "%s%d", "Noir : ", score[NOIR]);
	gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(Partie->build, "scoreAffichNoir")), buffer);
	gtk_widget_modify_bg(GTK_WIDGET(gtk_builder_get_object(Partie->build, "eventboxNoir")),
	GTK_STATE_NORMAL,
	&couleur);
	
	sprintf(buffer, "%s%d", "Blanc : ", score[BLANC]);
	gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(Partie->build, "scoreAffichBlanc")), buffer);
		gtk_widget_modify_bg(GTK_WIDGET(gtk_builder_get_object(Partie->build, "eventboxBlanc")),
	GTK_STATE_NORMAL,
	&couleur2);
	
}

void affichagePreferencesAffichage(partie* Partie){
	//Fonction qui sera utilisée plus tard.
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gtk_builder_get_object(Partie->build, "menu_afficheGrilleBouton")), Partie->Preferences.afficheGrille);
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gtk_builder_get_object(Partie->build, "menu_afficheDernierCoupBouton")), Partie->Preferences.afficheDernierCoup);
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gtk_builder_get_object(Partie->build, "menu_afficheCasesJouablesBouton")), Partie->Preferences.afficheCasesJouables);
}
void affichageDernierCoup(partie* Partie, GtkWidget* canvas)
{
	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	int X, Y;

	/* Initialisation du GdkGC* et de la GdkColormap* */	
	GdkGC* cadre = gdk_gc_new(canvas->window);
	GdkColormap* colormap = gdk_colormap_get_system();
	GdkColor rouge;
	
	/* Si ce n'est pas le premier coup */
	if (Partie->numeroCoupActuel != 0)
	{
		/* Initialisation de la couleur */
		gdk_color_parse("#FF0000", &rouge);
		gdk_colormap_alloc_color(colormap, &rouge, FALSE, FALSE);
		gdk_gc_set_foreground(cadre, &rouge);
	
		/* Calcul de la position */
		Y = (dernierePosition/TAILLE);
		 X = (dernierePosition-TAILLE*Y);
		
		gdk_draw_rectangle (canvas->window, cadre, FALSE, (X-1)*(largeur*1.0/(TAILLE-2)), (Y-1)*(hauteur*1.0/(TAILLE-2)), largeur/(TAILLE-2), hauteur/(TAILLE-2));
		gdk_draw_rectangle (canvas->window, cadre, FALSE, (X-1)*(largeur*1.0/(TAILLE-2))+1, (Y-1)*(hauteur*1.0/(TAILLE-2))+1, largeur/(TAILLE-2)-2, hauteur/(TAILLE-2)-2);
		
	}
}


void affichageRegles(partie* Partie){
	
	GtkTextBuffer* regles = gtk_text_buffer_new(NULL);
	GtkTextIter* a = malloc(sizeof(GtkTextIter));

	gtk_text_buffer_get_end_iter(regles, a);

	gtk_text_buffer_insert(regles, a, "Principes de base\n\tOthello est un jeu de stratégie à deux joueurs : Noir et Blanc. Il se joue sur un plateau unicolore de 64 cases, 8 sur 8, appelé othellier. Ces joueurs disposent de 64 pions bicolores, noirs d’un côtéet blancs de l’autre.\n\nBut du jeu\n\tLe but est d’avoir plus de pions de sa couleur que l’adversaire à la fin de la partie. Celle-ci s’achève lorsque les des deux joueurs ne peuvent plus jouer de coup légal.\n\nPose d’un pion\n\tLe joueur doit poser un pion de sa couleur sur une case vide de l’othellier, adjacente à un pion adverse. Il doit également, en posant son pion, encadrer un ou plusieurs pions adverses entre le pion qu’il pose et un pion à sa couleur, déjà placé sur l’othellier. Il retourne alors de sa couleur le ou les pions qu’il vient d’encadrer. Les pions ne sont ni retirés de l’othellier, ni déplacés d’une case\nà l’autre.\nOn peut encadrer des pions adverses dans les huit directions. Par ailleurs, dans chaque direction, plusieurs pions peuvent être encadrés. On doit alors tous les retourner. Si, à votre tour de jeu, vous ne pouvez pas poser un pion en retournant un pion adverse suivant les règles, vous devez passer votre tour et c’est à votre adversaire de jouer.\n\nFin de la partie\n\tLa partie est terminée lorsque aucun des deux joueurs ne peut plus jouer. Cela arrive généralement lorsque les 64 cases sont occupées. Mais il se peut qu’il reste des cases vides où personne ne peut plus jouer : par exemple lorsque tous les pions deviennent d’une même couleur après un retournement.\nOn compte les pions pour déterminer le score. Les cases vides sont données au vainqueur. En cas d’égalité, elles sont réparties équitablement entre les deux joueurs.\n", -1); 
	gtk_text_view_set_buffer((GtkTextView *) gtk_builder_get_object(Partie->build, "textView"), regles);
	
}
