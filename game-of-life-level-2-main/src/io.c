/**
 * @file io.c
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 * @brief Gestion de l'affichage
 */


#include "io.h"

int (*compte_voisins_vivants)(int, int, grille)=compte_voisins_vivants_cyclique ;
static int t=0; //Cycle d'évolution
int vieillissement=0;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne)
{
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   ");
		else {
            if(ligne[i] == -1) {
            printf ("| X ");
            }
            else printf ("| %d ", ligne[i]);
		}
	printf("|\n");
	return;
}

void affiche_grille (grille g)
{
	int i, l=g.nbl, c=g.nbc;
	printf("Cycle d'évolution: %d", t);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	
	return;
}


void efface_grille (grille g)
{
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc)
{
	char str[100];
	char c = getchar(); 
	int cyclique=1;

	// touche 'q' pour quitter	
	while (c != 'q') 
	{ 
		switch (c) 
		{
		    // touche "entrée" pour évoluer
			case '\n' : 
			{ 
				evolue(g,gc);
				efface_grille(*g);
				t=t+1;
				affiche_grille(*g);
			
				break;
			}
			// touche non traitée
			default : 
			{ 
				printf("\n\e[1A");
				break;
			}

			// touche 'n' pour charger une nouvelle grille
			case 'n' :
            { 
				t=0;

                printf("Parcourir de la nouvelle grille: \n");
                scanf(" %s", str);
                getchar();
				libere_grille(g);
                libere_grille(gc);
                init_grille_from_file(str, g);
                alloue_grille(g->nbl , g->nbc, gc);
                affiche_grille(*g);

                break;
            }
            case 'c':
                {
					cyclique = !cyclique;
					if(cyclique) {
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
					printf("Mode cyclique \n");
                }
                else {
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
                	printf("Mode non cyclique \n");
                }

			while(getchar() != '\n')
				printf("\n\e[%dA",3); 
                
		break;
                }
				// touche 'v' pour activer/désactiver le vieillissement
                case 'v':
            { 
                if(vieillissement==0) {
                	printf("vieillissement activé  \n");
                   vieillissement=1;
                }
                else {
                	printf("vieillissement désactivé  \n");
                    vieillissement=0;
                }
                while(getchar() != '\n')
					printf("\n\e[%dA",3); 
                break;
            }
			case 'o':
           		{if(morte_grille(g)) printf("grille vide\n");
				else
				{
					int o = oscillate_indirect(*g) ;
					if ((o == OSCILL_MAX_INDIRECT) || (o ==-1)) printf("grille pas oscillante\n") ;
					else if (o == 0) 
					{
						o = est_oscillante(*g,o) ;
						if(o == 1) printf("grille statique\n");
						else printf("grille oscillante de période %d\n",o);
					}
					else 
					{
						int oo = est_oscillante(*g,o) ;
						if(oo == 1 ) printf("grille statique après %d cycles\n",o);
						else
						{
							printf("grille oscillante après %d cycles période %d\n",o,oo);
						}
					}
				}
				while(getchar() != '\n')
					{printf("\n\e[%dA",3); }
				break;
				}
		}
		c = getchar(); 
	}
	return;	
}


