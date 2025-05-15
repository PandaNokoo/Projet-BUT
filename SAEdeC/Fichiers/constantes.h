#ifndef CONSTANTES_H
#define CONSTANTES_H

/* Définitions de constantes globales */
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define LARGEUR_BOUTON 200
#define HAUTEUR_BOUTON 50
#define MAX_OPTIONS 7
#define MAX_TAILLE 10

#define CYCLE 10000L  

/* Variables globales externes (utilisées dans plusieurs fichiers) */
extern int choisirTaille;
extern int modeJeu;
extern int etatJeu;
extern int etapePlacement;
extern int tourJoueur;
extern int casesCochees[MAX_OPTIONS];
extern char grille[MAX_TAILLE][MAX_TAILLE];
extern int joueur1X, joueur1Y;

/* Noms d'images */
#define IMAGE_MENU "ImageMenu.jpg"
#define IMAGE_FOND1 "ImageFond1.jpg"
#define IMAGE_FOND2 "ImageFond2.jpg"

#endif
