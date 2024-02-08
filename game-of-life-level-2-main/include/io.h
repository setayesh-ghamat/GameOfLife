/**
 * @file io.h
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 *@brief affichage d'un trait horizontal pour la grille 
 *@param c Nombres de colonnes 
*/
void affiche_trait (int c);


/**
 *@brief  affichage d'une ligne de la grille
 *@param c Nombres de colonnes 
 *@param ligne Pointeur vers le nombre de lignes
 
*/
void affiche_ligne (int c, int* ligne);

/**
 *@brief  affichage d'une grille
 *@param g Grille à afficher
*/
void affiche_grille (grille g);

/**
 *@brief  effacement d'une grille
 *@param g Grille à effacer
*/
void efface_grille (grille g);


void debut_jeu(grille *g, grille *gc);

#endif
