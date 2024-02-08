/**
 * @file grille.h
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 */
 
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define OSCILL_MAX 1000 
#define OSCILL_MAX_INDIRECT 1000


// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 *@brief Allouer une grille et initialiser les cellules à mortes
 *@param l nombres de lignes de la grille
 *@param c nombres de colonnes de la grille
 *@param g grille à allouer
*/
void alloue_grille (int l, int c, grille* g);


/**
 *@brief Libèrer une grille
 *@param g grille à libérer
*/
void libere_grille (grille* g);

/**
 *@brief Allouer et initialiser la grille g à partir d'un fichier
 *@param filename Nom du fichier source contenant la grille
 *@param g grille à initialiser
*/
void init_grille_from_file (char * filename, grille* g);


/**
 *@brief Rend vivante la cellule(i,j) de la grille g
 *@param i Ligne de la cellule à rendre vivante
 *@param j Colonne de la cellule à rendre vivante
 *@param g Grille contenant la cellule à rendre vivante
*/
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 *@brief Rend morte la cellule[i][j] de la grille g
 *@param i Ligne de la cellule à rendre morte
 *@param j Colonne de la cellule à rendre morte
 *@param g Grille contenant la cellule à rendre morte
*/
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}


/**
 *@brif teste si la cellule(i,j) de la grille g est vivante
 *@param i Ligne de la cellule à tester
 *@param j Colonne de la cellule à tester
 *@param g Grille contenant la cellule à tester
*/
static inline int est_vivante(int i, int j, grille g)
    {
        return ((1<=g.cellules[i][j]) && (g.cellules[i][j]<=9));
    }

/**
 *@brif recopie grill gs dans grille gd (sans allocation)
 *@param i gs Grille à copier
 *@param param gd Grille copiée
*/
void copie_grille (grille gs, grille gd);

/**
 * @brief Teste si la cellule (i, j) de la grille g est non-viable.
 * @param i Ligne de la cellule à vérifier.
 * @param j Colonne de la cellule à vérifier
 * @param g Grille à vérifier
 * @return 1 si la cellule est non-viable, 0 sinon.
 */
static inline int est_non_viable(int i, int j, grille g)
    {
        return g.cellules[i][j] == -1;
    }

/**
 * @brief Rend non-viable la cellule (i, j) de la grille g.
 * @param i Ligne de la cellule à rendre non-viable.
 * @param j Colonne de la cellule à rendre non-viable.
 * @param g Grille dans laquelle rendre une cellule non-viable.
 */
static inline void set_non_viable(int i, int j, grille g)
    {
        g.cellules[i][j] = -1;
    }

/**
 * @brief test l'égalité entre les deux grilles
 * @param g1 grille*
 * @param g2 grille*
 * @return int 1 si les deux grilles sont égalles 0 sinon
 */
int egale_grille(grille *g1 , grille *g2);

/**
 * @brief test si tous les cellules sont mortes
 * @param grille g
 * @return int 1 si tous les cellules sont mortes 0 sinon
 */
int morte_grille(grille *g);

#endif
