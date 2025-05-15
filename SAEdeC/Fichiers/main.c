#include <stdio.h>       
#include <stdlib.h>      
#include "Menu.h"
#include "AffichageGrille.h"
#include "CreationGrille.h"
#include "MenuInteractions.h"
#include "MenuOption.h"
#include "Sprites.h"
#include "Score.h"
#include "Recommencer.h"
#include "constantes.h"
#include "MenuAffichage.h"  

int main(void) {
    int positionSourisX, positionSourisY;
    unsigned long suivant = Microsecondes() + CYCLE;
     
       int boutonX, boutonY;
      

   
    if (InitialiserGraphique() == -1) {
        fprintf(stderr, "Erreur lors de l'initialisation graphique.\n");
        return EXIT_FAILURE;
    }


    CreerFenetre(20, 20, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    chargerSprites();
    chargerSpritesPions();
    afficherFondMenu();
    TailleJeux();

   

    while (1) {
        if (SourisCliquee()) {
            SourisPosition();
            positionSourisX = _X;
            positionSourisY = _Y;

            /* État de configuration du jeu (choix de taille et mode de jeu) */
            if (etatJeu == 1) {  
                gererInteractions(positionSourisX, positionSourisY);
                afficherGrilleSiValidee(positionSourisX, positionSourisY);

                 boutonX = (LARGEUR_FENETRE - LARGEUR_BOUTON) / 2;
                 boutonY = 400;

                /* Vérifie si les options de taille et de mode de jeu sont valides */
                if (positionSourisX >= boutonX && positionSourisX <= boutonX + LARGEUR_BOUTON &&
                    positionSourisY >= boutonY && positionSourisY <= boutonY + HAUTEUR_BOUTON) {
                    
                    if (choisirTaille >= 3 && choisirTaille <= 9 && modeJeu != 0) {
                        EffacerEcran(CouleurParNom("white"));

                        if (modeJeu == 1) {
                            afficherFondJeu1();
                        } else if (modeJeu == 2) {
                            afficherFondJeu2();
                        }

                        initialiserJeu(choisirTaille);
                        afficherGrilleJeu(choisirTaille);
                        

                       
                        etatJeu = 2; 
                        tourJoueur = 1;
                        etapePlacement = 1;
                    } else {
                        afficherMessageGraphique("Veuillez choisir une taille et un mode de jeu.");
                    }
                }
            } 
            /* Phase de jeu principale */
            else if (etatJeu == 2) {  
                /* Mode 1 joueur (Joueur contre IA) */
                if (modeJeu == 1) {
                    if (tourJoueur == 1) {  
                        if (etapePlacement == 1) { 
                            
                            if (gererClicGrille(positionSourisX, positionSourisY, 1, choisirTaille)) {
                                etapePlacement = 2;  
                            }
                        } else if (etapePlacement == 2) {  
                            afficherMessageGraphique("");
                            if (gererClicGrille(positionSourisX, positionSourisY, 1, choisirTaille)) {
                                etapePlacement = 1;  
                                tourJoueur = 2;
                            }
                        }

                        if (estPartieTerminee(joueur1X, joueur1Y, choisirTaille)) {
                            etatJeu = 3;      
                            afficherScore(2);  
                        }
                    }
                }
                /* Mode 2 joueurs (Humain contre humain) */ 
                else if (modeJeu == 2) {
                    if (tourJoueur == 1) {  
                        if (etapePlacement == 1) {  
                            
                            if (gererClicGrille(positionSourisX, positionSourisY, 1, choisirTaille)) {
                                etapePlacement = 2;  
                            }
                        } else if (etapePlacement == 2) {  
                            
                            if (gererClicGrille(positionSourisX, positionSourisY, 1, choisirTaille)) {
                                etapePlacement = 1;  
                                tourJoueur = 2;
                            }
                        }

                        if (estPartieTerminee(joueur1X, joueur1Y, choisirTaille)) {
                            etatJeu = 3;       
                            afficherScore(2);  
                        }
                    } 
                    else if (tourJoueur == 2) {  /* Tour du Joueur 2 */
                        if (etapePlacement == 1) {  
                            
                            if (gererClicGrille(positionSourisX, positionSourisY, 2, choisirTaille)) {
                                etapePlacement = 2;  
                            }
                        } else if (etapePlacement == 2) {  
                            
                            if (gererClicGrille(positionSourisX, positionSourisY, 2, choisirTaille)) {
                                etapePlacement = 1;  
                                tourJoueur = 1;
                            }
                        }

                        if (estPartieTerminee(joueur2X, joueur2Y, choisirTaille)) {
                            etatJeu = 3;      
                            afficherScore(1);  
                        }
                    }
                }
            }

            /* Tour du Joueur 2 (IA) sans clic pour le mode 1 joueur */
            if (etatJeu == 2 && modeJeu == 1 && tourJoueur == 2) {  
                mouvementIA(&joueur2X, &joueur2Y, choisirTaille);  

                if (estPartieTerminee(joueur2X, joueur2Y, choisirTaille)) {
                    etatJeu = 3;      
                    afficherScore(1);  
                } else {
                    tourJoueur = 1;  
                }
            }

            /* Gestion du mode fin de jeu avec retour au menu */
            if (etatJeu == 3) {
                revenirAuMenu();  
                etatJeu = 1;      
            }
        }

        if (Microsecondes() > suivant) {
            suivant = Microsecondes() + CYCLE;
        }
    }

    libererSprites();
    libererSpritesPions();
    FermerGraphique();
    return 0;
}
