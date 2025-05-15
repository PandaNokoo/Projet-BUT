#ifndef CREATION_GRILLE_H
#define CREATION_GRILLE_H

#include "constantes.h"



void initialiserJeu(int taille);

void deplacerPion(int joueur, int *x, int *y, int newX, int newY);

void condamnerCase(int x, int y);

int deplacementPossible(int x, int y, int taille);

void mettreAJourCase(int x, int y);

int estPartieTerminee(int x, int y, int taille);  /* Ajouté ici après le déplacement */

#endif  
