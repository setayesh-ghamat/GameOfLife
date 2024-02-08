
/**
 * @file main.c
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 * @brief code for the main
*/


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"
#ifndef TEXTE
  #include "io_cairo.h"
#endif

int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

  
#ifndef TEXTE
	debut_jeu_cairo(&g, &gc);
	
#else
  affiche_grille(g);
  debut_jeu(&g, &gc);
#endif

	libere_grille(&g);
	libere_grille(&gc);
 
	return 0;
}
