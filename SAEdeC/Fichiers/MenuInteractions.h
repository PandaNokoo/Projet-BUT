#ifndef MENU_INTERACTIONS_H
#define MENU_INTERACTIONS_H

#include "constantes.h"

void gererInteractions(int positionSourisX, int positionSourisY);

void gererMouvement(int joueur, int x, int y, int newX, int newY, int taille);

int gererClicGrille(int positionSourisX, int positionSourisY, int joueur, int taille);

void placerSpritePion(int x, int y, char type, int joueur, int taille);

#endif  
