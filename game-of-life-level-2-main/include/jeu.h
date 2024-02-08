/**
 * @file jeu.h
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 */

#ifndef __JEU_H
#define __JEU_H
#include "grille.h"

/**
 * @brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * @param param i dividende.
 * @param m diviseur.
 * @return reste de la disvion.
*/
static inline int modulo(int i, int m) 
    {
        return (i+m)%m;
    }

/**
 * @brief Compte le nombre de voisins d'une cellule (cyclique).
 * @param i Ligne de la cellule dont on cherche les voisins
 * @param j Colonne de la ligne dont on cherche les voisins.
 * @param g Grille dans laquelle la cellule se trouve.
 * @return Nombre de voisins de celulle (i,j).
*/
int compte_voisins_vivants_cyclique(int i, int j, grille g);

/**
 * @brief Compte le nombre de vosisins d'une cellule (non-cyclique).
 * @param i Ligne de la cellule dont on cherche les voisins.
 * @param j Colonne de la ligne dont on cherche les voisins.
 * @param g Grille dans laquelle la cellule se trouve.
 * @return Nombre de voisins de (i,j).
*/
int compte_voisins_vivants_non_cyclique(int i, int j, grille g);

/** 
 * @brief Fait évoluer la grille g d'un pas le temps sans vieillissement.
 * @param *g Grille à faire évoluer.
 * @param *gc Copie de *g.
*/
void evolue (grille *g, grille *gc);

/**
 * @brief donne la période de la grille
 * @param g grille
 * @param x int
 * @return int la périod de oscillation de la grille
*/
int est_oscillante(grille g, int x);

/**
 * @brief donne le nombre de cycle avant que la grille devient oscillante
 * @param g grille
 * @return int la cycle avant que la grille devient oscillante
*/
int oscillate_indirect(grille g);

#endif