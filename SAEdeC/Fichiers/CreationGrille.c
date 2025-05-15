#include "CreationGrille.h"
#include <stdlib.h>
#include "constantes.h"
#include <graph.h> 

char grille[MAX_TAILLE][MAX_TAILLE]; 

void initialiserJeu(int taille) {
    int i, j;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            grille[i][j] = ' '; 
        }
    }
}



void deplacerPion(int joueur, int *x, int *y, int newX, int newY) {
    grille[*x][*y] = ' ';  
    *x = newX;
    *y = newY;
    grille[newX][newY] = (joueur == 1) ? 'A' : 'B';  
}


void condamnerCase(int x, int y) {
    if (grille[x][y] == ' ') {
        grille[x][y] = 'X';  
    }
}


int deplacementPossible(int x, int y, int taille) {
    int i,j,newX,newY;
    for (i = -1; i <= 1; i++) {
        for ( j = -1; j <= 1; j++) {
            newX = x + i;
             newY = y + j;
            if (newX >= 0 && newX < taille && newY >= 0 && newY < taille && grille[newX][newY] == ' ') {
                return 1;  
            }
        }
    }
    return 0;  
}


void mettreAJourCase(int x, int y) {
    int cell_size = 50;
    int x_start = (LARGEUR_FENETRE - (choisirTaille * cell_size)) / 2;
    int y_start = 100;

    
    if (grille[x][y] == 'X') {
        ChoisirCouleurDessin(CouleurParNom("grey"));  
    } else if (grille[x][y] == 'A') {
        ChoisirCouleurDessin(CouleurParNom("red"));   
    } else if (grille[x][y] == 'B') {
        ChoisirCouleurDessin(CouleurParNom("blue")); 
    } else {
        ChoisirCouleurDessin(CouleurParNom("white")); 
    }

   
    RemplirRectangle(x_start + y * cell_size, y_start + x * cell_size, cell_size, cell_size);
    ChoisirCouleurDessin(CouleurParNom("black"));
    DessinerRectangle(x_start + y * cell_size, y_start + x * cell_size, cell_size, cell_size);
}


int estPartieTerminee(int x, int y, int taille) {
    int newX, newY, i;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};  /* Toutes les directions (y compris diagonales) */
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};  /* pour une vérification complète */

    /* Parcourt toutes les cases adjacentes */
    for (i = 0; i < 8; i++) {
        newX = x + dx[i];
        newY = y + dy[i];

        /* Vérifie que chaque case adjacente est bien dans les limites et libre */
        if (newX >= 0 && newX < taille && newY >= 0 && newY < taille) {
            if (grille[newX][newY] == ' ') {  /* Si au moins une case libre existe */
                return 0;  /* La partie n'est pas terminée */
            }
        }
    }

    /* Si aucune case adjacente n'est libre */
    return 1;
}
