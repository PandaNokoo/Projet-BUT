#include "Menu.h"
#include "AffichageGrille.h"
#include "CreationGrille.h"
#include "MenuAffichage.h"
#include "MenuInteractions.h"
#include "MenuOption.h"
#include "Recommencer.h"
#include "Score.h"
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "constantes.h"
#include "Sprites.h"

#define CYCLE 10000L  

/* Déclarations de variables globales */
int casesCochees[MAX_OPTIONS] = {0}; 
int choisirTaille = 0;
int modeJeu = 0;
int etatJeu = 1; 
int tourJoueur = 1;  
int etapePlacement = 1;  
int joueur1X = 0, joueur1Y = 0;
int joueur2X = 0, joueur2Y = 0;

/* Affiche un message graphique en bas de l'écran. */
void afficherMessageGraphique(const char *message) {
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(50, HAUTEUR_FENETRE - 30, (char *)message, 2);  
}

/* Affiche la grille si les options de jeu sont correctement sélectionnées et si le bouton est cliqué. */
void afficherGrilleSiValidee(int positionSourisX, int positionSourisY) {
    int boutonX = (LARGEUR_FENETRE - LARGEUR_BOUTON) / 2;
    int boutonY = 400;
    static int grilleAffichee = 0;

    /* Vérifie si la taille et le mode de jeu sont valides */
    if (choisirTaille >= 3 && choisirTaille <= 9 && modeJeu != 0) {
        if (positionSourisX >= boutonX && positionSourisX <= boutonX + LARGEUR_BOUTON &&
            positionSourisY >= boutonY && positionSourisY <= boutonY + HAUTEUR_BOUTON) {
            
            grilleAffichee = 0;

            /* Affiche la grille si elle n'est pas déjà affichée */
            if (!grilleAffichee) {
                EffacerEcran(CouleurParNom("white"));

                /* Affiche le fond en fonction du mode de jeu */
                if (modeJeu == 1) {
                    afficherFondJeu1();
                } else if (modeJeu == 2) {
                    afficherFondJeu2();
                }

                initialiserJeu(choisirTaille);  /* Initialise la grille de jeu */
                afficherGrilleJeu(choisirTaille);  /* Affiche la grille sur l'écran */
                afficherMessageGraphique("Cliquez sur la grille pour jouer.");

                grilleAffichee = 1;  /* Indique que la grille a été affichée */
            }
        }
    } else {
        /* Message d'avertissement si les options de jeu ne sont pas correctement sélectionnées */
        if (positionSourisX >= boutonX && positionSourisX <= boutonX + LARGEUR_BOUTON &&
            positionSourisY >= boutonY && positionSourisY <= boutonY + HAUTEUR_BOUTON) {
            afficherMessageGraphique("Veuillez choisir une taille et un mode de jeu.");
        }
    }
}
