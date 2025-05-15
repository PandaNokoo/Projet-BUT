#include "MenuInteractions.h"
#include "Menu.h"
#include "CreationGrille.h"
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "constantes.h"
#include "MenuAffichage.h"
#include "Sprites.h"




void gererInteractions(int positionSourisX, int positionSourisY) {
    int i,j;
    int caseX,caseY;
    int boutonY1,boutonY2;
    
    for (i = 0; i < MAX_OPTIONS; i++) {
         caseX = 75 + 150;  
         caseY = 130 + (i * 30) - 5;  

        
        if (positionSourisX >= caseX && positionSourisX <= caseX + 20 &&
            positionSourisY >= caseY && positionSourisY <= caseY + 20) {
            
            
            for (j = 0; j < MAX_OPTIONS; j++) {
                casesCochees[j] = 0;
            }
            casesCochees[i] = 1;  
            choisirTaille = i + 3;  
            TailleJeux();  
            break;
        }
    }

    
     boutonY1 = HAUTEUR_FENETRE * 0.3;  
     boutonY2 = boutonY1 + 50;  

    
    if (positionSourisX >= LARGEUR_FENETRE * 0.75 && positionSourisX <= LARGEUR_FENETRE * 0.95 &&
        positionSourisY >= boutonY1 && positionSourisY <= boutonY1 + 40) {
        modeJeu = 1;  
    }

   
    if (positionSourisX >= LARGEUR_FENETRE * 0.75 && positionSourisX <= LARGEUR_FENETRE * 0.95 &&
        positionSourisY >= boutonY2 && positionSourisY <= boutonY2 + 40) {
        modeJeu = 2;  
    }

    
    afficherFondMenu();
    TailleJeux();
    afficherOptionsJoueurs();
}



void gererMouvement(int joueur, int x, int y, int newX, int newY, int taille) {
    int dx = newX - x;
    int dy = newY - y;
     int blockX, blockY;

    /* Vérifie que le déplacement est dans les cases adjacentes uniquement (sans utiliser abs()) */
    if ((dx >= -1 && dx <= 1) && (dy >= -1 && dy <= 1) && grille[newX][newY] == ' ') {
        deplacerPion(joueur, &x, &y, newX, newY);

        
        do {
            printf("Choisissez une case à bloquer (x, y) : ");
            scanf("%d %d", &blockX, &blockY);
        } while (grille[blockX][blockY] != ' ');

        condamnerCase(blockX, blockY);

        if (estPartieTerminee(newX, newY, taille)) {
            printf("Le joueur %d a perdu !\n", joueur);
        }
    } else {
        printf("Deplacement invalide. Vous ne pouvez déplacer le pion que vers une case adjacente libre.\n");
    }
}





void placerSpritePion(int ligne, int colonne, char type, int joueur, int taille) {
    int cell_size = 50;
    int x_start = (LARGEUR_FENETRE - (taille * cell_size)) / 2;
    int y_start = (HAUTEUR_FENETRE - (taille * cell_size)) / 2;

    
    int x = x_start + colonne * cell_size + (cell_size - 25) / 2;
    int y = y_start + ligne * cell_size + (cell_size - 25) / 2;

    
    if (joueur == 1) {
        if (type == 'X') {
            AfficherSprite(spriteCroixBleue, x, y);  
        } else if (type == 'P') {
            AfficherSprite(spritePionBleu, x, y);    
        }
    } else if (joueur == 2) {
        if (type == 'X') {
            AfficherSprite(spriteCroixRouge, x, y);  
        } else if (type == 'P') {
            AfficherSprite(spritePionRouge, x, y);  
        }
    }
}

int gererClicGrille(int positionSourisX, int positionSourisY, int joueur, int taille) {
    int oldX, oldY;
    int cell_size = 50;
    int sprite_size = 25;
    int x_start = (LARGEUR_FENETRE - (taille * cell_size)) / 2;
    int y_start = (HAUTEUR_FENETRE - (taille * cell_size)) / 2;
    int border_thickness = 3; 
    int x, y, k;

    int colonne = (positionSourisX - x_start) / cell_size;
    int ligne = (positionSourisY - y_start) / cell_size;

    if (ligne >= 0 && ligne < taille && colonne >= 0 && colonne < taille) {

        if (modeJeu == 1 && joueur == 2) {
            return 0;  
        }

        if (etapePlacement == 1) {  
            int dx = ligne - (joueur == 1 ? joueur1X : joueur2X);
            int dy = colonne - (joueur == 1 ? joueur1Y : joueur2Y);
            
            int isFirstMove = (joueur == 1 && joueur1X == 0 && joueur1Y == 0 && grille[joueur1X][joueur1Y] != 'A') || 
                              (joueur == 2 && joueur2X == 0 && joueur2Y == 0 && grille[joueur2X][joueur2Y] != 'B');

            if (isFirstMove || ((abs(dx) <= 1) && (abs(dy) <= 1) && grille[ligne][colonne] == ' ')) {
                oldX = (joueur == 1) ? joueur1X : joueur2X;
                oldY = (joueur == 1) ? joueur1Y : joueur2Y;

                /* Efface la position précédente si ce n'est pas le premier coup */
                if (!isFirstMove && grille[oldX][oldY] != 'X') {
                    grille[oldX][oldY] = ' ';  
                    ChoisirCouleurDessin(CouleurParNom("white"));
                    RemplirRectangle(x_start + oldY * cell_size, y_start + oldX * cell_size, cell_size, cell_size);
                    
                    /* Redessine une bordure uniforme sur la case d'origine */
                    ChoisirCouleurDessin(CouleurParNom("black"));
                    for (k = 0; k < border_thickness; k++) {
                        DessinerRectangle(x_start + oldY * cell_size + k, y_start + oldX * cell_size + k,
                                          cell_size - 2 * k, cell_size - 2 * k);
                    }
                }

                if (joueur == 1) {
                    joueur1X = ligne;  
                    joueur1Y = colonne;
                    grille[ligne][colonne] = 'A';
                } else {
                    joueur2X = ligne;  
                    joueur2Y = colonne;
                    grille[ligne][colonne] = 'B';
                }

                if (joueur == 1) {
                    AfficherSprite(spritePionBleu, x_start + colonne * cell_size + (cell_size - sprite_size) / 2,
                                   y_start + ligne * cell_size + (cell_size - sprite_size) / 2);
                } else {
                    AfficherSprite(spritePionRouge, x_start + colonne * cell_size + (cell_size - sprite_size) / 2,
                                   y_start + ligne * cell_size + (cell_size - sprite_size) / 2);
                }

                etapePlacement = 2;
                return 1;  
            } else {
                afficherMessageGraphique("Deplacement invalide. Case non adjacente.");
                return 0;  
            }
        } else if (etapePlacement == 2) {  
            if (grille[ligne][colonne] == ' ') {  
                grille[ligne][colonne] = 'X';
                 x = x_start + colonne * cell_size + (cell_size - sprite_size) / 2;
                 y = y_start + ligne * cell_size + (cell_size - sprite_size) / 2;

                if (joueur == 1) {
                    AfficherSprite(spriteCroixBleue, x, y);
                } else {
                    AfficherSprite(spriteCroixRouge, x, y);
                }
                
                etapePlacement = 1;  /* Revient à l'étape de placement du pion */
                tourJoueur = (tourJoueur == 1) ? 2 : 1;  /* Change de joueur */
                return 1;  /* Placement de croix valide */
            } else {
                
                return 0;  /* Mouvement invalide */
            }
        }
    } else {
        afficherMessageGraphique("Position invalide. Hors de la grille.");
        return 0;  /* Mouvement invalide */
    }
return 0;
}





