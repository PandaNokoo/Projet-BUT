#ifndef MENU_H
#define MENU_H
#include "constantes.h"

#define MAX_OPTIONS 7

extern int choisirTaille;
extern int modeJeu;
extern int etatJeu;
extern int tourJoueur;
extern int etapePlacement;
extern int joueur1X, joueur1Y;
extern int joueur2X, joueur2Y;


void afficherMessageGraphique(const char *message);

void afficherGrilleSiValidee(int positionSourisX, int positionSourisY);

#endif  
