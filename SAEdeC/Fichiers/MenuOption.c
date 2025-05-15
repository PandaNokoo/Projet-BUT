#include "MenuOption.h"
#include "CreationGrille.h"
#include "MenuInteractions.h"
#include <graph.h>
#include "constantes.h"
#include <time.h>
#include "MenuAffichage.h"
#include "Sprites.h"
#include <stdlib.h> 



extern int joueur1X, joueur1Y;

int spritePionIA = -1;

void afficherOptionsJoueurs() {
    int optionY = HAUTEUR_FENETRE * 0.3;

    ChoisirCouleurDessin(modeJeu == 1 ? CouleurParNom("red") : CouleurParNom("lightgray"));
    RemplirRectangle(LARGEUR_FENETRE * 0.75, optionY, LARGEUR_FENETRE * 0.2, 40);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(LARGEUR_FENETRE * 0.75 + 35, optionY + 30, "1 Joueur", 2);

    ChoisirCouleurDessin(modeJeu == 2 ? CouleurParNom("red") : CouleurParNom("lightgray"));
    RemplirRectangle(LARGEUR_FENETRE * 0.75, optionY + 50, LARGEUR_FENETRE * 0.2, 40);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(LARGEUR_FENETRE * 0.75 + 35, optionY + 80, "2 Joueurs", 2);
}

void gererChoixJoueurs(int positionSourisX, int positionSourisY) {
    int boutonY1 = HAUTEUR_FENETRE * 0.3;
    int boutonY2 = boutonY1 + 50;

    if (positionSourisX >= LARGEUR_FENETRE * 0.75 && positionSourisX <= LARGEUR_FENETRE * 0.95 &&
        positionSourisY >= boutonY1 && positionSourisY <= boutonY1 + 40) {
        modeJeu = (modeJeu == 1) ? 0 : 1;
    }

    if (positionSourisX >= LARGEUR_FENETRE * 0.75 && positionSourisX <= LARGEUR_FENETRE * 0.95 &&
        positionSourisY >= boutonY2 && positionSourisY <= boutonY2 + 40) {
        modeJeu = (modeJeu == 2) ? 0 : 2;
    }

    EffacerEcran(CouleurParNom("lightblue"));
    TailleJeux();
    afficherOptionsJoueurs();
}




void mouvementIA(int *x, int *y, int taille) {
    int dx[] = {1, -1, 0, 0};  /* Directions : bas, haut, droite, gauche */
    int dy[] = {0, 0, 1, -1};
    int newX, newY, i, k,j;
    int cell_size = 50;
    int x_start = (LARGEUR_FENETRE - (taille * cell_size)) / 2;
    int y_start = (HAUTEUR_FENETRE - (taille * cell_size)) / 2;
    int border_thickness = 3;
    int posX, posY, bx, by;
    int bestMoveX = -1, bestMoveY = -1, bestMoveScore = -1000;
    int blockX = -1, blockY = -1, blockScore = -1000;

    for (i = 0; i < 4; i++) {
        newX = *x + dx[i];
        newY = *y + dy[i];

        if (newX >= 0 && newX < taille && newY >= 0 && newY < taille && grille[newX][newY] == ' ') {
            int score = 0;

            /* Calculer le nombre de cases libres après ce mouvement */
            for ( j = 0; j < 4; j++) {
                int adjX = newX + dx[j];
                int adjY = newY + dy[j];
                if (adjX >= 0 && adjX < taille && adjY >= 0 && adjY < taille && grille[adjX][adjY] == ' ') {
                    score++;
                }
            }

            /* Choisir le mouvement avec le meilleur score */
            if (score > bestMoveScore) {
                bestMoveScore = score;
                bestMoveX = newX;
                bestMoveY = newY;
            }
        }
    }

    /* Déplacer l'IA */
    if (bestMoveX != -1 && bestMoveY != -1) {
        grille[*x][*y] = ' ';
        ChoisirCouleurDessin(CouleurParNom("white"));
        RemplirRectangle(x_start + (*y) * cell_size, y_start + (*x) * cell_size, cell_size, cell_size);

        /* Redessiner bordure de l'ancienne case */
        ChoisirCouleurDessin(CouleurParNom("black"));
        for (k = 0; k < border_thickness; k++) {
            DessinerRectangle(x_start + (*y) * cell_size + k, y_start + (*x) * cell_size + k, cell_size - 2 * k, cell_size - 2 * k);
        }

        *x = bestMoveX;
        *y = bestMoveY;
        grille[bestMoveX][bestMoveY] = 'B';

        /* Dessiner le pion rouge */
        posX = x_start + bestMoveY * cell_size + (cell_size - 25) / 2;
        posY = y_start + bestMoveX * cell_size + (cell_size - 25) / 2;
        AfficherSprite(spritePionRouge, posX, posY);

        /* Redessiner bordure de la nouvelle case */
        ChoisirCouleurDessin(CouleurParNom("black"));
        for (k = 0; k < border_thickness; k++) {
            DessinerRectangle(x_start + bestMoveY * cell_size + k, y_start + bestMoveX * cell_size + k, cell_size - 2 * k, cell_size - 2 * k);
        }
    }

    
    blockX = -1; 
    blockY = -1; 
    blockScore = -1000;

    /* Explorer toutes les cases autour de l'adversaire */
    for (i = 0; i < 4; i++) {
        bx = joueur1X + dx[i];
        by = joueur1Y + dy[i];

        if (bx >= 0 && bx < taille && by >= 0 && by < taille && grille[bx][by] == ' ') {
            int score = 0;

            /* Calculer combien de cases l'adversaire perd si cette case est bloquée */
            for (j = 0; j < 4; j++) {
                int adjX = joueur1X + dx[j];
                int adjY = joueur1Y + dy[j];
                if (adjX >= 0 && adjX < taille && adjY >= 0 && adjY < taille && grille[adjX][adjY] == ' ') {
                    score++;
                }
            }

            /* Prioriser le blocage des cases qui limitent le plus l'adversaire */
            if (score > blockScore) {
                blockScore = score;
                blockX = bx;
                blockY = by;
            }
        }
    }

    /* Bloquer la meilleure case trouvée */
    if (blockX != -1 && blockY != -1) {
        grille[blockX][blockY] = 'X';
        placerSpritePion(blockX, blockY, 'X', 2, taille);

        /* Redessiner bordure de la case bloquée */
        ChoisirCouleurDessin(CouleurParNom("black"));
        for (k = 0; k < border_thickness; k++) {
            DessinerRectangle(x_start + blockY * cell_size + k, y_start + blockX * cell_size + k, cell_size - 2 * k, cell_size - 2 * k);
        }
    }
}


 

