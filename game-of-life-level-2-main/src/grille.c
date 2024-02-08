/**
 * @file grille.c
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 * @brief gestion des grilles
 */


#include "grille.h"

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,m,l,c,vivantes=0;
	int nonViables = 0;
	
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
        fscanf(pfile, "%d", &nonViables);
        for (m=0; m<nonViables; ++m){
        fscanf(pfile, "%d", & i);
        fscanf(pfile, "%d", & j);
        set_non_viable(i,j,*g);
    }
	
	fclose (pfile);
	return;
}
void alloue_grille (int l, int c, grille* g){
	g->nbl=l;
	g->nbc=c;

	g->cellules=(int **) malloc(l*sizeof(int*));
	for (int i = 0; i < g->nbl; i++)
	{
		g->cellules[i] = (int *)malloc(g->nbc*sizeof(int));
		for (int j = 0; j < c; j++)
		{
			set_morte(i,j,*g);
		}
	}
}

void libere_grille (grille* g){

	for(int i=0;i<g->nbl;i++){
	free(g->cellules[i]);
	}
	free(g->cellules);
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

int morte_grille(grille *g)
{
	int res = 1 ;
	int i = 0 , j = 0 ;
	while(i < g->nbl)
	{	
		j = 0 ;
		while((j < g->nbc) && (res == 1))
		{ 
			if (est_vivante(i,j,*g)) res = 0 ;
			j++ ;
		}
		i++ ;
	}
	return res ;
}

int egale_grille(grille *g1 , grille *g2)
{
	int res = 1 ;
	int i = 0 , j = 0 ;
	while(i < g1->nbl)
	{
		j = 0 ;
		while((j < g1->nbc) && (res == 1))
		{ 
			if(g1->cellules[i][j] != g2->cellules[i][j]) res = 0 ;
			j++ ;
		}
		i++ ;
	}
	return res ;
}


