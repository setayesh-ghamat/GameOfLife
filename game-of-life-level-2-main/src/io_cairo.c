/**
 * @file io_cairo.c
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 * @brief affichage en mode graphic
 */

#include "io_cairo.h"

int vieillissement=0;  
int cyclique=0;
char *tempsEvolution;
int temps=0;
int o;
int oo;
int text=-1;
char str[12];


int (*compte_voisins_vivants)(int, int, grille)=compte_voisins_vivants_cyclique ;

void affiche_grille_cairo(grille g, cairo_surface_t *surface){
    int l=g.nbl, c=g.nbc;
    int x = SIZEX/2-(c*SIZECELL)/2, y = SIZEY/2-(l*SIZECELL)/2;
       
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0.0,0.0,0.26);
    cairo_paint(cr);
    affiche_infos_cairo(cr);
    
    cairo_set_source_rgb(cr, 0.67,0.67,0.67);
    
    for(int i = 0; i <= c; i++){
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x, y+l*SIZECELL);
        cairo_stroke (cr);
        x += SIZECELL;
    }

    x = SIZEX/2-(c*SIZECELL)/2, y = SIZEY/2-(l*SIZECELL)/2;
    for(int i = 0; i <= l; i++){
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x+c*SIZECELL, y);
        cairo_stroke (cr);
        y += SIZECELL;
    }

    for(int j = 0; j < c; j++){
      for(int i = 0; i < l; i++){
            if(g.cellules[i][j] != 0) draw_cell_cairo(g, i, j, surface);
        }
    }
    cairo_destroy(cr);
}

void draw_cell_cairo(grille g, int i, int j, cairo_surface_t *surface){
    int x = SIZEX/2-(g.nbc*SIZECELL)/2, y = SIZEY/2-(g.nbl*SIZECELL)/2;
    cairo_t *cr;
    cr = cairo_create(surface);
    
    float colors_r[8] = {120, 167.0/256, 187.0/256, 202.0/256, 219.0/256, 131.0/256, 109.0/256, 87.0/256};
    float colors_g[8] = {0.40, 195.0/256, 167.0/256, 139.0/256, 112.0/256, 67.0/256, 56.0/256, 44.0/256};
    float colors_b[8] = {.100, 167.0/256, 187.0/256, 202.0/256, 219.0/256, 88.0/256, 73.0/256, 58.0/256};
    
    if(g.cellules[i][j] == -1) cairo_set_source_rgb(cr, 225,225,0.0);
    else if(vieillissement) cairo_set_source_rgb(cr, colors_r[g.cellules[i][j]-1], colors_g[g.cellules[i][j]-1], colors_b[g.cellules[i][j]-1]);
    else cairo_set_source_rgb(cr, colors_r[0], colors_g[0], colors_b[0]);
    cairo_rectangle(cr, x+(j * SIZECELL)+4, y+(i * SIZECELL)+4, 13, 13);
    cairo_fill(cr);
    cairo_destroy(cr);
}

void read_string_cairo(char t[], Display* dpy, XEvent e, cairo_surface_t *surface){
	text=-1;
	temps=0;
    int nbre;
    char chaine[50];
    cairo_t *cr;
    cr = cairo_create(surface);
    for(int i = 0; i < 50; i++) {
        chaine[i] = 0;
        t[i] = 0;
    }
    KeySym touche;
    int i = 0;
    while(chaine[0] != 13){
        cairo_set_source_rgb(cr, 0.0,0.0,0.26);
        cairo_paint(cr);
        cairo_set_source_rgb(cr, 0.67,0.67,0.67);
        cairo_move_to(cr, 5, 10);
        cairo_show_text(cr, "Nouvelle grille:");
        cairo_move_to(cr, 85, 10);
        t[i] = '\0';
        cairo_show_text(cr, t);
        XNextEvent(dpy, &e);
        if(e.type == KeyPress){
          nbre = XLookupString(&e.xkey, chaine, 20, &touche, 0);
          if (chaine[0] == 8) i--;
          else if(chaine[0] != 0){
              chaine[nbre] = 0;
              t[i] = chaine[0];
              i++;
        }
      }
    }
    t[i-1] = '\0';
}

void affiche_infos_cairo(cairo_t *cr){
    
  cairo_set_source_rgb(cr, 260,260,260);
  cairo_move_to(cr, 5, 10);
  cairo_show_text(cr, "Jeu de la vie ");
  
  cairo_move_to(cr, 5, 35);
  if(vieillissement) cairo_show_text(cr, "Vieillissement activé");
  else cairo_show_text(cr, "Vieillissement désactivé.");
  cairo_move_to(cr, 5, 50);
  if(cyclique) cairo_show_text(cr, "Mode cyclique activé");
  else cairo_show_text(cr, "Mode cyclique désactivé");
  
  cairo_move_to(cr, 5, 65);
  
  tempsEvolution = (char *)malloc(4*sizeof(char));
	sprintf (tempsEvolution, "%d", temps);
  cairo_show_text(cr, "Cycle d'évolution: ");
  cairo_move_to(cr, 103, 65);
  cairo_show_text(cr,tempsEvolution);
  
  cairo_move_to(cr, 5, 80);
  if(text==-1)
  cairo_show_text(cr, "Mode d'oscillation: appuyez sur 'o' ");
  	
 	if(text==0)
	cairo_show_text (cr, "grille vide");
	if(text==1)
	cairo_show_text (cr, "grille pas oscillante");
	if(text==2)
	cairo_show_text (cr, "grille statique");
	if(text==3)
	{								
	cairo_show_text (cr, "grille oscillante de période ");
    	sprintf(str, "%d", o);
	cairo_show_text (cr, str);
			}
	if(text==4){
	cairo_show_text (cr, "grille statique après ");
    	sprintf(str, "%d", o);
	cairo_show_text (cr, str);
	cairo_show_text (cr, " cycles");
	}
	if(text==5){
	cairo_show_text (cr, "grille oscillante après ");
    	sprintf(str, "%d", o);
	cairo_show_text (cr, str);
	cairo_show_text (cr, " cycles période ");
	sprintf(str, "%d", oo);
	cairo_show_text (cr, str) ;
	}								
}
void augmentation_temps(){
	temps++;
}

void debut_temps(){
	temps = 0;
}

void debut_jeu_cairo (grille *g, grille *gc){
    Display *dpy;
    Window rootwin;
    Window win;
    XEvent e;
    int scr;
    int nbre;
    char chaine[20];
    KeySym touche;
    debut_temps();
    char t[50];
    
    if(!(dpy=XOpenDisplay(NULL))){
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }

    scr = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, scr);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
                              BlackPixel(dpy, scr), BlackPixel(dpy, scr));

    XStoreName(dpy, win, "GAME OF LIFE");
    XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask );
    XMapWindow(dpy, win);

    cairo_surface_t *cs;
    cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			affiche_grille_cairo(*g,cs) ;
		} else if(e.type==ButtonPress){
			if(e.xbutton.button == 1) {
			evolue(g,gc);
			augmentation_temps();
			}
			else {
                break;
            }
		} 
    else if(e.type==KeyPress){
            nbre = XLookupString(&e.xkey, chaine, 20, &touche, 0);
            chaine[nbre] = 0;
            switch(chaine[0]){
                
                // touche 'c' pour la modification du voisinage cyclique
                 case 'c':
                { 
                    cyclique = !cyclique;
                    if(cyclique) compte_voisins_vivants = compte_voisins_vivants_cyclique;
                    else compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
                    break;
                }
                // touche 'v' pour activer/désactiver le vieillissement
                case 'v':
                { 
                    if(vieillissement==0) {
                        vieillissement=1;
                    }
                    else {
                        vieillissement=0;
                    }
                    break;
                }
              
              case 'n':
                {
                    read_string_cairo(t, dpy, e, cs);
    
                    libere_grille(g);
                    libere_grille(gc);
                    init_grille_from_file(t, g);
                    alloue_grille(g->nbl , g->nbc, gc);
                  
                    break;
                }
              case 'o':
			{
			if(morte_grille(g)) 
				{
                    //grille vide
                    text=0;
				}
			else
				{
					 o = oscillate_indirect(*g) ;
					if ((o == OSCILL_MAX_INDIRECT) || (o ==-1)) 
					text=1;
					
					else if (o == 0) 
						{
						o = est_oscillante(*g,o) ;
						if(o == 1)
						text=2; 
						
						else
						{
						text=3;
						
						}
						}
					else 
					{
						int oo = est_oscillante(*g,o) ;
						if(oo == 1 )
						{
						text=4;
						
						}
						else
						{
						text=5;
					
						}
					}
				}
					break ;
				}
                default :
                {
                    break;
                }
        }
            
    }
		affiche_grille_cairo(*g, cs);
  }
    //Détruire l'objet
	cairo_surface_destroy(cs); 
    //Fermer la fenêtre
	XCloseDisplay(dpy); 
	return ;
}


