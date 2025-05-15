#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include "constantes.h"

void afficherOptionsJoueurs();

void gererChoixJoueurs(int positionSourisX, int positionSourisY);

void mouvementIA(int *x, int *y, int taille);

int estPartieTerminee(int x, int y, int taille);

#endif  
