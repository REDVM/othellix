#include "main.h"

float tab_coef[NB_DECOUPAGES][NB_COEFS];

int main(int argc, char* argv[])
{
	partie Partie;
	
   	chargerCoefficients(tab_coef);
   	initPartie(&Partie, 1, True);
   	affichageFenetre(&Partie);
   
	return EXIT_SUCCESS;
}


