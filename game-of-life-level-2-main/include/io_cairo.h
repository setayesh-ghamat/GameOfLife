/**
 * @file io_cairo.h
 * @author GHAMAT Setayesh
 * @date 04/12/2021
 */

#ifndef __IO_CAIRO_H
#define __IO_CAIRO_H

#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <unistd.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "grille.h"
#include "jeu.h"
#define SIZEX 500
#define SIZEY 500
#define SIZECELL 20
/**
 * @brief Début du jeu de la vie.
 * @param *g Pointeur sur la grille initiale.
 * @param *gc Pointeur sur une copie de la grille initiale.
 */
void debut_jeu_cairo (grille *g, grille *gc);

/**
 * @brief Afficher la grille et les informations liées à la grille sur la fenêtre.
 * @param g Pointeur sur la grille initiale.
 * @param *cairo_surface_t Pointeur sur une copie de la grille initiale.
 * @return Affichage dans la fenêtre. 
 */
void Afficher_grille_cairo(grille g, cairo_surface_t *surface);

/**
 * @brief Affichage d'une cellule dans la grille.
 * @param g Grille à Afficher.
 * @param i Coordonée sur l'axe des ordonnées de la cellule à Afficher.
 * @param j Coordonée sur l'axe des abscisses de la cellule à Afficher.
 * @param *cairo_surface_t surface Surface cairo sur laquelle Afficher la cellule.
 * @return Affichage dans la fenêtre.
 */
void draw_cell_cairo(grille g,  int i, int j, cairo_surface_t *surface);

/**
 * @brief Obtenir la nouvelle grille à travers la fenêtre, sans passer par le terminal.
 * @param t Chaine de caractères contenant le chemin vers la grille.
 * @param *dpy Pointeur sur un "Display" utilisé pour les événements.
 * @param e Evénement X11.
 * @param *surface Surface cairo sur laquelle Afficher du texte.
 * @return Chaine de caractères contenant le chemin vers la grille dans t.
 */
void read_string_cairo(char t[], Display* dpy, XEvent e, cairo_surface_t *surface);


/**
 * @brief Afficher des informations sur la grille en cours d'évolution sur la fenêtre.
 * @param *cr Pointeur sur la surface cairo sur laquelle les informations seront affichées.
 * @return Chaine de caractères contenant le chemin vers la grille dans t.
 */
void Afficher_infos_cairo(cairo_t *cr);
#endif
