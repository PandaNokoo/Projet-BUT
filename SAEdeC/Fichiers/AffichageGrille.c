#include "AffichageGrille.h"
#include "CreationGrille.h"
#include <graph.h>
#include "constantes.h"

/* Affiche la grille de jeu avec couleurs pour chaque joueur */
void afficherGrilleJeu(int taille) {
    int cell_size = 50; /* Taille d'une cellule */
    int totalWidth = taille * cell_size;
    int totalHeight = taille * cell_size;

    int x_start = (LARGEUR_FENETRE - totalWidth) / 2; /* Calcul pour centrer la grille*/
    int y_start = (HAUTEUR_FENETRE - totalHeight) / 2;
    int border_thickness = 3; 

    int i, j, k;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            
            /* Couleur selon le contenu de la cellule */
            if (grille[i][j] == 'X') {
                ChoisirCouleurDessin(CouleurParNom("grey")); 
            } 
            else if (grille[i][j] == 'A') {
                ChoisirCouleurDessin(CouleurParNom("red"));   
            } 
            else if (grille[i][j] == 'B') {
                ChoisirCouleurDessin(CouleurParNom("blue"));  
            } 
            else {
                ChoisirCouleurDessin(CouleurParNom("white")); 
            }
            
            /* Remplit la cellule de la grille */
            RemplirRectangle(x_start + j * cell_size, y_start + i * cell_size, cell_size, cell_size);

            /* Dessine la bordure de la cellule */
            ChoisirCouleurDessin(CouleurParNom("black"));
            for (k = 0; k < border_thickness; k++) {
                DessinerRectangle(
                    x_start + j * cell_size + k, 
                    y_start + i * cell_size + k,
                    cell_size - 2 * k, 
                    cell_size - 2 * k
                );
            }
        }
    }
}

/* Affiche une grille vide centrée avec des bordures noires */
void afficherGrille(int taille) {
    int x_start = (LARGEUR_FENETRE - (taille * 50)) / 2; 
    int y_start = 100; /* Position de départ de la grille en y */
    int cell_size = 50; 

    int i, j;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            
            ChoisirCouleurDessin(CouleurParNom("white")); 
            RemplirRectangle(x_start + j * cell_size, y_start + i * cell_size, cell_size, cell_size); 

            ChoisirCouleurDessin(CouleurParNom("black")); 
            DessinerRectangle(x_start + j * cell_size, y_start + i * cell_size, cell_size, cell_size); 
        }
    }
}
