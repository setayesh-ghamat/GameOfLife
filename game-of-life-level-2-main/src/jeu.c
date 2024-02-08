/**
 * @file jeu.c
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 * @brief gestion de jeu de la vie
 */
 
 #include "jeu.h"

extern int (*compte_voisins_vivants)(int, int, grille) ;
extern int vieillissement;

int oscillate_indirect(grille g)
{
	int i, j, q = 0;
	grille temp,gce ;
	alloue_grille(g.nbl,g.nbc,&gce) ;
	alloue_grille(g.nbl,g.nbc,&temp) ;
	copie_grille(g,temp);
	for(i = 0 ; (i < OSCILL_MAX_INDIRECT) && (q == 0) ; i++)
	{
		j = est_oscillante(temp,0) ;
		if(j != 0) q = 1;
		evolue(&temp,&gce) ;
	}
	libere_grille(&gce) ;
	libere_grille(&temp) ;
	if(j == -1) return -1 ;
	if( q == 1 ) return i-1 ; 
	return i ;
} 

int est_oscillante(grille g, int x)
{
	int i = 0 ;
	int j = 1 ;
	grille gc,gce,ref ;
	alloue_grille(g.nbl,g.nbc,&gc) ;
	copie_grille(g,gc);
	alloue_grille(g.nbl,g.nbc,&gce) ;
	for(int i = 0 ; i < x ; i++) evolue(&gc,&gce) ;
	i = 0 ;
	alloue_grille(g.nbl,g.nbc,&ref) ;
	copie_grille(gc,ref);
	while((j < OSCILL_MAX) && (i == 0))
	{
		evolue(&gc,&gce) ;
		if(egale_grille(&ref,&gc) == 1) i = j ;
		j++ ;
	}
	if(morte_grille(&g) == 1 ) i = -1 ;
	libere_grille(&gc);
	libere_grille(&gce);
	libere_grille(&ref);
	return i ;
}

int compte_voisins_vivants_cyclique(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_non_cyclique(int i, int j, grille g){
	int v = 0, l = g.nbl, c = g.nbc;
	v += i > 0 && j > 0 && est_vivante(i-1, j-1, g);
	v += i > 0 && est_vivante(i-1, j, g);
	v += i > 0 && j < c && est_vivante(i-1, j+1, g);
	v += i < l -1 && j > 0 && est_vivante(i+1, j-1, g);
	v += i < l -1 && est_vivante(i+1, j, g);
	v += i < l -1 && j < c && est_vivante(i+1, j+1, g);
	v += j > 0 && est_vivante(i, j-1, g);
	v += j < c && est_vivante(i, j+1, g);
	return v;
}

void evolue (grille *g, grille *gc){
	// copie temporaire de la grille
	copie_grille (*g,*gc); 
	int i,j,l=g->nbl, c = g->nbc,v;
	
	if(vieillissement == 0){
        for (i=0; i<l; i++)
        {
            for (j=0; j<c; ++j)
            {
                v = compte_voisins_vivants(i, j, *gc);
                if (est_vivante(i,j,*g)) 
                {
					// évolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else set_vivante(i,j,*g);
                }
                else 
                { 
					// évolution d'une cellule morte
                  if ( v==3 && (g->cellules[i][j]!=-1)) set_vivante(i,j,*g);
                }
            }
        }
    }

    else{
        for (i=0; i<l; i++)
        {
            for (j=0; j<c; ++j)
            {
                v = compte_voisins_vivants(i, j, *gc);
                if (est_vivante(i,j,*g)) 
                { 
					// évolution d'une cellule vivante avec incrémentation
                    g->cellules[i][j]+=1;
                    if ((v!=2 && v!= 3) || (g->cellules[i][j]>9)) 
						set_morte(i,j,*g);
                }
                else 
                {  // évolution d'une cellule morte
                    if ( v==3 && (g->cellules[i][j]!=-1)) set_vivante(i,j,*g);
                }
            }
        }
    }
	
	return;
}
