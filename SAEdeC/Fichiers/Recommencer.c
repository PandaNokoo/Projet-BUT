#include "Recommencer.h"
#include "Menu.h"
#include "AffichageGrille.h"
#include "CreationGrille.h"
#include "MenuAffichage.h"
#include <graph.h>
#include "constantes.h"





void revenirAuMenu() {
    int i, j;
    EffacerEcran(CouleurParNom("white"));

    choisirTaille = 0;                
    modeJeu = 0;                      
    etatJeu = 1;                      
    etapePlacement = 1;
    tourJoueur = 1;

    
    for (i = 0; i < MAX_OPTIONS; i++) {
        casesCochees[i] = 0;          
    }

    
    for (i = 0; i < MAX_TAILLE; i++) {
        for (j = 0; j < MAX_TAILLE; j++) {
            grille[i][j] = ' ';
        }
    }

    
    joueur1X = 0; 
    joueur1Y = 0;
    joueur2X = 0;
    joueur2Y = 0;

    
    afficherFondMenu();
    TailleJeux();
}
